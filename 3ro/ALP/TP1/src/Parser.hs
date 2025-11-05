module Parser where

import           Text.ParserCombinators.Parsec
import           Text.Parsec.Token
import           Text.Parsec.Language           ( emptyDef )
import           AST

-----------------------
-- Función para facilitar el testing del parser.
totParser :: Parser a -> Parser a
totParser p = do
  whiteSpace lis
  t <- p
  eof
  return t

-- Analizador de Tokens
lis :: TokenParser u
lis = makeTokenParser
  (emptyDef
    { commentStart    = "/*"
    , commentEnd      = "*/"
    , commentLine     = "//"
    , opLetter        = char '='
    , reservedNames   = ["true", "false", "skip", "if", "else", "repeat", "until", "case"]
    , reservedOpNames = [ "+"
                        , "-"
                        , "*"
                        , "/"
                        , "<"
                        , ">"
                        , "&&"
                        , "||"
                        , "!"
                        , "="
                        , "=="
                        , "!="
                        , ";"
                        , ","
                        , "++"
                        ]
    }
  )

-----------------------------------
--- Parser de expresiones enteras
-----------------------------------
intexp :: Parser (Exp Int)
intexp = pOp1

pOp1 :: Parser (Exp Int)
pOp1 = chainl1 pOp2 getOp1

pOp2 :: Parser (Exp Int)
pOp2 = chainl1 pFactor getOp2

pFactor :: Parser (Exp Int)
pFactor =
  try (pUMinus) <|> 
  try (pVarOp) <|> 
  try (parens lis intexp) <|> 
  pConst

pConst :: Parser (Exp Int)
pConst = do 
  n <- integer lis
  return (Const (fromInteger n))


pVarOp :: Parser (Exp Int)
pVarOp = do 
  v <- identifier lis
  do 
    try (reservedOp lis "++")
    return (VarInc v)
   <|> (return (Var v))

pUMinus :: Parser (Exp Int)
pUMinus = do 
  reservedOp lis "-"
  e <- intexp;
  return (UMinus e)

getOp1 :: Parser (Exp Int -> Exp Int -> Exp Int)
getOp1 = do 
  try (reservedOp lis "+")
  return (Plus)
  <|> 
  do 
    try (reservedOp lis "-")
    return (Minus)
                 
getOp2:: Parser (Exp Int -> Exp Int -> Exp Int)
getOp2 = do 
  try (reservedOp lis "*")
  return (Times) 
  <|> 
  do 
    try (reservedOp lis "/")
    return (Div)
------------------------------------
--- Parser de expresiones booleanas
------------------------------------
boolexp :: Parser (Exp Bool)
boolexp = pOr

pOr :: Parser (Exp Bool)
pOr = chainl1 pAnd pAndOp

pAnd :: Parser (Exp Bool)
pAnd = chainl1 pBFactor pOrOp

pBFactor :: Parser (Exp Bool)
pBFactor = try (pNot) <|>
           try (pCompOp) <|>
           try (pBoolConst) <|>
           parens lis boolexp

pBoolConst :: Parser (Exp Bool)
pBoolConst = do 
  try (reserved lis "true")
  return (BTrue)
 <|> do
  try (reserved lis "false")
  return (BFalse)

pNot :: Parser (Exp Bool)
pNot = do 
  (reservedOp lis "!")
  b <- boolexp
  return (Not b)

pOrOp :: Parser (Exp Bool -> Exp Bool -> Exp Bool)
pOrOp = do
  try (reservedOp lis "||")
  return (Or)

pAndOp :: Parser (Exp Bool -> Exp Bool -> Exp Bool)
pAndOp = do
  try (reservedOp lis "&&")
  return (And)

pCompOp :: Parser (Exp Bool)
pCompOp = do 
  e1 <- intexp
  op <- (try pCompareOp <|> pEqOp)
  e2 <- intexp
  return (op e1 e2)

pEqOp :: Parser (Exp Int -> Exp Int -> Exp Bool)
pEqOp = do 
  try (reservedOp lis "==")
  return (Eq)
  <|> do 
    try (reservedOp lis "!=")
    return (NEq)

pCompareOp :: Parser (Exp Int -> Exp Int -> Exp Bool)
pCompareOp = do 
  try (reservedOp lis "<")
  return (Lt)
 <|> do 
  try (reservedOp lis ">")
  return (Gt)
-----------------------------------
--- Parser de comandos
-----------------------------------
comm :: Parser Comm
comm = pSeq

basicComm :: Parser Comm
basicComm = 
  try (pSkip) <|>
  try (pLet) <|>
  try (pIfThenElse) <|>
  try (pRepeatUntil) <|>
  pCase 

pSkip :: Parser Comm
pSkip = do 
  reserved lis "skip"
  return Skip

pLet :: Parser Comm
pLet = do 
  v <- identifier lis
  reservedOp lis "="
  e <- intexp
  return (Let v e)

seqOp :: Parser (Comm -> Comm -> Comm)
seqOp = do 
  try (reservedOp lis ";")
  return (Seq)

pSeq :: Parser Comm
pSeq = try (chainl1 basicComm seqOp)

pIfThenElse :: Parser Comm
pIfThenElse = do 
  reserved lis "if"
  b <- boolexp
  c1 <- (braces lis comm)
  do 
    try (reserved lis "else")
    c2 <- (braces lis comm)
    return (IfThenElse b c1 c2)
    <|> 
    return (IfThen b c1)

pRepeatUntil :: Parser Comm
pRepeatUntil = do 
  reserved lis "repeat"
  c <- (braces lis comm)
  reserved lis "until"
  b <- boolexp
  return (RepeatUntil c b)

pCase :: Parser Comm
pCase = do reserved lis "case"
           symbol lis "{"
           xs <- pCaseCase
           return (Case xs)
           
pCaseCase :: Parser [(Exp Bool, Comm)]
pCaseCase = do 
  try (symbol lis "}")
  return []
  <|> 
  do 
    b <- boolexp
    reservedOp lis ":"
    symbol lis "{"
    c <- comm
    symbol lis "}"
    rest <- pCaseCase
    return ((b,c):rest)
------------------------------------
-- Función de parseo
------------------------------------
parseComm :: SourceName -> String -> Either ParseError Comm
parseComm = parse (totParser comm)
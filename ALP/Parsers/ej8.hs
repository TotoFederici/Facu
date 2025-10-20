import Parsing
import Control.Applicative

data Expr = Num Int | BinOp Op Expr Expr deriving Show
data Op = Add | Mul | Min | Div deriving Show

pExpr :: Parser Expr
pExpr = do t <- pTerm
           e <- pExpr'
           return (e t)

pExpr' :: Parser (Expr -> Expr)
pExpr' = pSum <|> pMin <|> pEmpty

pSum :: Parser (Expr -> Expr)
pSum = do symbol "+"
          t <- pTerm
          e <- pExpr'
          return (\s -> e (BinOp Add s t))

pMin :: Parser (Expr -> Expr)
pMin = do symbol "-"
          t <- pTerm
          e <- pExpr'
          return (\s -> e (BinOp Min s t))

pTerm :: Parser Expr
pTerm = do f <- pFactor
           t <- pTerm'
           return (t f)

pTerm' :: Parser (Expr -> Expr)
pTerm' = pMul <|> pDiv <|> pEmpty

pMul :: Parser (Expr -> Expr)
pMul = do symbol "*"
          f <- pFactor
          t <- pTerm'
          return (\s -> t (BinOp Mul s f))

pDiv :: Parser (Expr -> Expr)
pDiv = do symbol "/"
          f <- pFactor
          t <- pTerm'
          return (\s -> t (BinOp Div s f))

pEmpty :: Parser (Expr -> Expr)
pEmpty = return (\s -> s)

pFactor :: Parser Expr
pFactor = do symbol "("
             e <- pExpr
             symbol ")"
             return e
          <|> do n <- int
                 return (Num n)
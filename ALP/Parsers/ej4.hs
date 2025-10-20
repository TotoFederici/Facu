import Parsing
import Control.Applicative

data Expr = Num Int | BinOp Op Expr Expr deriving Show
data Op = Add | Mul | Min | Div deriving Show

expr :: Parser Expr
expr =  do t <- term
           do symbol "+"
              e <- expr
              return (BinOp Add t e)
            <|> do symbol "-"
                   e <- expr
                   return (BinOp Min t e)
             <|> return t

term :: Parser Expr
term =  do f <- factor
           do symbol "*"
              t <- term
              return (BinOp Mul f t)
            <|> do symbol "/"
                   t <- term
                   return (BinOp Div f t)
             <|> return f

factor :: Parser Expr
factor =  do symbol "("
             e <- expr
             symbol ")"
             return e
           <|> do n <- natural
                  return (Num n)

eval :: String -> Expr
eval xs = fst (head (parse expr xs))
import Parsing
import Control.Applicative

data Hasktype = DInt | DChar | DFloat | Fun Hasktype Hasktype deriving Show

pHType :: Parser Hasktype
pHType = do string "Int"
            return DInt
         <|> do string "Char"
                return DChar
             <|> do string "Float"
                    return DFloat

pType :: Parser Hasktype
pType = do symbol "("
           v <- pFun
           symbol ")"
           return v
        <|> do t <- pHType
               return t

pFun :: Parser Hasktype
pFun = do x <- pType
          do space
             symbol "-"
             symbol ">"
             space
             xs <- pFun
             return (Fun x xs)
          <|> return x
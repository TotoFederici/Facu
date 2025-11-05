import Parsing
import Control.Applicative

data Basetype = DInt | DChar | DFloat deriving Show
type Hasktype = [Basetype]

pBasetype :: Parser Basetype
pBasetype = do string "Int"
               return DInt
            <|> do string "Char"
                   return DChar
                <|> do string "Float"
                       return DFloat

pHasktype :: Parser Hasktype
pHasktype = do x <- pBasetype
               do space
                  symbol "-"
                  symbol ">"
                  space
                  xs <- pHasktype
                  return (x:xs)
               <|> return [x]


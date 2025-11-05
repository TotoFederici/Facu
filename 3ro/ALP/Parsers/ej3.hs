import Parsing
import Control.Applicative

paren :: Parser a -> Parser a
paren p = do symbol "("
             v <- p
             return v
           <|> p
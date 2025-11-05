import Parsing
import Control.Applicative

data HType = DChar Char | DInt Int deriving Show
type HList = [HType]

pType :: Parser HType
pType = do d <- int
           return (DInt d)
        <|> do symbol "'"
               c <- item
               symbol "'"
               return (DChar c)

pList :: Parser HList
pList = do v <- pType
           do symbol ","
              vs <- pList
              return (v:vs)
             <|> return [v] 

pHList :: Parser HList
pHList = do symbol "["
            x <- pList
            symbol "]"
            return x
module LeerN where

main :: IO String
main = do putStrLn "Insertar un numero:"
          n <- getLine
          putStr ">$ "
          s <- leerN (read n)
          putStrLn s
          return s

leerN :: Int -> IO String
leerN n = sequenceA (replicate n getChar)
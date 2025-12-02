module Adivinar where

main :: IO ()
main = do n <- elegir
          adivinar n

elegir :: IO Int
elegir = do putStrLn "Ingresa el numero secreto:"
            n <- getLine
            return (read n)

adivinar :: Int -> IO ()
adivinar n = do putStrLn "Guess: "
                g <- getLine
                if (read g) == n then putStrLn "Ganasteeeee!!!"
                                 else if (read g) < n then do putStrLn "Te quedaste corto"
                                                              adivinar n
                                                      else do putStrLn "Te pasaste"
                                                              adivinar n
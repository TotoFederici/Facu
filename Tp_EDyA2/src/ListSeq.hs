module ListSeq where

import Seq
import Par

instance Seq [] where
  emptyS = []

  singletonS x = [x]

  lengthS = length

  nthS [] _ = error "Index muy grande"
  nthS (x:xs) 0 = x
  nthS xs n | n < 0 = error "Index negativo"
            | otherwise = nthS xs (n-1)

  tabulateS f n = tabulateS' 0
            where tabulateS' i | i == n = []
                               | otherwise = let (fi, xs') = f i ||| tabulateS' (i+1)
                                             in fi : xs'
                                   
  mapS _ [] = []
  mapS f (x:xs) = let (fi, xs') = f x ||| mapS f xs
                  in fi : xs'
                  
  filterS _ [] = [] 
  filterS p (x:xs) = let (px, xs') = p x ||| filter p xs
                     in if px then x:xs' else xs'

  appendS = (++)
  
  takeS s i = take i s

  dropS s i = drop i s

  showtS [] = EMPTY
  showtS [x] = ELT x
  showtS xs = let p = 2 ^ ilg ((lengthS xs) - 1)
                  (l,r) = (takeS xs p) ||| (dropS xs p)
              in NODE l r
            where ilg n = floor (logBase 2 (fromIntegral n))

  showlS [] = NIL
  showlS (x:xs) = CONS x xs

  joinS = concat

  reduceS _ e [] = e
  reduceS f e s = f e (reduceS' s)
        where reduceS' s = let t = showtS s
                           in case t of
                               ELT a -> a
                               NODE l r -> f (reduceS f e l) (reduceS f e r)

  scanS = undefined
  fromList s = s
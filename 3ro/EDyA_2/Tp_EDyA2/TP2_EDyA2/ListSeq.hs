module ListSeq where

import Seq
import Par

instance Seq [] where
  emptyS = []

  singletonS x = [x]

  lengthS = length

  nthS [] _ = error "Index muy grande"
  nthS (x:xs) 0 = x
  nthS (x:xs) n | n < 0 = error "Index negativo"
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
  showtS xs = let p = (div (lengthS xs) 2)
                  (l,r) = (takeS xs p) ||| (dropS xs p)
              in NODE l r

  showlS [] = NIL
  showlS (x:xs) = CONS x xs

  joinS = concat

  reduceS _ e [] = e
  reduceS f e s = f e (reduceS' s (lengthS s))
    where reduceS' s l | l == 1 = nthS s 0
                       | otherwise = let mid = div (l+1) 2
                                     in reduceS' (tabulateS (\i -> if (2*i+1 >= l)
                                                                   then nthS s (l-1) 
                                                                   else f (nthS s (2*i)) (nthS s (2*i+1))) mid) mid

  scanS f b [] = ([],b) 
  scanS f b [x] = ([b],(f b x))
  scanS f b s = let s' = contraer s
                    (s'', a) = scanS f b s'
                    s''' = expandir s s''
                in (s''', a)
    where contraer [] = []
          contraer [x] = [x]
          contraer (x:y:xs) = let (op, xs') = ((f x y) ||| contraer xs)
                              in op : xs'
          expandir s1 s2 = tabulateS (\i -> if (even i) 
                                            then nthS s2 (div i 2)
                                            else f (nthS s2 (div i 2)) (nthS s1 (i-1))) (lengthS s1)                  

  fromList s = s

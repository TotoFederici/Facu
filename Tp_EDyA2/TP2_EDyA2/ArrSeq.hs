module ArrSeq where

import Seq
import Par
import Arr as A

instance Seq Arr where
  emptyS = A.empty

  singletonS x = A.fromList [x]

  lengthS = A.length

  nthS = (!)

  tabulateS  = A.tabulate

  mapS f a = let len = lengthS a
             in tabulateS (\i -> f (nthS a i)) len

  filterS p a | len == 1 = if p (nthS a 0) then a else emptyS -- else emptyS 
              | otherwise = let (s1 ,s2) = (A.subArray 0 (div (len-1) 2) a ||| A.subArray (div len 2) (len-1) a) 
                                (l,r) = ((filterS p s1) ||| (filterS p s2))
                            in appendS l r
    where len = lengthS a

  appendS a1 a2 = let (l1,l2) = (lengthS a1 ||| lengthS a2)
                  in tabulateS (\i -> if i < l1 then (nthS a1 i) else (nthS a2 (i-l1))) (l1+l2)

  takeS a n = tabulateS (\i-> nthS a i) n

  dropS a n = (A.subArray n (lengthS a) a) --en este caso habria que chequear que sea sobre indice o como

  showtS a | len == 0 = EMPTY
           | len == 1 = ELT (nthS a 0)
           | otherwise = let(a1,a2)=(A.subArray 0 (div (len-1) 2) a ||| A.subArray (div len 2) (len-1) a) 
                         in NODE a1 a2 
    where len = lengthS a

  showlS a | (lengthS a) == 0 = NIL
           | otherwise = CONS (nthS a 0) (dropS a 1)

  joinS      = A.flatten

  reduceS f e a = f e (reduceS' a (lengthS a))
    where reduceS' a l | l == 1 = nthS a 0
                       | otherwise = let mid = div (l+1) 2
                                     in reduceS' (tabulateS (\i -> if (2*i+1 >= l)
                                                                   then nthS a (l-1) 
                                                                   else f (nthS a (2*i)) (nthS a (2*i+1))) mid) mid

  scanS f e a = scanS' a (lengthS a)
    where scanS' a l | l == 0 = (emptyS, e)
                     | l == 1 = (singletonS e, f e (nthS a 0))
                     | otherwise = let mid = div (l+1) 2
                                       a' = contraer a mid l
                                       (a'', u) = scanS' a' mid
                                       a''' = expandir a a'' l
                                   in (a''', u)
          contraer a mid l = tabulateS (\i -> if (2*i+1 >= l)
                                              then nthS a (l-1)
                                              else (f (nthS a (2*i)) (nthS a (2*i+1)))) mid
          expandir a1 a2 l = tabulateS (\i -> if (even i) 
                                          then nthS a2 (div i 2)
                                          else f (nthS a2 (div i 2)) (nthS a1 (i-1))) l                

  fromList   = A.fromList
module ArrSeq where

import Seq
import Par
import Arr as A

instance Seq Arr where

  emptyS = A.empty
  
  singletonS x = A.fromList [x]
  
  nthS  = A.(!)

  tabulateS  = A.tabulate

  mapS f a = let len = lengthS a
                 mid = (div len 2)
                 (s1 ,s2) = (A.subArray 0 mid a ||| A.subArray mid mid a)
                 l1 = lengthS s1
             in tabulateS (\i -> if i < l1 then f (nthS s1 i) else f (nthS s2 (i-l1))) len-1 --el "i-l1" supongo yo que tiene sentido
          
  filterS p a | len == 1 = if p (nthS a 0) then a else emptyS -- else emptyS 
              | otherwise = let (s1 ,s2) = (A.subArray 0 (div (len-1) 2) a ||| A.subArray (div len 2) (len-1) a) 
                                (l,r) = ((filterS p s1) ||| (filterS p s2))
                            in appendS l r
            where len = lengthS a
              

  appendS a1 a2 = let (l1,l2) = (lengthS a1 ||| lengthS a2)
                  in tabulateS (\i -> if i < l1 then (nthS a1 i) else (nthS a2 (i-l1))) (l1+l2)
                  

  takeS a n = tabulateS (\i-> nthS a i) n
  dropS a n = (A.subArray n (lengthS a) a) --en este caso habria que chequear que sea sobre indice o como
  
  showtS emptyS = EMPTY
  showtS a | len == 1 = ELT (nthS a 0)
           | otherwise = let(a1,a2)=(A.subArray 0 (div (len-1) 2) a ||| A.subArray (div len 2) (len-1) a) 
                         in NODE a1 a2 
            where len = lengthS a

  showlS emptyS = NIL
  showlS a      = CONS (nthS a 0) (dropS a 1)

  joinS      = A.flatten

  reduceS f e a = f e (reduceS' f a)
                  where reduceS' f a | lengthS a == 1 = nthS a 0
                                     | otherwise = let len = lengthS a
                                                       ilg = floor (logBase 2 (fromIntegral len-1))
                                                       (a1,a2) = (A.subArray 0 (div (ilg) 2) a ||| A.subArray ilg (len-1) a)
                                                       (l,r) = (reduceS' f a1 ||| reduceS' f a2 )
                                                   in f l r 

  scanS _ e emptyS = (singletonS e, e)
  scanS f e a | len == 1 = (singletonS e, f e (nthS a 0))
              | otherwise = let a' = contraer a
                                (a'', u) = scanS f e a'
                                a''' = expandir a a''
                            in (a''', u)
              where len = lengthS a
                    contraer a = let mid = div len 2
                                 in if even(len)
                                    then tabulateS (\i -> (f (nthS a (2*i)) (nthS a (2*i+1)))) mid
                                    else tabulateS (\i -> if i == mid
                                                          then nthS a (len-1)
                                                          else (f (nthS a (2*i)) (nthS a (2*i+1)))) mid
                    expandir a1 a2 = tabulateS (\i -> if (even i) 
                                                      then nthS a2 (div i 2)
                                                      else f (nthS a2 (div i 2)) (nthS a1 (i-1))) (lengthS a1) 
                          

--(fromList[0,6,9], 13) == (scanS (+) 0 s3)
--s3=fromList [6,3,4]
  fromList   = A.fromList
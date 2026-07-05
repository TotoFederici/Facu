-- TestTree (Secuencia: 10 5 15 2 1 8) (Node 6 (Node 2 (Node 1 (Empty) 10 (Empty)) 5 (Empty)) 15 (Node 3 (Node 1 (Empty) 2 (Empty)) 1 (Node 1 (Empty) 8 (Empty))))

data BTree a = Empty | Node Int (BTree a) a (BTree a) deriving Show


(|||) :: a -> b -> (a,b)
x ||| y = (x,y)

size :: BTree a -> Int
size Empty = 0
size (Node n _ _ _) = n

nth :: BTree a -> Int -> a
nth Empty _ = error "INDEX ERROR"
nth (Node n l x r) i | i == sl = x
                     | i < sl = nth l i
                     | otherwise = nth r (i-sl-1)
                where sl = size l

cons :: a -> BTree a -> BTree a
cons a Empty = (Node 1 Empty a Empty)
cons a (Node n l x r) = (Node (n+1) (cons a l) x r)

tabulate :: (Int -> a) -> Int -> BTree a
tabulate f 0 = Node 1 Empty (f 0) Empty
tabulate f n = cons (f n) (tabulate f (n-1))



mapT :: (a -> b) -> BTree a -> BTree b
mapT _ Empty = Empty
mapT f (Node n l x r) = let ((l',r'), x') = (mapT f l ||| mapT f r) ||| (f x)
                        in (Node n l' x' r')


takeT :: Int -> BTree a -> BTree a

takeT _ Empty = Empty
takeT i (Node n l x r) | i == sl = l
                       | i > sl = Node i l x r'
                       | otherwise = l'
                    where ((l',r'),sl) = ((takeT i l) ||| (takeT (i-(size l)-1) r)) ||| (size l) 


dropI :: Int -> BTree a -> BTree a

dropI _ Empty =error "INDEX ERROR"
dropI i (Node n l x r) |i == sl = r
                       |i > sl = r'
                       |otherwise = (Node (n-i-1) l' x r)
                       where ((l',r'),sl) = (((dropI i l) ||| (dropI (i-sl-1) r)) ||| (size l))

dropT :: Int -> BTree a -> BTree a

dropT _ Empty = Empty
dropT i (Node n l x r) | i==sl = Node (n-i) Empty x r
                       | i > sl = r'
                       | otherwise = (Node (n-i) l' x r)
                       where ((l',r'),sl)=(((dropT i l) ||| (dropT (i-sl-1) r)) |||(size l))

------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------

data Tree a = E| Leaf a | Join (Tree a) (Tree a) deriving Show

mapt :: (a -> b) -> Tree a -> Tree b
mapt _ E = E
mapt f (Leaf a) = Leaf (f a)
mapt f (Join l r) = Join (mapt f l) (mapt f r)

aux_reduce :: (a ->a-> a) -> Tree a -> a
aux_reduce f (Leaf a) = a
aux_reduce f (Join l r) = f (aux_reduce f l) (aux_reduce f r)

reduce ::(a ->a-> a) -> a -> Tree a -> a
reduce f e t = f e (aux_reduce f t)

combine :: (Num a , Ord a) => (a,a,a,a) -> (a,a,a,a) -> (a,a,a,a)
combine (m,p,s,t) (m',p',s',t') =(max (max (s+p') m) m',
                                  max p (t+p'),
                                  max s' (s+t'),
                                  t+t')

base :: (Num a, Ord a) => a -> (a,a,a,a)
base v = let v'= (max v 0) in (v',v',v',v)

val :: (Num a, Ord a) => (a,a,a,a)
val = (0,0,0,0)

mcss :: (Num a , Ord a) => Tree a -> a
mcss t = let (x1,x2,x3,x4) = (reduce combine val (mapt base t)) in x1 

--(Join (Join (Join (Leaf 82) (Leaf (-80))) (Join (Leaf 57) (Leaf 61))) (Join (Leaf (-1)) (Leaf 9))) 

-------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------
{- intercambiar :: Tree a -> Tree a
intercambiar E = E
intercambiar (Leaf a) = E
intercambiar (Join (Leaf a) r) = r
intercambiar (Join l r) = (Join (intercambiar l) r)  

sufijos :: Tree Int -> Tree(Tree Int)
sufijos E =Leaf E
sufijos (Leaf a)= (Leaf E)
sufijos t@(Join (Leaf a) r) = let n_t = (intercambiar t) in (Join (Leaf n_t) (sufijos n_t))
sufijos t@(Join l r)= let n_t = (intercambiar l) in (Join (sufijos l) (Leaf (Join n_t r)))  -}




-- t=Join (Join (Leaf 10) (Leaf 15)) (Leaf 20)


sufijos :: Tree Int -> Tree(Tree Int)
sufijos E = Leaf E
sufijos (Leaf _) = Leaf E
sufijos (Join l r) = Join (buildSufijos l r) (sufijos r)

buildSufijos :: Tree Int -> Tree Int -> Tree(Tree Int)
buildSufijos (Leaf _) r = Leaf r
buildSufijos (Join l r1) r2 = Join (buildSufijos l (Join r1 r2)) (buildSufijos r1 r2)


conSufijos :: Tree Int -> Tree(Int , Tree Int)
conSufijos E = (Leaf (error "Terrible paparulo" , E))
conSufijos (Leaf a) = Leaf (a, E)
conSufijos (Join l r) = Join (buildconSufijos l r) (conSufijos r)

buildconSufijos :: Tree Int -> Tree Int -> Tree(Int,Tree Int)
buildconSufijos (Leaf a) r = Leaf (a, r)
buildconSufijos (Join l r1) r2 = Join (buildconSufijos l (Join r1 r2)) (buildconSufijos r1 r2)


maxT :: Tree Int -> Int
maxT E = 0
maxT t = aux_reduce max t 

maxAll :: Tree(Tree Int) -> Int 
maxAll t = maxT (mapt maxT t)

restaTuplFunction :: (Int , Tree Int) -> Int
restaTuplFunction (a,t) = (maxT t) - a 

mejorGanancia :: Tree Int -> Int
mejorGanancia t = maxT (mapt restaTuplFunction (conSufijos t))

-------------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------------

data T a = Emp | N (T a) a (T a) deriving Show

--t1=N (N (N Emp 10 Emp) 7 (N Emp 5 Emp)) 29 (N Emp 3 Emp)
--t2= N (N (N Emp 89 Emp) 21 (N (N Emp 35 Emp) 76 Emp)) 0 Emp

altura :: T a -> Int 
altura Emp = 0
altura (N l a r) = 1+ (max (altura l) (altura r))

combinar :: T a -> T a -> T a

combinar Emp t = t
combinar (N l x r) t = N (combinar l r) x t 

{- NO' LA RE VOLAMO'
combinar Emp t = t
combinar t Emp = t
combinar (N Emp x r) t = (N t x r) 
combinar (N l x Emp) t = (N l x t) 
combinar (N l x r) (N l' x' r')= (N(combinar (N l' x' Emp) l) x (combinar r r') )
-}

filterT :: (a -> Bool) -> T a -> T a

filterT p Emp = Emp
filterT p (N l x r) | p x = (N l' x r')
                    | otherwise = (combinar l' r')
                    where (l',r')= ((filterT p l) ||| (filterT p r))


quicksortT :: T Int -> T Int
quicksortT Emp = Emp
quicksortT t@(N l x r) = (N (quicksortT l') x (quicksortT r'))
                      where (l',r')= ((filterT (<x) t),(filterT (>x) t))

-------------------------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------------------------

--data BTree a = Empty | Node Int (BTree a) a (BTree a) deriving Show

splitT :: BTree a -> Int ->(BTree a , BTree a)
splitT t i = (takeT i t ||| dropT i t)


import Heap as H

data Tree a = LeafB a | NodeB (Tree a) a (Tree a) deriving Show

completo :: a -> Int -> Tree a
completo x 0 = LeafB x
completo x d = let z = (completo x (d-1)) in (NodeB z x z)

{- balanceado' :: a -> Int -> Int -> Tree a
balanceado' x i d = | i <= d =NodeB (balanceado' x (2*i) d) x (balanceado' x ((2*i)+1) d)
                    | otherwise 

balanceado :: a -> Int -> Tree a
balanceado  -}

data BST a = Leaf | Node (BST a) a (BST a) deriving Show

maximum' :: Ord a => BST a -> a
maximum' (Node _ a Leaf) = a
maximum' (Node _ _ r) = maximum' r

minimum' :: Ord a => BST a -> a
minimum' (Node Leaf a _) = a
minimum' (Node l _ _) = minimum' l

insertBST :: Ord a => a -> BST a -> BST a
insertBST a Leaf = (Node Leaf a Leaf)
insertBST a (Node l b r) | a <= b = (Node (insertBST a l) b r)
                         | otherwise = (Node l b (insertBST a r))

member :: Ord a => a -> BST a -> Bool
member a Leaf = False
member a (Node l b r) | a == b = True
                      | a < b = member a l
                      | otherwise = member a r

member2 :: Ord a => a -> BST a -> Bool
member2 _ Leaf = False
member2 a (Node Leaf b Leaf) = a == b
member2 a (Node l b r) | a <= b = (a == b) || (member2 a l)
                       | otherwise = (member2 a r)

checkBST :: Ord a => BST a -> Bool
checkBST Leaf = True
checkBST (Node l a r) = (((maximum' l) <= a) && ((minimum' r) > a) && (checkBST l) && (checkBST r))

delete' :: Ord a => BST a -> BST a 
delete' (Node Leaf b Leaf) = Leaf
delete' (Node Leaf b r) = r
delete' (Node l b Leaf) = l
delete' (Node l b r) = let y = minimum' r in Node l y (delete y r)

delete :: Ord a => a -> BST a -> BST a
delete _ Leaf  = Leaf
delete z t@(Node l b r) | z < b = Node (delete z l) b r
                        | z > b = Node l b (delete z r)
                        | z == b = delete' t

------------------------------------------------------------------------------------------------------------------

data Color = R | B deriving Show
data RBT a = E | T Color (RBT a) a (RBT a) deriving Show

memberRBT :: Ord a => a -> RBT a -> Bool
memberRBT a E = False
memberRBT a (T _ l b r) | a == b = True
                      | a < b = memberRBT a l 
                      | a > b = memberRBT a r

balance :: Color -> RBT a -> a -> RBT a -> RBT a
balance B (T R (T R a x b) y c) z d = T R (T B a x b) y (T B c z d)
balance B (T R a x (T R b y c)) z d = T R (T B a x b) y (T B c z d)
balance B a x (T R (T R b y c) z d) = T R (T B a x b) y (T B c z d)
balance B a x (T R b y (T R c z d)) = T R (T B a x b) y (T B c z d)
balance c l a r = T c l a r

balancel :: Color -> RBT a -> a -> RBT a -> RBT a
balancel B (T R (T R a x b) y c) z d = T R (T B a x b) y (T B c z d)
balancel B (T R a x (T R b y c)) z d = T R (T B a x b) y (T B c z d)
balancel c l a r = T c l a r

balancer :: Color -> RBT a -> a -> RBT a -> RBT a
balancer B a x (T R (T R b y c) z d) = T R (T B a x b) y (T B c z d)
balancer B a x (T R b y (T R c z d)) = T R (T B a x b) y (T B c z d)
balancer c l a r = T c l a r

insert :: Ord a => a -> RBT a -> RBT a
insert x t = makeBlack (ins x t)
    where ins x E = T R E x E
          ins x (T c l y r) | x < y = balancel c (ins x l) y r
                            | x > y = balancer c l y (ins x r)
                            | otherwise = T c l y r
          makeBlack E = E
          makeBlack (T _ l x r) = T B l x r

-----------------------------------------------------------------------------------------------------------------------

data Tree123 a = E123 | T2 a (Tree123 a) (Tree123 a) | T3 a a (Tree123 a) (Tree123 a) (Tree123 a) | T4 a a a (Tree123 a) (Tree123 a) (Tree123 a) (Tree123 a) deriving Show

rbt2tree123 :: RBT a -> Tree123 a
rbt2tree123 E = E123
rbt2tree123 (T R l x r) = rbt2tree123 (T B l x r)
rbt2tree123 (T B l@(T R ll xl rl) x r@(T R lr xr rr)) = (T4 xl x xr (rbt2tree123 ll) (rbt2tree123 rl) (rbt2tree123 lr) (rbt2tree123 rr))
rbt2tree123 (T B l@(T R ll xl rl) x r) = (T3 xl x (rbt2tree123 ll) (rbt2tree123 rl) (rbt2tree123 r))
rbt2tree123 (T B l x r@(T R lr xr rr)) = (T3 x xr (rbt2tree123 l) (rbt2tree123 lr) (rbt2tree123 rr))
rbt2tree123 (T B l x r) = (T2 x (rbt2tree123 l) (rbt2tree123 r)) 

-- (insert 1 (insert 6 (insert 0 (insert 4 (insert 9 (insert (-2) (insert 7 (insert 15 (insert 2 (insert (-6) (insert 20 (insert 5 (insert (-1) E)))))))))))))

--------------------------------------------------------------------------------------------------------------------

fromList :: Ord a => [a] -> H.Heap a
fromList [] = H.empty
fromList (x:xs) = H.merge (H.makeH x H.empty H.empty) (fromList xs)

---------------------------------------------------------------------------------------------------------------------

data PHeaps a = Empty | Root a [PHeaps a] deriving Show

isPHeap :: Ord a => PHeaps a -> Bool
isPHeap Empty = True
isPHeap (Root a lh) = rootLeq a lh && childPHeap lh
    where rootLeq a [] = True
          rootLeq a (Empty:hs) = rootLeq a hs
          rootLeq a (h@(Root b _):hs) = (a <= b) && (rootLeq a hs)
          childPHeap [] = True
          childPHeap (Empty:hs) = childPHeap hs
          childPHeap (h:hs) = isPHeap h && childPHeap hs

mergePHeap :: Ord a => PHeaps a -> PHeaps a -> PHeaps a
mergePHeap h1 Empty = h1
mergePHeap Empty h2 = h2
mergePHeap h1@(Root x1 hs1) h2@(Root x2 hs2) | x1 <= x2 = (Root x1 (hs1 ++ [h2]))
                                             |otherwise = (Root x2 (hs2 ++ [h1]))

insertPHeaps :: Ord a => PHeaps a -> a -> PHeaps a
insertPHeaps h a = mergePHeap h (Root a [])

concatPHeaps :: Ord a => [PHeaps a] -> PHeaps a
concatPHeaps [] = Empty
concatPHeaps (h:hs) = mergePHeap h (concatPHeaps hs)

delMinPHeaps :: Ord a => PHeaps a -> Maybe (a, PHeaps a)
delMinPHeaps Empty = Nothing
delMinPHeaps (Root a hs) = Just (a, concatPHeaps hs)

-- (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps (insertPHeaps Empty 6) 7) (-8)) (-2)) 8) 3) 5) 0) (-12)) 20) 5) 2) 1)
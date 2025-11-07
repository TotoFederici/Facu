{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE TypeApplications #-}
{-# LANGUAGE ImpredicativeTypes #-}

-- En este archivo voy a (Intentar) implementar los ejercicios se Sistema F --
-- Terminos en sistema F: t := x | t t | \x:T.t | /\T.t | t <T>   (\ es lambda minuscula y /\ es lambda mayuscula)
-- Tipos                : T := B | T -> T | X | forall X.T

-- EJ 10 --

-- Sistema F --

{- 
double : forall X.(X -> X) -> X -> X
double = /\X.\f:X -> X.\x:X.f (f x)

doubleNat : (Nat -> Nat) -> Nat -> Nat
doubleNat = double <Nat>

doubleFun : ((Nat -> Nat) -> Nat -> Nat) -> (Nat -> Nat) -> Nat -> Nat
doubleFun = double <Nat -> Nat>

id : forall X.X -> X
id = /\X.\x:X.x

quadruple : forall X.(X -> X) -> X -> X
quadruple = /\X.\f:X -> X.\x:X. double f (double f x)
-}

-- Haskell --

double :: forall x . (x -> x) -> x -> x
double = \f -> \x -> f (f x)

doubleNat :: (Int -> Int) -> Int -> Int
doubleNat = double @Int

doubleFun :: ((Int -> Int) -> Int -> Int) -> (Int -> Int) -> Int -> Int
doubleFun = double @(Int -> Int)

id2 :: forall x . x -> x
id2 = \x -> x

quadruple :: forall x . (x -> x) -> x -> x
quadruple = \f -> \x -> double f (double f x)

-- EJ 11 --

-- Sistema F --

{- 
--------------Definicion de Bool, True y False--------------

-------Tipo Bool de Church-------

Bool = forall X.X -> X -> X

-------Constructores True y False-------

True : Bool
True = /\X.\t:X.\f.X.t

False : Bool
False = /\X.\t:X.\f.X.f

--------------Definicoin de And--------------

And : Bool -> Bool -> Bool
And = \p:Bool.\q:Bool.p <Bool> q False
-}

-- Haskell --

-- Definicion magica

checkCBool :: CBool -> Bool
checkCBool b = b True False

-- Fin de la magia --

-- Tipo y constructores --

type CBool = forall x . x -> x -> x

cTrue :: CBool
cTrue = \t f -> t

cFalse :: CBool
cFalse = \t f -> f

-- Fin de tipo y constructores --

cAnd :: CBool -> CBool -> CBool
cAnd = \p q -> p q cFalse

-- Seguir con Or, Not, etc

-- EJ 12 y 13--

-- Sistema F --

{- 
--------------Definicion de tipo, constructores de Nat--------------

-------Tipo Nat de Church-------

Nat = forall X.(X -> X) -> X -> X

-------Constructores de Nat-------

Zero : Nat
Zero = /\X.\s:X -> X.\z:X.z

Succ : Nat -> Nat
Succ = \n:Nat./\X.\s:X -> X.\z:X.s (n <X> s z)

--------------Definicion de suma--------------

suma : Nat -> Nat -> Nat
suma = \n:Nat.\m:Nat. n <Nat> (\x:Nat. Succ x) m

--------------Definicion de tipo, constructor y destructores de PairNat--------------

PairNat = forall X.(Nat -> Nat -> X) -> X

pairNat : Nat -> Nat -> PairNat
pairNat = \n:Nat.\m:Nat./\X.\f:Nat -> Nat -> Nat.f n m

fstNat : PairNat -> Nat
fstNat = \p:PairNat.P <Nat> (\x:Nat.\y:Nat.x)

sndNat : PairNat -> Nat
sndNat = \p:PairNat.P <Nat> (\x:Nat.\y:Nat.y)

--------------Definicion de pred y pred' usando tupling--------------

pred : Nat -> Nat
pred = \n:Nat.fstNat (pred' n)

pred' : Nat -> PairNat
pred' = \n:Nat.n <PairNat> (\p:PairNat.pairNat (sndNat p) n) (pairNat zero zero)
-}

-- Haskell --

-- Definiciones magicas --

checkNat :: Nat -> Int
checkNat n = runNat n (+1) 0

toNat :: Int -> Nat
toNat n | n == 0 = zero
        | otherwise = suc (toNat (n-1))

-- Fin de la magia --

-- Tipo y constructores --

newtype Nat = Nat { runNat :: forall x. (x -> x) -> x -> x }

zero :: Nat
zero = Nat (\s z -> z)

suc :: Nat -> Nat
suc = \n -> Nat (\s z -> s (runNat n s z)) 

-- Fin de tipo y constructores --

-- Truquito para poder hacer pred --
newtype PairNat = PairNat { runPairNat :: forall x. (Nat -> Nat -> x) -> x }
-- Fin del truquito

-- Estas defs usan funciones del truquito para que ande bien, en esencia es lo mismo --
pairNat :: Nat -> Nat -> PairNat
pairNat = \n m -> PairNat (\f -> f n m)

fstNat :: PairNat -> Nat
fstNat = \p -> runPairNat p (\n m -> n)

sndNat :: PairNat -> Nat
sndNat = \p -> runPairNat p (\n m -> m)
-- Fin de .... eso --

cSuma :: Nat -> Nat -> Nat
cSuma = \n m -> runNat n (\x -> suc x) m

cPred :: Nat -> Nat
cPred = \n -> fstNat (cPred' n)

cPred' :: Nat -> PairNat
cPred' = \n -> runNat n (\p -> pairNat (sndNat p) (suc (sndNat p))) (pairNat zero zero)

-- EJ 14 --

-- Sistema F --

{- 
--------------Definicion de tipo, constructores de Listas--------------

-------Tipo de listas de church-------

List X = forall R. (X -> R -> R) -> R -> R

-------Constructores de listas-------

nil : forall X. List X
nil = /\X./\R.\c:X -> R -> R.\n:R.n

cons : forall X. X -> List X -> List X
cons = /\X.\x:X.\xs:List X. /\R.\c:X -> R -> R.\n:R. c x (xs <R> c n)

--------------map, append, reverse y sumlist--------------

map : forall X. forall Y. (X -> Y) -> List X -> List Y
map = /\X./\Y.\f:X -> Y.\xs:List X. xs <List Y> (\x:X.\ys. cons (f x) ys) (nil <Y>)

append : forall X. ListX -> List X -> List X
append = /\X.\xs:List X.\ys:List X. xs <List X> (\x:X.\xss:List X. cons <X> x xss) ys

reverse : forall X. List X -> List X
reverse = /\X.\xs:List X. append <X> ys (cons <X> x (nil <X>)) (nil <X>)

sumlist : List Nat -> Nat
sumList = \ns:List Nat. ns <Nat> (\x:Nat.\m:Nat. suma n m)

--------------Definicion de pares generales (tipo, constructor y destructores)--------------

Pair X Y = forall z. (X -> Y -> Z) -> Z

pair :: forall X. forall Y. X -> Y -> Pair X Y
pair = /\X./\Y.\x:X.\y:Y. /\Z.\f:X -> Y -> Z. f x y

fstPair :: forall X. forall Y. Pair X Y -> X
fstPair = /\X./\Y.\p:Pair X Y. p <X> (\x:X.\y:Y. x)

sndPair :: forall X. forall Y. Pair X Y -> Y
sndPair = /\X./\Y.\p:Pair X Y. p <Y> (\x:X.\y:Y. y)

--------------Paramorfismo e insert--------------

param : forall X. forall Y. (X -> Pair Y (List X) -> Pair Y (List X)) -> Pair Y (List X) -> List X -> Pair Y (List X)
param = /\X./\Y.\c:X -> Pair Y (List X) -> Pair Y (List X).\n:Pair Y (List X).\xs:List X.
        xs <Pair Y (List X)>
        (\x:X.\p:Pair Y (List X). pair <Y> <List X> (fstPair <Y> <List X> (c x p)) (cons <X> x (sndPair <Y> <List X> p)))
        (pair <Y> <List X> (fstPair <Y> <List X> n) (nil <X>)
        
insert : forall X.(X -> X -> Bool) -> List X -> X -> List X
insert = /\X.\c:X -> X -> Bool.\xs:List X.\x:X. 
         fstPair <List X> <List X> (Param <X> <List X>
         (\y:X.\p:Pair (List X) (List X). (c x y) (pair <List X> <List X> (cons <X> x (cons <X> y (sndPair <List X> <List X> p))) (cons <X> y (sndPair <List X> <List X> p)))
                                                  (pair <List X> <List X> (cons <X> y (sndPair <List X> <List X> p)) (cons <X> y (sndPair <List X> <List X> p)))))
         (pair <List X> <List X> (cons <X> x nil <X>) nil <X>) xs
-}

-- Haskell --

-- Visualizer
checkList :: CList x -> [x]
checkList xs = runCList xs (:) []

cToList :: [x] -> CList x
cToList = foldr (cCons) cNil

-- Tipo de lista de church
newtype CList x = CList { runCList :: forall y. (x -> y -> y) -> y -> y }

-- Constructores
cNil :: forall x. CList x
cNil = CList (\c n -> n)

cCons :: forall x. x -> CList x -> CList x
cCons = \x xs -> CList (\c n -> c x (runCList xs c n))


-- map, append y reverse
cMap :: forall x. forall y. (x -> y) -> CList x -> CList y
cMap = \f xs -> runCList xs (\y ys -> cCons (f y) ys) cNil

cAppend :: forall x. CList x -> CList x -> CList x
cAppend = \xs ys -> runCList xs (\x xss -> cCons x xss) ys

cReverse :: forall x. CList x -> CList x
cReverse = \xs -> runCList xs (\x ys -> cAppend ys (cCons x cNil)) cNil

-- SumList
cSumList :: CList Nat -> Nat
cSumList = \ns -> runCList ns (\n m -> cSuma n m) zero

-- Seccion c (La pasé mal)

-- Pair general
newtype Pair x y = Pair { runPair :: forall z. (x -> y -> z) -> z }

checkPair :: Pair x y -> (x,y)
checkPair = \p -> (fstPair p, sndPair p)

pair :: forall x. forall y. x -> y -> Pair x y
pair = \x y -> Pair (\f -> f x y)

fstPair :: forall x. forall y. Pair x y -> x
fstPair = \p -> runPair p (\x y -> x)

sndPair :: forall x. forall y. Pair x y -> y
sndPair = \p -> runPair p (\x y -> y)

-- Paramorfismo
param :: forall x. forall y. (x -> Pair y (CList x) -> Pair y (CList x)) -> Pair y (CList x) -> CList x -> Pair y (CList x)
param = \c n xs -> runCList xs (\x p -> pair (fstPair (c x p)) (cCons x (sndPair p))) 
                               (pair (fstPair n) (cNil))

insert :: forall x. (x -> x -> CBool) -> CList x -> x -> CList x
insert = \c xs x -> fstPair (param (\y p -> (c x y) 
                                              (pair (cCons x (cCons y (sndPair p))) (cCons y (sndPair p))) 
                                              (pair (cCons y (fstPair p)) (cCons y (fstPair p))))
                                   (pair (cCons x cNil) cNil) xs)

-- Funcion para testear el insert
comp :: forall x. (x -> x -> Bool) -> x -> x -> CBool
comp = \c x y -> if (c x y) then cTrue else cFalse
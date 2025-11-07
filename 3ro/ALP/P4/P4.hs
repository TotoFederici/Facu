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
Definicion de Bool, True y False.

Tipo Bool de Church:
Bool = forall X.X -> X -> X

Constructores True y False:
True : Bool
True = /\X.\t:X.\f.X.t

False : Bool
False = /\X.\t:X.\f.X.f

Definicoin de And:

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
Tipo Nat de Church:
Nat = forall X.(X -> X) -> X -> X

Constructores de Nat:
Zero : Nat
Zero = /\X.\s:X -> X.\z:X.z

Succ : Nat -> Nat
Succ = \n:Nat./\X.\s:X -> X.\z:X.s (n <X> s z)

Definicion de tipo, constructor y destructores de PairNat

Tipo PairNat:
PairNat = forall X.(Nat -> Nat -> X) -> X

Constructor pairNat:
pairNat : Nat -> Nat -> PairNat
pairNat = \n:Nat.\m:Nat./\X.\f:Nat -> Nat -> Nat.f n m

Destructores fst y snd:
fstNat : PairNat -> Nat
fstNat = \p:PairNat.P <Nat> (\x:Nat.\y:Nat.x)

sndNat : PairNat -> Nat
sndNat = \p:PairNat.P <Nat> (\x:Nat.\y:Nat.y)

Definicion de pred y pred' usando tupling:
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
Tipo de listas de church: 

List X = forall R. (X -> R -> R) -> R -> R

Constructores de listas:

nil : forall X. List X
nil = /\X./\R.\c:X -> R -> R.\n:R.n

cons : forall X. X -> List X -> List X
cons = /\X.\x:X.\xs:List X. /\R.\c:X -> R -> R.\n:R. c x (xs <R> c n)

map : forall X. forall Y. (X -> Y) -> List X -> List Y
map = /\X./\Y.\f:X -> Y.\xs:List X. xs <List Y> (\x:X.\ys. cons (f x) ys) (nil <Y>)
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
cSumaList :: CList Nat -> Nat
cSumaList = \ns -> runCList ns (\n m -> cSuma n m) zero

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
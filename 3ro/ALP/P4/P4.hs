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

id :: forall x . x -> x
id = \x -> x

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
checkNat n = n (+1) 0

toNat :: Int -> Nat
toNat n | n == 0 = zero
        | otherwise = suc (toNat (n-1))

-- Fin de la magia --

-- Tipo y constructores --

type Nat = forall x . (x -> x) -> x -> x

zero :: Nat
zero = \s z -> z

suc :: Nat -> Nat
suc = \n -> \s z -> s (n s z)

-- Fin de tipo y constructores --

type PairNatRep = forall x . (Nat -> Nat -> x) -> x

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

cPred :: Nat -> Nat
cPred = \n -> fstNat (cPred' n)

cPred' :: Nat -> PairNat
cPred' = \n -> n (\p -> pairNat (sndNat p) (suc (sndNat p))) (pairNat zero zero)
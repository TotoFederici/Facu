module Simplytyped
  ( conversion
  ,    -- conversion a terminos localmente sin nombre
    eval
  ,          -- evaluador
    infer
  ,         -- inferidor de tipos
    quote          -- valores -> terminos
  )
where

import           Data.List
import           Data.Maybe
import           Prelude                 hiding ( (>>=) )
import           Text.PrettyPrint.HughesPJ      ( render )
import           PrettyPrinter
import           Common

-----------------------
-- conversion
-----------------------
-- conversion a términos localmente sin nombres
conversion :: LamTerm -> Term
conversion = conversion' []

conversion' ::  [Name] -> LamTerm -> Term
conversion' xs (LVar n) = case findBound xs (Global n) of
                            Nothing -> Free (Global n)
                            Just i  -> Bound i 
conversion' xs (LAbs n t l) = Lam t (conversion' ((Global n):xs) l)
conversion' xs (LApp t1 t2 ) = let c = conversion' xs 
                               in (c t1) :@: (c t2)
conversion' xs (LLet s t1 t2) = let nxs = ((Global s):xs) in Let (conversion' xs t1) (conversion' nxs t2)

-- NAT

conversion' xs (LZero) = Zero 
conversion' xs (LSuc t) = Suc (conversion' xs t)
conversion' xs (LRec t1 t2 t3) = let c = conversion' xs 
                                 in Rec (c t1) (c t2) (c t3) 

--LIST 
conversion' xs (LNil)           = Nil
conversion' xs (LCons t1 t2)    = let c = conversion' xs
                                  in (Cons (c t1) (c t2)) 
conversion' xs (LRecL t1 t2 t3) = let c = conversion' xs 
                                  in RecL (c t1) (c t2) (c t3)


findBound :: [Name] -> Name -> Maybe Int
findBound = elemIndex' 0 

elemIndex' :: Int ->[Name] -> Name -> Maybe Int
elemIndex' _ [] n  = Nothing
elemIndex' i (x:xs) n | n==x = Just i
                      | otherwise = elemIndex' (i+1) xs n   

----------------------------
--- evaluador de términos
----------------------------

-- substituye una variable por un término en otro término
sub :: Int -> Term -> Term -> Term
sub i t (Bound j) | i == j    = t
sub _ _ (Bound j) | otherwise = Bound j
sub _ _ (Free n   )           = Free n
sub i t (u   :@: v)           = sub i t u :@: sub i t v
sub i t (Lam t'  u)           = Lam t' (sub (i + 1) t u)
sub i t (Let t1 t2)           = Let (sub i t t1) (sub (i + 1) t t2)
sub _ _ (Zero)                = Zero
sub i t (Suc n)               = Suc (sub i t n)
sub i t (Rec t1 t2 t3)        = Rec (sub i t t1) (sub i t t2) (sub i t t3)


sub _ _ (Nil)                 = Nil
sub i t (Cons t1 t2)          = Cons (sub i t t1) (sub i t t2)
sub i t (RecL t1 t2 t3)       = RecL (sub i t t1) (sub i t t2) (sub i t t3) 

-- convierte un valor en el término equivalente
quote :: Value -> Term
quote (VLam t f)            = Lam t f
quote (VNum (NSuc n))       = Suc (quote (VNum n))
quote (VNum NZero)          = Zero
quote (VList VNil)          = Nil
quote (VList (VCons t1 t2)) = Cons (quote (VNum t1)) (quote (VList t2))
-- evalúa un término en un entorno dado
lookEnv :: NameEnv v t -> Name -> Maybe (v, t)
lookEnv [] n     = Nothing
lookEnv (x:xs) n = if (fst x) == n
                   then Just (snd x)
                   else lookEnv xs n 

eval :: NameEnv Value Type -> Term -> Value
eval e (Free n)                 = case lookEnv e n of
                                   Just (v,t) -> v      
eval e (Lam t f)                = VLam t f  --fix
eval e (t1 :@: t2)              = let (Lam t3 f) = (quote (eval e t1))
                                      v2 = (quote (eval e t2))
                                  in eval e (sub 0 v2 f)
eval e (Let t1 t2)              = let v1 = (quote (eval e t1))
                                  in eval e (sub 0 v1 t2)
--  NAT    
eval e Zero                     = VNum NZero
eval e (Suc t)                  = let VNum t' = eval e t
                                  in VNum (NSuc t')
eval e (Rec t1 t2 Zero)         = eval e t1
eval e (Rec t1 t2 (Suc t3))     = eval e ((t2 :@: (Rec t1 t2 t3)) :@: t3)
eval e (Rec t1 t2 t3)           = let t' = eval e t3 
                                  in eval e (Rec t1 t2 (quote t'))
    
-- List    
eval e Nil                      = VList VNil
eval e (Cons t1 t2)             = let VNum t1' = eval e t1
                                      VList t2' = eval e t2
                                  in VList (VCons t1' t2')
eval e (RecL t1 t2 Nil)          = eval e t1
eval e (RecL t1 t2 (Cons t3 t4)) = eval e (((t2 :@: t3) :@: t4) :@: (RecL t1 t2 t4))
eval e (RecL t1 t2 t3)           = let t' = eval e t3 
                                   in eval e (RecL t1 t2 (quote t'))


----------------------
--- type checker
-----------------------

-- infiere el tipo de un término
infer :: NameEnv Value Type -> Term -> Either String Type
infer = infer' []

-- definiciones auxiliares
ret :: Type -> Either String Type
ret = Right

err :: String -> Either String Type
err = Left

(>>=)
  :: Either String Type -> (Type -> Either String Type) -> Either String Type
(>>=) v f = either Left f v
-- fcs. de error

matchError :: Type -> Type -> Either String Type
matchError t1 t2 =
  err
    $  "se esperaba "
    ++ render (printType t1)
    ++ ", pero "
    ++ render (printType t2)
    ++ " fue inferido."


notfunError :: Type -> Either String Type
notfunError t1 = err $ render (printType t1) ++ " no puede ser aplicado."

notfoundError :: Name -> Either String Type
notfoundError n = err $ show n ++ " no está definida."

-- infiere el tipo de un término a partir de un entorno local de variables y un entorno global
infer' :: Context -> NameEnv Value Type -> Term -> Either String Type
infer' c _ (Bound i)        = ret (c !! i)
infer' _ e (Free  n)        = case lookup n e of
                               Nothing     -> notfoundError n
                               Just (_, t) -> ret t
                               
infer' c e (t :@: u)        = infer' c e t >>= \tt -> 
                              infer' c e u >>= \tu -> 
                                case tt of
                                 FunT t1 t2 -> if (tu == t1) then ret t2 else matchError t1 tu
                                 _          -> notfunError tt
                                 
infer' c e (Lam t u)        = infer' (t : c) e u >>= \tu -> ret $ FunT t tu

-- LET
infer' c e (Let t1 t2)      = infer' c e t1 >>= \tt -> infer' (tt : c) e t2 >>= \tu -> ret tu


-- NAT 
infer' c e (Zero)           = ret NatT
infer' c e (Suc t)          = infer' c e t >>= \tt -> case tt of
                                              NatT -> ret tt 
                                              _    -> matchError NatT tt
infer' c e (Rec t1 t2 t3) = infer' c e t1 >>= 
                    \tt1 -> infer' c e t2 >>=
                    \tt2 -> infer' c e t3 >>=
                    \tt3 -> case tt2 of
                              FunT a (FunT NatT b) -> if (a==tt1) then 
                                                        if (b==tt1) then case tt3 of
                                                                          NatT -> ret tt1
                                                                          _ -> matchError NatT tt3
                                                        else matchError tt1 b
                                                      else matchError tt1 a
                              FunT _ (FunT a _) -> matchError NatT a                               
                              _           -> notfunError tt2
-- LIST
infer' c e (Nil)            = ret ListT
infer' c e (Cons t1 t2)     = infer' c e t1 >>= \tt1 -> infer' c e t2 >>= 
                                                \tt2 -> case tt1 of
                                                         NatT -> case tt2 of
                                                                  ListT -> ret ListT
                                                                  _     -> matchError ListT tt2
                                                         _    -> matchError NatT tt1
                                                     
infer' c e (RecL t1 t2 t3) = infer' c e t1 >>=
                    \tt1 -> infer' c e t2 >>=
                    \tt2 -> infer' c e t3 >>=
                    \tt3 -> case tt2 of
                              FunT NatT (FunT ListT (FunT a b)) -> 
                                if (a == tt1) then 
                                  if (b == tt1) then 
                                    case tt3 of
                                      ListT -> ret tt1
                                      _     -> matchError ListT tt3
                                  else matchError tt1 b
                                else matchError tt1 a
                              FunT NatT (FunT a (FunT _ _)) -> matchError ListT a
                              FunT a (FunT _ (FunT _ _)) -> matchError NatT a
                              _ -> notfunError tt2


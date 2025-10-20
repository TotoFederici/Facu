module Eval1
  ( eval
  , State
  )
where

import           AST
import qualified Data.Map.Strict               as M
import           Data.Strict.Tuple

-- Estados
type State = M.Map Variable Int

-- Estado vacío
-- Completar la definición
initState :: State
initState = M.empty

-- Busca el valor de una variable en un estado
-- Completar la definición
lookfor :: Variable -> State -> Int
lookfor v m = case M.lookup v m of 
  (Just a) -> a
  Nothing -> undefined

-- Cambia el valor de una variable en un estado
-- Completar la definición
update :: Variable -> Int -> State -> State
update v n m = M.insert v n m

-- Evalúa un programa en el estado vacío
eval :: Comm -> State
eval p = stepCommStar p initState

-- Evalúa múltiples pasos de un comando en un estado,
-- hasta alcanzar un Skip
stepCommStar :: Comm -> State -> State
stepCommStar Skip s = s
stepCommStar c    s = Data.Strict.Tuple.uncurry stepCommStar $ stepComm c s

-- Evalúa un paso de un comando en un estado dado
-- Completar la definición
stepComm :: Comm -> State -> Pair Comm State
stepComm Skip m = (Skip :!: m)
stepComm (Let v n) m = let (x :!: m')= evalExp n m in (Skip :!: (update v x m'))
stepComm (Seq c1 c2) m = case c1 of 
                           Skip -> (c2 :!: m) --stepComm c2 m
                           _ -> let (c' :!: m') = stepComm c1 m in stepComm (Seq c' c2) m'
stepComm (IfThenElse b c1 c2) m = let (c' :!: m') = evalExp b m in if c' then (c1 :!: m') else (c2 :!: m')
stepComm (RepeatUntil c b) m = ((Seq c (IfThenElse b Skip (RepeatUntil c b))) :!: m) 

-- Evalúa una expresión
-- Completar la definición
evalExp :: Exp a -> State -> Pair a State
evalExp (Const n) m = (n :!: m)
evalExp (Var v) m = ((lookfor v m) :!: m) 
evalExp (UMinus n) m = let (u :!: m') = evalExp n m in (-u :!: m')
evalExp (Plus e1 e2) m = let (r1:!:m1) = (evalExp e1 m)
                             (r2:!:m2) = (evalExp e2 m1) in ((r1 + r2) :!: m2)
evalExp (Minus e1 e2) m = let (r1:!:m1) = (evalExp e1 m)
                              (r2:!:m2) = (evalExp e2 m1) in ((r1 - r2) :!: m2)
evalExp (Times e1 e2) m = let (r1:!:m1) = (evalExp e1 m)
                              (r2:!:m2) = (evalExp e2 m1) in ((r1 * r2) :!: m2)
evalExp (Div e1 e2) m = let (r1:!:m1) = (evalExp e1 m)
                            (r2:!:m2) = (evalExp e2 m1) in ((div r1  r2) :!: m2)
evalExp (VarInc v) m = let n = lookfor v m in (n+1 :!: update v (n+1) m)

--BoolTime

evalExp BTrue m= (True :!: m)
evalExp BFalse m= (False :!: m)
evalExp (Lt e1 e2) m = let (r1 :!: m1) = (evalExp e1 m)
                           (r2 :!: m2) = (evalExp e2 m1) in ((r1 < r2) :!: m2)
evalExp (Gt e1 e2) m = let (r1 :!: m1) = (evalExp e1 m)
                           (r2 :!: m2) = (evalExp e2 m1) in ((r1 > r2) :!: m2)
evalExp (And b1 b2) m = let (r1 :!: m1) = (evalExp b1 m)
                            (r2 :!: m2) = (evalExp b2 m1) in ((r1 && r2) :!: m2)
evalExp (Or b1 b2) m = let (r1 :!: m1) = (evalExp b1 m)
                           (r2 :!: m2) = (evalExp b2 m1) in ((r1 || r2) :!: m2)

evalExp (Not b) m = let (b' :!: m') = evalExp b m in ( not (b') :!: m')
 
evalExp (Eq e1 e2) m = let (r1 :!: m1) = (evalExp e1 m)
                           (r2 :!: m2) = (evalExp e2 m1) in ((r1 == r2) :!: m2)
evalExp (NEq e1 e2) m = let (r1 :!: m1) = (evalExp e1 m)
                            (r2 :!: m2) = (evalExp e2 m1) in (not (r1 == r2) :!: m2)



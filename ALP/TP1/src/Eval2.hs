module Eval2
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
lookfor :: Variable -> State -> Either Error Int
lookfor v m = case M.lookup v m of
  (Just a) -> Right a 
  Nothing -> Left UndefVar 

-- Cambia el valor de una variable en un estado
-- Completar la definición
update :: Variable -> Int -> State -> State
update v n m = M.insert v n m  

-- Evalúa un programa en el estado vacío
eval :: Comm -> Either Error State
eval p = stepCommStar p initState

-- Evalúa múltiples pasos de un comnado en un estado,
-- hasta alcanzar un Skip
stepCommStar :: Comm -> State -> Either Error State
stepCommStar Skip s = return s
stepCommStar c    s = do
  (c' :!: s') <- stepComm c s
  stepCommStar c' s'

-- Evalúa un paso de un comando en un estado dado
-- Completar la definición
stepComm :: Comm -> State -> Either Error (Pair Comm State)
stepComm Skip m = Right (Skip :!: m)
stepComm (Let v n) m = case evalExp n m of
  Right (x :!: m') ->  Right (Skip :!: (update v x m'))
  Left e -> Left e


stepComm (Seq c1 c2) m = case c1 of 
                           Skip -> Right (c2 :!: m) --stepComm c2 m
                           _ -> case stepComm c1 m of
                            Right (c' :!: m') -> stepComm (Seq c' c2) m'
                            Left e -> Left e
stepComm (IfThenElse b c1 c2) m = case evalExp b m of
  Right (c' :!: m') ->  if c' then Right (c1 :!: m') else Right (c2 :!: m')
  Left e -> Left e
stepComm (RepeatUntil c b) m = Right ((Seq c (IfThenElse b Skip (RepeatUntil c b))) :!: m) 

-- Evalúa una expresión
-- Completar la definición
evalExp :: Exp a -> State -> Either Error (Pair a State)
evalExp (Const n) m = Right (n :!: m)

evalExp (Var v) m = case lookfor v m of
  Right n -> Right (n :!: m)
  _ -> Left UndefVar

evalExp (UMinus n) m = case (evalExp n m) of
  Right (r :!: m') -> Right (-r :!: m')
  Left e -> Left e

evalExp (NEq e1 e2) m = case evalExp (Eq e1 e2) m of 
  Left e -> Left e 
  Right (b :!: m') -> Right (not b :!: m')

evalExp (VarInc v) m = case lookfor v m of
  Right n  -> Right ( n+1 :!:update v (n+1) m)
  Left e -> Left e 

evalExp BTrue m = Right (True :!: m) 
evalExp BFalse m = Right (False :!: m)

evalExp (Not b) m = case evalExp b m of
  Left e -> Left e
  Right (r :!: m') -> Right (not r :!: m')

evalExp (Plus e1 e2) m = evalExpOp e1 e2 m (+)
evalExp (Minus e1 e2) m = evalExpOp e1 e2 m (-)
evalExp (Times e1 e2) m = evalExpOp e1 e2 m (*)
evalExp (Div e1 e2) m = case evalExp e1 m of
  Left e -> Left e 
  Right (r1 :!: m1) -> case evalExp e2 m1 of
    Left e' -> Left e'
    Right (r2 :!: m2) ->if (r2 == 0) then Left DivByZero else Right (div r1 r2 :!: m2)

evalExp (Lt e1 e2) m = evalExpOp e1 e2 m (<)
evalExp (Gt e1 e2) m = evalExpOp e1 e2 m (>)
evalExp (Or e1 e2) m = evalExpOp e1 e2 m (||)
evalExp (And e1 e2) m = evalExpOp e1 e2 m (&&)
evalExp (Eq e1 e2) m = evalExpOp e1 e2 m (==)

evalExpOp :: Exp a -> Exp a -> State -> ( a ->  a ->  b) -> Either Error (Pair b State)
evalExpOp e1 e2 m op = case evalExp e1 m of
  Left e -> Left e 
  Right (r1 :!: m1) -> case evalExp e2 m1 of
    Left e' -> Left e'
    Right (r2 :!: m2) -> Right (op r1 r2 :!: m2)



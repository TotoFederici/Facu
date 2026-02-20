module Eval1
  ( eval
  , Env
  )
where

import           AST
import           Monads
import qualified Data.Map.Strict               as M
import           Data.Maybe
import           Prelude                 hiding ( fst
                                                , snd
                                                )
import           Data.Strict.Tuple
import           Control.Monad                  ( liftM
                                                , ap
                                                )

-- Entornos
type Env = M.Map Variable Int

-- Entorno nulo
initEnv :: Env
initEnv = M.empty

-- Mónada estado
newtype State a = State { runState :: Env -> Pair a Env }

instance Monad State where
  return x = State (\s -> (x :!: s))
  m >>= f = State (\s -> let (v :!: s') = runState m s in runState (f v) s')

-- Para calmar al GHC
instance Functor State where
  fmap = liftM

instance Applicative State where
  pure  = return
  (<*>) = ap

instance MonadState State where
  lookfor v = State (\s -> (lookfor' v s :!: s))
    where lookfor' v s = fromJust $ M.lookup v s
  update v i = State (\s -> (() :!: update' v i s)) where update' = M.insert

-- Ejercicio 1.b: Implementar el evaluador utilizando la monada State

-- Evalua un programa en el estado nulo
eval :: Comm -> Env
eval p = snd (runState (stepCommStar p) initEnv)

-- Evalua multiples pasos de un comando, hasta alcanzar un Skip
stepCommStar :: MonadState m => Comm -> m ()
stepCommStar Skip = return ()
stepCommStar c    = stepComm c >>= \c' -> stepCommStar c'

-- Evalua un paso de un comando
stepComm :: MonadState m => Comm -> m Comm
stepComm (Let v e)           = do a <- evalExp e
                                  update v a
                                  return Skip

stepComm (Seq c c')          = do stepComm c
                                  stepComm c'

stepComm (IfThenElse e c c') = do b <- evalExp e 
                                  if b then stepComm c
                                       else stepComm c'

stepComm (Repeat e c)        = do b <- evalExp e 
                                  if b then do stepComm c
                                               stepComm (Repeat e c)
                                       else return Skip

-- Evalua una expresion
evalExp :: MonadState m => Exp a -> m a
evalExp (Const n)    = return n

evalExp (Var v)      = lookfor v

evalExp (UMinus e)   = do n <- evalExp e
                          return (-n)

evalExp (Plus e e')  = do n1 <- evalExp e
                          n2 <- evalExp e'
                          return (n1 + n2)

evalExp (Minus e e') = do n1 <- evalExp e
                          n2 <- evalExp e'
                          return (n1 - n2)

evalExp (Times e e') = do n1 <- evalExp e
                          n2 <- evalExp e'
                          return (n1 * n2)

evalExp (Div e e')   = do n1 <- evalExp e
                          n2 <- evalExp e'
                          return (div n1 n2)

evalExp (BTrue)      = return True

evalExp (BFalse)     = return False 

evalExp (Lt e e')    = do e1 <- evalExp e
                          e2 <- evalExp e'
                          return (e1 < e2)

evalExp (Gt e e')    = do e1 <- evalExp e
                          e2 <- evalExp e'
                          return (e1 > e2)

evalExp (And e e')   = do n1 <- evalExp e
                          n2 <- evalExp e'
                          return (n1 && n2)

evalExp (Or e e')    = do n1 <- evalExp e
                          n2 <- evalExp e'
                          return (n1 || n2)

evalExp (Not e)      = do b <- evalExp e
                          return (not b)

evalExp (Eq e e')    = do n1 <- evalExp e
                          n2 <- evalExp e'
                          return (n1 == n2)           

evalExp (NEq e e')   = do n1 <- evalExp e
                          n2 <- evalExp e'
                          return (not (n1 == n2))        
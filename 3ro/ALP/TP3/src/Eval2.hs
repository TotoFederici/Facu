module Eval2
  ( eval
  , Env
  )
where

import           AST
import           Monads
import qualified Data.Map.Strict               as M
import           Data.Maybe
import           Data.Strict.Tuple
import           Control.Monad                  ( liftM
                                                , ap
                                                )

-- Entornos
type Env = M.Map Variable Int

-- Entorno nulo
initEnv :: Env
initEnv = M.empty

-- Mónada estado, con manejo de errores
newtype StateError a =
  StateError { runStateError :: Env -> Either Error ( Pair a Env) }


-- Para calmar al GHC
instance Functor StateError where
  fmap = liftM

instance Applicative StateError where
  pure  = return
  (<*>) = ap

-- Ejercicio 2.a: Dar una instancia de Monad para StateError:
instance Monad StateError where
  return x = StateError (\s -> Right (x :!: s))
  m >>= f = StateError (\s -> case runStateError m s of
                               Left e -> Left e
                               Right (x :!: s') -> runStateError (f x) s' )

-- Ejercicio 2.b: Dar una instancia de MonadError para StateError:
instance MonadError StateError where
  throw e = StateError (\_ -> Left e)

-- Ejercicio 2.c: Dar una instancia de MonadState para StateError:
instance MonadState StateError where
  lookfor v = StateError (\s -> case M.lookup v s of
                                  Nothing -> Left UndefVar
                                  Just a -> Right (a :!: s))
  update v e = StateError (\s -> Right (() :!: M.insert v e s))

-- Ejercicio 2.d: Implementar el evaluador utilizando la monada StateError.
-- Evalua un programa en el estado nulo
eval :: Comm -> Either Error Env
eval p = case runStateError (stepCommStar p) initEnv of
          Right a -> Right (Data.Strict.Tuple.snd a)
          Left e -> Left e

-- Evalua multiples pasos de un comando, hasta alcanzar un Skip
stepCommStar :: (MonadState m, MonadError m) => Comm -> m ()
stepCommStar Skip = return ()
stepCommStar c    = stepComm c >>= \c' -> stepCommStar c'

-- Evalua un paso de un comando
stepComm :: (MonadState m, MonadError m) => Comm -> m Comm
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
evalExp :: (MonadState m, MonadError m) => Exp a -> m a
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
                          if n2 == 0 then throw DivByZero
                                     else return (div n1 n2)

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
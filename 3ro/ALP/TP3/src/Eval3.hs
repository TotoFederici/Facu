module Eval3
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

-- Ejercicio 3.a: Proponer una nueva m\'onada que  
-- lleve una traza de ejecución (además de manejar errores y estado).
-- y dar su instancia de mónada. Llamarla |StateErrorTrace|. 
newtype StateErrorTrace a = 
  StateErrorTrace {runStateErrorTrace :: Env -> Either Error (Pair a (Env, Trace))}

instance Monad StateErrorTrace where
  return x = StateErrorTrace (\s -> Right (x :!: (s,"")))
  m >>= f  = StateErrorTrace (\s -> case runStateErrorTrace m s of
                                      Left e -> Left e
                                      Right (a :!: (s',t)) -> case runStateErrorTrace (f a) s' of
                                                                    Left e -> Left e
                                                                    Right (b :!: (s'',t')) -> Right (b :!: (s'', t ++ t')))                                                          
                                                                        
-- Recuerde agregar las siguientes instancias para calmar al GHC:
instance Functor StateErrorTrace where
  fmap = liftM

instance Applicative StateErrorTrace where
  pure  = return
  (<*>) = ap

-- Ejercicio 3.b: Resolver en Monad.hs
-- DONE

-- Ejercicio 3.c: Dar una instancia de MonadTrace para StateErrorTrace.
instance MonadTrace StateErrorTrace where
  addTrace t = StateErrorTrace (\s -> Right (() :!: (s,t)))

-- Ejercicio 3.d: Dar una instancia de MonadError para StateErrorTrace.
instance MonadError StateErrorTrace where
  throw e = StateErrorTrace (\_ -> Left e)

-- Ejercicio 3.e: Dar una instancia de MonadState para StateErrorTrace.
instance MonadState StateErrorTrace where
  lookfor v = StateErrorTrace (\s -> case M.lookup v s of
                                      Nothing -> Left UndefVar
                                      Just a -> Right (a :!: (s,"")))
  update v e = StateErrorTrace (\s -> Right (() :!: (M.insert v e s,"")))

-- Ejercicio 3.f: Implementar el evaluador utilizando la monada StateErrorTrace.
-- Evalua un programa en el estado nulo

eval :: Comm -> Either Error (Env, Trace)
eval p = case runStateErrorTrace (stepCommStar p) initEnv of
          Right a -> Right (Data.Strict.Tuple.snd a)
          Left e -> Left e


-- Evalua multiples pasos de un comando, hasta alcanzar un Skip
stepCommStar :: (MonadState m, MonadError m, MonadTrace m) => Comm -> m ()
stepCommStar Skip = return ()
stepCommStar c    = stepComm c >>= \c' -> stepCommStar c'

-- Evalua un paso de un comando
stepComm :: (MonadState m, MonadError m, MonadTrace m) => Comm -> m Comm
stepComm (Let v e)           = do a <- evalIntExp e
                                  update v a
                                  addTrace ("Let " ++ v ++ " = " ++ show a ++ "   ")
                                  return Skip

stepComm (Seq c c')          = do stepComm c
                                  stepComm c'

stepComm (IfThenElse e c c') = do b <- evalIntExp e 
                                  if b then stepComm c
                                       else stepComm c'

stepComm (Repeat e c)        = do b <- evalIntExp e 
                                  if b then do stepComm c
                                               stepComm (Repeat e c)
                                       else return Skip 

-- Evalua una expresion 
evalIntExp :: (MonadState m, MonadError m, MonadTrace m) => Exp a -> m a
evalIntExp (Const n)    = return n

evalIntExp (Var v)      = lookfor v

evalIntExp (UMinus e)   = do n <- evalIntExp e
                             return (-n)

evalIntExp (Plus e e')  = do n1 <- evalIntExp e
                             n2 <- evalIntExp e'
                             return (n1 + n2)

evalIntExp (Minus e e') = do n1 <- evalIntExp e
                             n2 <- evalIntExp e'
                             return (n1 - n2)

evalIntExp (Times e e') = do n1 <- evalIntExp e
                             n2 <- evalIntExp e'
                             return (n1 * n2)

evalIntExp (Div e e')   = do n1 <- evalIntExp e
                             n2 <- evalIntExp e'
                             if n2 == 0 then throw DivByZero
                                        else return (div n1 n2)

evalIntExp (BTrue)      = return True

evalIntExp (BFalse)     = return False 

evalIntExp (Lt e e')    = do e1 <- evalIntExp e
                             e2 <- evalIntExp e'
                             return (e1 < e2)

evalIntExp (Gt e e')    = do e1 <- evalIntExp e
                             e2 <- evalIntExp e'
                             return (e1 > e2)

evalIntExp (And e e')   = do n1 <- evalIntExp e
                             n2 <- evalIntExp e'
                             return (n1 && n2)

evalIntExp (Or e e')    = do n1 <- evalIntExp e
                             n2 <- evalIntExp e'
                             return (n1 || n2)

evalIntExp (Not e)      = do b <- evalIntExp e
                             return (not b)

evalIntExp (Eq e e')    = do n1 <- evalIntExp e
                             n2 <- evalIntExp e'
                             return (n1 == n2)           

evalIntExp (NEq e e')   = do n1 <- evalIntExp e
                             n2 <- evalIntExp e'
                             return (not (n1 == n2))

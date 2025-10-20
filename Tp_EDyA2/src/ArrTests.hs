module ArrTests where

import Test.HUnit
import Seq
import Arr        (Arr)
import ArrSeq


s0, s1, s2, s3 :: Arr Int
s0 = fromList []
s1 = fromList [4]
s2 = fromList [5,1]
s3 = fromList [6,3,4]

testLengthEmptySeq :: Test
testLengthEmptySeq = 
  TestCase $ assertEqual "Error on empty sequence length"
                         0 (lengthS s0)

testLengthNonEmptySeq :: Test
testLengthNonEmptySeq = 
  TestCase $ assertEqual "Error on non-empty sequence length"
                         2 (lengthS s2)

testMapEmptySeq :: Test
testMapEmptySeq = 
  TestCase $ assertEqual "Error on empty sequence map"
                         s0 (mapS (+1) s0)

testMapNonEmptySeq :: Test
testMapNonEmptySeq = 
  TestCase $ assertEqual "Error on non-empty sequence map"
                         (fromList [7,4,5]) (mapS (+1) s3)

testReduceSumSeq0 :: Test
testReduceSumSeq0 = 
  TestCase $ assertEqual "Error reducing empty sequence"
                         0 (reduceS (+) 0 s0)

testReduceSumSeq3 :: Test
testReduceSumSeq3 = 
  TestCase $ assertEqual "Error reducing sequence of length 3"
                         13 (reduceS (+) 0 s3)

testScanSumSeq0 :: Test
testScanSumSeq0 = 
  TestCase $ assertEqual "Error on empty sequence scan"
                         (emptyS, 0) (scanS (+) 0 s0)

testScanSumSeq3 :: Test
testScanSumSeq3 = 
  TestCase $ assertEqual "Error on scan for sequence of length 3"
                         (fromList[0,6,9], 13) (scanS (+) 0 s3)

testsArray = 
  [
    testMapEmptySeq,
    testMapNonEmptySeq,
    testLengthEmptySeq,
    testLengthNonEmptySeq,
    testReduceSumSeq0,
    testReduceSumSeq3,
    testScanSumSeq0,
    testScanSumSeq3
  ]


main :: IO Counts
main = runTestTT $ TestList testsArray

fview :: String -> String -> String
fview s0 s1 = "(" ++ s0 ++ "+" ++ s1 ++ ")"

longestStreak :: Float -> Arr Float -> Int
longestStreak v s = let s' = mapS (\n -> if n > v then (n,1,n) else (n,0,n)) s
                        (s'',r) = scanS combine (0,0,0) s'
                        s''' = appendS s'' (singletonS r)
                        res = mapS (\(_,i,_) -> i) s'''
                    in reduceS max 0 res
  where combine (l,i,r) (l',i',r') = if (r > v) && (l' > v)
                                     then (l,i+i',r')
                                     else (l,i',r')

s4 :: Arr Float
s4 = fromList [31,31,31,31,31,31,31]
module Lib
    ( someFunc
    ) where
import Data.Bits (Bits(xor))
import GHC.TypeError (ErrorMessage(ShowType))

someFunc :: IO ()
someFunc = putStrLn "someFunc"

hailStone :: Integer -> Integer
hailStone n
    | even n = n `div` 2
    | otherwise = 3 * n + 1

foo :: Integer -> Integer
foo 0 = 16
foo 1
    | "Haskell" > "C++" = 3
    | otherwise = 4
foo n
    | n < 0 = 0
    | n `mod` 17 == 2 = -43
    | otherwise = n + 3

isEven :: Integer -> Bool
isEven n
    | even n = True
    | otherwise = False

p :: (Int, Char)
p = (3, 'x')

f :: Num a => a -> a -> a -> a
f x y z = x + y + z

emptyList :: [a]
emptyList = []

intListLength :: Num a1 => [a2] -> a1
intListLength [] = 0
intListLength (x:xs) = 1 + intListLength xs

sumEveryTwo :: [Integer] -> [Integer]
sumEveryTwo [] = []
sumEveryTwo [x] = [x]
sumEveryTwo (x:y:zs) = (x + y) : sumEveryTwo zs

firstLetter "" = "empty"
firstLetter all@(x:xs) = "firstletter of" ++ xs ++ "is " ++ [x]

bmiTell :: Double -> Double -> String
bmiTell weight height
    | bmi <= skinny = "1"
    | bmi <= normal = "f"
    | bmi <= fat = "fat"
    | otherwise = "wtf"
    where
        bmi = weight / height ^ 2
        skinny = 18.5
        normal = 25.0
        fat = 30.0

calcBmis :: Fractional a => [(a, a)] -> [a]
calcBmis xs = [bmi | (w, h) <- xs, let bmi = w / h ^ 2]

myAdd :: (Eq a, Num a) => a -> a -> a
myAdd a b = let square x = x * x in case (a, b) of
    (0, 0) -> 0
    (0, _) -> b
    (_, 0) -> a
    (_, _) -> a + b

maximum' :: Ord a => [a] -> a
maximum' [] = error "fuck"
maximum' [x] = x
maximum' (x:xs) = max x (maximum' xs)

data Thing = Shoe
    | Fuck
    | Ship
    deriving Show

data IntList = Empty | Cons Int IntList deriving Show

mapIntList :: (Int -> Int) -> IntList -> IntList
mapIntList _ Empty = Empty
mapIntList f (Cons x xs) = Cons (f x) (mapIntList f xs)

filterIntList _ Empty = Empty
filterIntList f (Cons x xs)
    | f x = Cons x (filterIntList f xs)
    | otherwise = filterIntList f xs

keepOnlyEven :: IntList -> IntList
keepOnlyEven Empty = Empty
keepOnlyEven (Cons x xs)
    | even x = Cons x (keepOnlyEven xs)
    | otherwise = keepOnlyEven xs

data MyList t = E | C t (MyList t)
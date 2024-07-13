module Main (main) where

import Lib ( someFunc )

doubleMe :: Num a => a -> a
doubleMe x = x + x

doubleUs :: Num a => a -> a -> a
doubleUs x y = doubleMe x + doubleMe y

doubleSmallNumber :: (Ord a, Num a) => a -> a
doubleSmallNumber x = if x > 100 then x else x * 2

hankhogan :: String
hankhogan = "Hank Hogan"

lostNumbers :: [Integer]
lostNumbers = [4, 8, 15, 16, 23, 42]

test1 :: [Integer]
test1 = [2 * x | x <- [1 .. 10], x * 2 >= 12]

test2 :: [Char]
test2 = [x | x <- hankhogan, x `elem` ['A' .. 'Z']]

boomBangs :: Integral a => [a] -> [String]
boomBangs xs = [if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]

test3 :: [String]
test3 = boomBangs [7 .. 13]

test4 :: [Integer]
test4 = [x + y + z | x <- [1, 2, 3], y <- [10, 100, 1000], x * y > 100, z <- [100, 1000, 10000]]

length' :: Num a => [t] -> a
length' xs = sum [1 | _ <- xs]

removeNonUppercase :: [Char] -> [Char]
removeNonUppercase st = [c | c <- st, c `elem` ['A' .. 'Z']]

test5 :: Integral a => [[a]] -> [[a]]
test5 xxs = [[x | x <- xs, even x] | xs <- xxs]

t1 :: (Integer, String)
t1 = (1, "shits")

t2 :: Integer
t2 = 1

_ = snd (8, 11)

_ = take 5 (zip [1 ..] ['a' ..])

triples :: [(Integer, Integer, Integer)]
triples = [(a, b, c) | c <- [1 .. 10], a <- [1 .. c], b <- [1 .. a], a + b + c == 24, a ^ 2 + b ^ 2 == c ^ 2]

test6 :: (Char, Char)
test6 = ('a', 'b')

addThree :: Int -> Int -> Int -> Int
addThree x y z = x + y + z

product' :: (Num a, Enum a) => a -> a
product' n = product [1 .. n]

test7 :: Int
test7 = read "5" :: Int

test8 :: Int
test8 = minBound :: Int

lucky :: Int -> String
lucky 7 = "Lucky number seven!"
lucky x = "Sorry, you're out of luck, pal!"

sayMe :: Int -> String

sayME :: (Eq a, Num a) => a -> String
sayME 1 = "One!"

sayMe 2 = "Two!"
sayMe 3 = "Three!"
sayMe 4 = "Four!"
sayMe 5 = "Five!"
sayMe x = "Not between 1 and 5"

fact' :: Int -> Int
fact' 0 = 1
fact' n = n * fact' (n - 1)

addVectors :: (Num a, Num b) => (a, b) -> (a, b) -> (a, b)
addVectors (x1, y1) (x2, y2) = (x1 + x2, y1 + y2)

first' :: (a, b, c) -> a
first' (x, _, _) = x

fuck :: IO ()
fuck = do
  putStrLn "Hello"

main :: IO ()
main = someFunc

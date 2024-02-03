doubleMe x = x + x

doubleUs x y = doubleMe x + doubleMe y

doubleSmallNumber x = if x > 100 then x else x * 2

hankhogan = "Hank Hogan"

lostNumbers = [4, 8, 15, 16, 23, 42]

test1 = [2 * x | x <- [1 .. 10], x * 2 >= 12]

test2 = [x | x <- hankhogan, x `elem` ['A' .. 'Z']]

boomBangs xs = [if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]

test3 = boomBangs [7 .. 13]

test4 = [x + y + z | x <- [1, 2, 3], y <- [10, 100, 1000], x * y > 100, z <- [100, 1000, 10000]]

length' xs = sum [1 | _ <- xs]

removeNonUppercase st = [c | c <- st, c `elem` ['A' .. 'Z']]

test5 xxs = [[x | x <- xs, even x] | xs <- xxs]

t1 = (1, "shits")

t2 = 1

_ = snd (8, 11)

_ = take 5 (zip [1 ..] ['a' ..])

triples = [(a, b, c) | c <- [1 .. 10], a <- [1 .. c], b <- [1 .. a], a + b + c == 24, a ^ 2 + b ^ 2 == c ^ 2]

test6 :: (Char, Char)
test6 = ('a', 'b')

addThree :: Int -> Int -> Int -> Int
addThree x y z = x + y + z

product' n = product [1 .. n]

test7 = read "5" :: Int

test8 = minBound :: Int

lucky :: Int -> String
lucky 7 = "Lucky number seven!"
lucky x = "Sorry, you're out of luck, pal!"

sayMe :: Int -> String
sayME 1 = "One!"
sayMe 2 = "Two!"
sayMe 3 = "Three!"
sayMe 4 = "Four!"
sayMe 5 = "Five!"
sayMe x = "Not between 1 and 5"

fact' :: Int -> Int
fact' 0 = 1
fact' n = n * fact' (n - 1)

addVectors (x1, y1) (x2, y2) = (x1 + x2, y1 + y2)

first' (x, _, _) = x

main = do
  putStrLn "Hello"

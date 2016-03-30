---- Basics ----
{-
Filename.hs
:l Filename
:r
:t fxn
:q
ghc --make Filename
./Filename
-}

import Data.List
import System.IO

---- Data types
{-
Int
Integer
Float
Double
Bool
Char
Tuple
-}
maxInt = maxBound :: Int
minInt = minBound :: Int
exmInt = 55 :: Int

---- Math functions
{-
x + y
x - y
x * y
x / y
x ** y
x + (-y)

mod x y OR x `mod` y
fromIntegral x			Integer to Float
exp x					e ^ x
log x
truncate x
round x
ceiling
floor
-}

---- Lists
list1 = [1,2,3,4,5]
-- Concatenate
list2 = list1 ++ [6,7,8,9,10]
-- Cons
listodd = 1:3:5:7:9:11:13:[]
-- Length
lenlist1 = length list1
-- Reverse
tsil1 = reverse list1
-- isEmpty
isList1Empty = null list1
-- Indexing
thirdList2 = list2 !! 2
-- List Parts
headlo = head listodd
taillo = tail listodd
lastlo = last listodd
initlo = init listodd
takelo = take 3 listodd
droplo = drop 3 listodd
isInlo = 7 `elem` listodd
maxlo = maximum listodd
minlo = minimum listodd
sumlo = sum listodd
prodlo = product listodd
-- Range generation
listeven = [2,4..20]
actoy = ['a', 'c'..'z']
-- Infinite list (lazy creation)
tenonwards = [10,20..]
hundred = tenonwards !! 9
-- Repetition
manytens = take 20 (repeat 10)
manynines = replicate 10 9
manylist1 = take 15 (cycle list1)
-- Set notation
evenlist2 = [x * 2 | x <- list2]
divby6 = [x * 3 | x <- [1..30], mod x 2 == 0]
-- Sort
sortedlist = sort [4,1,4,6,2,6,8]
-- ZipWith
prodOfLists = zipWith (*) [5,6,7,8,9,10] [2,3,4,5,6,7]
-- Filter
listoddg5 = filter (>5) listodd
-- While
oddsTo20 = takeWhile (<= 20) [1,3..]
-- Foldl
sumList = foldl (+) 7 [2,3,4,5,6]
-- Other examples
pow2List = [2^x | x <- [0..10]]
multTable = [[x * y | y <- [1..10]] | x <- [1..10]]

---- Tuples
tuplePair = ("Francis dela Cruz", 201508086)
tpname = fst tuplePair
tpsn = snd tuplePair
-- zip
names = ["Francis", "Zac", "Quintin"]
studnums = [201508085, 201508084, 201508087]
namestudnums = zip names studnums

---- Functions
{-
main = do
	putStrLn "Enter something"
	name <- getLine
	putStrLn ("Hello " ++ name)
-}

-- Type declaration (OPTIONAL)
-- eg. :t sqrt >> sqrt :: Floating a => a -> a
addMe :: Int -> Int -> Int
-- funcName param1 param2 '=' operations (returned value)
{- Note: functions can't begin with uppercase
		 functions w/o params are definitions or names -}
addMe x y = x + y
addTuple :: (Int, Int) -> (Int, Int) -> (Int, Int)
addTuple (x, y) (x2, y2) = (x + x2, y + y2)

-- Cases
whatAge :: Int -> String
whatAge 16  = "You can drive"
whatAge 18 = "Nope"
whatAge _ = "eh"

-- Recursion
factorial :: Int -> Int
factorial 0 = 1 --Base case
factorial n = n * factorial (n - 1)

fibon :: Int -> Int
fibon 0 = 1
fibon 1 = 1
fibon n = fibon (n-1) + fibon (n-2)

-- List function
prodFact n = product [1..n]

-- Guards
whatGrade :: Int -> String
whatGrade age
	| (age > 5) && (age <= 6) = "Kindergarten"
	| (age > 6) && (age <= 10) = "Elementary"
	| (age > 10) && (age <= 14) = "Middle"
	| (age > 14) && (age <= 18) = "High"
	| otherwise = "Something else"

-- Where
gwa :: [Double] -> String
gwa grades
	| avg < 60.0 = "F"
	| (avg >= 60.0) && (avg < 80.0) = "D-C"
	| avg >= 80.0 = "B-A"
	where avg = (sum grades) / (fromIntegral (length grades))

-- (x:y)
getListItems :: [Int] -> String
getListItems [] = "empty"
getListItems (x:y:[]) = show x ++ " then "  ++ show y

-- @
getFirstItem :: String -> String
getFirstItem [] = "emptty"
getFirstItem all@(x:xs) = "first of " ++ all ++ " is " ++ [x]

---- Higher Order Functions
-- Map
times4 :: Int -> Int
times4 x = x * 4
listTimes4 = map times4 [1..5]
-- (x:xs)
sumtest :: [Int] -> Int
sumtest [x] = x
sumtest (x:xs) = x + sumtest xs
-- Eg.
strEq :: [Char] -> [Char] -> Bool
strEq (x:xs) (y:ys) = x==y && strEq xs ys
strEq _ _ = False

-- Fxn to Fxn
doMult :: (Int -> Int) -> Int --The one inside parenthesis is a fxn
doMult func = func 3
twelve = doMult times4

getAddFxn :: Int -> (Int -> Int)
getAddFxn x y = x + y
adds5 = getAddFxn 5
nine = adds5 4

-- Lambda (\param -> return)
db1to10 = map (\x -> x * 2) [1..10]

-- Conditionals and Logicals
-- < > <= >= == /= && || not
dblEvenOnly y =
	if (mod y 2 /= 0)
		then y
		else y * 2

getClass n = case n of
	5 -> "Kinder"
	6 -> "Elem"
	_ -> "blah"

---- Modules
-- import Module
{-
module SampFunctions (getClass, dblEvenOnly) where
	-- define the functions
-}

---- Custom Data Types
-- Enumerations
data Suit = Spades | Hearts | Diamonds | Clubs

-- Custom Types
data Card = Card Int Suit Bool
	deriving Show

randCard :: Card
randCard = Card 10 Spades True
getRank :: Card -> Int
getRank (Card n _ _) = n

-- Polymorphic Types
data Shape = Circle Float Float Float | Rectangle Float Float Float Float
	deriving Show

area :: Shape -> Float
area (Circle _ _ r) = pi * r ^ 2
area (Rectangle x1 y1 x2 y2) = (abs $ x2 - x1) * (abs $ y2 - y1)
-- Note: $ xxx is the same as (xxx)

-- Chaining
sumVal = putStrLn (show (1 + 2))
sumVal2 = putStrLn . show $ 1 + 2

---- Type Classes (Num, Eq, Or, Show)
{-
:t (+) >> (+) :: Num a => a -> a -> a
-}
data Employee = Employee {
	name :: String,
	position :: String,
	idNum :: Int
} deriving (Eq, Show) --Can be equated or shown

franzac = Employee {name="Francis Zac", position="Manager", idNum=12}

-- Instance
instance Show Suit where
	show Spades = "S"
	show Hearts = "H"
	show Diamonds = "D"
	show Clubs = "C"

-- Custom
class MyEq a where
	areEqual :: a -> a -> Bool

instance MyEq Suit where
	areEqual Spades Spades = True
	-- sosf
	areEqual _ _ = False

---- IO
{-
	CLI:
		putStrLn
		var <- getLine
	File:
		filevar <- openFile "file.txt" WriteMode
		hPutStrLn filevar ("String string")
		hClose filevar

		filevar <- openFile "file.txt" ReadMode
		contents <- hGetContents filevar
		putStr contents
		hClose filevar
-}

---- Eg. Fibonacci List
-- 1,1,2,3,5,8,13,...
fib = 1 : 1 : [a + b | (a,b) <- zip fib (tail fib)]
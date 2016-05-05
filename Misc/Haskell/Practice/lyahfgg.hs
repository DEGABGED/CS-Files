---- Pattern Matching
-- Matching an input to see if it follows a certain pattern, then deconstructing and using it as so.

---- Guards
-- For testing boolean conditions
-- Like syntactically sweet if else trees
-- If no conditions are satisfied, can fall back to pattern matching

---- Let
-- Like `where` bindings, but much more local -> cannot be used in guards

-- `let` bindings are actual expressions, while `where` bindings are syntactic bindings

cylinder :: (RealFloat a) => a -> a -> a
cylinder r h =
	let sideArea = 2 * pi * r * h
		topArea = pi * r ^ 2
	in sideArea + 2 * topArea -- Binding and using functions

(let a=100; b=200 in a*b, let foo="hello "; bar="world" in foo ++ bar) -- Binding several variable inline

(let (a,b,c) = (1,2,3) in a+b+c) * 100 -- Pattern Matching

calcBmis :: (RealFloat a) => [(a,a)] -> [a]
calcBmis xs = [bmi | (w,h) <- xs, let bmi = w / h ^ 2] -- List comprehension

---- Case expressions
-- Much like switch statements, but with pattern matching capabilities
-- PMing in function definitions is sytactic sugar for case expressions
-- Case expressions can be used in the middle of expressions
describeList :: [a] -> String

-- PMing for function definition
describeList [] = "List is empty"
describeList [x] = "List is singleton"
describeList xs = "List is long"

-- Case expressions
describeList xs = "List is " ++ case xs of [] -> "empty"
	[x] -> "singleton"
	xs -> "long"

-- Where binding
describeList xs = "List is " ++ strch xs
	where strch [] = "empty"
		strch [x] = "singleton"
		strch xs = "long"

------ Modules ------
---- 29/04/2016
---- Importing
-- import Data.List (nub, sort) //import only num and sort from Data.List
-- import Data.List hiding (nub) //import all but nub from Data.List
-- import qualified Data.Map as M //eg. M.filter vs filter

---- Data.List
-- intersperse, intercalate, transpose
-- and, or, any, all, iterate
-- splitAt, takeWhile, dropWhile, break, span, sort, group
-- inits, tails, isInfixOf, isPrefixOf, isSuffixOf, elem, notElem
-- partition, find, elemIndex (Maybe), elemIndices, findIndex, findIndices
-- lines, unlines, nub, delete, \\, union, intersect, insert
-- genericLength/Take/Drop/SplitAt/Index/Replicate
-- nub/delete/union/intersect/groupBy (take an equality function)
-- on :: (b -> b -> c) -> (a -> b) -> a -> a -> c
--   f `on` g = \x y -> f (g x) (g y)
-- sortBy, insertBy, maximumBy, minimumBy

---- Creation
{- Geometry.hs
	module Geometry
	( sphereVolume
	, sphereArea
	) where
	
	sphereVolume :: Float -> Float
	-- sosf.
-}
{- Geometry/Sphere.hs
	module Geometry.Sphere
	( volume
	, area
	) where

	-- sosf.

------ Custom Types and Typeclasses ------
---- Data
{-
	data Shape = Circle Float Float Float | Rectangle Float Float Float Float
	// append `deriving (Show)` to display them in the CLI
	// Circle :: Float -> Float -> Float -> Shape, sosf.
	// You can pattern match with constructors
	surface (Circle _ _ r) = pi * r ^ 2
-}
-- Exporting
{-
	module Shapes
	( Shape(..)
	, surface
	) where
-}
---- Records
{-
	data Student = Student {
			firstName :: String,
			lastName :: String,
			age :: Int,
			height :: Float
			weight :: Float
		} deriving (Show)
	// Automatically: firstName :: Person -> String, sosf.
	// When shown, it is displayed like an object
-}

---- Derived instances
{-
	When deriving from Eq, Show, etc., Haskell will automagically implement each based on the constructors and the data contained
	// Enum and Bounded for values with precessors / successors and min / max respectively
		// based on the order of constructors
-}

---- Type synonyms
{-
	eg. type String = [Char], type Dictionary = [(Int, String)]
	type AssocList k v = [(k,v)]
	// ! Distinction between type constructors and value constructors
	// Either a b = Left a | Right b deriving (Show, Read)
		// For Error messages (Left) and Results (Right)
-}

---- Recursive Data types
{-
	eg. data List a = Empty | Cons (a) (List a) deriving (Show, Read, Eq, Ord)
	// infixr <priority> <symbols for infix operation>
	// pattern matching actually matches constuctors
	// Try implementing a Linked List here
-}

---- Typeclasses
-- 03/05/2016
{-
	// For Eq:
	class Eq a where
		(==) :: a -> a -> Bool
		(/=) :: a -> a -> Bool
		x == y = not (x /= y)
		x /= y = not (x == y)

	// Creating an instance
	data Coin = Head | Tail
	instance Eq Coin where
		Head == Head = True
		Tail == Tail = True
		_ == _ = False
	instance Show Coin where
		show Head = "Heads"
		show Tail = "Tails"
-}

-- Eg. Boolean values in Javascript
{-
	class fuzzyBool where
		fuzzyBool :: a -> Bool

	instance fuzzyBool [a] where
		fuzzyBool [] = False
		fuzzyBool _ = True

	// sosf.
	fbIf :: (fuzzyBool y) => y -> a -> a -> a
-}

---- Functors
-- Typeclass:
{-
	class Functor f where
		fmap :: (a -> b) -> f a -> f b
	// f is a type constructor w/ one parameter

	// Examples:
	instance Functor [] where
		fmap = map
	instance Functor Maybe where
		fmap f (Just x) = Just (f x)
		fmap f Nothing = Nothing
-}

---- IO
-- Basic IO
{-
	main = do
		putStrLn "Enter something"
		name <- getLine
		putStrLn ("Something " ++ name)

	// getLine :: IO String
	// putStrLn :: IO () -- () is like void in Java
	// The IO is like an encapsulation of the actual data, which indicates that it came from the IO stuff, which tends to be impure.
	// note: a <- IO a, not a = IO a
-}

-- Compiling
{-
	ghc --make filename; ./filename
	runhaskell filename.hs
-}

-- Returning
{-
	// return x yields an IO action from a pure valu
	// It doesn't stop the program flow
	main = do
		a <- return "yeah"
		-- a is a pure String
	// return () yields a dud and can be used when you need to return an IO action but don't want to.
-}

-- IO functions
{-
	-- putChar, putStr
	putStr :: String -> IO ()
	putStr [] = return ()
	putStr (x:xs) = do
		putChar x
		putStr xs
	-- print = putStrLn . show
	-- getChar
	-- when :: Boolean -> IO a (when True do ...)
		-- in Control.Monad
	-- sequence :: [IO a] -> IO [a]
	-- mapM f [a] and forM [a] f -> map an IO function over a list and sequencing it
-}

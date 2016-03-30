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


chain :: (Integral a) => a -> [a]
chain n = n : ch n where
	ch x
		| x == 1 = []
		| odd x = (x*3 + 1) : ch (x*3 + 1)
		| otherwise = (div x 2) : ch (div x 2)

-- Better application
chain' :: (Integral a) => a -> [a]
chain' 1 = [1]
chain' n
	| even n = n : chain (div n 2)
	| odd n = n : chain (3*n + 1)

-- Get the lengths of their sequences
sizes = map length (map chain [1..])
-- Pair with their indices
sizesIndexed = zip [1..] sizes
-- Filter those greater than something
sl = fst $ head $ filter (\(a,b) -> b > 20) sizesIndexed


-- Func version
smallLong x = fst $ head $ filter (\(a,b) -> b >= x) sizesIndexed

-- Replace 0s with 1s and 1s with 10s

stringfxn :: [Char] -> [Char]
stringfxn [] = []
stringfxn (c:cs)
	| (c == '1') = '1' : '0' : stringfxn cs
	| (c == '0') = '1' : stringfxn cs

{-
charfxn :: Char -> String
charfxn '1' = "10"
charfxn '0' = "1"
-}


map' :: (a -> b) -> [a] -> [b]
map' _ [] = []
map' f (x:xs) = (f x) ++ (map' f xs)


episode10 :: Int -> [Char]
episode10 0 = "1"
episode10 1 = "10"
episode10 n = stringfxn (episode10 $ n-1)

{-
		| (char == '1') = '1' : '0'
		| otherwise = '1'
-}
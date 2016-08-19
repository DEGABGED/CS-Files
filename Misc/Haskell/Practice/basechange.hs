---- Previous attempts
-- charmap c = snd $ head $ [ (x,y) | (x,y) <- zip [0..9] ['0'..'9'], x == c]
{-
basech :: Int -> Int -> [Char]
basech b 0 = []
basech b a = let greatestBelow b a = last $ takeWhile (<=a) $ powers b
			in (charlist !! (div a (greatestBelow b a))) : basech b (mod a (greatestBelow b a))
-}
-- basech a b = scanr (\x acc -> (charlist) !! (div a x) : acc) [] $ takeWhile (<=a) $ powers b

charlist = ['0'..'9'] ++ ['A'..'Z']
powers x = map (x^) [0,1..]

greatestBelow b a = last $ takeWhile (<=a) $ powers b

basech :: Int -> Int -> [Char]
basech 0 b = ['0']
basech a b
	| b < 2 = []
	| otherwise = basechHelper a b $ greatestBelow b a

basechHelper :: Int -> Int -> Int -> [Char] -- Number -> Base -> BasePower -> String
basechHelper n b 0 = []
basechHelper n b p = charlist !! (div n p) : basechHelper (mod n p) b (div p b)

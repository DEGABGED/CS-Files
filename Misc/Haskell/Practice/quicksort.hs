qsort' :: (Ord a) => [a] -> [a]
qsort' [] = []
qsort' [x] = [x]
qsort' (x:xs) = let
	small = qsort' [y | y <- xs, y < x]
	big = qsort' [y | y <- xs, y >= x]
	in small ++ [x] ++ big

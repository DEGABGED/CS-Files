reversi :: [a] -> [a]
reversi xs = foldl (\acc x -> x : acc) [] xs
{-
qsort' :: (Ord a) => [a] -> [a]
qsort' [] = []
qsort' [x] = [x]
qsort' (x:xs) =
	let small = qsort' [a | :
-}

last' :: [a] -> a
last' [x] = x
last' (x:xs) = last' xs

sectolast :: [a] -> a
sectolast (x:y:[]) = x
sectolast (x:xs) = sectolast xs

index :: [a] -> Int -> a
index [] n = error "Empty list"
index xs n | n < 1 = error "Invalid index"
index xs 1 = head xs
index (x:xs) n = index xs $ n-1

size' :: [a] -> Int
size' [] = 0
size' xs = foldl (\acc x -> acc + 1) 0 xs

reversi :: [a] -> [a]
reversi [] = []
reversi xs = foldl (flip (:)) [] xs

isPalin :: (Eq a) => [a] -> Bool
isPalin xs = foldl (\acc x -> acc && x) True $ zipWith (\x y -> x == y) xs $ reversi xs

compress' :: (Eq a) => [a] -> [a]
compress' xs = foldr (\x acc -> if acc /= [] && x == head acc then acc else x:acc) [] xs

pack' :: (Eq a) => [a] -> [[a]]
pack' xs = foldr (\x acc -> if acc /= [] && x == (head . head) acc then x:(head acc) else [x]:acc) [] xs

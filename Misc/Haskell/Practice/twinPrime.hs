isPrime :: Int -> Bool
isPrime n = foldl (\acc x -> if mod n x == 0 then True else acc) False [2..(ceiling(sqrt(n)))]

twinprimes = [ (x,y) | x <- [5..], y <- [3..], x - y == 2, isPrime x && isPrime y]

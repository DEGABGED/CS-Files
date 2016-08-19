isPrime :: (Integral a) => a -> Bool
isPrime n = not $ foldl (\acc x -> acc || mod n x == 0) False [2..round (sqrt (fromIntegral n))]

twinprimes = filter istp (zip [3,5..] [5,7..]) where istp (x,y) = isPrime x && isPrime y

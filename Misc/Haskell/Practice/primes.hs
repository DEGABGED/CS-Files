import Data.List

primeByList :: (Integral a) => a -> [a] -> Bool
primeByList x xs = foldr (\ y acc -> mod x y /= 0 && acc) True xs

primeToList = flip primeByList

--sieveprimes = 2 : filter (primeToList sieveprimes) [3,5..]
--primes = 2 : [ x | x <- [3,5..], primeByList x primes]
primes = 2 : sieve
	where sieve = filter (primeToList primes) [3,5..]

-- To test filter with self
prods = 1 : filter (> product prods) [2..10]

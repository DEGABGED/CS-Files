import Data.List
import System.IO

singleRow :: Int -> Int -> [Char] --Base size -> Row Size (both odd)
singleRow b n
	| odd b && odd n =  let s = div (b-n) 2
		in iterate (' ':) (iterate ('@':) (iterate (' ':) ['\n'] !! s) !! n) !! s
		--in ((flipdex s (iterate (' ':))) . (flipdex n (iterate ('@':))) . (flipdex s (iterate (' ':)))) ['\n']
			--where flipdex = flip (!!)

triangleRec :: Int -> Int -> [Char] --Num of rows, Current row
triangleRec n c
	| n == c = []
	| otherwise = singleRow (rowsize n) (rowsize c) ++ triangleRec n (c+1)
	where rowsize x = [1,3..] !! x

triangle :: Int -> IO () -- Row -> String
triangle n
	| n > 0 = putStr $ triangleRec n 0

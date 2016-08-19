import Data.List
import System.IO

singleRow :: Int -> Int -> [Char] --Base size -> Row Size (both odd)
singleRow b n
	| odd b && odd n =  let s = div (b-n) 2
		in iterate (' ':) (iterate ('@':) (iterate (' ':) ['\n'] !! s) !! n) !! s
		--in ((flipdex s (iterate (' ':))) . (flipdex n (iterate ('@':))) . (flipdex s (iterate (' ':)))) ['\n']
			--where flipdex = flip (!!)

diamondRec :: Int -> Int -> [Char] -- Num of rows, Current row
diamondRec n c
	| n == c = []
	| otherwise = singleRow (maximum (rowsize n)) (rowsize n !! c) ++ diamondRec n (c+1)
	where rowsize s = (take (div s 2 + 1) [1,3..] ++ reverse (take (div s 2) [1,3..]))

diamond :: Int -> IO ()
diamond n
	| odd n && n > 0 = putStr $ diamondRec n 0

main = do
	putStrLn "Enter something"
	something <- getLine
	diamond (read something)

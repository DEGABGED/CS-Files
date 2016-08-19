charMap z = snd $ head $ [(x,y) | (x,y) <- (zip [0..9] ['0'..'9']), z == x]

fibu1 = map (\x -> if (mod x 3)==0 then "fi" else "") [1..50]
fibu2 = zipWith (\x y -> if (mod y 5)==0 then (x++"bu") else (x++"")) fibu1 [1..50]

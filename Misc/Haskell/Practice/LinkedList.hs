data LList a = Null | Node a (LList a) deriving (Show, Read, Eq)

instance Functor LList where
	fmap f Null = Null
	fmap f (Node a b) = Node (f a) (fmap f b)

singleton :: a -> LList a
singleton x = Node x (Null)

llistInsert :: (Show a) => a -> LList a -> LList a
llistInsert x Null = singleton x
llistInsert x list = Node x list

llistFromList :: (Show a) => [a] -> LList a
llistFromList [] = Null
llistFromList (x:xs) = Node x (llistFromList xs)

showList' :: (Show a) => LList a -> IO ()
showList' Null = putStr "[]\n"
showList' (Node a b) = do
	putStr $ show a ++ "->"
	showList' b

llistInsertMid :: (Num a, Eq a, Eq b) => b -> LList b -> a -> LList b
llistInsertMid x (Node a b) 0 = Node x (Node a b)
llistInsertMid x Null _ = Node x Null
llistInsertMid x (Node a b) n = Node a (llistInsertMid x b (n-1))

data Stack a = Null | Node a (Stack a) deriving (Show, Read, Eq)

instance Functor Stack where
	fmap f Null = Null
	fmap f (Node a b) = Node (f a) (fmap f b)

singleton :: a -> Stack a
singleton x = Node x (Null)

stackPush :: (a, Stack a) -> Stack a
stackPush (a, sa) = Node a sa

stackPop :: (Num a) => Stack a -> (a, Stack a)
stackPop Null = (0, Null)
stackPop (Node a sa) = (a, sa)

stackPeek :: (Num a) => Stack a -> a
stackPeek Null = 0
stackPeek (Node a sa) = a

listToStack :: [a] -> Stack a
listToStack [] = Null
listToStack (x:xs) = Node x (listToStack xs)

stackToList :: Stack a -> [a]
stackToList Null = []
stackToList (Node a sa) = a : (stackToList sa)

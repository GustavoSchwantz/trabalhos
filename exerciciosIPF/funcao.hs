mapInt :: (Int -> Int) -> [Int] -> [Int]
mapInt f []      = []
mapInt f (a : x) = f a : mapInt f x

times2 :: Int -> Int
times2 n = n*2

times3 :: Int -> Int
times3 n = n*3


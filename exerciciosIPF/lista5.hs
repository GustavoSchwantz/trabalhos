-- exercício 1
membro :: [Int] -> Int -> Bool
membro [] n       = False
membro (x : xs) n = (x == n) || (membro xs n)

-- exercício 2
membroNum :: [Int] -> Int -> Int
membroNum [] n       = 0
membroNum (x : xs) n = (umOuZero x n) + (membroNum xs n)

-- exercício 3
membro2 :: [Int] -> Int -> Bool
membro2 ns n   
    | (membroNum ns n) > 0 = True
    | otherwise            = False

-- exercício 4
unico :: [Int] -> [Int]
unico ns       = unico2 ns ns

-- exercício 5

umOuZero :: Int -> Int -> Int
umOuZero x y
    | (x == y)  = 1
    | otherwise = 0
 

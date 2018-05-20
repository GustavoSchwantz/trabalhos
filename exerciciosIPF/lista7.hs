-- exercício 1
total :: (Int -> Int) -> Int -> Int
total f 0 = f 0
total f n = f n + total f (n - 1)

vendas :: Int -> Int
vendas 0 = 0
vendas 1 = 42
vendas 2 = 313
vendas 3 = 20
vendas 4 = 7
vendas 5 = 10
vendas 6 = 9
vendas 7 = 50
vendas 8 = 888
vendas 9 = 70
vendas _ = 60

-- exercício 2
foldInt :: (Int -> Int -> Int) -> [Int] -> Int
foldInt f []       = 0
foldInt f (x : xs) = f x (foldInt f xs)

soma :: Int -> Int -> Int
soma x y = x + y

-- exercício 4
filterString :: (Char -> Bool) -> [Char] -> [Char]
filterString f []       = []
filterString f (x : xs) 
        | f x = x : filterString f xs
        | otherwise   = filterString f xs

naoEspaco :: Char -> Bool
naoEspaco x = x /= ' '

eA :: Char -> Bool
eA x = (x == 'a') || (x == 'A')

-- exercício 6
umaFuncao :: [Int] -> Int
umaFuncao xs = foldInt soma (mapInt elevadoDois xs)

mapInt :: (Int -> Int) -> [Int] -> [Int]
mapInt f []       = []
mapInt f (x : xs) = f x : mapInt f xs

elevadoDois :: Int -> Int
elevadoDois x = x * x

-- exercício 7
outraFuncao :: ([Int] -> [Int]) -> Int -> Bool
outraFuncao f n = peloMenosUm (> 0) (f [0..n]) 

peloMenosUm :: (Int -> Bool) -> [Int] -> Bool
peloMenosUm f []       = False
peloMenosUm f (x : xs) = (f x) || (peloMenosUm f xs) 

identidade :: [Int] -> [Int]
identidade ns = ns

somaUm :: [Int] -> [Int]
somaUm []       = []
somaUm (x : xs) = (x + 1) : somaUm xs 

-- exercício 8
duasVezes :: (Int -> Int) -> Int -> Int
duasVezes f n = f (f n)

times2 :: Int -> Int
times2 x = x * 2

-- exercício 9
inter :: Int -> (Int -> Int) -> Int -> Int
inter 3 f x = f(f (f x))















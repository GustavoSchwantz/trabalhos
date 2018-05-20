-- exercício 1
adicionaTupla :: (Int, Int, Int) -> Int
adicionaTupla (x, y, z) = x + y + z

-- exercício 2
shift :: ((Int, Int), Int) -> (Int, (Int, Int))
shift ((x, y), z) = (z, (x, y))

-- exercício 3
minEmax :: Int -> Int -> Int -> (Int, Int)
minEmax x y z = (myMin x (myMin y z), myMax x (myMax y z))

-- exercício 4
ordenaTupla :: (Int, Int, Int) -> (Int, Int, Int)
ordenaTupla (x, y, z) 
    | (x >= y) && (y >= z) = (z, y, x)
    | (x >= z) && (z >= y) = (y, z, x)
    | (y >= x) && (x >= z) = (z, x, y)
    | (y >= z) && (z >= x) = (x, z, y)
    | (z >= y) && (y >= x) = (x, y, z)
    | (z >= x) && (x >= y) = (y, x, z)
    
-- exercício 5
zeroVenda :: Int -> (Int, Bool)
zeroVenda n
    | vendas (n) == 0    =  (n, True)
    | n == 0             =  (-1, False)
    | otherwise          = zeroVenda (n - 1)

-- exercício 6
type Livro = (String, String, Int)

livro1 :: Livro
livro1 = ("Moby Dick", "Herman Melville", 11111111)

livro2 :: Livro
livro2 = ("Hamlet", "Shakespeare", 22222222)

titulo :: Livro -> String
titulo (t, a, i) = t

autor :: Livro -> String
autor (t, a, i) = a

isbn :: Livro -> Int
isbn (t, a, i) = i 

myMax :: Int -> Int -> Int
myMax x y
    | x >= y    = x
    | otherwise = y

myMin :: Int -> Int -> Int
myMin x y
    | x <= y    = x
    | otherwise = y

vendas :: Int -> Int
vendas 0 = 1
vendas 1 = 42
vendas 2 = 313
vendas 3 = 0
vendas 4 = 7
vendas 5 = 10
vendas 6 = 9
vendas 7 = 50
vendas 8 = 888
vendas 9 = 70
vendas _ = 60


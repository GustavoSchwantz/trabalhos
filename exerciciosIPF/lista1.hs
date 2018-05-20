-- exercício 1
osQuatroSaoIguais :: Int -> Int -> Int -> Int -> Bool
osQuatroSaoIguais x y z w = (x == y) && ( y == z) && (z == w)

-- exercício 2
quantosSaoIguais :: Int -> Int -> Int -> Int 
quantosSaoIguais x y z  
        | (x == y) && (y == z)                 =    3
        | (x == y) || (y == z) || (x == z)     =    2
        | otherwise                            =    0

-- exercício 3
todosDiferentes :: Int -> Int -> Int -> Bool
todosDiferentes x y z 
        | (x /= y) && (y /= z) && (x /= z) = True
        | otherwise                        = False

-- exercício 6
todosIguais :: Int -> Int -> Int -> Bool
todosIguais x y z = (x == y) && ( y == z)

-- exercício 7
quantosSaoIguais2 :: Int -> Int -> Int -> Int
quantosSaoIguais2 x y z
        | todosIguais x y z                    = 3
        | (todosDiferentes x y z) /= True      = 2
        | otherwise                            = 0 

-- exercício 8
elevadoDois :: Int -> Int
elevadoDois x = x * x

-- exercício 9
elevadoQuatro :: Int -> Int
elevadoQuatro x = (elevadoDois x) * (elevadoDois x)

-- exercício 10
vendas :: Int -> Int
vendas 0 = 3
vendas 1 = 0
vendas 2 = 2
vendas _ = 42

vendaTotal :: Int -> Int
vendaTotal 0 = vendas 0
vendaTotal n = vendas n + vendaTotal (n - 1)


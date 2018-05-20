-- exercício 1
myMax :: Int -> Int -> Int
myMax x y 
    | x >= y    = x
    | otherwise = y

-- exercício 2
maiorVenda :: Int -> Int
maiorVenda n 
    | (n == 0) = myMax (vendas (0)) (vendas (0))
    | (n > 0)  = myMax (vendas (n)) (maiorVenda (n - 1))

-- exercício 3
maxVenda :: Int -> Int
maxVenda n
    | vendas (n) == maiorVenda (n)    = n
    | otherwise                       = maxVenda (n - 1)

-- exercício 4
zeroVendas :: Int -> Int
zeroVendas n
    | vendas (n) == 0    =  n
    | n == 0             = -1
    | otherwise          = zeroVendas (n - 1)

-- exercício 5
sVendas :: Int -> Int -> Int
sVendas s n
    | vendas (n) == s    =  n
    | otherwise          = sVendas s (n - 1)

-- exercício 6
zeroVendas2 :: Int -> Int
zeroVendas2 n = sVendas 0 n

-- exercício 7
maiorVenda2 :: Int -> Int -> Int
maiorVenda2 m n
    | (n == m) = myMax (vendas (m)) (vendas (m))
    | (n > 0)  = myMax (vendas (n)) (maiorVenda2 m (n - 1))

maxVenda2 :: Int -> Int -> Int
maxVenda2 m n
    | vendas (n) == maiorVenda2 (m) (n)    = n
    | otherwise                            = maxVenda2 (m) (n - 1)

zeroVendas3 :: Int -> Int -> Int
zeroVendas3 m n
    | vendas (n) == 0    =  n
    | n == m             = -1
    | otherwise          = zeroVendas3 (m) (n - 1)

sVendas2 :: Int -> Int -> Int -> Int
sVendas2 s m n
    | (vendas (n) == s) && (n >= m)    =  n
    | otherwise                        = sVendas2 (s) (m) (n - 1)

zeroVendas4 :: Int -> Int -> Int
zeroVendas4 m n = sVendas2 0 m n

-- exercício 8
fatorial :: Int -> Int 
fatorial 1 = 1
fatorial n = n * fatorial (n - 1)

-- exercício 9
fatorial2 :: Int -> Int -> Int
fatorial2 m n 
    | (n == m)  = m
    | otherwise = n * fatorial2 (m) (n - 1)

-- exercício 10
fib :: Int -> Int
fib n 
    | (n == 1)  = 0
    | (n == 2)  = 1
    | otherwise = fib (n - 1) + fib (n - 2)

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

vendaTotal :: Int -> Int
vendaTotal 0 = vendas 0
vendaTotal n = vendas n + vendaTotal (n - 1)


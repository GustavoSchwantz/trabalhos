-- exercício 1
dobraLista :: [Int] -> [Int]
dobraLista []       = []
dobraLista (n : ns) = (n * n) : dobraLista ns
  
-- exercício 2
tamanho :: [Int] -> Int
tamanho []       = 0
tamanho (n : ns) = 1 + tamanho ns

-- exercício 3
produtoLista :: [Int] -> Int
produtoLista []       = 1
produtoLista (n : ns) = n * produtoLista ns

-- exercício 4
andLista :: [Bool] -> Bool
andLista [] = True
andLista (n : ns) = n && andLista (ns)

-- exercício 5
concatLista :: [[Int]] ->[Int]
concatLista []       = []
concatLista (n : ns) = n ++ concatLista ns
  
-- exercício 6
inverteLista :: [Int] -> [Int]
inverteLista []       = []
inverteLista (n : ns) = inverteLista ns ++ [n]


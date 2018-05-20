-- exercício 1
retornaUltimo :: [Int] -> Int
retornaUltimo [x]      = x
retornaUltimo (x : xs) = retornaUltimo xs

-- exercício 2
pegaPosicao :: Int -> [Int] -> Int 
pegaPosicao n (x : xs)
    | (n == 1)  = x
    | otherwise = pegaPosicao (n - 1) xs

-- exercício 3
pega :: Int -> [Int] -> [Int]
pega n []       = []
pega n (x : xs) 
    | (n == 0)  = []
    | otherwise = x : pega (n - 1) xs

-- exercício 4
retira :: Int -> [Int] -> [Int]
retira n []       = []
retira n (x : xs) 
    | (n == 0)  = x : xs
    | otherwise = retira (n - 1) xs

-- exercício 5
media :: [Int] -> Int
media []       = 0
media xs = (soma xs) `div` (length xs)

soma :: [Int] -> Int
soma []       = 0
soma (x : xs) = x + soma xs

-- exercício 6
pegaMaiores :: Int -> [Int] -> [Int]
pegaMaiores 0 xs       = []
pegaMaiores n []       = []    
pegaMaiores n (x : xs) = maior (x : xs) : pegaMaiores (n - 1) 
        (remover (maior (x : xs)) xs)

-- exercício 7
contaMaiores :: Int -> [Int] -> Int
contaMaiores n []       = 0
contaMaiores n (x : xs) 
        | (x > n)   = 1 + contaMaiores n xs
        | otherwise = contaMaiores n xs

-- exercício 8
concatena :: [a] -> [a] -> [a]
concatena [] [] = []
concatena xs [] = xs
concatena [] ys = ys
concatena xs ys = xs ++ ys

-- exercício 9
intercala :: [Int] -> [Int] -> [Int]
intercala [] []             = []
intercala xs []             = xs 
intercala [] ys             = ys
intercala (x : xs) (y : ys) = x : y : intercala xs ys 

-- exercício 10
compress :: Eq a => [a] -> [a]
compress []       = []
compress [x]      = [x]
compress (x : xs) 
        | (x /= (head xs))   = x : compress xs
        | otherwise          = compress xs 

-- exercício 11
-- pack :: [char] -> [[char]]
-- pack []       = []
-- pack [x]      = [[x]]
-- pack (x : xs) 
--        | (x == (head (head (pack xs)))) = [ x : head (pack xs)]
--        | otherwise                      = [x] : pack xs         

-- exercício 12
encode :: [Char] -> [(Int, Char)]
encode []       = []
encode [x]      = [(1, x)]
encode (x : xs) 
        | ( x == ( snd ( head (encode xs) ) ) ) = 
            ( (fst ( head (encode xs)) + 1), x) : tail (encode xs)
        | otherwise = (1, x) : encode xs

-- exercício 13
-- dupli :: [Int] -> [Int]
-- dupli []       = []
-- dupli [x]      = [x]
-- dupli (x : xs) 

-- exercício 14
repli :: Int -> [Char] -> [Char]
repli n []       = []
repli n [x]      = repliAux x n
repli n (x : xs) = repliAux x n ++ repli n xs

repliAux :: Char -> Int -> [Char]
repliAux x 0 = [] 
repliAux x n = x : repliAux x (n - 1) 

-- exercício 15
-- dropEvery :: Int -> [Char] -> [Char]
-- dropEvery n []       = []
-- dropEvery n (x : xs) = 

-- exercício 16
split :: Int -> [Char] -> ([Char], [Char])
split 0 [] = ([], [])
split 0 xs = ([], xs)
split n xs = (take n xs, drop n xs)

-- exercício 17
slice :: Int -> Int -> [Char] -> [Char]
slice x y ls = drop (x - 1) (take y ls)

maior :: [Int] -> Int
maior [x]      = x 
maior (x : xs) 
    | (maior xs >= x) = (maior xs)
    | otherwise       = x

remover :: Int -> [Int] -> [Int]
remover n []       = []
remover n (x : xs) 
    | (n == x)  = remover n xs
    | otherwise = x : remover n xs
 


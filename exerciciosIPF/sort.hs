ins :: Int -> [Int] -> [Int]
ins n []       = [n]
ins n (x : xs) 
    | (n >= x) && (n == x)  = x : xs
    | (n >= x)              = n : x : xs
    | otherwise = x : ins n xs

iSort :: [Int] -> [Int]
iSort [] = []
iSort (x : xs) = ins x (iSort xs)

qs :: [Int] -> [Int]
qs []       = []
qs (x : xs) = qs (menores x xs)
             ++ [x] ++
             qs (maiores x xs)

menores :: Int -> [Int] -> [Int]
menores n []       = []
menores n (x : xs) 
    | (x < n)   = x : (menores n xs)
    | otherwise = (menores n xs)
 
maiores :: Int -> [Int] -> [Int]
maiores n []       = []
maiores n (x : xs)  
    | (x >= n)   = x : (maiores n xs)
    | otherwise = (maiores n xs)

mimEmax :: [Int] -> (Int, Int)
minEmax [] = (0, 0) 
mimEmax xs = (head (iSort xs), head ( reverse ( (iSort xs)) ) )
  

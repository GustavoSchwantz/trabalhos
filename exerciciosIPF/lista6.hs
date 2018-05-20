-- exercício 1
somaTripla :: [(Int,Int,Int)] -> Int
somaTripla []       = 0
somaTripla (x : xs) = (somaTriplas x) + (somaTripla xs) 

somaTriplas :: (Int,Int,Int) -> Int
somaTriplas (x, y, z) = x + y + z

-- exercício 2
somaTupla :: [((Int,Int),(Int,Int))] -> Int
somaTupla []       = 0
somaTupla (x : xs) = (somaTuplasDeTuplas x) + (somaTupla xs)

somaTuplasDeTuplas :: ((Int, Int), (Int, Int)) -> Int
somaTuplasDeTuplas ((x0, y0), (x1, y1)) = x0 + y0 + x1 + y1

-- exercício 3
zipp :: [Int] -> [Int] -> [(Int,Int)]
zipp [] []             = []
zipp [] ys             = []
zipp xs []             = []
zipp (x : xs) (y : ys) = (x, y) : (zipp xs ys)

-- exercício 4
zipp3 :: [Int] -> [Int] -> [Int] -> [(Int,Int,Int)]
zipp3 [] _ _ = []
zipp3 _ [] _ = []
zipp3 _ _ [] = []
zipp3 (x : xs) (y : ys) (z : zs) = (x, y, z) : (zipp3 xs ys zs)

-- exercício 5
unZipp :: [(Int,Int)] -> ([Int], [Int])
unZipp []       = ([], [])
unZipp (x : xs) = let f = (unZipp xs)
                     in  (fst  x : fst f, snd x : snd f)
 

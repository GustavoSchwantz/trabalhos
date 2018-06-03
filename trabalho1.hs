nome = "Gustavo \n\
\Adolfo \n\ 
\Schwantz \n\
\Oliveira.\n"

quincasBorba = "RUBIAO fitava a enseada -- eram oito horas da manha.\n\
\Quem o visse com os polegares metidos no cordao do chambre a janela de uma\n\
\grande casa de Botafogo cuidaria que ele admirava aquele pedaco de agua\n\
\quieta mas em verdade vos digo que pensava em outra coisa.\n\
\Cotejava o passado com o presente. Que era ha um ano?\n\
\Professor. Que e agora? Capitalista! Olha para si para as chinelas\n\
\(umas chinelas de Tunis que lhe deu recente amigo Cristiano Palha) para a casa\n\
\para o jardim para a enseada para os morros e para o \
\ceu e tudo desde as chinelas\n\
\\ate o ceu tudo entra na \
\mesma sensacao de propriedade.\n"

domQuixote = "- Nao entendo la isso - replicou Sancho; - o que entendo e que quando estou a dormir,\n\
\nem tenho temor nem esperanca, nem pena nem gloria; e bem haja quem inventou o sono, capa\n\
\que encobre todos os pensamentos humanos, manjar que tira a fome, agua que afujenta a sede,\n\
\fogo que alenta o frio, frio que mitiga o ardor, e finalmente moeda geral com que tudo se compra,\n\
\balanca e peso que iguala o pastor ao rei e o simples ao discreto. So uma coisa ma tem o sono,\n\
\segundo tenho ouvido dizer: e parecer-se com a morte, por que, de uma adormecido a um morto,\n\
\pouca diferenca vai.\n"  

justifica :: String -> String
justifica [] = []
justifica ls = let f = separaLinhas ls
               in 
               juntaLinhas (insereEspacos (tamanhoMaiorLinha f) f) 

-- junta as linha tudo.
juntaLinhas :: [String] -> String
juntaLinhas []       = []
juntaLinhas (x : xs) = x ++ juntaLinhas xs

-- quebra o texto em linhas.
separaLinhas :: String -> [String]
separaLinhas [x]       = [[x]]
separaLinhas (x : xs) 
        | (x == '\n') = ['\n'] : separaLinhas xs
        | otherwise   = let f = separaLinhas xs 
                            in ((x : head f) : tail f)

-- encontra o tamanho da maior linha.
tamanhoMaiorLinha :: [String]-> Int
tamanhoMaiorLinha []       = 0
tamanhoMaiorLinha (x : xs) 
        | ((length x) > (tamanhoMaiorLinha xs)) = length x
        | otherwise                            = tamanhoMaiorLinha xs

-- retorna o número de espaços que deve ser colocado
-- em uma linha.
numEspacos :: Int -> String -> Int
numEspacos x ys = x - (length ys)

-- insere o número de espaços apropriado em cada linha.
insereEspacos :: Int -> [String] -> [String]
insereEspacos n []       = []
insereEspacos n (x : xs) = (insereEspacos'' n (numEspacos n x) x) : insereEspacos n xs   

-- recebe um inteiro n (número de espaços), uma string
-- e retorna a mesma string com um número <= n de espaços
-- adicionados.
insereEspacos' :: Int -> String -> String
insereEspacos' _ []             = []
insereEspacos' 0 ls             = ls
insereEspacos' n [a]            = [a]
insereEspacos' n (a : b : ls)    
        | (a == ' ' ) && (b /= ' ') = a : ' ' : insereEspacos' (n - 1) (b : ls)
        | otherwise  = a : insereEspacos' n (b : ls)

-- recebe um valor x (tamanho maior linha), um valor y 
-- (espaços para adicionar na string) e uma string e 
-- retorna a mesma string com tamanho x. 
insereEspacos'' :: Int -> Int -> String -> String
insereEspacos'' x y zs
        | (x > (length (insereEspacos' y zs))) 
                = insereEspacos'' x (x - (length (insereEspacos' y zs))) (insereEspacos' y zs)   
        | otherwise                           = insereEspacos' y zs














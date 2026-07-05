module Huffman where

import Data.Map as DM (Map, fromList, lookup, union, empty, insertWith, toList)
import Heap as H

{-
Integrantes grupo:
- Matias Marelli
- Tomas Federici
- Franco Nael Di Santis
-}

-- Bits y códigos

data Bit = Zero | One deriving (Eq, Show)

type Code = [Bit]

-- Árbol de codificación

data HTree = Leaf Char Int
           | Node HTree HTree Int
           deriving Show

weight :: HTree -> Int
weight (Leaf _ w)   = w
weight (Node _ _ w) = w

-- Diccionarios de frecuencias y códigos

type FreqMap = Map Char Int

type CodeMap = Map Char Code

-- Ejercicio 1

instance Eq HTree where
    (Leaf c1 n1) == (Leaf c2 n2) = (c1 == c2) && (n1 == n2)
    (Node left1 right1 n1) == (Node left2 right2 n2) = (left1 == left2) && (right1 == right2) && (n1 == n2) 
    _ == _ = False

instance Ord HTree where
    compare (Leaf _ n1) (Leaf _ n2) = compare n1 n2
    compare (Leaf _ n1) (Node _ _ n2) = compare n1 n2
    compare (Node _ _ n1) (Leaf _ n2) = compare n1 n2
    compare (Node _ _ n1) (Node _ _ n2) = compare n1 n2 

-- Ejercicio 2

buildFreqMap :: String -> FreqMap
buildFreqMap "" = fromList []
buildFreqMap (c:cs) = DM.insertWith (+) c 1 (buildFreqMap cs)

-- Ejercicio 3
 
buildHeap :: [(Char,Int)] -> H.Heap HTree
buildHeap [] = H.empty
buildHeap ((k,a):ms) = H.insert (Leaf k a) (buildHeap ms)

buildHTree' :: H.Heap HTree -> HTree
buildHTree' h = if H.isEmpty (H.deleteMin h) then (H.findMin h)
    else
        buildHTree' (H.insert (Node x' y' ((weight x') + (weight y'))) y) 
            where x = (H.deleteMin h)
                  y = (H.deleteMin x)
                  x' = H.findMin h
                  y' = H.findMin x

buildHTree :: FreqMap -> HTree
buildHTree m = buildHTree' (buildHeap (DM.toList m))

-- Ejercicio 4

buildCodeMap' :: HTree -> Code -> CodeMap
buildCodeMap' (Leaf c n) s = DM.insertWith (++) c s DM.empty
buildCodeMap' (Node l r w) s = DM.union (buildCodeMap' l (s++[Zero])) ((buildCodeMap' r (s++[One])))

buildCodeMap :: HTree -> CodeMap
buildCodeMap t = buildCodeMap' t []

-- Ejercicio 5

look :: Maybe Code -> Code
look Nothing = error "(!!!) Caracter no encontrado (!!!)"
look (Just a) = a

encode :: CodeMap -> String -> Code
encode m "" = []
encode m (c:cs) = (look (DM.lookup c m)) ++ (encode m cs)

-- Ejercicio 6

decode' :: HTree -> HTree -> Code -> String
decode' t (Leaf c _) [] = [c]
decode' t (Leaf c _) b = c:(decode' t t b)
decode' t (Node l r _) (b:bs) = if b == Zero then (decode' t l bs) else (decode' t r bs)

decode :: HTree -> Code -> String
decode t c = decode' t t c

-- Ejercicio 7

engFM :: FreqMap
engFM = fromList [
    ('a', 691),
    ('b', 126),
    ('c', 235),
    ('d', 360),
    ('e', 1074),
    ('f', 188),
    ('g', 170),
    ('h', 515),
    ('i', 589),
    ('j', 13),
    ('k', 65),
    ('l', 340),
    ('m', 203),
    ('n', 571),
    ('o', 635),
    ('p', 163),
    ('q', 8),
    ('r', 506),
    ('s', 535),
    ('t', 766),
    ('u', 233),
    ('v', 83),
    ('w', 200),
    ('x', 13),
    ('y', 167),
    ('z', 6),
    (' ', 1370),
    (',', 84),
    ('.', 89)
    ]

string1 :: String
string1 = "brother may i have some oats, no. i am starving, brother. as am i, brother. the tall skinny figure has thrown the oats at me. me, brother. i believe they have taken a liking to me. no brother, i have seen this before. i have observed many things. from the roaring beasts that the tall skinny figures crawl inside of to travel far beyond the horizon, to how the figure weeped when the other had fallen into a deep sleep. and from my experiences i have learned that they will give extra oats to one of us before taking them into the shed of no return.. they will do terrible things in that shed, brother. lies, that shed is where the chosen ones go to dine with our tall skinny gods. you are a fool brother and you shall be left behind in the mud with your backwards ideas. no, brother. you must believe me. share with me the oats and you shall not reach the desired girth for the tall skinny ones. they will spare your life, brother. aha. so this was all a plan to steal my oats. you truly are dispicable, brother. i will not trust your lies. brother, when they took me outside the reaches of the pointy fences, into the roaring beast and way over the horizon, i saw it. i was taken to a gathering of these tall skinny figures. they paraded me around, brother, and i saw the truth. i saw the tall skinny figures consuming our flesh. could not have been mistaken, brother. the smell of the flesh was surely one of us. they suspended the flesh above a fire and let it burn before consuming it. they did not just consume it either brother. they took pleasure from this their mouths curved a wicked smile and some even let out moans of satisfaction from consuming our flesh brother. the figures are consumers, brother. they are no different than the furry, red, demon that consumed and terrorized us and the feathered ones. your story amuses me, brother, but does not convince me. i shall have these oats myself and dine with the tall skinny gods. i am sorry for you, brother. your eyes cannot take the blinding light of the truth and you scurry back into the cave. i shall take care of your spawn once they consume you, brother, as they have consumed your lover, our father, our mother, and many more."

-- Bits usados para encriptar:
-- engFM: 9266
-- Codificacion con 5 bits por caracter: 10985

string2 :: String
string2 = "in a village of la mancha, the name of which i have no desire to call to mind, there lived not long since one of those gentlemen that keep a lance in the lancerack, an old buckler, a lean hack, and a greyhound for coursing. an olla of rather more beef than mutton, a salad on most nights, scraps on saturdays, lentils on fridays, and a pigeon or so extra on sundays, made away with threequarters of his income. the rest of it went in a doublet of fine cloth and velvet breeches and shoes to match for holidays, while on weekdays he made a brave figure in his best homespun. he had in his house a housekeeper past forty, a niece under twenty, and a lad for the field and marketplace, who used to saddle the hack as well as handle the billhook. the age of this gentleman of ours was bordering on fifty he was of a hardy habit, spare, gaunt featured, a very early riser and a great sportsman. they will have it his surname was quixada or quesada for here there is some difference of opinion among the authors who write on the subject, although from reasonable conjectures it seems plain that he was called quexana. this, however, is of but little importance to our tale it will be enough not to stray a hairs breadth from the truth in the telling of it."

-- Bits usados para encriptar:
-- engFM: 5260
-- Codificacion con 5 bits por caracter: 6250

string3 :: String
string3 = "petrichor v is a diverse world, with a wide array of environments that includes deserts, tundras, fungal jungles, and islands floating freely in the sky. beyond these areas, the planet also sports a hefty variety of otherworldly realms, ranging from outright hellish to dimensions beyond common understanding. it is orbited by its moon, where commencement is located. the fauna of the planet is as equally diverse, and yet neartotally united in their violent hostility towards the crew of the contact light. it was no sort of territorial dispute or desire to scare off the contact lights survivors the monstrous denizens of the planet relentlessly pursued them. there were some who attempted to document the native life, observing peaceful and gentle creatures who would turn savagely violent upon seeing a human. the signal echoes from rallypoint delta the closest thing to a human settlement describe the futility of their attempts to regroup in the wake of the planets wrathful inhabitants. by the time the ues safe travels responds to the contact lights distress call, it is unable to find any trace of surviving humans left on the planet, and the members of the safe travels crew find themselves met with the same hostility by the planets inhabitants."

-- Bits usados para encriptar:
-- engFM: 5268
-- Codificacion con 5 bits por caracter: 6280

string4 :: String
string4 = "distant flickerings, greener scenery this weathers bringing it all back again great adventures, faces in condensation im going outside to take it all in you say too late to start got your heart in a headlock i dont believe any of it you say too late to start with your heart in a headlock you know youre better than this wear a different pair, do something out of step throw a stranger an unexpected smile with big intention, still posted at your station always on about the day it should have flied you say too late to start got your heart in a headlock i dont believe any of it you say too late to start with your heart in a headlock you know youre better than this afraid to start how can you lose how can you lose got your heart in a headlock how can you lose how can you lose i dont believe any of it how can you lose you say too late to start with your heart in a headlock how can you lose how can you lose you know youre better than this how can you lose youve been walking, youve been hiding and you look half dead half the time monitoring you, like machines do youve still got it, im just keeping an eye youve been walking, youve been hiding and you look half dead half the time dont care monitoring you, like machines do will not youve still got it, im just keeping an eye the end you know youre better than this cant make a start got your heart in a headlock no, i dont believe any of it you say too late to start with your heart in a headlock you know youre better than this afraid to start how can you lost how can you lose got your heart in a headlock how can you lost how can you lose i dont believe any of it how can you lose you say too late to start with your heart in a headlock how can you lost how can you lose you know youre better than this how can you lose"

-- Bits usados para encriptar:
-- engFM: 7468
-- Codificacion con 5 bits por caracter: 8900

string5 :: String
string5 = "around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world around the world, around the world"

-- Bits usados para encriptar:
-- engFM: 8490
-- Codificacion con 5 bits por caracter: 9970

string6 :: String
string6 = "and one of them began to speak you, whoever you are, turn your face, as we go, and think if you ever saw me over there. i turned towards him, and looked hard he was blond and handsome, and of noble aspect, but a blow had split one of his eyebrows. when i had denied, humbly, ever seeing him, he said now look, and he showed me a wound at the top of his chest. then, smiling, he said i am manfred, grandson of the empress constance and i beg you, when you return, go to my lovely daughter, costanza, mother of james and frederick, sicilys and aragons pride, and tell her this truth, if things are said differently there. after my body had been pierced, by two mortal wounds, i rendered my spirit to him, who pardons, willingly. my sins were terrible, but infinite goodness has such a wide embrace it accepts all those who turn to it. if the bishop of cozenza, who was set on by clement to hound me, had read that page of gods rightly, the bones of my corpse would still be at the bridgehead, by benevento, under the guardianship of the heavy cairn. now, the rain bathes them, and the wind moves them, beyond the kingdom, along the river verde, where he carried them, a lume spento, with quenched tapers. but no one is so lost by the malediction, of that excommunication, that eternal love may not turn back to him, as long as hope is green. it is true that those who die, disobedient to the holy church, even though they repent at the end, must remain outside this bank for thirty times the duration of their life of insolence, unless such decree is shortened by the prayers of the good. see now, if you can give me delight, by telling my good costanza how you saw me, and also of my ban, since much benefit arises, here, through the prayers of those who are still over there."

-- Bits usados para encriptar:
-- engFM: 7545
-- Codificacion con 5 bits por caracter: 8875

string7 :: String
string7 = "we had already left him, when i saw two spirits frozen in a hole, so close together that the one head capped the other, and the uppermost set his teeth into the other, as bread is chewed, out of hunger, there where the back of the head joins the nape. tydeus gnawed the head of menalippus, no differently, out of rage, than this one the skull and other parts. i said o you, who, in such a brutal way, inflict the mark of your hatred, on him, whom you devour, tell me why on condition that, if you complain of him with reason, i, knowing who you are, and his offence, may repay you still in the world above, if the tongue i speak with is not withered."

-- Bits usados para encriptar:
-- engFM: 2753
-- Codificacion con 5 bits por caracter: 3250

string8 :: String
string8 = "then i saw many lights, living and victorious, make a central point of us, and a coronet, even sweeter in voice than shining in appearance, of themselves. so we sometimes see the moon, diana, latonas daughter, haloed when the air is so damp as to retain the rainbow thread that weaves her zone. there are many jewels so dear and lovely, in the courts of heaven i have returned from, that they cannot be moved from that region, and such was the song of these lights he who does not wing himself to fly up to them, may as well look for news of them from the speechless. when those burning suns, so singing, had circled round us three times, like stars near the fixed poles, they seemed as ladies do, not released from the dance, but resting, silent, listening, until they hear the notes again. and in one i heard a voice begin to say since the light of grace glows in you, at which true love is lit, and then by loving is multiplied, so as to lead you on that stair, that no one descends except to climb again, whoever denied you the wine from his glass, to quench your thirst, would be as little at liberty to do so, as water to refuse to flow to the sea. you wish to know with what flowers this garland is decorated that circles the lovely lady who strengthens your resolve for heaven. i was one of the lambs, of the sacred flock, that dominic leads on the path where there is good pasture, if we do not stray. he, who is nearest to me on the right, was my master and my brother he was albert of cologne, and i, thomas aquinas."

-- Bits usados para encriptar:
-- engFM: 6383
-- Codificacion con 5 bits por caracter: 7635

string9 :: String
string9 = "a turing machine is a mathematical model of computation describing an abstract machine that manipulates symbols on a strip of tape according to a table of rules. despite the models simplicity, it is capable of implementing any computer algorithm. the machine operates on an infinite memory tape divided into discrete cells, each of which can hold a single symbol drawn from a finite set of symbols called the alphabet of the machine. it has a head that, at any point in the machines operation, is positioned over one of these cells, and a state selected from a finite set of states. at each step of its operation, the head reads the symbol in its cell. then, based on the symbol and the machines own present state, the machine writes a symbol into the same cell, and moves the head one step to the left or the right, or halts the computation. the choice of which replacement symbol to write, which direction to move the head, and whether to halt is based on a finite table that specifies what to do for each combination of the current state and the symbol that is read. as with a real computer program, it is possible for a turing machine to go into an infinite loop which will never halt."

-- Bits usados para encriptar:
-- engFM: 4915
-- Codificacion con 5 bits por caracter: 5945

string10 :: String
string10 = "lorem ipsum is simply dummy text of the printing and typesetting industry. lorem ipsum has been the industrys standard dummy text ever since the s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. it has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. it was popularised in the s with the release of letraset sheets containing lorem ipsum passages, and more recently with desktop publishing software like aldus pagemaker including versions of lorem ipsum."

-- Bits usados para encriptar:
-- engFM: 2430
-- Codificacion con 5 bits por caracter: 2825

{-
    Conclusion: 
        Usar el diccionario de frecuencias de el idioma particular con el que se trabaja
        ayuda a ahorrar bits al codificar un texto a diferencia de una codificacion fija
        por caracter.
        Esto gracias a que los carcteres mas usuales en el idioma requieren una codificacion
        mas corta, mientras que utilizando 5 bits por caracter no se tiene en cuenta que
        un caracter puede ser mas frecuente que otro.
-}
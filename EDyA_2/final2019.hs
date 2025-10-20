type Name = String
data DirTree a = Dir Name [DirTree a] | File Name a deriving Show
type Path = [String]

names :: [DirTree a] -> [Name]
names [] = []
names (t@(Dir "/" tl):ts) = names ts ++ names' tl []

names' :: [DirTree a] -> [Name] -> [Name]
names' [] ns = ns
names' (t:ts) ns = names' ts (buildNames ns t)
  where buildNames xs (File n _) = (n:xs)
        buildNames xs (Dir n _) = (n:xs)

mkDir :: Path -> Name -> DirTree a -> DirTree a
mkDir p n d = mkdir ("/":p) n d

mkdir :: Path -> Name -> DirTree a -> DirTree a
mkdir ("/":ps) n t@(Dir "/" ts) = Dir "/" (mkdir' ps n ts)

mkdir' :: Path -> Name -> [DirTree a] -> [DirTree a]
mkdir' [] n ts = cyc n ts
mkdir' _ _ [] = []
mkdir' (p:ps) n (di@(Dir m d):ts) = if p == m then (Dir m (mkdir' ps n d)):ts
                                              else di:(mkdir' (p:ps) n ts)
mkdir' pa n (f:ts) = f:(mkdir' pa n ts)

cyc :: Name -> [DirTree a] -> [DirTree a]
cyc n [] = [Dir n []]
cyc n (f@(File m c):ts) = if m == n then f:ts
                                    else f:(cyc n ts)
cyc n (di@(Dir m d):ts) = if m == n then di:ts
                                    else di:(cyc n ts)

ls :: Path -> DirTree a -> [Name]
ls p t = ls' ("/":p) t

ls' :: Path -> DirTree a -> [Name]
ls' ("/":p) (Dir "/" ts) = ls'' p ts

ls'' :: Path -> [DirTree a] -> [Name]
ls'' [] ts = names [Dir "/" ts]
ls'' p [] = []
ls'' p ((File _ _):ts) = ls'' p ts
ls'' pa@(p:ps) ((Dir n d):ts) = if p == n then ls'' ps d
                                          else ls'' pa ts
# enveloppe_convexe_polygone

## EXPLICATION DU CODE:

## genererPointAleatoire(self, borneX, borneY):
de la classe Point2D génère un point 
aléatoire dans un espace bidimensionnel délimité par les bornes spécifiées borneX et borneY. 

## distanceEuclidienne(self, p):
calcule la distance euclidienne entre ce point et un autre point p 
dans l'espace bidimensionnel. 

## calculPente(self): 
Calcule la pente du vecteur en utilisant la formule de la différence des 
coordonnées y sur la différence des coordonnées x. 

## puissance(self, m): 
Calcule la puissance du point m par rapport à ce vecteur. Cette 
méthode utilise la formule de la puissance d'un point par rapport à un vecteur, qui est le carré du 
déterminant entre le vecteur et le vecteur formé par p0, p1 et m.

## genereNuagePointAlea(self, nbPoints, borneX, borneY): 
Génère un nombre spécifié de points 
aléatoires à l'intérieur des bornes spécifiées pour les coordonnées x et y. 

## copieNuagePoints(self): 
Crée une copie du nuage de points actuel dans un nouveau nuage. 

## ajoutePoint(self, p): 
Ajoute un point donné au nuage de points. 

## retirePoint(self, p): 
Retire un point donné du nuage de points s'il existe. 

## trierNuagePoints(self): 
les points du nuage selon les coordonnées y, puis les coordonnées x en 
cas d'égalité. 

## triPolaire(self): 
Trie les points du contour du polygone en utilisant l'algorithme du tri polaire. Il trouve 
d'abord le point le plus bas du polygone, puis trie les autres points selon leur angle polaire par rapport à 
ce point. 

## enveloppeConvexe:
prend une liste de points en entrée et retourne l'enveloppe convexe 
de ces points. 

### Fonctionnement : 
- Vérifie si le nombre de points est inférieur à 3, auquel cas il n'est pas possible de former une 
enveloppe convexe, donc affiche un message d'erreur et retourne une liste vide. 
- Trouve le point le plus bas parmi tous les points. 
- Trie les points en fonction de leur angle polaire par rapport au point le plus bas, en utilisant la 
fonction math.atan2 pour calculer l'angle. 
- Initialise l'enveloppe convexe avec les deux premiers points triés. 
- Parcourt les points restants et les ajoute à l'enveloppe convexe, en vérifiant que l'angle formé par les 
derniers deux points de l'enveloppe avec le point actuel est orienté dans le sens trigonométrique. Si 
ce n'est pas le cas, les derniers points sont retirés de l'enveloppe jusqu'à ce que cela soit vrai. 
- Retourne l'enveloppe convexe ainsi formée. 

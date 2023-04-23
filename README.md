# lcd
Ce code est destiné à être utilisé dans un projet de jeu vidéo. Les fonctions et les classes sont conçues pour être étendues et modifiées en fonction des besoins du projet.

La classe "Parametre" contient plusieurs variables qui définissent les limites de l'écran, la taille de l'écran, les boutons du joueur, etc. Elle contient également des fonctions pour initialiser les éléments graphiques du jeu et pour afficher ou cacher les éléments.

La classe "Position" hérite de "Parametre" et ajoute des variables pour la taille de l'écran, la vitesse de défilement et la position des différents éléments (héros, ennemis, obstacles, etc.). Elle contient également des fonctions pour générer la position initiale des éléments, déplacer les éléments et détecter les collisions.

La classe "Hero" hérite de "Parametre" et ajoute des variables pour la vitesse et les mouvements du héros, ainsi que pour les différents objets qu'il peut ramasser. Elle contient également des fonctions pour déplacer le héros, sauter et interagir avec les objets.

La classe "Mechant" hérite de "Parametre" et ajoute des variables pour les ennemis, comme leur vitesse, leur saut et leur feu. Elle contient également des fonctions pour créer et déplacer les ennemis.



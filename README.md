# Jeu arduino sur ecran Lcd
Ce code est destiné à être utilisé dans un projet de jeu vidéo. Les fonctions et les classes sont conçues pour être étendues et modifiées en fonction des besoins du projet.

La classe "Parametre" contient plusieurs variables qui définissent les limites de l'écran, la taille de l'écran, les boutons du joueur, etc. Elle contient également des fonctions pour initialiser les éléments graphiques du jeu et pour afficher ou cacher les éléments.

La classe "Position" hérite de "Parametre" et ajoute des variables pour la taille de l'écran, la vitesse de défilement et la position des différents éléments (héros, ennemis, obstacles, etc.). Elle contient également des fonctions pour générer la position initiale des éléments, déplacer les éléments et détecter les collisions.

La classe "Hero" hérite de "Parametre" et ajoute des variables pour la vitesse et les mouvements du héros, ainsi que pour les différents objets qu'il peut ramasser. Elle contient également des fonctions pour déplacer le héros, sauter et interagir avec les objets.

La classe "Mechant" hérite de "Parametre" et ajoute des variables pour les ennemis, comme leur vitesse, leur saut et leur feu. Elle contient également des fonctions pour créer et déplacer les ennemis.

##Parametre 
Le code que vous avez fourni est un ensemble de méthodes qui définissent différents comportements pour les équipements connectés à votre arduino, tels qu'un écran LCD et un joystick.

La classe "Parametre" définit différentes variables pour ces équipements, comme la plage de lecture pour les entrées analogiques, la taille de l'écran LCD, les broches utilisées pour le joystick, etc.

La méthode "initialisation" est utilisée pour initialiser les équipements connectés à l'arduino, comme l'écran LCD, ainsi que pour définir certaines variables comme le temps écoulé depuis le démarrage de l'arduino.

Les méthodes "display" et "notDisplay" sont utilisées pour afficher ou masquer différents symboles sur l'écran LCD.

Les méthodes suivantes sont utilisées pour détecter les mouvements du joystick : "boutonLeft", "boutonRight", "boutonTop", "boutonBottom" et "boutonMonostable". La méthode "boutonShortPress" est utilisée pour détecter un appui court sur le bouton du joystick.

Enfin, les méthodes "specialMoveLeft", "specialMoveRight", "specialMoveTop" et "specialMoveBottom" sont utilisées pour détecter des mouvements spéciaux du joystick, qui nécessitent de maintenir le bouton enfoncé en même temps.

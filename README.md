# Jeu arduino sur ecran Lcd
Ce code est destiné à être utilisé dans un projet de jeu vidéo. Les fonctions et les classes sont conçues pour être étendues et modifiées en fonction des besoins du projet.

La classe "Parametre" contient plusieurs variables qui définissent les limites de l'écran, la taille de l'écran, les boutons du joueur, etc. Elle contient également des fonctions pour initialiser les éléments graphiques du jeu et pour afficher ou cacher les éléments.

La classe "Position" hérite de "Parametre" et ajoute des variables pour la taille de l'écran, la vitesse de défilement et la position des différents éléments (héros, ennemis, obstacles, etc.). Elle contient également des fonctions pour générer la position initiale des éléments, déplacer les éléments et détecter les collisions.

La classe "Hero" hérite de "Parametre" et ajoute des variables pour la vitesse et les mouvements du héros, ainsi que pour les différents objets qu'il peut ramasser. Elle contient également des fonctions pour déplacer le héros, sauter et interagir avec les objets.

La classe "Mechant" hérite de "Parametre" et ajoute des variables pour les ennemis, comme leur vitesse, leur saut et leur feu. Elle contient également des fonctions pour créer et déplacer les ennemis.

## Parametre 
Le code que vous avez fourni est un ensemble de méthodes qui définissent différents comportements pour les équipements connectés à votre arduino, tels qu'un écran LCD et un joystick.

La classe "Parametre" définit différentes variables pour ces équipements, comme la plage de lecture pour les entrées analogiques, la taille de l'écran LCD, les broches utilisées pour le joystick, etc.

* La méthode "initialisation" est utilisée pour initialiser les équipements connectés à l'arduino, comme l'écran LCD, ainsi que pour définir certaines variables comme le temps écoulé depuis le démarrage de l'arduino.

* Les méthodes "display" et "notDisplay" sont utilisées pour afficher ou masquer différents symboles sur l'écran LCD.

* Les méthodes suivantes sont utilisées pour détecter les mouvements du joystick : "boutonLeft", "boutonRight", "boutonTop", "boutonBottom" et "boutonMonostable". La méthode "boutonShortPress" est utilisée pour détecter un appui court sur le bouton du joystick.

* Enfin, les méthodes "specialMoveLeft", "specialMoveRight", "specialMoveTop" et "specialMoveBottom" sont utilisées pour détecter des mouvements spéciaux du joystick, qui nécessitent de maintenir le bouton enfoncé en même temps.

## Position
La classe "Position" contient des fonctions pour initialiser les paramètres de position, générer des positions aléatoires pour chaque type de caractère, afficher ces caractères sur l'écran LCD, définir le type et le mode d'affichage et supprimer les positions de tous les caractères.

* La fonction "generatePosition" initialise un tableau à trois dimensions appelé "ary" qui contient la position de chaque caractère. Chaque élément du tableau est défini par trois coordonnées: la position horizontale, la position verticale et un paramètre qui indique si le caractère est affiché ou non.

* La fonction "typeZelda" génère des positions aléatoires pour chaque type de caractère, en vérifiant que chaque caractère n'entre pas en collision avec un autre. Les positions des héros et des portes sont définies aux extrémités gauche et droite de l'écran respectivement, tandis que les positions des autres caractères sont générées de manière aléatoire sur l'écran.

* La fonction "compareAll" est utilisée pour vérifier si une nouvelle position est en collision avec une position existante de tous les caractères déjà affichés sur l'écran.

La classe "Position" fournit également des fonctions pour définir la taille de l'écran LCD, la vitesse de défilement et la suppression de toutes les positions de caractères.

## hero 
Le constructeur Hero() : initialise les attributs de l'objet Hero, tels que la position, la vitesse de déplacement, le nombre de vies, de monstres, de clés, d'arcs, de pièces, de niveaux, etc.

* Les getters et setters : permettent d'accéder aux attributs et de les modifier. Par exemple, getFire() renvoie la valeur de l'attribut fire.

* Les méthodes de déplacement : permettent de déplacer le personnage vers la gauche, la droite, le haut ou le bas en fonction des boutons appuyés. Les méthodes goLeft(), goRight(), goTop() et goBottom() vérifient si le personnage peut se déplacer dans la direction souhaitée, puis mettent à jour sa position dans l'array.

 * Les méthodes de mouvement : permettent de faire bouger le personnage à gauche et à droite en continu en fonction du temps écoulé depuis le dernier mouvement. La méthode moveLeftRight() fait avancer le personnage dans les deux directions, tandis que la méthode move() permet de sauter et de se déplacer à gauche ou à droite.

* Les méthodes de combat : permettent d'attaquer et de tuer les ennemis. La méthode shoot() permet de tirer une flèche, la méthode kill() tue l'ennemi et la méthode death() gère la mort du personnage.

* Les méthodes d'interaction : permettent d'interagir avec les objets du jeu, tels que les portes, les clés, les pièces, les équations, etc. Par exemple, la méthode collectCoin() ajoute une pièce à l'inventaire du personnage.

 * Les méthodes d'affichage : permettent d'afficher le personnage et les objets à l'écran en fonction de leur position dans l'array. La méthode display() affiche l'objet à la nouvelle position, tandis que la méthode notDisplay() efface l'objet de l'ancienne position.

En résumé, la classe Hero représente le personnage principal du jeu, qui peut se déplacer, combattre, interagir avec les objets et collecter des ressources.

## Mechant

* Constructeur : il y a deux constructeurs différents qui initialisent différents attributs du personnage "mechant", tels que sa vitesse, sa position, son nombre de vies, etc.

* Méthodes "get" et "set" : ces méthodes permettent de récupérer ou de modifier certaines valeurs d'attributs du personnage "mechant". Par exemple, la méthode "getFire()" permet de récupérer la valeur de l'attribut "fire" qui indique si le personnage est en train de tirer ou non.

* Méthodes de vérification de déplacement : il y a quatre méthodes différentes ("noElementLeft()", "noElementRight()", "noElementTop()", "noElementBottom()") qui vérifient si le personnage peut se déplacer dans une direction donnée. Elles retournent "true" si le personnage peut se déplacer et "false" sinon.

* Méthodes de déplacement : il y a deux méthodes ("goLeft()" et "goRight()") qui permettent de faire déplacer le personnage vers la gauche ou la droite, respectivement. Elles vérifient d'abord si le personnage peut se déplacer dans cette direction en utilisant les méthodes de vérification de déplacement. Si c'est le cas, le personnage est déplacé vers la nouvelle position. Sinon, le personnage se déplace de manière aléatoire en utilisant la méthode "goRandom()".

* Méthode de tir : la méthode "shoot()" permet de faire tirer le personnage. Elle met à jour l'attribut "fire" à "true" pour indiquer que le personnage est en train de tirer.

* Méthode de perte de vie : la méthode "loseLife()" permet de faire perdre une vie au personnage. Elle met à jour l'attribut "numberOfLife" en décrémentant sa valeur de 1.

* Autres méthodes : il y a quelques autres méthodes qui ne sont pas mentionnées ici, comme "goRandom()" qui permet de faire déplacer le personnage de manière aléatoire, ou "setFireFalse()" qui permet de remettre l'attribut "fire" à "false".

## shot 

Le code fourni est un ensemble de classes pour un jeu. La classe "Shot" représente une balle qui peut être tirée par un héros pour attaquer un méchant. Les classes "Bullet", "ArrowBullet", "EqualBullet" et "MinusBullet" héritent de la classe "Shot" et représentent différents types de balles.

* La méthode "element" de la classe "Bullet" permet de déterminer quel caractère a été touché par la balle en examinant les positions actuelles de la balle et des caractères activés dans un tableau de positions.

* La méthode "canProgress" de la classe "Bullet" vérifie si la balle peut continuer à se déplacer en examinant les limites d'écran et si elle a touché un certain nombre de caractères.

* La méthode "displayStar" de la classe "Bullet" affiche un caractère blanc à la position de la balle si elle touche un caractère étoile.

* La méthode "bulletReachHero" de la classe "Shot" déclenche une perte de vie pour le héros touché par la balle et réinitialise la position et l'écran.

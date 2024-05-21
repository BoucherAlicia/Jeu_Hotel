# Projet Jeu Hôtel

## Auteurs
- Alicia BOUCHER
- Charbel EL MORR

## Bibliothèques, Frameworks et Outils Utilisés
- [SDL2](https://www.libsdl.org/download-2.0.php) - Simple DirectMedia Layer
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) - Extension de SDL2 pour le rendu de texte avec des polices TrueType
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/) - Extension de SDL2 pour le chargement d'images


## Instructions de Compilation

### Pré-requis
1. Installer les bibliothèques SDL2, SDL2_ttf, et SDL2_image.
   - Sous Linux, vous pouvez les installer via le gestionnaire de paquets :
     
    sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev
    
   - Sous Windows, téléchargez les bibliothèques depuis leurs sites officiels et suivez les instructions d'installation.

### Compilation
1. Cloner le dépôt du projet :
   
   git clone https://gitlabsu.sorbonne-universite.fr/Alicia.Boucher/jeu-hotel-boucher-elmorr.git

   cd jeu-hotel-boucher-elmorr

2. Compiler le projet :

    Si vous utilisez un simple makefile : 
        make
    Si vous utilisez CMake :
        mkdir build
        cd build
        cmake ..
        make
3. Exécuter le projet :

    ./hotel

### Exécution

1. But du jeu

    Le but du jeu est de devenir le joueur le plus riche en construisant et en gérant des hôtels. Les joueurs doivent se déplacer sur le plateau, acheter des propriétés et construire des hôtels. Ils peuvent également acheter des entrées pour leurs hôtels afin d'augmenter leurs revenus.

2. Comment jouer
    
    2.1. Déplacement :
        Chaque joueur lance un dé pour déterminer combien de cases il doit avancer.
        Deux joueurs ne peuvent pas se trouver sur la même case. 
        Si vous arrivez sur une case où se trouve un autre joueur, avancez jusqu’à la prochaine case libre.
    
    2.2. Les propriétés :
        Si le joueur atterrit sur une propriété non achetée, il peut choisir de l'acheter.
        Si le joueur atterrit sur une propriété déjà possédée, il doit payer un loyer au propriétaire.

    2.3. Construire des hôtels :
        Les joueurs peuvent construire des hôtels sur leurs propriétés.
        Les hôtels augmentent les revenus des joueurs lorsqu'un autre joueur atterrit sur leur case.
        Des hôtels de luxe peuvent être achetés lors du passage du joueur su un terrain lui appartenant. 
        Cet hôtel de luxe n'augmente pas le loyer mais permet l'achat d'entrées.
    
    2.4. Acheter des entrées :
        Lorsqu'un joueur est entre les cases 27 et 30, il peut choisir d'acheter des entrées pour ses hôtels.
        Les entrées coûtent 500 euros et augmentent les revenus des hôtels.
    
    2.5. Banque :
        Lorsqu'un joueur atterrit sur la case de la banque (case 12), il reçoit 1000 euros.

    2.6. Dé spécial :
        Lorsque le joueur veut acheter un hôtel il doit lancer le dé spécial. 
        Si le dé retourne "rouge", alors le joueur ne peut pas acheter l'hôtel.
        Si le dé retourne "vert", alors le joueur peut acheter l'hôtel.
        Si le dé retourne "H (gratuit)", alors le joueur a gratuitement l'hôtel.
        Si le dé retourne "2D (double)", alors le joueur doit payer deux fois le prix de l'achat de l'hôtel.

    2.7. Rejouer le dé :
        Si vous obtenez un « 6 » en lançant le dé lors de votre déplacement, vous devrez rejouer immédiatement après avoir effectué votre tour normalement (y compris le paiement éventuel d’un loyer).

    2.8. Fin de la partie :
        Lorsqu'un joueur n'a plus d'argent, il est éliminé du jeu.

3. Commandes

    - Lancer le dé : Cliquez sur le bouton de lancer le dé pour avancer sur le plateau.
    - Achat terrain : Cliquez sur le bouton de confirmation pour acheter des terrains lorsque vous y êtes invité.
    - Achat hôtel(s) : Sélectionnez l'option de construction lorsque vous possédez déjà le terrain.
    - Achat entrée(s): Cliquez sur le bouton de confirmation lorsque vous êtes éligible pour acheter des entrées pour vos hôtels.
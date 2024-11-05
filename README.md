# Quixo (Glisséo)
## Contexte

Une **entreprise de jeu de société** est en train de préparer la sortie future d’un **nouveau jeu**, celui-ci s’appelle **Quixo**. Cependant, l’entreprise ne sait pas si ce jeu va plaire et elle ne veut pas **décevoir sa clientèle** et veut proposer un jeu le plus qualitatif et adapté aux demandes, aux envies des clients avec l’objectif que ce jeu devienne un classique dans le monde des jeux de société au même niveau que les monopoly, puissance 4…. C’est pour cela, que l’entreprise décide de développer d’abord ce jeu dans une version en ligne  puis de créer un **site web avec intégré**, le jeu, les explications, et un formulaire de contact et de recommandation permettant aux visiteurs de donner leur avis afin d’améliorer le jeu après une partie.

## Description du projet
**Quixo (Glisséo)** est une implémentation du jeu de stratégie Quixo en langage C. Le jeu se déroule sur un plateau 5x5 et consiste à déplacer des cubes pour aligner cinq symboles identiques. Cette version est jouable en mode console, offrant une interface simple et intuitive.

## Table des matières
- [Règles du jeu](#règles-du-jeu)
- [Compilation](#compilation)
- [Exécution](#exécution)
- [Fonctionnalités](#fonctionnalités)
- [Exemple d'utilisation](#exemple-dutilisation)
- [Contributions](#contributions)
- [Licence](#licence)

## Règles du jeu
1. **Plateau de jeu** : Le plateau est composé de 25 cases formant un carré de 5x5, chacune contenant un cube.
2. **Objectif** : Aligner cinq symboles identiques (X ou O) horizontalement, verticalement ou en diagonale.
3. **Déroulement du jeu** :
   - Les joueurs choisissent alternativement un cube en bordure du plateau, le retirent, le tournent (pour afficher leur symbole), puis le replacent à l'une des extrémités de la rangée ou colonne d'où il a été pris.
   - Les autres cubes de la ligne ou colonne se décalent pour combler l'espace laissé par le cube retiré.
4. **Fin de partie** :
   - Un joueur gagne lorsqu'il aligne cinq de ses symboles.
   - La partie peut finir en match nul si toutes les cases sont occupées sans qu'aucun joueur n'ait aligné cinq symboles.

## Compilation
Pour compiler le projet, exécutez le script suivant :
```bash

build.cmd
```

## Exécution
Exécutez le programme `.\bin\main.exe`

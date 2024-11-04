# Quixo (Glisséo)

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

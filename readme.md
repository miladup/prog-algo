# Workshop Programmation & Algorithmique – Traitement d’images

Ce workshop de programmation en C++ utilise la librairie **SIL** pour manipuler des images pixel par pixel.  
L’objectif est de découvrir les bases du **traitement d’image algorithmique** : modification de couleurs, filtres, transformations géométriques et génération d’images.

## Mettre en vert

**Description :**  
Supprime les composantes rouge et bleue de l’image pour ne conserver que le vert.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/pouet.png)

## Échanger rouge et bleu

**Description :**  
Inverse les canaux rouge et bleu de chaque pixel.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/logo_swap.png)

## Noir et blanc

**Description :**  
Convertit l’image en niveaux de gris à partir d’une moyenne pondérée des couleurs.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/noir_blanc.png)

## Négatif

**Description :**  
Inverse les couleurs de l’image (effet négatif).

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/negatif.png)

## Dégradé horizontal (gris)

**Description :**  
Crée une image avec un dégradé horizontal du noir vers le blanc.

**Création :**  
![Dégradé](output/degrade.png)

## Dégradé de couleur

**Description :**  
Crée un dégradé horizontal allant du bleu vers le rouge.

**Création :**  
![Dégradé couleur](output/degrade_couleur.png)

## Miroir horizontal

**Description :**  
Retourne l’image horizontalement.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/logo_miroir.png)

## Bruit aléatoire

**Description :**  
Ajoute du bruit aléatoire sur certains pixels de l’image.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/logo_bruit.png)

## Rotation 90° à droite

**Description :**  
Fait pivoter l’image de 90 degrés dans le sens horaire.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/logo_90deg.png)

## Décalage RGB

**Description :**  
Décale les canaux rouge et bleu horizontalement pour créer un effet chromatique.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/logo_rgb_split.png)

## Cercle plein

**Description :**  
Dessine un cercle blanc plein au centre d’une image noire.

**Création :**  
![Cercle](output/cercle.png)

## Cercle avec contour

**Description :**  
Dessine uniquement le contour d’un cercle avec une épaisseur donnée.

**Création :**  
![Cercle contour](output/cercle_contour.png)

## Animation d’un cercle

**Description :**  
Génère une animation où un cercle se déplace de gauche à droite sur plusieurs frames.

**Création :**  
Les images sont sauvegardées sous la forme `frame_000.png` à `frame_059.png`.

## Rosace à 6 cercles

**Description :**  
Dessine une rosace composée de 6 cercles autour d’un cercle central.

**Création :**  
![Rosace](output/rosace_6.png)

## Mosaïque simple

**Description :**  
Répète l’image source pour remplir une image plus grande.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/mosaique.png)

## Mosaïque miroir

**Description :**  
Crée une mosaïque en alternant des images retournées horizontalement et verticalement.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/mosaique_miroir.png)

## Glitch

**Description :**  
Échange aléatoirement des rectangles de pixels pour créer un effet glitch.

**Avant :**  
![Avant](images/logo.png)

**Après :**  
![Après](output/logo_glitch.png)

## Conclusion

Ce workshop m’a permis de comprendre :
- la manipulation d’images pixel par pixel
- l’utilisation de boucles et de mathématiques simples en traitement d’image
- la génération d’images et d’animations
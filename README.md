# Projet-QT
Projet C++ de L2 : Création d'application de transactions

# Auteurs : 

- Marc-Eli CROAIN </br>
- Gauthier ROUSSEL </br>
- Antoine CAILLAUD </br>

# Technologies :

- C++ </br>
- QT  </br>
- SQLITE </br>


# Description :

 . Il s'agit d'une application servant à gérer des Transactions entre des Fournisseurs et des Clients. 

- Il ya une nomenclature déterminant l’élément sur lequel une transaction sera opérée (par exemple l’article à créditer ou à débiter). Elle est structurée en arborescence ou les premiers élément (nœuds racines) contiennent les nœuds feuilles du premier niveau, qui elles contiennent les nœuds feuilles du second niveau etc..
- Il existe 3 types de transactions :  </br>
 . Dotation : Créditer le compte d'un utilisateur </br>
 . Dépense : Débiter le compte d'un utilisateur </br>
 . Transfert de fonds : Transaction entre deux comptes (Donc implique une Dotation et une Dépense) </br>
 
- On doit pouvoir enregistrer les Transactions pour chaque utilisateur, et retrouver la liste de ces dernières. </br>
- On doit également pouvoir donner une note et un avis sur un fournisseur.  </br>
- Une partie admin sera dédiée à l'ajout, suppression et modifications d'éléments existant (CRUD).  </br>
- On aimerait pouvoir imprimer un Compte rendu pour chaque transaction.  </br>

# Autre :

Le fichier "CR.pdf" peut être consulté pour un résumé rapide du projet.




# bucketing-superkmers

C++ implementation of a superkmer bucketing tool for an intern test from https://github.com/yoann-dufresne/buckettingtest

# Utilisation 

## Compilation

Pour compiler une première fois veuillez utiliser la commande :
```
make
```

Pour nettoyer le dossier et supprimer tous les fichiers compilés :
```
make clean
```

## Execution

Pour utiliser le programme voici la syntaxe à suivre :
```
./main file_in rep_out k m
```
Avec : 
- file_in : fichier au format FASTA
- rep_out : chemin vers un répertoire où seront stockées les sorties
- k : un entier inférieur ou égal à 31
- m : un entier inférieur à k représentant la taille des minimiseurs

Par exemple : 
```
./main ../fastafiles/sequence.fasta ../fastafiles/ 31 20
# ou
./main data/ecoli.fasta data/ecoli_out/ 31 13
```

## Résultat

En sortie, un fichier `superkmer_buckets.txt` dans le répertoire donné en paramètre, contenant un superkmer par ligne.
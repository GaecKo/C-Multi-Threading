# C-Multi-Threading

## Lancement du code
Pour lancer le code, il faut simplement entrer `make`. Les trois fichiers `c` seront compilés en exécutables. Il suffit alors de les lancer avec `./c/filename` (les exécutables sont dans le dossier `c/`, on peut donc aussi faire `cd c/` puis `./filename`). 

## Organisation des fichiers
```
|- Makefile     # make command
|- tester.sh    # data maker
|- analyser.py  # graph maker
|- README.md    # project explainer
|- *.pdf        # project instruction
|
|c/  # c folder (programs)
    |- executable (×3 after `make`)
    |- philosophe.c
    |- prod_conso.c
    |- lect_writer.h
    |- includes/  # headers
        |- philosophe.h
        |- prod_conso.h
        |- lect_writer.h
| 
|data/  # csv folder (retrieved data)
    |- t2.csv
    |- t4.csv
    |- t8.csv
    |- t16.csv
    |- t32.csv
    |- t64.csv
|
```


## Tâches
#### (1.1) Problème des philosophes
- Le nombre de philosophes N est un paramètre obtenu à partir de la ligne de commande ;
- Chaque philosophe effectue 10,000,000 cycles penser/manger ;
- On n’utilise pas d’attente dans les phases manger et penser (ces actions sont immédiates) pour mettre en avant le coût des opérations de synchronisation.

#### (1.2) Problème des producteurs-consommateurs
- Le nombre de threads consommateur et le nombre de threads producteurs sont deux paramètres obtenus à partir de la ligne de commande ;

- Le buffer est un tableau partagé de 8 places, contenant des entiers (`int`) : 
    - Une donnée produite ne doit jamais ‘écraser’ une donnée non consommée !
    - On doit pouvoir produire des entiers sur l’ensemble de la plage `MIN_INT` à `MAX_INT`.

- Entre chaque consommation ou production, un thread « simule » un traitement utilisant de la ressource CPU, en utilisant : `for (int i=0; i<10000; i++);`
- Le nombre d’éléments produits (et donc consommé) est toujours de 8192.

#### (1.3) Problème des lecteurs écrivains
- Le nombre de threads écrivains et le nombre de threads lecteurs sont deux paramètres obtenus à partir de la ligne de commande ;
- Un écrivain ou un lecteur « simule » un accès en écriture ou en lecture à la base de données avec la commande donnée ci-dessus, il n’y a pas d’attente entre deux tentatives d’accès ;
- Le(s) écrivain(s) effectue(nt) 640 écritures et le(s) lecteur(s) effectue(nt) 2560 lectures.

#### (1.4) Écrire un script d’évaluation des performances
- Sur le modèle du précédent TD, mesurer la performance de chacun des trois programmes et la sauver dans des fichiers `.csv` en faisant attention à :
    - Désactiver toute sortie sur `STDOUT` (car cela diminuerait les performances) ;
    - Prendre 5 mesures pour chaque configuration avec les nombres de threads TOTAUX suivants: `[2, 4, 8, 16, 32, 64]`
        - Pour les problèmes avec deux types distincts de threads, vous devez donc séparer ce nombre en 2 ensembles de threads de taille égale.


#### (1.5) Représenter graphiquement les résultats

- En utilisant matplotlib et un script python, représenter graphiquement le temps d’exécution en fonction du nombre de threads, en respectant les consignes suivantes :
    - Les axes x et y doivent avoir des titres clairs ;
    - Chaque mesure doit présenter la moyenne et l’écart type3 ;
    - L’axe des y doit systématiquement commencer à 0.


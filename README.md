# C-Multi-Threading
Bienvenue sur notre projet P1. Voici quelques petites informations utiles en plus de ce qui est repris dans notre rapport. 


## Lancement du code
Pour lancer le code, il faut simplement entrer `make`. Les différents fichiers `c` seront compilés en exécutables. Il suffit alors de les lancer avec `./executables/filename`. 

## Lancement des tests
Afin de lancer les tests, il faut utiliser la commande `make test`. Celle-ci compilera automatiquement les fichiers et lancera les tests. Le résultat de ces tests seront enregistrés dans les fichiers `.csv` dans `data/`. 

Vous pouvez aussi lancer directement le fichier `expermients.sh`, mais assurez vous d'avoir compilé les fichiers au préalable. 

> **Notes**: Les résultats actuels dans `data/` sont ceux de la machine INGInious. Relancer les tests écraiserait donc ceux-ci et modifierait les graphes. 

## Lancement des graphes
Une fois les tests finis, ou si vous souhaitez afficher les résultats de la machine INGInious, il vous suffit de lancer les fichiers `analyser.py` et `analyser2.py`. 
* `analyser.py` contient des `box plot`, donc 4 graphes avec toutes les données dessus
* `analyser2.py` contient des `bar plot` et des `error bar` (8 graphes en tout), permettant plus facilement la comparaison de temps. 


## Organisation des fichiers
```
|- Makefile         # make command
|- experiments.sh   # data maker
|- analyser.py      # graph maker
|- analyser2.py     # graph maker
|- README.md        # project explainer
|- *.pdf            # project instruction
|
|c/             # c folder (programs)

    |- sem.c
    |- philosophe.c
    |- prod_conso.c
    |- lect_writer.c
    |- philosophe2.c    # using header/sem.h
    |- prod_conso2.c    # using header/sem.h
    |- lect_writer2.c   #using header/sem.h
    |- includes/        # headers
        |- sem.h
        |- philosophe.h
        |- prod_conso.h
        |- lect_writer.h
    |- build/
        |- sem.o        # compiled version of sem, when make is runned
| 
|data/          # csv folder (retrieved data)
    |- philosophe.csv
    |- prod_conso.csv
    |- lect_writer.csv
    |- philosophe2.csv
    |- prod_conso2.csv
    |- lect_writer2.csv
    |- test_and_set.csv
    |- test_and_test_and_set.csv
|
|executables/   # completed when make run is runned
    |- philosophe
    |- ...
|
```



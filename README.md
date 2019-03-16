# IN403-Rooting-Table

J'ai refait tout le graph.c/graphe.h et ajouté error.h.
Le programme quitte si il y a un problème d'allocation en affichant l'erreur (même si c'est un peu dégeu, au moins on ne se casse pas la tête).
Il y a des macros dans graph.h pour simplifier le code.
Le fichier network.c et network.h permettera de créer le réseau selon les conditions demandées.
make debug permet de run avec valgrind
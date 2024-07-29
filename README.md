Here we go :

Référence bash --posix

23/07

0 - Garbage Collector

- création d'un garbage_collector.c qui devra réunir toutes les fonctions de free.
---> Peut-être intéressant de faire un initialisation.c aussi.

I - GIT 

- 2 git branch Yoann/Amaury + Main

Dans l'ordre :
1 - Git add / commit / push sur sa branche perso
2 - git checkout main
3 - git pull
4 - git merge Amaury où Yoann
5 - Résoudre les conflits si il y en a.
6 - git add / commit / push sur branche main.
7 - git checkout sur sa branche perso
8 - git merge main

AND WE GOOD.

II - Display  

- display "minishell:"					OK
- readline?						OK
- Gérer ^c / ^d / ^\ et entrée				OK
--> ^d : display "exit" + quitte le programme. 	OK
--> ^c : display "^C\n"				OK
--> ^\ : Ne fait rien du tout. 				OK
--> entrée : \n + ré-affiche le prompt.			OK

III - Gestion des here_docs

- Création d'un fichier here_doc.c pour toutes les fonctions relatives aux here_docs.
- Réutilisation de lil_gnl pour reproduire le comportement du here_doc. 
--> Peut-être qu'on utilisera readline à la place. À vérifier. 
- Réutilisation de la fonction here_doc error.


FIN DE JOURNÉE 23/07.

25/07

I - Organisation des structs de data + vecteurs + enum

26/07

I - Tentative d'exec d'here_doc dans minishell.

a - Je récupère bien les données dans le vecteur. 	OK
b - Je display correctement "here_doc>". 			OK

27/07

I - Here_doc dans Minishell fonctionne. Pourquoi? Magie noire.

a - Gérer les signaux dans le here_doc
b - Faire la fonction qui adapte en fonction du limiter.
c - Unlink le here_doc.tmp à la fin. (Dans garbage collector?)
d - Gérer les name.tmp si plusieurs here_doc.


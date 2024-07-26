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

- 1 enum e_redir dédiée aux redirections, qui permet de rendre lisible les redirections des cmd.
- 1 structure globale : Qui contient toutes les data, qu'on peut transporter tout au long du programme pour avoir accès à toutes les data.
- 1 vecteur t_vector : Qui contient un pointeur sur la struct t_node, ainsi que size/capacity pour l'allocation dynamique de mémoire.
- 1 structure t_node : Qui contient un pointeur sur un vecteur2 v_redir et un vecteur2 v_cmd
- 1 "sous" vecteur t_vector2  : Qui contient un char *data (Une cmd), size/capacity.  

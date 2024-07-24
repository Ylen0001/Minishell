Here we go :

Référence bash --posix

23/07

0 - Garbage Collector

- création d'un garbage_collector.c qui devra réunir toutes les fonctions de free.
---> Peut-être intéressant de faire un initialisation.c aussi.

I - GIT 

- 2 git branch Yoann/Amaury + Main

Si besoin de push sur la main : git checkout main + git merge Yoann où Amaury
Si besoin de récupérer le merge sur branche annexe : git checkout Yoann + git merge main

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

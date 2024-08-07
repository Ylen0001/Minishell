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

III - Architecture des structs

1 - Une structure globale data
---> Un vecteur v_path
     ----> Un tableau de vecteur v_parsed
	 	   ----> Un char **cmd + char *redir + int type

Donc si je veux accéder à la cmd[0] de l'input 1

data->v_path.v_parsed[0].cmd->data[0] = Première cmd + options + arguments (ls -lr)
data->v_path.v_parsed[0].cmd->data[1] = Deuxième cmd etc...
data->v_path.parsed[0].cmd->size = size du nbr d'args de l'input 1.
data->v_path.parsed[0].type.redir_type[0] = Première redir


IV - Architecture de l'exec

1 - Si une seule cmd NON BUILT-IN
---> On exec dans le parent.
1b - Si une seule cmd BUILT-IN
---> On fork pour exec dans l'enfant.
2 - Si plusieurs cmds
---> On fork du nombre de cmd. Même si il y a des built-in

FORK CASE 

On fork pour le nombre de cmd à executer, et on stock le pid dans un tableau t_pid *pids.
a -> Pipe
b -> dup2()
----> Par défaut, on effectue toujours la redirection vers le pipe. Si on croise une autre redirection dans cette cmd, elle écrasera la précédente. I.e si on a une commande qui est redirigée sur un outfile avant un pipe. 
c -> déterminer les redirs, si here_doc alors on traite les here_docs en prio.
----> itérer à travers les redirs avec un compteur de here_doc.
----> Nommer les différents here_docs en ajoutant un itérateur via strjoin. Here_doc1.tmp, Here_doc_2.tmp etc..
d -> Exec la commande, si on doit récupérer le path, on ira le chercher dans cmd[0].


01/08
-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fstack-protector-strong -fno-optimize-sibling-calls

07/08

I - Début de l'EXEC

Objectifs :

1 - Récupérer les cmds dans les vecteurs.
2 - Récupérer l'env dans vect_env pour execve.
3 - Récupérer les redirs
4 - Récupérer les files des redirs.
5 - exec une cmd.
6 - exec 2 cmds.

EXEC

1 - Boucle principale : Tant que i_cmd < au nbr de cmd de l'input.
2 - Pipe si nbr_cmd >= 1.
3 - 
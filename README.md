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

31/07 

I - L'initialisation des vecteurs est OK


--> Deux cmds (une avec options) bien initialisés dans le vecteur
	---> Bien récupéré dans un char data->**cmds.
--> Nbr de cmds bien initialisé dans le vecteur
	---> Bien récupéré dans un size_t data->nbr_cmd
--> Redir bien initialisée dans le vecteur 
	---> Bien récupérée dans un int data->redir
--> Initialisation du int *pipefds et de i_pipes (à vérifier.).
--> Initialisation du int *pids et de i_pids (à vérifier.).
							TENIR À JOUR LE GARBAGE COLLECTOR
--> Envoi à execve de la cmd[0] (ls -lr), une fois splitté. OK

01/08
-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -fstack-protector-strong -fno-optimize-sibling-calls

I - Mise en place de la structure de l'exec.

1 - Pipes et fork en fonction du nbr de commandes, stockés dans des tableaux.
2 - Petit souci sur l'argument d'erreur de waitpid. À checker plus tard, pour l'instant NULL.
3 - Il faut itérer correctement les i_pipes/i_pids.


Structure de la fonction child :

On lui déclare un const t_vecstr *cmd = data->v_path.parsed[idx].cmd
I.e cette constante contient la cmd à l'index correspondant.

II - Gestion des pipes

1 - Si pids = 0 :
--> dup2 pipe[1], STDOUT_FILENO



BLOQUAGE >>

- Le stdin->infile de process 1 OK
- Le stdout->pipe[0][1] de P1 OK
- Le stdin->pipe[0][0] de P2 OK
- Le stdout->outfile de P2 OK

close :

- P1 close pipe[0][1]


02/08

IMPORTANT : Il me faut 2 idx. Un pour le parsed (l'idx de l'input qu'on traite) et un pour la cmd dans l'input. 


FIN DE JOURNÉE 02/08

Problème de redirection, soit à l'infile, soit à l'outfile.
Mais si LS dans cmd2, LS s'effectue bien dans l'outfile. Donc la redirection de i_pids2 est OK. 

Le problème vient soit du dup2 STDIN où STDOUT de P1, où du STDIN de P2 


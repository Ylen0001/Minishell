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


PIPES

1 - Si premier pipe   
--> STDIN / pipe[1]    		 OK
2 - Si entre deux 
--> pipe[0][0] / pipe[1][1]  OK
3 - Si dernier pipe
---> pipe[i - 1][0] / STDOUT OK

08/08

Infos nécessaires

Index de la cmd à gérer dans child : i_cmd++ à chaque appel de child.
Mais en même temps il ne peut pas y avoir + d'une cmd dans un appel à child. 

Nombre de cmds total de l'input : nbr_cmd = data->v_path.size

Pour le 09/08

- Plusieurs here_doc dans la meme commande : Boucle 
- La size de redir_type est de 6 quand on lui donne 3 redir "<< << >". 
Je me demande si c'est bien que ce soit un tableau d'int dans ce vecteur, plutot qu'un simple int. 

14/08

Trajet : 

- Here doc detector : 
--> Compte les here_docs et appelle here_doc_case du nbr d'HD.

- Here doc case : 
-->  Malloc un tableau de noms de here_doc
-->  Créer et ouvre le Here_doc, en le nommant (0, 1, 2 etc...);
-->  Ferme le fd.

Souci : problème de redir lorsqu'il y a plus d'un here_doc.

15/08

I - Refaire les pipes

Si + d'une cmd :

- On rentre bien deux fois dans la première condition du while de minishell
- On crée donc bien deux pipes.
- On fork bien et on rentre bien dans child 2 fois.

Dans Child :

i_cmd : 0

--> On rentre bien dans la 2nde condition. On dup stdout sur pipe[0][1]
--> On rentre dans redir, et on dup stdin sur here_doc.

i_cmd : 1

---> à partir de find_path, plus aucun print ne s'affiche. 


19/08

IMPORTANT À TRAITER : Si l'input est full whitespace, on ne rentre pas dans la fonction minishell.

Problèmes à régler 

Si 2 pipes (3cmds), avec un infile, le résultat s'affiche dans STDIN. 

Chemin :



Première cmd -> Pipe -> Fork -> Child -> STDOUT devient pipe[0][1] -> Redirection -> STDIN devient Infile -> execve de cmd1
On close pipe[0][1] / pipe[0][0].

Main post fork 1 : Après le 1st appel à fork, on ne peut pas close pipe[0][1] / [0][0]. Sinon le deuxième enfant ne pourra pas lire pipe -1. 

Seconde cmd -> Pipe -> fork -> Child -> STDIN devient pipe[0][0] -> close pipe[0][0] / [0][1] -> STDOUT devient pipe[1][1] -> close pipe[1][0] / [1][1] -> execve failure
On close pipe[1][1] / pipe[1][0] et pipe[0][0] / pipe [0][1].

Main post fork 2 : close pipe[0][0] / [0][1]

Condition = Si i_pipes == 2 (close pipe - 2)











On ne peut pas close pipe[-1][] et pipe[0][] dans le main puisque les enfants les utilisent. 
Pourtant dans le cas où on a soit une commande seul non built-in soit deux commandes


Si 3 cmd -> 3 pipes, (seulement 2 d'utilisés), i_pipes = nbr_pipes - 1.
Donc pipe[0], pipe[1] et pipe[2].

la cmd 3 utilise pipe[1] et pipe[2]. Donc on ferme pipe[0] dans main.


Si 1 cmd ->
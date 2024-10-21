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


22/08

CD built_in

- Gérer cd sans options
- Gérer cd - : Retourne au directory précédent. Si le précédent est le même, on effectue tout de même le remplacement.
- Gérer cd ~ : Retourne à la racine. En l'occurence "/home/user" (Attention à user, il faut récupérer la data dans vect_env).
- Gérer chemin absolu et relatif.

Fonctions nécéssaires :

- CHDIR int chdir(const char *path) : Change le répertoire courant du processus.
- GETCWD char *getcwd(char *buf, size_t size) : Remplit un buffer avec le chemin absolu du répertoire courant du processus. La size doit être assez grande pour récupérer le chemin absolu.

Structure :

1 - Récupérer le home. 						OK
2 - Récupérer le cwd. --> get_home_value() 	OK
3 - Récupérer le previous_directory			EN COURS.
3b - Le mettre jour avant chaque chdir.
4 - Gérer le changement de directory avec chdir. EN COURS.

--> Si cd [1] = -
--> Si cmd[1] = ~
Sinon 
--> Si chemin absolu : If access, chdir(cmd[1])
==> Si chemin relatif : access sur join de cwd + '/' + cmd[1].
-----> Si access == -1 : Non-existing path. 

1er souci : Si on fait cd - après avoir changé de dir une première fois, on reste dans le même dir. Faut-il utiliser old_pwd et le mettre à jour? Donc free, + strdup?

Pour CD - : Il faut utiliser la variable d'environnement oldpwd, et la mettre à jour avant chaque chdir.

IMPORTANT : On ne doit pas refresh le pwd à chaque nouvel input. Il doit y avoir une continuité de cd tout le long de l'exécution du programme. 

Cas particulier : 

- cd tout court fait comme cd ~ et renvoi à home.
- cd \42 : Cas de caractère d'échappement? // Pas besoin de gérer.
- cd /42 : Synthax error.

ISSUES :

CONDITION DE LA FONCTION MINISHELL:

Si une seule cmd ET non built_in ----> FORK
Si une seule cmd ET built_in 	 ----> PARENT
Si plusieurs cmd built_in où non ----> FORK


TESTER DEBUG :

59; echo hi < ./minishell_tester/test_files/infile bye bye 
59: Pour débuguer, rajouter exit(0) ligne 269.
Problème sur ce test : On devrait renvoyer "hi bye bye".
Je print bien hi bye bye, mais ensuite boucle infinie.
On rentre dans une boucle infinie dans minishell. 
i_cmd ne s'itère pas.
Le souci semble venir de la redirection. 

Problème rencontré : Si on exit pas après built_in_manager, on rentre dans une boucle infinie d'execve. 

Pour echo : exit code toujours à 0

Si une seule commande :

11 / 09

Test 136 : Test 136: ❌ ./test_files/invalid_permission 
mini exit code = 127
bash exit code = 126


127 : La cmd n'existe pas où n'a pas été trouvée
126 : La cmd existe, mais on a pas les permissions dessus. 



                         --- CLEANING ---

0 - Cmd erronée : ✅ (Les leaks restant viennent du parsing)
1 - Cmd simple (ls) : ✅
2 - Cmd simple avec argument (cat logo.txt) : ✅
3 - Cmd simple avec arguments (cat -e logo.txt) : ✅
4 - Cmd built-in echo avec et sans options (echo -n) : ✅
5 - Cmd non built_in avec redir > : ✅
6 - Cmd built_in avec redir > ✅
5 - 2 cmd non Built_in avec pipe : ✅
6 - 2 cmd Built_in avec pipe : echo bonjour | rev : ✅
7 - Here_doc : ✅
8 - ^C / ^D : ✅


❌ Souci de fermeture de FD après utilisation d'un built_in. Réglé ✅
❌ Souci quand on utilise exit.


IMPORTANT : Découpage de redirections -> if_heredoc_case à revérifier après merge. 



								| NORME |

<<<<<<< HEAD
built_in.c : ✅
minishell_core.c : ✅
core_exec.c : ✅
echo.c : ✅
redirections.c : ✅
files_checker.c : ✅
here_doc_handler.c : ✅
garbage_vector.c : ✅
garbage_collector.c : ✅
mc_utils1.c : ✅
init_vect.c : ✅
init_exec.c : ✅
path_exec : ✅
prompt.c : ✅
pwd.c : ✅
minishell.c : DÉCOUPAGE NÉCESSAIRE.

Me reste à découper : minishell.c / cd.c


RETOUR SUR CD

1 - cd initializer :

- cwd : OK
- last_dir : OK (Prend bien la valeur de oldpwd)
- home_dir : OK
- Updateoldpwd : On veut qu'à chaque appel de CD on update OLDPWD par le CWD. 
OK

<<<<<<< HEAD

--> Leaks de pipefds / pids /

=======
2 - 
=======
minishell_core.c : ✅
core_exec.c : ✅
redirections.c : ✅
files_checker.c : ✅
here_doc_handler.c : ✅
init_vect.c : ✅
init_exec.c : ✅
prompt.c : ✅ (Juste le warning pour la globale)



SEANCE DU 22/09

1 - Modification de la condition de free pour data->pids dans garbage_destructor.



< outfile rev >>outfile1
3 : ls ''
4 : make -n 
5 : Error print exit salut
6 : minishell: << eof cat << eof | rev >outfile>>outfile1





                               			| FINITIONS |

DEBUG PARSING :

    // vect_print(s_data->v_path);
	// printf("redir :\n");
	// vect_print(s_data->v_path->parsed->redir);
	// printf("type :\n");
	// vect_print(s_data->v_path->parsed->type);


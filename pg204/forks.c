#define _GNU_SOURCE 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
    pid_t pid = getpid(), pid2;
#ifdef WRONG
    fprintf(stdout, "%" PRId32, pid);//probleme
#elif defined(USE_FLUSH) //1ere solution
    fprintf(stdout, "%" PRId32, pid);
    fflush(stdout);
#elif defined(USE_SYS)//2ieme solution.
    char *buff = NULL;
    //un char* buffer=NULL
    //puis un asprintf(&buffer,"%"PRId32,pid)
    //puis un dernier write pour en finir.
    //puis free(buff) ; à ne pas oublier !
    int buffSize = 0;
    buffSize = asprintf(&buff, "%" PRId32, pid);
    if (0 > buffSize)
        return EXIT_FAILURE;
    write(STDOUT_FILENO, buff, buffSize);
    free(buff);
#endif

    pid2 = fork();
    
    if (0 > pid2) {
        perror ("fork");
    }

    else if (0 == pid2) {
      
        /* Process fils commence ici son exécution (à peu près) */

      
#if !defined(USE_SYS)
       fprintf(stdout, " %" PRId32 " %" PRId32 "\n", pid, pid2);
       //même avec flush tout seul cela marche car le premier
       //qui posait probleme pas celui-ci.
       
       //si on execute avec le flag WRONG
       //on retrouve le même problème que avec ./fork (après make fork)
       //cela va afficher 2 fois le ppid() ici(contexte) puis afficher
       //252268 même valeur en 1/2 puis 0 car pid2 vaut 0.(le pid du fils
       //dans le cas !=0)
#else
        char *buff = NULL;
        int buffSize = 0;
        buffSize = asprintf(&buff, " %" PRId32 " %" PRId32 "\n", pid, pid2);
        if (0 > buffSize)
            return EXIT_FAILURE;
        write(STDOUT_FILENO, buff, buffSize);
	//si USE_SYS est définie
	//on va afficher la valeur du pid pere
	//puis espace puis reafficher de meme la même valeur
	//puis 0. Aucun problème de nombre de printf fprintf write
	//et d'affichages sur la console(separateurs connus).
        free(buff);
#endif /* !defined(USE_SYS) */

    }


    
#if defined(USE__EXIT)
    else
        _exit(EXIT_SUCCESS);
#endif /* USE__EXIT */
    return EXIT_SUCCESS;//le exit tradionnel($?).
}
//on résoud la double écriture sur le flux sortant
//qui émerge de -DWRONG dans CFLAGS
//qui ne termine pas le buffer du coup deux buffers vont etre vides
//dans le cas du fils terminaison.

//l'affichage du pid du fils 0 ne choque pas les esprits,
//on est pas là pour ça.
//les CFLAGS+="-D??" sont connus comme pour le programme buffer(./buffer
//avec rm buffer && make buffer -CFLAGS+="-D??").

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h> /* for strrchr */

#include <stdlib.h>
#include <stdio.h>

#define ERROR(msg) do { perror(msg); return EXIT_FAILURE; } while (0)

void usage(const char *fullname)
{
    const char *name = strrchr(fullname, '/') + 1;
    fprintf(stderr, "Usage: %s <sortie> <cmd> [arg1, [arg2,...]]\n", name);
}

int main(int argc, char **argv)
{
    int fd, status;
    pid_t pid;
    if (argc < 3)
        return (usage(argv[0]), EXIT_FAILURE);

    
    fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0644);
    pid = fork();

    if (-1 == pid) {
        perror("fork");
        return EXIT_FAILURE;
    }

    else if (0 == pid) {

      if (-1 == fd)
            ERROR("open sortie");

      if (-1 == dup2(fd, STDOUT_FILENO))
            ERROR("dup2");

      execvp(argv[2], argv+2);
        /* execvp should not return(IMPORTANT) */

      ERROR(argv[2]);//c'est pour cela.(le IMPORTANT d'avant)

    }//fin code du fils.

    if (-1 == wait(&status))
        ERROR("wait");
    if (WIFEXITED(status))
        printf("Le fils a terminé normalement, code de retour: %d\n",
               WEXITSTATUS(status));
    else {
        if (WIFSIGNALED(status))
            printf("Le fils a terminé par un signal %d\n", WTERMSIG(status));
    }


    
    close(fd);
    return EXIT_SUCCESS;
}

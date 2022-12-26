#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>//le nouveau par rapport aux précédents.
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

//programme version1 sans gestion d'erreurs avancée.
int main(int argc, char** argv){
  int fd, status;
  pid_t pid;
  fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0644);
  pid=fork();
  if(0==pid){
    dup2(fd,STDOUT_FILENO);
    execvp(argv[2],argv+2);
  }
  wait(&status);
  if(WIFEXITED(status)){
    printf("Le fils a terminé normalement, code de retour: %d\n",WEXITSTATUS(status));
  }
  else{
    if(WIFSIGNALED(status)){
      printf("Le fils a terminé par un signal %d\n",WTERMSIG(status));
    }
  }
  close(fd);
  return 0;
}

//le fils a terminé par un signal 11 si on passe ./segfault.
//cela s'execute, la sortie rien(car dup2 $2!=stderr)
//et les argv+2 dans $2 de execvp c'est fait($3 n'existe pas dans le main
//\à exevp) puis cela génère une erreur d'execution de processus qui
//est reprise par le père soit le signal 11 de segfault en general.

//c'est ca.

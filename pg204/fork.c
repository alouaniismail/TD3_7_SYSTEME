#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <inttypes.h>

int main(int argc, char* argv[]){
  printf("%ld",(long)getpid());//bufferisation ici et non complete
  //pas de fflush et pas de \n implicite.
  //fflush(stdout);(solution a part d'ajouter un \n au printf).
  //utilisation de write direct pour éviter cette bufferisation.
  //ou bien ecrire dans la sortie standard mais là l'ordre ne va jouer
  //en notre faveur.
  pid_t pid2=fork();
  if(pid2==0){
    printf("Child PID: %d, Parent PID: %d\n",getpid(),getppid());
    //quand le programme se termine avec \n cela affiche en cascade
    //tout le buffer soit le premier et ici en complet
    //soit (pas de fflush(stdout)) 25001 25001 avec ce nombre le pid
    //du pere(main process) et apres affichage de celui-là.
    //car quand on appelle a fork on a deux buffers non complets mis en place
    //car pas complet(comme un prog en cours d'execution.) soit
    //le retour du programme affiche en cascade tout cela soit (\npresent.)
    //2 fois le même pid.
    //le programme forks.c resoud ceci.(avec les méthodes présentées
    //ci-dessus)
  }
  return 0;
}

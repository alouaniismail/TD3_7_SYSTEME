#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"

#define CHAINE1 "Debut\n" //le \n change tout.
#define CHAINE2 "Fin"

int main(int argc, char ** argv)
{
    int out1 = 1;
    int out2 = 1;
    FILE *fout1 = stdout;
    FILE *fout2 = stdout;

#ifdef UTILISER_SORTIE_ERREUR1
    out1 = 2;
    fout1 = stderr;
#endif

#ifdef UTILISER_SORTIE_ERREUR2
    out2 = 2;
    fout2 = stderr;
#endif

#ifdef UTILISER_FPRINTF1
    fprintf( fout1, "%s", CHAINE1 );
#else
    write( out1, CHAINE1, strlen(CHAINE1) );
#endif /* UTILISER_FPRINTF1 */

    sleep(1);
    
#ifdef UTILISER_FPRINTF2
    fprintf( fout2, "%s", CHAINE2 );
#else
    write( out2, CHAINE2, strlen(CHAINE2) );
#endif /* UTILISER_FPRINTF2 */

#ifdef UTILISER__EXIT
    _exit(EXIT_SUCCESS);
#else
    exit(EXIT_SUCCESS);
#endif /* UTILISER__EXIT */
}

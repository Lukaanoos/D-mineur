#ifndef biblio
    #define biblio
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <time.h>
    #include <sys/time.h>
    #include <conio.h>
#endif

#ifndef fonctionG
    #define fonctionG
    #include "fonctionGenerale.h"
#endif

#ifndef fonctionJ
    #define fonctionJ
    #include "fonctionJeu.h"
#endif

void menu_custom(int demineurSize[]);
int menu_level(int deminerSize[]);
int menu_play();

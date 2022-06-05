#ifndef fonctionG
    #define fonctionG
    #include "fonctionGenerale.h"
#endif

#ifndef fonctionM
    #define fonctionM
    #include "fonctionMenu.h" //contient les bibliothèques
#endif

void boom();
void score(unsigned long timeur, int mode);
int isItABombe(int demineurBombe[], int totalBombe, int position);
int checkBombe(int demineurBombe[], int totalBombe, int length, int width, int indexX, int indexY);
int recDiscoverZone(int* demineur, int* demineurBombe, int totalBombe, int length, int width, int indexX, int indexY);
static void printDemineurSmall(int* demineur, int length, int width);
static void printDemineurBig(int* demineur, int length, int width);
void enterCord(int caseCords[], int length, int width);
void setBombe(int demineurBombe[], int length, int width, int nBombe, int firstTry);
char chooseBombeOrSafe();
void revealBombe(int* demineur, int demineurBombe[], int nBombe);
int start_game(int length, int width, int bombe);

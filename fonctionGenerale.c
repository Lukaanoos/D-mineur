#ifndef fonctionG
    #define fonctionG
    #include "fonctionGenerale.h"
#endif


//////////////////////////////
///// fonction generale //////
//////////////////////////////

//affiche le titre du jeu
void title() {
    printf("    ____                       _\n   / __ \\  ___    ____ ___    (_)  ____   ___   __  __  _____\n  / / / / / _ \\  / __ `__ \\  / /  / __ \\ / _ \\ / / / / / ___/\n / /_/ / /  __/ / / / / / / / / / / / //  __// /_/ / / /\n/_____/  \\___/ /_/ /_/ /_/ /_/ /_/ /_/ \\___/ \\__,_/ /_/\n\n");
}

//transforme une lettre en un nombre (ex: A->0, C->2, a->26, d->29)
int charToInt(char c) {
    int res = c - '0' - 17;
    if (res > 25) {return res - 6;}
    return res;
}

//transforme un nombre en une lettre (ex: 0->A, 2->C, 26->a, 29->d)
char intToChar(int i) {
    int res = i + '0' + 17;
    if (res > 90) {return res + 6;}
    return res;
}

//clear la console
void clear() {
    system("@cls||clear");
}

//recupère le temps en milliseconde
unsigned long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (1000000 * tv.tv_sec) + tv.tv_usec;
}

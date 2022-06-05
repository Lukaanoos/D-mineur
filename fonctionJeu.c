#ifndef fonctionJ
    #define fonctionJ
    #include "fonctionJeu.h"
#endif


//////////////////////////////
//////// fonction jeu ////////
//////////////////////////////

char input[5]; //input

//affiche BOOM! quand le joueur à perdu
void boom() {
    printf("\n _______       ______        ______     ___      ___       ___\n|   _  \"\\     /    \" \\      /    \" \\   |\"  \\    /\"  |     |\"  |\n(. |_)  :)   // ____  \\    // ____  \\   \\   \\  //   |     ||  |\n|:     \\/   /  /    ) :)  /  /    ) :)  /\\\\  \\/.    |     |:  |\n(|  _  \\\\  (: (____/ //  (: (____/ //  |: \\.        |    _|  /\n|: |_)  :)  \\        /    \\        /   |.  \\    /:  |   / |_/ )\n(_______/    \\\"_____/      \\\"_____/    |___|\\__/|___|  (_____/\n");
}

//récupère le score du joueur et le meilleur score
void score(unsigned long timeur, int mode) {
    int scoreGame = (getTime() - timeur) / 1000000;
    title();
    clear();
    printf("Vous  avez finis en %d sec\n", scoreGame);
    FILE* fichier = NULL; 
    int bestScore9; int bestScore16;
    fichier = fopen("score.txt", "r");
    if (fichier == NULL) {
        printf("Fichier score.txt introuvable /!\\");
        getch();
    } else {
        fscanf(fichier, "%d", &bestScore9);
        fscanf(fichier, "%d", &bestScore16);
        if (mode == 0) {
            printf("Le meilleur score est %d sec\n", bestScore9);
        } else if (mode == 1) {
            printf("Le meilleur score est %d sec\n", bestScore16);
        }
        getch();
    }
    fclose(fichier);
    fichier = fopen("score.txt", "w");
    if (mode == 0 && scoreGame < bestScore9) {
        fprintf(scoreGame, "\n", bestScore16);
    } else if (mode == 1 && scoreGame < bestScore16) {
        fprintf(bestScore9, "\n", scoreGame);
    }
    fclose(fichier);

}

//retourne 1 si la case passer en argument est une bombre sinon 0
int isItABombe(int demineurBombe[], int totalBombe, int position) {
    for (int i=0; i<totalBombe; i++) {
        if (demineurBombe[i] == position) {
            return 1;
        }
    }
    return 0;
}

//retourne le nombre de bombe autour de la case
int checkBombe(int demineurBombe[], int totalBombe, int length, int width, int indexX, int indexY) {
    int bombe = 0;
    for (int i=-1; i<2; i++) {
        for (int j=-1; j<2; j++) {
            if (indexX + i >= 0 && indexY + j >= 0 && indexX + i < length && indexY + j < width) {
                bombe += isItABombe(demineurBombe, totalBombe, (indexX + i) * width + indexY + j);
            }
        }
    }
    return bombe;
}

//fonction recursive permettant de découvrir les cases vide
int recDiscoverZone(int* demineur, int* demineurBombe, int totalBombe, int length, int width, int indexX, int indexY) {
    //teste si la case est une bombre
    if (isItABombe(demineurBombe, totalBombe, indexX * width + indexY) == 1) {
        return 0;
    }
    //remplace la valeur de case par le nombre de bombe qui l'entour
    demineur[indexX * width  + indexY] = checkBombe(demineurBombe, totalBombe, length, width, indexX, indexY);
    if (demineur[indexX * width  + indexY] > 0) {
        return 1;
    }
    //zone contient le nombre de case que la fonctionà découvert
    int zone = 1;

    //éxécute la fonction sur les cases autour
    //haut
    if (indexX - 1 >= 0 && demineur[(indexX - 1) * width  + indexY] == -1) {
        zone += recDiscoverZone(demineur, demineurBombe, totalBombe, length, width, indexX - 1, indexY);
    }
    //bas
    if (indexX + 1 < length && demineur[(indexX + 1) * width  + indexY] == -1) {
        zone += recDiscoverZone(demineur, demineurBombe, totalBombe, length, width, indexX + 1, indexY);
    }
    //gauche
    if (indexY - 1 >= 0 && demineur[indexX * width  + indexY - 1] == -1) {
        zone += recDiscoverZone(demineur, demineurBombe, totalBombe, length, width, indexX, indexY - 1);
    }
    //droite
    if (indexY + 1 < width && demineur[indexX * width  + indexY + 1] == -1) {
        zone += recDiscoverZone(demineur, demineurBombe, totalBombe, length, width, indexX, indexY + 1);
    }
    //haut gauche
    if (indexX - 1 >= 0 && indexY - 1 >= 0 && demineur[(indexX - 1) * width  + indexY - 1] == -1) {
        zone += recDiscoverZone(demineur, demineurBombe, totalBombe, length, width, indexX - 1, indexY - 1);
    }
    //haut droite
    if (indexX - 1 >= 0 && indexY + 1 < width && demineur[(indexX - 1) * width  + indexY + 1] == -1) {
        zone += recDiscoverZone(demineur, demineurBombe, totalBombe, length, width, indexX - 1, indexY + 1);
    }
    //bas gauche
    if (indexX + 1 < length && indexY - 1 >= 0 && demineur[(indexX + 1) * width  + indexY - 1] == -1) {
        zone += recDiscoverZone(demineur, demineurBombe, totalBombe, length, width, indexX + 1, indexY - 1);
    }
    //bas droite
    if (indexX + 1 < length && indexY + 1 < width && demineur[(indexX + 1) * width  + indexY + 1] == -1) {
        zone += recDiscoverZone(demineur, demineurBombe, totalBombe, length, width, indexX + 1, indexY + 1);
    }
    return zone;
}

//affiche la grille de façon non-compact lorsque le démineur fait moins de 13x27
static void printDemineurSmall(int* demineur, int length, int width) {
    clear();
    title();
    printf("\\  ");
    if (length > 9) {
        printf(" ");
    }
    for (int i=0; i < width; i++) { //affiche les lettres en haut
        printf(" %c  ", intToChar(i));
    }
    for (int i=0; i < length * 2 + 1; i++) {
        if (i % 2 == 1) {
            printf("\n%d ", i/2);
        } else {
            printf("\n  ");
        }
        if (length > 9 && i/2 <= 9 || i % 2 == 0 && i/2 > 9) {
            printf(" ");
        }
        printf("|");
        for (int j=0; j < width; j++) {
            if (i % 2 == 1) {
                switch (demineur[i/2 * width + j]) {
                case -1:
                    printf("   "); //case non découverte
                    break;
                case 0:
                    printf(" ~ "); //case vide
                    break;
                case -2:
                    printf(" X "); //drapeau
                    break;
                case -3:
                    printf(" O "); //bombre
                    break;
                default:
                    printf(" %d ", demineur[i/2 * width + j]); //nombre de bombe autour
                    break;
                }
            } else {
                printf("---");
            }
            printf("|");
        }
    }
}

//affiche la grille de façon compact lorsque le démineur fait plus de 12x26
static void printDemineurBig(int* demineur, int length, int width) {
    clear();
    title();
    printf("\\  ");
    if (length > 9) {
        printf(" ");
    }
    for (int i=0; i < width; i++) { //affiche les lettres des coordonnées
        printf("%c ", intToChar(i));
    }
    for (int i=0; i < length; i++) {
        printf("\n%d ", i);
        if (length > 9 && i <= 9) {
            printf(" ");
        }
        printf("|");
        for (int j=0; j < width; j++) {
            switch (demineur[i * width + j]) {
            case -1:
                printf(" "); //case non découverte
                break;
            case 0:
                printf("~"); //case vide découverte
                break;
            case -2:
                printf("X"); //drapeau
                break;
            case -3:
                printf("O"); //bombe
                break;
            default:
                printf("%d", demineur[i * width + j]); //nombre de bombe autour
                break;
            }
            printf("|");
        }
    }
}

//permet au joueur de rentrer les coordonnées
void enterCord(int caseCords[], int length, int width) {
    int lengthE = -1;
    int widthE = -1;
    while (lengthE < 0 || lengthE >= length || widthE < 0 || widthE >= width) {
        printf("Entrez les coordonnées séparé par une virgule (sans espace):\n");
        scanf("%s", input);
        if (isalpha(input[0]) && input[1] == ',' && isdigit(input[2])) {
            if (isdigit(input[3])) { //teste si le premier coordonnée est un nombre
                lengthE = (input[2] + '0' - 96) * 10 + (input[3] + '0' -96); //traduit la chaine de caractère en nombre
            } else {
                lengthE = (input[2] + '0' - 96); //traduit la chaine de caractère en index
            }
            widthE = charToInt(input[0]);
        } else if (isalpha(input[3]) && input[2] == ',' && isdigit(input[0]) && isdigit(input[1])) {
            lengthE = (input[0] + '0' - 96) * 10 + (input[1] + '0' -96);
            widthE = charToInt(input[3]);
        } else if (isalpha(input[2]) && input[1] == ',' && isdigit(input[0])) {
            lengthE = (input[0] + '0' - 96);
            widthE = charToInt(input[2]);
        }
    }
    caseCords[0] = lengthE;
    caseCords[1] = widthE;
}

void setBombe(int demineurBombe[], int length, int width, int nBombe, int firstTry) {
    srand(time(NULL));
    int i=0; int temp; int doubleBombe;
    while (i < nBombe) {
        temp = rand()%length * width + rand()%width;
        if (temp != firstTry) {
            doubleBombe = 0;
            for (int j=0; j<i; j++) {
                if (demineurBombe[j] == temp) {
                    doubleBombe = 1;
                    break;
                }
            }
            if (doubleBombe == 0) {
                demineurBombe[i] = temp;
                i++;
            }
        }
    }
}

char chooseBombeOrSafe() {
    do {
        printf("Choisir une action\n");
        printf("1 - Placer un drapeau\n2 - Dévoiler une case\n-> ");
        scanf("%s", input);
    } while (input[0] != '1' && input[0] != '2' || input[1] != '\0');
    return input[0];
}

void revealBombe(int* demineur, int demineurBombe[], int nBombe) {
    for (int i=0; i<nBombe; i++) {
        demineur[demineurBombe[i]] = -3;
    }
}

int start_game(int length, int width, int bombe) {
    int endGame = 0;
    int demineur[length * width];
    int demineurBombe[bombe];
    for (int i=0; i < length; i++) {
        for (int j=0; j < width; j++) {
            demineur[i * width +j] = -1;
        }
    }
    for (int i=0; i < bombe; i++) {
        demineurBombe[i] = -1;
    }
    int zoneClean = 0;
    int caseCords[2];
    void (*printDemineur)();
    if (length > 13 || width > 27) {
        printDemineur = &printDemineurBig;
    } else {
        printDemineur = &printDemineurSmall;
    }
    unsigned long begin = getTime();
    while (endGame == 0) {
        if (zoneClean + bombe >= length * width) {
            if (length == width && length==9) {
                score(begin, 0);
            } else if (length == width && length==16) {
                score(begin, 1);
            } else {
                score(begin, 1);
            }
            return 1;
        }
        (*printDemineur)(demineur, length, width);
        printf("\n\n");
        enterCord(caseCords, length, width);
        if (chooseBombeOrSafe() == '1') {
            if (demineur[caseCords[0] * width + caseCords[1]] == -1) {
                demineur[caseCords[0] * width + caseCords[1]] = -2;
            } else if (demineur[caseCords[0] * width + caseCords[1]] == -2) {
                demineur[caseCords[0] * width + caseCords[1]] = -1;
            }
        } else {
            if (demineurBombe[0] == -1) {
                setBombe(demineurBombe, length, width, bombe, caseCords[0] * width + caseCords[1]);
            }
            if (isItABombe(demineurBombe, bombe, caseCords[0] * width + caseCords[1]) == 1 &&demineur[caseCords[0] * width + caseCords[1]] != -2) {
                endGame = 1;
                revealBombe(demineur, demineurBombe, bombe);
                (*printDemineur)(demineur, length, width);
            }
            zoneClean += recDiscoverZone(demineur, demineurBombe, bombe, length, width, caseCords[0], caseCords[1]);
        }
    }
    boom();
    getch();
}

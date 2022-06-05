#ifndef fonctionM
    #define fonctionM
    #include "fonctionMenu.h"
#endif


//////////////////////////////
//////// fonction menu ///////
//////////////////////////////

char input[5]; //input

void menu_custom(int demineurSize[]) {
    do {
        clear();
        title();
        printf("Entrez la longueur espace la largeur (longeur Max: 100, largeur Max 52): \n");
        scanf("%s", input);
        if (isdigit(input[2]) && isdigit(input[1]) && isdigit(input[0]) && input[3] == '\0') {
            demineurSize[0] = (input[0] - 48) * 100 + (input[1] - 48) * 10 + (input[2] - 48);
        } else if (isdigit(input[1]) && isdigit(input[0]) && input[2] == '\0') {
            demineurSize[0] = (input[0] - 48) * 10 + (input[1] - 48);
        } else if (isdigit(input[0]) && input[1] == '\0') {
            demineurSize[0] = (input[0] - 48);
        } else {
            demineurSize[0] = 0;
        }
        scanf("%s", input);
        if (isdigit(input[2]) && isdigit(input[1]) && isdigit(input[0]) && input[3] == '\0') {
            demineurSize[1] = (input[0] - 48) * 100 + (input[1] - 48) * 10 + (input[2] - 48);
        } else if (isdigit(input[1]) && isdigit(input[0]) && input[2] == '\0') {
            demineurSize[1] = (input[0] - 48) * 10 + (input[1] - 48);
        } else if (isdigit(input[0]) && input[1] == '\0') {
            demineurSize[1] = (input[0] - 48);
        } else {
            demineurSize[1] = 0;
        }
    } while (demineurSize[0] <= 0 || demineurSize[0] > 100  || demineurSize[1] <= 0 || demineurSize[1] > 52);
    do {
        clear();
        title();
        printf("Entrez le nombre de bombe (Max %d): \n", demineurSize[0] * demineurSize[1] - 1);
        scanf("%s", input);
        if (isdigit(input[3]) && isdigit(input[2]) && isdigit(input[1]) && isdigit(input[0]) && input[4] == '\0') {
            demineurSize[2] = (input[0] - 48) * 1000 + (input[0] - 48) * 100 + (input[1] - 48) * 10 + (input[2] - 48);
        } else if (isdigit(input[2]) && isdigit(input[1]) && isdigit(input[0]) && input[3] == '\0') {
            demineurSize[2] = (input[0] - 48) * 100 + (input[1] - 48) * 10 + (input[2] - 48);
        } else if (isdigit(input[1]) && isdigit(input[0]) && input[2] == '\0') {
            demineurSize[2] = (input[0] - 48) * 10 + (input[1] - 48);
        } else if (isdigit(input[0]) && input[1] == '\0') {
            demineurSize[2] = (input[0] - 48);
        } else {
            demineurSize[2] = 0;
        }
    } while (demineurSize[2] <= 0 || demineurSize[2] > demineurSize[0] * demineurSize[1] - 1);
}

int menu_level(int deminerSize[]) {
    do {
        clear();
        title();
        printf("Taille de grille:\n1 - 9 x 9\n2 - 16 x 16\n3 - Personnalisée\n4 - Retour\n-> ");
        scanf("%s", input);
    } while (input[0] != '1' && input[0] != '2' && input[0] != '3' && input[0] != '4' || input[1] != '\0');
    switch (input[0]) {
        case '1':
            deminerSize[0] = 9; deminerSize[1] = 9; deminerSize[2] = 10;
            break;
        case '2':
            deminerSize[0] = 16; deminerSize[1] = 16;  deminerSize[2] = 40;
            break;
        case '3':
            menu_custom(deminerSize);
            break;
        case '4':
            return 0;
            break;
    }
    return 1;
}

int menu_play() {
    int deminerSize[3];
    do {
        clear();
        title();
        printf("1 - Joueur\n2 - Quitter\n-> ");
        scanf("%s", input);
    } while (input[0] != '1' && input[0] != '2' || input[1] != '\0');
    if (input[0] == '2') {
        exit(1);
    } else {
        if (menu_level(deminerSize) == 0) {
            return 0;
        }
    }
    start_game(deminerSize[0], deminerSize[1], deminerSize[2]);
    return 1;
}

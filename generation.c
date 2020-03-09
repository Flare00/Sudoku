#include "generation.h"
#include "difficulte.h"

// A COMPLETER
unsigned int *genererChaineSudoku(size_t taille, int level){
    int difficulte = 0;
    uint8_t ** grille = genererGrilleComplete(taille);

    int casesRestante = retirerCaseRandom(grille);

    do{
        uint8_t ** grilleTemp = grille; // faire une de la grille copie;
        casesRestante = retirerCaseRandomAvecCaseRestante(grilleTemp, taille);
        difficulte = validiterEtDifficulter(grille, taille, level);
        //La difficulté 5 permet a l'algorithme de renvoyer la derniere grille, car la nouvelle ne correspond plus au niveau souhaiter.
        //La difficulté 0 (erreur) ne remplace pas grille par grille_temp et permet donc de changer la case retirer aléatoirement.
        if (difficulte != 5 && difficulte != 0){
            // libere la mémoire de la grille, et la remplace par la grille temporaire.
            free(grille); 
            grille = grilleTemp;
        }

        //si le nombre de cases restante est inferieur a 20, termine la boucle.
        if(casesRestante < 20){
            difficulte = 5;
        }
    }while(difficulte != 5);

    return ""; // A COMPLETER
}

uint8_t **genererGrilleSudokuValide(int taille, int level){
    int difficulte = 0;
    uint8_t ** grille = genererGrilleComplete(taille);

    int casesRestante = retirerCaseRandom(grille);

    do{
        uint8_t ** grilleTemp = grille; // faire une de la grille copie;
        casesRestante = retirerCaseRandomAvecCaseRestante(grilleTemp, taille);
        difficulte = validiterEtDifficulter(grilleTemp, taille, level);
        //La difficulté 5 permet a l'algorithme de renvoyer la derniere grille, car la nouvelle ne correspond plus au niveau souhaiter.
        //La difficulté 0 (erreur) ne remplace pas grille par grille_temp et permet donc de changer la case retirer aléatoirement.
        if (difficulte != 5 && difficulte != 0){
            // libere la mémoire de la grille, et la remplace par la grille temporaire.
            free(grille); 
            grille = grilleTemp;
            free(grilleTemp);
        }

        //si le nombre de cases restante est inferieur a 20, termine la boucle.
        if(casesRestante < 20){
            difficulte = 5;
        }
    }while(difficulte != 5);

    return grille;
}

size_t retirerCaseRandomAvecCaseRestante(uint8_t ** grille, size_t taille){
    size_t nbCases = 0;
    struct posCase * pos = malloc(taille*taille);
    for(int i = 0; i < taille; i++){
        for(int j = 0; j < taille; j++){
            if(grille[i][j] != 0){
                struct posCase temp = {i,j};
                pos[nb_cases] = temp;
                nb_cases++;
            }
        }
    }

    int aSuppr = rand(time())%nb_cases;

    grille[pos[aSuppr].colonne][pos[aSuppr].ligne] = 0;

    return (nbCases - 1);
}

uint8_t retirerCaseRandom(uint8_t ** grille, size_t taille){
    size_t ligne = rand(time())%taille;
    size_t colonne = rand(time())%taille;
    int reussi = 0;

    while (reussi == 0){
        if(grille[colonne][ligne] != 0){
            grille[colonne][ligne] = 0;
            reussi = 1;
        }
    }

    return grille;
}


uint8_t genererGrilleComplete(size_t taille){
    // A FAIRE;
    return 0;
}

uint8_t ** permutationLignes(uint8_t ** grille, size_t taille, size_t ligne1, size_t ligne2){
        for(int i = 0; i < taille; i++){
            int8_t temp = grille[i][ligne1];
            grille[i][ligne1] = grille[i][ligne2];
            grille[i][ligne2] = temp;
        }

        return grille;
}

uint8_t ** permutationColones(uint8_t ** grille, size_t taille, size_t colone1, size_t colone2){
        for(int i = 0; i < taille; i++){
            int8_t temp = grille[colone1][i];
            grille[colone1][i] = grille[colone2][i];
            grille[colone2][i] = temp;
        }

        return grille;
}

uint8_t ** rotation(uint8_t ** grille, size_t taille){
    //A FAIRE;
    return 0;
}
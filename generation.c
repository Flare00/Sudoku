#include "generation.h"
#include "difficulte.h"

// A COMPLETER
unsigned int *generer_chaine_sudoku(size_t taille, int level){
    int difficulte = 0;
    uint8_t ** grille = generer_grille_complete(taille);

    int cases_restante = retirer_case_random(grille);

    do{
        uint8_t ** grille_temp = grille; // faire une de la grille copie;
        cases_restante = retirer_case_random(grille_temp);
        difficulte = validiter_et_difficulter(grille, taille, level);
        //La difficulté 5 permet a l'algorithme de renvoyer la derniere grille, car la nouvelle ne correspond plus au niveau souhaiter.
        //La difficulté 0 (erreur) ne remplace pas grille par grille_temp et permet donc de changer la case retirer aléatoirement.
        if (difficulte != 5 && difficulte != 0){
            // libere la mémoire de la grille, et la remplace par la grille temporaire.
            free(grille); 
            grille = grille_temp;
        }

        //si le nombre de cases restante est inferieur a 20, termine la boucle.
        if(cases_restante < 20){
            difficulte = 5;
        }
    }while(difficulte != 5);

    return ""; // A COMPLETER
}

uint8_t **generer_grille_sudoku_valide(int taille, int level){
    int difficulte = 0;
    uint8_t ** grille = generer_grille_complete(taille);

    int cases_restante = retirer_case_random(grille);

    do{
        uint8_t ** grille_temp = grille; // faire une de la grille copie;
        cases_restante = retirer_case_random(grille_temp);
        difficulte = validiter_et_difficulter(grille, taille, level);
        //La difficulté 5 permet a l'algorithme de renvoyer la derniere grille, car la nouvelle ne correspond plus au niveau souhaiter.
        //La difficulté 0 (erreur) ne remplace pas grille par grille_temp et permet donc de changer la case retirer aléatoirement.
        if (difficulte != 5 && difficulte != 0){
            // libere la mémoire de la grille, et la remplace par la grille temporaire.
            free(grille); 
            grille = grille_temp;
        }

        //si le nombre de cases restante est inferieur a 20, termine la boucle.
        if(cases_restante < 20){
            difficulte = 5;
        }
    }while(difficulte != 5);

    return grille;
}

size_t retirer_case_random(uint8_t ** grille, size_t taille){
    size_t nb_cases = 0;
    struct pos_case * pos = malloc(taille*taille);
    for(int i = 0; i < taille; i++){
        for(int j = 0; j < taille; j++){
            if(grille[i][j] != 0){
                struct pos_case temp = {i,j};
                pos[nb_cases] = temp;
                nb_cases++;
            }
        }
    }

    int a_suppr = rand(time())%nb_cases;

    grille[pos_case[a_suppr].colonne][pos_case[a_suppr].ligne] = 0;

    return (nb_cases - 1);
}

uint8_t generer_grille_complete(size_t taille){
    // A FAIRE;
    return 0;
}
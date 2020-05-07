#include "generation.h"

uint8_t **genererGrilleSudokuValide(size_t taille, size_t niveauDemander)
{
    size_t difficulte = 0;
    size_t difficulteMaxAtteint = 0;
    srand(time(NULL));

    uint8_t **grille = genererGrilleComplete(taille);

    size_t nbCasesTotal = taille*taille;
    size_t casesRestantes = nbCasesTotal;

    size_t casesRestantesMin = taille*taille;
    size_t casesRestantesMax = taille*taille;
    int compteurEchec = 0;

    if(taille == 4){
        //niveau max : facile;
        niveauDemander = 1;
        if (niveauDemander == 1){
            //niveau facile;
            casesRestantesMax = 6;
            casesRestantesMin = 6;
        } 
    } else if (taille == 9){
        if(niveauDemander == 1){
            //niveau facile;
            casesRestantesMax = 40;
            casesRestantesMin = 30;
        } else if(niveauDemander == 2){
            //niveau moyen;
            casesRestantesMax = 30;
            casesRestantesMin = 25;
        }else if (niveauDemander == 3){
            //niveau difficile;
            casesRestantesMax = 25;
            casesRestantesMin = 18;
        } else if (niveauDemander == 4){
            //niveau extreme;
            casesRestantesMax = 20;
            casesRestantesMin = 19;
        }
    } else if (taille == 16){
        if(niveauDemander == 2){
            //niveau moyen;
            casesRestantesMax = 160;
            casesRestantesMin = 150;
        }else if (niveauDemander == 3){
            //niveau difficile;
            casesRestantesMax = 150;
            casesRestantesMin = 140;
        } else if (niveauDemander == 4){
            //niveau extreme;
            casesRestantesMax = 140;
            //casesRestantesMin = 70;
            casesRestantesMin = 135;
        } else {
            niveauDemander = 2;
            casesRestantesMax = 160;
            casesRestantesMin = 150;
        }
    } else if (taille == 25){
        if (niveauDemander == 3){
            //niveau difficile;
            casesRestantesMax = 400;
            casesRestantesMin = 380;
        } else if (niveauDemander == 4){
            //niveau extreme;
            casesRestantesMax = 380;
            //casesRestantesMin = 180;
            casesRestantesMin = 370;
        } else {
            niveauDemander = 3;
            casesRestantesMax = 400;
            casesRestantesMin = 380;
        }
    } else if (taille == 36){
            casesRestantesMax = 880;
            casesRestantesMin = 880;
    } else if (taille == 49){
            casesRestantesMax = 1750;
            casesRestantesMin = 1750;
    } else if (taille == 64){
            casesRestantesMax = 3100;
            casesRestantesMin = 3100;
    }
    uint8_t **grilleTemp = NULL;
    size_t retraitTot = 0;
    do
    {
        grilleTemp = grilleCloner(grille,taille); // faire une de la grille copie;
        int retrait = retirerCaseSymetrie(grilleTemp, taille);
        casesRestantes -= retrait;

        if(taille >= 36 || (taille == 25 && niveauDemander == 4)){
        	while(casesRestantes > casesRestantesMax){
        		retrait = retirerCaseSymetrie(grilleTemp, taille);
        		casesRestantes -= retrait;
                retraitTot+= retrait;
        	}
        } 
        difficulte = validiterEtDifficulter(grilleCloner(grilleTemp,taille), taille, niveauDemander);
        if(difficulte == 6){
            detruire2D(grille, taille);
            grille = grilleTemp;
            difficulte = 5;
        }else{
            if(difficulte < 5 && difficulte > difficulteMaxAtteint){
                difficulteMaxAtteint = difficulte;
            }
            //La difficulté 5 permet a l'algorithme de renvoyer la derniere grille, car la nouvelle ne correspond plus au niveau souhaiter.
            //La difficulté 0 (erreur) ne remplace pas grille par grille_temp et permet donc de changer la case retirer aléatoirement.
            if (difficulte != 5 && difficulte != 0)
            {
                // libere la mémoire de la grille, et la remplace par la grille temporaire.
                detruire2D(grille, taille);
                grille = grilleTemp;
                compteurEchec = 0;
            } else if(difficulte == 0){
                compteurEchec += 1;
                detruire2D(grilleTemp, taille);
                if(taille >= 36 || (taille == 25 && niveauDemander == 4)){
                    casesRestantes += retraitTot;
                    retraitTot = 0;
                } else {
                    casesRestantes += retrait;
                }
                if(casesRestantes <= casesRestantesMax && (difficulteMaxAtteint == niveauDemander || niveauDemander == 4)){
                    difficulte = 5;
                }
            } else {
                compteurEchec += 1;
            	if(casesRestantes > casesRestantesMax){
            		difficulte = 0;
            	}
                detruire2D(grilleTemp, taille);
            }
            
            //si le nombre de cases restante est inferieur au nombre de casesRestantesMin, termine la boucle.
            
        }
        if(compteurEchec > 1 && (taille <= 16 || (taille <= 25 && niveauDemander < 4))){
            difficulte = 5;
        }
        if (casesRestantes <= casesRestantesMin)
        {
            difficulte = 5;
        }
    } while (difficulte != 5);
    return grille;
}

/*void retirerCaseRandom(uint8_t **grille, size_t taille)
{

    int reussi = 0;

    while (reussi == 0)
    {
        size_t ligne = rand() % taille;
        size_t colonne = rand() % taille;
        if (grille[colonne][ligne] != 0)
        {
            grille[colonne][ligne] = 0;
            reussi = 1;
        }
    }
}*/

size_t retirerCaseSymetrie(uint8_t **grille, size_t taille)
{
    size_t reussi = 0;

    while (reussi == 0)
    {
        size_t ligne = rand() % taille;
        size_t colonne = rand() % taille;
        size_t symLigne = taille-ligne-1;
		size_t symColonne = taille-colonne-1;
        if (grille[colonne][ligne] != 0)
        {
            grille[colonne][ligne] = 0;

            reussi = 1;
            if(grille[symColonne][symLigne] != 0){
        		grille[symColonne][symLigne] = 0;
            	reussi = 2;
			}
        }
    }
    return reussi;
}

uint8_t **genererGrilleComplete(size_t taille)
{
    uint8_t **retour = malloc(taille * sizeof(uint8_t *));
    for (int i = 0; i < taille; i++)
    {
        retour[i] = malloc(taille * sizeof(uint8_t));
    }
    size_t tailleBloc = (size_t)sqrt(taille);

    //Creer une liste valeurMelange pour mélanger les valeurs lors de la génération;
    uint8_t *valeurMelange = malloc(taille);
    for (int i = 0; i < taille; i++)
    {
        valeurMelange[i] = i + 1;
    }
    for (int i = 0; i < taille * 2;i++)
    {
        //choisie aléatoirement deux case a echangeé
        int base = rand() % taille;
        int echange = rand() % taille;
        //les echange dans la liste
        uint8_t temp = valeurMelange[base];
        valeurMelange[base] = valeurMelange[echange];
        valeurMelange[echange] = temp;
    }

    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            //Formule pour generer, selon i, j,la taille de la grille, et tailleBloc la taille d'un bloc de la grille.
            //Genere une grille complete valide ayant pour premiere ligne le tableau valeurMelange;
        	retour[i][j] = valeurMelange[(((tailleBloc * i) + (((j % tailleBloc) + (i/tailleBloc)) + (tailleBloc * (j / tailleBloc)))) % (taille))];
        }
    }

    //Permutation 

    for (int i = 0; i < taille * 4; i++)
    {
        int x = rand() % taille;
        int y = rand() % taille;

        while (x == y)
        {
            y = rand() % taille;
        }

        permuterLignes(retour, taille);

        permuterColonnes(retour, taille);
    }

    return retour;
}

void permuterLignes(uint8_t **grille, size_t taille)
{
    size_t tailleBloc = sqrt(taille);
    //permutation des lignes d'une bande

    for (int i = 0; i < taille*2; i++)
    {
        int v1 = (rand() % tailleBloc) + (tailleBloc * (i % tailleBloc));
        int v2 = (rand() % tailleBloc) + (tailleBloc * (i % tailleBloc));
        while (v1 == v2)
        {
            v2 = (rand() % tailleBloc) + (tailleBloc * (i % tailleBloc));
        }
        echangerLignes(grille, taille, v1, v2);
    }

    //permutation des bandes
    for (int i = 0; i < taille; i++)
    {
        int v1 = rand() % tailleBloc;
        int v2 = rand() % tailleBloc;
        while (v1 == v2)
        {
            v2 = rand() % tailleBloc;
        }
        for(int i = 0; i < tailleBloc;i++){
        	echangerLignes(grille, taille, (v1 * tailleBloc)+i, (v2 * tailleBloc) + i);
        }
    }
}

void permuterColonnes(uint8_t **grille, size_t taille)
{

    size_t tailleBloc = sqrt(taille);

    //permutation des colonne d'une pile
    for (int i = 0; i < taille * 2; i++)
    {
        int v1 = (rand() % tailleBloc) + (tailleBloc * (i % tailleBloc));
        int v2 = (rand() % tailleBloc) + (tailleBloc * (i % tailleBloc));
        while (v1 == v2)
        {
            v2 = (rand() % tailleBloc) + (tailleBloc * (i % tailleBloc));
        }
        echangerColonnes(grille, taille, v1, v2);
    }

    //permutation des piles
    for (int i = 0; i < taille; i++)
    {
        int v1 = rand() % tailleBloc;
        int v2 = rand() % tailleBloc;

        while (v1 == v2)
        {
            v2 = rand() % tailleBloc;
        }

		for(int i = 0; i < tailleBloc;i++){
        	echangerColonnes(grille, taille, (v1 * tailleBloc)+i, (v2 * tailleBloc) + i);
        }
    }

}

void echangerLignes(uint8_t **grille, size_t taille, size_t ligne1, size_t ligne2)
{
    for (int i = 0; i < taille; i++)
    {
        int8_t temp = grille[i][ligne1];
        grille[i][ligne1] = grille[i][ligne2];
        grille[i][ligne2] = temp;
    }
}

void echangerColonnes(uint8_t **grille, size_t taille, size_t colonne1, size_t colonne2)
{
    for (int i = 0; i < taille; i++)
    {
        int8_t temp = grille[colonne1][i];
        grille[colonne1][i] = grille[colonne2][i];
        grille[colonne2][i] = temp;
    }
}

uint8_t** grilleCloner(uint8_t ** grille, size_t taille){
    uint8_t ** retour = malloc(taille * sizeof(uint8_t*));

    for(int i = 0; i < taille; i++)
    {
        retour[i] = malloc(taille*sizeof(uint8_t));
    }

    for(int i = 0; i < taille; i++){
        for(int j = 0; j < taille; j++){
            retour[i][j] = grille[i][j];
        }
    }

    return retour;
}

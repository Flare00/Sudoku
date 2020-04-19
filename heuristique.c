#include "heuristique.h"

size_t heuristiqueFacile(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map)
{
    uint8_t modifier = 1;
    while (modifier > 0)
    {
        modifier = 0;
        modifier += heuristiqueSingletonVisible(grille, n, liste, map);
    }

    return listeNbElement(liste) - 1;
}

size_t heuristiqueMoyenne(uint8_t **grille, size_t n, Liste *liste , uint8_t ** map)
{
    uint8_t modifier = 1;

    //tant que l'algorithme heuristique modifie les cases restante, alors continu.
    while (modifier > 0)
    {
        modifier = 0;
        modifier += heuristiqueJumeauANVisible(grille, n, liste, map);
        modifier += heuristiqueSingletonCacher(grille, n, liste, map);
        //modifier += heuristiqueCandidatsIdentique(grille, n, bbL, bbC, bbB, liste);
    }

    return heuristiqueFacile(grille, n, liste, map);
}

size_t heuristiqueDifficile(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, Liste *liste, uint8_t ** map)
{
    return 0;
    uint8_t modifier = 1;

    //tant que l'algorithme heuristique modifie les cases restante, alors continu.
    while (modifier > 0)
    {
        modifier = 0;
        modifier += heuristiqueGroupesIsoler(grille, n, bbL, bbC, bbB, liste);
        modifier += heuristiqueGroupesMelanger(grille, n, bbL, bbC, bbB, liste);
    }

    if (heuristiqueFacile(grille, n, liste , map) > 0)
    {
        return heuristiqueMoyenne(grille, n, liste, map);
    }
    else
    {
        return 0;
    }
}

uint8_t heuristiqueSingletonVisible(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map){
    uint8_t retour = 0;
    uint8_t aUpdate = 0;
    Liste * temp = NULL;
    Liste * first = liste->suivante;
    int t = 0;

    while(first != NULL){
        uint64_t c = first->candidats;
        if(__builtin_popcountll(c) == 1){
            retour = 1;

            Liste * seconde = liste->suivante;

            grille[first->i][first->j] = 1+__builtin_ctz(c);
            seconde = liste->suivante;
            while(seconde != NULL){
                if(!(seconde->i == first->i && seconde->j == first->j)){
                    if(seconde->i == first->i || seconde->j == first->j || map[seconde->i][seconde->j] == map[first->i][first->j]){
                        seconde->candidats = seconde->candidats & ~c;
                    }
                }
                seconde = seconde->suivante;
            }

            temp = first->precedente;
            temp->suivante = first->suivante;
            temp = first->suivante;
            if(first->suivante != NULL){
                temp->precedente = first->precedente;
            }
            free(first);
            first = temp;
        } else {
            first = first->suivante;
        }
    }
    return retour;
}
uint8_t heuristiqueSingletonCacher(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map){
    uint8_t retour = 0;
    uint8_t aUpdate = 0;
    Liste * temp = NULL;
    Liste * first = liste->suivante;
    int t = 0;

    while(first != NULL){
        uint64_t c = first->candidats;

        Liste * seconde = liste->suivante;
        while(seconde != NULL){
            if(!(seconde->i == first->i && seconde->j == first->j)){
                if(map[seconde->i][seconde->j] == map[first->i][first->j]){
                    c = c & ~seconde->candidats;
                }
            }
            seconde = seconde->suivante;
        }    

        if(__builtin_popcountll(c) == 1){
            retour = 1;

            Liste * seconde = liste->suivante;

            grille[first->i][first->j] = 1+__builtin_ctz(c);
            seconde = liste->suivante;
            while(seconde != NULL){
                if(!(seconde->i == first->i && seconde->j == first->j)){
                    if(seconde->i == first->i || seconde->j == first->j || map[seconde->i][seconde->j] == map[first->i][first->j]){
                        seconde->candidats = seconde->candidats & ~c;
                    }
                }
                seconde = seconde->suivante;
            }

            temp = first->precedente;
            temp->suivante = first->suivante;
            temp = first->suivante;
            if(first->suivante != NULL){
                temp->precedente = first->precedente;
            }
            free(first);
            first = temp;
            aUpdate = 0;
        } else {
            first = first->suivante;
        }
    }
    return retour;
}

uint8_t heuristiqueSingleton(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map){
    uint8_t retour = 0;
    uint8_t aUpdate = 0;
    Liste * temp = NULL;
    Liste * first = liste->suivante;
    int t = 0;

    while(first != NULL){
        uint64_t c = first->candidats;
        if(__builtin_popcountll(c) == 1){
            aUpdate = 1;
            
        } else {
            Liste * seconde = liste->suivante;
            while(seconde != NULL){
                if(!(seconde->i == first->i && seconde->j == first->j)){
                    if(map[seconde->i][seconde->j] == map[first->i][first->j]){
                        c = c & ~seconde->candidats;
                    }
                }
                seconde = seconde->suivante;
            }



            if(__builtin_popcountll(c) == 1){
                aUpdate = 1;
            } else {
                c = 0;
            }
        }

        if(aUpdate == 1){
            retour = 1;

            Liste * seconde = liste->suivante;

            grille[first->i][first->j] = 1+__builtin_ctz(c);
            seconde = liste->suivante;
            while(seconde != NULL){
                if(!(seconde->i == first->i && seconde->j == first->j)){
                    if(seconde->i == first->i || seconde->j == first->j || map[seconde->i][seconde->j] == map[first->i][first->j]){
                        seconde->candidats = seconde->candidats & ~c;
                    }
                }
                seconde = seconde->suivante;
            }

            temp = first->precedente;
            temp->suivante = first->suivante;
            temp = first->suivante;
            if(first->suivante != NULL){
                temp->precedente = first->precedente;
            }
            free(first);
            first = temp;
            aUpdate = 0;
        } else {
            first = first->suivante;
        }
    }
    return retour;
}

uint8_t heuristiqueJumeauANVisible(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map){
    uint8_t retour = 0;
    size_t taille = n*n;
    uint64_t mask = (1 << taille) - 1;
    Liste * temp;

    for(int bloc = 0; bloc < taille; bloc++){
        temp = liste->suivante;
        uint64_t *mbbBL = calloc(n,sizeof(uint64_t));
        uint64_t *ubbBL = calloc(n,sizeof(uint64_t));
        uint64_t *mbbBC = calloc(n,sizeof(uint64_t));
        uint64_t *ubbBC = calloc(n,sizeof(uint64_t));
        while(temp != NULL){
            if(bloc == 2){}
            if(map[temp->i][temp->j] == bloc){
                ubbBL[temp->i%n] = mask & (ubbBL[temp->i%n] ^ (temp->candidats & ~mbbBL[temp->i%n]));
                mbbBL[temp->i%n] = mask & (mbbBL[temp->i%n] | (temp->candidats & ~ubbBL[temp->i%n]));
                ubbBC[temp->j%n] = mask & (ubbBC[temp->j%n] ^ (temp->candidats & ~mbbBC[temp->j%n]));
                mbbBC[temp->j%n] = mask & (mbbBC[temp->j%n] | (temp->candidats & ~ubbBC[temp->j%n]));
            }
            temp = temp->suivante;
        }
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                    uint64_t tempL = ~(ubbBL[i] | mbbBL[i]);
                    uint64_t tempC = ~(ubbBC[i] | mbbBC[i]);  
                    mbbBL[i] = mbbBL[i] & ~(ubbBL[j] | mbbBL[j]);
                    mbbBL[j] = mbbBL[j] & tempL;
                    mbbBC[i] = mbbBC[i] & ~(ubbBC[j] | mbbBC[j]);
                    mbbBC[j] = mbbBC[j] & tempC;
            }
        }
        
        temp = liste->suivante;
        while(temp != NULL){ 
            if(map[temp->i][temp->j] != bloc){
                if((temp->i > (bloc/n)*n) && (temp->i < ((bloc/n)*n) + n) && (mbbBL[temp->i%n] > 0) && (temp->candidats & ~mbbBL[temp->i%n]) != temp->candidats){
                    retour = 1;
                    temp->candidats = mask & temp->candidats & ~mbbBL[temp->i%n];
                }
                if((temp->j > (bloc%n)*n) && (temp->j < ((bloc%n)*n) + n) && (mbbBC[temp->j%n] > 0) && (temp->candidats & ~mbbBC[temp->j%n]) != temp->candidats){
                    retour = 1;
                    temp->candidats = mask & temp->candidats & ~mbbBC[temp->j%n];
                }
            }
            temp = temp->suivante;
        }
        free(mbbBL);
        free(ubbBL);
        free(mbbBC);
        free(ubbBC);
    }
    return retour;
}


uint8_t heuristiqueGroupesIsoler(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, Liste *liste)
{
    size_t retour = 0;
    size_t taille = n * n;
    //matrice 2:Taille permettant de stocker pour chaque ligne/colonne, en [0] : les candidats a supprimé, en [1] les cases à ignoré.
    uint64_t **pourSuppressionLigne = malloc(taille * sizeof(uint64_t *));
    uint64_t **pourSuppressionColonne = malloc(taille * sizeof(uint64_t *));
    Liste *temp = NULL;
    for (int i = 0; i < taille; i++)
    {
        pourSuppressionLigne[i] = malloc(2 * sizeof(uint64_t));
        pourSuppressionColonne[i] = malloc(2 * sizeof(uint64_t));
    }

    //Nous devons regarder Ligne par ligne / colonne par colonne, nous pouvons scruter les deux en même temps.
    //Nous devons trouvé sur une même ligne, qu'importe le positionnement, au moins une case comportant N candidats (exemple 1,3,7)
    //et N-1 autre cases comportant une partie d'eux  ou la totalité (1,3,7 ou 1,3 ou 1,7 ou 3,7)
    //Ils sont isolé, donc il ne peuvent avoir que eux en candidats.
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            //A FAIRE
        }
    }

    //Supprime sur les cases selectionné les candidats.
    retour = ligneColonneCandidatsSupprimer(taille, pourSuppressionLigne, pourSuppressionColonne, liste, 0);

    for (int i = 0; i < taille; i++)
    {
        free(pourSuppressionLigne[i]);
        free(pourSuppressionColonne[i]);
    }
    free(pourSuppressionLigne);
    free(pourSuppressionColonne);
    return retour;
}

uint8_t heuristiqueGroupesMelanger(uint8_t **grille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, Liste *liste)
{
    size_t retour = 0;
    size_t taille = n * n;
    //matrice 2:Taille permettant de stocker pour chaque ligne/colonne, en [0] : les candidats a supprimé, en [1] les cases à supprimé.
    uint64_t **pourSuppressionLigne = malloc(taille * sizeof(uint64_t *));
    uint64_t **pourSuppressionColonne = malloc(taille * sizeof(uint64_t *));
    Liste *temp = NULL;
    for (int i = 0; i < taille; i++)
    {
        pourSuppressionLigne[i] = malloc(2 * sizeof(uint64_t));
        pourSuppressionColonne[i] = malloc(2 * sizeof(uint64_t));
    }

    //Nous devons regarder Ligne par ligne / colonne par colonne, nous pouvons scruter les deux en même temps.
    //Nous devons trouvé sur une même ligne, qu'importe le positionnement, au moins une case comportant N candidats (exemple 1,3,7) (et d'autre candidats annexe)
    // et N-1 autre cases comportant une partie d'eux ou la totalité (1,3,7 ou 1,3 ou 1,7 ou 3,7) (et d'autre candidats annexe)
    //Ils sont mélangé, il peut y avoir plusieurs candidats parasite.
    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            //A FAIRE
        }
    }

    retour = ligneColonneCandidatsSupprimer(taille, pourSuppressionLigne, pourSuppressionColonne, liste, 1);

    for (int i = 0; i < taille; i++)
    {
        free(pourSuppressionLigne[i]);
        free(pourSuppressionColonne[i]);
    }
    free(pourSuppressionLigne);
    free(pourSuppressionColonne);
    return retour;
}

uint8_t ligneColonneCandidatsSupprimer(uint8_t taille, uint64_t **pourSuppressionLigne, uint64_t **pourSuppressionColonne, Liste *liste, uint8_t mode)
{
    Liste *temp = NULL;
    uint8_t retour = 0;
    for (int i = 0; i < taille; i++)
    {
        temp = liste;
        if (pourSuppressionLigne[i][0] != 0 || pourSuppressionColonne[i][0] != 0)
        {
            while (temp != NULL)
            {
                //Si il y as des candidats et la coordonnée i correspond a la ligne vérifié alors
                if (pourSuppressionLigne[i][0] != 0 && temp->i == i)
                {
                    //Si la coordonnée J ne correspond pas a une des colonnes à évité, donc supprime les candidats.
                    if (mode == 0)
                    {
                        //Si la coordonnée J correspond à la case à supprimer, supprime les candidats selectionné de celle-ci.
                        if ((1 << temp->j & pourSuppressionLigne[i][1]) == 0)
                        {
                            temp->candidats = temp->candidats & ~pourSuppressionLigne[i][0];
                            temp->population = __builtin_popcount(temp->candidats);
                            retour = 1;
                        }
                    }
                    else if (mode == 1)
                    {
                        //Si la coordonnée J correspond à la case à supprimer, supprime les candidats non selectionné.
                        if ((1 << temp->j & pourSuppressionLigne[i][1]) == 1)
                        {
                            temp->candidats = temp->candidats & pourSuppressionLigne[i][0];
                            temp->population = __builtin_popcount(temp->candidats);
                            retour = 1;
                        }
                    }
                }
                //Si il y as des candidats et la coordonnée i correspond a la ligne vérifié alors
                if (pourSuppressionColonne[i][0] != 0 && temp->j == i)
                {
                    if (mode == 0)
                    {
                        //Si la coordonnée I correspond à la case à supprimer, supprime les candidats selectionné de celle-ci.
                        if ((1 << temp->i & pourSuppressionColonne[i][1]) == 0)
                        {

                            temp->candidats = temp->candidats & ~pourSuppressionColonne[i][0];
                            temp->population = __builtin_popcount(temp->candidats);

                            retour = 1;
                        }
                    }

                    else if (mode == 1)
                    {
                        //Si la coordonnée I correspond a la case a supprimer, supprime les candidats non selectionné.
                        if ((1 << temp->i & pourSuppressionColonne[i][1]) == 1)
                        {
                            temp->candidats = temp->candidats & pourSuppressionColonne[i][0];
                            temp->population = __builtin_popcount(temp->candidats);
                            retour = 1;
                        }
                    }
                }
                temp = temp->suivante;
            }
        }
    }
}


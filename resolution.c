#include "resolution.h"

void heuristiqueUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map)
{
    Liste* liste = listeCreerUniqueCandidat(n, bbL, bbC, bbB, grille, map);

    if(liste == NULL) return;
    size_t indice;
    while(liste)
    {
        indice = __builtin_ctz(liste->candidats);
        grille[liste->i][liste->j]=1+indice;
        bbL[liste->i] |= (uint64_t)(1<<indice);
        bbC[liste->j] |= (uint64_t)(1<<indice);
        bbB[map[liste->i][liste->j]] |= (uint64_t)(1<<indice);
        listeDetruireTete(&liste);
    }
    heuristiqueUniqueCandidat(n, bbL, bbC, bbB, grille, map);
}

void heuristiqueUniqueCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille, uint8_t** map)
{
    Liste32* liste = listeCreerUniqueCandidat32(n, bbL, bbC, bbB, grille, map);

    if(liste == NULL) return;
    size_t indice;
    while(liste)
    {
        indice = __builtin_ctz(liste->candidats);
        grille[liste->i][liste->j]=1+indice;
        bbL[liste->i] |= (uint32_t)(1<<indice);
        bbC[liste->j] |= (uint32_t)(1<<indice);
        bbB[map[liste->i][liste->j]] |= (uint32_t)(1<<indice);
        listeDetruireTete32(&liste);
    }
    heuristiqueUniqueCandidat32(n, bbL, bbC, bbB, grille, map);
}

void heuristiquePaireCachee(size_t taille,Liste *dl,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t**map)
{
    Liste * sl = dl;
    Liste * al = dl;
    while(sl!=NULL)
    {
        al=dl;
        size_t i,j,b;
        i = sl->i;
        j=sl->j;
        b=map[sl->i][sl->j];
        int pop = sl->population;
        uint64_t candidats = sl->candidats;

        uint64_t mask = (1<<taille)-1;


        while(al!=NULL)
        {
            if(pop==al->population && al->population==2 && (al->i == i||al->j==j||map[al->i][al->j]==b) && candidats==al->candidats)
            {

                if(al->i == i && al->j!=j&&map[al->i][al->j]!=b)
                {

                   bbC[al->i]|=mask&candidats;
                   bbB[map[al->i][al->j]]|=mask&candidats;
                }

                if(al->i != i && al->j==j && map[al->i][al->j]!=b)
                {

                   bbL[i]|=mask&candidats;
                   bbB[b]|=mask&candidats;
                }
                if(al->i != i && al->j!=j&&map[al->i][al->j]==b)
                {

                   bbL[i]|=mask&candidats;
                   bbC[j]|=mask&candidats;

                }
            }
                al=al->suivante;
        }
        sl=sl->suivante;
    }
}

void heuristiquePaireCachee32(size_t taille,Liste32 *dl,uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t**map)
{
    Liste32 * sl = dl;
    Liste32 * al = dl;
    while(sl!=NULL)
    {
        al=dl;
        size_t i,j,b;
        i = sl->i;
        j=sl->j;
        b=map[sl->i][sl->j];
        int pop = sl->population;
        uint32_t candidats = sl->candidats;

        uint32_t mask = (1<<taille)-1;


        while(al!=NULL)
        {
            if(pop==al->population && al->population==2 && (al->i == i||al->j==j||map[al->i][al->j]==b) && candidats==al->candidats)
            {

                if(al->i == i && al->j!=j&&map[al->i][al->j]!=b)
                {

                   bbC[al->i]|=mask&candidats;
                   bbB[map[al->i][al->j]]|=mask&candidats;
                }

                if(al->i != i && al->j==j && map[al->i][al->j]!=b)
                {

                   bbL[i]|=mask&candidats;
                   bbB[b]|=mask&candidats;
                }
                if(al->i != i && al->j!=j&&map[al->i][al->j]==b)
                {

                   bbL[i]|=mask&candidats;
                   bbC[j]|=mask&candidats;

                }
            }
                al=al->suivante;
        }
        sl=sl->suivante;
    }
}

bool heuristiqueSolo(Liste **liste, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t **map, uint8_t **grille){
    bool resultat = ((*liste) != NULL && (*liste)->population == 1);

    while(*liste && (*liste)->population == 1){
        uint64_t mask = (uint64_t)(1<<__builtin_ctz((*liste)->candidats));
        uint64_t inver = (uint64_t)(~mask);
        grille[(*liste)->i][(*liste)->j] = ((*liste)->c[0])+1;
        bbL[(*liste)->i] |= (uint64_t)mask;
        bbC[(*liste)->j] |= (uint64_t)mask;
        bbB[map[(*liste)->i][(*liste)->i]] |= (uint64_t)mask;

        Liste *courante = listeRechercherMinXPopulation(liste, 2); //à partir de deux candidats...
        while(courante){
            if(courante->i == (*liste)->i || courante->j == (*liste)->j || map[courante->i][courante->j] == map[(*liste)->i][(*liste)->j]){
                if(courante->candidats&mask){
                    courante->population--;
                    courante->candidats &= inver;
                    
                    listeRedefinirC(&courante);

                    if(courante->precedente && courante->population<courante->precedente->population){
                        Liste *tmp = courante;
                        while(tmp->precedente && courante->population<tmp->precedente->population){
                            tmp = tmp->precedente;
                        }
                        listeDeplacerAvant(&tmp, &courante);
                    }
                }
            }
            courante = courante->suivante;
        }
        listeDetruireTete(liste);
    }

    return resultat;
}

bool heuristiqueSolo32(Liste32 **liste, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t **map, uint8_t **grille){
    bool resultat = ((*liste) != NULL && (*liste)->population == 1);

    while(*liste && (*liste)->population == 1){
        uint32_t mask = (uint32_t)(1<<__builtin_ctz((*liste)->candidats));
        uint32_t inver = (uint32_t)(~mask);
        grille[(*liste)->i][(*liste)->j] = ((*liste)->c[0])+1;
        bbL[(*liste)->i] |= (uint32_t)mask;
        bbC[(*liste)->j] |= (uint32_t)mask;
        bbB[map[(*liste)->i][(*liste)->i]] |= (uint32_t)mask;

        Liste32 *courante = listeRechercherMinXPopulation32(liste, 2); //à partir de deux candidats...
        while(courante){
            if(courante->i == (*liste)->i || courante->j == (*liste)->j || map[courante->i][courante->j] == map[(*liste)->i][(*liste)->j]){
                if(courante->candidats&mask){
                    courante->population--;
                    courante->candidats &= inver;
                    
                    listeRedefinirC32(&courante);

                    if(courante->precedente && courante->population<courante->precedente->population){
                        Liste32 *tmp = courante;
                        while(tmp->precedente && courante->population<tmp->precedente->population){
                            tmp = tmp->precedente;
                        }
                        listeDeplacerAvant32(&tmp, &courante);
                    }
                }
            }
            courante = courante->suivante;
        }
        listeDetruireTete32(liste);
    }

    return resultat;
}

bool heuristiquePaireNue(Liste **liste, uint8_t **map){
    Liste *checkPoint = listeRechercherDebutXPopulation(liste, 2); // Première occurence de la liste avec population de 2 ; NULL sinon
    Liste *cpL1 = NULL, *cpL2 = NULL, *courante = checkPoint;
    bool resultat = false;
    while(courante && courante->population == 2){/*analyser chaque élément de la liste*/
            uint64_t inver = (uint64_t)(~(courante->candidats));
            uint64_t cand1 = courante->candidats;
            uint64_t mask1 = (uint64_t)(1<<__builtin_ctz(cand1));
            cand1 ^= mask1;
            uint64_t mask2 = (uint64_t)(1<<__builtin_ctz(cand1));

            cpL1 = checkPoint; 
            while(cpL1 && cpL1->population == 2){
                if(cpL1 != courante && cpL1->candidats == courante->candidats){/*vérifier si un autre élément de même*/
                    if(cpL1->i == courante->i){/*ligne*/
                        cpL2 = checkPoint; 
                        while(cpL2){
                            Liste *cpL2Suiv = cpL2->suivante;
                            if(cpL2 != courante && cpL2 != cpL1 && cpL2->i == courante->i){
                                resultat = true;
                                if(cpL2->candidats&mask1)
                                    cpL2->population--;
                                if(cpL2->candidats&mask2)
                                    cpL2->population--;

                                cpL2->candidats &= inver;
                                listeRedefinirC(&cpL2);
                                if(cpL2->precedente && cpL2->population<cpL2->precedente->population){
                                    Liste *tmp = cpL2;
                                    while(tmp->precedente && cpL2->population<tmp->precedente->population){
                                        tmp = tmp->precedente;
                                    }
                                    listeDeplacerAvant(&tmp, &cpL2);
                                }
                            }
                            cpL2 = cpL2Suiv;
                        }                   
                    }
                    if(cpL1->j == courante->j){/*colonne*/
                        cpL2 = checkPoint;
                        while(cpL2){
                            Liste *cpL2Suiv = cpL2->suivante;
                            if(cpL2 != courante && cpL2 != cpL1 && cpL2->j == courante->j){
                                resultat = true;
                                if(cpL2->candidats&mask1)
                                    cpL2->population--;
                                if(cpL2->candidats&mask2)
                                    cpL2->population--;

                                cpL2->candidats &= inver;
                                listeRedefinirC(&cpL2);
                                if(cpL2->precedente && cpL2->population<cpL2->precedente->population){
                                    Liste *tmp = cpL2;
                                    while(tmp->precedente && cpL2->population<tmp->precedente->population){
                                        tmp = tmp->precedente;
                                    }
                                    listeDeplacerAvant(&tmp, &cpL2);
                                }
                            }
                            cpL2 = cpL2Suiv;
                        }   
                    }
                    if(map[cpL1->i][cpL1->j] == map[courante->i][courante->j]){/*ou block a identiquement les mêmes candidats... Modifier la/les zones concernées*/
                        cpL2 = checkPoint;
                        while(cpL2){
                            Liste *cpL2Suiv = cpL2->suivante;
                            if(cpL2 != courante && cpL2 != cpL1 && map[cpL2->i][cpL2->j] == map[courante->i][courante->j]){
                                resultat = true;
                                if(cpL2->candidats&mask1)
                                    cpL2->population--;
                                if(cpL2->candidats&mask2)
                                    cpL2->population--;

                                cpL2->candidats &= inver;
                                listeRedefinirC(&cpL2);
                                if(cpL2->precedente && cpL2->population<cpL2->precedente->population){
                                    Liste *tmp = cpL2;
                                    while(tmp->precedente && cpL2->population<tmp->precedente->population){
                                        tmp = tmp->precedente;
                                    }
                                    listeDeplacerAvant(&tmp, &cpL2);
                                }
                            }
                            cpL2 = cpL2Suiv;
                        }   
                    }
                }
                cpL1 = cpL1->suivante;
            }
        courante = courante->suivante;
    }

    return resultat;
}

bool heuristiquePaireNue32(Liste32 **liste, uint8_t **map){
    Liste32 *checkPoint = listeRechercherDebutXPopulation32(liste, 2); // Première occurence de la liste avec population de 2 ; NULL sinon
    Liste32 *cpL1 = NULL, *cpL2 = NULL, *courante = checkPoint;
    bool resultat = false;
    while(courante && courante->population == 2){/*analyser chaque élément de la liste*/
            uint32_t inver = (uint32_t)(~(courante->candidats));
            uint32_t cand1 = courante->candidats;
            uint32_t mask1 = (uint32_t)(1<<__builtin_ctz(cand1));
            cand1 ^= mask1;
            uint32_t mask2 = (uint32_t)(1<<__builtin_ctz(cand1));

            cpL1 = checkPoint; 
            while(cpL1 && cpL1->population == 2){
                if(cpL1 != courante && cpL1->candidats == courante->candidats){/*vérifier si un autre élément de même*/
                    if(cpL1->i == courante->i){/*ligne*/
                        cpL2 = checkPoint; 
                        while(cpL2){
                            Liste32 *cpL2Suiv = cpL2->suivante;
                            if(cpL2 != courante && cpL2 != cpL1 && cpL2->i == courante->i){
                                resultat = true;
                                if(cpL2->candidats&mask1)
                                    cpL2->population--;
                                if(cpL2->candidats&mask2)
                                    cpL2->population--;

                                cpL2->candidats &= inver;
                                listeRedefinirC32(&cpL2);
                                if(cpL2->precedente && cpL2->population<cpL2->precedente->population){
                                    Liste32 *tmp = cpL2;
                                    while(tmp->precedente && cpL2->population<tmp->precedente->population){
                                        tmp = tmp->precedente;
                                    }
                                    listeDeplacerAvant32(&tmp, &cpL2);
                                }
                            }
                            cpL2 = cpL2Suiv;
                        }                   
                    }
                    if(cpL1->j == courante->j){/*colonne*/
                        cpL2 = checkPoint;
                        while(cpL2){
                            Liste32 *cpL2Suiv = cpL2->suivante;
                            if(cpL2 != courante && cpL2 != cpL1 && cpL2->j == courante->j){
                                resultat = true;
                                if(cpL2->candidats&mask1)
                                    cpL2->population--;
                                if(cpL2->candidats&mask2)
                                    cpL2->population--;

                                cpL2->candidats &= inver;
                                listeRedefinirC32(&cpL2);
                                if(cpL2->precedente && cpL2->population<cpL2->precedente->population){
                                    Liste32 *tmp = cpL2;
                                    while(tmp->precedente && cpL2->population<tmp->precedente->population){
                                        tmp = tmp->precedente;
                                    }
                                    listeDeplacerAvant32(&tmp, &cpL2);
                                }
                            }
                            cpL2 = cpL2Suiv;
                        }   
                    }
                    if(map[cpL1->i][cpL1->j] == map[courante->i][courante->j]){/*ou block a identiquement les mêmes candidats... Modifier la/les zones concernées*/
                        cpL2 = checkPoint;
                        while(cpL2){
                            Liste32 *cpL2Suiv = cpL2->suivante;
                            if(cpL2 != courante && cpL2 != cpL1 && map[cpL2->i][cpL2->j] == map[courante->i][courante->j]){
                                resultat = true;
                                if(cpL2->candidats&mask1)
                                    cpL2->population--;
                                if(cpL2->candidats&mask2)
                                    cpL2->population--;

                                cpL2->candidats &= inver;
                                listeRedefinirC32(&cpL2);
                                if(cpL2->precedente && cpL2->population<cpL2->precedente->population){
                                    Liste32 *tmp = cpL2;
                                    while(tmp->precedente && cpL2->population<tmp->precedente->population){
                                        tmp = tmp->precedente;
                                    }
                                    listeDeplacerAvant32(&tmp, &cpL2);
                                }
                            }
                            cpL2 = cpL2Suiv;
                        }   
                    }
                }
                cpL1 = cpL1->suivante;
            }
        courante = courante->suivante;
    }

    return resultat;
}

bool resoudreRecursivement(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map)
{
    if(!dl)
        return true;
    size_t k, i = dl->i, j= dl->j, b = map[i][j];
    for(k = 0 ; k < dl->population ; k++)
    {

        size_t indice1 = dl->c[k];
        uint8_t val = indice1+1;
        uint64_t bitVal = (uint64_t)1<<indice1;

       if(!(( (bbL[i] | bbC[j] | bbB[b])>>indice1)&1))
        {
            grille[i][j] = val;
            bbL[i] |= bitVal;
            bbC[j] |= bitVal;
            bbB[b] |= bitVal;
            if(resoudreRecursivement(grille, dl->suivante, bbL, bbC, bbB,map))
			{
				return true;
			}
        }
    }
    if(dl->precedente)
    {
        size_t bi =dl->precedente->i , bj = dl->precedente->j;
        uint64_t bitVal2 = (uint64_t)(1<<(grille[bi][bj]-1));
        bbL[bi] ^= bitVal2;
        bbC[bj] ^= bitVal2;
        bbB[map[bi][bj]] ^= bitVal2;
    }
    grille[i][j] = 0;
    return false;
}

bool resoudreRecursivement32(uint8_t** grille, Liste32 *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t **map)
{
    if(!dl)
        return true;
    size_t k, i = dl->i, j= dl->j, b = map[i][j];
    for(k = 0 ; k < dl->population ; k++)
    {

        size_t indice1 = dl->c[k];
        uint8_t val = indice1+1;
        uint32_t bitVal = (uint32_t)(1<<indice1);

       if(!(( (bbL[i] | bbC[j] | bbB[b])>>indice1)&1))
        {
            grille[i][j] = val;
            bbL[i] |= bitVal;
            bbC[j] |= bitVal;
            bbB[b] |= bitVal;
            if(resoudreRecursivement32(grille, dl->suivante, bbL, bbC, bbB,map))
            {
                return true;
            }
        }
    }
    if(dl->precedente)
    {
        size_t bi =dl->precedente->i , bj = dl->precedente->j;
        uint32_t bitVal2 = (uint32_t)(1<<(grille[bi][bj]-1));
        bbL[bi] ^= bitVal2;
        bbC[bj] ^= bitVal2;
        bbB[map[bi][bj]] ^= bitVal2;
    }
    grille[i][j] = 0;
    return false;
}

int resolu_64(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map, int count, int pi, int pj)
{
    if(!dl){
        return 1;
    }

    size_t k, i = dl->i, j= dl->j, b = map[i][j];
    uint8_t val, indice1;
    uint32_t bitVal;

        for(k = 0 ; k < dl->population ; k++)
        {

            indice1 = dl->c[k];
            val = indice1+1;
            bitVal = (uint64_t)(1<<indice1);

           if((val && !(( (bbL[i] | bbC[j] | bbB[b])>>indice1)&1) ) )
            {
                grille[i][j] = val;
                bbL[i] |= bitVal;
                bbC[j] |= bitVal;
                bbB[b] |= bitVal;

                if(resolu_64(grille, dl->suivante, bbL, bbC, bbB,map,count, pi,pj))
                {

                   count++;
                   if(k == dl->population-1 && i==pi &&j==pj)
                        return count;
                }

            }

        }

    size_t bi =dl->precedente->i , bj = dl->precedente->j;
    uint8_t indice2 = grille[bi][bj]-1;
    uint32_t bitVal2 = (uint64_t)(1<<indice2);
    bbL[bi] ^= bitVal2;
    bbC[bj] ^= bitVal2;
    bbB[map[bi][bj]] ^= bitVal2;

    return count;
}

int resolu_32(uint8_t** grille, Liste *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t **map, int count, int pi, int pj)
{
    if(!dl){
        return 1;
    }

    size_t k, i = dl->i, j= dl->j, b = map[i][j];
    uint8_t val, indice1;
    uint32_t bitVal;

        for(k = 0 ; k < dl->population ; k++)
        {

            indice1 = dl->c[k];
            val = indice1+1;
            bitVal = (uint32_t)(1<<indice1);

           if((val && !(( (bbL[i] | bbC[j] | bbB[b])>>indice1)&1) ) )
            {
                grille[i][j] = val;
                bbL[i] |= bitVal;
                bbC[j] |= bitVal;
                bbB[b] |= bitVal;

                if(resolu_32(grille, dl->suivante, bbL, bbC, bbB,map,count, pi,pj))
                {

                   count++;
                   if(k == dl->population-1 && i==pi &&j==pj)
                        return count;
                }

            }

        }

    size_t bi =dl->precedente->i , bj = dl->precedente->j;
    uint8_t indice2 = grille[bi][bj]-1;
    uint32_t bitVal2 = (uint32_t)(1<<indice2);
    bbL[bi] ^= bitVal2;
    bbC[bj] ^= bitVal2;
    bbB[map[bi][bj]] ^= bitVal2;

    return count;
}

bool resoudre(uint8_t *entree, size_t n)
{
    size_t taille = n*n;
    uint8_t **map = mapCreer(n);
    if(!map) return false;
    uint8_t **grille = grilleCreer(entree, taille);
    if(!grille) return false;
    bool resultat = true;
    if(n < 6)
    {
        uint32_t* bbL = bitboard32Creer(taille);
        uint32_t* bbC = bitboard32Creer(taille);
        uint32_t* bbB = bitboard32Creer(taille);

        if(!bitBoardInitialiser32(grille, n, bbL, bbC, bbB)){
            resultat = false;
        }
        else{
            Liste32 *liste = listeRechercherCandidat32(n, bbL, bbC, bbB, grille, map);

            //réduction du nombre de candidats dans la liste
            bool c1, c2, c3 = true;
            while(c3){
                c1 = heuristiqueSolo32(&liste, bbL, bbC, bbB, map, grille);
                c2 = heuristiquePaireNue32(&liste, map);
                c3 = c1 || c2;
            }

            if(!resoudreRecursivement32(grille, liste, bbL, bbC, bbB, map)){
                resultat = false;
            }
            else
                for (size_t i = 0; i < taille; i++)
                {
                    size_t tmpI = i*taille;
                    for (size_t j = 0; j < taille; j++)
                    {
                        entree[tmpI+j] = grille[i][j];
                    }
                }

            bitBoardDetruire32(bbL);
            bitBoardDetruire32(bbC);
            bitBoardDetruire32(bbB);
            listeDetruire32(liste);
        }
    }
    else{
        uint64_t* bbL = bitboard64Creer(taille);
        uint64_t* bbC = bitboard64Creer(taille);
        uint64_t* bbB = bitboard64Creer(taille);

        if(!bitBoardInitialiser(grille, n, bbL, bbC, bbB)){
            resultat = false;
        }
        else{
            Liste *liste = listeRechercherCandidat(n, bbL, bbC, bbB, grille, map);

            bool c1, c2, c3 = true;
            while(c3){
                c1 = heuristiqueSolo(&liste, bbL, bbC, bbB, map, grille);
                c2 = heuristiquePaireNue(&liste, map);
                c3 = c1 || c2;
            }

            if(!resoudreRecursivement(grille, liste, bbL, bbC, bbB, map))
                resultat = false;
            else
                for (size_t i = 0; i < taille; i++)
                {
                    size_t tmpI = i*taille;
                    for (size_t j = 0; j < taille; j++)
                    {
                        entree[tmpI+j] = grille[i][j];
                    }
                }

            bitBoardDetruire(bbL);
            bitBoardDetruire(bbC);
            bitBoardDetruire(bbB);
            listeDetruire(liste);
        }
    }

    detruire2D(grille, taille);
    detruire2D(map, taille);
    return resultat;
}

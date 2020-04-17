#include "resolution.h"

Liste* ajouterEnTete(Liste *liste, uint64_t candidats, size_t i, size_t j)
{
    Liste *elem = malloc(sizeof(Liste));
    if(!elem)
    {
        listeDetruire(liste);
        return NULL;
    }
    elem->c = NULL;
    elem->candidats = candidats;
    elem->population = 1;
    elem->i=i;
    elem->j=j;
    elem->precedente = NULL;
    elem->suivante = liste;

    return elem;
}

Liste32* ajouterEnTete32(Liste32 *liste, uint32_t candidats, size_t i, size_t j)
{
    Liste32 *elem = malloc(sizeof(Liste32));
    if(!elem)
    {
        listeDetruire32(liste);
        return NULL;
    }
    elem->c = NULL;
    elem->candidats = candidats;
    elem->population = 1;
    elem->i=i;
    elem->j=j;
    elem->precedente = NULL;
    elem->suivante = liste;

    return elem;
}

Liste* creerListeUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map)
{
    size_t taille = n*n;
    Liste *liste = NULL;
    uint64_t mask = (1<<taille)-1, cdt;
    for(size_t i = 0; i < taille; i++)
    {
        for(size_t j = 0; j < taille; j++)
        {
            if(!grille[i][j] && __builtin_popcountll((cdt=mask&(~(bbL[i] | bbC[j] | bbB[map[i][j]])))) == 1)
            {
                liste = ajouterEnTete(liste, cdt, i, j);
            }
        }
    }
    return liste;
}

Liste32* creerListeUniqueCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille, uint8_t** map)
{
    size_t taille = n*n;
    Liste32 *liste = NULL;
    uint64_t mask = (1<<taille)-1, cdt;
    for(size_t i = 0; i < taille; i++)
    {
        for(size_t j = 0; j < taille; j++)
        {
            if(!grille[i][j] && __builtin_popcount((cdt=mask&(~(bbL[i] | bbC[j] | bbB[map[i][j]])))) == 1)
            {
                liste = ajouterEnTete32(liste, cdt, i, j);
            }
        }
    }
    return liste;
}

void heuristiqueUniqueCandidat(size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint8_t** grille, uint8_t** map)
{
    Liste* liste = creerListeUniqueCandidat(n, bbL, bbC, bbB, grille, map);

    if(liste == NULL) return;
    size_t indice;
    while(liste)
    {
        indice = __builtin_ctz(liste->candidats);
        grille[liste->i][liste->j]=1+indice;
        bbL[liste->i] |= (1<<indice);
        bbC[liste->j] |= (1<<indice);
        bbB[map[liste->i][liste->j]] |= (1<<indice);
        listeDetruireTete(&liste);
    }
    heuristiqueUniqueCandidat(n, bbL, bbC, bbB, grille, map);
}

void heuristiqueUniqueCandidat32(size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint8_t** grille, uint8_t** map)
{
    Liste32* liste = creerListeUniqueCandidat32(n, bbL, bbC, bbB, grille, map);

    if(liste == NULL) return;
    size_t indice;
    while(liste)
    {
        indice = __builtin_ctz(liste->candidats);
        grille[liste->i][liste->j]=1+indice;
        bbL[liste->i] |= (1<<indice);
        bbC[liste->j] |= (1<<indice);
        bbB[map[liste->i][liste->j]] |= (1<<indice);
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

bool resoudreRecursivement(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map)
{
    if(!dl)
        return true;
    size_t k, i = dl->i, j= dl->j, b = map[i][j];
    for(k = 0 ; k < dl->population ; k++)
    {

        size_t c = dl->c[k];
        uint8_t val = c+1, indice1 = val-1;
        uint64_t bitVal = 1<<indice1;

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
        uint64_t bitVal2 = (1<<(grille[bi][bj]-1));
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

        size_t c = dl->c[k];
        uint8_t val = c+1, indice1 = val-1;
        uint32_t bitVal = 1<<indice1;

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
        uint32_t bitVal2 = (1<<(grille[bi][bj]-1));
        bbL[bi] ^= bitVal2;
        bbC[bj] ^= bitVal2;
        bbB[map[bi][bj]] ^= bitVal2;
    }
    grille[i][j] = 0;
    return false;
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
            /*printf("BitBoard à la phasse d'initialisation : \n");
            afficherTousBitBoard32(taille, bbL, bbC, bbB);*/

            heuristiqueUniqueCandidat32(n, bbL, bbC, bbB, grille, map);
            /*printf("BitBoard après heuristiques unique candidats : \n");
            afficherTousBitBoard32(taille, bbL, bbC, bbB);*/

            Liste32 *liste = rechercherCandidat32(n, bbL, bbC, bbB, grille, map);
            // afficherListe32(liste);

            /*printf("Fin affichage\n");*/
            if(!resoudreRecursivement32(grille, liste, bbL, bbC, bbB, map)){
                /*printf("pas resolu !\n");*/
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
            heuristiqueUniqueCandidat(n, bbL, bbC, bbB, grille, map);

            Liste *liste = rechercherCandidat(n, bbL, bbC, bbB, grille, map);
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

    grilleDetruire(grille, taille);
    mapDetruire(map, taille);
    return resultat;
}
#include "resolution.h"

uint8_t** creerMap(size_t n)
{
    size_t taille = n*n;
    uint8_t **map = malloc(taille * sizeof(uint8_t*));
    if(map != NULL)
    {
        for (size_t i = 0; i < taille; i++)
        {
            map[i] = malloc(taille * sizeof(uint8_t));
        }
    }
    for (size_t i = 0; i < taille; i++)
    {
        for (size_t j = 0; j < taille; j++)
        {
            map[i][j] = block(i,j,n);
        }
    }

    return map;
}

bool insertionValide(uint64_t *bbL, uint64_t *bbC, uint64_t *bbB, uint64_t candidat, uint64_t mask)
{

    if((mask|candidat&*bbL &*bbC &*bbB))
    {
        *bbL|=candidat;
       *bbC|=candidat;
        *bbB|=candidat;

        return true;

    }
    else
        return false;

}
bool insertionValide_32(uint32_t *bbL, uint32_t *bbC, uint32_t *bbB, uint32_t candidat, uint32_t mask)
{

    if((mask|candidat&*bbL &*bbC &*bbB))
    {
        *bbL|=candidat;
       *bbC|=candidat;
        *bbB|=candidat;

        return true;

    }
    else
        return false;

}
void iterativeResolution(size_t taille, size_t n, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t** grille, uint8_t** map,Liste** l1)
{
    uint64_t mask = (1<<taille)-1;
    Liste* lp = (*l1);

	//while(nbElementListe(lp)>250)
    while(lp)
    {
        if(lp->population==1)
        {
             if(insertionValide(&bbL[lp->i],&bbC[lp->j],&bbB[map[lp->i][lp->j]],lp->candidats,mask))
            {
                grille[lp->i][lp->j]=1+lp->c[0];


                (*l1)=rechercheCandidat( taille,  n,bbL, bbC, bbB,grille,map);
                lp = (*l1);

            }

        }
        else
            lp=lp->next;
    }

}
void iterativeResolution_32(size_t taille, size_t n, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t** grille, uint8_t** map,Liste** l1)
{
    uint32_t mask = (1<<taille)-1;
    Liste* lp = (*l1);

	//while(nbElementListe(lp)>250)
    while(lp)
    {
        if(lp->population==1)
        {
             if(insertionValide_32(&bbL[lp->i],&bbC[lp->j],&bbB[map[lp->i][lp->j]],lp->candidats_32,mask))
            {
                grille[lp->i][lp->j]=1+lp->c[0];


                (*l1)=rechercheCandidat_32( taille, bbL, bbC, bbB,grille,map);
                lp = (*l1);

            }
        }
        else
            lp=lp->next;

    }

}
uint64_t *rotationBoard(size_t taille,uint64_t *bb)
{
    uint64_t *c = malloc(taille*sizeof(uint64_t)),x;

    for(size_t i=0 ; i<taille; i++)
    {
        c[i]=0;
    }
    for (size_t i = 0; i < taille; i++){
        for (size_t j = 0; j < taille; j++)
        {
                x=1<<taille-i-1;
                if(bb[j]&x)
                {
                   c[i]|=1<<j;

                }
        }

    }
    printf("\n");
    afficherBitBoard(taille,c);
    printf("\n");
    return c;

}
void trouvehiddenpair(size_t taille,Liste *dl,uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t**map)
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
        uint32_t candidats = sl->candidats_32;

        uint32_t mask = (1<<taille)-1;


        while(al!=NULL)
        {
            if(pop==al->population&&(al->i == i||al->j==j||map[al->i][al->j]==b)&&candidats == al->candidats_32)
            {

                if(al->i == i && al->j!=j&&map[al->i][al->j]!=b)
                {
                  // printf("MATCH L  : pop : %d i : %ld %ld  \n",pop,al->i,i);
                   //printf("MATCH L  : j: %ld %ld b : %ld %d \n",al->j, j, b,map[al->i][al->j]);
                   //afficherBit_32(candidats);
                   bbC[al->i]|=mask&candidats;
                   bbB[map[al->i][al->j]]|=mask&candidats;
                }

                if(al->i =! i && al->j==j&&map[al->i][al->j]!=b)
                {
                   //printf("MATCH C  : pop : %d i : %ld %ld  \n",pop,al->i,i);
                   //printf("MATCH C  : j: %ld %ld b : %ld %d \n",al->j, j, b,map[al->i][al->j]);
                   //afficherBit_32(candidats);
                   bbL[i]|=mask&candidats;
                   bbB[b]|=mask&candidats;
                }
                if(al->i != i && al->j!=j&&map[al->i][al->j]==b)
                {
                   //printf("MATCH B  : pop : %d i : %ld %ld  \n",pop,al->i,i);
                   //printf("MATCH B  : j: %ld %ld b : %ld %d \n",al->j, j, b,map[al->i][al->j]);
                   //afficherBit_32(candidats);
                   bbL[i]|=mask&candidats;
                   bbC[j]|=mask&candidats;

                }
            }
                al=al->next;
        }
        sl=sl->next;
    }
}
bool searchListe (size_t taille,Liste *dl, Liste*dl2,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t** map)
{
    size_t i,j,b;
    i = dl2->i;
    j=dl2->j;
    b=map[dl2->i][dl2->j];
    int pop = dl2->population;
    uint64_t candidats = dl2->candidats;
    bool cont=false;
    uint64_t mask = (1<<taille)-1;

    while(dl!=NULL)
    {
        if(pop==dl->population&&candidats == dl->candidats)
        {

//            afficherBit_64(candidats);
//            printf("\n");
//            afficherBit_64(dl2->candidats);
//            printf("\n");

            if(dl->i == i)
            {
               bbC[j]|=mask&candidats;
               bbB[b]|=mask&candidats;
               dl->candidats^=candidats;

            }
            if(dl->j == j)
            {
               bbL[i]|=mask&candidats;
               bbB[b]|=mask&candidats;
               dl->candidats^=candidats;

            }
            if(map[dl->i][dl->j] == b)
            {
               bbL[i]|=mask&candidats;
               bbC[j]|=mask&candidats;
               dl->candidats^=candidats;

            }


           cont = true;

        }

            dl=dl->next;


    }
    return cont;
}

void trouveCandidatCache(size_t taille,uint8_t** grille,uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map)
{
    uint64_t *rL = malloc(taille*sizeof(uint64_t));
    uint64_t *rC = malloc(taille*sizeof(uint64_t));
    uint64_t *rB = malloc(taille*sizeof(uint64_t));

    uint64_t mask = (1<<taille)-1;

    rL = rotationBoard(taille,bbL);
    rC = rotationBoard(taille,bbC);
    rB = rotationBoard(taille,bbB);
/*

    for(size_t i = 0; i < taille; i++){
        for(size_t j = 0 ; j<taille ;j++)
        {
             if(__builtin_popcountll(mask&(~rL[i]))==__builtin_popcountll(mask&(~rC[j])) ==2)
             {
                bbL[i]|=mask&(~rL[i]);
                bbC[j]|=mask&(~rC[j]);
                bbB[map[i][j]]|=mask&(~rB[map[i][j]]);
             }

        }

    }

*/
}
bool resolu(uint8_t** grille, Liste *dl, uint64_t *bbL, uint64_t *bbC, uint64_t *bbB,uint8_t **map)
{
    if(!dl)
        return true;
    //printf("%ld\n", nbElementListe(dl));
    size_t k,c, i = dl->i, j= dl->j, b = map[i][j];
    uint8_t val, indice1;
    uint64_t bitVal;
    for(k = 0 ; k < dl->population ; k++)
    {

        c = dl->c[k];
        val = c, indice1 = val-1;
        bitVal = 1<<indice1;

       if((val && !(( (bbL[i] | bbC[j] | bbB[b])>>indice1)&1) ) )
        {
            grille[i][j] = val;
            bbL[i] |= bitVal;
            bbC[j] |= bitVal;
            bbB[b] |= bitVal;
            if(resolu(grille, dl->next, bbL, bbC, bbB,map))
			{
				return true;
			}
        }
    }
    size_t bi =dl->back->i , bj = dl->back->j;
    uint8_t indice2 = grille[bi][bj]-1;
    uint64_t bitVal2 = (1<<indice2);
    bbL[bi] ^= bitVal2;
    bbC[bj] ^= bitVal2;
    bbB[map[bi][bj]] ^= bitVal2;
    return false;
}
bool resolu_32(uint8_t** grille, Liste *dl, uint32_t *bbL, uint32_t *bbC, uint32_t *bbB,uint8_t **map)
{
    if(!dl)
        return true;
    //printf("%ld\n", nbElementListe(dl));
    size_t k,c, i = dl->i, j= dl->j, b = map[i][j];
    uint8_t val, indice1;
    uint32_t bitVal;
    for(k = 0 ; k < dl->population ; k++)
    {

        c = dl->c[k];
        val = c, indice1 = val-1;
        bitVal = 1<<indice1;

       if((val && !(( (bbL[i] | bbC[j] | bbB[b])>>indice1)&1) ) )
        {
            grille[i][j] = val;
            bbL[i] |= bitVal;
            bbC[j] |= bitVal;
            bbB[b] |= bitVal;
            if(resolu_32(grille, dl->next, bbL, bbC, bbB,map))
			{
				return true;
			}
        }
    }
    size_t bi =dl->back->i , bj = dl->back->j;
    uint8_t indice2 = grille[bi][bj]-1;
    uint32_t bitVal2 = (1<<indice2);
    bbL[bi] ^= bitVal2;
    bbC[bj] ^= bitVal2;
    bbB[map[bi][bj]] ^= bitVal2;
    return false;
}

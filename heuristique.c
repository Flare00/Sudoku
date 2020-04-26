#include "heuristique.h"

size_t heuristiqueFacile(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map)
{
    uint8_t modifier = 1;
    //tant que l'algorithme heuristique modifie les cases restante, alors continu.
    while (modifier > 0)
    {
        modifier = 0;
        modifier += heuristiqueSingletonVisible(grille, n, liste, map);
    }
    //retourne le nombre d'element présent dans la liste.
    return listeNbElement(liste) - 1;
}

size_t heuristiqueMoyenne(uint8_t **grille, size_t n, Liste *liste , uint8_t ** map)
{
    uint8_t modifier = 1;

    //tant que l'algorithme heuristique modifie les cases restante, alors continu.
    while (modifier > 0)
    {
        modifier = 0;
        modifier += heuristiqueJumeauANVisible( n, liste, map);
        modifier += heuristiqueSingletonCacher(grille, n, liste, map);
        //modifier += heuristiqueCandidatsIdentique(grille, n, bbL, bbC, bbB, liste);
    }

    return heuristiqueFacile(grille, n, liste, map);
}

size_t heuristiqueDifficile(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map)
{
    return 0;
    uint8_t modifier = 1;

    //tant que l'algorithme heuristique modifie les cases restante, alors continu.
    while (modifier > 0)
    {
        modifier = 0;
        modifier += heuristiqueGroupesIsoler(n,liste);
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
    Liste * temp = NULL;
    Liste * first = liste->suivante;

    while(first != NULL){
    	//pour tout element de la liste
        uint64_t c = first->candidats;
        //si un seul candidat se trouve dans la liste des candidats alors
        if(__builtin_popcountll(c) == 1){
            retour = 1;

            Liste * seconde = liste->suivante;
            //met la valeur du candidats dans la grille correspondante
            grille[first->i][first->j] = 1+__builtin_ctz(c);
            seconde = liste->suivante;
            while(seconde != NULL){
            	//pour toutes les autre elements de la liste, dans la même ligne, colonne ou bloc, retire le candidats
                if(!(seconde->i == first->i && seconde->j == first->j)){
                    if(seconde->i == first->i || seconde->j == first->j || map[seconde->i][seconde->j] == map[first->i][first->j]){
                        seconde->candidats = seconde->candidats & ~c;
                    }
                }
                seconde = seconde->suivante;
            }

            //supprime de la liste l'elements trouvé.
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
    Liste * temp = NULL;
    Liste * first = liste->suivante;

    while(first != NULL){
    	//pour tout element de la liste
    	//attribut a c ses candidats
        uint64_t c = first->candidats;

        Liste * seconde = liste->suivante;
        while(seconde != NULL){
        	//pour tout element de la liste si un element secondaire ne correspond pas a l'element primaire
            if(!(seconde->i == first->i && seconde->j == first->j)){
            	//retire tout de c tout les candidats déjà présent dans le bloc
                if(map[seconde->i][seconde->j] == map[first->i][first->j]){
                    c = c & ~seconde->candidats;
                }
            }
            seconde = seconde->suivante;
        }    
        // si il ne reste plus que 1 seul candidats restant
        if(__builtin_popcountll(c) == 1){
            retour = 1;

            Liste * seconde = liste->suivante;
            //ecrit dans la grille a l'endroit de l'element, la valeur du candidat
            grille[first->i][first->j] = 1+__builtin_ctz(c);
            seconde = liste->suivante;
            while(seconde != NULL){
            	//pour tout element de la liste non identique
                if(!(seconde->i == first->i && seconde->j == first->j)){
                	//supprime le candidats si il se situe sur la meme ligne/colonne/bloc
                    if(seconde->i == first->i || seconde->j == first->j || map[seconde->i][seconde->j] == map[first->i][first->j]){
                        seconde->candidats = seconde->candidats & ~c;
                    }
                }
                seconde = seconde->suivante;
            }
            //retire l'element trouvé de la liste.
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

uint8_t heuristiqueSingleton(uint8_t **grille, size_t n, Liste *liste, uint8_t ** map){
    uint8_t retour = 0;
    uint8_t aUpdate = 0;
    Liste * temp = NULL;
    Liste * first = liste->suivante;

    while(first != NULL){
    	//pour tout elements de la liste
        uint64_t c = first->candidats;
        //si il est constitué d'un seul candidat alors
        if(__builtin_popcountll(c) == 1){
        	//passe aUpdate a 1;
            aUpdate = 1;
            
        } else {
        	//sinon
            Liste * seconde = liste->suivante;
            while(seconde != NULL){
            	//pour tout element de la liste non identique
                if(!(seconde->i == first->i && seconde->j == first->j)){
                	//retirer les candidats présent dans le même bloc
                    if(map[seconde->i][seconde->j] == map[first->i][first->j]){
                        c = c & ~seconde->candidats;
                    }
                }
                seconde = seconde->suivante;
            }


            //si il ne reste plus qu'un seul candidat alors passe aUpdate a 1, sinon passe candidat a 0;
            if(__builtin_popcountll(c) == 1){
                aUpdate = 1;
            } else {
                c = 0;
            }
        }
        //si aUpdate == 1
        if(aUpdate == 1){
            retour = 1;

            Liste * seconde = liste->suivante;
            //met dans la grille la valeur du candidat
            grille[first->i][first->j] = 1+__builtin_ctz(c);
            seconde = liste->suivante;
            while(seconde != NULL){
            	//pour tout elements de la liste non identique
                if(!(seconde->i == first->i && seconde->j == first->j)){
                	//supprime le candidats dans les element de la même ligne/colonne/bloc.
                    if(seconde->i == first->i || seconde->j == first->j || map[seconde->i][seconde->j] == map[first->i][first->j]){
                        seconde->candidats = seconde->candidats & ~c;
                    }
                }
                seconde = seconde->suivante;
            }
            //supprime l'element trouvé
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

uint8_t heuristiqueJumeauANVisible(size_t n, Liste *liste, uint8_t ** map){
    uint8_t retour = 0;
    size_t taille = n*n;
    uint64_t mask = (uint64_t)(1 << taille) - 1;
    Liste * temp;

    for(int bloc = 0; bloc < taille; bloc++){
    	uint8_t trouve = 0;
        temp = liste->suivante;
        //attribue a 0 les bitboard temporaire.
        uint64_t *mbbBL = calloc(n,sizeof(uint64_t));
        uint64_t *ubbBL = calloc(n,sizeof(uint64_t));
        uint64_t *mbbBC = calloc(n,sizeof(uint64_t));
        uint64_t *ubbBC = calloc(n,sizeof(uint64_t));
        while(temp != NULL){
        	//pour tout element de la liste etant dans le bloc.
            if(map[temp->i][temp->j] == bloc){
            	//effectue un Xor pour permettre de deceler les element trouvé une fois uniquement des elements trouvé N fois.
                ubbBL[temp->i%n] = mask & (ubbBL[temp->i%n] ^ (temp->candidats & ~mbbBL[temp->i%n]));
                //effectue un Ou pour mettre tout les element trouvé plusieur fois.
                mbbBL[temp->i%n] = mask & (mbbBL[temp->i%n] | (temp->candidats & ~ubbBL[temp->i%n]));
            	//effectue un Xor pour permettre de deceler les element trouvé une fois uniquement des elements trouvé N fois.
                ubbBC[temp->j%n] = mask & (ubbBC[temp->j%n] ^ (temp->candidats & ~mbbBC[temp->j%n]));
                //effectue un Ou pour mettre tout les element trouvé plusieur fois.
                mbbBC[temp->j%n] = mask & (mbbBC[temp->j%n] | (temp->candidats & ~ubbBC[temp->j%n]));
            }
            temp = temp->suivante;
        }

        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
        		//retire pour tout les bitboard temporaire, les elements répété ou présent qu'une seule fois.
                uint64_t tempL = ~(ubbBL[i] | mbbBL[i]);
                uint64_t tempC = ~(ubbBC[i] | mbbBC[i]);  
                mbbBL[i] = mbbBL[i] & ~(ubbBL[j] | mbbBL[j]);
                mbbBL[j] = mbbBL[j] & tempL;
                mbbBC[i] = mbbBC[i] & ~(ubbBC[j] | mbbBC[j]);
                mbbBC[j] = mbbBC[j] & tempC;
            }
            //si un element est a modifier, mais trouve a 1
            if( mbbBL[i] > 0 || mbbBC[i] > 0){
            	trouve = 1;
            }
        }
        //si trouve alors
        if(trouve)
        {
	        temp = liste->suivante;
	        while(temp != NULL){ 
	        	//pour tout les elements de la liste, si ils ne font pas parti du bloc
	            if(map[temp->i][temp->j] != bloc){
	            	//si l'element de la liste est dans la bande et que la ligne est a modifier / est modifiable.
	                if((temp->i >= (bloc/n)*n) && (temp->i < ((bloc/n)*n) + n) && (mbbBL[temp->i%n] > 0) && (temp->candidats & ~mbbBL[temp->i%n]) != temp->candidats){
	                    retour = 1;
	                    //passe retour a 1, et eneleve les candidats a retirers.
	                    temp->candidats = mask & temp->candidats & ~mbbBL[temp->i%n];
	                }
	            	//si l'element de la liste est dans la Piles et que la colonne est a modifier / est modifiable.
	                if((temp->j >= (bloc%n)*n) && (temp->j < ((bloc%n)*n) + n) && (mbbBC[temp->j%n] > 0) && (temp->candidats & ~mbbBC[temp->j%n]) != temp->candidats){
	                    retour = 1;
	                    //passe retour a 1, et eneleve les candidats a retirers.
	                    temp->candidats = mask & temp->candidats & ~mbbBC[temp->j%n];
	                }
	            }
	            temp = temp->suivante;
        	}
        }
        //Libere les bitboard temporaire.
        free(mbbBL);
        free(ubbBL);
        free(mbbBC);
        free(ubbBC);
    }
    return retour;
}

uint8_t heuristiqueGroupesIsoler(size_t n, Liste *liste)
{
	uint8_t retour = 0;

	size_t taille = n*n;
	Liste * temp, * temp2;


	//stock les différent groupe possible (candidats)[0] et leurs positions[1].
	uint64_t ** groupeLigne = malloc(taille*sizeof(uint64_t*));
	uint64_t ** groupeColonne = malloc(taille*sizeof(uint64_t*));

	//stock le groupe trouvé.
	uint64_t * groupeLigneSauv = malloc(2*sizeof(uint64_t));
	uint64_t * groupeColonneSauv = malloc(2*sizeof(uint64_t));

	for(int j = 0; j < taille; j++)
	{
		groupeLigne[j] = malloc(2*sizeof(uint64_t));
		groupeColonne[j] = malloc(2*sizeof(uint64_t));
	}


	for(int i = 0; i < taille; i++)
	{
		uint8_t finiL = 0, finiC = 0;
		groupeLigneSauv[0] = 0;
		groupeLigneSauv[1] = 0;
		groupeColonneSauv[0] = 0;
		groupeColonneSauv[1] = 0;
		temp = liste->suivante;
		while(temp != NULL && (finiL == 0 || finiC == 0))
		{
			//Pour tout element de la liste tant que finiL ou finiC sont a 0
			for(int j = 0; j < taille; j++)
			{
				//met les valeur des groupe a 0;
				groupeLigne[j][0] = 0;
				groupeLigne[j][1] = 0;
				groupeColonne[j][0] = 0;
				groupeColonne[j][1] = 0;
			}
			//si temp se trouve dans la ligne ou dans la colonne (ou les deux) a analyser, et qu'il a plus d'un candidats
			if(temp->i == i || temp->j == i && __builtin_popcountll(temp->candidats) > 1)
			{
				temp2 = liste->suivante;
				while(temp2 != NULL)
				{	
					//pour tout element de la liste
					//si il a plus d'un candidats alors
					if(__builtin_popcountll(temp2->candidats) > 1)
					{
						//si l'element secondaire se trouve dans la ligne analysé mais pas sur la meme colonne que l'element primaire et que finiL est egal à 0
						if(temp2->i == i && temp2->j != temp->j && finiL == 0)
						{
							uint8_t groupeRetrouve = 0, indice = 0;
							//test le binaire des candidats de l'element primaire et secondaire,(dans la ligne) et si un en commun est trouvé alors
							if((temp->candidats & temp2->candidats) > 0)
							{
								//trouve le groupe en fusionnant les candidats de l'element primaire et secondaire.
								uint64_t groupe = temp->candidats | temp2->candidats;
								//verifie que le groupe n'as pas déjà été trouvé dans la liste
								while(groupeLigne[indice][0] != 0 && groupeRetrouve == 0)
								{
									if(groupeLigne[indice][0] == groupe)
									{
										//si déjà trouvé, alors rajoute la position de la case sur la ligne.
										groupeLigne[indice][1] = groupeLigne[indice][1] | ((uint64_t)1 << temp2->j);
										groupeRetrouve = 1;
									}
									indice++;
								}
								if(groupeRetrouve == 0)
								{
									//si non trouvé alors creer l'element au premier indice vide et rajoute la position de l'element primaire et secondaire
									groupeLigne[indice][0] = groupe;
									groupeLigne[indice][1] = ((uint64_t)1 << temp->j) | ((uint64_t)1 << temp2->j);
								}
							}
						}
						//test le binaire des candidats de l'element primaire et secondaire,(dans la colonne) et si un en commun est trouvé alors
						if(temp->j == i && temp2->j == temp->j && temp2->i != temp->i && finiL == 0)
						{
							uint8_t groupeRetrouve = 0, indice = 0;
							if((temp->candidats & temp2->candidats) > 0)
							{
								//trouve le groupe en fusionnant les candidats de l'element primaire et secondaire.
								uint64_t groupe = temp->candidats | temp2->candidats;
								//verifie que le groupe n'as pas déjà été trouvé dans la liste
								while(groupeColonne[indice][0] != 0 && groupeRetrouve == 0)
								{
									if(groupeColonne[indice][0] == groupe)
									{
										//si déjà trouvé, alors rajoute la position de la case sur la colonne.
										groupeColonne[indice][1] = groupeColonne[indice][1] | ((uint64_t)1 << temp2->i);
										groupeRetrouve = 1;
									}
									indice++;
								}
								if(groupeRetrouve == 0)
								{
									//si non trouvé alors creer l'element au premier indice vide et rajoute la position de l'element primaire et secondaire
									groupeColonne[indice][0] = groupe;
									groupeColonne[indice][1] = ((uint64_t)1 << temp->i) | ((uint64_t)1 << temp2->i);
								}
							}
						}
					}
					temp2 = temp2->suivante;
				}
			}

			uint8_t k = 0;
			//pour tout elements présent dans les groupes, tant qu'on as pas atteint des elements vide ou pas terminer la recherche.
			while((groupeLigne[k][0] != 0 || groupeColonne[k][0] != 0) && (finiL == 0 || finiC == 0))
			{
				if(groupeLigne[k][0] != 0)
				{
					//si un groupe est dans la ligne et que le nombre d'element du groupe correspond au nombre de case ayant se groupe
					if(__builtin_popcountll(groupeLigne[k][0]) ==  __builtin_popcountll(groupeLigne[k][1]))
					{
						//alors sauvegarde le groupe et passe finiL a 1;
						groupeLigneSauv[0] = groupeLigne[k][0];
						groupeLigneSauv[1] = groupeLigne[k][1];
						finiL = 1;
					}					
				}
				

				if(groupeColonne[k][0] != 0)
				{
					//si un groupe est dans la colonne et que le nombre d'element du groupe correspond au nombre de case ayant se groupe
					if(__builtin_popcountll(groupeColonne[k][0]) ==  __builtin_popcountll(groupeColonne[k][1]))
					{
						//alors sauvegarde le groupe et passe finiL a 1;
						groupeColonneSauv[0] = groupeColonne[k][0];
						groupeColonneSauv[1] = groupeColonne[k][1];
						finiC = 1;
					}
				}
				k++;
			}
			temp = temp->suivante;
		}
		//si au moins un groupe a été trouvé
		if(finiL == 1 || finiC == 1)
		{
			temp = liste->suivante;
			while(temp != NULL){
				//pour tout element de la liste,
				if(finiL == 1 && groupeLigneSauv != NULL )
				{
					//si il s'agit de la ligne alors 
					if(temp->i == i && ((1 << temp->j) & groupeLigneSauv[1]) == 0)
					{
						//si l'element est dans la ligne et qu'il ne s'agit pas d'une des cases du groupe alors
						if((temp->candidats & ~groupeLigneSauv[0]) != temp->candidats)
						{
							retour = 1;
							//supprime les candidats du groupe de la case
							temp->candidats = temp->candidats & ~groupeLigneSauv[0];
							temp->population = __builtin_popcountll(temp->candidats);
						}
					}
				}
				if(finiC == 1 && groupeColonneSauv != NULL )
				{
					//si il s'agit de la colonne alors 
					if(temp->j == i && ((1 << temp->i) & groupeColonneSauv[1]) == 0)
					{
						//si l'element est dans la ligne et qu'il ne s'agit pas d'une des cases du groupe alors
						if((temp->candidats & ~groupeColonneSauv[0]) != temp->candidats)
						{
							retour = 1;
							//supprime les candidats du groupe de la case
							temp->candidats = temp->candidats & ~groupeColonneSauv[0];
							temp->population = __builtin_popcountll(temp->candidats);
						}
					}
				}
				temp = temp->suivante;
			}
		}
	}

	//libere tout ce qui a été alloué
	for(int j = 0; j < taille; j++)
	{
			free(groupeLigne[j]);
			free(groupeColonne[j]);
	}

	free(groupeLigneSauv);
	free(groupeColonneSauv);
	free(groupeLigne);
	free(groupeColonne);

	return retour;
}

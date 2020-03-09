#include difficulte.h

int validiterEtDifficulter(uint8_t **grille, size_t taille, int level);
	//NON FONCTIONNEL - A FAIRE
	bool terminer = false;
	bool bloque = false;
	bool avance = false;
	bool depasser = false;

	int difficulte = 0;
	// Essaye de faire sur toute la grille les techniques de résolution facile, jusqu'a terminer ou bloqué, recommence avec le niveau du dessus si bloqué (et ainsi de suite)
	// doit s'arreter si le niveau dépasse le niveau maximum désiré.
	

	do{
		bool utilise = false;
		avance = false;
		// NIVEAU 1
		
		if(utilise && difficulte < 1){
			avance = true;
			difficulte = 1;
		} else if (utilise){
			avance = true;
		}
		
		if(!terminer && level >=2){
			utilise = false;
			// NIVEAU 2
			
			if(utilise && difficulte < 2){	
				avance = true;
				difficulte = 2;
			} else if (utilise){
				avance = true;
			}
			if(!termine && level >= 3){
				utilise = false;
				// NIVEAU 3
				
				if(utilise && difficulte < 3){		
					avance = true;
					difficulte = 3;
				} else if (utilise){
					avance = true;
				}
				
				if(!termine && level >= 4){
					utilise = false;
					// NIVEAU 4
					
					if(utilise && difficulte < 4){						
						difficulte = 4;
					}	else if (utilise){
						avance = true;
					}
				} else if(!termine){
					depasser = true;
				}
			} else if(!termine){
				depasser = true;
			}
		} else if(!termine){
			depasser = true;
		}
	}while(!termine && !avance && depasser);
	
	if(depasser){
		difficulte = 0;
	}
	return difficulte;
}

	
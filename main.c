			///////////////////////////////////
			////						   ////
			////  Auteur: Quentin GRUCHET  ////
			////  Date : Decembre 2020 	   ////
			////						   ////
			///////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

////////////////////////////////////////////////////////
///////////////////FONCTIONS UTILES/////////////////////
////////////////////////////////////////////////////////
/**
 * *Description : Alloue et verifie la mémoire d'une matrice.
 * *Function : _initialiseTab.
 * @param tab, le tableau a alloué, poids la taille de ce tableau.
 * @return le tableau alloué ou NULL en cas d'erreur
 * */
int** _initialiseTab(int **tab, int poids){

	tab = calloc(poids, poids * sizeof(int*));
	if(tab){
		for(int h = 0; h < poids; ++h){
			tab[h] = calloc(poids, poids *sizeof(int));
		}
	}else{
		return printf("Erreur d'allocation memoire (1)"), NULL;
	}
	if(*tab){
		return tab;
	} else{
		return printf("Erreur d'allocation memoire (2)"), NULL;
	}
}

/**
 * *Description : inverse les element d'un tableau.
 * *Function : _inverseTab.
 * @param tab[] le tableau a inversé, tailleTab la taille de ce tableau.
 * @return *tab, le tableau inversé.
 * */
int _inverseTab(int tab[], int tailleTab){
	
	int tmp[tailleTab];
	int i, j;

	for ( i = tailleTab - 1, j = 0; i >= 0; i--, j++){
        tmp[j] = tab[i];
	}
	for (i = 0; i < tailleTab; i++){
        tab[i] = tmp[i];
	}

	return *tab;
}

/**
 * *Description : trie par ordre décroissant un tableau.
 * *Function : _trieTabDecroissant.
 * @param tab[] le tableau a trié, tailleTab la taille de ce tableau.
 * @return *tab, le tableau trié.
 * */
int _trieTabDecroissant(int tab[], int tailleTab){
	int tmp = 0;
	for(int i=0; i< tailleTab-1; i++){
		for(int j=i+1; j<tailleTab; j++){
			if(tab[i] > tab[j]){
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
		}
	}

	_inverseTab(tab, tailleTab);
	return *tab;
}

/**
 * *Description : fais une copie profonde d'un tableau.
 * *Function : _copieTab.
 * @param copieTab[] le tableau contenant la copie ,tab[] le tableau a copié, tailleTab la taille du tableau.
 * @return *tab, le tableau contenant la copie.
 * */
int _copieTab(int copieTab[], int tab[], int tailleTab){
	for (size_t i = 0; i < tailleTab; i++){
		copieTab[i] = tab[i];
	}

	return *copieTab;
	
}

/**
 * *Description : remplie aleatoirement le tableau des colis.
 * *Function : _remplirColisAleatoirement.
 * @param tab[] le tableau a remplir, nbObjet le nombre d'objet dans ce tableau, poids le poids max des colis.
 * @return *tab, le tableau rempli.
 * */
int _remplirColisAleatoirement(int tab[], int nbObjet, int poids){
	
	srand(time(NULL));
	for (size_t i = 0; i < nbObjet; i++){
		tab[i] = rand() % poids +1;	
	}

	return *tab;
}

/**
 * *Description : compte le nombre de carton.
 * *Function : _nbColis.
 * @param tab[] le tableau a compter; tailleTab la taille du tableau.
 * @return compt, le nombre de colus.
 * */
int _nbColis(int **tab, int tailleTab){
	int compt = 0;
	for (size_t i = 0; i < tailleTab; i++){
		if(tab[i][0] != 0){
			compt++;
		}
	}

	return compt;
}

/**
 * *Description : affiche le resultat des algo sous forme { , , , }.
 * *Function : _afficherResultat.
 * @param tab[] le tableau a afficher, tailleTab la taille du tableau.
 * */

void _afficherResultat(int **tab, int tailleTab){
	int compt = 0;
	compt = _nbColis(tab, tailleTab);

	for (size_t i = 0; i < compt; i++){
		printf("{");
		for (int j = 0; j < compt; j++){
			if(tab[i][j] != 0){
				printf(" %d ", tab[i][j]);
			}
		}
		printf("}\n");
	}

	
	printf("Il y a %d colis au total.\n", compt);
}

/**
 * *Description : affiche le resultat des algo sous forme matricielle.
 * *Function : _afficherMatrice.
 * @param tab[] le tableau a afficher, tailleTab la taille du tableau.
 * */
void _afficheMatrice(int** tab, int tailleTab){
	for (size_t i = 0; i < tailleTab; i++){
		printf("[");
		for (size_t j = 0; j < tailleTab; j++)
		{
			printf(" %d ", tab[i][j]);
		}
		printf("]\n");	
	}
}

/**
 * *Description : affiche le resultat du tableau contenant tout les colis a faire entrer.
 * *Function : _afficheTabColis.
 * @param colis[] le tableau a afficher, tailleTab la taille du tableau.
 * */
void _afficheTabColis(int colis[], int tailleTab){
	printf("{");
	for (size_t i = 0; i < tailleTab; i++){
		printf(" %d, ", colis[i]);
	}
	printf("}\n");
}

/**
 * *Description : libère proprement la mémoire alloué de la matrice.
 * *Function : _freeMem.
 * @param tab[] le tableau a liberer, tailleTab la taille du tableau.
 * */
void _freeMem(int **tab, int tailleTab){

	for (int i = 0; i < tailleTab; i++){
		free(tab[i]);
	}
	free(tab);
}

////////////////////////////////////////////////////////
//////////////////ALGORITHME REPONSE////////////////////
////////////////////////////////////////////////////////

/**
 * *Description : repond a la question selon le principe FIFO.
 * *Function : _premierArrivePremierServis.
 * @param **res tableau contenant les reponse, colis[] tableau qui contient les colis a faire entrer.
 * @param poids le poids maximum d'un colis, tailleTab la taille de la matrice.
 * @return res
 * */
int** _premierArrivePremierServis(int **res, int colis[], int poids, int tailleTab){
	int tmpCalcul = 0;
	int indexH = 0;
	int indexV = 0;

	for (size_t i = 0; i < tailleTab; i++){
		if((tmpCalcul + colis[i]) <= poids){
			tmpCalcul += colis[i];
			res[indexV][indexH] = colis[i];
			indexH++;
		} else{
			tmpCalcul = 0;
			indexV++;
			indexH = 0;
			i--;
		}
	}
	return res;
}


/**
 * *Description : repond a la question selon le principe des plus imposant en premier.
 * *Function : _lesPlusGrosDabord.
 * @param **res tableau contenant les reponse, colis[] tableau qui contient les colis a faire entrer.
 * @param poids le poids maximum d'un colis, tailleTab la taille de la matrice.
 * @return res
 * */
int** _lesPLusGrosDabord(int **res, int colis[], int poids, int tailleTab){
	int tmpTab[tailleTab];

	_copieTab(tmpTab, colis, tailleTab);

	_trieTabDecroissant(tmpTab, tailleTab);

	return res = _premierArrivePremierServis(res, tmpTab, poids, tailleTab);

}

/**
 * *Description : repond a la question selon le principe de la complémentarite.
 * *Function : _complementarite.
 * @param **res tableau contenant les reponse, colis[] tableau qui contient les colis a faire entrer.
 * @param poids le poids maximum d'un colis, tailleTab la taille de la matrice.
 * @return res
 * */
int** _complementarite(int **res, int colis[], int poids, int tailleTab){
	
	int indexH = 0;
	int indexV = 0;
	int tmpTab[tailleTab]; //on travaille sur un copie pour ne pas alterer le tableau original

	_copieTab(tmpTab, colis, tailleTab);
	_trieTabDecroissant(tmpTab, tailleTab);
	
	for (size_t i = 0; i < tailleTab; i++){
		if(tmpTab[i] == 0){
			continue;
		}
		int tmpCalcul = 0;
		for (size_t j = i + 1; j < tailleTab; j++){
			if(tmpTab[j] == 0){
				continue;
			}
			if(tmpCalcul == 0){
				res[indexV][indexH] = colis[i];
				indexH++;
				tmpCalcul += colis[i];
				tmpTab[i] = 0;
			}
			if(tmpCalcul + colis[j] <= poids){
				res[indexV][indexH] = colis[j];
				tmpCalcul += colis[j];
				indexH++;
				tmpTab[j] = 0;
			}
		}
		indexH = 0;
		indexV++;
	}

	return res;
}

////////////////////////////////////////////////////////
//////////////////////////MENU//////////////////////////
////////////////////////////////////////////////////////

/**
 * *Description : menu permettant l'interaction avec les algo.
 * *Function : _choix.
 * @param *cmd, tableau des caractere entre par l'utilisateur, colis[] tableau qui contient les colis a faire entrer.
 * @param poids le poids maximum d'un colis, poidsAlea, maximum des poids aleatoire.
 * @return res
 * */
int _choix(const char* cmd, int colis[], int tailleTab, int poidsAlea){

	int poids = 10;
	int **res;
	int taille = 100;

	if(cmd[0] == 'q'){
		return printf("\t Merci d'avoir utiliser mes algorithmes\n"), 0;
	}

	if(cmd[0] == '1'){
		if(poidsAlea > poids){
			return printf("Veuillez augmenter le poids maximum\n"), 1;
		} else{
			printf("Resultat du premier algorithme :\n");

			res = _initialiseTab(res, taille);
			res = _premierArrivePremierServis(res, colis, poids, tailleTab);
			_afficherResultat(res, taille);
			_freeMem(res, taille);
		}
	}

	if(cmd[0] == '2'){
		if(poidsAlea > poids){
			return printf("Veuillez augmenter le poids maximum\n"), 1;
		} else{
			printf("\nResultat du deuxieme algorithme :\n");

			res = _initialiseTab(res, taille);
			res = _lesPLusGrosDabord(res, colis, poids, tailleTab);
			_afficherResultat(res, taille);
			_freeMem(res, taille);
		}
	}

	if(cmd[0] == '3'){
		if(poidsAlea > poids){
			return printf("Veuillez augmenter le poids maximum\n"), 1;
		} else{
			printf("\nResultat de l'algorithme optimal :\n");

			res = _initialiseTab(res, taille);
			res = _complementarite(res, colis, poids, tailleTab);
			_afficherResultat(res, taille);
			_freeMem(res, taille);
		}
	}

	if(cmd[0] == 'h'){
		printf("\t 'q' : quitte le programme\n");
		printf("\t '1' : lance l'algorithme numero 1 (premierArrivePremierServis)\n");
		printf("\t '2' : lance l'algorithme numero 2 (lesPLusGrosDabord)\n");
		printf("\t '3' : lance l'algorithme numero 3 (optimal : complementarite)\n");
		printf("\t 'h' : liste les commandes disponibles\n");
		printf("\t 'c' : affiche le poids des colis\n");
		printf("\t 'm' : calcul la moyenne des colis pour les 3 algos\n");
	}	

	if(cmd[0] == 'c'){
		printf("Voici le tableau des colis :\n");
		_afficheTabColis(colis, tailleTab);
		printf("Le poids maximum du colis a remplir est de : %d\n", poids);
	}

	if(cmd[0] == 'm'){
		float somme = 0;
		int nbEntree = 1000;
		for (size_t i = 0; i < nbEntree; i++){
			int tabColis[100];
			for (size_t j = 0; j < 100; j++){
				tabColis[j] = 0;
			}
			_remplirColisAleatoirement(tabColis, 100, 10);
			res = _initialiseTab(res, taille);
			res = _premierArrivePremierServis(res, tabColis, 10, 100);
			int nombrebColis = _nbColis(res, 100);
			somme += nombrebColis;
			_freeMem(res, taille);
		}
		printf("La moyenne pour le premier algo est : %f\n", somme/nbEntree);

		somme = 0;
		for (size_t i = 0; i < nbEntree; i++){
			int tabColis[100];
			for (size_t j = 0; j < 100; j++){
				tabColis[j] = 0;
			}
			_remplirColisAleatoirement(tabColis, 100, 10);
			res = _initialiseTab(res, taille);
			res = _lesPLusGrosDabord(res, tabColis, 10, 100);
			int nombrebColis = _nbColis(res, 100);
			somme += nombrebColis;
			_freeMem(res, taille);
		}
		printf("La moyenne pour le deuxieme algo est : %f\n", somme/nbEntree);

		somme = 0;
		for (size_t i = 0; i < nbEntree; i++){
			int tabColis[100];
			for (size_t j = 0; j < 100; j++){
				tabColis[j] = 0;
			}
			_remplirColisAleatoirement(tabColis, 100, 10);
			res = _initialiseTab(res, taille);
			res = _complementarite(res, tabColis, 10, 100);
			int nombrebColis = _nbColis(res, 100);
			somme += nombrebColis;
			_freeMem(res, taille);
		}
		printf("La moyenne pour lalgo optimal est : %f\n", somme/nbEntree);
	}
}

////////////////////////////////////////////////////////
//////////////////////////MAIN//////////////////////////
////////////////////////////////////////////////////////

int main(int argc, char* argv[]){
	int nbObjet = 100;
	int poidsAleatoireMax = 10;
	int colis[nbObjet];
	//int colis[10] = {2, 6, 1, 5, 8, 4, 5, 7, 5, 3};
	int tailleTab = sizeof(colis)/sizeof(colis[0]);

	_remplirColisAleatoirement(colis, nbObjet, poidsAleatoireMax);

	printf("Tapez 'h' pour obtenir la liste des commandes\n");

	char tab[64];
	do{
		printf(">");

		fgets(tab, 64, stdin);
	}while(_choix(tab, colis, tailleTab, poidsAleatoireMax));

	return 0;
}
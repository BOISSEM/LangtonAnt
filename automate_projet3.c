//--------------------------------
//								
//	automate_projet3.c 			
//	Created by Seif Eddine BEN RHOUMA
//	January 2018 				
//								
//--------------------------------

#include <stdio.h>
#include <stdlib.h>

#define NB_EVOLUTION 20

/* ---------------------------- 2.1 ---------------------------- */

//--------------------------------
//	Fonction indice
//	Entrée: coordonnées cartésiennes i, j
//			Taille du tableau N
//	Sortie: Correspondance sur un tableau 1D
//--------------------------------

int indice(int i, int j, int N)	{
	// Cas d'erreur (utile pour la fonction evolution)
	// if(i < 0)
	// 	i = 0;
	// if(j < 0)
	// 	j = 0;
	// if(i > N-1)
	// 	i = N-1;
	// if(j > N-1)
	// 	j = N-1;
	return N * i + j;
}

/* ------------------------------------------------------------- */

/* ---------------------------- 2.2 ---------------------------- */

//--------------------------------
//	Fonction init
//	Entrée: Fichier init.dat
//	Sortie: Pointeur vers vecteur contenant les valeurs du tableau
//--------------------------------

char* init(int N, int nb_file)	{

	FILE* file = NULL;
	int etat = 1;
	int i = 0;
	// Allocation dynamique
	char* vecteur = malloc(N*N * sizeof(char));

	// Ouverture du fichier en lecture
	if(nb_file == 1)
		file = fopen("init1.dat", "r");
	else if(nb_file == 2)
		file = fopen("init2.dat", "r");
	else
		file = fopen("init3.dat", "r");

	// Arrêt du programme en cas d'erreur
	if(file == NULL)	{
		printf("Erreur d'ouverture du fichier\n");
		exit(1);
	}

	// On lit le caractere
	etat = fgetc(file);

	while(etat != EOF)	{	// On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
		if(etat != '\n')	{
			vecteur[i] = etat;
			i++;
		}
		etat = fgetc(file);
	}

    // Fermeture du fichier
	fclose(file);

	return vecteur;
}

//--------------------------------
//	Fonction affichage
//	Entrée: pointeur vers vecteur de description
//	Sortie: Rien
//--------------------------------

void affichage(char* vecteur, int N)	{
	int i, j, k;

	for(i = 0; i < N; i++)	{
		for(j = 0; j < N; j++)	{
			k = indice(i, j, N);
			if(vecteur[k] == '1')
				printf("[]");
			else
				printf("  ");
		}
		printf("\n");
	}
}

/* ------------------------------------------------------------- */

/* ---------------------------- 2.4 ---------------------------- */

//--------------------------------
//	Fonction conditions_limites
//	Entrée: pointeur vers vecteur de description
//	Sortie: pointeur vers vecteur de description 
//			auquel nous avons ajouté les conditions
//	Numéro d'étudiant: P1613690
//--------------------------------

char* conditions_limites(char* vecteur, int N)	{
	
	// Conditions aux limites gauches et droites
	// de type Mur à gauche et à droite
	/*
		0 1 1 0 1		Devient		1 0 1 1 0
		1 0 0 1 0					0 1 0 0 1
		0 1 0 0 0					1 0 0 0 0
		1 1 1 1 0					1 1 1 0 1
		0 1 0 0 0					1 0 0 0 0
	*/

	int i;
	char val;

	// Côté gauche
	for(i = 0; i < N; i++)	{
		vecteur[indice(i, 0, N)] = val;
		vecteur[indice(i, 0, N)] = vecteur[indice(i, 1, N)];
		vecteur[indice(i, 1, N)] = val;
	}
	// Côté droit
	for(i = 0; i < N; i++)	{
		vecteur[indice(i, N-1, N)] = val;
		vecteur[indice(i, N-1, N)] = vecteur[indice(i, N-2, N)];
		vecteur[indice(i, N-2, N)] = val;
	}

	// Conditions aux limites haute et basse
	// de type Conditions aux limites périodiques
	/*
		0 1 1 0 1		Devient		1 1 1 1 0
		1 0 0 1 0					0 1 0 0 1
		0 1 0 0 0					1 0 0 0 0
		1 1 1 1 0					1 1 1 0 1
		0 1 0 0 0					1 0 0 1 0
	*/

	// Côté haut et bas
	for(i = 0; i < N; i++)	{
		vecteur[indice(0, i, N)] = vecteur[indice(N-2, i, N)];
		vecteur[indice(N-1, i, N)] = vecteur[indice(1, i, N)];
	}

	return vecteur;
}

/* ------------------------------------------------------------- */

/* ---------------------------- 2.3 ---------------------------- */

//--------------------------------
//	Fonction evolution
//	Entrée: pointeur vers vecteur de description
//	Sortie: nouveau pointeur vers vecteur de description
//--------------------------------

char* evolution(char* vecteur, int N)	{

	int i, j;
	char* new_vecteur = malloc(N*N * sizeof(char));
	int nb_voisin_vivant;

	char voisin1, voisin2, voisin3, voisin4,
			voisin5, voisin6, voisin7, voisin8;

	// Conditions aux limites
	vecteur = conditions_limites(vecteur, N);

	for(i = 1; i < N-1; i++)	{
		for(j = 1; j < N-1; j++)	{
			// Calcul nombre de voisines vivantes
			nb_voisin_vivant = 0;

			voisin1 = vecteur[indice(i-1, j-1, N)];
			voisin2 = vecteur[indice(i-1, j, N)];
			voisin3 = vecteur[indice(i-1, j+1, N)];
			voisin4 = vecteur[indice(i, j-1, N)];
			voisin5 = vecteur[indice(i, j+1, N)];
			voisin6 = vecteur[indice(i+1, j-1, N)];
			voisin7 = vecteur[indice(i+1, j, N)];
			voisin8 = vecteur[indice(i+1, j+1, N)];

			if(voisin1 == '1')
				nb_voisin_vivant++;
			if(voisin2 == '1')
				nb_voisin_vivant++;
			if(voisin3 == '1')
				nb_voisin_vivant++;
			if(voisin4 == '1')
				nb_voisin_vivant++;
			if(voisin5 == '1')
				nb_voisin_vivant++;
			if(voisin6 == '1')
				nb_voisin_vivant++;
			if(voisin7 == '1')
				nb_voisin_vivant++;
			if(voisin8 == '1')
				nb_voisin_vivant++;

			// Cellule vivante avec moins de 2 voisins vivants
			if(vecteur[indice(i, j, N)] == '1' && nb_voisin_vivant < 2)
				new_vecteur[indice(i, j, N)] = '0';

			// Cellule vivante avec plus de 3 voisins vivants
			else if(vecteur[indice(i, j, N)] == '1' && nb_voisin_vivant > 3)
				new_vecteur[indice(i, j, N)] = '0';

			// Cellule morte avec 3 voisins vivants
			else if(vecteur[indice(i, j, N)] == '0' && nb_voisin_vivant == 3)
				new_vecteur[indice(i, j, N)] = '1';
			
			// Autres cas
			else
				new_vecteur[indice(i, j, N)] = vecteur[indice(i, j, N)];

			// printf("vecteur[%d] = %c\n", indice(i, j, N), vecteur[indice(i, j, N)]);
			// printf("new_vecteur[%d] = %c\n", indice(i, j, N), new_vecteur[indice(i, j, N)]);

		}
	}

	return new_vecteur;
}

/* ------------------------------------------------------------- */

/* ---------------------------- Fonctions tests ---------------------------- */

void stable(void)	{

	char* vecteur;
	int i;
	int nb_file = 1;
	int N = 20;

	vecteur = init(N, nb_file);

	for(i = 0; i < NB_EVOLUTION; i++)	{
		printf("------------- Evolution -------------\n");
		vecteur = evolution(vecteur, N);
		affichage(vecteur, N);
	}

	free(vecteur);
}

void oscillateurs(void)	{

	char* vecteur;
	int i;
	int nb_file = 2;
	int N = 20;

	vecteur = init(N, nb_file);
	affichage(vecteur, N);

	for(i = 0; i < NB_EVOLUTION; i++)	{
		printf("------------- Evolution -------------\n");
		vecteur = evolution(vecteur, N);
		affichage(vecteur, N);
	}

	free(vecteur);
}

void planeurs(void)	{

	char* vecteur;
	int i;
	int nb_file = 3;
	int N = 20;

	vecteur = init(N, nb_file);

	for(i = 0; i < NB_EVOLUTION; i++)	{
		printf("------------- Evolution -------------\n");
		vecteur = evolution(vecteur, N);
		affichage(vecteur, N);
	}

	free(vecteur);
}

/* ------------------------------------------------------------------------- */

/* ---------------------------- Fonctions Main ----------------------------- */

int main(void)	{

	//stable();
	oscillateurs();
	//planeurs();

	return 0;
}

/* ------------------------------------------------------------------------- */
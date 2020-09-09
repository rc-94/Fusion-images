#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fonctions.h"


/* PROJET DE C : FUSION D'IMAGES */


int main(int argc, char *argv[]) {


        // Verification du nombre d'arguments
        if (argc < 3) {
                printf("Nombre d'arguments invalides.\n");
                return 0;
        }
        FILE *image1 = fopen(argv[1], "r");
        FILE *image2 = fopen(argv[2], "r");


        // Recuperation de la taille des images
        int l, h, l2, h2, valeur_max;

        fscanf(image1, "P3");
        fscanf(image1, "%d %d", &l, &h);
        fscanf(image1, "%d", &valeur_max);
        printf("Image 1 : Largeur = %d et Hauteur = %d\n", l, h);

        fscanf(image2, "P3");
        fscanf(image2, "%d %d", &l2, &h2);
        fscanf(image2, "%d", &valeur_max);
        printf("Image 2 : Largeur = %d et Hauteur = %d\n\n", l, h);

        if (l != l2 || h != h2) {
                printf("Les images n'ont pas la meme taille.\n\n");
                return 0;
        }
        else {
                printf("Les images ont la meme taille.\n\n");
        }
        

        // Tableau Image 1 and Image 2
        Pixel I1[h][l];
        Pixel I2[h][l];
        
        RemplirTableau(h, l, I1, image1);
        RemplirTableau(h, l, I2, image2);
        
        
        
        // Matrice Graphe
        Sommet graphe[h][l];
        CreationGraphe(h, l, I1, I2, graphe);
        
        
        
        Pixel *S[h][l]; // S est l'ensemble de l'image 1
        Pixel *T[h][l]; // T est l'ensemble de l'image 2
        Pixel *pixel_neutre = InitialisationpixelNeutre(); 
        
        
        
        // Initialisation des ensemble S et T : s'il y a un masque
        if (argv[3] != NULL) {
        
                int l3, h3;
                FILE *masque = fopen(argv[3], "r");
                fscanf(masque,"P3");
                fscanf(masque,"%d %d", &l3, &h3);
                fscanf(masque,"%d", &valeur_max);
                printf("Masque : Largeur = %d et Hauteur = %d\n\n", l3, h3);
                
                if (l != l3 || h != h3) {
                        printf("Le masque n'est pas de la même taille que les images.\n\n");
                        return 0;
                }
                
                Pixel M[h][l];
                RemplirTableau(h, l, M, masque);
                InitialisationAvecMasque(h, l, graphe, S, T, M, pixel_neutre);            
        }



        // Initialisation des ensemble S et T : s'il n'y a pas de masque
        else {
                int choix;
                printf("Saisir une initialisation :\nAleatoire (1) OU par bords (2) OU un par bord et un aleatoirement (3) : ");
                scanf("%d", &choix);
                while (choix != 1 && choix != 2 && choix != 3) {
                        printf("Saisir une entrée correcte : ");
                        scanf("%d", &choix);
                }     
                switch (choix) {
                        case 1 :
                                InitialisationAleatoire(h, l, graphe, S, T, pixel_neutre);
                                break;
                        case 2 : // Initialisation des ensembles S et T par bords
                                InitialisationBords(h, l, graphe, S, T, pixel_neutre);
                                break;
                        case 3 :
                                InitialisationBordEtAleatoire(h, l, graphe, S, T, pixel_neutre);
                                break;
                }    
        }
        
        
        
        int choix4;
        printf("Choisir un mode de fusion :\nParcours en largeur (1) OU Algorithme de Karger (2) : ");
        scanf("%d",&choix4);
        while (choix4 != 1 && choix4 != 2) {
                printf("Saisir une entrée correcte : ");
                scanf("%d", &choix4);
        }
        if (choix4 == 2) {
                char choix6[3];
                printf("L'implementation de l'algorithme de Karger n'abouti pas a un resultat satisfaisant...\nVoulez-vous tout de meme le tester ? Entrez 'oui' si c'est la cas : ");
                scanf("%s", choix6);
                if (strcmp(choix6,"oui") != 0) {
                        printf("Vous allez effectuer le parcours en largeur.\n");
                        choix4 = 1;
                }
        }
        
        if (choix4 == 1) {
                // PARCOURS EN LARGEUR        
                int visite[h][l]; // tableau de sommets visites
                Zero(h, l, visite);
                ParcoursEnLargeur(h, l, graphe, S, T, visite, pixel_neutre);
                                
                
                // Tableau final qui contient les ensembles S et T
                Pixel *final[h][l];
                CreationTableauFinal(h, l, final, graphe, S, T, visite, pixel_neutre);

                
                // Choix du floutage
                char choix5[3];
                printf("Voulez vous appliquer un floutage a l'image ? Entrez 'oui' si c'est le cas : ");
                scanf("%s", choix5);
                if (strcmp(choix5, "oui") == 0) {
                        Flou(h, l, graphe, visite, final);
                }
                
                
                // Creation de l'image finale
                CreationImageFinal("ImagePPM.ppm", h, l, final);
                
                free(pixel_neutre);
        }
        
        else {
                // ALGORITHME DE KARGER
                Liste *voisins[h][l]; // tableau des voisins de chaque sommet dans graphe
                CreationVoisins(h, l, voisins, graphe);
                int sommets_contractes[h][l]; // tableau de sommets contractes
                Zero(h, l, sommets_contractes);
                Pixel *final_karger[h][l];
                Karger(h, l, sommets_contractes, voisins, graphe, final_karger);
                
                
                // Creation de l'image finale
                CreationImageFinal("ImagePPM.ppm", h, l, final_karger);
        
        }
        
        
        return 0;
}

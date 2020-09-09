#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fonctions.h"


//Fonction qui enfile un element dans une file
void Enfiler(File *file, Sommet *sommet) {
        Element *nouveau = malloc(sizeof(*nouveau));
        
        if (file == NULL || nouveau == NULL) {
                printf("Erreur");
        }
        
        nouveau->valeur = sommet;
        nouveau->suivant = NULL;
        
        // Si la file est pas nulle
        if (file->premier != NULL) {
                Element *tete = file->premier;
                while (tete->suivant != NULL) {
                        tete = tete->suivant;
                }
                tete->suivant = nouveau;
        }
        // Si la file est vide
        else {
                file->premier = nouveau;
        }
}


// Fonction qui defile une file
Sommet* Defiler(File *file) {
        if (file == NULL) {
                return 0;                
        }
        
        Sommet *sommet_a_recuperer = NULL;
        if (file->premier != NULL) {
                Element *defiler = file->premier;
                sommet_a_recuperer = defiler->valeur;
                file->premier = defiler->suivant;
                free(defiler);
                
        }
        return sommet_a_recuperer;
}


// Fonction qui initialise une file
File *InitialisationFile(void) {            
        File *file = malloc(sizeof(*file));
        if (file == NULL) {
                return NULL;
        }
        file->premier = NULL;
        return file;
}


// Fonction delta
double delta(Pixel p1, Pixel p2) {
        return sqrt(((pow((p1.R - p2.R), 2) + pow((p1.G - p2.G), 2) + pow((p1.B - p2.B), 2)) / 3)) / 255;
}

// Fonction qui calcule la capacite des aretes
double CapaF(Pixel p11, Pixel p21, Pixel p12, Pixel p22) {
         return (delta(p11, p21) + delta(p12, p22)) / (delta(p11, p12) + delta(p21, p22) + pow(10, -4));
}


//Fonction qui construit les aretes entre les deux images
Aretes *ConstructionAretes(int i, int j, int h, int l, Pixel I1[h][l], Pixel I2[h][l]) {
        Aretes *aretes = malloc(sizeof(*aretes));
        
        if ((i-1 >= 0) &&(j-1 >= 0) && (i+1 < h) && (j+1 < l)) { // cas où le pixel est au milieu donc 9 voisins
                aretes->arete_haut = CapaF(I1[i][j], I2[i][j], I1[i-1][j], I2[i-1][j]);
                aretes->arete_bas = CapaF(I1[i][j], I2[i][j], I1[i+1][j], I2[i+1][j]);
                aretes->arete_droite = CapaF(I1[i][j], I2[i][j], I1[i][j+1], I2[i][j+1]);
                aretes->arete_gauche = CapaF(I1[i][j], I2[i][j], I1[i][j-1], I2[i][j-1]);
                aretes->arete_haut_droit = CapaF(I1[i][j], I2[i][j], I1[i-1][j+1], I2[i-1][j+1]);
                aretes->arete_haut_gauche = CapaF(I1[i][j], I2[i][j], I1[i-1][j-1], I2[i-1][j-1]);
                aretes->arete_bas_droit = CapaF(I1[i][j], I2[i][j], I1[i+1][j+1], I2[i+1][j+1]);
                aretes->arete_bas_gauche = CapaF(I1[i][j], I2[i][j], I1[i+1][j-1], I2[i+1][j-1]);
                return aretes;
        }
        if ((j-1 < 0) && (i-1 >= 0) && (i+1 < h) && (j+1 < l)) { // cas où le pixel est sur le bord gauche, mais non sur le bord haut ou bas
                aretes->arete_haut = CapaF(I1[i][j], I2[i][j], I1[i-1][j], I2[i-1][j]);
                aretes->arete_bas = CapaF(I1[i][j], I2[i][j], I1[i+1][j], I2[i+1][j]);
                aretes->arete_droite = CapaF(I1[i][j], I2[i][j], I1[i][j+1], I2[i][j+1]);
                aretes->arete_haut_droit = CapaF(I1[i][j], I2[i][j], I1[i-1][j+1], I2[i-1][j+1]);
                aretes->arete_bas_droit = CapaF(I1[i][j], I2[i][j], I1[i+1][j+1], I2[i+1][j+1]);
                return aretes;
        }
        if ((i+1>=h) &&(j-1>=0)&&(j+1<l)&&(i-1>=0)) { // cas où le pixel est sur le bord bas mais pas sur le bord gauche ou droit
                aretes->arete_haut = CapaF(I1[i][j], I2[i][j], I1[i-1][j], I2[i-1][j]);
                aretes->arete_droite = CapaF(I1[i][j], I2[i][j], I1[i][j+1], I2[i][j+1]);
                aretes->arete_gauche = CapaF(I1[i][j], I2[i][j], I1[i][j-1], I2[i][j-1]);
                aretes->arete_haut_droit = CapaF(I1[i][j], I2[i][j], I1[i-1][j+1], I2[i-1][j+1]);
                aretes->arete_haut_gauche = CapaF(I1[i][j], I2[i][j], I1[i-1][j-1], I2[i-1][j-1]);
                return aretes;
        }
        if ((j+1>=l)&&(i-1>=0)&&(j-1>=0)&&(i+1<h)) { // cas où le pixel est sur le bord droit mais pas sur le bord haut ou bas
                aretes->arete_haut = CapaF(I1[i][j], I2[i][j], I1[i-1][j], I2[i-1][j]);
                aretes->arete_bas = CapaF(I1[i][j], I2[i][j], I1[i+1][j], I2[i+1][j]);
                aretes->arete_gauche = CapaF(I1[i][j], I2[i][j], I1[i][j-1], I2[i][j-1]);
                aretes->arete_haut_gauche = CapaF(I1[i][j], I2[i][j], I1[i-1][j-1], I2[i-1][j-1]);
                aretes->arete_bas_gauche = CapaF(I1[i][j], I2[i][j], I1[i+1][j-1], I2[i+1][j-1]);
                return aretes;
        }
        if ((i-1<0)&&(j-1>=0)&&(j+1<l)&&(i+1<h)) { // cas où le pixel est sur le bord haut mais pas sur le bord droit ou gauche
                aretes->arete_bas = CapaF(I1[i][j], I2[i][j], I1[i+1][j], I2[i+1][j]);
                aretes->arete_droite = CapaF(I1[i][j], I2[i][j], I1[i][j+1], I2[i][j+1]);
                aretes->arete_gauche = CapaF(I1[i][j], I2[i][j], I1[i][j-1], I2[i][j-1]);
                aretes->arete_bas_droit = CapaF(I1[i][j], I2[i][j], I1[i+1][j+1], I2[i+1][j+1]);
                aretes->arete_bas_gauche = CapaF(I1[i][j], I2[i][j], I1[i+1][j-1], I2[i+1][j-1]);
                return aretes;
        }
        if ((i-1<0)&&(j-1<0)&&(j+1<l)&&(i+1<h)) { // coin gauche haut
               
                aretes->arete_bas = CapaF(I1[i][j], I2[i][j], I1[i+1][j], I2[i+1][j]);
                aretes->arete_droite = CapaF(I1[i][j], I2[i][j], I1[i][j+1], I2[i][j+1]);
                aretes->arete_bas_droit = CapaF(I1[i][j], I2[i][j], I1[i+1][j+1], I2[i+1][j+1]);
                return aretes;
        }
        if ((i-1<0)&&(j+1>=l)&&(j-1>=0)&&(i+1<h)) { // coin droit haut
                
                aretes->arete_bas = CapaF(I1[i][j], I2[i][j], I1[i+1][j], I2[i+1][j]);
                aretes->arete_gauche = CapaF(I1[i][j], I2[i][j], I1[i][j-1], I2[i][j-1]);
                aretes->arete_bas_gauche = CapaF(I1[i][j], I2[i][j], I1[i+1][j-1], I2[i+1][j-1]);
                return aretes;
        }
        if ((i+1>=h)&&(j+1>=l)&&(j-1>=0)&&(i-1>=0)) { // coin droit bas
                aretes->arete_haut = CapaF(I1[i][j], I2[i][j], I1[i-1][j], I2[i-1][j]);
                aretes->arete_gauche = CapaF(I1[i][j], I2[i][j], I1[i][j-1], I2[i][j-1]);
                aretes->arete_haut_gauche = CapaF(I1[i][j], I2[i][j], I1[i-1][j-1], I2[i-1][j-1]);
                return aretes;
        }
        if ((i+1>=h)&&(j-1<0)&&(j+1<l)&&(i-1>=0)) { // coin gauche bas
                aretes->arete_haut = CapaF(I1[i][j], I2[i][j], I1[i-1][j], I2[i-1][j]);
                aretes->arete_droite = CapaF(I1[i][j], I2[i][j], I1[i][j+1], I2[i][j+1]);
                aretes->arete_haut_droit = CapaF(I1[i][j], I2[i][j], I1[i-1][j+1], I2[i-1][j+1]);
                return aretes;
        }
        return NULL;        
}


// Fonction qui libere l'espace occupe par les aretes du graphe
void LibererAretesGraphe(int i, int j, int h, int l, Sommet graphe[h][l]) {
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        free(graphe[i][j].aretes);
                }
        }
}


// Fonction qui affiche la capacite des aretes entre deux images
void AfficherAretes(Aretes *aretes) {
        printf("aretes haut : %f\n", aretes->arete_haut);
        printf("aretes bas : %f\n", aretes->arete_bas);
        printf("arete droite : %f\n", aretes->arete_droite);
        printf("arete gauche : %f\n", aretes->arete_gauche);
        printf("arete haut droit : %f\n", aretes->arete_haut_droit);
        printf("arete haut gauche : %f\n", aretes->arete_haut_gauche);
        printf("arete bas droite : %f\n", aretes->arete_bas_droit);
        printf("aretes bas gauche : %f\n", aretes->arete_bas_gauche);
} 


// Fonction qui met les pixels d'une image/masque dans un tableau
void RemplirTableau(int h, int l, Pixel tab[h][l], FILE *image) {
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        fscanf(image,"%d %d %d", &tab[i][j].R, &tab[i][j].G, &tab[i][j].B);
                        //printf("%d %d %d ", I1[i*l+j].R, I1[i*l+j].G, I1[i*l+j].B);
                }
        }
}


// Fonction qui cree le graphe
void CreationGraphe(int h, int l, Pixel I1[h][l], Pixel I2[h][l], Sommet graphe[h][l]) {
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        graphe[i][j].x = i;
                        graphe[i][j].y = j;
                        graphe[i][j].pixel1 = &I1[i][j];
                        graphe[i][j].pixel2 = &I2[i][j];
                        graphe[i][j].aretes = ConstructionAretes(i, j, h, l, I1, I2);
                        //AfficherAretes(graphe[i][j].aretes);
                }
        }
}


// Fonction qui initialise un pixel test
Pixel *InitialisationpixelNeutre() {
        Pixel *pixel_neutre = malloc(sizeof(Pixel));
        pixel_neutre->R = 256;
        pixel_neutre->G = 256;
        pixel_neutre->B = 256;
        return pixel_neutre; // LIBERE MEMOIRE
}


// Fonction qui initialise les ensembles S et T avec un masque
void InitialisationAvecMasque(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], Pixel M[h][l], Pixel *pixel_neutre) {
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {        
                        if (M[i][j].R == 255 && M[i][j].G == 0 && M[i][j].B == 0) {                                        
                                S[i][j] = graphe[i][j].pixel1;  
                                T[i][j] = pixel_neutre;
                                
                        }
                        else if (M[i][j].R == 0 && M[i][j].G == 0 && M[i][j].B == 255) {
                                T[i][j] = graphe[i][j].pixel2; 
                                S[i][j] = pixel_neutre;
                        }
                        else {
                                S[i][j] = pixel_neutre;
                                T[i][j] = pixel_neutre;
                        }
                        //printf("%d %d %d ", T[i][j]->R, T[i][j]->G, T[i][j]->B);
                }
        }
}



// Fonction qui initialise les ensembles S et T avec un point aleatoire
void InitialisationAleatoire(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], Pixel *pixel_neutre) {
        int n = rand()%h;
        int m = rand()%l;

        int p = rand()%h;
        int q = rand()%l;
        while ((n == p) && (m == q)) {
                n = rand()%h;
                m = rand()%l;
        }
        
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {        
                        if (i == n && j == m) {
                                T[i][j] = graphe[i][j].pixel2;       
                        }                       
                        else {
                                T[i][j] = pixel_neutre;
                        }
                        
                        if (i == p && j == q) {
                                S[i][j] = graphe[i][j].pixel1;   
                        }                        
                        else {
                                S[i][j] = pixel_neutre;  
                        }                 
                }
        }
}


// Fonction qui initialise les ensembles S et T sur les bords
void InitialisationBords(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], Pixel *pixel_neutre) {     
   
        // si l'image est en format paysage, intialisation via bords gauche et droit
        if (l >= h) {
                 for (int i = 0; i < h; i++) {
                        for (int j = 0; j < l; j++) {  
                                if (j == 0) {
                                        S[i][j] = graphe[i][j].pixel1;       
                                }
                                
                                else {
                                        S[i][j] = pixel_neutre;  
                                }
                                if (j == l-1) {
                                        T[i][j] = graphe[i][j].pixel2;
                                }
                                
                                else {
                                        T[i][j] = pixel_neutre;
                                }
                        }
                }
        }        
        
        // si l'image est en format portrait, intialisation via bords haut et bas
        if (h > l) {
                for (int i = 0; i < h; i++) {
                        for (int j = 0; j < l; j++) {        
                                if (i == 0) {
                                        S[i][j] = graphe[i][j].pixel1;       
                                }
                                
                                else {
                                        S[i][j] = pixel_neutre;  
                                }
                                if (i == h-1) {
                                        T[i][j] = graphe[i][j].pixel2;
                                }
                                
                                else {
                                        T[i][j] = pixel_neutre;
                                }
                        }
                }
        }
}



// Fonction qui initialise l'ensemble S sur un bord et T aleatoirement
void InitialisationBordEtAleatoire(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], Pixel *pixel_neutre) {

        // si l'image est en format paysage, intialisation via bords gauche et droit
        if (l >= h) {
                int n = rand()%h;
                int m = rand()%l;
                 for (int i = 0; i < h; i++) {
                        for (int j = 0; j < l; j++) {  
                                if (j == 0) {
                                        S[i][j] = graphe[i][j].pixel1;       
                                }
                                
                                else {
                                        S[i][j] = pixel_neutre;  
                                }
                                if (i == n && j == m) {
                                        T[i][j] = graphe[i][j].pixel2;
                                }
                                
                                else {
                                        T[i][j] = pixel_neutre;
                                }
                        }
                }
        }    
            
        // si l'image est en format portrait, intialisation via bords haut et bas
        if (h > l) {
                int p = rand()%h;
                int q = rand()%l;
                for (int i = 0; i < h; i++) {
                        for (int j = 0; j < l; j++) {        
                                if (i == 0) {
                                        S[i][j] = graphe[i][j].pixel1;       
                                }
                                
                                else {
                                        S[i][j] = pixel_neutre;  
                                }
                                if (i == p && j == q) {
                                        T[i][j] = graphe[i][j].pixel2;
                                }
                                
                                else {
                                        T[i][j] = pixel_neutre;
                                }
                        }
                }
        }
}


// Fonction qui initialise a 0 toutes les cases d'un tableau
void Zero(int h, int l, int tableau[h][l]) {
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        tableau[i][j] = 0;
                }
        }
}


// Fonction qui place les sommets de S dans la file
void SommetsDepartDansFile(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], int visite[h][l], int dans_file[h][l], Pixel *pixel_neutre, File *queue) {
        int ligne;
        int colonne;
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        if (S[i][j] != pixel_neutre) {
                                ligne = i;
                                colonne = j;
                                Enfiler(queue, &graphe[ligne][colonne]);
                                dans_file[ligne][colonne] = 1;
                        }
                }
        }
}


// Fonction pour le parcours en largeur : place les voisins du sommet depile dans la queue
void EnfilerVoisins(Sommet *actuel, int h, int l, Sommet graphe[h][l], int visite[h][l], int dans_file[h][l], File *queue) {
        
        visite[actuel->x][actuel->y] = 1;
        //printf("%d %d\n",actuel->x,actuel->y); // Pour image non carrée à un moment ça prend des coordonnees bizarres bien trop élevées
        
        // On met dans la queue tous les voisins du sommet depile s'ils n'ont pas deja ete visites
        if (((actuel->x)-1 >= 0) && ((actuel->y)-1 >= 0) && ((actuel->x)+1 < h) && ((actuel->y)+1 < l)) { // cas où le pixel est au milieu donc 9 voisins
        
                if (dans_file[(actuel->x)-1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)]); // haut
                        dans_file[(actuel->x)-1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)-1][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)+1]); // haut droite
                        dans_file[(actuel->x)-1][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)+1]); // droite
                        dans_file[(actuel->x)][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)+1]); // bas droite
                        dans_file[(actuel->x)+1][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)]); // bas
                        dans_file[(actuel->x)+1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)-1]); // bas gauche
                        dans_file[(actuel->x)+1][(actuel->y)-1] = 1;
                }                        
                if (dans_file[(actuel->x)][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)-1]); // gauche
                        dans_file[(actuel->x)][(actuel->y)-1] = 1;
                }                        
                if (dans_file[(actuel->x)-1][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)-1]); // haut gauche
                        dans_file[(actuel->x)-1][(actuel->y)-1] = 1;
                }
        }
        
        if (((actuel->y)-1 < 0) && ((actuel->x)-1 >= 0) && ((actuel->x)+1 < h) && ((actuel->y)+1 < l)) { // cas où le pixel est sur le bord gauche, mais non sur le bord haut ou bas
        
                if (dans_file[(actuel->x)-1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)]); // haut
                        dans_file[(actuel->x)-1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)-1][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)+1]); // haut droite
                        dans_file[(actuel->x)-1][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)+1]); // droite
                        dans_file[(actuel->x)][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)+1]); // bas droite
                        dans_file[(actuel->x)+1][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)]); // bas
                        dans_file[(actuel->x)+1][(actuel->y)] = 1;
                }
        }
        
        if (((actuel->x)+1>=h) &&((actuel->y)-1>=0)&&((actuel->y)+1<l)&&((actuel->x)-1>=0)) { // cas où le pixel est sur le bord bas mais pas sur le bord gauche ou droit
          
                if (dans_file[(actuel->x)-1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)]); // haut
                        dans_file[(actuel->x)-1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)-1][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)+1]); // haut droite
                        dans_file[(actuel->x)-1][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)+1]); // droite
                        dans_file[(actuel->x)][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)-1]); // gauche
                        dans_file[(actuel->x)][(actuel->y)-1] = 1;
                }
                if (dans_file[(actuel->x)-1][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)-1]); // haut gauche
                        dans_file[(actuel->x)-1][(actuel->y)-1] = 1;
                }
        }
        
        if (((actuel->y)+1>=l)&&((actuel->x)-1>=0)&&((actuel->y)-1>=0)&&((actuel->x)+1<h)) { // cas où le pixel est sur le bord droit mais pas sur le bord haut ou bas
    
                if (dans_file[(actuel->x)-1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)]); // haut
                        dans_file[(actuel->x)-1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)]); // bas
                        dans_file[(actuel->x)+1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)-1]); // bas gauche
                        dans_file[(actuel->x)+1][(actuel->y)-1] = 1;
                }
                if (dans_file[(actuel->x)][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)-1]); // gauche
                        dans_file[(actuel->x)][(actuel->y)-1] = 1;
                }
                if (dans_file[(actuel->x)-1][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)-1]); // haut gauche
                        dans_file[(actuel->x)-1][(actuel->y)-1] = 1;
                }
                 
        }
        
        if (((actuel->x)-1<0)&&((actuel->y)-1>=0)&&((actuel->y)+1<l)&&((actuel->x)+1<h)) { // cas où le pixel est sur le bord haut mais pas sur le bord droit ou gauche

                if (dans_file[(actuel->x)][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)+1]); // droite
                        dans_file[(actuel->x)][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)+1]); // bas droite
                        dans_file[(actuel->x)+1][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)]); // bas
                        dans_file[(actuel->x)+1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)-1]); // bas gauche
                        dans_file[(actuel->x)+1][(actuel->y)-1] = 1;
                }
                if (dans_file[(actuel->x)][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)-1]); // gauche
                        dans_file[(actuel->x)][(actuel->y)-1] = 1;
                }                      
        }
        
        if (((actuel->x)-1<0)&&((actuel->y)-1<0)&&((actuel->y)+1<l)&&((actuel->x)+1<h)) { // coin gauche haut

                if (dans_file[(actuel->x)][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)+1]); // droite
                        dans_file[(actuel->x)][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)+1]); // bas droite
                        dans_file[(actuel->x)+1][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)]); // bas
                        dans_file[(actuel->x)+1][(actuel->y)] = 1;
                }
        }
        
        if (((actuel->x)-1<0)&&((actuel->y)+1>=l)&&((actuel->y)-1>=0)&&((actuel->x)+1<h)){ // coin droit haut

                if (dans_file[(actuel->x)+1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)]); // bas
                        dans_file[(actuel->x)+1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)+1][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)+1][(actuel->y)-1]); // bas gauche
                        dans_file[(actuel->x)+1][(actuel->y)-1] = 1;
                } 
                if (dans_file[(actuel->x)][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)-1]); // gauche
                        dans_file[(actuel->x)][(actuel->y)-1] = 1;
                }
        }
        
        if (((actuel->x)+1>=h)&&((actuel->y)+1>=l)&&((actuel->y)-1>=0)&&((actuel->x)-1>=0)){ // coin droit bas 

                if (dans_file[(actuel->x)-1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)]); // haut
                        dans_file[(actuel->x)-1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)-1]); // gauche
                        dans_file[(actuel->x)][(actuel->y)-1] = 1;
                }
                if (dans_file[(actuel->x)-1][(actuel->y)-1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)-1]); // haut gauche
                        dans_file[(actuel->x)-1][(actuel->y)-1] = 1;
                }
        }
        
        if (((actuel->x)+1>=h)&&((actuel->y)-1<0)&&((actuel->y)+1<l)&&((actuel->x)-1>=0)){ // coin gauche bas
  
                if (dans_file[(actuel->x)-1][(actuel->y)] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)]); // haut
                        dans_file[(actuel->x)-1][(actuel->y)] = 1;
                }
                if (dans_file[(actuel->x)-1][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)-1][(actuel->y)+1]); // haut droite
                        dans_file[(actuel->x)-1][(actuel->y)+1] = 1;
                }
                if (dans_file[(actuel->x)][(actuel->y)+1] != 1) {
                        Enfiler(queue, &graphe[(actuel->x)][(actuel->y)+1]); // droite
                        dans_file[(actuel->x)][(actuel->y)+1] = 1;
                }
        }
}


// Fonction qui compte le nombre de pixels dans un tableau
int NombrePixelsDansTableau(int h, int l, Pixel *tab[h][l], Pixel *pixel_neutre) {
        int cpt = 0;
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        if (tab[i][j] != pixel_neutre) {
                                cpt ++;
                        }
                }
        }
        return cpt;
}


// Fonction du parcours en largeur
void ParcoursEnLargeur(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], int visite[h][l], Pixel *pixel_neutre) {
        File *queue = InitialisationFile();
        int dans_file[h][l]; // tableau de sommets presents dans la file
  
      
        // Stockage des sommets de S dans la file
        SommetsDepartDansFile(h, l, graphe, S, visite, dans_file, pixel_neutre, queue);

        Sommet *actuel;
        
        int choix2;
        printf("Saisir une conditon d'arret :\nRencontre d'un sommet de T (1) OU apres X iterations (2) : " );
        scanf("%d", &choix2);
        while (choix2 != 1 && choix2 != 2) {
                printf("Saisir une entrée correcte : ");
                scanf("%d", &choix2);
        }
        
        
        // Condition d'arret : rencontre d'un pixel de T
        if (choix2 == 1) {
                int condition_arret = 0;
                while (queue != NULL && condition_arret == 0) {
                        actuel = Defiler(queue);
                        EnfilerVoisins(actuel, h, l, graphe, visite, dans_file, queue);
                        
                        // Si le sommet depile apartient a T, on a rencontre la condition d'arret
                        if (T[actuel->x][actuel->y] != pixel_neutre) {
                                printf("Condition d'arret rencontree.\n\n");
                                condition_arret = 1;
                        }
                }
        }

        
        // Condition d'arret : au bout d'un certain nombre d'iterations
        if (choix2 == 2) {
                int a = NombrePixelsDansTableau(h, l, S, pixel_neutre);                
                int choix3;
                printf("Veuillez choisir le nombre d'iterations (nous conseillons pas plus de %d) : ", (h*l)-a);
                scanf("%d", &choix3);
                while (choix3 > (h*l)-a) {
                        printf("Nous conseillons pas plus de %d : ", (h*l)-a);
                        scanf("%d", &choix3);
                }
                
                int nb_iterations;
                while (queue != NULL && nb_iterations < choix3) {
                        nb_iterations ++;
                        actuel = Defiler(queue);
                        EnfilerVoisins(actuel, h, l, graphe, visite, dans_file, queue);
                }
        }
        
        free(queue);
}


// Fonction qui cree le tableau contenant S et T a la fin d'un parcours
void CreationTableauFinal(int h, int l, Pixel *final[h][l], Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], int visite[h][l], Pixel *pixel_neutre) {
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {        
                        if (S[i][j] != pixel_neutre) {
                                final[i][j] = graphe[i][j].pixel1;
                        }
                        else if (T[i][j] != pixel_neutre) {
                                final[i][j] = graphe[i][j].pixel2;  
                        }
                        else {
                                if (visite[i][j] == 1) {
                                        final[i][j] = graphe[i][j].pixel1;
                                }
                                else {
                                        final[i][j] = graphe[i][j].pixel2;
                                }                                
                        }
                }
        }
}


// Fonction qui cree l'image de sortie
void CreationImageFinal(char *nom_image, int h, int l, Pixel *final[h][l]) {
        FILE* imagePPM = fopen(nom_image, "w");
        fprintf(imagePPM, "P3\n");
        fprintf(imagePPM, "%d %d\n", l, h);
        fprintf(imagePPM, "255\n");
        
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        fprintf(imagePPM, "%d %d %d ", final[i][j]->R, final[i][j]->G, final[i][j]->B);
                }
        }
        
        fclose(imagePPM);
}


// Fonctions utilisee pour l'algorithme de Karger

// Fonction qui initialise une liste
Liste *InitialisationListe() {
        Liste *liste = malloc(sizeof(Liste));
        if (liste == NULL) {
                return NULL;
        }
        liste->premier = NULL;
        return liste;
}


// Fonction qui insere un nouvel element dans une Liste
void Insertion(Liste *liste, double arete, int i, int j) {
        Cellule *nouveau = malloc(sizeof(Cellule));
        if (nouveau == NULL) {
                printf("L'insertion n'a pas abouti.\n");
        }
        nouveau->arete = arete;
        nouveau->coord_x = i;
        nouveau->coord_y = j;
        nouveau->suivant = liste->premier;
        liste->premier = nouveau;
}


// Fonction qui cree un tableai contenant une liste chainee des aretes de chaque sommet
void CreationVoisins(int h, int l, Liste *voisins[h][l], Sommet graphe[h][l]) {
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        voisins[i][j] = InitialisationListe();
                        Insertion(voisins[i][j], graphe[i][j].aretes->arete_haut, i-1, j);
                        Insertion(voisins[i][j], graphe[i][j].aretes->arete_haut_droit, i-1, j+1);
                        Insertion(voisins[i][j], graphe[i][j].aretes->arete_droite, i, j+1);
                        Insertion(voisins[i][j], graphe[i][j].aretes->arete_bas_droit, i+1, j+1);
                        Insertion(voisins[i][j], graphe[i][j].aretes->arete_bas, i+1, j);
                        Insertion(voisins[i][j], graphe[i][j].aretes->arete_bas_gauche, i+1, j-1);
                        Insertion(voisins[i][j], graphe[i][j].aretes->arete_gauche, i, j-1);
                        Insertion(voisins[i][j], graphe[i][j].aretes->arete_haut_gauche, i-1, j-1);
                }
        }
}


// Fonction qui initialise une liste de sommets
ListeSommets *InitialisationListeSommets(void) {
        ListeSommets *liste = malloc(sizeof(ListeSommets));
        if (liste == NULL) {
                return NULL;
        }
        liste->tete = NULL;
        return liste;
}


// Fonction qui insere un sommet dans une liste de sommets
void InsertionSommet(ListeSommets *liste, Sommet *sommet, int i, int j) {
        CelluleSommet *nouveau = malloc(sizeof(CelluleSommet));
        if (nouveau == NULL) {
                printf("L'insertion n'a pas abouti, plus de place pour inserer un sommet.\n");
        }
        nouveau->sommetcellule = sommet;
        nouveau->coord2_x = i;
        nouveau->coord2_y = j;
        nouveau->suivant = liste->tete;
        liste->tete = nouveau;
}


// Fonction qui supprime l'arete dont les coordonnées sont i et j dans la liste d'aretes de u
void SupprimerArete(int h, int l, int x, int y, Liste *voisins[h][l],int i, int j) {
        Cellule *tmp = voisins[x][y]->premier;
        if (tmp->coord_x == i && tmp->coord_y == j) {
                voisins[x][y]->premier = tmp->suivant;
                free(tmp);
        }
        while (tmp->suivant != NULL){
                if (tmp->suivant->coord_x == i && tmp->suivant->coord_y == j) {
                        Cellule *supprimer = tmp->suivant;
                        tmp->suivant = tmp->suivant->suivant;
                        free(supprimer);
                }
                else {
                        tmp = tmp->suivant;
                }
       }
}
                        

// Fonction qui contracte deux sommets
void Contraction(int h, int l, Sommet u, Sommet v, Sommet graphe[h][l], Liste *voisins[h][l], ListeSommets *tab_liste_sommets[h][l]) {
        Insertion(voisins[u.x][u.y], graphe[v.x][v.y].aretes->arete_haut, (u.x)-1, u.y);
        Insertion(voisins[u.x][u.y], graphe[v.x][v.y].aretes->arete_haut_droit, (u.x)-1, (u.y)+1);
        Insertion(voisins[u.x][u.y], graphe[v.x][v.y].aretes->arete_droite, (u.x), (u.y)+1);
        Insertion(voisins[u.x][u.y], graphe[v.x][v.y].aretes->arete_bas_droit, (u.x)+1, (u.y)+1);
        Insertion(voisins[u.x][u.y], graphe[v.x][v.y].aretes->arete_bas, (u.x)+1, u.y);
        Insertion(voisins[u.x][u.y], graphe[v.x][v.y].aretes->arete_bas_gauche, (u.x)+1, (u.y)-1);
        Insertion(voisins[u.x][u.y], graphe[v.x][v.y].aretes->arete_gauche, (u.x), (u.y)-1);
        Insertion(voisins[u.x][u.y], graphe[v.x][v.y].aretes->arete_haut_gauche, (u.x)-1, (u.y)-1);
        
        
        InsertionSommet(tab_liste_sommets[u.x][u.y], &v, v.x, v.y);
        CelluleSommet *tampon = tab_liste_sommets[v.x][v.y]->tete;
        while (tampon != NULL) {
                InsertionSommet(tab_liste_sommets[u.x][u.y], tampon->sommetcellule, tampon->coord2_x, tampon->coord2_y);
                tampon = tampon->suivant;
        }
        
        // Supression des aretes en double
        SupprimerArete(h, l, u.x, u.y, voisins, v.x, v.y);
        
        v = u;
        tab_liste_sommets[v.x][v.y] = tab_liste_sommets[u.x][u.y];
        
        // Tous les sommets representant u vont prendre les nouveaux parametres de u
        CelluleSommet *tampon2 = tab_liste_sommets[u.x][u.y]->tete;
        while (tampon2 != NULL) {
                tampon2->sommetcellule = &u;
                tab_liste_sommets[tampon2->coord2_x][tampon2->coord2_y] =  tab_liste_sommets[u.x][u.y];
                tampon2 = tampon2->suivant;
        }
        
}
                

// Fonction qui compte les sommets qui sont encore contractables qui sont mis en 0
int CompterSommetsContractables( int h, int l, int  sommets_contractes[h][l]) { // on compte les sommets qui sont encore contractables qui sont mis en 0
        int sommets_contractables = 0;
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        if (sommets_contractes[i][j] == 0) {
                                sommets_contractables++;
                        }     
                }
        }
        return sommets_contractables;
}    


// Fonction qui effectue l'algorithme de Karger 
void Karger(int h, int l, int sommets_contractes[h][l], Liste *voisins[h][l], Sommet graphe[h][l], Pixel *final[h][l]) {
        ListeSommets *tab_liste_sommets[h][l];
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        tab_liste_sommets[i][j] = InitialisationListeSommets();
                }
        }        
        while (CompterSommetsContractables(h, l, sommets_contractes) > 2) {
                int i = rand()%h;
                int j = rand()%l;
                
                while (sommets_contractes[i][j] == 1 ||
                      (sommets_contractes[i][j] == 1 &&
                       sommets_contractes[i+1][j] == 1 &&
                       sommets_contractes[i-1][j] == 1 &&
                       sommets_contractes[i][j+1] == 1 &&
                       sommets_contractes[i][j-1] == 1 &&
                       sommets_contractes[i+1][j+1] == 1 &&
                       sommets_contractes[i-1][j-1] == 1 &&
                       sommets_contractes[i-1][j+1] == 1 &&
                       sommets_contractes[i+1][j-1] == 1)) {
                       
                        i = rand()%h;
                        j = rand()%l;
                }
                
                Cellule *temp = voisins[i][j]->premier;
                while (temp->arete == 0) {
                        temp = temp->suivant;
                }
                /*int position_arete = 0;
                int compteur = 1;
                int max_capa = temp->arete;
                while (temp->suivant != NULL) {
                        if (temp->arete > max_capa) {
                                max_capa = temp->arete;
                                position_arete = compteur;
                        }
                        compteur++;
                 }
                 compteur = 0;
                 temp = voisins[i][j]->premier;
                 while (compteur != position_arete){
                        temp=temp->suivant;
                 }*/
                 printf("LA-3\n");
                 printf("%d %d ", i, j);
                 printf("%d %d ", temp->coord_x, temp->coord_y);
                 
                 Contraction(h, l, graphe[temp->coord_x][temp->coord_y], graphe[i][j], graphe, voisins, tab_liste_sommets);
                 printf("Encore contr : %d\n",CompterSommetsContractables(h, l, sommets_contractes));
                 sommets_contractes[temp->coord_x][temp->coord_y] = 1;
        }
        
        int condition_boucle = 0;
        for (int i = 0; i < h; i++) {
                for (int j = 0; j < l; j++) {
                        if (sommets_contractes[i][j] == 0 && condition_boucle == 0) {
                                CelluleSommet *dans_final = tab_liste_sommets[i][j]->tete;
                                while (dans_final != NULL) {
                                        final[dans_final->coord2_x][dans_final->coord2_y] = graphe[dans_final->coord2_x][dans_final->coord2_y].pixel1;
                                        dans_final = dans_final->suivant;
                                }
                                sommets_contractes[i][j] = 1;
                                condition_boucle = 1;
                        }
                        if (sommets_contractes[i][j] == 0 && condition_boucle == 1) {
                                CelluleSommet *dans_final = tab_liste_sommets[i][j]->tete;
                                while (dans_final != NULL) {
                                        final[dans_final->coord2_x][dans_final->coord2_y] = graphe[dans_final->coord2_x][dans_final->coord2_y].pixel2;
                                        dans_final = dans_final->suivant;
                                }
                                sommets_contractes[i][j] = 1;
                                condition_boucle = 2;
                                break;
                        }
                }
                if (condition_boucle == 2) {
                        break;
                }
        }
}

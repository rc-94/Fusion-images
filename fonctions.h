#ifndef FONCTIONS_H
#define FONCTIONS_H


// Structures Pixe, Aretes et Sommet
typedef struct {
        int R;
        int G;
        int B;
} Pixel;

typedef struct {
        double arete_haut;
        double arete_bas;
        double arete_droite;
        double arete_gauche;
        double arete_haut_droit;
        double arete_haut_gauche;
        double arete_bas_droit;
        double arete_bas_gauche;
} Aretes;
        
typedef struct {
        Pixel *pixel1;
        Pixel *pixel2;
        Aretes *aretes;
        int x;
        int y;
} Sommet;


// Structure Element et File
typedef struct element {
        Sommet* valeur;
        struct element *suivant;
} Element;

typedef struct {
        Element *premier;
} File;


//Fonction qui enfile un element dans une file
void Enfiler(File *file, Sommet *sommet);


// Fonction qui defile une file
Sommet* Defiler(File *file);


// Fonction qui initialise une file
File *InitialisationFile(void);


// Fonction delta
double delta(Pixel p1, Pixel p2);


// Fonction qui calcule la capacite des aretes
double CapaF(Pixel p11, Pixel p21, Pixel p12, Pixel p22);


//Fonction qui construit les aretes entre les deux images
Aretes *ConstructionAretes(int i, int j, int h, int l, Pixel I1[h][l], Pixel I2[h][l]);


// Fonction qui libere l'espace occupe par les aretes du graphe
void LibererAretesGraphe(int i, int j, int h, int l, Sommet graphe[h][l]);


// Fonction qui affiche la capacite des aretes entre deux images A ENLEVER
void AfficherAretes(Aretes *aretes);


// Fonction qui met les pixels d'une image/masque dans un tableau
void RemplirTableau(int h, int l, Pixel tab[h][l], FILE *image);


// Fonction qui cree le graphe
void CreationGraphe(int h, int l, Pixel I1[h][l], Pixel I2[h][l], Sommet graphe[h][l]);


// Fonction qui initialise un pixel test
Pixel *InitialisationpixelNeutre();


// Fonction qui initialise les ensembles S et T avec un masque
void InitialisationAvecMasque(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], Pixel M[h][l], Pixel *pixel_neutre);


// Fonction qui initialise les ensembles S et T avec un point aleatoire
void InitialisationAleatoire(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], Pixel *pixel_neutre);


// Fonction qui initialise les ensembles S et T sur les bords
void InitialisationBords(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], Pixel *pixel_neutre);


// Fonction qui initialise l'ensemble S sur un bord et T aleatoirement
void InitialisationBordEtAleatoire(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], Pixel *pixel_neutre);


// Fonction qui initialise a 0 toutes les cases d'un tableau
void Zero(int h, int l, int tableau[h][l]);


// Fonction qui place les sommets de S dans la file
void SommetsDepartDansFile(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], int visite[h][l], int dans_file[h][l], Pixel *pixel_neutre, File *queue);


// Fonction pour le parcours en largeur : place les voisins du sommet depile dans la queue
void EnfilerVoisins(Sommet *actuel, int h, int l, Sommet graphe[h][l], int visite[h][l], int dans_file[h][l], File *queue);


// Fonction qui compte le nombre de pixels dans un tableau
int NombrePixelsDansTableau(int h, int l, Pixel *tab[h][l], Pixel *pixel_neutre);


// Fonction du parcours en largeur
void ParcoursEnLargeur(int h, int l, Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], int visite[h][l], Pixel *pixel_neutre);


// Fonction qui cree le tableau contenant S et T a la fin d'un parcours
void CreationTableauFinal(int h, int l, Pixel *final[h][l], Sommet graphe[h][l], Pixel *S[h][l], Pixel *T[h][l], int visite[h][l], Pixel *pixel_neutre);


// Fonction qui cree l'image de sortie
void CreationImageFinal(char *nom_image, int h, int l, Pixel *final[h][l]);


// Fonction de floutage sur un pixel
void FlouPixel(int i, int j, int h, int l, Sommet graphe[h][l], int visite[h][l], Pixel *final[h][l]);


// Fonction de floutage qui module la distance
void Flou(int h, int l, Sommet graphe[h][l], int visite[h][l], Pixel *final[h][l]);


// Fonctions et structures pour l'algorithme de karger

//Structures Cellule et Liste
typedef struct cellule {
        double arete;
        int coord_x;
        int coord_y;
        struct cellule *suivant;
} Cellule;


typedef struct {
        Cellule *premier;
} Liste;

// Fonction qui initialise une Liste
Liste *InitialisationListe();


// Fonction qui insere un nouvel element dans une Liste
void Insertion(Liste *liste, double arete, int i, int j);


// Fonction qui cree un tableai contenant une liste chainee des aretes de chaque sommet
void CreationVoisins(int h, int l, Liste *voisins[h][l], Sommet graphe[h][l]);


// Structures CelluleSommet et ListeSommets permettant de creer une liste de sommets
typedef struct cellulesommet {
        Sommet *sommetcellule;
        int coord2_x;
        int coord2_y;
        struct cellulesommet *suivant;
} CelluleSommet;


typedef struct {
        CelluleSommet *tete;
} ListeSommets;


// Fonction qui initialise une liste de sommets
ListeSommets *InitialisationListeSommets(void);


// Fonction qui insere un sommet dans une liste de sommets
void InsertionSommet(ListeSommets *liste, Sommet *sommet, int i, int j);


// Fonction qui supprime l'arete dont les coordonnées sont i et j dans la liste d'aretes de u
void SupprimerArete(int h, int l, int x, int y, Liste *voisins[h][l],int i, int j);


// Fonction qui contracte deux sommets
void Contraction(int h, int l, Sommet u, Sommet v, Sommet graphe[h][l], Liste *voisins[h][l], ListeSommets *tab_liste_sommets[h][l]);


// Fonction qui compte les sommets qui sont encore contractables qui sont mis en 0
int CompterSommetsContractables( int h, int l, int  sommets_contractes[h][l]);

// Fonction qui effectue l'algorithme de Karger 
void Karger(int h, int l, int sommets_contractes[h][l], Liste *voisins[h][l], Sommet graphe[h][l], Pixel *final[h][l]);


#endif

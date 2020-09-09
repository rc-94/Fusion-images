#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "fonctions.h"


// Fonction de floutage qui module la distance
void Flou(int h, int l, Sommet graphe[h][l], int visite[h][l], Pixel *final[h][l]){
        for (int i = 0; i < h-2; i++) {
                for (int j = 0; j < l-2; j++) {
                        FlouPixel(i,j,h,l,graphe,visite,final);
                }
        }
}


// Fonction de floutage sur un pixel
void FlouPixel(int i, int j, int h, int l, Sommet graphe[h][l], int visite[h][l], Pixel *final[h][l]){
        if (visite[i][j]==0 && visite[i][j+1]==1){ // d=1 pour l'instant, donc tous les sommets a distance d du sommet de S et du sommet de T
                int Rmax=graphe[i][j].pixel2->R;
                int Gmax=graphe[i][j].pixel2->G;
                int Bmax=graphe[i][j].pixel2->B;
                int nb_pixels=0;
                if (graphe[i][j].aretes->arete_gauche!=0){ // on somme les valeurs RGB des sommets voisins du pixel[i][j]
                        if (visite[i][j-1]==1){
                                Rmax=Rmax+graphe[i][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas_gauche!=0){
                        if (visite[i+1][j-1]==1){
                                Rmax=Rmax+graphe[i+1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas!=0){
                        if (visite[i+1][j]==1){
                                Rmax=Rmax+graphe[i+1][j].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas_droit!=0){
                        if (visite[i+1][j+1]==1){
                                Rmax=Rmax+graphe[i+1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_droite!=0){
                        if (visite[i][j+1]==1){
                                Rmax=Rmax+graphe[i][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut_droit!=0){
                        if (visite[i-1][j+1]==1){
                                Rmax=Rmax+graphe[i-1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut!=0){
                        if (visite[i-1][j]==1){
                                Rmax=Rmax+graphe[i-1][j].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut_gauche!=0){
                        if (visite[i-1][j-1]==1){
                                Rmax=Rmax+graphe[i-1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_gauche!=0){ // on somme les valeurs RGB des sommets voisins du pixel[i][j+1]
                        if (visite[i][j]==1){
                                Rmax=Rmax+graphe[i][j].pixel1->R;
                                Gmax=Gmax+graphe[i][j].pixel1->G;
                                Bmax=Bmax+graphe[i][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j].pixel2->R;
                                Gmax=Gmax+graphe[i][j].pixel2->G;
                                Bmax=Bmax+graphe[i][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_bas_gauche!=0){
                        if (visite[i+1][j-1]==1){
                                Rmax=Rmax+graphe[i+1][j].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_bas!=0){
                        if (visite[i+1][j]==1){
                                Rmax=Rmax+graphe[i+1][j].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_bas_droit!=0){
                        if (visite[i+1][j+1]==1){
                                Rmax=Rmax+graphe[i+1][j+2].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j+2].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j+2].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j+2].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j+2].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j+2].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_droite!=0){
                        if (visite[i][j+1]==1){
                                Rmax=Rmax+graphe[i][j+2].pixel1->R;
                                Gmax=Gmax+graphe[i][j+2].pixel1->G;
                                Bmax=Bmax+graphe[i][j+2].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j+2].pixel2->R;
                                Gmax=Gmax+graphe[i][j+2].pixel2->G;
                                Bmax=Bmax+graphe[i][j+2].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_haut_droit!=0){
                        if (visite[i-1][j+1]==1){
                                Rmax=Rmax+graphe[i-1][j+2].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j+2].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j+2].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j+2].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j+2].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j+2].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_haut!=0){
                        if (visite[i-1][j]==1){
                                Rmax=Rmax+graphe[i-1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_haut_gauche!=0){
                        if (visite[i-1][j-1]==1){
                                Rmax=Rmax+graphe[i-1][j].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }

                int Rmoy=Rmax/nb_pixels; // on calcule les valeurs moyennes RGB de ces pixels
                int Gmoy=Gmax/nb_pixels;
                int Bmoy=Bmax/nb_pixels;

                if (graphe[i][j].aretes->arete_gauche!=0){
                        final[i][j-1]->R=Rmoy;
                        final[i][j-1]->G=Gmoy;
                        final[i][j-1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas_gauche!=0){
                        final[i+1][j-1]->R=Rmoy;
                        final[i+1][j-1]->G=Gmoy;
                        final[i+1][j-1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas!=0){
                        final[i+1][j]->R=Rmoy;
                        final[i+1][j]->G=Gmoy;
                        final[i+1][j]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas_droit!=0){
                        final[i+1][j+1]->R=Rmoy;
                        final[i+1][j+1]->G=Gmoy;
                        final[i+1][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_droite!=0){
                        final[i][j+1]->R=Rmoy;
                        final[i][j+1]->G=Gmoy;
                        final[i][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut_droit!=0){
                        final[i-1][j+1]->R=Rmoy;
                        final[i-1][j+1]->G=Gmoy;
                        final[i-1][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut!=0){
                        final[i-1][j]->R=Rmoy;
                        final[i-1][j]->G=Gmoy;
                        final[i-1][j]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut_gauche!=0){
                        final[i-1][j-1]->R=Rmoy;
                        final[i-1][j-1]->G=Gmoy;
                        final[i-1][j-1]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_gauche!=0){
                        final[i][j]->R=Rmoy;
                        final[i][j]->G=Gmoy;
                        final[i][j]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_bas_gauche!=0){
                        final[i+1][j]->R=Rmoy;
                        final[i+1][j]->G=Gmoy;
                        final[i+1][j]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_bas!=0){
                        final[i+1][j+1]->R=Rmoy;
                        final[i+1][j+1]->G=Gmoy;
                        final[i+1][j+1]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_bas_droit!=0){
                        final[i+1][j+2]->R=Rmoy;
                        final[i+1][j+2]->G=Gmoy;
                        final[i+1][j+2]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_droite!=0){
                        final[i][j+2]->R=Rmoy;
                        final[i][j+2]->G=Gmoy;
                        final[i][j+2]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_haut_droit!=0){
                        final[i-1][j+2]->R=Rmoy;
                        final[i-1][j+2]->G=Gmoy;
                        final[i-1][j+2]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_haut!=0){
                        final[i-1][j+1]->R=Rmoy;
                        final[i-1][j+1]->G=Gmoy;
                        final[i-1][j+1]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_haut_gauche!=0){
                        final[i-1][j]->R=Rmoy;
                        final[i-1][j]->G=Gmoy;
                        final[i-1][j]->B=Bmoy;
                }
        }

        if (visite[i][j]==1 && visite[i][j+1]==0){

                int Rmax=graphe[i][j].pixel1->R;
                int Gmax=graphe[i][j].pixel1->G;
                int Bmax=graphe[i][j].pixel1->B;
                int nb_pixels=0;
                
                if (graphe[i][j].aretes->arete_gauche!=0){ // on somme les valeurs RGB des sommets voisins du pixel[i][j]
                        if (visite[i][j-1]==1){
                                Rmax=Rmax+graphe[i][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i][j-1].pixel1->B;
                        }
                        else{                             
                                Rmax=Rmax+graphe[i][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas_gauche!=0){
                        if (visite[i+1][j-1]==1){
                                Rmax=Rmax+graphe[i+1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel2->B;
                               
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas!=0){
                        if (visite[i+1][j]==1){
                                Rmax=Rmax+graphe[i+1][j].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j].pixel1->B;
                        }
                        else{                               
                                Rmax=Rmax+graphe[i+1][j].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas_droit!=0){
                        if (visite[i+1][j+1]==1){
                                Rmax=Rmax+graphe[i+1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel2->B;                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_droite!=0){
                        if (visite[i][j+1]==1){
                                Rmax=Rmax+graphe[i][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i][j+1].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut_droit!=0){
                        if (visite[i-1][j+1]==1){
                                Rmax=Rmax+graphe[i-1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut!=0){
                        if (visite[i-1][j]==1){
                                Rmax=Rmax+graphe[i-1][j].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut_gauche!=0){
                        if (visite[i-1][j-1]==1){
                                Rmax=Rmax+graphe[i-1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j-1].pixel2->B;                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_gauche!=0){ // on somme les valeurs RGB des sommets voisins du pixel[i][j+1]
                        if (visite[i][j]==1){
                                Rmax=Rmax+graphe[i][j].pixel1->R;
                                Gmax=Gmax+graphe[i][j].pixel1->G;
                                Bmax=Bmax+graphe[i][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j].pixel2->R;
                                Gmax=Gmax+graphe[i][j].pixel2->G;
                                Bmax=Bmax+graphe[i][j].pixel2->B;
                                Rmax=Rmax+graphe[i][j].pixel1->R;
                                Gmax=Gmax+graphe[i][j].pixel1->G;
                                Bmax=Bmax+graphe[i][j].pixel1->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_bas_gauche!=0){
                        if (visite[i+1][j-1]==1){
                                Rmax=Rmax+graphe[i+1][j].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_bas!=0){
                        if (visite[i+1][j]==1){
                                Rmax=Rmax+graphe[i+1][j].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_bas_droit!=0){
                        if (visite[i+1][j+1]==1){
                                Rmax=Rmax+graphe[i+1][j+2].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j+2].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j+2].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j+2].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j+2].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j+2].pixel2->B;                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_droite!=0){
                        if (visite[i][j+1]==1){
                                Rmax=Rmax+graphe[i][j+2].pixel1->R;
                                Gmax=Gmax+graphe[i][j+2].pixel1->G;
                                Bmax=Bmax+graphe[i][j+2].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j+2].pixel2->R;
                                Gmax=Gmax+graphe[i][j+2].pixel2->G;
                                Bmax=Bmax+graphe[i][j+2].pixel2->B;                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_haut_droit!=0){
                        if (visite[i-1][j+1]==1){
                                Rmax=Rmax+graphe[i-1][j+2].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j+2].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j+2].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j+2].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j+2].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j+2].pixel2->B;                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_haut!=0){
                        if (visite[i-1][j]==1){
                                Rmax=Rmax+graphe[i-1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_haut_gauche!=0){
                        if (visite[i-1][j-1]==1){
                                Rmax=Rmax+graphe[i-1][j].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }

                int Rmoy=Rmax/nb_pixels; // on calcule les valeurs moyennes RGB de ces pixels
                int Gmoy=Gmax/nb_pixels;
                int Bmoy=Bmax/nb_pixels;

                if (graphe[i][j].aretes->arete_gauche!=0){
                        final[i][j-1]->R=Rmoy;
                        final[i][j-1]->G=Gmoy;
                        final[i][j-1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas_gauche!=0){
                        final[i+1][j-1]->R=Rmoy;
                        final[i+1][j-1]->G=Gmoy;
                        final[i+1][j-1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas!=0){
                        final[i+1][j]->R=Rmoy;
                        final[i+1][j]->G=Gmoy;
                        final[i+1][j]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas_droit!=0){
                        final[i+1][j+1]->R=Rmoy;
                        final[i+1][j+1]->G=Gmoy;
                        final[i+1][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_droite!=0){
                        final[i][j+1]->R=Rmoy;
                        final[i][j+1]->G=Gmoy;
                        final[i][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut_droit!=0){
                        final[i-1][j+1]->R=Rmoy;
                        final[i-1][j+1]->G=Gmoy;
                        final[i-1][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut!=0){
                        final[i-1][j]->R=Rmoy;
                        final[i-1][j]->G=Gmoy;
                        final[i-1][j]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut_gauche!=0){
                        final[i-1][j-1]->R=Rmoy;
                        final[i-1][j-1]->G=Gmoy;
                        final[i-1][j-1]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_gauche!=0){
                        final[i][j]->R=Rmoy;
                        final[i][j]->G=Gmoy;
                        final[i][j]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_bas_gauche!=0){
                        final[i+1][j]->R=Rmoy;
                        final[i+1][j]->G=Gmoy;
                        final[i+1][j]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_bas!=0){
                        final[i+1][j+1]->R=Rmoy;
                        final[i+1][j+1]->G=Gmoy;
                        final[i+1][j+1]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_bas_droit!=0){
                        final[i+1][j+2]->R=Rmoy;
                        final[i+1][j+2]->G=Gmoy;
                        final[i+1][j+2]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_droite!=0){
                        final[i][j+2]->R=Rmoy;
                        final[i][j+2]->G=Gmoy;
                        final[i][j+2]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_haut_droit!=0){
                        final[i-1][j+2]->R=Rmoy;
                        final[i-1][j+2]->G=Gmoy;
                        final[i-1][j+2]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_haut!=0){
                        final[i-1][j+1]->R=Rmoy;
                        final[i-1][j+1]->G=Gmoy;
                        final[i-1][j+1]->B=Bmoy;
                }
                if (graphe[i][j+1].aretes->arete_haut_gauche!=0){
                        final[i-1][j]->R=Rmoy;
                        final[i-1][j]->G=Gmoy;
                        final[i-1][j]->B=Bmoy;
                }
        }
        
        if (visite[i][j]==0 && visite[i+1][j]==1){ // d=1 pour l'instant, donc tous les sommets a distance d du sommet de S et du sommet de T
                int Rmax=graphe[i][j].pixel2->R;
                int Gmax=graphe[i][j].pixel2->G;
                int Bmax=graphe[i][j].pixel2->B;
                int nb_pixels=0;
                if (graphe[i][j].aretes->arete_gauche!=0){ // on somme les valeurs RGB des sommets voisins du pixel[i][j]
                        if (visite[i][j-1]==1){
                                Rmax=Rmax+graphe[i][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas_gauche!=0){
                        if (visite[i+1][j-1]==1){
                                Rmax=Rmax+graphe[i+1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas!=0){
                        if (visite[i+1][j]==1){
                                Rmax=Rmax+graphe[i+1][j].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas_droit!=0){
                        if (visite[i+1][j+1]==1){
                                Rmax=Rmax+graphe[i+1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_droite!=0){
                        if (visite[i][j+1]==1){
                                Rmax=Rmax+graphe[i][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut_droit!=0){
                        if (visite[i-1][j+1]==1){
                                Rmax=Rmax+graphe[i-1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut!=0){
                        if (visite[i-1][j]==1){
                                Rmax=Rmax+graphe[i-1][j].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut_gauche!=0){
                        if (visite[i-1][j-1]==1){
                                Rmax=Rmax+graphe[i-1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_gauche!=0){ // on somme les valeurs RGB des sommets voisins du pixel[i][j+1]
                        if (visite[i+1][j-1]==1){
                                Rmax=Rmax+graphe[i+1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_bas_gauche!=0){
                        if (visite[i+2][j-1]==1){
                                Rmax=Rmax+graphe[i+2][j].pixel1->R;
                                Gmax=Gmax+graphe[i+2][j].pixel1->G;
                                Bmax=Bmax+graphe[i+2][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+2][j].pixel2->R;
                                Gmax=Gmax+graphe[i+2][j].pixel2->G;
                                Bmax=Bmax+graphe[i+2][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_bas!=0){
                        if (visite[i+2][j]==1){
                                Rmax=Rmax+graphe[i+2][j].pixel1->R;
                                Gmax=Gmax+graphe[i+2][j].pixel1->G;
                                Bmax=Bmax+graphe[i+2][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+2][j].pixel2->R;
                                Gmax=Gmax+graphe[i+2][j].pixel2->G;
                                Bmax=Bmax+graphe[i+2][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_bas_droit!=0){
                        if (visite[i+2][j+1]==1){
                                Rmax=Rmax+graphe[i+2][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i+2][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i+2][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+2][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i+2][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i+2][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_droite!=0){
                        if (visite[i+1][j+1]==1){
                                Rmax=Rmax+graphe[i+1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_haut_droit!=0){
                        if (visite[i][j+1]==1){
                                Rmax=Rmax+graphe[i][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_haut!=0){
                        if (visite[i][j]==1){
                                Rmax=Rmax+graphe[i][j].pixel1->R;
                                Gmax=Gmax+graphe[i][j].pixel1->G;
                                Bmax=Bmax+graphe[i][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j].pixel2->R;
                                Gmax=Gmax+graphe[i][j].pixel2->G;
                                Bmax=Bmax+graphe[i][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_haut_gauche!=0){
                        if (visite[i][j-1]==1){
                                Rmax=Rmax+graphe[i][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }

                int Rmoy=Rmax/nb_pixels; // on calcule les valeurs moyennes RGB de ces pixels
                int Gmoy=Gmax/nb_pixels;
                int Bmoy=Bmax/nb_pixels;

                if (graphe[i][j].aretes->arete_gauche!=0){
                        final[i][j-1]->R=Rmoy;
                        final[i][j-1]->G=Gmoy;
                        final[i][j-1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas_gauche!=0){
                        final[i+1][j-1]->R=Rmoy;
                        final[i+1][j-1]->G=Gmoy;
                        final[i+1][j-1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas!=0){
                        final[i+1][j]->R=Rmoy;
                        final[i+1][j]->G=Gmoy;
                        final[i+1][j]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas_droit!=0){
                        final[i+1][j+1]->R=Rmoy;
                        final[i+1][j+1]->G=Gmoy;
                        final[i+1][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_droite!=0){
                        final[i][j+1]->R=Rmoy;
                        final[i][j+1]->G=Gmoy;
                        final[i][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut_droit!=0){
                        final[i-1][j+1]->R=Rmoy;
                        final[i-1][j+1]->G=Gmoy;
                        final[i-1][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut!=0){
                        final[i-1][j]->R=Rmoy;
                        final[i-1][j]->G=Gmoy;
                        final[i-1][j]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut_gauche!=0){
                        final[i-1][j-1]->R=Rmoy;
                        final[i-1][j-1]->G=Gmoy;
                        final[i-1][j-1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_gauche!=0){
                        final[i+1][j-1]->R=Rmoy;
                        final[i+1][j-1]->G=Gmoy;
                        final[i+1][j-1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_bas_gauche!=0){
                        final[i+2][j-1]->R=Rmoy;
                        final[i+2][j-1]->G=Gmoy;
                        final[i+2][j-1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_bas!=0){
                        final[i+2][j]->R=Rmoy;
                        final[i+2][j]->G=Gmoy;
                        final[i+2][j]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_bas_droit!=0){
                        final[i+2][j+1]->R=Rmoy;
                        final[i+2][j+1]->G=Gmoy;
                        final[i+2][j+1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_droite!=0){
                        final[i+1][j+1]->R=Rmoy;
                        final[i+1][j+1]->G=Gmoy;
                        final[i+1][j+1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_haut_droit!=0){
                        final[i][j+1]->R=Rmoy;
                        final[i][j+1]->G=Gmoy;
                        final[i][j+1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_haut!=0){
                        final[i][j]->R=Rmoy;
                        final[i][j]->G=Gmoy;
                        final[i][j]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_haut_gauche!=0){
                        final[i][j-1]->R=Rmoy;
                        final[i][j-1]->G=Gmoy;
                        final[i][j-1]->B=Bmoy;
                }
        }

        if (visite[i][j]==1 && visite[i+1][j]==0) {
                int Rmax=graphe[i][j].pixel1->R;
                int Gmax=graphe[i][j].pixel1->G;
                int Bmax=graphe[i][j].pixel1->B;
                int nb_pixels=0;
                if (graphe[i][j].aretes->arete_gauche!=0){ // on somme les valeurs RGB des sommets voisins du pixel[i][j]
                        if (visite[i][j-1]==1){
                                Rmax=Rmax+graphe[i][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i][j-1].pixel1->B;                                
                        }
                        else{
                                Rmax=Rmax+graphe[i][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i][j-1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas_gauche!=0){
                        if (visite[i+1][j-1]==1){
                                Rmax=Rmax+graphe[i+1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel2->B;                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas!=0){
                        if (visite[i+1][j]==1){
                                Rmax=Rmax+graphe[i+1][j].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j].pixel1->B;
                                
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_bas_droit!=0){
                        if (visite[i+1][j+1]==1){
                                Rmax=Rmax+graphe[i+1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel2->B;                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_droite!=0){
                        if (visite[i][j+1]==1){
                                Rmax=Rmax+graphe[i][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i][j+1].pixel2->B;                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut_droit!=0){
                        if (visite[i-1][j+1]==1){
                                Rmax=Rmax+graphe[i-1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel1->B;                               
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut!=0){
                        if (visite[i-1][j]==1){
                                Rmax=Rmax+graphe[i-1][j].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j].pixel2->B;                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j].aretes->arete_haut_gauche!=0){
                        if (visite[i-1][j-1]==1){
                                Rmax=Rmax+graphe[i-1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i-1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i-1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i-1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i-1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i-1][j-1].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_gauche!=0){ // on somme les valeurs RGB des sommets voisins du pixel[i][j+1]
                        if (visite[i+1][j-1]==1){
                                Rmax=Rmax+graphe[i+1][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j-1].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_bas_gauche!=0){
                        if (visite[i+2][j-1]==1){
                                Rmax=Rmax+graphe[i+2][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i+2][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i+2][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+2][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i+2][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i+2][j-1].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_bas!=0){
                        if (visite[i+2][j]==1){
                                Rmax=Rmax+graphe[i+2][j].pixel1->R;
                                Gmax=Gmax+graphe[i+2][j].pixel1->G;
                                Bmax=Bmax+graphe[i+2][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+2][j].pixel2->R;
                                Gmax=Gmax+graphe[i+2][j].pixel2->G;
                                Bmax=Bmax+graphe[i+2][j].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_bas_droit!=0){
                        if (visite[i+2][j+1]==1){
                                Rmax=Rmax+graphe[i+2][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i+2][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i+2][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+2][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i+2][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i+2][j+1].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_droite!=0){
                        if (visite[i+1][j+1]==1){
                                Rmax=Rmax+graphe[i+1][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i+1][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i+1][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i+1][j+1].pixel2->B;
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i+1][j].aretes->arete_haut_droit!=0){
                        if (visite[i][j+1]==1){
                                Rmax=Rmax+graphe[i][j+1].pixel1->R;
                                Gmax=Gmax+graphe[i][j+1].pixel1->G;
                                Bmax=Bmax+graphe[i][j+1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j+1].pixel2->R;
                                Gmax=Gmax+graphe[i][j+1].pixel2->G;
                                Bmax=Bmax+graphe[i][j+1].pixel2->B;    
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_haut!=0){
                        if (visite[i][j]==1){
                                Rmax=Rmax+graphe[i][j].pixel1->R;
                                Gmax=Gmax+graphe[i][j].pixel1->G;
                                Bmax=Bmax+graphe[i][j].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j].pixel2->R;
                                Gmax=Gmax+graphe[i][j].pixel2->G;
                                Bmax=Bmax+graphe[i][j].pixel2->B;
                               
                        }
                        nb_pixels=nb_pixels+1;
                }
                if (graphe[i][j+1].aretes->arete_haut_gauche!=0){
                        if (visite[i][j-1]==1){
                                Rmax=Rmax+graphe[i][j-1].pixel1->R;
                                Gmax=Gmax+graphe[i][j-1].pixel1->G;
                                Bmax=Bmax+graphe[i][j-1].pixel1->B;
                        }
                        else{
                                Rmax=Rmax+graphe[i][j-1].pixel2->R;
                                Gmax=Gmax+graphe[i][j-1].pixel2->G;
                                Bmax=Bmax+graphe[i][j-1].pixel2->B;
                                
                        }
                        nb_pixels=nb_pixels+1;
                }

                int Rmoy=Rmax/nb_pixels; // on calcule les valeurs moyennes RGB de ces pixels
                int Gmoy=Gmax/nb_pixels;
                int Bmoy=Bmax/nb_pixels;

                if (graphe[i][j].aretes->arete_gauche!=0){
                        final[i][j-1]->R=Rmoy;
                        final[i][j-1]->G=Gmoy;
                        final[i][j-1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas_gauche!=0){
                        final[i+1][j-1]->R=Rmoy;
                        final[i+1][j-1]->G=Gmoy;
                        final[i+1][j-1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas!=0){
                        final[i+1][j]->R=Rmoy;
                        final[i+1][j]->G=Gmoy;
                        final[i+1][j]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_bas_droit!=0){
                        final[i+1][j+1]->R=Rmoy;
                        final[i+1][j+1]->G=Gmoy;
                        final[i+1][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_droite!=0){
                        final[i][j+1]->R=Rmoy;
                        final[i][j+1]->G=Gmoy;
                        final[i][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut_droit!=0){
                        final[i-1][j+1]->R=Rmoy;
                        final[i-1][j+1]->G=Gmoy;
                        final[i-1][j+1]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut!=0){
                        final[i-1][j]->R=Rmoy;
                        final[i-1][j]->G=Gmoy;
                        final[i-1][j]->B=Bmoy;
                }
                if (graphe[i][j].aretes->arete_haut_gauche!=0){
                        final[i-1][j-1]->R=Rmoy;
                        final[i-1][j-1]->G=Gmoy;
                        final[i-1][j-1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_gauche!=0){
                        final[i+1][j-1]->R=Rmoy;
                        final[i+1][j-1]->G=Gmoy;
                        final[i+1][j-1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_bas_gauche!=0){
                        final[i+2][j-1]->R=Rmoy;
                        final[i+2][j-1]->G=Gmoy;
                        final[i+2][j-1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_bas!=0){
                        final[i+2][j]->R=Rmoy;
                        final[i+2][j]->G=Gmoy;
                        final[i+2][j]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_bas_droit!=0){
                        final[i+2][j+1]->R=Rmoy;
                        final[i+2][j+1]->G=Gmoy;
                        final[i+2][j+1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_droite!=0){
                        final[i+1][j+1]->R=Rmoy;
                        final[i+1][j+1]->G=Gmoy;
                        final[i+1][j+1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_haut_droit!=0){
                        final[i][j+1]->R=Rmoy;
                        final[i][j+1]->G=Gmoy;
                        final[i][j+1]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_haut!=0){
                        final[i][j]->R=Rmoy;
                        final[i][j]->G=Gmoy;
                        final[i][j]->B=Bmoy;
                }
                if (graphe[i+1][j].aretes->arete_haut_gauche!=0){
                        final[i][j-1]->R=Rmoy;
                        final[i][j-1]->G=Gmoy;
                        final[i][j-1]->B=Bmoy;
                }
        }
}

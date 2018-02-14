#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "rdjpeg.h"
#include "svm.h"
#define RBINS 4
#define GBINS 4
#define BBINS 4

long* histogramme(CIMAGE *cim, int rBins, int gBins, int bBins){
	int c,i,j,hauteur,largeur;
	hauteur = cim->ny;
	largeur = cim->nx;
	int** r = malloc(sizeof(int*) * largeur);
	int** g = malloc(sizeof(int*) * largeur);
	int** b = malloc(sizeof(int*) * largeur);	
	for (i = 0; i < largeur; i++){
	    r[i] = malloc(sizeof(int) * hauteur);
   	    g[i] = malloc(sizeof(int) * hauteur);
   	    b[i] = malloc(sizeof(int) * hauteur);
	}
	long* k = malloc(sizeof(int) * rBins*gBins*bBins);
	
	printf("hauteur : %d largeur : %d\n",hauteur,largeur);
	//r[0][0] = (cim->r[0][0] * rBins)/256;
	for(j=0; j < hauteur; j++){
		for(i=0; i < largeur; i++){
			r[i][j] = (cim->r[i][j] * rBins)/256;
			g[i][j] = (cim->g[i][j] * gBins)/256;
			b[i][j] = (cim->b[i][j] * bBins)/256;
			int indiceK = r[i][j] + rBins*g[i][j] + rBins*gBins*b[i][j];
			k[indiceK] += 1;
		}
		printf("historgramme2\n");
	}
	return k;
} 

int main(int argc, char *argv[])
{
  int i,j,n,nx,ny,nb;
  CIMAGE cim;
  /*------------------------------------------------*/
  /* lecture d'une image requête                    */
  /*------------------------------------------------*/
  read_cimage(argv[1],&cim);
  /*------------------------------------------------*/
  /* affichage des valeurs pour le premier bloc 8x8 */
  /* comme exemple de traitement                    */
  /*------------------------------------------------*/
  printf("Largeur de l'image : %d\n",cim.nx);
  printf("Heuteur de l'image : %d\n",cim.ny);
  printf("Plan rouge du premier bloc 8x8 :\n");
  for (j = 0; j < 8; j++) {       /* ligne par ligne */
    printf("  ");
    for (i = 0; i < 8; i++) {   /* pixel par pixel */
      printf("%4d",cim.r[i][j]);
    }
    printf("\n");
  }
  printf("Plan vert du premier bloc 8x8 :\n");
  for (j = 0; j < 8; j++) {       /* ligne par ligne */
    printf("  ");
    for (i = 0; i < 8; i++) {   /* pixel par pixel */
      printf("%4d",cim.g[i][j]);
    }
    printf("\n");
  }
  printf("Plan bleu du premier bloc 8x8 :\n");
  for (j = 0; j < 8; j++) {       /* ligne par ligne */
    printf("  ");
    for (i = 0; i < 8; i++) {   /* pixel par pixel */
      printf("%4d",cim.b[i][j]);
    }
    printf("\n");
  }
  /*------------------------------------------------*/
  printf("historgramme\n");
  long* histo = histogramme(&cim, RBINS, GBINS, BBINS);

  for(int c = 0; c < RBINS*GBINS*BBINS; c++){
  	printf("%ld   ", histo[c]);
  }
  printf("\n");

  creation_svm_concept();

  exit(0);
}

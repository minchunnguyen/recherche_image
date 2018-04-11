#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

#define RBINS 4
#define GBINS 4
#define BBINS 4
#define TAILLE_URL 500

// ---------------------Fonction permet de calculer l'histogramme de couleur-------------------------
double*** histogramme_couleur(CIMAGE cim){
  // déclarer un histogramme de trois dimensions
  double*** histogramme = (double ***) malloc(RBINS*sizeof(double**));
  int i,j,k;
  int r,g,b;
  for (i=0;i<RBINS;i++){
    histogramme[i]=(double **)malloc(GBINS*sizeof(double*));
    for(j=0;j<GBINS;j++){
      histogramme[i][j] = (double *)malloc(BBINS*sizeof(double));
    }
  }
  
  for(i=0;i<RBINS;i++){
    for(j=0;j<GBINS;j++){
      for(k=0;k<BBINS;k++){
        histogramme[i][j][k]=0.0;
      }
    }
  }

  for(i=0;i<cim.nx;i++){
    for(j=0;j<cim.ny;j++){
      r=(cim.r[i][j]*RBINS)/256;
      g=(cim.g[i][j]*GBINS)/256;
      b=(cim.b[i][j]*BBINS)/256;
      histogramme[r][g][b]++;
    }
  }
  
  for(i=0;i<RBINS;i++){
    for(j=0;j<GBINS;j++){
      for(k=0;k<BBINS;k++){
        histogramme[i][j][k]=histogramme[i][j][k]/(cim.nx*cim.ny);
      }
    }
  }
  return histogramme;
}

// --------------------Fonction permet de créer les fichiers neutre SVM ------------------------
void fichiers_svm_neutre( char * type){
  int i,j,k;
  CIMAGE cim;
  FILE * entree = NULL;
  FILE *sortie  = NULL;

  if(strcmp(type, "train") == 0){
      entree = fopen("urls/urls_train","r");
      remove("resultat_train_a.svm");
      sortie = fopen("svm/resultat_train.svm","w");  
  }
  if(strcmp(type, "val") == 0){
      entree = fopen("urls/urls_val","r");
      remove("resultat_val_a.svm");
      sortie = fopen("svm/resultat_val.svm","w");  
  }
  if(entree !=NULL){
  char* url_img = malloc(TAILLE_URL*sizeof(char));
  int nb_img =0;
  while(fgets(url_img,TAILLE_URL,entree) != NULL){
    int ch =0;
    while(url_img[ch] != '\n' && ch < TAILLE_URL){
      ch++;
    }
    url_img[ch] = '\0';

    read_cimage(url_img,&cim);
    double*** histogramme = histogramme_couleur(cim);
    int count =1;
    fprintf(sortie,"0 "); //mettre le 0 tout au début
    for(i=0;i<RBINS;i++){
      for(j=0;j<GBINS;j++){
        for(k=0;k<BBINS;k++){
          if (histogramme[k][j][i]){
            fprintf(sortie,"%d:%f ",count,histogramme[k][j][i]);
          }
          count++;
        }
      }
    }
    fprintf(sortie,"\n");
    nb_img++;
    free_cimage(url_img,&cim);
  }

  fclose(entree);
  fclose(sortie);
}


}


int main(int argc, char *argv[])
{
  CIMAGE cim;
  fichiers_svm_neutre("train");
  fichiers_svm_neutre("val");

  exit(0);
}

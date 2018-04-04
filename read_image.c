#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

#define RBINS 4
#define GBINS 4
#define BBINS 4
#define TAILLE_MAX_URL 20000

double*** histogrammeRGB(CIMAGE cim){

  double*** histo = (double ***) malloc(RBINS*sizeof(double**));
  int i,j,k;
  for (i=0;i<RBINS;i++){
    histo[i]=(double **)malloc(GBINS*sizeof(double*));
    for(j=0;j<GBINS;j++){
      histo[i][j] = (double *)malloc(BBINS*sizeof(double));
    }
  }
  
  for(i=0;i<RBINS;i++){
    for(j=0;j<GBINS;j++){
      for(k=0;k<BBINS;k++){
        histo[i][j][k]=0.0;
      }
    }
  }

        
  int r,g,b;
  for(i=0;i<cim.nx;i++){
    for(j=0;j<cim.ny;j++){
      r=(cim.r[i][j]*RBINS)/256;
      g=(cim.g[i][j]*GBINS)/256;
      b=(cim.b[i][j]*BBINS)/256;
      histo[r][g][b]++;
    }
  }
  
  for(i=0;i<RBINS;i++){
    for(j=0;j<GBINS;j++){
      for(k=0;k<BBINS;k++){
        histo[i][j][k]=histo[i][j][k]/(cim.nx*cim.ny);
      }
    }
  }
  
  /*for(i=0;i<RBINS;i++){
    for(j=0;j<GBINS;j++){
      for(k=0;k<BBINS;k++){
        printf("%f ",histo[k][j][i]);
      }
      printf("\n");
    }
    printf("\n");
  }*/
  
  return histo;


}


void creation_fichier_neutre(FILE *f_entree, FILE *f_res){

int i,j,k;
CIMAGE cim;
if(f_entree !=NULL){
  char* url_img = malloc(TAILLE_MAX_URL*sizeof(char));
  int nb_img =0;
  while(fgets(url_img,TAILLE_MAX_URL,f_entree) != NULL){
    int ch =0;
    while(url_img[ch] != '\n' && ch < TAILLE_MAX_URL){
      ch++;
    }
    url_img[ch] = '\0';
    //printf("%s\n",url_img);

    read_cimage(url_img,&cim);
    double*** histo = histogrammeRGB(cim);
    int count =1;
    fprintf(f_res,"0 ");
    for(i=0;i<RBINS;i++){
      for(j=0;j<GBINS;j++){
        for(k=0;k<BBINS;k++){
          if (histo[k][j][i]){
            //printf("%d:%f ",count,histo[k][j][i]);
            fprintf(f_res,"%d:%f ",count,histo[k][j][i]);
          }
          count++;
        }
      }
    }
    fprintf(f_res,"\n");
    nb_img++;
    free_cimage(url_img,&cim);
  }
}


}



int main(int argc, char *argv[])
{
  int i,j,k,n,nx,ny,nb;
  CIMAGE cim;
  FILE* f_url_train = NULL;
  FILE* f_res_train = NULL;

  FILE* f_url_val = NULL;
  FILE* f_res_val = NULL;   
  
  // CREATION FICHIER SVM NEUTRE
  f_url_train = fopen("urls/urls_train","r");
  remove("resultat_train_a.svm");
  f_res_train = fopen("svm/resultat_train.svm","w");  

  f_url_val = fopen("urls/urls_val","r");
  remove("resultat_val_a.svm");
  f_res_val = fopen("svm/resultat_val.svm","w");  
  
  creation_fichier_neutre(f_url_train,f_res_train);
  creation_fichier_neutre(f_url_val,f_res_val);


  exit(0);
}

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>
#include "rdjpeg.h"
#include "svm.h"
#define TAILLE_MAX 1000
#define TAILLE_ANN 20


int main(int argc, char *argv[])
{
    creation_svm_concept(argv[1]);
    exit(0);
}

void creation_svm_concept(char * f1){
    char* histos[5*TAILLE_MAX];
    char* svm_concept[5*TAILLE_MAX];

    char chaine[TAILLE_MAX] = "";
    char chaine2[TAILLE_ANN] = "";

    FILE *svm;
    FILE *ann;
    FILE *resul;
    //ann = fopen("./annotation/aeroplane.ann","r");
    ann = fopen(f1,"r");

    svm = fopen("./svm/resultat_train.svm","r");

    //resul = fopen("./resul/color.svm","w");
    //svm = fopen(f2,"r");

    char nom_fichier_svm[100];
    nom_fichier_svm[0]='\0';

    int j = 2;

    while(f1[j] != '/'){
        j++;
    }
     j++;
    int k = 0;

    while(f1[j] != '.'){
        nom_fichier_svm[k] = f1[j];
        k++;
        j++;
    }

    nom_fichier_svm[k] = '\0';

    char chemin_fichier[50]; 
    chemin_fichier[0] = '\0';
    strcat(chemin_fichier, "./resul/color_");
    strcat(chemin_fichier,nom_fichier_svm);
    strcat(chemin_fichier,".svm");
    printf("chemin fichier %s\n",chemin_fichier );
    resul = fopen(chemin_fichier,"w");

    if (svm != NULL && ann != NULL && resul != NULL)
    {
        int i = 0;
        while( (fgets(chaine, TAILLE_MAX, svm) != NULL) &&  (fgets(chaine2, TAILLE_ANN, ann) != NULL)  ) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            histos[i] = chaine;
               // On affiche la chaîne qu'on vient de lire
              int c = 0;
                  while(chaine2[c] != ' '){
                      c++;
                  }
                    c++;
                 //   printf("%c\n", chaine2[c]);
                    if(chaine2[c] == ' '){
                            histos[i][0] = '1';

                    }else if(chaine2[c] == '-'){
                            histos[i][0]= '-';
                            histos[i][1]= '1';
                            char temp = ' ';
                            char temp2;
                            for (int j = 2; j < TAILLE_MAX-1; ++j)
                            {
                                temp2 = histos[i][j];
                                histos[i][j]=temp;
                                temp = temp2;
                            }
                    }
                   // printf("%s", histos[i]);
                    fputs(histos[i], resul); //écrire le résultat dans un fichier de sortie
                    //printf(" %d: ", i);
                         i++;
        }

        fclose(svm);
        fclose(ann);
        fclose(resul);
    }else{
        printf("erreur d'ouverture un des fichiers \n");
    }
    //$HOME/Documents/M2/recherche_image/libsvm-3.22/svm-predict -b 1 svm/resultat_val.svm model/color_aeroplane.model out/color_aeroplane.out

}








// #include <stdio.h>
// #include <malloc.h>
// #include <stdlib.h>
// #include <string.h>
// #include <strings.h>
// #include <dirent.h>
// #include "rdjpeg.h"
// #include "svm.h"
// #define TAILLE_MAX 1000
// #define TAILLE_ANN 20

// void creation_svm_concept(){
// 	char* histos[5*TAILLE_MAX];
//     char* svm_concept[5*TAILLE_MAX];

// 	char chaine[TAILLE_MAX] = "";
//     char chaine2[TAILLE_ANN] = "";

// 	int i = 0;
// 	FILE *svm;

// 	svm = fopen("./svm/resultat_train.svm","r");
// 	if (svm != NULL)
//     {
// 		while( (fgets(chaine, TAILLE_MAX, svm) != NULL) ) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
//         {
//            	histos[i] = chaine;
//           printf("%s", histos[i]); // On affiche la chaîne qu'on vient de lire
//         	i++;
//         }

//         fclose(svm);
//     }

//     printf("----------------------------------------------------------------------------------------------");
//     // for(int c= 0; c < 5*TAILLE_MAX; c++){
//     //     printf("%s\n", histos[c]);
//     // }
            
//     printf("----------------------------------------------------------------------------------------------\n");
//         FILE *ann;
//         ann = fopen("./annotation/aeroplane.ann","r");
//         i=0;

//             while (fgets(chaine2, TAILLE_ANN, ann) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
//             {
//                 //printf("%s", histos[i]);
//                 //printf("%s", chaine2); // On affiche la chaîne qu'on vient de lire
//                 int c = 0;
//                   while(chaine2[c] != ' '){
//                       c++;
//                   }

//                 //for(c ; chaine2[c]!=' ' && c < TAILLE_ANN ;c++){
//                     c++;
//                  //   printf("%c\n", chaine2[c]);
//                     if(chaine2[c] == ' '){
//                             histos[i][0] = '1';

//                     }else if(chaine2[c] == '-'){
//                             histos[i][0]= '-';
//                             histos[i][1]= '1';
//                             //char temp = ' ';
//                             char temp2;
//                             for (int j = 2; j < (TAILLE_MAX)-1; j++)
//                             {
//                                 temp2 = histos[i][j+1];
//                                 histos[i][j+1]= histos[i][j];
//                                 histos[i][j] = temp2;
//                             }
//                     }     
//                     //printf(" %d: ", i);
//                          i++;
                  

//             }
//             printf("FIN");
//             //}
//         fclose(ann);

// }

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

void creation_svm_concept(){
    char* histos[5*TAILLE_MAX];
    char* svm_concept[5*TAILLE_MAX];

    char chaine[TAILLE_MAX] = "";
    char chaine2[TAILLE_ANN] = "";

    int i = 0;
    FILE *svm;
    FILE *ann;
    FILE *resul;
    ann = fopen("./annotation/aeroplane.ann","r");

    svm = fopen("./svm/resultat_train.svm","r");

    resul = fopen("./resul/fichier_fusion","w");

    printf("----------------------------------------------------------------------------------------------");
    if (svm != NULL && ann != NULL && resul != NULL)
    {
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
                    printf("%s", histos[i]);
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
    printf("FIN");
    printf("----------------------------------------------------------------------------------------------\n");
    //$HOME/Documents/M2/recherche_image/libsvm-3.22/svm-predict -b 1 svm/resultat_val.svm model/color_aeroplane.model out/color_aeroplane.out

}








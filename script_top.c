#include <stdio.h>
// #include <malloc.h>
// #include <stdlib.h>
#include <string.h>
// #include <strings.h>
//#include <dirent.h>
//#include "rdjpeg.h"
//#include "svm.h"
#define TAILLE_MAX 100


int main(int argc, char *argv[]){

	// fichier top : <concept> Q0   <image>   0  <score>   R
	// 				 aeroplane  Q0 2008_000008 0 0.00393715 R
	// 				 nom_fichier   /annotation       /out
     printf("----------------------------------------------------------------------------------------------");

	char concept[] = "aeroplane";
	char chaine_out[TAILLE_MAX];
	char chaine_ann[TAILLE_MAX];
	//char *image_id[20];
	//char *score[20];
	//char *top[100]
	int i = 0;
    FILE *out;
    FILE *ann;
    FILE *top;
    ann = fopen("./annotation/aeroplane.ann","r");

    out = fopen("./out/color_aeroplane.out","r");

    top = fopen("./top/color_aeroplane.top","w");

    printf("----------------------------------------------------------------------------------------------");
    if (ann != NULL && out != NULL && top != NULL)
    {
    	char chaine_top[TAILLE_MAX];
        while( (fgets(chaine_out, TAILLE_MAX, out) != NULL) &&  (fgets(chaine_ann, TAILLE_MAX, ann) != NULL)  ) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
        	
        	strcat(chaine_top,concept);
            strcat(chaine_top," Q0 ");
            int c = 0;
	        while(chaine_ann[c] != ' '){
	         	 // BUG!!!
	            c++;
	        }
	        chaine_ann[c]='\0';
	        printf("    %s     ",chaine_ann);

	        strcat(chaine_top,chaine_ann);
	        strcat(chaine_top," 0 ");

	        c = 0;
           	while(chaine_out[c] != ' '){
            	c++;
          	}
          	c++;
          	while(chaine_out[c] != ' '){
          		strcat(chaine_top,chaine_out[c]);
            	c++;
          	}

          	strcat(chaine_top," R");
          	fputs(chaine_top, top);
        }

        fclose(out);
        fclose(ann);
        fclose(top);
    }else{
        printf("erreur d'ouverture un des fichiers \n");
    }
    exit(0);
}
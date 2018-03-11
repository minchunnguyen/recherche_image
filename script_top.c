#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 100
#define NB_IMAGE 7000


int main(int argc, char *argv[]){

	// fichier top : <concept> Q0   <image>   0  <score>   R
	// 				 aeroplane  Q0 2008_000008 0 0.00393715 R
	// 				 nom_fichier   /annotation       /out
     printf("----------------------------------------------------------------------------------------------");

	char *concept = "aeroplane";
	char chaine_out[TAILLE_MAX];
	char chaine_ann[TAILLE_MAX];
	//char *image_id[20];
	//char *score[20];
	//char *top[100]
    FILE *out;
    FILE *ann;
    FILE *top;
    ann = fopen("./annotation_val/aeroplane_val.ann","r");

    out = fopen("./out/color_aeroplane.out","r");

    top = fopen("./top/color_aeroplane.top","w+");


    if (ann != NULL && out != NULL && top != NULL)
    {
      fgets(chaine_out, TAILLE_MAX, out); //lit la preimiere ligne
    	char chaine_top[TAILLE_MAX];
      chaine_top[0]='\0';

      int i = 0;

      double* score_image;
      score_image=(double*)malloc(NB_IMAGE*sizeof(double));

      char** nom_image; 
    
      nom_image = (char**)malloc(NB_IMAGE*sizeof(char*));
      for(i=0;i<NB_IMAGE;i++){
        nom_image[i] = (char*)malloc(TAILLE_MAX*sizeof(char));
      }

      while( (fgets(chaine_out, TAILLE_MAX, out) != NULL) &&  (fgets(chaine_ann, TAILLE_MAX, ann) != NULL)  ) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
      {
      	
      	strcat(chaine_top,concept);
        strcat(chaine_top," Q0 ");
        int c = 0;
        while(chaine_ann[c] != ' '){
          c++;
        }
        chaine_ann[c]='\0';
        //printf("\n    %s     ",chaine_ann);

        strcat(chaine_top,chaine_ann);
        strcat(chaine_top," 0 ");

        c = 0;
       	while(chaine_out[c] != ' '){
        	c++;
      	}
      	c++;
        char str_out[TAILLE_MAX];
        str_out[0]='\0';
        int i = 0;
      	while(chaine_out[c] != ' '){
          str_out[i] = chaine_out[c];
        	c++;
          i++;
      	}
        str_out[i]='\0';
	      strcat(chaine_top,str_out);



      	strcat(chaine_top," R\n");
      	fputs(chaine_top, top);

        double score;

        sscanf(str_out, "%lf", &score);

        score_image[i] = score;
        nom_image[i] = chaine_top;

        chaine_top[0]='\0';
        chaine_ann[0]='\0';
        chaine_out[0]='\0';
        str_out[0]='\0';

        i++;

      }

      fclose(out);
      fclose(ann);
      fclose(top);
    }else{
        printf("erreur d'ouverture un des fichiers \n");
    }
        printf("FIN");

    return 0;
}


// trec_eval.9.0/trec_eval -q -m official rel_val/$concept.rel top/$concept.top > res_trec_eval/$concept.txt

// trec_eval.9.0/trec_eval -q -m official rel_val/aeroplane.rel top/aeroplane.top > res_trec_eval/aeroplane.txt

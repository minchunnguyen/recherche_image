#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 100
#define NB_IMAGE 7000

int main(int argc, char *argv[]){

	// fichier top : <concept> Q0   <image>   0  <score>   R
	// 				 aeroplane  Q0 2008_000008 0 0.00393715 R
	// 				 nom_fichier   /annotation       /out

    char concept[20] = "";
    concept[0]='\0';

    char chaine_out[TAILLE_MAX];
    char chaine_ann[TAILLE_MAX];

    FILE *out;
    FILE *ann;
    FILE *top;
  

    char nom_fichier[20];
    nom_fichier[0]='\0';

    int j = 2;

    while(argv[1][j] != '/'){
        j++;
    }
    j++;

    int k =0;
    while(argv[1][j] != '.'){
        nom_fichier[k] = argv[1][j];
        k++;
        j++;
    }
    nom_fichier[k] = '\0';
    //---------------------------------------Chemin du fichier .top--------------------------------------------------------
    char chemin_fichier_top[50]; 
    chemin_fichier_top[0] = '\0';
    strcat(chemin_fichier_top, "./top/");
    strcat(chemin_fichier_top,nom_fichier);
    strcat(chemin_fichier_top,".top");
    printf("chemin fichier top %s\n",chemin_fichier_top);

    //----------------------------------------Chemin du fichier .out---------------------------------------------------------
    char chemin_fichier_out[50]; 
    chemin_fichier_out[0] = '\0';
    strcat(chemin_fichier_out, "./out/color_");
    strcat(chemin_fichier_out,nom_fichier);
    strcat(chemin_fichier_out,".out");

    //----------------------------------------Ouverture des fichiers----------------------------------------------------------
    ann = fopen(argv[1],"r");

    out = fopen(chemin_fichier_out,"r");

    top = fopen(chemin_fichier_top,"w+");

    strcpy(concept, nom_fichier); // définir la valeur de concept 

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
    return 0;
}


// trec_eval.9.0/trec_eval -q -m official rel_val/$concept.rel top/$concept.top > res_trec_eval/$concept.txt

// trec_eval.9.0/trec_eval -q -m official rel_val/aeroplane.rel top/aeroplane.top > res_trec_eval/aeroplane.txt

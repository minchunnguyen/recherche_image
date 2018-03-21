#!/bin/bash



#$HOME/Documents/M2/recherche_image/libsvm-3.22/svm-predict -b 1 svm/resultat_val.svm model/color_aeroplane.model out/color_aeroplane.out


for fichier in `ls annotation_train/`
do
	./read_image ./annotation_train/$fichier
done




#for fichier in `ls resul/`
#do
#	echo $fichier | cut -d'.' -f1 > nomFichier
#	cat nomFichier
#	./libsvm-3.22/svm-train  -w+1 19 -b 1 -g 1.0 -h 0  ./resul/$fichier ./model/$(cat nomFichier).model
#done


for fichier in `ls model/`
do
	echo $fichier | cut -d'.' -f1 > nomFichier
	cat nomFichier
	./libsvm-3.22/svm-predict -b 1 ./svm/resultat_val.svm ./model/$fichier ./out/$(cat nomFichier).out
done


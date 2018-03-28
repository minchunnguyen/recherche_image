#!/bin/bash
echo '----------------Créer les fichiers.svm---------------------------'
cc  rdjpeg.c read_image.c svm.c -o read_image

for fichier in `ls annotation_train/`
do
	./read_image ./annotation_train/$fichier
done
echo '--------------------------------------------------------------------'
echo -e



echo '----------------Créer les fichiers.model---------------------------'
#for fichier in `ls resul/`
#do
#	echo $fichier | cut -d'.' -f1 > nomFichier
#	cat nomFichier
#	./libsvm-3.22/svm-train  -w+1 19 -b 1 -g 1.0 -h 0  ./resul/$fichier ./model/$(cat nomFichier).model
#done
echo '--------------------------------------------------------------------'
echo -e

echo '----------------Créer les fichiers.out------------------------------'

#for fichier in `ls model/`
#do
#	echo $fichier | cut -d'.' -f1 > nomFichier
#	cat nomFichier
#	./libsvm-3.22/svm-predict -b 1 ./svm/resultat_val.svm ./model/$fichier ./out/$(cat nomFichier).out
#done
echo '--------------------------------------------------------------------'
echo -e


echo '----------------Créer les fichiers.top------------------------------'
cc script_top.c -o script_top
for fichier in `ls annotation_val/`
do
	 ./script_top ./annotation_val/$fichier
done
echo '--------------------------------------------------------------------'
echo -e


echo '----------------Créer les résultat des fichiers.txt------------------------------'
for fichier in `ls top/`
do
	  concept=${fichier%.top}	
	  ./trec_eval.9.0/trec_eval -q -m official rel_val/$concept.rel top/$concept.top > res_trec_eval/$concept.txt
done
echo '--------------------------------------------------------------------'
echo -e



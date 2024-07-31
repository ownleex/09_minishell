#!/bin/bash

# Fichier brut généré par Valgrind
input_file="valgrind_suppressions_raw.txt"
# Fichier de suppression propre
output_file="valgrind_suppressions.txt"

# Initialiser le fichier de sortie
echo "" > $output_file

# Extraire les suppressions
awk '/^{/{flag=1} flag; /}$/{flag=0}' $input_file >> $output_file

echo "Les suppressions ont été extraites et enregistrées dans $output_file"

#!/bin/bash

# Fichier brut généré par Valgrind
input_file="valgrind_suppressions_raw.txt"
# Fichier de suppression propre
output_file="valgrind_suppressions.txt"

# Extraire les suppressions
awk '/^{/{flag=1} flag; /}$/{flag=0}' $input_file >> $output_file

# Supprimer le fichier brut
rm $input_file

# Message de confirmation
echo "Les suppressions ont été extraites et enregistrées dans $output_file, et $input_file a été supprimé."

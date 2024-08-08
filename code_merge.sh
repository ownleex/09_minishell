#!/bin/bash

# Dossier source contenant les fichiers .c
SRC_DIR="./src"
# Dossier contenant les fichiers .h
INCLUDE_DIR="./include"
# Fichier de sortie
OUTPUT_FILE="./code_master.c"

# Nettoyer le fichier de sortie s'il existe déjà
> "$OUTPUT_FILE"

# Fonction pour traiter un fichier et enlever l'entête 42
process_file() {
        local file="$1"
        local skip_header=true
        while IFS= read -r line; do
                # Si la ligne contient la fin de l'entête, désactiver le drapeau skip_header
                if [[ "$line" == *"*/"* ]]; then
                        skip_header=false
                        continue
                fi
                # Si nous sommes en dehors de l'entête, écrire la ligne dans le fichier de sortie
                if [ "$skip_header" = false ]; then
                        echo "$line" >> "$OUTPUT_FILE"
                fi
        done < "$file"
}

# Traiter les fichiers .h dans le dossier include et ajouter au début du fichier de sortie
for header in "$INCLUDE_DIR"/*.h; do
        process_file "$header"
done

# Ajouter une ligne vide pour séparer les headers du reste du code
echo "" >> "$OUTPUT_FILE"

# Parcourir tous les fichiers .c dans le dossier src et ses sous-dossiers
find "$SRC_DIR" -name "*.c" | while read -r file; do
        process_file "$file"
done

echo "Tous les fichiers .c et les headers .h ont été fusionnés dans $OUTPUT_FILE"

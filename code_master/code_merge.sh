#!/bin/bash

# Dossier source contenant les fichiers .c, en remontant d'un niveau
SRC_DIR="../src"
# Dossier contenant les fichiers .h, en remontant d'un niveau
INCLUDE_DIR="../include"
# Fichier de sortie dans le dossier actuel (code_master)
OUTPUT_FILE="./code_master.txt"
# Fichier Makefile, en remontant d'un niveau
MAKEFILE="../Makefile"

# Nettoyer le fichier de sortie s'il existe déjà
> "$OUTPUT_FILE"

# Fonction pour traiter un fichier et enlever les 11 premières lignes (entête 42)
process_file() {
    local file="$1"
    local line_number=0
    
    # Ajouter un commentaire avec le chemin relatif du fichier
    echo "// Contenu du fichier $file" >> "$OUTPUT_FILE"

    while IFS= read -r line; do
        # Ignorer les 11 premières lignes
        line_number=$((line_number + 1))
        if [ "$line_number" -le 11 ]; then
            continue
        fi
        # Écrire la ligne dans le fichier de sortie après la ligne 11
        echo "$line" >> "$OUTPUT_FILE"
    done < "$file"
}

# Traiter les fichiers .h dans le dossier include et ajouter au début du fichier de sortie
for header in "$INCLUDE_DIR"/*.h; do
    process_file "$header"
    echo "#endif" >> "$OUTPUT_FILE"
done

# Ajouter une ligne vide pour séparer les headers du reste du code
echo "" >> "$OUTPUT_FILE"

# Traiter main.c en priorité
if [ -f "$SRC_DIR/main.c" ]; then
    process_file "$SRC_DIR/main.c"
fi

# Parcourir tous les autres fichiers .c dans le dossier src et ses sous-dossiers, sauf main.c
find "$SRC_DIR" -name "*.c" ! -name "main.c" | while read -r file; do
    process_file "$file"
done

# Ajouter une ligne vide pour séparer le code du Makefile du reste du code
echo "" >> "$OUTPUT_FILE"

# Ajouter le contenu du Makefile à la fin du fichier de sortie en supprimant les 11 premières lignes
if [ -f "$MAKEFILE" ]; then
    process_file "$MAKEFILE"
else
    echo "Makefile non trouvé."
fi

echo "Le contenu des fichiers .h, des headers .c, et du Makefile ont été fusionnés dans $OUTPUT_FILE"

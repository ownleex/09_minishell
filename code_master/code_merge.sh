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
    echo "#endif" >> "$OUTPUT_FILE"
done

# Ajouter une ligne vide pour séparer les headers du reste du code
echo "" >> "$OUTPUT_FILE"

# Parcourir tous les fichiers .c dans le dossier src et ses sous-dossiers
find "$SRC_DIR" -name "*.c" | while read -r file; do
    process_file "$file"
done

# Ajouter une ligne vide pour séparer le code du Makefile du reste du code
echo "" >> "$OUTPUT_FILE"

# Ajouter le contenu du Makefile à la fin du fichier de sortie
if [ -f "$MAKEFILE" ]; then
    echo "# Contenu du Makefile" >> "$OUTPUT_FILE"
    cat "$MAKEFILE" >> "$OUTPUT_FILE"
else
    echo "Makefile non trouvé."
fi

echo "Le contenu des fichiers .c, des headers .h, et du Makefile ont été fusionnés dans $OUTPUT_FILE"

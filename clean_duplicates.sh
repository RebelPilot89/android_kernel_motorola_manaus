#!/bin/bash

REPORTE="reporte_limpieza.txt"
echo "--- REPORTE DE LIMPIEZA DE ARCHIVOS (2) ---" > $REPORTE
echo "Fecha: $(date)" >> $REPORTE
echo "-------------------------------------------" >> $REPORTE

echo "Iniciando barrido... El reporte se guardará en $REPORTE"

find . -type f -name "*(2)*" | while read -r file_ref; do
    dir=$(dirname "$file_ref")
    base=$(basename "$file_ref")
    
    if [[ "$base" == *"(2)."* ]]; then
        original_name="${base//(2)./.}"
    else
        original_name="${base//(2)/}"
    fi
    
    file_orig="$dir/$original_name"

    if [ -f "$file_orig" ]; then
        # -B ignora líneas en blanco, -b ignora espacios
        diff_output=$(diff -u -B -b "$file_orig" "$file_ref")
        
        if [ -z "$diff_output" ]; then
            echo "[IDÉNTICO] Eliminando $file_ref" | tee -a $REPORTE
            rm "$file_ref"
        else
            # Contar líneas de cambio real
            cambios=$(echo "$diff_output" | grep -E "^[+-]" | grep -vE "^\+\+\+|^\-\-\-" | wc -l)
            
            if [ "$cambios" -le 2 ]; then
                echo "[SIMILAR] Diferencia mínima en $original_name ($cambios líneas), eliminando $file_ref" | tee -a $REPORTE
                rm "$file_ref"
            else
                echo "[MANTENER] $original_name tiene $cambios cambios importantes." | tee -a $REPORTE
            fi
        fi
    else
        echo "[HUÉRFANO] No se encontró original para $file_ref. SE MANTIENE." | tee -a $REPORTE
    fi
done

echo "-------------------------------------------" >> $REPORTE
echo "Barrido completado."

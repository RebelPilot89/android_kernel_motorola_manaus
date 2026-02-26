#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"
cp mt6879.dts mt6879.dts.bak  # Backup
# Correcciones sugeridas (básicas y seguras):
sed -i 's/merge0 =&disp_merge0;/merge0 = &disp_merge0;/g' mt6879.dts || true
sed -i 's/GIC_SPI/0/g' mt6879.dts || true
sed -i 's/IRQ_TYPE_LEVEL_HIGH/4/g' mt6879.dts || true
# Intento de un join de tokens partidas comunes (por si acaso)
perl -0777 -pe "s/([A-Z0-9_]{3,})\s*\n\s*([A-Z0-9_]{3,})/\1\2/g" -i mt6879.dts || true
# Lanzar compilación (se guarda log relativo al repo root)
make O=out ARCH=arm64 LLVM=1 LLVM_IAS=1 dtbs -j1 V=1 2>&1 | tee ../../../../build_fix_dtb.log
make_rc=${PIPESTATUS[0]}
if [ "$make_rc" -ne 0 ]; then
    echo "Error en compilación (rc=$make_rc), revertiendo cambios"
    cp mt6879.dts.bak mt6879.dts
    exit $make_rc
fi
echo "Compilación DTB finalizada correctamente"

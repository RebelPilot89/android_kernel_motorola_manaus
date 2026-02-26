#!/usr/bin/env bash
set -euo pipefail

export PATH="/opt/neutron-clang/bin:/usr/local/bin:/usr/bin:/bin"

# 2. Variables de Arquitectura
export ARCH=arm64
export SUBARCH=arm64

# 3. Activación de LLVM puro (v23)
export LLVM=1
export LLVM_IAS=1

# 4. Definición de herramientas (Aseguramos que no use nada de GNU)
export CC=clang
export LD=ld.lld
export AR=llvm-ar
export NM=llvm-nm
export OBJCOPY=llvm-objcopy
export OBJDUMP=llvm-objdump
export STRIP=llvm-strip
export READELF=llvm-readelf
export OBJSIZE=llvm-size

# 5. Prefijos de Compilación Cruzada
# Añadimos CLANG_TRIPLE para que Clang sepa a qué target apuntar exactamente
export CLANG_TRIPLE=aarch64-linux-gnu-
export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE_COMPAT=arm-linux-gnueabi-

# Uso: make O=out M=drivers/misc modules
# - ejecutar el script SIN argumentos: hace un build completo usando out/.config
# - ejecutar con cualquier argumento: solo exporta las variables y sale (modo "export-only" para pruebas)

if [ "$#" -gt 0 ]; then
    echo "Export-only mode: environment variables exported for testing."
    printf "ARCH=%s\nSUBARCH=%s\nLLVM=%s\nLLVM_IAS=%s\nCROSS_COMPILE=%s\nCROSS_COMPILE_COMPAT=%s\nPATH=%s\n" \
        "$ARCH" "$SUBARCH" "$LLVM" "$LLVM_IAS" "$CROSS_COMPILE" "$CROSS_COMPILE_COMPAT" "$PATH"
    exit 0
fi

# Build mode: usa out/.config si existe, si no genera uno con defconfig
if [ -f out/.config ]; then
    echo "Found out/.config — building kernel in O=out..."
else
    echo "No out/.config found — creating a defconfig in out/"
    make O=out ARCH=arm64 manaus_defconfig
fi

echo "Starting full build (O=out)"
bear -- make prepare O=out ARCH=arm64 LLVM=1 LLVM_IAS=1 -j"$(nproc)" 
bear -- make O=out ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- -j"$(nproc)" 

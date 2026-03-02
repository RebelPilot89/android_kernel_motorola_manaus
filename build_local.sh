#!/usr/bin/env bash
set -euo pipefail

export PATH="/opt/neutron-clang/bin:/usr/local/bin:/usr/bin:/bin"

# Arquitectura
export ARCH=arm64
export SUBARCH=arm64

# Activación de LLVM puro (Neutron Clang 23)
export LLVM=1
export LLVM_IAS=1

# Herramientas target (cross-compilation)
export CC=clang
export LD=ld.lld
export AR=llvm-ar
export NM=llvm-nm
export OBJCOPY=llvm-objcopy
export OBJDUMP=llvm-objdump
export STRIP=llvm-strip
export READELF=llvm-readelf
export OBJSIZE=llvm-size

# Herramientas host (compilación de programas del sistema de build)
export HOSTCC=clang
export HOSTCXX=clang++
export HOSTAR=llvm-ar
export HOSTLD=ld.lld

# Prefijos de Compilación Cruzada
export CLANG_TRIPLE=aarch64-linux-gnu-
export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE_COMPAT=arm-linux-gnueabi-

# Parámetros comunes para todos los invocaciones de make
MAKE_FLAGS=(
    O=out
    ARCH=arm64
    LLVM=1
    LLVM_IAS=1
    CC=clang
    LD=ld.lld
    AR=llvm-ar
    NM=llvm-nm
    OBJCOPY=llvm-objcopy
    OBJDUMP=llvm-objdump
    STRIP=llvm-strip
    READELF=llvm-readelf
    OBJSIZE=llvm-size
    HOSTCC=clang
    HOSTCXX=clang++
    HOSTAR=llvm-ar
    HOSTLD=ld.lld
    CROSS_COMPILE=aarch64-linux-gnu-
    CROSS_COMPILE_COMPAT=arm-linux-gnueabi-
    CLANG_TRIPLE=aarch64-linux-gnu-
    -j"$(nproc)"
)

# Uso: make O=out M=drivers/misc modules
# - ejecutar el script SIN argumentos: hace un build completo usando out/.config
# - ejecutar con cualquier argumento: solo exporta las variables y sale (modo "export-only" para pruebas)

if [ "$#" -gt 0 ]; then
    echo "Export-only mode: environment variables exported for testing."
    printf "ARCH=%s\nSUBARCH=%s\nLLVM=%s\nLLVM_IAS=%s\nHOSTCC=%s\nHOSTCXX=%s\nHOSTAR=%s\nHOSTLD=%s\nCROSS_COMPILE=%s\nCROSS_COMPILE_COMPAT=%s\nPATH=%s\n" \
        "$ARCH" "$SUBARCH" "$LLVM" "$LLVM_IAS" "$HOSTCC" "$HOSTCXX" "$HOSTAR" "$HOSTLD" \
        "$CROSS_COMPILE" "$CROSS_COMPILE_COMPAT" "$PATH"
    exit 0
fi

# Build mode: usa out/.config si existe, si no genera uno con defconfig
if [ -f out/.config ]; then
    echo "Found out/.config — building kernel in O=out..."
else
    echo "No out/.config found — creating a defconfig in out/"
    make "${MAKE_FLAGS[@]}" manaus_defconfig
fi

echo "Starting full build (O=out)"
bear -- make "${MAKE_FLAGS[@]}" prepare
bear -- make "${MAKE_FLAGS[@]}"

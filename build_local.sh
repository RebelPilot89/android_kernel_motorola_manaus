#!/usr/bin/env bash
set -euo pipefail

# ccache setup (ajusta CCACHE_DIR a tu dir, e.g. ~/.ccache)
export CCACHE_DIR="${CCACHE_DIR:-$HOME/.ccache}"
export CCACHE_EXEC=/usr/bin/ccache  # ruta si no en PATH
export CCACHE_NOHASHDIR=true        # estabilidad en O=out
export CCACHE_COMPILERCHECK=content # hash por contenido (mejor para kernel)
export CCACHE_BASEDIR="$(pwd)"      # limita cache a este tree
export KBUILD_BUILD_TIMESTAMP=''    # determinístico para cache hits[web:101][web:92]

# Limpiar stats previas (opcional)
ccache -z 2>/dev/null || true

export PATH="/opt/neutron-clang/bin:/usr/local/bin:/usr/bin:/bin:$CCACHE_EXEC"

# Arquitectura
export ARCH=arm64
export SUBARCH=arm64

# LLVM + ccache
export LLVM=1
export LLVM_IAS=1
export CC="ccache clang"
export HOSTCC="ccache clang"
export HOSTCXX="ccache clang++"

# Resto tools (ccache solo en CC/HOSTCC)
export LD=ld.lld
export AR=llvm-ar
export NM=llvm-nm
export OBJCOPY=llvm-objcopy
export OBJDUMP=llvm-objdump
export STRIP=llvm-strip
export READELF=llvm-readelf
export OBJSIZE=llvm-size
export HOSTAR=llvm-ar
export HOSTLD=ld.lld

# Prefijos
export CLANG_TRIPLE=aarch64-linux-gnu-
export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE_COMPAT=arm-linux-gnueabi-

# MTK incremental
export SKIP_MRPROPER=1  # evita clean en build.sh[web:99]

# Flags make
MAKE_FLAGS=(
    O=out
    ARCH=arm64
    LLVM=1 LLVM_IAS=1
    CC="ccache clang"
    HOSTCC="ccache clang" HOSTCXX="ccache clang++"
    LD=ld.lld AR=llvm-ar NM=llvm-nm OBJCOPY=llvm-objcopy
    OBJDUMP=llvm-objdump STRIP=llvm-strip READELF=llvm-readelf
    OBJSIZE=llvm-size HOSTAR=llvm-ar HOSTLD=ld.lld
    KBUILD_LDFLAGS=--error-limit=0
    CROSS_COMPILE=aarch64-linux-gnu- CROSS_COMPILE_COMPAT=arm-linux-gnueabi-
    CLANG_TRIPLE=aarch64-linux-gnu-
    SKIP_MRPROPER=1
    -j"$(nproc)"
)

if [ "$#" -gt 0 ]; then
    echo "Export-only mode."
    printf "CC=%s HOSTCC=%s PATH=%s CCACHE_DIR=%s\n" "$CC" "$HOSTCC" "$PATH" "$CCACHE_DIR"
    exit 0
fi

if [ -f out/.config ]; then
    echo "Using out/.config..."
else
    echo "Generating defconfig..."
    make "${MAKE_FLAGS[@]}" manaus_defconfig
fi

echo "Build con ccache (stats: ccache -s)"
make "${MAKE_FLAGS[@]}" prepare
make "${MAKE_FLAGS[@]}"

echo "Build done. Cache stats:"
ccache -s


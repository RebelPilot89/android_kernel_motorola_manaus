#!/bin/bash

# Rutas a tus herramientas "superiores"
export PATH="/opt/neutron-clang/bin:/opt/binutils-2.45/bin:$PATH"

# Variables de la guía de Motorola
export ARCH=arm64
export SUBARCH=arm64
export LLVM=1
export LLVM_IAS=1

# Definir los prefijos para compilación cruzada (Cross-Compile)
export CROSS_COMPILE=aarch64-linux-gnu-
export CROSS_COMPILE_COMPAT=arm-linux-gnueabi-

echo "--- Entorno de compilación Manaus Kernel activado ---"
echo "Binutils: $(ld -v | head -n 1)"
echo "Clang: $(clang-22 --version | head -n 1)"

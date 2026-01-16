docker run --rm -it \

#!/bin/bash
# Script para compilar el kernel automáticamente en Docker usando toolchain y binutils locales
# Uso: ./build_kernel_docker.sh

set -e

# Variables de rutas locales
BASE_DIR="/home/rebelpilot89/manaus-kernel"
TOOLCHAIN_DIR="$BASE_DIR/toolchain/neutron-clang-19"
BINUTILS_DIR="$BASE_DIR/toolchain/binutils-2.37"
KERNEL_SRC="$BASE_DIR"

# Dockerfile temporal (solo dependencias del sistema, sin clang/lld/llvm del sistema)
cat > Dockerfile.kernelbuild <<'EOF'
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
  apt-get install -y --no-install-recommends \
  build-essential \
  bc \
  git \
  wget \
  curl \
  ca-certificates \
  python3 \
  python-is-python3 \
  bison \
  flex \
  libssl-dev \
  libelf-dev \
  rsync \
  file \
  xz-utils \
  cpio \
  libdebuginfod1 \
  gcc-aarch64-linux-gnu \
  libxml2 \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /kernel
EOF

# Construir imagen Docker
DOCKER_BUILDKIT=1 docker build -t kernelbuild:latest -f Dockerfile.kernelbuild .

# Ejecutar contenedor y compilar, redirigiendo toda la salida a build.log
docker run --rm -it \
  --name kernel-build-manaus \
  -v "$KERNEL_SRC":/kernel \
  -v "$TOOLCHAIN_DIR":/opt/clang \
  -v "$BINUTILS_DIR":/opt/binutils \
  kernelbuild:latest \
  bash -c '
    export PATH=/opt/clang/bin:/opt/binutils/bin:$PATH
    git config --global --add safe.directory /kernel/KernelSU-Next
    export ARCH=arm64
    export SUBARCH=arm64
    export CROSS_COMPILE=aarch64-linux-gnu-
    export CROSS_COMPILE_ARM32=arm-linux-gnueabi-
    export HOST_UID=$(id -u)
    export HOST_GID=$(id -g)
    echo "--- VERIFICANDO HERRAMIENTAS ---"
    clang --version
    aarch64-linux-gnu-ld --version
    make O=out manaus_defconfig
    ./scripts/config --file out/.config --enable CONFIG_CGROUP_DEVICE
    ./scripts/config --file out/.config --enable CONFIG_USER_NS
    ./scripts/config --file out/.config --enable CONFIG_OVERLAY_FS
    make O=out LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc)
    chown $HOST_UID:$HOST_GID /kernel/build.log 2>/dev/null || true
  ' | tee build.log

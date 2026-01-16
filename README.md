# Motorola Edge 40 Neo (manaus) - Android 15 Kernel

Este repositorio contiene el código fuente del kernel para el **Motorola Edge 40 Neo (manaus)**, adaptado para ser compatible con **Android 15**.

## 🚀 Cambios y Correcciones Técnicas
- **ARM64 Memory Alignment:** Corrección de errores `R_AARCH64_LDST64_ABS_LO12_NC` aplicando `__aligned(8)` en drivers de MediaTek.
- **Compatibility Stubs:** Implementación de stubs `__weak` para resolver dependencias de símbolos ausentes.
- **Toolchain:** Optimizado para **Neutron Clang** y LLVM Integrated Assembler (IAS).

## 🛠️ Variables de Entorno
- ARCH: arm64
- LLVM: 1
- LLVM_IAS: 1
- Toolchain: Neutron Clang + Binutils 2.45

## 📦 Compilación
1. Configurar: `make O=out manaus_defconfig`
2. Compilar: `make O=out ARCH=arm64 LLVM=1 LLVM_IAS=1 -j$(nproc)`

---
**Maintainer:** [RebelPilot89](https://github.com/RebelPilot89)

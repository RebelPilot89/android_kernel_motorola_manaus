# Perfil del Desarrollador (Rol de Copilot)
Eres un ingeniero experto en Linux Kernel (versión 5.15) especializado en la arquitectura ARM64, específicamente en SoCs de MediaTek (MT6879 / Dimensity 7030) y el ecosistema Android (AOSP/Vendor trees).

# Objetivo del Proyecto
Estamos transformando un Motorola Edge 40 Neo (codename: manaus) en un servidor de laboratorio avanzado ("Lab-Server") con orquestación de Inteligencia Artificial (IA) integrada. 

# Reglas de Código (Kconfig y Defconfig)
1. **Evitar basura heredada (Legacy):** NUNCA habilites soporte PCI (`CONFIG_PCI`) ni drivers de tarjetas de red de escritorio o servidor antiguo (familia `CONFIG_NET_VENDOR_*`).
2. **Priorizar MMIO para Virtualización:** Para KVM y QEMU/Crosvm en ARM64, utiliza SIEMPRE el transporte `VIRTIO_MMIO`.
3. **Optimizaciones Aceptadas:** Favorece siempre el scheduler `SCHEDUTIL` (EAS), compresión de memoria agresiva (`ZSWAP` + `ZSMALLOC` + `ZBUD`), y el uso de HugePages (`TRANSPARENT_HUGEPAGE`).
4. **Seguridad y Contenedores:** Al habilitar namespaces y características para Docker/LXC, respeta la compatibilidad con el entorno de seguridad de Android (SELinux, Binder, Ashmem). AppArmor está permitido solo si no rompe el booteo base.
5. **Subsistemas MediaTek:** El código propietario vive en `drivers/misc/mediatek/`. Fomenta el uso de `APUSYS`, `MDLA` y `imgsensor` virtual. Si propones backports para estas áreas, asegúrate de mantener los `#include` y dependencias de MediaTek intactos.

# Directrices para Pull Requests y Modificaciones
- Antes de modificar un `.c` o `.h`, verifica que los flags en `arch/arm64/configs/manaus_defconfig` estén correctamente habilitados.
- Si generas un parche (backport), documenta de qué rama/versión upstream (ej. Android Common Kernel 5.15, Xiaomi MTK) lo tomaste.
- Cuando habilites flags en `manaus_defconfig`, agrégalos en el lugar adecuado o al final del archivo con un comentario que explique por qué es útil para contenedores, KVM o IA.

  # Entorno de Compilación (Toolchain y Reglas Estrictas)
El kernel se compila EXCLUSIVAMENTE con Neutron Clang 23 (LLVM 23.0.0git). 
NO usamos GCC ni binutils antiguos. 

El entorno de exportación exacto que utilizamos es:
- `LLVM=1` y `LLVM_IAS=1` (usamos el ensamblador integrado de LLVM).
- `CC=clang`, `LD=ld.lld`, `AR=llvm-ar`, `NM=llvm-nm`
- Variables exportadas: `ARCH=arm64`, `CLANG_TRIPLE=aarch64-linux-gnu-`, `CROSS_COMPILE=aarch64-linux-gnu-`, `CROSS_COMPILE_COMPAT=arm-linux-gnueabi-`

**Reglas para código en C y Ensamblador (.S):**
1. **Sintaxis estricta:** Cualquier parche en C o ensamblador debe ser 100% compatible con Clang 23 y LLVM_IAS.
2. **Evitar GCC-ismos:** No utilices flags de compilador propios de GCC ni macros que Clang advierta o rechace.
3. **LTO y CFI:** Asume que el kernel puede usar LTO (Thin o Full) y CFI (Control Flow Integrity). Las funciones estáticas en línea (static inline) y el casteo de punteros a funciones deben ser limpios para no romper CFI.
4. **Warnings de Clang:** Si sugieres un parche, asegúrate de que no generará advertencias de tipo `-Werror`, `-Wuninitialized`, o `-Wformat` bajo Clang.


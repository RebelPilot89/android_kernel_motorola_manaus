# Inventario KVM donor vs canon (MT6879)

## Resumen rápido

- Archivos **distintos** entre `kvm-canon/` y `kvm-donor/`: **72**
- Archivos/rutas **solo en donor**: **78**
- Alcance principal de cambios: `hyp/`, `hyp/nvhe/`, `hyp/vhe/`, `vgic/`, `sys_regs`, `mmu`, `pmu`, `psci`.

## Hallazgos clave

1. El donor trae infraestructura amplia para **pKVM/nVHE** (`pkvm.c`, `hyp/include/nvhe/pkvm.h`, `modules.c`, `module.lds.S`, `mem_protect-donor.*`, etc.).
2. Hay trazas y observabilidad extra (`hyp_events.c`, `hyp_trace.c`, `trace.h` adicional en nvhe).
3. Existen archivos base sensibles con divergencias fuertes (`entry.S`, `hyp-entry.S`, `switch.c`, `mm.c`, `mem_protect.c`, `sys_regs.*`).
4. Integrar todo de golpe es de alto riesgo; se recomienda migración por lotes con validación completa por etapa.

## Priorización por riesgo

### Lote A (bajo riesgo, habilita observabilidad)

- `kvm-donor/hyp_trace.c`
- `kvm-donor/hyp_trace.h`
- `kvm-donor/hyp_events.c`
- Ajustes mínimos en `Kconfig`/`Makefile` para activar trazas opcionales.

### Lote B (riesgo medio, infraestructura aislable por Kconfig)

- `kvm-donor/android_erratum_pgtable.c`
- `kvm-donor/pkvm.c`
- `kvm-donor/vmid.c`
- Encapsular bajo nuevas opciones (`CONFIG_*`) desactivadas por defecto inicialmente.

### Lote C (riesgo alto, core nVHE/HYP)

- `kvm-donor/hyp/nvhe/*` (memoria, switch, setup, tlb, psci-relay)
- `kvm-donor/hyp/entry.S`, `hyp-entry.S`, `exception.c`, `pgtable.c`
- Requiere test de boot/hyp intensivo tras cada sublote.

### Lote D (riesgo alto, emulación/IRQ/interrupt controller)

- `kvm-donor/vgic/*`
- `kvm-donor/vgic-sys-reg-v3.c`
- Validar con guest ARM64 y tests de IRQ virtual.

## Matriz de validación por lote

1. Build: `make O=out ARCH=arm64 LLVM=1 LLVM_IAS=1 CROSS_COMPILE=aarch64-linux-gnu- -j$(nproc)`
2. Boot: arranque completo sin panic ni hard lock en init.
3. Hypervisor: inicialización KVM/hyp correcta en logs.
4. Funcional: smoke test de guest (cuando corresponda al lote).
5. Estrés: carga sostenida (CPU/IRQ/memoria) sin corrupción.

## Próximo paso recomendado

Iniciar con **Lote A** (trazas HYP) porque entrega visibilidad para depurar los lotes riesgosos posteriores sin cambiar aún la ruta crítica de ejecución del hypervisor.

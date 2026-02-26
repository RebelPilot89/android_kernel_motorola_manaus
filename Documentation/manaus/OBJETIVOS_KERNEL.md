# Objetivos del kernel Manaus (plan de ejecución)

Este documento convierte las metas del proyecto en un plan técnico ejecutable.

## Estado base real (punto de partida actual)

- El árbol **no está en cero**: ya existe integración funcional de GPU (`mali avalon r49p1`) y virtualización KVM.
- Existen rutas nVHE/pKVM en el código y en la configuración de build activa.
- El enfoque inmediato cambia de "integrar desde cero" a **afinar, estabilizar y medir**.

## Metas estratégicas

1. **Optimización total de rendimiento/latencia/consumo**.
2. **Terminal nativa robusta** en dispositivo (PTY, namespaces, cgroups, depuración y herramientas).
3. **Virtualización + hypervisor de nivel producción** (KVM + pKVM/nVHE según hardware).
4. **IA integrada profunda** con aceleradores (APU/NPU/GPU/CPU) y pipeline estable para inferencia local.

## Principios de integración

- Priorizar **estabilidad primero**: cada feature se integra detrás de Kconfig y se valida con build/boot/regresión.
- Integrar del donor por dominios, no en bloque: **KVM/hyp**, luego **scheduler/perf**, luego **AI stack**.
- Evitar duplicados de símbolos o stacks paralelos: un proveedor funcional por dominio.
- Todo cambio debe pasar por: compila -> bootea -> valida funcionalidad -> prueba de estrés.

## Fase 1: Baseline estable (obligatoria)

### Objetivo

Tener un baseline reproducible que compile y bootee siempre.

### Entregables

- Config base fijada sobre `manaus_defconfig`.
- Lista de subsistemas MTK conflictivos desactivados o corregidos.
- Build limpia documentada con comando único.

### Criterios de salida (Fase 1)

- `vmlinux` y `Image.gz` sin errores.
- Boot funcional en dispositivo objetivo.
- Sin regressions críticas en logs de arranque.

## Fase 2: Virtualización e Hypervisor (alta prioridad)

### Estado actual observado

- Existe árbol donor extenso en `kvm-donor/` con piezas pKVM/hyp adicionales.
- `kvm-canon/` y `kvm-donor/` tienen diferencias profundas (archivos y rutas nVHE/VHE).
- `manaus_defconfig` y la build activa usan `CONFIG_VIRTUALIZATION=y`, `CONFIG_KVM=y` y `CONFIG_KVM_ARM_PROTECTED_STATE=y`.

### Estrategia

1. Consolidar el modo protegido ya presente con pruebas repetibles de boot/guest.
2. Afinar observabilidad HYP (trazas/stacktrace/debug) detrás de Kconfig para diagnóstico controlado.
3. Integrar del donor solo lotes puntuales que mejoren robustez o rendimiento medible.

### Criterios de salida (Fase 2)

- KVM funcional (guest boot básico).
- Sin fallos en rutas HYP bajo carga.
- pKVM habilitable por config sin romper build estándar.

## Fase 3: Optimización de rendimiento

### Líneas de trabajo

- Scheduler tuning (latencia interactiva y throughput).
- DVFS/cpufreq y políticas térmicas coherentes.
- Reducción de overhead en paths críticos (MM, IRQ, IO, binder, storage).
- Trazas de rendimiento y perfiles reproducibles.

### Métricas objetivo

- Menor jank en UI/foreground.
- Mejor tiempo de respuesta en carga mixta.
- Mejor eficiencia energética sin thermal throttling agresivo.

## Fase 4: Terminal nativa

### Alcance mínimo

- PTY/TTY completos y estables.
- Namespaces/cgroups/seccomp funcionales para shells avanzadas.
- Herramientas de observabilidad habilitadas (tracefs, perf básico, logs útiles).

### Criterios de salida (Fase 4)

- Sesiones terminal prolongadas sin cuelgues ni pérdidas de I/O.
- Compatibilidad con workflows de desarrollo local en dispositivo.

## Fase 5: IA integrada profunda

### Alcance técnico

- Integración estable de APU/NPU + rutas GPU/CPU como fallback.
- Módulos y drivers de aceleración sin conflictos de enlace.
- Trazabilidad de inferencia (latencia, throughput, consumo).

### Criterios de salida (Fase 5)

- Pipeline de inferencia local estable.
- Latencia predecible y consumo controlado.
- Sin regresión en estabilidad general del sistema.

## Backlog inmediato (siguiente iteración)

1. Consolidar build limpia del baseline actual (resolver último error de enlace pendiente, si existe).
2. Ejecutar smoke tests de virtualización en modo protegido (arranque host, creación de VM, carga simple).
3. Medir overhead inicial de GPU/KVM para definir objetivos cuantitativos de tuning.
4. Aplicar primer lote de afinamiento de bajo riesgo (flags/debug/trace) y revalidar build + boot.

## Regla de operación

No importa cuánto tome: se prioriza progreso sostenido, verificable y sin deuda técnica oculta.

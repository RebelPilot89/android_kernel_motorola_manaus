# Copyright (C) 2015 MediaTek Inc.
# (Licencia omitida por brevedad...)

ifneq ($(CONFIG_MTK_GPU_VERSION),"")
  MTK_GPU_VERSION = $(subst ",,$(CONFIG_MTK_GPU_VERSION))
  $(info MTK_GPU_VERSION = $(MTK_GPU_VERSION))

  ifneq ($(CONFIG_MTK_PLATFORM),)
    export MTK_PLATFORM = $(subst ",,$(CONFIG_MTK_PLATFORM))
  else
    export MTK_PLATFORM = $(word 4,$(MTK_GPU_VERSION))
  endif

  # Soporte específico de plataforma
  ifeq ($(MTK_PLATFORM),mt6873)
    subdir-ccflags-y += -DCONFIG_GPU_MT6873
  else ifeq ($(MTK_PLATFORM),mt6893)
    subdir-ccflags-y += -DCONFIG_GPU_MT6893
  else ifeq ($(MTK_PLATFORM),mt6853)
    subdir-ccflags-y += -DCONFIG_GPU_MT6853
  endif
endif

# --- SECCIÓN CORREGIDA ---
# Forzamos GPUEB y GPU_BM si el soporte de GPU está activo
ifneq ($(CONFIG_MTK_GPU_SUPPORT),)
    obj-y += gpu_bm/
    obj-y += gpueb/
    obj-y += ged/
    obj-y += hal/
    obj-y += gpufreq/

    # Compilación del driver principal según versión o plataforma
    ifneq ($(CONFIG_MTK_GPU_VERSION),"")
        ifeq ($(CONFIG_MTK_GPU_R5P0),y)
            obj-y += $(subst ",,$(CONFIG_MTK_PLATFORM))/
        else ifneq ($(word 1,$(MTK_GPU_VERSION)),)
            obj-y += gpu_$(word 1,$(MTK_GPU_VERSION))/
        else
            obj-y += $(subst ",,$(CONFIG_MTK_PLATFORM))/
        endif
    endif
endif

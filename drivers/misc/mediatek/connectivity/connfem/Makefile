# drivers/misc/mediatek/connectivity/connfem/Makefile

obj-$(CONFIG_MTK_CONNFEM) += connfem.o

# Compilación de todos los componentes en un solo objeto consolidado
connfem-y := connfem_module.o \
             connfem_api.o \
             connfem_cfg.o \
             connfem_container.o \
             connfem_dt_parser.o \
             connfem_epaelna.o \
             connfem_internal.o \
             connfem_sku.o \
             connfem_subsys_common.o \
             connfem_subsys_wifi.o \
             connfem_subsys_bt.o

# Solo incluir el test si es necesario (opcional para producción)
connfem-$(CONFIG_MTK_CONNFEM_TEST) += connfem_test.o

# Rutas de headers
ccflags-y += -I$(srctree)/$(src)/include \
             -I$(srctree)/$(src)/../common/include

# Flags de optimización para el MT6879
ccflags-y += -DCONNFEM_PLATFORM_MT6879
ccflags-y += -DCONNFEM_TEST_ENABLED=0

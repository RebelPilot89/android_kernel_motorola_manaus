subdir-ccflags-y += -I$(srctree)/include/
subdir-ccflags-y += -I$(srctree)/kernel/

ifneq ($(filter y m,$(CONFIG_MTK_SLBC)),)
subdir-ccflags-y += -I$(srctree)/drivers/misc/mediatek/slbc/
endif

ccflags-y += -I$(src)

obj-$(CONFIG_MTK_CPUQOS_V3) += cpuqos_v3.o
cpuqos_v3-y += mpam_proto.o cpuqos_sys_common.o

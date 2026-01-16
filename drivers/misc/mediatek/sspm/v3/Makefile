obj-$(CONFIG_MTK_TINYSYS_SSPM_SUPPORT) += sspm_v3.o

sspm_v3-y += sspm_sysfs.o
sspm_v3-y += sspm_helper.o
sspm_v3-y += sspm_plt.o
sspm_v3-y += sspm_logger_impl.o
sspm_v3-y += sspm_timesync.o
sspm_v3-y += sspm_ipi_mbox.o

sspm_v3-$(CONFIG_OF_RESERVED_MEM) += sspm_reservedmem.o
sspm_v3-$(CONFIG_MTK_EMI) += sspm_emi_mpu.o

# --- ESTA ES LA PARTE QUE DEBES CORREGIR ---
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include/mt-plat/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/sspm/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/tinysys_scmi/
ccflags-y += -I$(srctree)/drivers/misc/mediatek/include
ccflags-y += -I$(srctree)/drivers/misc/mediatek/sspm/v3
# -------------------------------------------

#ccflags-y += -DDEBUG

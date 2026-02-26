# drivers/misc/mediatek/connectivity/gps/Makefile

obj-$(CONFIG_MTK_GPS) += mtk_gps_drv.o

GPS_DL_PLATFORM := v061
GPS_MCUDL_PLATFORM := v060

ccflags-y += -DMTK_GPS_MET20_SUPPORT -DCONFIG_MTK_GPS_V2
ccflags-y += -DGPS_DL_HAS_CONNINFRA_DRV=1
ccflags-y += -DGPS_DL_HAS_MCUDL=1
ccflags-y += -DGPS_DL_HAS_MCUDL_HAL=1
ccflags-y += -DGPS_DL_HAS_MCUDL_HW=1
ccflags-y += -DGPS_DL_HAS_MCUDL_FW=1

ccflags-y += -I$(srctree)/$(src)/data_link/plat/$(GPS_DL_PLATFORM)
ccflags-y += -I$(srctree)/$(src)/data_link/plat/$(GPS_DL_PLATFORM)/inc
ccflags-y += -I$(srctree)/$(src)/data_link/plat/$(GPS_DL_PLATFORM)/hw/inc
ccflags-y += -I$(srctree)/$(src)/data_link/inc
ccflags-y += -I$(srctree)/$(src)/data_link/linux/inc
ccflags-y += -I$(srctree)/$(src)/data_link/link/inc
ccflags-y += -I$(srctree)/$(src)/data_link/lib/inc
ccflags-y += -I$(srctree)/$(src)/data_link/hal/inc
ccflags-y += -I$(srctree)/$(src)/data_link/hw/inc

ccflags-y += -I$(srctree)/$(src)/gps_mcudl/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/linux/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/xlink/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/ylink/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/hal/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/hw/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/fw/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/data_intf/common/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/data_intf/host/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/gps_hif/common/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/gps_hif/host/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/mcu_sys/common/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/mcu_sys/host/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/plat/$(GPS_MCUDL_PLATFORM)/hw/inc
ccflags-y += -I$(srctree)/$(src)/gps_mcudl/plat/$(GPS_MCUDL_PLATFORM)/fw/inc

ccflags-y += -I$(srctree)/$(src)/../common/include
ccflags-y += -I$(srctree)/$(src)/../conninfra/include
ccflags-y += -I$(srctree)/$(src)/../conninfra/conn_drv/connv2/debug_utility
ccflags-y += -I$(srctree)/$(src)/../conninfra/conn_drv/connv2/debug_utility/include
ccflags-y += -I$(srctree)/$(src)/../conninfra/conn_drv/connv2/debug_utility/metlog
ccflags-y += -I$(srctree)/$(src)/../conninfra/conn_drv/connv2/debug_utility/coredump
ccflags-y += -I$(srctree)/$(src)/../conninfra/conn_drv/connv2/debug_utility/connsyslog
ccflags-y += -I$(srctree)/drivers/misc/mediatek/dvfsrc

mtk_gps_drv-y += data_link/gps_dl_module.o
mtk_gps_drv-y += data_link/gps_dl_context.o
mtk_gps_drv-y += data_link/gps_each_link.o

mtk_gps_drv-y += data_link/lib/gps_dl_dma_buf.o
mtk_gps_drv-y += data_link/lib/gps_dl_lib_misc.o
mtk_gps_drv-y += data_link/lib/gps_dl_hist_rec.o
mtk_gps_drv-y += data_link/lib/gps_dl_hist_rec2.o
mtk_gps_drv-y += data_link/lib/gps_dl_time_tick.o
mtk_gps_drv-y += data_link/lib/gps_dl_name_list.o

mtk_gps_drv-y += data_link/hw/gps_dl_hw_conn_infra.o
mtk_gps_drv-y += data_link/hw/gps_dl_hw_semaphore.o
mtk_gps_drv-y += data_link/hw/gps_dl_hw_bgf.o
mtk_gps_drv-y += data_link/hw/gps_dl_hw_gps.o
mtk_gps_drv-y += data_link/hw/gps_dl_hw_power_ctrl.o
mtk_gps_drv-y += data_link/hw/gps_dl_hw_usrt_apb.o
mtk_gps_drv-y += data_link/hw/gps_dl_hw_util.o

mtk_gps_drv-y += data_link/hal/gps_dl_hal.o
mtk_gps_drv-y += data_link/hal/gps_dl_hal_util.o
mtk_gps_drv-y += data_link/hal/gps_dsp_fsm.o
mtk_gps_drv-y += data_link/hal/gps_dl_power_ctrl.o
mtk_gps_drv-y += data_link/hal/gps_dl_isr.o
mtk_gps_drv-y += data_link/hal/gps_dl_dma.o
mtk_gps_drv-y += data_link/hal/gps_dl_mcub.o
mtk_gps_drv-y += data_link/hal/gps_dl_zbus.o
mtk_gps_drv-y += data_link/hal/gps_dl_conn_infra.o
mtk_gps_drv-y += data_link/hal/gps_dl_hal_met2_0.o

mtk_gps_drv-y += data_link/link/gps_dl_link_event_proc.o
mtk_gps_drv-y += data_link/link/gps_dl_link_hal_ctrl.o
mtk_gps_drv-y += data_link/link/gps_dl_link_irq_ctrl.o
mtk_gps_drv-y += data_link/link/gps_dl_link_state.o
mtk_gps_drv-y += data_link/link/gps_dl_link_sync.o
mtk_gps_drv-y += data_link/link/gps_dl_link_util.o
mtk_gps_drv-y += data_link/link/gps_dl_subsys_reset.o

mtk_gps_drv-y += data_link/linux/gps_data_link_devices.o
mtk_gps_drv-y += data_link/linux/gps_each_device.o
mtk_gps_drv-y += data_link/linux/gps_dl_linux.o
mtk_gps_drv-y += data_link/linux/gps_dl_linux_plat_drv.o
mtk_gps_drv-y += data_link/linux/gps_dl_linux_reserved_mem.o
mtk_gps_drv-y += data_link/linux/gps_dl_linux_reserved_mem_v2.o
mtk_gps_drv-y += data_link/linux/gps_dl_emi.o
mtk_gps_drv-y += data_link/linux/gps_dl_ctrld.o
mtk_gps_drv-y += data_link/linux/gps_dl_procfs.o
mtk_gps_drv-y += data_link/linux/gps_dl_osal.o

mtk_gps_drv-y += data_link/plat/$(GPS_DL_PLATFORM)/gps_dl_hw_dep_bgf.o
mtk_gps_drv-y += data_link/plat/$(GPS_DL_PLATFORM)/gps_dl_hw_dep_gps.o
mtk_gps_drv-y += data_link/plat/$(GPS_DL_PLATFORM)/gps_dl_hw_dep_debug.o
mtk_gps_drv-y += data_link/plat/$(GPS_DL_PLATFORM)/gps_dl_hw_dep_dma.o
mtk_gps_drv-y += data_link/plat/$(GPS_DL_PLATFORM)/gps_dl_hw_dep_met2_0.o

ifeq ($(CONFIG_MTK_GPS_XLINK),y)
mtk_gps_drv-y += gps_mcudl/gps_mcudl_context.o
mtk_gps_drv-y += gps_mcudl/gps_mcudl_name_list.o

mtk_gps_drv-y += gps_mcudl/data_intf/common/gps_mcudl_data_pkt_parser.o
mtk_gps_drv-y += gps_mcudl/data_intf/common/gps_mcudl_data_pkt_rbuf.o
mtk_gps_drv-y += gps_mcudl/data_intf/common/gps_mcudl_data_pkt_slot.o
mtk_gps_drv-y += gps_mcudl/data_intf/host/gps_mcudl_data_pkt_host_impl.o

mtk_gps_drv-y += gps_mcudl/fw/gps_mcudl_fw_code.o

mtk_gps_drv-y += gps_mcudl/gps_hif/common/gps_mcu_hif_common.o
mtk_gps_drv-y += gps_mcudl/gps_hif/common/gps_mcu_hif_core.o
mtk_gps_drv-y += gps_mcudl/gps_hif/host/gps_mcu_hif_host.o
mtk_gps_drv-y += gps_mcudl/gps_hif/host/gps_mcu_hif_mgmt_cmd_send.o

mtk_gps_drv-y += gps_mcudl/hal/gps_mcudl_hal_ccif.o
mtk_gps_drv-y += gps_mcudl/hal/gps_mcudl_hal_conn.o
mtk_gps_drv-y += gps_mcudl/hal/gps_mcudl_hal_mcu.o
mtk_gps_drv-y += gps_mcudl/hal/gps_mcudl_hal_user_fw_own_ctrl.o

mtk_gps_drv-y += gps_mcudl/hw/gps_mcudl_hw_ccif.o
mtk_gps_drv-y += gps_mcudl/hw/gps_mcudl_hw_mcu.o

mtk_gps_drv-y += gps_mcudl/linux/gps_mcudl_devices.o
mtk_gps_drv-y += gps_mcudl/linux/gps_mcudl_each_device.o
mtk_gps_drv-y += gps_mcudl/linux/gps_mcudl_linux_fw_loading.o
mtk_gps_drv-y += gps_mcudl/linux/gps_mcudl_linux_xlink_buf.o
mtk_gps_drv-y += gps_mcudl/linux/gps_nv_each_device.o

mtk_gps_drv-y += gps_mcudl/mcu_sys/common/gps_mcusys_nv_common_impl.o
mtk_gps_drv-y += gps_mcudl/mcu_sys/host/gps_mcusys_data_dispatcher_host.o
mtk_gps_drv-y += gps_mcudl/mcu_sys/host/gps_mcusys_data_sync2target.o
mtk_gps_drv-y += gps_mcudl/mcu_sys/host/gps_mcusys_fsm_host.o
mtk_gps_drv-y += gps_mcudl/mcu_sys/host/gps_mcusys_nv_data_host.o
mtk_gps_drv-y += gps_mcudl/mcu_sys/host/gps_mcusys_nv_lock_host.o

mtk_gps_drv-y += gps_mcudl/plat/gps_mcudl_plat_dedicated_mcu.o

mtk_gps_drv-y += gps_mcudl/xlink/gps_mcudl_each_link.o
mtk_gps_drv-y += gps_mcudl/xlink/gps_mcudl_link_state.o
mtk_gps_drv-y += gps_mcudl/xlink/gps_mcudl_link_sync.o
mtk_gps_drv-y += gps_mcudl/xlink/gps_mcudl_link_util.o
mtk_gps_drv-y += gps_mcudl/xlink/gps_mcudl_reset.o
mtk_gps_drv-y += gps_mcudl/xlink/gps_mcudl_xlink_event_proc.o
mtk_gps_drv-y += gps_mcudl/xlink/gps_mcudl_xlink.o

mtk_gps_drv-y += gps_mcudl/ylink/gps_mcudl_ylink_event_proc.o
endif

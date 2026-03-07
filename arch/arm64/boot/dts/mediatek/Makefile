# SPDX-License-Identifier: GPL-2.0
# -@ enables phandle symbol generation required for DT overlay / DTBO support.
DTC_FLAGS += -@

# SoC Base DTB (standalone, loaded from the "dtb" partition)
dtb-$(CONFIG_ARCH_MEDIATEK) += mt6879.dtb

# Motorola Edge 40 Neo (manaus) DTBO overlay entries.
# Each file must have a unique mot,board-id so the bootloader can select the
# correct entry for the installed hardware variant.  Overlays without a board-id
# are omitted here because the Moto bootloader requires board-id matching and
# a "catch-all" entry without one can trigger incorrect DT merges and bricks.
#
# Board-id to entry mapping (matches stock DTBO):
#   0x44b / 0xa100  -> docomo-evt1  (MANAUS_DOCOMO_RADIO << 8 | 0x4B)
#   0x47  / 0xa100  -> evb
#   0x47  / 0xb100  -> dvt1
#   0x48  / 0xb1a0  -> dvt1a
#   0x47,0x48 / 0xb200 -> dvt2
dtb-$(CONFIG_ARCH_MEDIATEK) += mt6879-manaus-docomo-evt1-overlay.dtb
dtb-$(CONFIG_ARCH_MEDIATEK) += mt6879-manaus-evb-overlay.dtb
dtb-$(CONFIG_ARCH_MEDIATEK) += mt6879-manaus-dvt1-overlay.dtb
dtb-$(CONFIG_ARCH_MEDIATEK) += mt6879-manaus-dvt1a-overlay.dtb
dtb-$(CONFIG_ARCH_MEDIATEK) += mt6879-manaus-dvt2-overlay.dtb

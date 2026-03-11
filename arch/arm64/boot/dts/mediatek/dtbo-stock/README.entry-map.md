# manaus stock DTBO entry map

Source image: `Analisis/Firmware-stock/dtbo.img`
Table parser: `mkdtimg dump`
Entry blobs: `manaus_stock_entry.dtbo.{0..4}`
Decompiled DTS: `manaus_stock_entry.dtbo.{0..4}.dts`

## Selection model

`mkdtimg dump` shows IDs `0..4` and `custom[] = 0` for all entries.
On this platform, runtime selection is constrained in the overlay by `mot,board-id`.

## Entry mapping

- `entry 0` (`id = 0`)
  - `mot,board-id = <0x44b 0xa100>`
  - Uses single charger node `bq25960-standalone@65`.
  - Reference: `arch/arm64/boot/dts/mediatek/dtbo-stock/manaus_stock_entry.dtbo.0.dts`

- `entry 1` (`id = 1`)
  - `mot,board-id = <0x47 0xa100>`
  - Uses dual charger nodes `bq25960-master@66` + `bq25960-slave@67`.
  - Contains `platform_state = "evt"`.
  - Reference: `arch/arm64/boot/dts/mediatek/dtbo-stock/manaus_stock_entry.dtbo.1.dts`

- `entry 2` (`id = 2`)
  - `mot,board-id = <0x47 0xb100>`
  - Dual charger (`master/slave`).
  - Reference: `arch/arm64/boot/dts/mediatek/dtbo-stock/manaus_stock_entry.dtbo.2.dts`

- `entry 3` (`id = 3`)
  - `mot,board-id = <0x48 0xb1a0>`
  - Dual charger (`master/slave`).
  - Reference: `arch/arm64/boot/dts/mediatek/dtbo-stock/manaus_stock_entry.dtbo.3.dts`

- `entry 4` (`id = 4`)
  - `mot,board-id = <0x47 0xb200 0x48 0xb200>`
  - Dual charger (`master/slave`).
  - Multi-board match in a single overlay (0x47 and 0x48 on `0xb200`).
  - Reference: `arch/arm64/boot/dts/mediatek/dtbo-stock/manaus_stock_entry.dtbo.4.dts`

## Panel/touch notes common to entries

All entries include panel candidates and touch gating via `mmi,panel_name`:

- Panels: `tianma,vtdr6115,vdo,144hz`, `csot,vtdr6115,vdo,144hz,c7`, `tianma,vtdr6115,vdo,144hz,u8`, `boe,nt37701a,cmd,144hz`
- Touch candidates: `goodix,gt9916S` and `focaltech,fts`

This means panel vendor alone does not pick DTBO table entry; board-id is the primary discriminator.

## Practical conclusion for this tree

Most likely active stock overlay for current retail devices is `entry 4` (id 4), because it targets newer board IDs `0x47/0x48` with revision `0xb200`.

To confirm 100 percent on-device, read live `mot,board-id` from devicetree and match against the list above.

## Live runtime confirmation (this device)

ADB runtime properties confirm the active overlay index is `4`:

- `ro.boot.dtbo_idx = 4`
- `ro.boot.slot_suffix = _a`

Therefore, for this specific unit the active stock DTBO entry is `entry 4`.

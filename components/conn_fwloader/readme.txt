1. FW image names:
	Production FW, for users:
		rw61x_sb_wifi_a1.bin, for CPU1_wifi of redfinch a1 board
		rw61x_sb_ble_a1.bin, for CPU2_ble of redfinch a1 board
		rw61x_sb_ble_15d4_combo_a1.bin, for CPU2_ble_15.4_combo of redfinch a1 board

		rw61x_sb_wifi_a2.bin, for CPU1_wifi of redfinch a2 board
		rw61x_sb_ble_a2.bin, for CPU2_ble of redfinch a2 board
		rw61x_sb_ble_15d4_combo_a2.bin, for CPU2_ble_15.4_combo of redfinch a2 board
	Production mfg_FW, for users:
		rw61xw_sb_mfg_fw_cpu1_a1.bin for mfg_fw_cpu1_wifi of redfinch a1 board
		rw61xn_sb_mfg_fw_cpu2_ble_a1.bin for mfg_fw_cpu2_ble of redfinch a1 board
		rw61xn_sb_mfg_fw_cpu2_combo_a1.bin, for mfg_fw_cpu2_15.4 of redfinch a1 board

		rw61xw_sb_mfg_fw_cpu1_a2.bin for mfg_fw_cpu1_wifi of redfinch a2 board
		rw61xn_sb_mfg_fw_cpu2_ble_a2.bin for mfg_fw_cpu2_ble of redfinch a2 board
		rw61xn_sb_mfg_fw_cpu2_combo_a2.bin, for mfg_fw_cpu2_15.4 of redfinch a2 board

2. where to get FW image(Production and mfg_FW):
	In the directory:  /components/conn_fwloader/fw_bin

3. How to load FW(Production and mfg_FW):
	Need to write the FW image to flash first, then the loadservice will download FW when power on.
	For example, the CMD to write CPU1 image to flash in J-link window:
		loadbin C:\xxx\rw61x_sb_wifi_xx.bin,0x08400000

	The CMD to write CPU2_ble image to flash in J-link window:
		loadbin C:\xxx\rw61x_sb_ble_xx.bin,0x08540000

	The CMD to write CPU2_15.4 image to flash in J-link window:
		loadbin C:\xxx\rw61x_sb_ble_15d4_combo_xx.bin,0x085e0000

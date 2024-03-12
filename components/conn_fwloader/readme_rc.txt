1. FW image names:
	Raw FW, for users:
		rw610w_raw_cpu1_v0.bin, for CPU1_wifi of redfinch A0 board
		rw610n_raw_cpu2_ble_v0.bin, for CPU2_ble of redfinch A0 board
		rw610n_combo_raw_cpu2_ble_15_4_combo_v0.bin, for CPU2_ble_15.4_combo of redfinch A0 board

		rw610w_raw_cpu1_v1.bin, for CPU1_wifi of redfinch A1 board
		rw610n_raw_cpu2_ble_v1.bin, for CPU2_ble of redfinch A1 board
		rw610n_combo_raw_cpu2_ble_15_4_combo_v1.bin, for CPU2_ble_15.4_combo of redfinch A1 board

		rw610w_raw_cpu1_v2.bin, for CPU1_wifi of redfinch A2 board
		rw610n_raw_cpu2_ble_v2.bin, for CPU2_ble of redfinch A2 board
		rw610n_combo_raw_cpu2_ble_15_4_combo_v2.bin, for CPU2_ble_15.4_combo of redfinch A2 board
	Production mfg_FW, for users:
		rw610w_mfg_fw_cpu1.bin for mfg_fw_cpu1_wifi
		rw610n_mfg_fw_cpu2.bin for mfg_fw_cpu2_ble
		nbu_15_4_mfg.bin, for mfg_fw_cpu2_15.4

2. where to get FW image:
	In the directory:  /components/conn_fwloader/fw_bin

3. How to load FW:
	Need to write the FW image to flash first, then the loadservice will download FW when power on.
	For example, the CMD to write CPU1 image to flash in J-link window:
		loadbin C:\xxx\rw610w_raw_cpu1_xx.bin,0x08400000

	The CMD to write CPU2_ble image to flash in J-link window:
		loadbin C:\xxx\rw610n_raw_cpu2_ble_xx.bin,0x08540000

	The CMD to write CPU2_15.4 image to flash in J-link window:
		loadbin C:\xxx\rw610n_combo_raw_cpu2_ble_15_4_combo_xx.bin,0x085e0000
		

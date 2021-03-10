@ingroup tfa9xxx

The **tfa9xxx** driver supported the following TFA amplifiers: TFA9894N1, TFA9894N2 and TFA9892N1.

### Typical use cases:

1. Initialize TFA:

	Create a `tfa9xxx_config_t`, and set up all the necessary fields.

		#include "tfa_config_tfa9894N2.h"
		tfa9xxx_config_t tfa9xxxConfig = {
			.i2cConfig         = {.codecI2CInstance = BOARD_CODEC_I2C_INSTANCE, .codecI2CSourceClock = 19000000U},
			.slaveAddress      = TFA9XXX_I2C_ADDR_0,
			.protocol          = kTFA9XXX_BusI2S,
			.format            = {.sampleRate = kTFA9XXX_AudioSampleRate48KHz, .bitWidth = kTFA9XXX_AudioBitWidth16bit},
			.tfaContainer      = tfa_container_bin,
			.deviceIndex       = 0,
		};
		codec_config_t boardCodecConfig = {.codecDevType = kCODEC_TFA9XXX, .codecDevConfig = &tfa9xxxConfig};

	- If you use multiple TFAs, each TFA requires a `tfa9xxx_config_t`.

	- The `.tfaContainer` should point to an hex array, here defined in `tfa_config_tfa9894N2.h`. This header file included in the driver is for default usage. A customized tuning can be achieved using QuickStudio or TFAConfigurator, generating customized configuration header file.

	- The `.deviceIndex` should be 0 for a single TFA. For multiple TFAs use case, the `.deviceIndex` should be from 0 to (`TFA9XXX_DEV_NUM - 1`) for each `tfa9xxx_config_t`.

	- The slave address of TFA is defined by the voltage level on pin ADS2 and ADS1. Therefore 4 possible slave addresses are: 0x34, 0x35, 0x36 and 0x37.

	Call `CODEC_Init(codecHandle, &boardCodecConfig)` to initialize the TFA.

		void BOARD_Codec_Init()
		{
			status_t rc;
			rc = CODEC_Init(&codecHandle, &boardCodecConfig);
			if(rc != kStatus_Success)
				usb_echo("Codec init failed!\n");
		}

	- If you use multiple TFAs, you need to call `CODEC_Init()` for each TFA, every call with its own handle and config.

	- `CODEC_Init()` eventually calls `TFA9XXX_Init()`, this is the actual function for TFA initialization.

2. Set Volume:

	Call `CODEC_SetVolume()` with volume between 0 ~ 100, which eventually passes volume to `TFA9XXX_SetVolume()`.

		CODEC_SetVolume(&codecHandle, kCODEC_SupportPlayChannelLeft0 | kCODEC_SupportPlayChannelRight0, volume);

	For tuning using QuickStudio, it is suggested to set the volume to be 100 (maximum) before tuning started. Otherwise, changes during tuning might be too subtle to be heard.


3. Mute/unmute

	Call `CODEC_SetMute()` to mute or unmute the TFA, which eventually calls `TFA9XXX_SetMute()`.

		void BOARD_SetCodecMuteUnmute(bool mute)
		{
			status_t rc;
			rc = CODEC_SetMute(&codecHandle, kCODEC_PlayChannelLeft0 | kCODEC_PlayChannelRight0, mute);
			if(rc != kStatus_Success)
				usb_echo("Codec set mute/unmute failed!\n");
		}

	- The `TFA9XXX_Init()` function calls `TFA9XXX_SetMute()` at the end to unmute the TFA. This is fine for single TFA usage. If multiple TFAs are used, you might want to unmute all of them at once instead of unmuting TFA one by one as `TFA9XXX_Init()` is called respectively. In this case, you need to comment out the `TFA9XXX_SetMute()` part in `TFA9XXX_Init()` function, and do the unmute after all the `CODEC_Init()` calls.

## Special functions

	status_t TFA9XXX_SetPlayChannel(tfa9xxx_handle_t *handle, enum _codec_play_channel playChannel);

- By default, I2S channel is configured by the `.tfaContainer` in `tfa9xxx_config_t`. So you don't need to call this function. However, if required, calling this function allows overwriting I2S channel selection. This can be useful when the tuning is done, and you simply want to change the I2S channel.

- A typical stereo setup is to play left channel for left speaker and right channel for right speaker. A typical mono setup is play both channel for a single speaker.


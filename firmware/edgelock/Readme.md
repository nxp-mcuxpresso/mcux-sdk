# Revision History

# **ELE FW NOM v1.0.0 (8ULP/93 ONLY !)**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## RC1 (344acb84):
**FW generic:** 
* Increase SRTC serving LMDA timer from 1h to 23h59 (93 only)

**Baseline:**
* Check for events before closing the chip
* Write fuse policy reworked for OEM closed lifecycles

**SAB:**
* CFB, OFB, CTR length alignement check bugfix
* Add NXP_PROD_MANUFACT_KA key to be used with key exchange API (93 only)
* Better indicator when output buffer is too short
* Dedicated error code when HSM disabled in case of NVM error

## RC2 (04b8492e) - 93 only:
* 24h watchdog fix
* fast boot get status event fix
* remove lp boot limitation for A55 resume

## Supported revsion
* i.MX8ULP A1/A2
* i.MX93 A1

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.1.1 (RT1180 ONLY !)**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## (5771ddc1):
**Baseline**
* bugfix IEE runtime API
* Update FW version to 0.1.1
 
## Supported revsion
* i.MXRT1180 B0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.


# **ELE FW NOM v0.1.0 (RT1180 ONLY !)**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.


## RC1 (642b5ae2):
**FW generic**
* Bug fix when FW is re-authenticated

**SAB:**
* Storage master import performance improved
* Add new Key store reprovisioning API
* Add SAB get device information API
* Add EL2GO key import API (SRKH import supported)
* Add EL2GO data import API
* RSA opaque sign/verify is now supported
* AES opaque cipher encrypt/decrypt is now supported
* AES opaque AEAD encrypt/decrypt is now supported
* HMAC/CMAC opaque keys are now supported
* Key ID can now be set by User
* Brainpool added to ECC support
* ELE maintain list of keys (Max number of keys set to 100)

## RC2 (aa1615e1):
**Baseline**
* New program BBSM API
* IEE runtime API
* Write shadow API removed from Alternative FW to make room 

**SAB:**
* AEAD generic API input sanity check bugfix

Please note that some APIs are expected to be slower than in previous release because now ROM is used to handle these. At ROM release time, the differents performances optimisations were not done. 


## Supported revsion
* i.MXRT1180 B0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.1.0 (8ULP/93 ONLY !)**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.


## RC1:
**FW generic**
* Bug fix when FW is re-authenticated

**Baseline:**
* Program BBSM API (i.MX93 only)

**SAB:**
* SAB NVM command CRC bugfix
* Storage master import performance improved
* UUID endianness fix in Data storage encrypted API and public key attest API 
* Add reseed flags in RNG API
* Add new Key store reprovisioning API (i.MX93 only)
* Add new Key exchange API (i.MX93 only)
* Add new OEM key import API (i.MX93 only)

## RC2:

**SAB:**
* AEAD generic API input check bugfix
* AES opaque key OFB CFB CTR input check bugfix
* BBSM CPR_CONFIG bugfix
* pulldown apply on BBSM tamper1 pin (8ULP)

## Supported revsion
* i.MX8ULP A1/A2
* i.MX93 A1

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.0.12 (RT1180 A0 ONLY !)**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## SAB features
**opaque keys:**  
asymmetric:  
- ECC

symmetric:  
- NA

**Plaintext keys:**  
asymmetric:
- RSA: key gen

symmetric:
- Cipher
- AEAD
- HMAC
- Fast HMAC

## RC1:
* Fast HMAC API: New API to let ELE enter a "special" fast mac mode. In this mode, ELE can only handle MAC compute request. User can exit this mode at any time.

# Delivery contents

## Supported revsion
* i.MXRT1180 rev A0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.0.11 (8ULP/93 ONLY !)**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.


## RC1:
**FW generic**
* 93: MU trust now supported. A dummy header needs to be sent in order to workaround HW trust MU protocol

**Baseline:**
* Device Attest API version missmatch fix. API now take 4 words of nonce. v1 (8ULP) will use the first nonce word, v2(93) will use them all
* 8ULP: OEM encrypted boot bugfix
* 8ULP: CAAM security violation workaround after JTAG connection:
    * Sec_vio0 is not set in release CAAM command in oem open
    * Sec_vio0 is unset during a debug authentication protocol success
* Device Attest API version returned in Get info API
* 8ULP: Derive key API removed

**SAB:**
* SAB init can be called multiple time
* Fix ELE key group cache mechanism. If key is already loaded to ELE, performances will significantly increase
* 93: SAB public key attestation API added
* SAB data storage updated to support 32 bits ID
* SAB data storage updated to support EL2GO TLV
* SAB encrypted data storage API added

## RC2:
**FW generic**
* 93: MU trust address convertion bugfix: This MU now assume that requester is in APD for address convertion. (used to be RTD in RC1).

**SAB:**
* FW vs PSA key list is now maintained by ELE to ensure integrity.
* Data storage: Fix EL2GO TLV decode function when LENGTH field is a long form format.
* Encrypted Data storage: Accept 0x0 as lifecycle to set the "current device lifecycle" to the data (same behavior as generate key API).

## Supported revsion
* i.MX8ULP A1/A2
* i.MX93 A1

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.0.11 (RT1180 ONLY !)**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## SAB features
**opaque keys:**  
asymmetric:  
- ECC  

symmetric:  
- NA

**Plaintext keys:**  
asymmetric:
- RSA: key gen
- RSA: sig/ver/crypt (B0)

symmetric:
- Cipher
- AEAD
- HMAC

## Existing feature changes 
* ELE FW overhead optimized for max performances. Some hardening has been removed to achieve requested performances.

## EAR
* HMAC generic crypto API with delivered new hmac() CryptoLib function

**Bug fixes**
* Data storage bug fix with sizes not 4 bytes aligned

## RC1:
* Generic RSA Sig/verif/encrypt/decrypt is removed on A0
* Crypto lib RC1 package integrated in FW (S401_2_0_0 package)
* Address MSB word removed from request (only 8 request word now, including CRC)

# Delivery contents

## Supported revsion
* i.MXRT1180 rev A0/B0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.0.10 (i.MX8ULP, i.MX93)**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## Existing feature changes
**ALL APIs:**
* ELE now use requestor's DID to access external memory
* ELE now use requestor's TrustZone bit to access external memory

**Baseline:**
* Derive key API: derived key are now binded with requestor's MasterNum and TrustZone state. One time only call policy do no longer apply
* Derive key API: User can now gives to ELE a context to diversify key
* Write Fuse API: 8ULP - USB VID, USB0_PID, USB1_PID can now be written by customer. Bank 5 word 6-7
* Write Shadow API: OCOTP write shadow policy updated. It now use fuselist to prevent a bad write shadow fusing
* Release CAAM API: Only released in secure state in OEM Closed lifecycle on 8ULP A2 if fuse SI_REV is provionned with value 0x2

**SAB:**
* Hardening added after VA/SMP code review
* Hash API: open and close API removed
* RNG API: open and close API not supported anymore (not needed anymore, deprecated in previous release)
* RNG API: command ID changed to match "generic" API ones.
* Key location define updated


## New features
**SAB:**
* Add key lifecycle and key origin attribute. Get key attribute API updated accordingly
* Hash API: streaming capability. Init/Update/Final 
* RSA with opaque keys now supported: Sign/Verify (93 only)
* RSA with plaintext keys now supported: Sign/Verify/Encrypt/Decrypt (93 only)
* AES CTR/OFB/CFB added (93 only)
* Support of user's input key ID
* NVM new command created to handle user's key ID feature
* Keystore are binded to a MasterNumber TZ, and UUID.
* Session open: Fields DID, TZ, and MU are not needed anymore. ELE read it directly with HW. Fields are now reserved and not checked by ELE for backward compatibility
* ELE ROM provisioned keys can now be used in SAB APIs (EL2GO key)
* EL2GO key import support: Key importation to SAB keystore using an EL2GO signed TLV blob
* EL2GO SRKH import support: OEM SRKH can now be burn into fuses using an EL2GO self-signed TLV blob
* Monotonic counter. Keystore can now be protected from rollback attacks with fuses. New flag for increment added. Make sure to use this feature with caution as no keystore re-provisioning mechanism is implemented for now.
* Key store cannot be retrieve in Field return lifecycles


## Bug fixes
**RC1:**

**Baseline:**
* Attest API: Bugfix - Signature now cover all the fields.

**SAB:**
* Minor define bug fix (lifetime, truncated mac etc)
* Bug fix when a user try to generate a key in a key group > 100
* CRC added for command longer than 4 words in NVM requests
* MAC bugfix

**RC2:**

**Baseline:**
* Get info soc_rev return 0xA200 if fuse SI_REV equal 2

**SAB:**
* Update usage policy (sign hash will set automatically sign message as well)
* Update key lifecycle mangement to match EL2GO requirements
* Permanent key hanling fix
* RSA export public key fix
* Support of "system" keys (nxp_die_id_auth_prk) through SAB APIs
* Update hardcoded key IDs to match EL2GO requirements 
* Data storage bugfix with sizes not 4 bytes aligned

**Hotfix 1 (JTAG CAAM violation fix)**
* Sec_vio0 is not set in release CAAM command in oem open.
* Sec_vio0 is unset during a debug authentication protocol success.

## Known issues
* 8ULP: Attest API - Same ELE ROM is used between A1 and A2. As a result, RROT protected attest API return 0xA100 for silicon revision. SHA256 ROM patch can be used to distinguish a A1 from an A2.
* 8ULP: Due to a lack of space in FW, AES and ECC generic crypto (plaintext keys) are disabled 
* 93 A0: RSA PSS OEM auth container salt len fixed to 20. No more space in FW to fix it. Will be done on A1
* 93 A0: Due to a lack of space in FW, debug authentication is not supported in this FW. Another one with Debug Auth and without SAB will be provided.
* SAB performance degradation in case of opaque key operation due to new NVM command.
# Delivery contents

## Supported revsion
* i.MX8ULP rev A1/A2
* i.MX93 rev A0/A1

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.0.10 (RT1180 ONLY !)**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## Existing feature changes 
* RNG Open/Close APIs are removed
* Hash API is now in generic APIs
* Key location value updated

## New features
* Hash streaming capability
* AES CTR/OFB/CFB added
* ECC opaque key generation
* ECC opaque key sig/verify
* Keystore anti rollback protection based on fuses

## Bug fixes
* Bug fix when a user try to generate a key in a key group > 100
* CRC added for command longer than 4 words in NVM requests
* generic API address check bugfix

# Delivery contents

## Supported revsion
* i.MXRT1180 rev A0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.


# **ELE FW NOM v0.0.9**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## Existing feature changes 
* Open GP fuses to read fuse API (8ULP  only)

## New features
* Service swap API (8ULP only)
* Get info API version 2
* SAB functionalities are now available after RTD powerdown
* Generic API: RSA key generate, Sign/Verify and Encrypt/Decrypt (RT1180 only)

## Bug fixes
RC1 bug fixes:
* OEM RSA PSS authenticate container now use hash lenght as saltLen. Used to be 20. (93 only)
* Get info API fix
RC2 (RT1180 only):
* Get info API back to version 1
* Data storage abort bug fix

# Delivery contents

## Supported revsion
* i.MX93 rev A0
* i.MX8ULP rev A1
* i.MXRT1180 rev A0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.


# **ELE FW NOM v0.0.8**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## Existing feature changes 
* SAB Improve error code indication
* SAB Get random API don't need open/close anymore
* SAB Do not abort anymore in case of a NVM failure
* SAB Pub key recovery API update (key type not needed anymore)
* SAB Fix signature API and add SAB_ELE_ALG_ECDSA_ANY signature scheme
* SAB Update key generate API
* SAB Maximum global chunk is now 100
* SAB Data storage is no more limited to 1024 bytes
* SAB Bugfix and internal improvments
  
## New features
* SAB Get key attributes API
* Derive key API

## Bug fixes
RC1 bug fixes:
* OEM blob can now be generated in DDR.
* CAAM is now released in secure state in OEM closed lifecycles (8ULP)
* SAB AEAD API fix
  
RC2 bug fixes:
* 8ULP: XRDC release with config 5
* 8ULP: Handle APD power-up in case S400 is the only DBD owner
* SAB: Fix SRDC chunk import/export
* SAB: Fix transient keystore closing
* SAB: fix cipher for size bigger than UINT16_MAX
* Allow write secure fuse mass updates in the open lifecycles
* Secure counter isr bug fix
* OEM Encryption fix for image size bigger than 65k

Hotfix 1(8ULP A1 Only):
* Fuse bank 32 to 36 and 49 to 51 can be read through ELE read fuse API
* Hotfix bit in FW version increased

# Delivery contents

## Supported revsion
* i.MX93 rev A0
* i.MX8ULP rev A1
* i.MX8ULP rev A0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.0.7**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## Existing feature changes 
* SAB Improve RNG API performance 
* SAB Improve verify API performance
* SAB AEAD GCM IV can now be fully generated by the user 
* SAB AEAD no more payload size limitation
* SAB key delete do not require key_group in parameter anymore
  
## New features
* SAB Init API (will be needed later)
* SAB Min mac length now suported
* RT1180: Data storage added 

## Bug fixes
RC2 bug fix (8ULP A1 only) : 
* TRDC fix 
* Mandatory HSM API are now accessible after a power down

# Delivery contents

## Supported revsion
* i.MX93 rev A0
* i.MXRT1180 rev A0
* i.MX8ULP rev A0
* i.MX8ULP rev A1

## Tests description

Functional tests have been performed on the SAB features delivered:

**SAB :**
* Asymetric NIST/BRAINPOOL cypto signature/verify
* Hash 256/384/512
* SAB Key management
* Symetric crypto AES 128/256 CBC/ECB/CCM
* CMAC/HMAC
* RNG 
* Generic crypto
* Data storage

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.



# **ELE FW NOM v0.0.6**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## Existing feature changes 
* Get FW version API rework
* SAB Success status is now 0xd6
* SAB Generic crypto API command id has changed 
* SAB cipher is no more limited to 1024 bytes
* SAB Payload for MAC is no more limited 
* SAB rework of some algorithm define

## New features
* OEM Image encryption
* TRNG start API
* TRNG state API
* Debug Authentication

## Bug fixes

NA

# Delivery contents

## Supported revsion
* i.MXRT1180 rev A0
* i.MX93 rev A0

## Known limitation 
* iMX93: FW will not authenticate in OEM closed lifecycles as it is an engineering release

## Tests description

Functional tests have been performed on the SAB features delivered:

**SAB :**
* Asymetric NIST/BRAINPOOL cypto signature/verify
* Hash 256/384/512
* SAB Key management
* Symetric crypto AES 128/256 CBC/ECB/CCM
* CMAC/HMAC
* RNG 
* Generic crypto
* Data storage

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.




# **ELE FW NOM v0.0.5**

# Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## Existing feature changes 

* SAB API use now PSA standard
* SAB Cipher API bug fix when IV is not null
* SAB Crypto operation are now done "in place"
* SAB Key consistency is now checked in key generate API
* SAB Other minor Fix
* SAB ECC brainpool now supported

## New features

* SAB Generic crypto API
* Secure JTAG
* Commit API
* Get event

## Missing features

OEM image encryption is not yet available.

## Bug fixes

NA

# Delivery contents

## Supported revsion
* i.MX8ULP rev A0
* i.MX8ULP rev A1

## Tests description

Functional tests have been performed on the SAB features delivered:

**SAB :**
* Asymetric NIST/BRAINPOOL cypto signature/verify
* Hash 256/384/512
* SAB Key management
* Symetric crypto AES 128/256 CBC/ECB/CCM
* CMAC/HMAC
* RNG 
* Generic crypto
* Data storage

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.




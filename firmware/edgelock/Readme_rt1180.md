# Revision History

# **ELE FW NOM v1.1.0 (RT1180 B0 ONLY !)**

## Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## (b32f0938):
**FW common**
FW splitting into 4 binaries to support all needed features

**Baseline**
* TRDC multimage from same memory
* BBSM API

**SAB:**
* Fast MAC API 
* Generic MAC API
* Reseed flag in RNG API
* OEM key exchange API
* OEM key import API
* EL2GO data storage encrypted API
* Public key attest API

## Supported revsion
* i.MXRT1180 B0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.


# **ELE FW NOM v0.0.14 (RT1180 A0 ONLY !)**

## Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## RC1 (360e0165):
### SAB features
* Fast HMAC API: Performance Improvement + Dual key support and truncated MAC + corner case fix

## RC1.1 (473f0df9):
### SAB features
* Fast HMAC API: performance drop bugfix

## Delivery contents

## Supported revsion
* i.MXRT1180 rev A0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.


# **ELE FW NOM v0.0.13 (RT1180 A0 ONLY !)**

## Release description

This is the release note for EdgeLock Enclave (ELE) Firmware. This ELE FW is authenticated and installed by ELE ROM. It provides new features, fixes, and exposes cryptographic services to other cores through SAB.

## RC1:
### SAB features
* Fast HMAC API: Performance Improvement + Dual key support and truncated MAC.

## Delivery contents

## Supported revsion
* i.MXRT1180 rev A0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.


# **ELE FW NOM v0.1.1 (RT1180 B0 ONLY !)**

## Release description

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


# **ELE FW NOM v0.1.0 (RT1180 B0 ONLY !)**

## Release description

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

# **ELE FW NOM v0.0.12 (RT1180 A0 ONLY !)**

## Release description

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

## Delivery contents

## Supported revsion
* i.MXRT1180 rev A0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.0.11 **

## Release description

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

## Delivery contents

## Supported revsion
* i.MXRT1180 rev A0/B0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.0.10 (RT1180 A0 ONLY !)**

## Release description

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

## Delivery contents

## Supported revsion
* i.MXRT1180 rev A0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.


# **ELE FW NOM v0.0.9**

## Release description

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

## Delivery contents

## Supported revsion
* i.MX93 rev A0
* i.MX8ULP rev A1
* i.MXRT1180 rev A0

## Static code analysis

Static code analysis tool used is Coverity central analysis version **2021.12.1**

## Build instructions

The FW cannot be rebuilt and is available in binary form only.

# **ELE FW NOM v0.0.7**

## Release description

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

## Delivery contents

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

## Release description

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

## Delivery contents

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

## Release description

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

## Delivery contents

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




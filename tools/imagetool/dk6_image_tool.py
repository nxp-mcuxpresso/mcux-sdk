#!python

from collections import namedtuple
import re
import argparse
import subprocess
import struct
import binascii
import os
import sys
import string
import pdb

from io import StringIO

def auto_int(x):
   return int(x, 0)



def get_symbol_value(file, symb_name):
    val = -1

    objdump = subprocess.check_output(['arm-none-eabi-objdump', '--syms', file])
    objdump = objdump.decode('utf-8')

    symb_re = re.compile(r'^([0-9a-f]{8})[\s\S]+[\s]+([0-9a-f]{8})\s([\w\.]+)')

    for ln in StringIO(objdump):
        m = symb_re.match(ln)
        if m:
            if m.group(3) == symb_name:
                val = int(m.group(1), 16)
                break

    return val

def parse_sections(file):
    sections = {}

    Section = namedtuple('Section', ['idx', 'name', 'size', 'vma', 'lma', 'offset', 'align', 'flags'])

    objdump = subprocess.check_output(['arm-none-eabi-objdump', '-h', file])
    objdump = objdump.decode('utf-8')

    section_re = re.compile(r'(?P<idx>[0-9]+)\s'
                            r'(?P<name>.{13,})s*'
                            r'(?P<size>[0-9a-f]{8})\s*'
                            r'(?P<vma>[0-9a-f]{8})\s*'
                            r'(?P<lma>[0-9a-f]{8})\s*'
                            r'(?P<offset>[0-9a-f]{8})\s*'
                            r'(?P<align>[0-9*]*)\s*'
                            r'(?P<flags>[\[[\w]*[, [\w]*]*)')

    for match in re.finditer(section_re, objdump):
        sec_dict = match.groupdict()

        sec_dict['idx'] = int(sec_dict['idx'])

        for attr in ['vma', 'lma', 'size', 'offset']:
            sec_dict[attr] = int(sec_dict[attr], 16)

        sec_dict['align'] = eval(sec_dict['align'])

        #sections[sec_dict['name']] = Section(**sec_dict)
        sections[sec_dict['idx']] = Section(**sec_dict)

        if verbose > 1:
            #print "parse_sections " + (sections[sec_dict['name']])
            print (sections[sec_dict['idx']])

    return sections

def get_last_section(sections):
    last_section = None
    for _, section in sections.items():
        if 'LOAD' in section.flags:
            if last_section is None or section.lma > last_section.lma:
                if section.size > 0:
                    last_section = section
    if verbose:
        print("Last Section name= " + last_section.name.rstrip())
        print("Last Section LMA={:08x} Size={:08x}".format(last_section.lma, last_section.size))
    return last_section

def get_first_section(sections):
    first_section = None
    for _, section in sections.items():
        if verbose > 1:
            print("Section: {:s} {:s} {:x} {:x}".format(section.name, section.flags, section.lma, section.size))
        if 'LOAD' in section.flags:
            if first_section is None or section.lma < first_section.lma:
                first_section = section
    if verbose:
        print("First Section name= " + first_section.name.rstrip())
        print("First Section LMA={:08x} Size={:08x}".format(first_section.lma, first_section.size))
    return first_section

def get_section(sections, section_name):
    section_found = None
    for _, section in sections.items():
        if verbose > 1:
            print("Section: {:s} {:s} {:x} {:x}".format(section.name, section.flags, section.lma, section.size))
        if section.name.rstrip() == section_name and section.size != 0:
            section_found = section
    return section_found  

def reverseString2by2(string, stringLength):
    result = ""
    i = stringLength-1
    while i >=0:
        result = result + string[i-1]
        result = result + string[i]
        i = i-2
    return result

def print_sota_img_directory_cmd(blobNumber):
    nbBlobFound = 0
    sota_final_print = ""
    sota_final_print += "=================> SOTA information\n"
    # Generate the image directory command that will be used to provision the device
    valueToPrint = ".\\DK6Programmer.exe -V5 -s <COM_PORT> -P 1000000 -w PSECT:64@0x160="
    for i in range(1,9):
        bootable = "00"
        if i==1:
            bootable = "01"
        position_in_flash = get_symbol_value(elf_file_name, "m_blob_position"+str(i))
        position_in_flash = '%0*X' % (2,position_in_flash)
        blobTargetAddr = get_symbol_value(elf_file_name, "m_blob"+str(i)+"_start")
        blobTargetAddr = '%0*X' % (8,blobTargetAddr)
        blobStatedSize = get_symbol_value(elf_file_name, "m_blob"+str(i)+"_size")
        if position_in_flash != "00" and blobStatedSize != 0:
            nbBlobFound=nbBlobFound+1
            sota_final_print += "Position in flash = " + position_in_flash+" - targetAddr = 0x" +blobTargetAddr+ "\n"
        blobTargetAddr = reverseString2by2(blobTargetAddr, len(blobTargetAddr))
        blobNbPage = blobStatedSize/512
        blobNbPage = '%0*X' % (4,int(blobNbPage))
        blobNbPage = reverseString2by2(blobNbPage, len(blobNbPage))
        if blobStatedSize != 0:
            valueToPrint = valueToPrint + blobTargetAddr + blobNbPage + bootable + position_in_flash
        else:
            valueToPrint = valueToPrint + "0000000000000000"
    sota_final_print += "=====> Image directory command"
    sota_final_print += valueToPrint
    sota_final_print += "=================> (end) SOTA information"
    if nbBlobFound == blobNumber:
        print(sota_final_print)

def EvalHexArgumentToInt(arg_name, arg_str):
    int_result = 0
    error = 0
    arg_str = arg_str.strip()

    if arg_str.find("0x") != 0:
        try:
            int_result = int(arg_str, 10)
            error = 0
        except ValueError:
            error = -1
            print (arg_name + " integer argument must be composed of numeric digits")
    else:
        arg_str = arg_str[2:]
        try:
            int_result = int(arg_str, 16)
            error = 0
        except ValueError:
            error = -1
            print (arg_name + " integer argument must be composed of hex digits")

    return int_result, error

def HandleExtFlashSection(elf_file_name, sections, sect_name):
    extflash_section = get_section(sections, sect_name)
    if extflash_section is None:
        # print (sect_name + " section not found in ELF file: check name in linker script")
        return 0
    else:
        if extflash_section.size != 0 and extflash_section.lma >= 0x10000000:
            # the rodata section is placed in external flash
            extflash_section_hash = get_section(sections, '.extflash_hash')
            if extflash_section_hash is None:
                return -2
            if extflash_section_hash.size != 40 or extflash_section_hash.lma > 0x9de00:
                print(".extflash_hash section headroom must have been reserved in internal flash")
                return -3
            # Compute hash of rodata section
            from Crypto.Hash import SHA256
            with open(elf_file_name, 'r+b') as elf_file:
                elf_file.seek(extflash_section.offset)
                extflash_contents = elf_file.read(extflash_section.size)
                hash = SHA256.new(extflash_contents)
                # write hash to ro_data_section_hash
                hdr_s = struct.Struct("<LL")
                #pdb.set_trace()
                sect_hdr = hdr_s.pack(extflash_section.lma, extflash_section.size)
                print("extflash_section: address 0x{:08x} size 0x{:08x}".format(extflash_section.lma, extflash_section.size))
                elf_file.seek(extflash_section_hash.offset)
                elf_file.write(sect_hdr)

                elf_file.seek(extflash_section_hash.offset + hdr_s.size)
                elf_file.write(hash.digest())

            extflash_elf_name = elf_file_name.split(".")[0]+'_extflash.'+elf_file_name.split(".")[1]
            extflash_bin_name = extflash_elf_name.split(".")[0]+'.bin'
    
            #extflash_text_file =  'extFlash_text'

            extract_section = subprocess.check_output(['arm-none-eabi-objcopy',
                                             '--only-section='+sect_name,
                                              elf_file_name,
                                              extflash_elf_name])

            extract_section = subprocess.check_output(['arm-none-eabi-objcopy', 
                                                        '-v', '-O' , 'binary',  
                                                        extflash_elf_name, 
                                                        extflash_bin_name])

            remove_section = subprocess.check_output(['arm-none-eabi-objcopy',
                                             '--remove-section='+sect_name,
                                              elf_file_name])
            return 1
        else:
            return 0 
#
# Fill in the Nonce section that is used for AES image encryption and decryption
# Populating the .ro_nonce overwrites the section not changing its size 
#
def PopulateNonceSection(sections, args):
    nonce_section = get_section(sections, '.ro_nonce')
    if nonce_section is None:
        print (".ro_nonce section not found in ELF file: must be reserved in linker script")
        return -1
    else:
        NONCE_SECTION_SZ = 16
        if nonce_section.size < NONCE_SECTION_SZ:
            return -2
        if args.EncIV.find("0x") == -1:
            sNonceString = args.EncIV
        else:
            # skip the 0x
            sNonceString = args.EncIV[2:]
        sNonceString = sNonceString.strip()    
        if len(sNonceString) != NONCE_SECTION_SZ*2:
            print ("The AES initialization vector must be a 32 character string composed of hex digits")
            return -3
        if not all(c in string.hexdigits for c in sNonceString):
            print ("The AES initialization vector must be composed of hex string")
            return -4
        with open(args.out_file, 'r+b') as elf_file:
            elf_file.seek(nonce_section.offset)
            nonce = binascii.unhexlify(sNonceString)
            elf_file.write(nonce)
            elf_file.close()

        if verbose:
            print ("Populated Nonce with " + sNonceString)
        return 0

#
# ota_ext_hdr_value determines the format of the OTA Header extension optional fields
#  
#
def PopulateOtaHeaderOptionalFields(ota_ext_hdr_value, args):
    #write 13 bytes in all cases, the padding size is adjusted so that the place to wrtie the CRC to is always after
    if ota_ext_hdr_value == 0:
        ota_hdr_pad0_crc=struct.Struct("<13B")                # padding only till CRC
        ota_hdr_ext = ota_hdr_pad0_crc.pack(0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff)
        hdr_ext_sz = 0
    elif ota_ext_hdr_value == 1:
        ota_hdr_ext_security=struct.Struct("<B12B")           # only security version optional field
        ota_hdr_ext = ota_hdr_ext_security.pack(args.OtaSecurityVersion, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff)
        hdr_ext_sz = ota_hdr_ext_security.size - 12
    elif ota_ext_hdr_value == 2:
        ota_hdr_ext_mac=struct.Struct("<Q5B")                 # only OtaDestinationMac optional field
        ota_hdr_ext = ota_hdr_ext_mac.pack(args.OtaDestinationMac, 0xff, 0xff, 0xff, 0xff, 0xff)
        hdr_ext_sz = ota_hdr_ext_mac.size - 5
    elif ota_ext_hdr_value == 3:
        ota_hdr_ext_security_mac=struct.Struct("<BQ4B")
        ota_hdr_ext = ota_hdr_ext_security_mac.pack(args.OtaSecurityVersion, args.OtaDestinationMac, 0xff, 0xff, 0xff, 0xff)
        hdr_ext_sz = ota_hdr_ext_security_mac.size - 4
    elif ota_ext_hdr_value == 4:
        ota_hdr_ext_hardware=struct.Struct("<HH9B")  
        ota_hdr_ext = ota_hdr_ext_hardware.pack(args.OtaHwVersionMin, args.OtaHwVersionMax, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff)
        hdr_ext_sz = ota_hdr_ext_hardware.size - 9
    elif ota_ext_hdr_value == 5:
        ota_hdr_ext_security_hardware=struct.Struct("<BHH8B")
        ota_hdr_ext = ota_hdr_ext_security_hardware.pack(args.OtaSecurityVersion, args.OtaHwVersionMin, args.OtaHwVersionMax, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff)
        hdr_ext_sz = ota_hdr_ext_security_hardware.size - 8
    elif ota_ext_hdr_value == 6:
        ota_hdr_ext_mac_hardware=struct.Struct("<QHHB")          # single padding byte
        ota_hdr_ext = ota_hdr_ext_mac_hardware.pack(args.OtaDestinationMac, args.OtaHwVersionMin, args.OtaHwVersionMax,0xff)
        hdr_ext_sz = ota_hdr_ext_mac_hardware.size - 1
    elif ota_ext_hdr_value == 7:                                                     # all optional fields present no padding
        ota_hdr_ext_s = struct.Struct("<BQHH")    
        ota_hdr_ext = ota_hdr_ext_s.pack(args.OtaSecurityVersion, args.OtaDestinationMac, args.OtaHwVersionMin, args.OtaHwVersionMax)
        hdr_ext_sz = ota_hdr_ext_s.size
    else:
        ota_hdr_ext = []
        hdr_ext_sz = 0

    return ota_hdr_ext, hdr_ext_sz

#
# Populating the .ro_ota_header overwrites the section not changing its size
# Note that img_size must have been determined already
#
def PopulateOtaHdrSection(sections, args, img_size, is_signature):
    ota_hdr_section = get_section(sections, '.ro_ota_header')
    if ota_hdr_section is None:
        print (".ro_ota_header section not found in ELF file: must be reserved in linker script")
        return -1
    else:
        # the OTA header section is a placeholder that must contain the 56 mandatory bytes 
        # + 13 optional bytes 
        # + 4 CRC bytes --> thence the 75 
        # The actual section size is normally rounded to 80 bytes
        OTA_HDR_SECTION_SZ = (56+13+4)
        if ota_hdr_section.size < OTA_HDR_SECTION_SZ:
            return -2
        OTA_HEADER_MARKER = 0x0beef11e
        ota_hdr_s = struct.Struct("<I5HIH32sI")
        ota_ext_hdr = False
 
        ota_ext_hdr_value = 0             
        manufacturer = int(args.OtaManufacturer, 0)
        imageType = int(args.OtaImageType, 0)
        imageVersion = int(args.OtaFileVersionNb, 0)

        if args.OtaVersionString is None or len(args.OtaVersionString) != 32:
            print ("OTA Version string must be passed and its sie must be 32 characters")
            return -3

        # The OTA header may contain 3 optional fields:
        #  Hw Version range defined by Min and Max HH
        #  Security version  
        #if either OtaHwVersionMin or OtaHwVersionMax or both are specified
        # a Hw restriction applies and the extension must be added 
        if args.OtaHwVersionMin is not None or args.OtaHwVersionMax is not None:
            if args.OtaHwVersionMax > 0 and args.OtaHwVersionMax <= 0xffff:
                if args.OtaHwVersionMax >=  args.OtaHwVersionMin:
                    ota_ext_hdr = True
                    ota_ext_hdr_value   |= 4
        #if either OtaSecurityVersion is defined 
        # a Hw restriction applies and the extension must be added 
        if(args.OtaSecurityVersion != None):
            ota_ext_hdr_value  |= 1

        # OtaDestinationMac is to fill the u64UpgradeFileDest optional field
        if(args.OtaDestinationMac != None) :
            ota_ext_hdr = True
            ota_ext_hdr_value   |= 2

        if ota_ext_hdr_value != 0:
            ota_ext_hdr = True

        #####################
        # PopulateOtaHeaderOptionalFields call
        # hdr_ext_sz returns the number of significant extension bytes
        # but PopulateOtaHeaderOptionalFields fills padding up to CRC location

        ota_hdr_ext, hdr_ext_sz = PopulateOtaHeaderOptionalFields(ota_ext_hdr_value, args)
        header_size = ota_hdr_s.size
        header_size += hdr_ext_sz
        if verbose:
            print("ota_ext_hdr_value: {}".format(ota_ext_hdr_value))
            print("hdr_ext_sz: {}".format(hdr_ext_sz))


        total_image_size = header_size + img_size + 6
        if (is_signature):
            total_image_size += 256
        crc_s = struct.Struct("<I")
        crc = crc_s.pack(0)
        version_string = args.OtaVersionString.encode()
        version_array = bytearray(version_string)
        ota_hdr = ota_hdr_s.pack(
            OTA_HEADER_MARKER,
            int(args.OtaHeaderVersionNb, 0),
            header_size,
            ota_ext_hdr_value if ota_ext_hdr else 0,
            manufacturer,
            imageType,
            imageVersion,
            int(args.OtaStackVersionNb, 0),
            version_array,
            total_image_size)
        
        with open(args.out_file, 'r+b') as elf_file:
            elf_file.seek(ota_hdr_section.offset)
            elf_file.write(ota_hdr)
            elf_file.write(ota_hdr_ext)  # always write 13 bytes because of padding
            elf_file.write(crc)          # so that CRC immediately follows
            elf_file.close()
        if verbose:
            print ("Populated OTA Header")
        return 0

def PatchOtaHeaderImageCrc(sections, args, crc_value):
    ota_hdr_section = get_section(sections, '.ro_ota_header')
    if ota_hdr_section is None:
        print (".ro_ota_header section not found in ELF file: must be reserved in linker script")
        return -1
    else:
        with open(args.out_file, 'r+b') as elf_file:
            # CRC is located at a fixed offset 69 from start of OTA HEader section
            elf_file.seek(ota_hdr_section.offset + 69)
            #crc = crc_value.encode()
            crc_s = struct.Struct("<I")
            crc = crc_s.pack(crc_value)
            crc_array = bytearray(crc)
            elf_file.write(crc_array)
            elf_file.close()
        if 0:
            print ("Updated CRC with 0x{:08x}".format(crc_value))  
        return 0       

#
# Populating the .ro_se_LnkKey overwrites the section not changing its size 
#
def PopulateLnkKeySection(sections, args):
    lnk_key_section = get_section(sections, '.ro_se_lnkKey')
    if lnk_key_section is None:
        print (".ro_se_lnkKey section not found in ELF file: must be reserved in linker script")
        return -1
    else:
        LNK_KEY_SECTION_SZ = 16
        if lnk_key_section.size < LNK_KEY_SECTION_SZ:
            return -2
        if args.EncLnkKey.find("0x") == -1:
            sKeyString = args.EncLnkKey
        else:
            # skip the 0x
            sKeyString = args.EncLnkKey[2:]
        sKeyString = sKeyString.strip()

        if len(sKeyString) != LNK_KEY_SECTION_SZ*2:
            print ("The AES key must be a 32 character string composed of hex digits")
            return -3
        if not all(c in string.hexdigits for c in sKeyString):
            print ("The AES key must be composed of hex string")
            return -4
        with open(args.out_file, 'r+b') as elf_file:
            elf_file.seek(lnk_key_section.offset)
            lnk_key = binascii.unhexlify(sKeyString)
            elf_file.write(lnk_key)
            elf_file.close()
        if verbose:
            print ("Populated LnkKey with " + sKeyString)        
        return 0

def BuildCompatibilityList(args, offset):
    status = 0
    compatibility_list = []
    compatibility_len = 0
    compatibility = b''

    if args.compatibility_list is None:
        # dont go any further
        print("No compatibility list")
        return compatibility, compatibility_len, status

    compatibility_struct     = struct.Struct('<2L')
    compatibility_len_struct = struct.Struct('<L')
    print("Compatibility list:")
    if verbose:
        print("    {}".format(args.compatibility_list))
    compatibility_list = [list(map(auto_int, compatibility_item.split(","))) for compatibility_item in args.compatibility_list.split(";")]
    print("    Length: {}".format(len(compatibility_list)))
    for i in range(len(compatibility_list)):
        item = compatibility_list[i]
        for j in range(len(item)):
            if j ==1:
                blobIdCompatibilityList = "     Blob ID 0x="  + '%0*X' % (8,item[j-1])
                print("Blob ID =0x"+'%0*X' % (4,item[j-1]) +" - version =0x"+'%0*X' % (8,item[j]))
    compatibility_len = len(compatibility_list) * compatibility_struct.size + compatibility_len_struct.size
    if verbose:
        print("    {}".format(compatibility_len))
    
    if args.sota_number_of_blob is not None:
        # make sure that the compatibility list is added and equals to nb_blob - 1
        if (compatibility_len//compatibility_struct.size) != args.sota_number_of_blob-1:
            print("!!! Error the compatibility list length must be = to the number of blobs -1 : "+str(compatibility_len/compatibility_struct.size)+"(len) != "+ str(args.sota_number_of_blob-1))
            status = 1
        #make sure that the blob ID is given
        if args.blob_id is None:
            print("!!! Error the blob ID is missing")
            status = 1

    if compatibility_len != 0:
        compatibility = compatibility_len_struct.pack(len(compatibility_list)) + b''.join([compatibility_struct.pack(*compatibility_item) for compatibility_item in compatibility_list])

    return compatibility, compatibility_len, status

def DetermineImageCharacteristics(elf_file_name, args):
    error = 0
    IMAGE_HEADER_MARKER    = 0x98447902
    IMAGE_HEADER_APP_CORE  = 0x02794498
    IMAGE_HEADER_ESCORE    = IMAGE_HEADER_MARKER
    SSBL_OR_LEGACY_ADDRESS = 0x00000000
    SSBL_STATED_SIZE       = 0x2000
    ZB_TARGET_ADDRESS      = SSBL_STATED_SIZE * 2
    ZB_STATED_SIZE         = 0x4f000
    BLE_TARGET_ADDRESS     = ZB_TARGET_ADDRESS + ZB_STATED_SIZE
    BLE_STATED_SIZE        = 0x40000
    if args.image_identifier is not None:
        image_iden = args.image_identifier
    else:
        if args.sota_number_of_blob is not None:
            # In case of SOTA get the position in flash from the linker it should be the app_id
            image_iden = get_symbol_value(elf_file_name, '__blob_position__')
            print("Blob position in flash = #"+str(image_iden))
        else:
            image_iden = 0

    #Default value for SSBL, ZigbeeFull and BleFull image id
    if image_iden == 0:
        image_addr = SSBL_OR_LEGACY_ADDRESS
        stated_size = SSBL_STATED_SIZE
    elif image_iden == 1:
        image_addr = ZB_TARGET_ADDRESS
    elif image_iden == 2:
        image_addr = BLE_TARGET_ADDRESS

    if verbose:
        print("Image Identifier is {:d}".format(image_iden))

    image_addr = get_symbol_value(elf_file_name, 'm_app_start')
    if (image_addr == -1):
            image_addr = get_symbol_value(elf_file_name, '__vectors_start__')
    stated_size = get_symbol_value(elf_file_name, 'm_app_size')            

    # Overwrite defaults for image address, stated size and header marker (-t, -s, -a options)
    if args.target_addr is not None:
        image_addr, error = EvalHexArgumentToInt("image_addr", args.target_addr)
    if args.stated_size is not None:
        stated_size, error = EvalHexArgumentToInt("stated_size", args.stated_size)
    if args.appcore_image is True:
        img_header_marker  = IMAGE_HEADER_APP_CORE
    else:
        img_header_marker = IMAGE_HEADER_MARKER + image_iden


    if verbose:
        print("image_iden=%d image_addr=0x%0*X" % (image_iden, 8, image_addr))
        print("stated_size=%d" % (stated_size))
        print("version=0x%0*X" % (8,args.version))

    return error, img_header_marker, image_addr, stated_size

def ComputeVectorChecksum(fields):
    vectsum = 0
    for x in range(7):
        vectsum += fields[x]
    res = (~vectsum & 0xFFFFFFFF) + 1
    if 0:
        print("Checksum {:08x} Complement to 1 {:08x}".format(vectsum, res))
    return res
#
# Patching the image header section simply partially overwrites the section not changing its size 
#
def PatchImageHeader(first_section, elf_file_name, args, img_header_marker, boot_block_offset):
    status = 0
    header_struct     = struct.Struct('<7LLLLL')

    header=""
    with open(args.out_file, 'r+b') as elf_file:
        elf_file.seek(first_section.offset)
        vectors = elf_file.read(header_struct.size)

        fields = list(header_struct.unpack(vectors))


        vectsum = ComputeVectorChecksum(fields)
        fields[7]  = vectsum
        fields[8]  = img_header_marker
        fields[9]  = boot_block_offset

        #Compute crc
        head_struct     = struct.Struct('<10L')
        try:
            if verbose:
                for i in range(10):
                    print("Header[{:d}]= {:08x}".format(i, fields[i]))
            values = head_struct.pack(fields[0],
                                  fields[1],
                                  fields[2],
                                  fields[3],
                                  fields[4],
                                  fields[5],
                                  fields[6],
                                  fields[7],
                                  fields[8],
                                  fields[9])
            fields[10] = binascii.crc32(values) & 0xFFFFFFFF
        except:
            status = -1

        print("Writing checksum {:08x} to file {:s}".format(vectsum, args.out_file))
        print("Writing CRC32 of header {:08x} to file {:s}".format(fields[10], args.out_file))

        elf_file.seek(first_section.offset, 0)
        header = header_struct.pack(*fields)
        elf_file.write(header)
        elf_file.close()
    return status


# 
#  UpdateLastSection: changes the length of the section so requires an 'update_section' operation
#  This function is called a first time 
#
def UpdateLastSection(sections, args, 
                      image_addr, stated_size,
                      cert_file_path, signing, signature):
    status = 0
    boot_block_struct = struct.Struct('<8L')
    BOOT_BLOCK_MARKER      = 0xBB0110BB
    certificate_offset = 0
    compatibility_offset = 0
    expected_cert_len = 0
    boot_block_offset = 0
    last_section = get_last_section(sections)
    # IAR toolchain uses odd section names that contain spaces
    # the regexp now may now return trailing spaces too, need to strip them
    last_section_name = last_section.name.rstrip()

    # and add quotes around the section name
    last_section_name = r"%s" % (last_section_name)
    offset = last_section.lma + last_section.size - image_addr


    with open(args.out_file, 'r+b') as elf_file:
        elf_file.seek(last_section.offset, 0)
        initial_last_section_content = elf_file.read(last_section.size)
        elf_file.close()

    if not signing:
        compatibility, compatibility_len, error = BuildCompatibilityList(args, offset)
        if error != 0:
            print ("Failed to append compatibility section")
            return -100, 0, 0
        if compatibility_len == 0:
            compatibility_offset = 0
        else:
            compatibility_offset = offset

        boot_block_offset = offset + compatibility_len

        # determine amount of padding to be inserted
        # IAR toolchain uses odd section names that contain spaces
        if (args.certificate is True):
            expected_cert_len = 40+256+256

        # Correction for image size not being multiple of 4 (IAR)
        padding_len_4 = ((4 - (boot_block_offset%4)) & 3)
        boot_block_offset = boot_block_offset + padding_len_4
        if verbose:
            print ("Section 4 byte rounding: padding %d bytes" % (padding_len_4))

        # Add padding for AES : iterate to force size to be a multiple of AES blocks 
        tmp_boot_block_offset = boot_block_offset
        total_sz = tmp_boot_block_offset + boot_block_struct.size + expected_cert_len
        padding_len_16 = (16 - (total_sz % 16)) & 15
        boot_block_offset = boot_block_offset + padding_len_16
        total_sz += padding_len_16
        if verbose:
            print ("Section 16 byte alignment %d" % (padding_len_16))


        #if there is padding to be inserted, it cannot go beyond 18 bytes
        padding_len = padding_len_4 + padding_len_16
        if padding_len != 0:
            padding_bytes = bytearray(padding_len)

        print ("Boot Block Offset: {:08x}".format(boot_block_offset))

        # the boot block presence is unconditional: insert it right after the padding
        if args.appcore_image is True:
            boot_block_id = 1
        else:
            boot_block_id = 0

        if (args.certificate is True):
            certificate_offset = boot_block_offset + boot_block_struct.size

        if args.blob_id is not None:
            boot_block_id = args.blob_id
        
        if verbose:
            print("stated size is {:08x} ({})".format(stated_size,stated_size))
            print("Image total size is {:d}".format(total_sz))
        boot_block = boot_block_struct.pack(BOOT_BLOCK_MARKER,
                                            boot_block_id,
                                            image_addr,
                                            total_sz, # padding already included in the boot_block_offset
                                            stated_size,
                                            certificate_offset,
                                            compatibility_offset,
                                            args.version)
        total_img_sz = boot_block_offset + boot_block_struct.size
        # Append the certificate after the BOOT_BLOCK structure
        certificate_len = 0     
        if (args.certificate is True):
            certif_file_path = cert_file_path
            if verbose:
                print("Cert key path is " + cert_file_path)
            if (os.path.isfile(certif_file_path)):
                certif_file=open(certif_file_path, 'rb')
                certificate = certif_file.read()
                print("Certificate processing...")
                certificate_len = len(certificate)
                if certificate_len != expected_cert_len:
                    print("Certificate length error expected %d got %d" % (expected_cert_len, certificate_len))
                    return -101, 0, 0
                else:
                    total_img_sz += expected_cert_len
        with open('temp_last_section.bin', 'wb') as tmp_file:
            tmp_file.write(initial_last_section_content)
            if compatibility_len != 0:
                tmp_file.write(compatibility)
            if padding_len != 0:
                tmp_file.write(padding_bytes)
            tmp_file.write(boot_block)
            if certificate_len != 0:
                tmp_file.write(certificate)
    else:
        total_img_sz = offset + len(signature)
        # appending signature
        with open('temp_last_section.bin', 'wb') as tmp_file:
            tmp_file.write(initial_last_section_content)
            tmp_file.write(signature)

    update_section = subprocess.check_output(['arm-none-eabi-objcopy',
                                              '--update-section',
                                              '%s=temp_last_section.bin' % last_section_name,
                                              args.out_file,
                                              args.out_file])

    return status, boot_block_offset, total_img_sz

#
# JN518x ES2 version
######################
def BuildImageElf(args, elf_bin_file, bin_file_name, verbose):
    is_signature = False
    error = 0
    if args.signature_path is not None:
       sign_dir_path = args.signature_path
       if os.path.isdir(sign_dir_path) == False:
          sign_dir_path = os.path.join(os.path.dirname(__file__), args.signature_path)
          if os.path.isdir(sign_dir_path) == False:
             return -1
          else:
             error = 0
       else:
          error = 0
       priv_key_file_path = os.path.join(sign_dir_path, 'priv_key.pem')
       cert_file_path = os.path.join(sign_dir_path, 'cert.bin')
    else:
        sign_dir_path = os.path.join(os.path.dirname(__file__), '')
        priv_key_file_path = os.path.join(sign_dir_path, 'testkey_es2.pem')
        cert_file_path = os.path.join(sign_dir_path, 'certif_es2')

    if args.key is True:
        from Crypto.Signature import pkcs1_15
        from Crypto.PublicKey import RSA
        from Crypto.Hash import SHA256
        from Crypto.Util import number

        key_file_path = priv_key_file_path
        if verbose:
            print("key path is " + key_file_path)
        if (os.path.isfile(key_file_path)):
            key_file=open(key_file_path, 'r')
            key = RSA.importKey(key_file.read(), args.password)
            print("Private RSA key processing...")
            is_signature = True
        else:
           print("Private key file not found")
           return -2

    sections = parse_sections(elf_file_name)


    # if encryption of the image is to be performed, we need to store the nonce in the ro_nonce section placeholder
    if args.EncIV is not None:
        error = PopulateNonceSection(sections, args)
        if error != 0:
            print ("Failed to populate Nonce initialization vector")
            return -3

    if args.EncLnkKey is not None:
        error = PopulateLnkKeySection(sections, args)
        if error != 0:
            print ("Failed to populate LnkKey ")
            return -4
    status = HandleExtFlashSection(elf_file_name, sections, '.ext_text')
    if status < 0:
        print ("Failed to place section in external flash")
        return -12
    elif status == 1:
        # need to reload sections
        sections = parse_sections(elf_file_name)

    error, image_header_marker, image_addr, stated_size = DetermineImageCharacteristics(elf_file_name, args)
    if error != 0:
        print("Bad argument setting stated_size or target_address")
        return -5

    error, boot_block_offset, img_total_len = UpdateLastSection(sections, args,
                                                                image_addr, stated_size, 
                                                                cert_file_path, False, b'')
    if error != 0:
        print("Error while patching last section")
        return -6

    # force section parsing again because ELF file got updated
    sections = parse_sections(elf_file_name)

    # we only learn the final boot_block_offset when we know the padding size which is itself deduced depending on the
    # overal
    first_section = get_first_section(sections)
    error = PatchImageHeader(first_section, elf_file_name, args, image_header_marker, boot_block_offset)
    if error != 0:
        print("Error while patching image header")
        return -7 

    # Force CRC to 0 at this stage
    if (args.zgEmbedOtaHeader is True):
        error = PopulateOtaHdrSection(sections, args, img_total_len, is_signature)
        if error != 0:
            print("Error while patching embedded OTA header")
            return -8

    # The ELF file is patched at this stage : let's proceeed to the CRC computation
    if (args.zgEmbedOtaHeader is True):
        import crccheck
        bin_output = subprocess.check_output(['arm-none-eabi-objcopy', '-O', 'binary', elf_file_name, bin_file_name])
        with open(bin_file_name, 'rb') as in_file:
            input_file = in_file.read()
        imagecrc = crccheck.crc.Crc32Bzip2().process(input_file).finalhex()
        in_file.close()
        print("Computed Image CRC " + imagecrc )
        if PatchOtaHeaderImageCrc(sections, args, int("0x"+imagecrc, 16)) != 0:
            print("Error while updating CRC in OTA header")
            return -9


    if (is_signature == True):
        # read again the whole file and compute the hash and signature
        bin_output = subprocess.check_output(['arm-none-eabi-objcopy', '-O', 'binary', elf_file_name, bin_file_name])
        with open(bin_file_name, 'rb') as in_file:
            message = in_file.read()
        hash = SHA256.new(message)
        signer = pkcs1_15.new(key)
        signature = signer.sign(hash)
        # append signature to last section

        error, boot_block_offset, img_total_len = UpdateLastSection(sections, args,
                                                                    image_addr, stated_size,
                                                                    cert_file_path, True, signature)
        print("Signature processing...")
        if error != 0:
            print("Error while signing image")
            return -10

    bin_output = subprocess.check_output(['arm-none-eabi-objcopy',
                                          '-O',
                                          'binary',
                                          elf_file_name,
                                          bin_file_name])

    out_file_sz = os.stat(bin_file_name).st_size
    print("Binary size is {:08x} ({})".format(out_file_sz, out_file_sz))

    if args.sota_number_of_blob is not None:
        print_sota_img_directory_cmd(args.sota_number_of_blob)

    if out_file_sz > stated_size:
        print("Error: Binary file size ({:08x}) must be less or equal to stated size {:08x}".format(os.stat(bin_file_name).st_size, stated_size))
        return -11
    if out_file_sz != img_total_len:
        print("File size %d different from expected %d" %  (out_file_sz, img_total_len))
        return -12

    return 0


parser = argparse.ArgumentParser(description='DK6 Image Header Generator')
parser.add_argument('in_file', help="Binary to be post-processed: generating header and optionally appending certificate and/or signature.")
parser.add_argument('out_file', nargs='?')
parser.add_argument('-g',        '--signature_path',                                                                   help="Sets directory from which certificate and private key are to be retrieved")
parser.add_argument('-k',        '--key', action='store_true',                                                         help="2048 bits RSA private key in PEM format used to sign the full image. If -c option is used the full image includes the certificate + the signature of the certificate. The key shall be located in the same directory as the image_tool script. See priv_key.pem example.")
parser.add_argument('-p',        '--password',                                                                         help="This is the pass phrase from which the encryption key is derived. This parameter is only required if key provided through the -k option is a PEM encrypted key.")
parser.add_argument('-c',        '--certificate', action='store_true',                                                 help="When option is selected, the certificate cert.bin is appended to the image.")
parser.add_argument('-i',        '--image_identifier', type=int,                                                       help="This parameter is to set the archive identifier. 0: SSBL or legacy JN518x/QN9090 applications, loaded at 0x00000000. 1: application (ZB) loaded at address 0x00004000 by default. 2: application (BLE) image loaded at address 0x00053000 by default")
parser.add_argument('-a',        '--appcore_image', action='store_true',                                               help="This parameter is only relevant if dual application (app1 image) shall reside in flash. Do not use in conjunction with -i option.")
parser.add_argument('-t',        '--target_addr',                                                                      help="Target address of image. Used in conjunction with -i option to override the default set by image identifier, or with -a option to specify address of the appcore image (app1 image).")
parser.add_argument('-s',        '--stated_size',                                                                      help="This is the stated size of the image in bytes. Default is 0x48000.")
parser.add_argument('-v',        '--version', type=auto_int, default=0, help="Image version. Default is 0.")
parser.add_argument('-b',        '--verbose', type=int, default=0, help="verbosity level. Default is 0.")
parser.add_argument('-cl',       '--compatibility_list',                                                               help="Compatibility list")
parser.add_argument('-sota',     '--sota_number_of_blob', type=int, help="This parameter is used to generate the image directory command to be provisioned")
parser.add_argument('-bid',      '--blob_id', type=auto_int, help="This parameter is to add a blob id. Can be used only if the sota arg is given")

parser.add_argument('-zgEmbedOtaHeader',  '--zgEmbedOtaHeader', action='store_true',                                   help="When option is selected, zigbee ota header information will be filled")
parser.add_argument("-EncIv",             '--EncIV',                                                                   help="Nonce Initial Vector for encryption 16 hex bytes" )
parser.add_argument("-EncLnkKey",         '--EncLnkKey',                                                               help="Key AES encryption/decryption 16 hex bytes" )

parser.add_argument("-OtaMan",            '--OtaManufacturer',                      default="0x1037",                  help="OTA manufacturer code" )
parser.add_argument("-OtaVersionStr",     '--OtaVersionString',                                                        help="OTA version string")

parser.add_argument("-OtaImgTyp",         '--OtaImageType',                         default="0x0001",                  help="OTA header image type")
parser.add_argument("-OtaHdrV",           '--OtaHeaderVersionNb',                   default="0x0100",                  help="OTA header version")
parser.add_argument("-OtaFileVersion",    '--OtaFileVersionNb',                     default="0x0001",                  help="OTA File version")
parser.add_argument("-OtaStackVersion",   '--OtaStackVersionNb',                    default="0x002",                   help="OTA stack version")
parser.add_argument("-OtaDestMac",        '--OtaDestinationMac',     type=int,                                         help="IEEE address of destination node targeted by OTA")
parser.add_argument("-OtaSecV",           '--OtaSecurityVersion',    type=auto_int,                                    help="Ota security credential version")
parser.add_argument('-OtaHwMin',          '--OtaHwVersionMin',       type=int,                                         help="define min of Hw versions compatible with OTA file. Implies inclusion in OTA header")
parser.add_argument('-OtaHwMax',          '--OtaHwVersionMax',       type=int,                                         help="define max of Hw versions compatible with OTA file. Implies inclusion in OTA header")

args = parser.parse_args()

elf_file_name = args.in_file
bin_file_name = elf_file_name.split(".")[0]+'_temp.bin'

if args.out_file is None:
    args.out_file = elf_file_name
verbose = args.verbose != 0

out_file_path = args.out_file

error = BuildImageElf(args, elf_file_name, bin_file_name, verbose)

cleanup_on_error = 1
if error != 0 and cleanup_on_error:
        os.remove(elf_file_name)
        os.remove(out_file_path)
os.remove(bin_file_name)
os.remove('temp_last_section.bin')


#
# JN518x ES1 version
######################
def BuildImageElfDeprecated(args, elf_file_name, bin_file_name, verbose):
    error = 0
    BOOT_BLOCK_MARKER = 0xBB0110BB

    header_struct     = struct.Struct('<7LLLLL')
    boot_block_struct = struct.Struct('<6LQ')

    sections = parse_sections(args.in_file)

    last_section = get_last_section(sections)

    if args.appcore_image is True:
        image_size = last_section.lma + last_section.size - args.target_appcore_addr
    else:
        image_size = last_section.lma + last_section.size

    dump_section = subprocess.check_output(['arm-none-eabi-objcopy', '--dump-section', '%s=data.bin' % last_section.name, args.in_file])

    if args.appcore_image is True:
        boot_block = boot_block_struct.pack(BOOT_BLOCK_MARKER, 1, args.target_appcore_addr, image_size + boot_block_struct.size, 0, 0, 0)
    else:
        boot_block = boot_block_struct.pack(BOOT_BLOCK_MARKER, 0, 0, image_size + boot_block_struct.size, 0, 0, 0)

    with open('data.bin', 'ab') as out_file:
        out_file.write(boot_block)

    update_section = subprocess.check_output(['arm-none-eabi-objcopy', '--update-section', '%s=data.bin' % last_section.name, args.in_file, args.out_file])

    first_section = get_first_section(sections)

    with open(args.out_file, 'r+b') as elf_file:
        elf_file.seek(first_section.offset)
        vectors = elf_file.read(header_struct.size)

        fields = list(header_struct.unpack(vectors))

        vectsum = 0

        for x in range(7):
            vectsum += fields[x]

        fields[7]  = (~vectsum & 0xFFFFFFFF) + 1
        if args.appcore_image is True:
            fields[9]  = 0x02794498
        else:
            fields[9]  = 0x98447902
        #fields[9]  = 0x98447902
        fields[10] = image_size

        print("Writing checksum {:08x} to file {:s}".format(vectsum, args.out_file))

        elf_file.seek(first_section.offset)
        elf_file.write(header_struct.pack(*fields))
    return error

#/*
# * Copyright 2024 NXP
# * 
# * SPDX-License-Identifier: BSD-3-Clause
# * The BSD-3-Clause license can be found at https://spdx.org/licenses/BSD-3-Clause.html
# */
import argparse
import os
import sys

def bin2c_convert(binfile_name, array_name, padding_len=0):

    with open(binfile_name, 'rb') as in_file:
        bindata = in_file.read()

    out = 'const char %s[%d] = {\n' % (array_name, len(bindata)+padding_len)
    line = ''
    first_char=True
    nb_char_in_line = 0
    for byte in bindata:
        if first_char:
            line += '     0x%02x' % byte
            first_char  = False
        else:
            line += ',0x%02x' % byte
        nb_char_in_line = nb_char_in_line + 1
        if nb_char_in_line == 16:
            out += '    ' + line + '\n'
            nb_char_in_line = 0
            line = '    '
    while padding_len > 0:
        line += ',0xff'
        padding_len = padding_len-1
    # add the last line
    if nb_char_in_line < 16:
        out += '    ' + line + '\n'
    out += '};\n'
    return out


def bin2c_file(bin_file_name, out_src_file_name, dest_path):

    bin_file_name=dest_path+'/../'+bin_file_name
    if not os.path.isfile(bin_file_name):
        print('File "%s" is not found!' % bin_file_name)
        return ''

    array_name = out_src_file_name
    out_src_file_name = dest_path + '/' + out_src_file_name + '.c'
    with open(out_src_file_name, 'w') as out_file:
        c_file = bin2c_convert(bin_file_name, array_name, 4)
        out_file.write(c_file)

def generate_sb_src(conn_fwloader_dir, chip_revision):

    a1_sb_list = [
        {'file': 'rw61x_sb_wifi_a1.bin',           'array_name': 'fw_cpu1'},
        {'file': 'rw61x_sb_ble_a1.bin',            'array_name': 'fw_cpu2_ble'},
        {'file': 'rw61x_sb_ble_15d4_combo_a1.bin', 'array_name': 'fw_cpu2_combo'}
    ]
    a2_sb_list = [
        {'file': 'rw61x_sb_wifi_a2.bin',           'array_name': 'fw_cpu1'},
        {'file': 'rw61x_sb_ble_a2.bin',            'array_name': 'fw_cpu2_ble'},
        {'file': 'rw61x_sb_ble_15d4_combo_a2.bin', 'array_name': 'fw_cpu2_combo'}
    ]

    if (chip_revision == 'A2'):
        binlist = a2_sb_list
    elif (chip_revision == 'A1'):
        binlist = a1_sb_list
    else:
        return
    print ("Directory=" + conn_fwloader_dir)
    dest_dir=conn_fwloader_dir+'/'+chip_revision
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)
     # SB3 format built for A0
    for i in range(0,3):
        input_file = binlist[i]['file']
        print(input_file, binlist[i]['array_name'])
        bin2c_file(input_file,  binlist[i]['array_name'],  dest_dir)


def generate_raw_src(conn_fwloader_dir, chip_revision):

    a1_raw_list = [
        {'file': 'rw61xw_raw_cpu1_a1.bin',                      'array_name': 'fw_cpu1'},
        {'file': 'rw61xn_raw_cpu2_ble_a1.bin',                  'array_name': 'fw_cpu2_ble'},
        {'file': 'rw61xn_combo_raw_cpu2_ble_15_4_combo_a1.bin', 'array_name': 'fw_cpu2_combo'}
    ]
    a2_raw_list = [
        {'file': 'rw61xw_raw_cpu1_a2.bin',                      'array_name': 'fw_cpu1'},
        {'file': 'rw61xn_raw_cpu2_ble_a2.bin',                  'array_name': 'fw_cpu2_ble'},
        {'file': 'rw61xn_combo_raw_cpu2_ble_15_4_combo_a2.bin', 'array_name': 'fw_cpu2_combo'}
    ]

    if (chip_revision == 'A2'):
        binlist = a2_raw_list
    elif (chip_revision == 'A1'):
        binlist = a1_raw_list
    else:
        return
    dest_dir=conn_fwloader_dir+'/'+chip_revision
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)
     # SB3 format built for A0
    for i in range(0,3):
        #print(binlist[i]['file'], binlist[i]['array_name'])
        bin2c_file(binlist[i]['file'],  binlist[i]['array_name'],  dest_dir)



def main():
    parser = argparse.ArgumentParser(description='Bin2C Generator')
    parser.add_argument('in_path', help="Directory to fw_bin containing binaries.")
    parser.add_argument('out_dir', nargs='?')
    parser.add_argument('-v', '--verbose', action='store_true', default=False, help="Sets verbose mode")
    parser.add_argument('-t', '--type', nargs='?',  default='sb', help='generate SB3 version or raw version')
    parser.add_argument('-r', '--rev', default='all', help='generate for chip revisions A0, A1, A2 or all' )
    args = parser.parse_args()

    if args.type == 'sb':
        if args.rev == 'all':
            generate_sb_src(args.in_path, 'A1')
            generate_sb_src(args.in_path, 'A2')
        else:
            if args.rev == 'A1' or args.rev == 'A2':
                generate_sb_src(args.in_path, args.rev, args.verbose)
    elif args.type == 'raw':
        if args.rev == 'all':
            generate_raw_src(args.in_path, 'A1')
            generate_raw_src(args.in_path, 'A2')
        else:
            if args.rev == 'A1' or args.rev == 'A2':
                generate_raw_src(args.in_path, args.rev, args.verbose)
            else:
                print("error wrong chip revision argument must be in A0, A1, A2, or all")
    else:
        print("error wrong type argument")


if __name__ == '__main__':
    main()




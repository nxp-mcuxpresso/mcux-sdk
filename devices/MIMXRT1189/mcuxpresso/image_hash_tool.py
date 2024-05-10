"""
Copyright 2022 NXP
All rights reserved.

SPDX-License-Identifier: BSD-3-Clause
"""

 
from collections import namedtuple
import hashlib
import logging
import re
import argparse
import subprocess
import os
import sys
import traceback



def parse_elf_sections(file):
    sections = {}

    Section = namedtuple('Section', ['idx', 'name', 'size', 'vma', 'lma', 'offset', 'align', 'flags'])

    objdump = subprocess.check_output(['arm-none-eabi-objdump', '-h', file])
    objdump = objdump.decode('utf-8')

    section_re = re.compile(r'(?P<idx>[0-9]+)\s'
                            r'(?P<name>\.\S+)\s*'
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

        sections[sec_dict['idx']] = Section(**sec_dict)

        logging.debug(sections[sec_dict['idx']])

    return sections

def get_section_by_name(sections, name):
    for _, section in sections.items():
        logging.debug("Section: {} {} {:08x} {:08x}".format(section.name, section.flags, section.lma, section.size))
        if name == section.name:
            logging.info("Section name={} LMA={:08x} Size={:08x}".format(section.name, section.lma, section.size))
            return section
    return None

def joinit(iterable, delimiter):
    for el in iter(iterable):
        yield delimiter
        yield el

def compute_hash(args):

    elf_file_name = args.in_file
    bin_file_name = elf_file_name + '_temp.bin'

    hasher = hashlib.new(args.hash_algorithm)

    try:
        out = subprocess.check_output(['arm-none-eabi-objcopy', '-O', 'binary', *joinit(args.exclude_section, '-R'), elf_file_name, bin_file_name])
        logging.debug(out.decode('utf-8'))

        with open(bin_file_name, 'rb') as afile:
            while True:
                buf = afile.read(1024)
                if not buf:
                    break
                hasher.update(buf)
    finally:
        if (os.path.exists(bin_file_name)):
            os.remove(bin_file_name)
    logging.info(hasher.hexdigest())
    return hasher

def update_elf(args, hasher):

    hash_size = args.out_len if args.out_len else hasher.digest_size
    pad_size = hash_size - hasher.digest_size if hash_size > hasher.digest_size else 0
    hash_data = hasher.digest() + bytes([args.out_padding] * pad_size)

    sect = get_section_by_name(parse_elf_sections(args.out_file), args.out_section)
    if not sect:
        msg = 'Requested section {} not found!'.format(args.out_section)
        logging.error(msg)
        raise SystemExit()

    with open(args.out_file, 'r+b') as elf_file:
        elf_file.seek(sect.offset + args.out_offset)
        old_data = elf_file.read(hash_size)
        elf_file.seek(sect.offset + args.out_offset)
        elf_file.write(hash_data)
        logging.info('Updating hash [{}] -> [{}]'.format(old_data.hex(), hash_data.hex()))

def auto_int(x):
    return int(x, 0)

parser = argparse.ArgumentParser(description='Image hash tool')
parser.add_argument('in_file', help="ELF file to be post-processed: generating hash and patching value in file.")
parser.add_argument('out_file', nargs='?')
parser.add_argument('-a', '--hash_algorithm', required=True, choices=list(hashlib.algorithms_available), help="Hash algorithm")
parser.add_argument('-x', '--exclude_section', action='append', default=[], help="Exclude the named section when calculating the image hash")
parser.add_argument('-s', '--out_section', required=True, help="Output section name. Used in conjunction with -o option to specify the location <section> + <offset> where the computed hash value will be inserted.")
parser.add_argument('-o', '--out_offset', required=True, type=auto_int, help="Output offset relative to the section start. Used in conjunction with -s option to specify the location <section> + <offset> where the computed hash value will be inserted.")
parser.add_argument('-l', '--out_len', required=False, type=auto_int, help="Output length. Optional output length, used in conjunction with -p option if the output location needs to be padded beyond the natural length of the hash code algorithm.")
parser.add_argument('-p', '--out_padding', required=False, type=auto_int, default=0xff, help="Output padding value. Optional padding byte value, used in conjunction with -l option if the output location needs to be padded beyond the natural length of the hash code algorithm.")
parser.add_argument('-v', '--verbose',  help='increase output verbosity', action='store_true')
args = parser.parse_args()

logger = logging.getLogger(__name__)
logging.basicConfig(format='%(message)s', level=logging.INFO if args.verbose else logging.WARN)

if args.out_file is None:
    args.out_file = args.in_file

try:
	update_elf(args, compute_hash(args))
except Exception as e:
	logging.error(traceback.format_exc())
	sys.exit(1)

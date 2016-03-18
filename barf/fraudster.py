#!/usr/bin/env python

import argparse
import sys

from fasta import parser as fastaParser

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input', type=argparse.FileType('rb'), 
                        default=sys.stdin)
    parser.add_argument('--output', type=argparse.FileType('wb'),
                        default=sys.stdout)
    args = parser.parse_args()

    for record in fastaParser(args.input):
        args.output.write('>{0}\n{1}\n'.format(record.name, record.sequence))
    # add a phony read
    args.output.write('>BAD\nATGGG\n')

if __name__ == '__main__':
    main()

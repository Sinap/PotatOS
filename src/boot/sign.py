#!/usr/env python
from __future__ import print_function
import os
import sys


def main():
    boot = sys.argv[1]
    if not os.path.exists(boot):
        print('File %s does not exist' % boot, file=sys.stderr)
        exit(1)

    with open(boot, 'rb') as f:
        buff = f.read()
        buff_len = len(buff)
        if buff_len > 510:
            print('Boot block to large: %d bytes (max 510)' % buff_len,
                  file=sys.stderr)
            exit(1)
        buff += "\0" * (510 - buff_len)
        buff += "\x55\xAA"

    with open(boot, 'wb') as f:
        f.write(buff)

if __name__ == '__main__':
    main()

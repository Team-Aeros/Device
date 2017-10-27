#!/usr/bin/env python3

import subprocess
import sys
import re

SCRIPT_VERSION = '1.0.0'


def get_target():
    if len(sys.argv) > 2:
        print('=> Fatal error: invalid number of arguments')
        sys.exit(-1)
    elif len(sys.argv) < 2:
        return 'device'

    if not re.match(r'^[a-zA-Z0-9]*$', sys.argv[1]):
        print('=> Fatal error: invalid target name')
        sys.exit(-1)

    return sys.argv[1]


def run():
    print(':: Code uploader')
    print('Copyright: Team Aeros\nVersion:', SCRIPT_VERSION)

    while True:
        print('=> Please enter the desired port:', end=' ')
        inpt = input()

        if not re.match(r'^[a-zA-Z/0-9]*$', inpt):
            print('=> Error: Invalid input. Try again')
            continue

        break

    args = ('avrdude -F -V -c arduino -p atmega328p -P ' + inpt + ' -b 115200 -U flash:w:' + get_target() + '.hex').split()

    try:
        subprocess.run(args)
    except subprocess.CalledProcessError as e:
        print('=> Error: Could not execute command')


if __name__ == '__main__':
    run()

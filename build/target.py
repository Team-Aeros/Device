#!/usr/bin/env python3

from shutil import copyfile

import re
import sys

SCRIPT_VERSION = '1.0.0'
SOURCE = '../src/modules/sensor.h'
BAK_DESTINATION = '../src/modules/sensor.h-bak'

MODES = ['light', 'temperature']


def run():
    print(':: Compilation options')
    print('Copyright: Team Aeros\nVersion:', SCRIPT_VERSION)

    inpt = None

    while True:
        print('=> Please specify a sensor mode [{0}]:'.format('/'.join(MODES)), end=' ')
        inpt = input()

        if inpt.lower() not in MODES:
            print('=> Error: sensor mode not recognized')
        else:
            break

    try:
        copyfile(SOURCE, BAK_DESTINATION)
        print('=> File {0} copied to {1}'.format(SOURCE, BAK_DESTINATION))
    except IOError as e:
        print('=> Error: unable to create backup file')
        return -1

    with open(SOURCE, 'r+') as file:
        buffer = []
        found = False

        for line in file:
            if '#define SENSOR_MODE' in line and not found:
                buffer.append('#define SENSOR_MODE {0}'.format(0 if inpt.lower() == 'light' else 1) + \
                                ' // 0 = light_sensor, 1 = temp_sensor \n')

                print('=> Line found')
                found = True
            else:
                buffer.append(line)

        if not found:
            print('=> Error: could not find SENSOR_MODE constant')
            return -1

        file.seek(0)
        file.truncate(0)

        for line in buffer:
            file.write(line)


if __name__ == '__main__':
    run()

#!/usr/bin/env python3

import os

if __name__ == '__main__':
    duplicates = {}  # name : [size, filepath]

    root_dir = '/Users/karsten/Downloads'

    for subdir, dirs, files in os.walk(root_dir):
        for f in files:
            filepath = os.path.join(root_dir, subdir, f)
            filesize = os.stat(filepath).st_size
            if f not in duplicates:
                #print('adding', filepath)
                duplicates[f] = [[filesize, filepath]]
            else:
                available_files = duplicates[f]
                to_be_added = False
                for ff in available_files:
                    if ff[0] == filesize:
                        print('duplicates found:')
                        print('a)', filepath)
                        print('b)', ff[1])
                    else:
                        to_be_added = True
                        break
                if to_be_added:
                    duplicates[f].append([filesize, filepath])

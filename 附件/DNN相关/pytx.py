#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import os.path

pathh = "/home/zzzing/桌面/jpgs"

for filenames in os.walk(pathh):
    filenames = list(filenames)
    filenames = filenames[2]
    for filename in filenames:
        print(filename)
        with open ("/home/zzzing/桌面/train.txt",'a') as f:
            f.write(pathh+'/'+filename+'\n')

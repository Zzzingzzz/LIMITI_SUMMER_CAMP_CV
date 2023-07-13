#!/usr/bin/env python
# -*- coding: utf-8 -*-  
#此脚本需要执行两次，在91行train_number执行一次，test_number执行一次
import xml.etree.ElementTree as ET
import pickle
import os
from os import listdir, getcwd
from os.path import join

sets = []
classes = ['silver']


picture_dir = "/home/zzzing/桌面/jpgs"
labels_dir = "/home/zzzing/桌面/jpgs/txt"
xml_dir = "/home/zzzing/桌面/jpgs/xml"
pic_file_config = "/home/zzzing/桌面/train.txt"


#z
# 将ROI的坐标转换为yolo需要的坐标  
# size是图片的w和h  
# box里保存的是ROI的坐标（x，y的最大值和最小值）  
# 返回值为ROI中心点相对于图片大小的比例坐标，和ROI的w、h相对于图片大小的比例  
def convert(size, box):
    dw = 1./(size[0])
    dh = 1./(size[1])
    x = (box[0] + box[1])/2.0 - 1
    y = (box[2] + box[3])/2.0 - 1
    w = box[1] - box[0]
    h = box[3] - box[2]
    x = x*dw
    w = w*dw
    y = y*dh
    h = h*dh
    return (x,y,w,h)

#对于单个xml的处理
def convert_annotation(image_add):
    #image_add进来的是带地址的.jpg
    image_add = os.path.split(image_add)[1] #截取文件名带后缀
    image_add = image_add[0:image_add.find('.',1)] #删除后缀，现在只有文件名没有后缀
    in_file = open(xml_dir+ '/' + image_add+".xml",encoding='utf-8')

    print('now write to:'+ labels_dir + '/%s.txt'%(image_add))
    out_file = open(labels_dir + '/%s.txt'%(image_add), 'w')

    tree=ET.parse(in_file)
    root = tree.getroot()

    #f = open("F:\Traintest1\\"+ image_add+".xml")
    #xml_text = f.read()
    #root = ET.fromstring(xml_text)
    #f.close()

    #加入我的预处理<name>代码：
   # for obj in root.findall("object"):
        #obj.append("number") = obj.find('name').text
        #obj.find('name').text = "box"
       # print(obj.find('name').text)
    #tree.write('/home/xushuo/Test/Annotations/'+ image_add + '.xml')

    size = root.find('size')
    # <size>
    #     <width>500</width>
    #     <height>333</height>
    #     <depth>3</depth>
    # </size>
    w = int(size.find('width').text)
    h = int(size.find('height').text)

    #在一个XML中每个Object的迭代
    for obj in root.iter('object'):
        #iter()方法可以递归遍历元素/树的所有子元素
        '''
        <object>
        <name>car</name>
        <pose>Unspecified</pose>
        <truncated>1</truncated>
        <difficult>0</difficult>
        <bndbox>
            <xmin>141</xmin>
            <ymin>50</ymin>
            <xmax>500</xmax>
            <ymax>330</ymax>
        </bndbox>
        </object>
        '''
        difficult = obj.find('difficult').text
        #找到所有的椅子
        cls = obj.find('name').text
        #如果训练标签中的品种不在程序预定品种，或者difficult = 1，跳过此object
        if cls not in classes or int(difficult)==1:
            continue
        #cls_id 只等于1
        cls_id = classes.index(cls)
        xmlbox = obj.find('bndbox')
        #b是每个Object中，一个bndbox上下左右像素的元组
        b = (float(xmlbox.find('xmin').text), float(xmlbox.find('xmax').text), float(xmlbox.find('ymin').text), float(xmlbox.find('ymax').text))
        bb = convert((w,h), b)
        out_file.write(str(cls_id) + " " + " ".join([str(a) for a in bb]) + '\n')


if not os.path.exists(labels_dir):
    os.makedirs(labels_dir)
image_adds = open(pic_file_config)
for image_add in image_adds:
    image_add = image_add.strip()
    print (image_add)
    convert_annotation(image_add)


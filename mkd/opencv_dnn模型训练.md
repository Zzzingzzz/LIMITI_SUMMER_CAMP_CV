##  数据集及训练

+ ###  图片拍摄及标数据集

  使用labelImg进行数据集标注，保存标注后检查每个图片对应的txt文件是否有数据

  1. 尽可能拍摄被识别物体的所有情况（不同姿位，不同光线，不同遮挡），并在图片中放置与被识别物体相似的物体，使dnn识别更加精准
  2. 标数据集时若被识别物体被遮挡严重时可以不标
  3. 数据集按日期分类图片，并用日期+图片数区分图片，以免出现命名混乱等问题

+ ###  训练

  + ####  生成txt

    1. 将所有图片放置在一个文件夹下，所有xml文件放置于另一个文件夹下

    2. 建立txt存放文件夹

    3. 修改pytx.py及pycreat.py

       ```
       将 pytx.py 中的 pathh 修改为图片所在文件夹的路径
       可将 pytx.py 中的 train.txt 修改为 train+训练次数.txt（或者你自己喜欢的名称），该txt会保存pytx.py找到的所有图片的路径
       将 pycreat.py 中的 picture_dir 修改为图片所在文件夹的路径
       	                                   labels_dir 修改为生成的 txt 所在文件夹的路径
       	                                   xml_dir 修改为 xml 所在文件夹的路径
       	                                   pic_file_config 中 train.txt 的名称与 pytx.py 保持一致
       	                                   classes 修改为标签分类名称
       ```

    4. 执行 pytx.py : python3 pytx.py

    5. 执行 pycreat.py : python3 pycreat.py

    6. 将生成的 txt 与图片放在同一文件夹下

    7. 将 txt 与图片所在文件夹==压缩==并上传FileZilla云盘上传至云盘，注意要放在CloudData文件下（若不压缩就慢慢等时间吧）

  + ####  训练

    1. 在微信小程序==智星云服务==上租服务器

    2. 在VNC上登陆服务器：输入VNC图形桌面链接；输入密码

    3. 在服务器中，将txt与图片及MYyolo.rar从云盘上下载下来

    4. 解压MYyolo.rar

       ```
       sudo apt-get install rar
       rar x MYyolo.rar
       ```

    5. 将存放 txt 和图片的文件夹改名为 picture （否则 14 步的路径需要更改）

    6. 克隆 darknet`git clone https://github.com/AlexeyAB/darknet/`

    7. 修改Makefile

       ```
       cd darknet 
       gedit Makefile 
       将 GPU、CUDNN、CUDNN_HALF、OPENCV 修改为 1 并保存
       ```

    8. 编译并发现报错 : `make -j16` （有报错）

    9. 更新并安装依赖

       ```
       sudo apt-get update 
       sudo apt install libopencv-dev
       ```

    10. 编译 : `make -j16`

    11. 修改MYyolo里yolo-fastest.names : 修改标签分类名称

    12. 修改MYyolo里yolo-fastest-xl.cfg

        ```
        修改 net 中的 width、height : width = 416 height = 416 （按照实际需求进行修改，此处数值仅为示范）
        修改 net 中的 hue : hue 用于调色调，可直接给 0
        修改 net 中的 batch : 使用 nvidia-smi 查看显存，batch 所给值塞满显存 （batch 越大下降越稳定,batch=256）
        在yolo-fastest-xl.cfg里搜索yolo（有两处yolo模块）
        	将 yolo 中的 classes 修改为实际标签分类数量，并将对应yolo上方的convolutional 中的 filters 修改为 (classes + 5) * 3
        ```

    13. 修改MYyolo里yolo-fastest.data : 将 classes 修改为实际标签分类数量

    14. 在新终端执行`find /root/picture -name *.jpg > train.txt`生成train.txt

    15. 在主目录下创建backup文件夹，生成的权重会生成在此文件夹下

    16. 进入darknet文件夹开始训练

        ```
        cd darknet
        ./darknet detector train ../yolo-fastest.data ../yolo-fastest-xl.cfg 
        ```

    17. 当运行图表中loss下降至0.3以下即可根据实际情况收菜。~~一般0.1以下效果好~~

    18. 将`yolo-fastest-xl.weights`、`yolo-fastest-xl.cfg`、`yolo-fastest.names`保存至云盘，并从云盘中下载，训练结束






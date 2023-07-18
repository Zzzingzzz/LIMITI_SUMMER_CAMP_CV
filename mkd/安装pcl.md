#  简介

pcl是常见的C++点云库，以下介绍pcl的安装方法

##  安装pcl库的一些依赖

```
sudo apt-get update  
sudo apt-get install git build-essential linux-libc-dev
sudo apt-get install cmake cmake-gui
sudo apt-get install libusb-1.0-0-dev libusb-dev libudev-dev
sudo apt-get install mpi-default-dev openmpi-bin openmpi-common 
sudo apt-get install libflann1.8 libflann-dev
sudo apt-get install libeigen3-dev
sudo apt-get install libboost-all-dev
sudo apt-get install libvtk5.10-qt4 libvtk5.10 libvtk5-dev
sudo apt-get install libqhull* libgtest-dev
sudo apt-get install freeglut3-dev pkg-config
sudo apt-get install libxmu-dev libxi-dev
sudo apt-get install mono-complete
sudo apt-get install qt-sdk openjdk-8-jdk openjdk-8-jre
```

可能会存在一些过期或无效版本，可根据终端提示根据自己情况下载

##  从github 下载pcl

```
git clone https://github.com/PointCloudLibrary/pcl.git 
```

##  编译安装

推荐使用cmake-gui编译，可自己选择需要编译的项目进行编译

点击Configure配置 和 Generate生成后，即可完成配置

进入build文件夹编译安装

```
cd build
make -j16
sudo make install
```

##  测试安装结果

切换到pcl安装目录，找一个点云pcd文件，输入以下代码查看

```
pcl_viewer model.pcd
```

若正常显示点云文件，即表示安装成功

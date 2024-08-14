#  夏令营培训5——PCL

PCL库(全称[Point Cloud Library](https://pointclouds.org/))，是一个重要的点云处理库，而点云又是雷达等常用的数据格式，故在此介绍此库。

安装PCL请见：[安装pcl.md](./安装pcl.md)

##  1. 任务1——PCL数据类型和可视化

学习了解PCL的PointCloud和几个主要的数据类型（主要是PointXYZ和PointXYZRGB）

读取PCL源码中随便一个PCD文件（或在附近中的five_people.pcd），使用`boost::shared_ptr<pcl::visualization::PCLVIsualizer>`将点云进行可视化

##  2. 任务2——点云聚类算法

聚类是点云中常见的算法，主要用以将离散的点云划分为不同的物体

学习kmeans和dbscan等几种聚类算法，了解其原理并能调用PCL库中有关函数进行点云聚类

## 3. 任务3——点云滤波

滤波也是点云操作中常用的算法，可以减少不必要的点云噪点或下采样减少点云数据

见[PCL——点云滤波](https://blog.csdn.net/sinat_41837954/article/details/100306836?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522172362067416800213028105%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=172362067416800213028105&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-100306836-null-null.142^v100^pc_search_result_base4&utm_term=pcl%E7%82%B9%E4%BA%91%E6%BB%A4%E6%B3%A2&spm=1018.2226.3001.4187)

##  *3. 任务3——查阅SLAM

SLAM是视觉、雷达等场景建模、机器人定位的一类重要算法

在此仅作介绍，请自行查阅SLAM大致的功能、算法

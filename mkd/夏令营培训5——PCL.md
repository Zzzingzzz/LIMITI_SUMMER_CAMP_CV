#  夏令营培训5——PCL

PCL库(全称[Point Cloud Library](https://pointclouds.org/))，是一个重要的点云处理库，而点云又是雷达等常用的数据格式，故在此介绍此库。

##  1. 任务1——PCL数据类型和可视化

学习了解PCL的PointCloud和几个主要的数据类型（主要是PointXYZ和PointXYZRGB）

读取PCL源码中随便一个PCD文件（或在附近中的five_people.pcd），使用`boost::shared_ptr<pcl::visualization::PCLVIsualizer>`将点云进行可视化

##  2. 任务2——点云聚类算法

聚类是点云中常见的算法，主要用以将离散的点云划分为不同的物体

学习kmeans和dbscan等几种聚类算法，了解其原理并能调用PCL库中有关函数进行点云聚类



##  *3. 任务3——查阅SLAM

SLAM是视觉、雷达等场景建模、机器人定位的一类重要算法

在此仅作介绍，请自行查阅SLAM大致的功能、算法

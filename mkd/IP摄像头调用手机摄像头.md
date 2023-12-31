#  IP摄像头调用手机摄像头

调用usb摄像头代码为

````c++
VideoCapture cap(0); // 调用系统0号usb摄像头
````

如果要使用手机摄像头，请安装**IP摄像头**（安卓手机可以在附件中寻找**IP摄像头.apk**，苹果手机可以在App Store中查询**IP摄像头**下载）

下为安卓端IP摄像头示例：

0. 将手机和电脑连接到同一个WIFI下，IP摄像头依靠WIFI传输画面

1. 进入IP摄像头主界面

![IP摄像头1](./images/IP摄像头1.jpg)

2. 进入IP摄像头设置界面，下滑找到密码

![IP摄像头2](./images/IP摄像头2.jpg)

3. 设置密码为空，并确定

![IP摄像头3](./images/IP摄像头3.jpg)

4. 回到主界面，点击打开IP摄像头服务器，并记录下局域网的IP地址

​		如我的局域网IP地址为：`http://192.168.88.35:8081`

![IP摄像头4](./images/IP摄像头4.jpg)

5. 在opencv调用的代码中，将原本调用usb的代码

````C++
VideoCapture cap(0); // 调用系统0号usb摄像头
````

​		更改为

````C++
VideoCapture cap("http://192.168.88.35:8081"); // 调用对应IP的摄像头
````

​		其余代码与调用usb的代码相同，即可完成IP摄像头调用

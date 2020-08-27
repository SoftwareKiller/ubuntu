ubuntu安装asio

```sh
 sudo apt-get install -y libasio-dev
```



centos 7.x安装

```C++
# CentOS 7.x在root权限下执行下列命令安装ASIO:
yum install -y epel-release
yum install -y asio-devel
```

因为使用系统自带安装包，安装的asio库版本比较古老，一些特性玩不到，或者和boost牵连不清
后面的案例都会使用asio-1.18.0版本，在主目录下也提供出来了，编译时只需将该版本的代码拷贝到案例的根目录即可

示例：
```sh
cp asio-1.18.0 http
cd http/build
cmake ..
```
依照上面示例，即可完成编译，对代码进行使用

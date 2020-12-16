使用时将上一层目录的asio-1.18.0库放入opt文件即可编译

示例：
```sh
cp -r ../asio-1.18.0 opt
cd build
cmake ..
```
build文件里的src有一个etc文件，为启动配置

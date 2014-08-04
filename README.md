# 目录结构说明

***

### server
===

服务器端程序(主要在ubuntu10.10上测试, linux平台编译，运行都是没问题的)


`编译:`
    
    cd src
    make distclean 
    make && make install

    

`运行:`
    
    php mysql.php  (创建数据库和表格，及插入调试用户及数据，脚本在目录 debug_script)
    ./redis-server --loglevel verbose (--loglevel verbose 表示带调试信息，默认端口为6379)
    python fakeClient.py (模拟真实用户及智能数据节点，可根据实际情况修改)
    
    


### android_client  
===
andriod平台的客户端，使用eclipse打开即可。   
假如没有android开发环境， 可直接下载最新apk安装即可 : http://git.oschina.net/xmeter/My-smart-home/blob/master/android_client/bin/MyNode.apk

### restful  
===
提供简单的restful api (get put post delete)，可通过http协议访问，返回json数据结果集


### tools 
===
提供些由于网络问题不好下的，软件包及调试工具

PS：感觉放这里不怎么厚道，于是决定放网盘的说

PS2.0: 我也这么认为，我错了，每次下载代码都花掉太多时间

### iOS_client
===
iOS平台的客户端，使用xcode5或以上打开即可。


### debug_script
===
mysql数据库初始化，测试用例的一些脚本

**所有脚本都是和服务器相关，所以脚本移动到server/mytest，这里的将不再更新维护**


### www
===
http服务器代码，简单的web控制，有任何问题,或者要添加测试用户等，随时联系:

<liyongming1982@163.com> <ckrissun@gmail.com>  <896640547@qq.com>

PS:http服务器方面在Web分支上开发，有问题和建议请提交Issue

### webhook
代码自动部署，持续集成
     

### hardware
===
硬件ardunio以及相关传感器的demo。(LM35，MQ2 MQ7 , W5100等)
     
* [硬件介绍](http://git.oschina.net/xmeter/My-smart-home/wikis/%E7%A1%AC%E4%BB%B6%E9%83%A8%E5%88%86%E4%BB%8B%E7%BB%8D)
       
***

> 更详细的说明，请移步 [WiKi](http://git.oschina.net/xmeter/My-smart-home/wikis/Home)

> 联系方式：http://git.oschina.net/xmeter/My-smart-home/wikis/%E8%81%94%E7%B3%BB%E6%96%B9%E5%BC%8F

> 希望有新的小伙伴加入！

> 你还可以看看[自我介绍](http://git.oschina.net/xmeter/My-smart-home/issues/24)

***

> liyongming1982@163.com _管理员_

> 服务器 硬件 Android Client

***

> ckrissun@gmail.com _管理员_

> 服务器 协议 硬件

***

> 896640547@qq.com _管理员_

> 负责Web及API方面

***

> siz@sonwa.cn

> iPhone Client

***

> david_lxh@aliyun.com

> 特别感谢fireman,把Web服务移植到树莓派 (并写下文档供后来者参考)

***

> raythandong@gmail.com

> 硬件

***

> 604217454@qq.com

> iPhone Client

***

> liduanjun@126.com

> 硬件及Web

## 感谢

   * 感谢xiangjm资助我200元人民币购买3D打印机
   * 感谢我老婆这个月多给了我点零花钱
   * 感谢3D淘宝店老板便宜了50元钱 http://3dprinter-diy.taobao.com/?spm=2013.1.0.0.donECP
   * ......
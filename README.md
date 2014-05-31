##目录结构说明
===

#### server
===

服务器端程序(主要在ubuntu10.10上测试, linux平台编译，运行都是没问题的)


`编译:`
    
    cd src
    make distclean
    make    
    

`运行:`
    
    php mysql.php  (创建数据库和表格，及插入调试用户及数据，脚本在目录 debug_script)
    ./redis-server --loglevel verbose (--loglevel verbose 表示带调试信息，默认端口为6379)
    python fakeClient.py (模拟真实用户及智能数据节点，可根据实际情况修改)
    
    


#### android_client  
===
andriod平台的客户端，使用eclipse打开即可。



#### debug_script
===
mysql数据库初始化，测试用例的一些脚本
所有脚本都是和服务器相关，所以脚本移动到 server/mytest ，这里的将不再更新维护。


#### www
===
http服务器代码，简单的web控制，有任何问题,或者要添加测试用户等，随时联系:

<liyongming1982@163.com>
     

#### hardware
===
硬件ardunio以及相关传感器的demo。(LM35，MQ2 MQ7 , W5100等)
     
* [硬件介绍](http://git.oschina.net/xmeter/My-smart-home/wikis/%E7%A1%AC%E4%BB%B6%E9%83%A8%E5%88%86%E4%BB%8B%E7%BB%8D)
       
===
更详细的说明，麻烦移步 [WiKi](http://git.oschina.net/xmeter/My-smart-home/wikis/pages)

希望有新的小伙伴加入， `随时联系:`
===
    <liyongming1982@163.com>
    <ckrissun@gmail.com>
    <siz@sonwa.cn>
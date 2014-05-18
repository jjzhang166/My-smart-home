目录结构说明
1      server
         服务器端程序(主要在ubuntu10.10上测试, linux 平台编译，运行都是没问题的)
         怎么编译：
         cd  src
          make    
         怎么运行：
          php mysql.php  (创建数据库和表格，及插入调试用户及数据，脚本在目录 debug_script )
          ./redis-server --loglevel verbose    (--loglevel verbose 表示带调试信息，默认端口为6379)
          python fakeClient.py  (模拟真实用户及智能数据节点，可根据实际情况修改)
2
      android_client  
       为andriod平台的客户端，用eclipse打开即可。

3
     debug_script
     为mysql数据库初始话，测试用例的一些脚本

4
     www
     http服务器用的代码，简单的web控制 

     有任何问题,或者要添加测试用户等  :  随时联系 liyongming1982@163.com
     
     
   硬件介绍：
   
   http://git.oschina.net/xmeter/My-smart-home/wikis/%E7%A1%AC%E4%BB%B6%E9%83%A8%E5%88%86%E4%BB%8B%E7%BB%8D
   
   
     
   更详细的说明，麻烦移步：

    http://git.oschina.net/xmeter/My-smart-home/wikis/pages
    

    希望有新的小伙伴加入，随时联系： liyongming1982@163.com
# 分支说明

***

此分支基于master，用于服务器端开发

包括webhook、www等内容

和master分支分离，防止误操作

有问题请提交Issue

# www相关

***

## 环境需求

* php5.3及以上

* PDO扩展和MySQLi扩展

* MySQL

## 安装方法
    
    cd www
	cd install
	php install.php
    
## 升级方式

### 自动升级

制作中

### 手动升级

如果没有大的改动（涉及到数据库等），直接上传新文件覆盖原来的文件即可

如果有，请先上传新文件覆盖原来的文件，之后到www/update目录下寻找名称为：
**update_更新日期.php**
的文件，上传到自己的服务器上面后以cli方式运行即可

**注意：升级完成请及时删除升级文件**

## 可能涉及到的目录

* www

* server/mytest （注：本目录的mysql.php不再维护，而是转至www/install/install.php）
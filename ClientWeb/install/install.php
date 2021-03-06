<?php
/*
 * 安装文件
 * 建立MySQL数据库
*/
//抑制所有错误信息
@error_reporting(E_ALL &~ E_NOTICE);
@set_time_limit(0);
date_default_timezone_set('PRC');
if (!isset($_SERVER['PHP_SELF']) || empty($_SERVER['PHP_SELF'])) $_SERVER['PHP_SELF']=$_SERVER['SCRIPT_NAME'];
header('Content-type:text/html; charset=utf-8'); //强制语言
//判断是否为CLI模式
if (strtolower(php_sapi_name())!=='cli') exit('请在cli模式下安装');
//开始连接MySQL
echo '---------------------------',"\n";
echo 'My Smart Home 正在安装，请稍候',"\n";
echo '---------------------------',"\n";
echo '尝试连接到MySQL数据库...',"\n";
require('../data/db.inc.php');
require('../include/common.func.php');
if (!defined(ENKEY)) define('ENKEY',randstr(10));
@list($dbhost,$dbport)=explode(':',SQLHOST);
!$dbport && $dbport=3306;
$link=mysqli_init();
mysqli_real_connect($link,$dbhost,SQLUSER,SQLPWD,FALSE,$dbport);
mysqli_errno($link)!=0 && exit('错误警告： 链接到MySQL发生错误');
//处理错误，成功连接则选择数据库
if (!$link) exit('连接数据库失败，可能数据库密码不对或数据库服务器出错！');
mysqli_query($link,"SET character_set_connection=utf8,character_set_results=utf8,character_set_client=binary");
mysqli_query($link,"SET sql_mode=''");
echo '连接数据库成功！',"\n";
if (mysqli_query($link,'CREATE DATEBASE '.SQLNAME)) echo '建立数据库 ',SQLNAME,' 成功',"\n";
else echo '建立数据库 ',SQLNAME,' 失败，可能数据库已经存在',"\n";
if (SQLNAME && !@mysqli_select_db($link,SQLNAME)) exit('无法使用数据库');
//开始安装
require('sql.php');
echo '---------------------------',"\n";
echo '开始建立数据表',"\n";
echo '---------------------------',"\n";
foreach ($sql as $key=>$val) {
	mysqli_query($link,'DROP TABLE IF EXISTS '.DBPREFIX.$key; //如果表存在则先drop掉
	if (mysqli_query($link,str_replace('#@__',DBPREFIX,$val))) echo '建立数据表 ',$val,' 成功',"\n"; //建表
	else echo '建立数据表 ',$val,' 失败',"\n";
}
echo '---------------------------',"\n";
echo '建立数据表成功',"\n";
echo '---------------------------',"\n";
//初始化管理员信息
do {
	if (isset($user)) echo '格式不正确！',"\n";
	echo '请设置管理员用户名（数字/字母/下划线，20字以内）：';
	$user=trim(fgets(STDIN));
} while (!preg_match('/^[A-Za-z0-9_]+$/',$user) && strlen($user)>20);
do {
	if (isset($email)) echo '请输入正确的邮箱！',"\n";
	echo '请输入您的邮箱：';
	$email=trim(fgets(STDIN));
} while (!preg_match('/^[_.0-9a-z-]+@([0-9a-z][0-9a-z-]+.)+[a-z]{2,3}$/',$email));
do {
	if (isset($pwd1)) echo '两次输入的密码不一致！',"\n";
	echo '请设置管理员密码：';
	$pwd1=trim(fgets(STDIN));
	echo '请再输一次：';
	$pwd2=trim(fgets(STDIN));
} while ($pwd1!=$pwd2);
$pwd=pwdcode($pwd1);
echo '初始化管理员数据，请稍候',"\n";
mysqli_query($link,"INSERT INTO `".DBPREFIX."user` (`id`,`type`,`name`,`password`,`email`,`isAdmin`) VALUES ('1','1','$user','".pwdcode($pwd)."','$email','1')");
echo '---------------------------',"\n";
echo '初始化管理员数据成功',"\n";
echo '---------------------------',"\n";
echo '初始化基本数据，请稍候',"\n";
echo '---------------------------',"\n";
//插入初始数据
foreach ($sqldata as $val) {
	mysqli_query($link,str_replace('#@__',DBPREFIX,$val));
}
echo '初始化数据完成',"\n";
echo '---------------------------',"\n";
echo '写入配置文件，请稍候',"\n";
echo '---------------------------',"\n";
$writes=array('ENKEY','SQLHOST','SQLUSER','SQLPWD','SQLNAME','NOSQLHOST','NOSQLPORT','DBPREFIX');
$f=file_get_contents('db.inc.php');
foreach ($writes as $val) {
$f=str_replace('#'.$val.'#',constant($val),$f);
}
echo 'Write File 
echo '写入配置文件成功',"\n";
echo '---------------------------',"\n";
echo '安装成功."\n"';
?>
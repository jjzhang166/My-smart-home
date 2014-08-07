<?php
//  auther :  yongming.li
$con = mysql_connect("localhost","root","123456");
$i=0;
if (!$con)
{
  die('Could not connect: ' . mysql_error());
}

if (mysql_query("drop database mynode",$con))
{
  echo "drop mynode succssful \r\n";
}
else
{
  echo "Error drop mynode database: \r\n " . mysql_error();
}
if (mysql_query("create database  mynode",$con))
{
  echo "mynode Database created succssful \r\n";
}
else
{
  echo "Error creating database: \r\n " . mysql_error();
}

mysql_select_db("mynode", $con);
echo "drop tables  \r\n" ;
mysql_query("DROP TABLE node",$con);
mysql_query("DROP TABLE user",$con);
mysql_query("DROP TABLE emailmd5",$con);
echo "create tables \r\n" ;

mysql_query("CREATE  TABLE emailmd5  (email  VARCHAR(50) UNIQUE,saltmd5 VARCHAR(50))",$con);
$i=mysql_query("CREATE  TABLE node  (id bigint(10) AUTO_INCREMENT , userid VARCHAR(50) ,nodeid VARCHAR(50),command VARCHAR(50) , value VARCHAR(50), PRIMARY KEY(id) ,INDEX(userid) )",$con);
mysql_query("CREATE  TABLE user (id bigint(10) AUTO_INCREMENT , host VARCHAR(10),hostname VARCHAR(50),userid VARCHAR(50) ,name VARCHAR(50) UNIQUE,password VARCHAR(50),email VARCHAR(50), nickname VARCHAR(50) , PRIMARY KEY(id) ,INDEX(name),INDEX(email) )",$con);

// insert fake data
$arr=array("yongming","rex","fireman","root");
//$family=array("father","mother","brother","sister","son","daught");
$family=array("wife","son");
foreach ($arr as $value)
{
  $name=$value;
  echo "name is : ".$name."\r\n";
  $email=$name."@gmail.com";
  echo "email is : ".$email."\r\n";
  $str = sprintf("insert into user (host,hostname,userid,name,password,email,nickname)values('%s','%s','%s','%s','%s','%s','%s')","true",$name,md5($email),$name,$name,$email,$name);
   //echo "str is : \r\n".$str;
  $i=mysql_query($str,$con);
     if ($i)
     {
      echo "insert into host user succssful \r\n";
    }
    else
    {
      echo "Error insert into user: \r\n " . mysql_error();
    }
  
  foreach ($family as $value)
  {
     $familyname=$name.$value;
     $familyemail=$familyname."@163.com";
     $str = sprintf("insert into user (host,hostname,userid,name,password,email,nickname)values('%s','%s','%s','%s','%s','%s','%s')","false",$name,md5($email),$familyname,$familyname,$familyemail,$familyname);
     //echo "str is : \r\n".$str;
     $i = mysql_query($str,$con);
     if ($i)
     {
      echo "insert into family user succssful \r\n";
    }
    else
    {
      echo "Error insert into user: \r\n " . mysql_error();
    }
  }
  mysql_query(sprintf("insert into node (userid,nodeid,command,value)values('%s', 'tv','0','0')",md5($email)),$con);
  mysql_query(sprintf("insert into node (userid,nodeid,command,value)values('%s', 'light','0','0')",md5($email)),$con);
  mysql_query(sprintf("insert into node (userid,nodeid,command,value)values('%s', 'air','0','0')",md5($email)),$con);
  mysql_query(sprintf("insert into node (userid,nodeid,command,value)values('%s', 'temperature','0','0')",md5($email)),$con);
  mysql_query(sprintf("insert into emailmd5 (email,saltmd5)values('%s','%s')",$email,md5($email)),$con);
}
//  remember free resource
echo "close mysql connect \r\n" ;
mysql_close($con);

?>



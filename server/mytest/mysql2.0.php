<?php
//  auther :  yongming.li
$con = mysql_connect("localhost","root","123456");
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
echo "drop and create \r\n" ;
//mysql_query("DROP TABLE node",$con);
//mysql_query("DROP TABLE alluser",$con);
//mysql_query("DROP TABLE emailmd5",$con);

mysql_query("CREATE  TABLE emailmd5  (email  VARCHAR(50) UNIQUE,saltmd5 VARCHAR(50))",$con);
mysql_query("CREATE  TABLE node  (userid VARCHAR(50) ,nodeid VARCHAR(50),command VARCHAR(50) , value VARCHAR(50))",$con);
mysql_query("CREATE  TABLE alluser (host VARCHAR(10),hostname VARCHAR(50),userid VARCHAR(50) ,name VARCHAR(50) UNIQUE,password VARCHAR(50),email VARCHAR(50), nickname VARCHAR(50) )",$con);
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
  mysql_query(sprintf("insert into alluser values('%s','%s','%s', '%s','%s','%s')","true",$name,md5($email),$name,$name,$email),$con);
  foreach ($family as $value)
  {
     $familyname=$name.$value;
     $familyemail=$familyname."@163.com";
     mysql_query(sprintf("insert into alluser values('%s','%s','%s', '%s','%s','%s')","false",$name,md5($email),$familyname,$familyname,$familyemail),$con);
  }

  mysql_query(sprintf("insert into node values('%s', 'tv','0','0')",md5($email)),$con);
  mysql_query(sprintf("insert into node values('%s', 'light','0','0')",md5($email)),$con);
  mysql_query(sprintf("insert into node values('%s', 'air','0','0')",md5($email)),$con);
  mysql_query(sprintf("insert into node values('%s', 'temperature','0','0')",md5($email)),$con);

  mysql_query(sprintf("insert into emailmd5 values('%s','%s')",$email,md5($email)),$con);

}
//  remember free resource
echo "close mysql connect \r\n" ;
mysql_close($con);

?>



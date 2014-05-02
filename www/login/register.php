<?php
//  auther :  yongming.li

if($name == NULL || $password == NULL || $email==NULL || $userid==NULL)
{
   die(" sorry something cant be null ...");
}
$con = mysql_connect("localhost","root","123456");
mysql_select_db("mynode", $con);

//  check name and email
$sql = sprintf("select * from alluser where email='%s' or name='%s'",$email,$name);  
//echo "sql is : ".$sql."\r\n";
//echo "<p>";
$result = NULL;
if ($result=mysql_query($sql,$con))
{
  //echo " succssful \r\n";
}
else
{
  //die("Error : \r\n " . mysql_error());
}
if(mysql_num_rows($result)>0)
{
   die("you have registered , or the email has been used");
}


//  check userid
$sql = sprintf("select * from emailmd5 where email='%s' and saltmd5='%s'",$email,$userid);  
//echo "sql is : ".$sql."\r\n";
//echo "<p>";
$result = NULL;
if ($result=mysql_query($sql,$con))
{
  //echo " succssful \r\n";
}
else
{
  die("Error : " . mysql_error());
}
if(mysql_num_rows($result)==0)
{
   die("sorry wrong userid , check the email or generate the userid again");
}
$sql = sprintf("insert into alluser values('%s','%s','%s','%s')",$userid,$name,$password,$email);  
//echo "sql is : ".$sql;
if (mysql_query($sql,$con))
{
  //echo " succssful ";
}
else
{
  die("Error : " . mysql_error());
}
echo "you are so lucky , have registered successful";
mysql_close($con);
?>



<?php
//  auther :  yongming.li

if($email==NULL)
{
   die(" sorry email cant be null ...");
}
//$email = "liyongming1982@163.com";
$saltemail =$email;
//$saltemail =$email.rand();
//echo $saltemail;
echo "your email is : ".$email;
echo "<p>";
$userid = md5($saltemail);

$con = mysql_connect("localhost","root","123456");
mysql_select_db("mynode", $con);
$result = NULL;

$sql = sprintf("select * from alluser where email='%s'",$email);  
//echo "sql is : ".$sql."\r\n";

if ($result=mysql_query($sql,$con))
{
 // echo " succssful \r\n";
}
else
{
   die("Error : \r\n " . mysql_error());
}
if(mysql_num_rows($result)>0)
{
   die("sorry the email has been used");
}

$sql = sprintf("insert into emailmd5 values('%s','%s')",$email,$userid);  
//echo "sql is : ".$sql."\r\n";
if (mysql_query($sql,$con))
{
  //echo " succssful \r\n";
}
else
{
  //echo "Error : \r\n " . mysql_error();
}

$sql = sprintf("update  emailmd5 set saltmd5='%s' where email='%s'",$userid,$email);  
//echo "sql is : ".$sql."\r\n";
echo "<p>";
if (mysql_query($sql,$con))
{
  //echo " succssful \r\n";
}
else
{
  echo "Error : \r\n " . mysql_error();
  die("");
}
/*
echo "<p>";
$to = $email;
$subject = "Mynode userid ";
$message = $userid ;
$from = "yongming.li.hz@tcl.com";
$headers = "From: $from";
$mailerror = mail($to,$subject,$message,$headers);
echo $mailerror;
echo "Mail Sent successful \r\n";
*/
echo "your userid is : ".$userid;
mysql_close($con);
?>



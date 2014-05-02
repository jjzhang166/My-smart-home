<?php
//  auther :  yongming.li
if($name == NULL || $password == NULL)
{
   die(" name or password cant be null ...");
}
$con = mysql_connect("localhost","root","123456");
mysql_select_db("mynode", $con);

$sql = sprintf("select * from alluser where name='%s' and password='%s'",$name,$password);  
//$sql = sprintf("select * from alluser where password='%s'",$password);  
//echo "sql is : ".$sql."\r\n";
$result = NULL;
if ($result=mysql_query($sql,$con))
{
  //echo " succssful \r\n";
}
else
{
  die("Error : \r\n " . mysql_error());
}
if(mysql_num_rows($result)==0)
{
   die( "wrong name or password , and i cant tell you more ... you can understand \r\n");
}
while($row = mysql_fetch_array($result))
{
  // added by yongming.li
  // PHP Warning:  Cannot modify header information - headers already sent by
  $userid = $row['userid'];
  setcookie("userid",$userid, time()+3600);
  //echo $row['name'] . " : " . $row['password'];
  echo "<p>";
 
  echo "your userid is : ".$row['userid'];
  // added by yongming.li for multi users
  break;
  //echo "<p>";
}
mysql_close($con);
?>

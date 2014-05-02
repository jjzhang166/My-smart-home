<?php
$password=$_POST['password'];
$name=$_POST['name'];
$email=$_POST['email'];
$userid=$_POST['userid'];
$operation=$_POST['operation'];
/*
echo "password is:\r\n";
echo  "<p>";
echo $password;
echo  "<p>";
echo "name is :\r\n";
echo  "<p>";
echo $name;
echo  "<p>";
echo "email is :\r\n";
echo  "<p>";
echo $email;
echo  "<p>";
echo "operation is : \r\n";
echo  "<p>";
echo $operation;
echo  "<p>";
echo "userid is : \r\n";
echo  "<p>";
echo $userid;
*/

if($operation=="getuserid")
{
  echo "goto getuserid";
  echo  "<p>"; 
  include 'emailuserid.php';
}
if($operation=="register")
{
  echo "goto register";
  echo  "<p>"; 
  include 'register.php'; 
}
if($operation=="logon")
{
  //echo "goto  logon";
  //echo  "<p>"; 
  include 'logon.php'; 
  include 'managernode.php'; 
}
?>

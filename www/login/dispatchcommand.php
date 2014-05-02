<?php
//  auther :  yongming.li
echo "enter dispatchcommand";
echo "<p>";
$nodeid=$_POST['nodeid'];
$command=$_POST['command'];
echo "nodeid is :".$nodeid;
echo "<p>";

echo "command is : $command";
echo "<p>";
if(strlen($command) == 0)
{
   die("command cant be null");
}

$credis_string = sprintf("./credis-php hset %s command %s",$nodeid,$command);
echo $credis_string;
system($credis_string);
echo "<p>";
?>

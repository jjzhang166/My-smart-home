<?php 
// 建立客户端的socet连接 
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP); 
$connection = socket_connect($socket, '127.0.0.1', 6379); //连接服务器端socket 
socket_write($socket, "")
 

//服务器端收到信息后，给于的回应信息 

 

while ($buffer = socket_read($socket, 1024, PHP_NORMAL_READ)) { 

 

echo "sent to server: SOME DATA\n response from server was:" . $buffer . "\n"; 

 

} 

 

 

 

} 

 

} 

 

 

 

?> 

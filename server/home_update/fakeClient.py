#!/usr/bin/env python   

from socket import *  

HOST='172.0.0.1'  
PORT=6379  
BUFSIZ=1024  
ADDR=(HOST,PORT)
 
tcpCliSock=socket(AF_INET,SOCK_STREAM)  
tcpCliSock.connect(ADDR)  
 
while True:  

    tcpCliSock.send('smembers alluser') 
    data=tcpCliSock.recv(BUFSIZ) 
    if not data:  
       break  
    print data  
 
tcpCliSock.close()  


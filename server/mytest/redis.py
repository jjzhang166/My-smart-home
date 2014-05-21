#!/usr/bin/python 
#   yongming.li

import re
import string
import os
import time
import  sys
import socket  
   
 
myclient = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
myclient.connect(("localhost", 6379))  
myclient.send("chat logon yinzhi yinzhi \r\n")  
print  "send";
result=myclient.recv(256)  
print result  
myclient.send("lpush  yongming:message i\r\n")  
myclient.send("lpush  yongming:message love\r\n")  
myclient.send("lpush  yongming:message you\r\n")  
result=myclient.recv(256) 
print result  
myclient.close()

#print result   

def start():
    print   "start";
if __name__ == '__main__':
    HOST, PORT = "localhost", 4455
    #start()

version =  '0.2'  

class severity:
    UNKNOWN=0
    SKIP=100
    FIXMENOW=1
    HIGH=2
    MEDIUM=3
    LOW=4
    HARMLESS=5

def colorforseverity(sev):
    if sev == severity.FIXMENOW:
        return 'fuchsia'
    if sev == severity.HIGH:
        return 'red'
    if sev == severity.MEDIUM:
        return 'orange'
    if sev == severity.LOW:
        return 'yellow'
    if sev == severity.HARMLESS:
        return 'limegreen'
    if sev == severity.UNKNOWN:
        return 'blue'
    return 'grey'





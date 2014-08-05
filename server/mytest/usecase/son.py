import time
import string
from socket import *  
from time import sleep,ctime  
import thread  

print 'begin'
HOST='127.0.0.1'  
PORT=6379  
BUFSIZ=1024  
ADDR=(HOST,PORT)
 
c =socket(AF_INET,SOCK_STREAM)  
c.connect(ADDR)  

c.send('user login yongmingson yongmingson r r\r\n')

def heartbeat():  
    while True:
        time.sleep(30) 
        c.send('user heartbeat r r r r \r\n')
        time.sleep(30) 
thread.start_new_thread(heartbeat,()) 

def receiveMessage():  
    while True:  
        buf = c.recv(BUFSIZ) 
        print 'receive buf  is : '+buf
        parsr(buf)

thread.start_new_thread(receiveMessage,()) 

def parsr(s):
    s=s.strip()
    if 'response'  in s:
        return -1 
    items=string.split(s)

    # login ok 2745dd5ef44dd3f7a9a19e6d1491f18f
    if items[0]=='login' and   items[1]=="ok" :
        if items[2]=='2745dd5ef44dd3f7a9a19e6d1491f18f':
            print 'login ok ok ok'
        else:
            print 'login fail fail fail'
        return

    #  node  ok  yongming   state=close  messageid   qos
    if items[0]=="node" and items[1]=="ok" and items[5]=='1' :
        print 'should response the message'
        c.send(('node say  %s  response  %s  %s \r\n')%(items[2],items[4],items[5]))
        return
    # user ok yongming hello 445566 1 (qos)
    if items[0]=='user' and   items[1]=="ok" :
        if items[3]=="hello" and items[4]=="445566":
            print 'user say hello qos=1  ok  ok  ok'
            c.send(('user say  %s  response  %s  %s \r\n')%(items[2],items[4],items[5]))
            time.sleep(3)  
            c.send(('user say  %s  world  %s  %s \r\n')%(items[2],'NULL','0'))

        if items[3]=='hi' and items[4]=="778899":
            c.send(('user say  %s  hi  %s  %s \r\n')%(items[2],'NULL','0'))
        return

while True:  
    time.sleep(600)  
   
c.close()



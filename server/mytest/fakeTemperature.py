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

c.send('node login 2745dd5ef44dd3f7a9a19e6d1491f18f temperature  r r\r\n')

def heartbeat():  
    while True:
        time.sleep(30) 
        c.send('node heartbeat r r r r \r\n')
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
        if items[2]=='yongming':
            print 'login ok ok ok'
        else:
            print 'login fail fail fail'
        return

    #  node  ok  yongming   state=close  messageid   qos
    if items[0]=='node' and   items[1]=="ok" :
        if items[2]=='yongming' and items[4]=="445566" and items[5]=='1':
            print 'node say qos=1  ok  ok  ok'
            c.send(('node say  %s  response  %s  %s \r\n')%(items[2],items[4],items[5]))
            c.send(('node say  family  %s  %s  %s \r\n')%(items[3],'NULL','0'))

        if items[2]=='yongming' and items[4]=="778899":
            c.send(('node say  family  %s  %s  %s \r\n')%(items[3],'NULL','0'))
        return

#time.sleep(3)  
#c.send('node say family  state=open  112233  1 \r\n')
#time.sleep(3) 
#c.send('node say yongming  state=close  112233  0 \r\n') 

temperature=30
while True:  
    time.sleep(15)  
    if temperature > 35:
        temperature=30
    c.send(('node say family  name=temperature,value=%s  778899  0 \r\n')%(temperature))
    temperature= temperature+1
 
c.close()





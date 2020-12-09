#创建客户端

import socket

print("测试中===========")

s = socket.socket()

host = '192.168.43.21' 
#input("请输入链接的主机ip：")

port = 63213

s.connect_ex((host, port))
while True:
    print("收到的服务的消息：")
    res = s.recv(1024).decode()
    res_char = ''.join([chr(int(each)) for each in res.strip().split(" ")])
    '''if res == '':
        break'''

    print(res_char)
    sends = s.send(input("客户端发送的消息：").encode())
    if sends == 'qq':
        break

s.close()

import socket

s = socket.socket()

inputstr = []

host = socket.gethostname()
#print(host)
port =  63213

add = (host, port)

s.bind(add)

s.listen(5)
print("working ------------")
c, addr = s.accept()
print("accepted ------------\n连接地址：", addr)

def secret(inputstr):
    res = ''.join([str(ord(each))+" " for each in inputstr])
    res = res.encode()
    return res

while True:
    inputstr = input("请输入发送内容：")
    res = secret(inputstr)
    c.send(res)
    print("accepted------------")

    s = c.recv(1024).decode()

    if s.strip():
        print("接受到信息%s\n" % s)

c.close()
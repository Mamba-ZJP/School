from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM) # create socket
serverSocket.bind(('', serverPort)) # bind socket and port
serverSocket.listen(1) # 请求连接的最大数
print ("The server is ready!")
connectSocket, addr = serverSocket.accept() # 接收连接请求

while 1:
    sentence = connectSocket.recv(1024).decode() # bufsize
    print("Client says: ", sentence)
    response = input("Your answer: ")
    connectSocket.send(response.encode())

connectSocket.close()






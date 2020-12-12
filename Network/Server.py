from socket import *
import base64


serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM) # create socket
serverSocket.bind(('', serverPort)) # bind socket and port
serverSocket.listen(1)  # 请求连接的最大数

print ("The server is ready!")
connectSocket, addr = serverSocket.accept() # 接收连接请求

def encrypt(plaintext):   # 加密明文
    encryptedText = base64.b64encode(plaintext.encode("utf-8"))  # 先将字符串转为 2 进制
    return encryptedText

def decrypt(ciphertext):
    decryptedText = base64.b64decode(ciphertext).decode("utf-8")
    return decryptedText


while 1:
    sentence = decrypt( connectSocket.recv(1024) )  # bufsize
    print("Client says: ", sentence)
    response = input("Your answer: ")
    connectSocket.send( encrypt(response) )

connectSocket.close()







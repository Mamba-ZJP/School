from socket import * 
import base64

serverAddr = input("Server address:") # server ip  192.168.8.108
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM) 
clientSocket.connect((serverAddr, serverPort))

def encrypt(plaintext):   # 加密明文
    encryptedText = base64.b64encode(plaintext.encode("utf-8"))  # 先将字符串转为 2 进制 (utf-8：一种二进制编码格式)
    return encryptedText

def decrypt(ciphertext):
    decryptedText = base64.b64decode(ciphertext).decode("utf-8")
    return decryptedText

while 1:
    sentence = input("Client input : ")
    clientSocket.send( encrypt(sentence) )  # why encode()

    response = decrypt( clientSocket.recv(1024) )
    print ('Server answer: ', response)


clientSocket.close()








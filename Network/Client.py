from socket import * 

serverAddr = "192.168.43.230"
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverAddr, serverPort))

while 1:
    sentence = input("Client input : ")
    clientSocket.send(sentence.encode()) # why encode()

    response = clientSocket.recv(1024).decode()
    print ('Server answer: ', response)
    # clientSocket.close()

clientSocket.close()



#!/usr/bin/env python3
# command line http client
# call: ./htpclient.py <hostname>

import socket
import lxml.html

HOST = 'localhost' 
PORT = 80         
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
s.connect((HOST, PORT))
s.sendall(b'GET /\r\n\r\nHTTP/1.1\r\n')
data = s.recv(1024)
s.close()
print('Received', repr(data))
# print(lxml.html.document_fromstring(data).text_content())


connect: connect.c
	gcc connect.c -Wall -o connect

connect-http: connect-http.c
	gcc connect-http.c -Wall -o connect-http

mirror-server: mirror-server.c
	gcc mirror-server.c -Wall -o mirror-server 

mirror-server-threaded: mirror-server-threaded.c
	gcc mirror-server-threaded.c -Wall -o mirror-server-threaded  -l pthread

thread-example: thread-example.c
	gcc thread-example.c -o thread-example -lpthread -Wall

http-server: http-server.c
	gcc http-server.c -Wall -o http-server 

clean:
	-rm *.o connect connect-http mirror-server mirror-server-threaded http-server


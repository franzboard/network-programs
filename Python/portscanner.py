#!/usr/bin/env python3
# call: ./portscanner.py <hostname>
import socket
import sys

remoteServer  = sys.argv[1]

try:
    for port in range(1,1025):  
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(1.0)
        result = sock.connect_ex((remoteServer, port))
        if result == 0:
            print( "Port ", port, " open")
        sock.close()

except KeyboardInterrupt:
    print ("You pressed Ctrl+C")
    sys.exit()

except socket.gaierror:
    print ('Hostname could not be resolved. Exiting')
    sys.exit()

except socket.error:
    print ("Couldn't connect to server")
    sys.exit()

# Printing the information to screen
print ('Scanning Completed')

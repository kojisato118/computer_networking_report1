import socket
from contextlib import closing
import argparse

def connect(host='127.0.0.1', port=3000):
  bufsize = 4096

  print('connect to host:%s, port:%d' %(host, port))
  sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  with closing(sock):
    sock.connect((host, port))
    print('response: ' + sock.recv(bufsize))
  return

if __name__ == '__main__':
  p = argparse.ArgumentParser()

  #TODO: validation
  p.add_argument('-b', '--base', default='127.0.0.1')
  p.add_argument('-p', '--port', default=3000, type=int)
  args = p.parse_args()
  
  connect(args.base, args.port)

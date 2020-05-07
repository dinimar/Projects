# RSA used only for prime number generation
from Crypto.PublicKey import RSA
from binascii import unhexlify
from hashlib import sha1
import hashlib
from ch39 import modinv
import re

def find_cube_root(n):
    return int(round(n**(1./3)))

def prime_numbers(length):
    rsa_key = RSA.generate(length)

    return rsa_key.p, rsa_key.q

def verify_signature(e, n, msg, sign):
    block = b'\x00' + pow(sign, e, n)
    r = re.compile(b'\x00\x01\xff+?\x00(.{20})', re.DOTALL)
    m = r.match(block)
    if not m:
        return False
    digest = m.group(1)
    sha1 = hashlib.sha1()
    sha1.update(msg)
    return digest == sha1.digest()

if __name__ == "__main__":
    bit_length = 1024

    # generate prime 1024-bit numbers  
    p, q = prime_numbers(bit_length)
    n = p * q
    # message to sign
    msg = b'hi mom'
    # specify e
    e = 3
    # et
    et = (p-1)*(q-1)
    # d
    d = modinv(e, et)

    # asn1 string for sha-1 (from rfc 3447)
    asn1 = b"\x30\x21\x30\x09\x06\x05\x2b\x0e\x03\x02\x1a\x05\x00\x04\x14"
    # a block that looks like PKCS1.5 standard format
    block = b'\x00\x01\xff\x00' + asn1 + unhexlify(sha1(msg))
    garbage = (((bit_length + 7) // 8) - len(block)) * b'\x00'
    block += garbage
    
    # convert to int and find cube root
    pre_enc = int.from_bytes(block, byteorder='big')
    sign = find_cube_root(pre_enc)

    assert verify_signature(e, n, msg, sign)
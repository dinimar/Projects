import json
from Crypto import Random
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Util.Padding import unpad
from base64 import b64encode
from base64 import b64decode
from binascii import unhexlify
from hashlib import sha1
from ch33 import DiffieHellMan

def safe_transfer():
    # A->B
    a = DiffieHellMan()
    # Send p, g, A. Use default p, g
    A = a.mod_exp()
    # B->A
    b = DiffieHellMan()
    B = b.mod_exp()

    # A->B
    # Send AES-CBC(SHA1(s)[0:16], iv=random(16), msg) + iv
    a_msg = b'SOS'
    sh_key = unhexlify(sha1(str(B).encode()).hexdigest())[:16]
    a_enc_cipher = AES.new(sh_key, AES.MODE_CBC)
    a_iv = a_enc_cipher.IV
    a_ct = a_enc_cipher.encrypt(pad(a_msg, AES.block_size))+a_iv
    a_result_msg = {'iv':a_iv, 'ciphertext': a_ct}
    
    # B received A's msg
    b_inbox = a_result_msg
    # remove last 16 bits
    b_ct = b_inbox['ciphertext'][0:-16]
    b_iv = b_inbox['iv']
    dec_cipher = AES.new(sh_key, AES.MODE_CBC, b_iv)
    b_rec_msg = unpad(dec_cipher.decrypt(b_ct), AES.block_size)
    
    # B->A
    # Send AES-CBC(SHA1(s)[0:16], iv=random(16), A's msg) + iv
    b_enc_cipher = AES.new(sh_key, AES.MODE_CBC)
    b_iv = a_enc_cipher.IV
    b_ct = a_enc_cipher.encrypt(pad(b_rec_msg, AES.block_size))+b_iv
    b_result_msg = {'iv':a_iv, 'ciphertext': a_ct}
    
    # A received B's msg
    a_inbox = b_result_msg
    # remove last 16 bits
    a_ct = a_inbox['ciphertext'][0:-16]
    a_iv = a_inbox['iv']
    dec_cipher = AES.new(sh_key, AES.MODE_CBC, a_iv)
    a_rec_msg = unpad(dec_cipher.decrypt(a_ct), AES.block_size)
    
    assert a_msg == a_rec_msg
    print("Sent: ", a_msg)
    print("Recieved: ", a_rec_msg)


if __name__ == "__main__":
    safe_transfer()
    pass
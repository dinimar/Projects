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
    a_key = unhexlify(sha1(str(B).encode()).hexdigest())[:16]
    a_enc_cipher = AES.new(a_key, AES.MODE_CBC)
    a_iv = a_enc_cipher.IV
    a_ct = a_enc_cipher.encrypt(pad(a_msg, AES.block_size))+a_iv
    a_result_msg = {'iv':a_iv, 'ciphertext': a_ct}
    
    # B received A's msg
    b_inbox = a_result_msg
    b_key = unhexlify(sha1(str(B).encode()).hexdigest())[:16]
    # remove last 16 bits
    b_ct = b_inbox['ciphertext'][0:-16]
    b_iv = b_inbox['iv']
    dec_cipher = AES.new(b_key, AES.MODE_CBC, b_iv)
    b_rec_msg = unpad(dec_cipher.decrypt(b_ct), AES.block_size)
    
    # B->A
    # Send AES-CBC(SHA1(s)[0:16], iv=random(16), A's msg) + iv
    b_enc_cipher = AES.new(b_key, AES.MODE_CBC)
    b_iv = a_enc_cipher.IV
    b_ct = a_enc_cipher.encrypt(pad(b_rec_msg, AES.block_size))+b_iv
    b_result_msg = {'iv':a_iv, 'ciphertext': a_ct}
    
    # A received B's msg
    a_inbox = b_result_msg
    # remove last 16 bits
    a_ct = a_inbox['ciphertext'][0:-16]
    a_iv = a_inbox['iv']
    dec_cipher = AES.new(a_key, AES.MODE_CBC, a_iv)
    a_rec_msg = unpad(dec_cipher.decrypt(a_ct), AES.block_size)
    
    assert a_msg == a_rec_msg
    print("A Sent: ", a_msg)
    print("A Recieved: ", a_rec_msg)

def mitm_attack():
    # A->M
    a = DiffieHellMan()
    # Send p, g, A. Use default p, g
    A = a.mod_exp()



    # M->B
    # Send p, g, p. No data transferred cause default values used



    # B->M
    # Send B
    b = DiffieHellMan()
    B = b.mod_exp()



    # M->A
    # Send p. No data transferred cause default values used



    # A->M
    a_msg = b'We see you, MAN!'
    a_key = unhexlify(sha1(str(a.p_()).encode()).hexdigest())[:16]
    a_enc_cipher = AES.new(a_key, AES.MODE_CBC)
    a_iv = a_enc_cipher.IV
    a_ct = a_enc_cipher.encrypt(pad(a_msg, AES.block_size))+a_iv
    a_result_msg = {'iv':a_iv, 'ciphertext': a_ct}



    # M->B
    # M received A's msg
    m_a_key = unhexlify(sha1(str(a.p_()).encode()).hexdigest())[:16]
    m_inbox = a_result_msg
    # remove last 16 bits
    m_ct = m_inbox['ciphertext'][0:-16]
    m_iv = m_inbox['iv']
    dec_cipher = AES.new(m_a_key, AES.MODE_CBC, m_iv)

    m_rec_msg = unpad(dec_cipher.decrypt(m_ct), AES.block_size)
    assert a_msg == m_rec_msg
    print("A Sent: ", a_msg)
    print("M Recieved: ", m_rec_msg)
    print()

    # Relay received to B
    m_b_key = unhexlify(sha1(str(B).encode()).hexdigest())[:16]
    m_enc_cipher = AES.new(m_b_key, AES.MODE_CBC)
    m_iv = m_enc_cipher.IV
    m_ct = m_enc_cipher.encrypt(pad(a_msg, AES.block_size))+a_iv
    m_b_result_msg = {'iv':m_iv, 'ciphertext': m_ct}



    # B->M
    # B received M's msg
    b_m_key = unhexlify(sha1(str(B).encode()).hexdigest())[:16]
    b_inbox = m_b_result_msg
    # remove last 16 bits
    b_ct = b_inbox['ciphertext'][0:-16]
    b_iv = b_inbox['iv']
    dec_cipher = AES.new(b_m_key, AES.MODE_CBC, b_iv)

    b_rec_msg = unpad(dec_cipher.decrypt(b_ct), AES.block_size)
    assert m_rec_msg == b_rec_msg
    print("M Sent: ", m_rec_msg)
    print("B Recieved: ", b_rec_msg)
    print()


    # Relay that message to M
    b_enc_cipher = AES.new(b_m_key, AES.MODE_CBC)
    b_iv = b_enc_cipher.IV
    b_ct = b_enc_cipher.encrypt(pad(b_rec_msg, AES.block_size))+b_iv
    b_m_result_msg = {'iv':b_iv, 'ciphertext': b_ct}



    # M->A
    # M received B's msgs
    m_inbox = b_m_result_msg
    # remove last 16 bits
    m_ct = m_inbox['ciphertext'][0:-16]
    m_iv = m_inbox['iv']
    dec_cipher = AES.new(m_b_key, AES.MODE_CBC, m_iv)

    m_b_rec_msg = unpad(dec_cipher.decrypt(m_ct), AES.block_size)
    assert m_b_rec_msg == b_rec_msg
    print("B Sent: ", m_b_rec_msg)
    print("M Reieved: ", b_rec_msg)
    print()


    # Relay received to A
    m_enc_cipher = AES.new(m_a_key, AES.MODE_CBC)
    m_iv = m_enc_cipher.IV
    m_ct = m_enc_cipher.encrypt(pad(m_b_rec_msg, AES.block_size))+a_iv
    m_a_result_msg = {'iv':m_iv, 'ciphertext': m_ct}


    
    
    # A received M's message
    a_inbox = m_a_result_msg
    # remove last 16 bits
    a_ct = a_inbox['ciphertext'][0:-16]
    a_iv = a_inbox['iv']
    dec_cipher = AES.new(a_key, AES.MODE_CBC, a_iv)

    a_rec_msg = unpad(dec_cipher.decrypt(a_ct), AES.block_size)
    assert a_rec_msg == m_b_rec_msg
    print("M Sent: ", m_rec_msg)
    print("A Recieved: ", b_rec_msg)
    print()



if __name__ == "__main__":
    safe_transfer()
    print("---")
    mitm_attack()
    pass
# RSA used only for prime number generation
from Crypto.PublicKey import RSA
from ch39 import modinv
from ch39 import encrypt
from ch39 import decrypt
from ch42 import prime_numbers

def parity_oracle(c, d, n):
    """Decrypts the input data and returns whether the resulting number is odd."""
    p = decrypt(c, d, n)
    return p % 2

def deduce_plaintext(ciphertext, e, n, d):
    low = 0
    high = 1
    denom = 1
    # convert bytes to int
    c = int.from_bytes(ciphertext, byteorder='big')
    # compute the encryption of 2, which will be our ciphertext multiplier
    k = pow(2, e, n)
    # binary search for the correct plaintext
    for _ in range(n.bit_length()):
        c  = (c * k) % n
        p = parity_oracle(c, d, n)
        d = high - low
        low *= 2
        high *= 2
        denom *= 2
        if p == 0:
            high -= d
        else:
            low += d
        # convert num to bytes
        hightext = (n * high // denom).to_bytes((k.bit_length() + 7) // 8, byteorder='big')
        # to see the message being decrypted at every iteration, print the current hightext
        print(hightext)

    return hightext

if __name__ == '__main__':
    """
    Decrypts the given ciphertext using just the parity method of the oracle. Here a detailed explanation:
    http://secgroup.dais.unive.it/wp-content/uploads/2012/11/Practical-Padding-Oracle-Attacks-on-RSA.html
    """
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

    plain_text = b'VGhhdCdzIHdoeSBJIGZvdW5kIHlvdSBkb24ndCBwbGF5IGFyb3VuZCB3aXRoIHRoZSBGdW5reSBDb2xkIE1lZGluYQ=='
    
    ciphertext = encrypt(plain_text, e, n)
    deduced_text = deduce_plaintext(ciphertext, e, n, d)

     # check if the attack works
    assert deduced_text == plain_text
from ch39 import encrypt
from ch39 import decrypt
from ch39 import modinv
from random import randint

if __name__ == "__main__":
    p = 17
    q = 11
    
    N = p*q
    E = 3

    # et
    et = (p-1)*(q-1)
    # d
    d = modinv(E, et)

    m = "Hi to Alice from Bob!"
    C = encrypt(m, E, N)
    S = randint(1, N)

    C_script = [pow(S, E, N) * num % N for num in C]
    P = decrypt(C_script, d, N) 
    P_rec = ''.join([chr(modinv(S, N) * ord(ch) % N) for ch in P])

    print(P_rec)
    assert(m == P_rec)


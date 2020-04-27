def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

if __name__ == "__main__":
    # generate prime numbers
    p = 11
    q = 17
    # n
    n = p * q
    # et
    et = (p-1)*(q-1)
    # e
    e = 3
    # d
    d = modinv(e, et)
    # encrypt
    m = 42
    c = 42**e%n
    # decrypt
    d_m = c**d%n

    assert(m == d_m)
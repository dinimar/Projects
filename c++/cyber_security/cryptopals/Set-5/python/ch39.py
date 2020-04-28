def primes(n):  # simple Sieve of Eratosthenes
    odds = range(3, n+1, 2)
    sieve = set(sum([list(range(q*q, n+1, q+q)) for q in odds], []))
    return [2] + [p for p in odds if p not in sieve]


def extended_gcd(aa, bb):
    lastremainder, remainder = abs(aa), abs(bb)
    x, lastx, y, lasty = 0, 1, 1, 0
    while remainder:
        lastremainder, (quotient, remainder) = remainder, divmod(
            lastremainder, remainder)
        x, lastx = lastx - quotient*x, x
        y, lasty = lasty - quotient*y, y
    return lastremainder, lastx * (-1 if aa < 0 else 1), lasty * (-1 if bb < 0 else 1)


def modinv(a, m):
    g, x, y = extended_gcd(a, m)
    if g != 1:
        raise ValueError
    return x % m


def encrypt(plaintext, e, n):
    # Convert each letter in the plaintext to numbers based on the character using a^b mod m
    cipher = [(ord(char) ** e) % n for char in plaintext]
    # Return the array of bytes
    return cipher


def decrypt(ciphertext, d, n):
    # Generate the plaintext based on the ciphertext and key using a^b mod m
    plain = [chr((char ** d) % n) for char in ciphertext]
    # Return the array of bytes as a string
    return ''.join(plain)


if __name__ == "__main__":
    # generate prime numbers
    p = int('fb61c111b038153b645cdd3103fc5eb3e9ab09b64d11de97a08662c569fb22456203fa5fc6b7e41a8e83fe995eeaea9cca670575a662447d39012aa093a051e781df6018c0ea8ab76d49353363074e92f070dfe3c3c8964acad4532da8bea7b0944ffd229f06da23abe7b050418abe4b44513777b988ab30ee696ef053e23ca5', 16)
    q = int('c0ef0f196921eea05721308d4edca39afd20d0dbd6c6c446571f69d6c873838558c8bd2e3a5bee4b7d32de9819caf9f07d3807a16616081275263789adb5c1d092f9d0001486fde649998d15650b1e442e0076cacf5b276d6d52cbbe1ec713237ff0f59460967515914aed67eb806e92bc9a0affb27de9c5c74fa9aefa357627', 16)
    # p = 29
    # q = 11
    # n
    n = p * q
    # et
    et = (p-1)*(q-1)
    # e
    e = 3
    # d
    d = modinv(e, et)
    # encrypt
    m = "A"  # each character should be in range [0, n-1]
    c = encrypt(m, e, n)
    # decrypt
    d_m = decrypt(c, d, n)

    assert(m == d_m)

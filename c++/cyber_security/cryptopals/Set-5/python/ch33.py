from random import randint

class DiffieHellMan:
    DEFAULT_G = 2
    DEFAULT_P = int('ffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd129024e088a67cc74020bbea63b139b225'
                    '14a08798e3404ddef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245e485b576625e7ec6f4'
                    '4c42e9a637ed6b0bff5cb6f406b7edee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3dc20'
                    '07cb8a163bf0598da48361c55d39a69163fa8fd24cf5f83655d23dca3ad961c62f356208552bb9ed5'
                    '29077096966d670c354e4abc9804f1746c08ca237327ffffffffffffffff', 16)

    def p_(self):
        return self.p

    
    def g_(self):
        return self.g

    def mod_exp(self):
        pow(self.g, self.x_lower, self.p) 

    def public_key(p, g):
        x = x_lower(p)
        X = mod_exp(g, x, p)

        y = x_lower(p)
        Y = mod_exp(g, y, p)

        sX = mod_exp(X, y, p)
        sY = mod_exp(Y, x, p)

        assert sX == sY

    def __init__(self, g=DEFAULT_G, p=DEFAULT_P):
        self.g = g
        self.p = p
        self.x_lower = randint(0, self.p-1)
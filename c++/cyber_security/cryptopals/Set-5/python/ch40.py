from ch39 import encrypt
from ch39 import modinv

if __name__ == "__main__":
    p1 = 11
    p2 = 17
    p3 = 19
    q1 = 23
    q2 = 29
    q3 = 31

    n_0 = p1*q1
    n_1 = p2*q2
    n_2 = p3*q3
    e = 3

    m = "B"
    c_0 = encrypt(m, e, n_0)
    c_1 = encrypt(m, e, n_1)
    c_2 = encrypt(m, e, n_2)

    m_s_0 = n_1 * n_2
    m_s_1 = n_0 * n_2
    m_s_2 = n_0 * n_1

    n_012 = n_0 * n_1 * n_2

    t_0 = c_0[0] * m_s_0 * modinv(m_s_0, n_0)
    t_1 = c_1[0] * m_s_1 * modinv(m_s_1, n_1)
    t_2 = c_2[0] * m_s_2 * modinv(m_s_2, n_2)

    result = sum([t_0, t_1, t_2]) % n_012

    # decryted message
    d_m = int(round(result**(1./3)))

    assert(ord(m) == d_m)

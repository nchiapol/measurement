# coding: utf-8
from mss import MSS

R = MSS(1400, 30, 0)
I = MSS(1.12, 0.01, 0)
U = R*I
print U

import random
def bisetion(f, a, b, tol = 1e-6):
    fa = f(a)
    fb = f(b)
    while True:
        c = (a + b)/2
        fc = f(c)
        if abs(fc) < tol:
            break
        if fc*fa > 0:
            a, fa = c, fc
        if fc*fb > 0:
            b, fb = c, fc
    return c

def main():
    f = lambda x: x**3 -x -2
    while True:
        a = random.random()
        b = random.random()
        if f(a) * f(b) < 0:
            print(bisetion(f, a, b))
            break
    print (a,b)

main()
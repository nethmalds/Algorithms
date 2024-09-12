def main():
    x = float(input("Enter the number that you want to find the sqrt: "))
    g = float(input("Enter the guss number: "))

    print(findSqrt(x,g))
    
def findSqrt(x,g):
    sqr = g**2
    while abs(sqr-x)>=0.001:
        g = float((g + (x/g))/2) #Newton's law of finding sqrt
        sqr = g**2
    return round(g,3)

main()
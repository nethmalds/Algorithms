def main():
    s = int(input("Enter a number to caculate the pyramid count: "))
    print(pyramid(s))

def pyramid(s):
    if (s <= 3):
        return s
    else:
        i = 0
        while (s-4 >= i):
            result = pow(2,i) + s
            i += 1
        return result

main()
            

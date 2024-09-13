def main():
    t = int(input("Enter the number of test cases that you want: "))
    m = []
    for _ in range(t):
        m.append(int(input("Enter the generation, that disaster occured: ")))

    left_humans = humanPopulation(m,t)

    for left_human in left_humans:
        print(left_human)

def humanPopulation(m,t):
    left_humans = []
    for i in range(t):
        if m[i]<=1:
            left_humans.append(1%10)
        elif m[i] == 2:
            left_humans.append(2%10)
        else:
            total = 3
            n1=1
            n2=1
            for n in range(3,m[i],+1):
                result = n1 + n2
                n2 = n1
                n1 = result
                total = total + result
            left_humans.append(total%10)

    return left_humans
    
main()
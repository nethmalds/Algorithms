def main():
    t = int(input("Enter the test cases that you Expect: "))
    maximum_fighting_power = []
    for _ in range(t):
        c = int(input("Capacity of the beetleMan Bag: "))
        n = int(input("Number of gadgets in copperman Lab: "))

        weights = []
        f_powers = []
        for _ in range(n):
            w = int(input("Gadeget weight: "))
            f = int(input("Fighting Power: "))
            weights.append(w)
            f_powers.append(f)

        maximum_fighting_power.append(Max_FightingPower(c,weights,f_powers,n,t))
    for max_f in maximum_fighting_power:
        print(max_f)

def Max_FightingPower(capacity,weights,f_powers,n,t):
    capable_pow = []
    for i in range(n):
        if capacity >= weights[i]:
            capable_pow.append(f_powers[i])

    for j in range(len(capable_pow)):
        if capable_pow[j-1] >= capable_pow[j]:
            f_max = capable_pow[j-1]
    return f_max

main()

def main():
    N = int(input("Enter the number of elements in the array: "))
    array = [] * N
    array.extend(map(int, input("Enter elements: ").split()))
    originSum = 0
    for i in range(N):
        originSum = array[i] +originSum

    print(ZeroFinder(N,array,originSum))

def ZeroFinder(N,array,originSum):
    sum = 0
    for i in range(N):
        sum = originSum - array[i] + array[i]*-1
        if sum == 0:
            return i+1
    if sum!= 0:
        return '-1'

main()
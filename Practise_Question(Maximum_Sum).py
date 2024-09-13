def main():
    t = int(input("Enter the test cases that you Expect: "))
    n = int(input("Enter the integer count of the sequence: "))
    for _ in range(t):
        print("Enter Numbers for the sequence:",end='')
        array = list(map(int,input().split()))
        max_sum,sorted_sequence = maximum_sum(n,array)

        print(max_sum)
        print(' '.join(map(str,sorted_sequence)))

def maximum_sum(n,arr):

    arr = list(map(str,arr))
    arr.sort()
    result = [0]*len(arr)
    left = 0
    right = len(arr) - 1
    for i in range(len(arr)):
        if i % 2 == 0:
            result[left] = arr[i]
            left += 1
        else:
            result[right] = arr[i]
            right -= 1

    arr = list(map(int,arr))
    max_sum = sum(arr[i]*arr[i+1] for i in range(n-1))
    
    return max_sum,arr

main()

from collections import deque

def main():
    N , K = map(int,input().split())
    print(smallestMultiple(N,K))

def smallestMultiple (N,K):
    queue = deque()
    queue.append(str(K))
    visited = set()

    while queue:
        current = queue.popleft()
        number = int(current)
        if number % N == 0:
            return current
        else:
            for i in [str(K), '0']:
                new_num = current + i
                new_remainder = int(new_num) % N

                if new_remainder not in visited:
                    visited.add(new_remainder)
                    queue.append(new_num)
                    
main()
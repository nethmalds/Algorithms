def main():
    S = input()
    q = int(input())
    queries = []
    for _ in range(q):
        queries.append(input())

    results = longestSuffix(S,queries)

    for result in results:
        print(result)

def longestSuffix(s, queries):
    n = len(s)
    next_pos = [[n] * 26 for _ in range(n + 1)]

    for i in range(n - 1, -1, -1):
        for j in range(26):
            next_pos[i][j] = next_pos[i + 1][j]
        next_pos[i][ord(s[i]) - ord('a')] = i
    results = []
    for p in queries:
        m = len(p)
        pos = 0
        suffix_length = 0

        for i in range(m - 1, -1, -1):
            C_index = ord(p[i]) - ord('a')
            if next_pos[pos][C_index] == n:
                break
            suffix_length += 1
            pos = next_pos[pos][C_index] + 1

        results.append(suffix_length)

    return results

main()





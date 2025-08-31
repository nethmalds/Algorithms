
def main():
    n = int(input())
    name_height = []
    for _ in range(n):
        name, height = input().split()
        height = int(height)
        name_height.append((name, height))
    findGangPosition(name_height)

def findGangPosition(name_height):
    height_groups ={}
    for name,height in name_height:
        if height not in height_groups:
            height_groups[height] = []
        height_groups[height].append(name)

    sorted_heights = sorted(height_groups.keys())
    current_position = 1
    for height in sorted_heights:
        names = sorted(height_groups[height])
        min_position = current_position
        max_position = current_position + (len(names) - 1)
        print(' '.join(names),min_position,max_position)
        current_position = max_position + 1
main()
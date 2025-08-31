import random

def main():
    i = 0
    choice1 = 0
    choice2 = 0
    choice3 = 0
    choice4 = 0
    choice5 = 0
    choice6 = 0
    n = int(input())
    while(i< n):
        list  = [0,1,2,3,4,5,6]
        rand = random.choice(list)
        if rand == 1:
            choice1+=1
        elif rand == 2:
            choice2+=1
        elif rand == 3:
            choice3+=1
        elif rand == 4:
            choice4+=1
        elif rand == 5:
            choice5+=1
        elif rand == 6:
            choice6+=1
        
        i += 1

    predictions = [choice1, choice2, choice3, choice4, choice5, choice6]

    for predict in predictions:
        print(predict/n)

main() 
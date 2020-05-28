from random import randrange

def DisplayBoard(board):
    R_pic = "+-------+-------+-------+"
    C_pic_left = "|   "
    C_pic_right= "   " 
    
    for i in range(3):
        print(R_pic)
        for j in range(3):
            for k in range(3):
                if(j == 1):
                    print(C_pic_left,end='')
                    print(board[i][k], end='')
                    print(C_pic_right, end='')
                else:
                    print(C_pic_left,end='')
                    print(' ', end='')
                    print(C_pic_right, end='')

            print("|")

    print(R_pic)


def isValid(board, move):
    for i in range(3):
        for j in range(3):
            if(board[i][j] == move):
                return True

    return False


def EnterMove(board):
    print("Enter your move:", end='')
    move = input()
    while True:
        if isValid(board, move):
            break
        else:
            print("Enter valid move:", end='')
            move = input()

    x = 0
    y = 0
    for i in range(3):
        for j in range(3):
            if board[i][j] == move:
                x = i
                y = j

    board[x][y] = 'O'



# def MakeListOfFreeFields(board):
#
# the function browses the board and builds a list of all the free squares; 
# the list consists of tuples, while each tuple is a pair of row and column numbers
#

def VictoryFor(board, sign):
    # check all rows
    for i in range(3):
        cnt = 0
        for j in range(3):
            if board[i][j] == sign:
                cnt+=1

        if cnt == 3:
           return True

    # check all cols
    for i in range(3):
        cnt = 0
        for j in range(3):
            if board[j][i] == sign:
                cnt+=1

        if cnt == 3:
           return True

    # check digonals
    cnt = 0
    for i in range(3):
        for j in range(3):
            if i == j:
                if board[i][j] == sign:
                    cnt+=1

    if cnt == 3:
        return True

    cnt = 0
    for i in range(3):
        for j in range(3):
            if i + j == 2:
                if board[i][j] == sign:
                    cnt+=1

    if cnt == 3:
        return True 

    return False 


def checkForDraw(board):
    for i in range(3):
        for j in range(3):
            if board[i][j] != 'O' and board[i][j] != 'X':
                return False

    return True

def DrawMove(board):
    chosen = str(randrange(1,11))
    while True:
        if isValid(board,chosen):
            for i in range(3):
                for j in range(3):
                    if board[i][j] == chosen:
                        board[i][j] = 'X'
            break
        else:
            chosen = str(randrange(1,10))


board = [['1', '2', '3'],
         ['4', 'X', '6'],
         ['7', '8', '9']]

user = True
while True:
    if checkForDraw(board):
        DisplayBoard(board)
        print("DRAW !!!")
        break
    else:
        if user:
            if VictoryFor(board, 'O'):
                print("You Win!!")
                break

            else:
                user = False

            DisplayBoard(board)
            EnterMove(board)

            if VictoryFor(board, 'O'):
                DisplayBoard(board)
                print("You Win!!")
                break

            else:
                user = False

        else:
            if VictoryFor(board, 'X'):
                print("You Lose!!")
                break

            else:
                user = True
            
            DisplayBoard(board)
            DrawMove(board)

            if VictoryFor(board, 'X'):
                DisplayBoard(board)
                print("You Lose!!")
                break

            else:
                user = True

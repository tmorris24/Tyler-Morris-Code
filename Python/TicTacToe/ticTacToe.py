'''
 Tic Tac Toe: tict+TacToe.py
 Programmed by Tyler Morris - 06/03/2020

 This program allows for two players sitting at the same machine to be able to play a game of
 Tic Tac Toe. One player will be assigned "X", who will go first, and another player will be
 assigned "O", who will go second. The goal of the game is to get three in a row of the player's
 respective symbol. The three in a row can be vertical, horizontal, or diagonal. Upon achieving
 this, the player will have satisfied the win condition, ending the gameself.
'''


# This function prompts the users to decide who will go first, and will then ask if both
# players are ready to play.
def game_prompt():
    print("Welcome to Tic Tac Toe!")
    x = 0 # infinite loop conditon
    # initialization of vars
    player1 = ""
    gameon = ""

    # loop determines who will be first. If player one chooses "X", they will go first
    while x != 1:
        player1 = input("Player 1: Do you want to be X or O?\n")
        if player1 in ["x", "X", "o", "O"]:
            if player1 in ["x", "X"]:
                print("Player 1 will go first.")
            else:
                print("Player 2 will go first.")
            break
        else:
            print("I did not understand, please enter X or O")

    # loop determines whether or not to begin the game. If "Yes" the game will continue. If "No"
    # the program will end.
    while x != 1:
        gameon = input("Are you ready to play? Enter Yes or No.\n")
        if gameon in ["Y", "y","yes", "Yes", "YES", "N", "n", "no", "No", "NO"]:
            break
        else:
            print("I do not understand, please enter Yes or No.")
    if gameon in ["Y", "y","yes", "Yes", "YES"]:
        return player1.upper()
    else:
        return 0


# This function makes the move for the "X" player
def make_moveX(board):
    # Initialization of variables to a space that is off the board.
    locY = -1
    locX = -1
    selected = 0 # Verifies valid space

    row_display(board)

    # lopp that takes two coordinates, x and y, and plots them on the board
    while selected == 0:
        while locY not in ["1", "2", "3"]:
            locY = input("Please Enter a Row (1-3): ")
            if locY not in ["1", "2", "3"]:
                print("Invalid Entry")
        locY = int(locY) - 1
        while locX not in ["1", "2", "3"]:
            locX = input("Please Enter a Column (1-3): ")
            if locX not in ["1", "2", "3"]:
                print("Invalid Entry")
        locX = int(locX) - 1
        # Checks if the space is already taken
        if board[locY][locX] != " ":
            print("This space is taken! Try a different one!")
            locY = -1
            locX = -1
        # Plots the point
        else:
            board[locY][locX] = "X"
            selected = 1
    return board


# Does the same things as the previous move function but for "O". Could have passed in
# currentPlayer and added more control flow to condense into a single function.
def make_moveO(board):
    locY = -1
    locX = -1
    selected = 0

    row_display(board)

    while selected == 0:
        while locY not in ["1", "2", "3"]:
            locY = input("Please Enter a Row (1-3): ")
            if locY not in ["1", "2", "3"]:
                print("Invalid Entry")
        locY = int(locY) - 1
        while locX not in ["1", "2", "3"]:
            locX = input("Please Enter a Column (1-3):")
            if locX not in ["1", "2", "3"]:
                print("Invalid Entry")
        locX = int(locX) - 1
        if board[locY][locX] != " ":
            print("This space is taken! Try a different one!")
            locY = -1
            locX = -1
        else:
            board[locY][locX] = "O"
            selected = 1
    return board


# This function displays the board on call.
def row_display(board):
    # Unnecessary but aesthetically pleasing border rows
    padRow = "   |   |   "
    divRow = "-----------"

    # Plots the board
    print(padRow)
    print(" {} | {} | {}".format(board[0][0], board[0][1], board[0][2]))
    print(padRow)
    print(divRow)
    print(padRow)
    print(" {} | {} | {}".format(board[1][0], board[1][1], board[1][2]))
    print(padRow)
    print(divRow)
    print(padRow)
    print(" {} | {} | {}".format(board[2][0], board[2][1], board[2][2]))
    print(padRow)
    return 0


# This function checks the board to see if a win condition has been met.
def winCheck(board):
    # TODO: Rethink wincon logic to a more concise statement. May require board creation redesign
    for i, value in enumerate(board):
        # Checks all horizontal combinations and makes sure they aren't blank
        if board[i][0] == board[i][1] and board[i][1] == board[i][2] and board[i][0] != " ":
            return 1
        # Checks all vertical combinations and makes sure they aren't blank
        if board[0][i] == board[1][i] and board[1][i] == board[2][i] and board[0][i] != " ":
            return 1
    # Checks the diagonal from the top left corner and makes sure they aren't blank
    if board[0][0] == board[1][1] and board[1][1] == board[2][2] and board[0][0] != " ":
        return 1
    # Checks the diagonal from the bottom left corner and makes sure they aren't blank
    if board[0][2] == board[1][1] and board[1][1] == board[2][0] and board[0][2] != " ":
        return 1
    return 0


# Our main game function with the bulk of the game logic
def tictactoe():
    # Initialization of the board, filling it with blank spaces.
    board = [[" ", " ", " "],
             [" ", " ", " "],
             [" ", " ", " "]]
    # Win condition
    win = 0
    # Counter for the number of moves made
    moveCount = 0
    # Current Player
    currentPlayer = 0

    # Prompts the users to decide who will go first. Based on this we will display who will need
    # to make their move and change the current player to that player
    player1 = game_prompt()
    if player1 == 0:
        print("Goodbye!")
        return 0
    if player1 == "X":
        currentPlayer = 1
    else:
        currentPlayer = -1

    # The main game loop
    # While neither player has won
    while win == 0:
        if currentPlayer == 1:
            print("Player 1 Make your move!")
        else:
            print("Player 2 Make your move!")
        print("\n\n")

        # X makes their move
        board = make_moveX(board)
        moveCount += 1 # Add to count
        currentPlayer *= -1 # Switch Players
        # Checks if there are 5 or more moves made. This is because the minimum number of moves
        # before there can be a win conditon met is 5. 3 X moves and 2 O moves
        if moveCount >= 5:
            win = winCheck(board) # Checks for wincon
        for i in range(1, 100): # Clears window
            print("\n")

        # Here we see if a player has won or if the board is full
        if win == 1 or moveCount == 9:
            break

        # O makes their move. The rest is the same as the X move portion
        if currentPlayer == 1:
            print("Player 1 Make your move!")
        else:
            print("Player 2 Make your move!")
        print("\n\n")
        board = make_moveO(board)
        moveCount += 1
        currentPlayer *= -1
        if moveCount >= 5:
            win = winCheck(board)
        for i in range(1, 100):
            print("\n")

    # Check if a player has won, if not then the game ended in a draw
    if win == 0:
        print("It's a Draw!")
    # If a player has won
    else:
        # Change the player because we did so before we verified if someone had won and therefore
        # before we broke the while loop
        currentPlayer *= -1

        # Show which player won
        if currentPlayer == 1:
            print("Player 1 Wins!")
        else:
            print("Player 2 Wins!")

    # Display the final board
    print("\n\n")
    row_display(board)

    return 0



tictactoe()

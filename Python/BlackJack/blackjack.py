import deck
import card
import hand

def black_jack():
    deck1 = deck.Deck()
    balance = 1000


    print("Welcome to Black Jack!\n")

    while True:
        win = 0
        playerturn = 0
        dealerturn = 0

        print(f"Current Balance: ${balance}")
        if balance <= 0:
            print("You are out of money! Goodbye!")
            break
        play = input("Would you like to place a bet? Please enter Yes to play.\
        \nEnter any other input to quit\n\n")
        if play == "Yes" or play == "yes" or play == "y":
            pass
        else:
            print(f"Goodbye! Your final balance is: ${balance}")
            break

        print(f"\nPlease enter a bet!\nCurrent Balance: ${balance}")
        bet = 0
        while bet <= 0 or bet > balance:
            try:
                bet = int(input("Enter a bet: $"))
            except:
                bet = -1
            if bet <= balance and bet > 0:
                pass
            else:
                print(f"\nPlease enter a valid bet!\n\nCurrent Balance: ${balance}")
        print(f"Bet Placed!: ${bet}\n")

        print("Let's Play!\n")
        playerhand = hand.Hand(deck1)
        dealerhand = hand.Hand(deck1)
        while win == 0:
            print(f"Dealer is showing a {dealerhand.hand[-1].rank} of {dealerhand.hand[-1].suit}\n")

            while playerturn == 0:
                print("Player Hand:")
                for i, val in enumerate(playerhand.hand):
                    print(f"{playerhand.hand[i].rank} of {playerhand.hand[i].suit}")
                print(f"Player has {playerhand.total()}\n")

                move = input("Would you like to hit or stay?: ")
                if move == "Hit" or move == "hit":
                    playerhand.hit(deck1)
                    if playerhand.total() > 21:
                        print("Player Busts!\n")
                        win = -1
                        playerturn = 1
                elif move == "Stay" or "stay":
                    print(f"Player stays with {playerhand.total()}\n")
                    playerturn = 1
                else:
                    print("I didn't understand you!\n")

            if win == -1:
                print(f"Dealer wins with a {dealerhand.hand[-1].rank} of {dealerhand.hand[-1].suit}\
 and a {dealerhand.hand[-2].rank} of {dealerhand.hand[-2].suit}\n")
                break

            print(f"Dealer reveals a {dealerhand.hand[-2].rank} of {dealerhand.hand[-2].suit}\n")
            while dealerturn == 0:
                print("Dealer Hand:")
                for i, val in enumerate(dealerhand.hand, -1):
                    print(f"{dealerhand.hand[i].rank} of {dealerhand.hand[i].suit}")
                print(f"Dealer has {dealerhand.total()}\n")

                if dealerhand.total() <= 16:
                    print("The dealer hits\n")
                    dealerhand.hit(deck1)
                else:
                    print(f"The dealer stays with {dealerhand.total()}\n")
                    dealerturn = 1
                if dealerhand.total() > 21:
                    print("The dealer busts\n")
                    win = 1
                    dealerturn = 1
            break
        if win == 1 or ((playerhand.total() > dealerhand.total()) and win != -1):
            print(f"The player wins with {playerhand.total()}!\n")
            balance += bet
        elif win == -1 or playerhand.total() < dealerhand.total():
            print(f"The dealer wins with {dealerhand.total()}!\n")
            balance -= bet
        else:
            print("The player and dealer drew!\n")





black_jack()

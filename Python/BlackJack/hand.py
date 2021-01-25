import card
import deck

class Hand():

    hand = [None] * 2
    def __init__(self, deck):
        self.hand = [deck.deck.pop(0), deck.deck.pop(0)]

    def hit(self, deck):
        self.hand.append(deck.deck.pop(0))
        print(f"Dealt the {self.hand[-1].rank} of {self.hand[-1].suit}\n")

    def total(self):
        sum = 0
        for i in range(len(self.hand)):
            sum += self.hand[i].value
        if any(x.value == 11 for x in self.hand ) and sum > 21:
            sum -= 10
        return sum

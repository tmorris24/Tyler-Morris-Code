import card
import random
class Deck():
    deck = [None] * 52
    def __init__(self):
        x = 0
        for i in range(len(card.Card.suits)):
            for j in range(len(card.Card.ranks)):
                self.deck[x] = card.Card(card.Card.suits[i], card.Card.ranks[j])
                x += 1
        random.shuffle(self.deck)

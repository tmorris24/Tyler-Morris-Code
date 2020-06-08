# Given three integers between 1 and 11, if their sum is less than or equal to 21, return their
# sum. If their sum exceeds 21 and there's an eleven, reduce the total sum by 10. Finally, if
# the sum (even after adjustment) exceeds 21, return 'BUST'

def blackjack(n1, n2, n3):
    hand = [n1, n2, n3]
    total = sum(hand)
    if 11 in hand:
        total -= 10
    if total <= 21:
        return total
    else:
        return "BUST"

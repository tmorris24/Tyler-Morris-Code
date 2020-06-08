def lesser_of_two_evens(a, b):
    if a % 2 == 0 and b % 2 == 0:
        if a < b:
            return a
        else:
            return b
    elif a % 2 == 1 or b % 2 == 1:
        if a > b:
            return a
        else:
            return b


mynum = lesser_of_two_evens(2, 5)

print(mynum)

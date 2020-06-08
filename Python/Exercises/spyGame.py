# Write a function that takes in a list of integers and returns True if it contains 007 in order

def spy_game(n):
    i = 0
    while i != len(n):
        if n[i] == 0:
            while i != len(n) - 1:
                if n[i + 1] == 0:
                    while i != len(n) - 2:
                        if n[i + 2] == 7:
                            return True
                        i += 1
                i += 1
        i += 1
    return False

print(spy_game([1,2,4,0,0,7,5]))

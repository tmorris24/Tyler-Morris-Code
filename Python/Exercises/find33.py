# Given a list of ints, return True if the array contains a 3 next to a 3 somewhere

def has_33(n):
    for i, value in enumerate(n):
        if n[i] == 3 and i != len(n) - 1:
            if n[i + 1] == 3:
                return True
    return False

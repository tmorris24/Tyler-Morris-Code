# Given two integers, return True if the sum of the integers is 20 or if one of the
# integers is 20. If not, return False

def makes_twenty(n1, n2):
    if n1 == 20 or n2 == 20:
        return True
    elif n1 + n2 == 20:
        return True
    else:
        return False

num = makes_twenty(12, 8)
print(num)

# Given an integer n, return True if n is within 10 of either 100 or 200

def almost_there(n):
    if (90 <= n and n <= 110) or (190 <= n and n <= 210):
        return True
    else:
        return False

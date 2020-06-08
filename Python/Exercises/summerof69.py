# Return the sum of the numbers in the array, except ignore sections of numbers starting with a
# 6 and extending to the next 9 (every 6 will be followed by at least one 9). Return 0
# for no numbers.

def summer_69(n):
    total = 0
    count = 1
    i = 0
    while  i != len(n):
        if n[i] == 6:
            count = 0
        if count == 1:
            total += n[i]
        if n[i] == 9:
            count = 1
        i += 1
    return total

print(summer_69([2, 1, 6, 9, 11]))

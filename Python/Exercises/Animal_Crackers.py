# Write a function takes a two-word string and returns True if both words begin with same letter
def animal_crackers(string):
    s1, s2 = string.split()
    if s1[0] == s2[0]:
        return True
    else:
        return False

status =animal_crackers("Crazy Kangaroo")

print(status)

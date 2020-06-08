# Given a string, return a string where for every character in the original
# there are three characters

def paper_doll(string):
    s = list(string)
    i = 0
    while i != len(s) - 1:
        s.insert(i+1, s[i])
        s.insert(i+2, s[i])
        i = i+3
    s.insert(i+1, s[i])
    s.insert(i+2, s[i])
    return "".join(s)

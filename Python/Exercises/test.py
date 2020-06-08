def myfunc(word):
    s = list(word.lower())
    for x in range(0, len(s)):
        if x % 2 == 0:
            s[x] = s[x].upper()

    word = "".join(s)
    return word
myword = myfunc("Tyler")
print(myword)

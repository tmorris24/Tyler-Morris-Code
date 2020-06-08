# Given a sentence, return a sentence with the words reversed
def master_yoda(string):
    str = string.split()
    str = str[::-1]
    return " ".join(str)

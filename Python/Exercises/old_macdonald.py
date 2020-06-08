# Write a function that capitalizes the first and fourth letters of a name

def old_macdonald(name):
    str = list(name)
    str[0] = str[0].upper()
    str[3] = str[3].upper()
    return "".join(str)

print(old_macdonald("macdonald"))

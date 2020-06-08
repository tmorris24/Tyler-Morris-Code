def name_function():
    print("Hello")


name_function()


def say_hello(name="NAME"):
    print("hello " + name)

say_hello()

def add(n1, n2):
    print(n1 + n2)

add(203, 501)

def dog_check(mystring):
    if "dog" in mystring.lower():
        return True
    else:
        return False
print(dog_check("My Dog ran away"))

def pig_latin(word):

    first_letter = word[0]
    # check if vowel
    if first_letter in "aeiou":
        pig_word = word + "ay"
    else:
        pig_word = word[1:] + first_letter + "ay"
    return pig_word

myword = pig_latin("apple")
print(myword)

def myfunc(a, b, c = 0, d = 0, e = 0):
    return sum((a, b, c, d, e)) * 0.05
print(myfunc(40, 60, 100, 100, 3))

def myfunc(*args):
    return sum((args)) * 0.05
print(myfunc(40, 60, 100, 100, 3, 4))

def myfunc(**kwargs):
    if "fruit" in kwargs:
        print("My fruit of choice is {}".format(kwargs['fruit']))
    else:
        print("I did not find any fruit here")

myfunc(fruit = "apple")

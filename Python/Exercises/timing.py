import time
import timeit

def func_one(n):
    return[str(num) for num in range(n)]
start_time = time.time()
result = func_one(1000000)
end_time = time.time()
elapsed_time = end_time - start_time
print(elapsed_time)

def func_two(n):
    return list(map(str, range(n)))

start_time = time.time()
result = func_two(1000000)
end_time = time.time()
elapsed_time = end_time - start_time
print(elapsed_time)

stmt = '''
func_one(100)
'''

setup = '''
def func_one(n):
    return[str(num) for num in range(n)]
'''

a = timeit.timeit(stmt,setup, number = 1000000)
print(a)

stmt2 = '''
func_two(100)
'''
setup2 = '''
def func_two(n):
    return list(map(str, range(n)))
'''
b = timeit.timeit(stmt2, setup2, number = 1000000)
print(b)

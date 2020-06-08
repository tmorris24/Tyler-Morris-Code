# Write a function that returns the number of prime numbers that
# exist up to and including a given number

def count_primes(n):
    count = 0
    prime = 1
    for i in range(2, n):
        for j in range(2, i):
            if (i % j) == 0:
                prime = 0
                break
        if prime == 1:
            count += 1
        prime = 1
    return count

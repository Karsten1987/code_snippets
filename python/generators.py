#!/usr/env python

def fibonacci_generator(n):
    a = 0
    b = 1
    for i in range(n):
        c = a + b
        yield c
        a = b
        b = c
    return


def fibonacci(n):
    a = 0
    b = 1
    for i in range(n):
        c = a + b
        print(c)
        a = b
        b = c

def fibonacci_rec(n, a, b):
    if n == 0:
        return a+b
    return fibonacci_rec(n-1, b, a+b)

if __name__ == "__main__":
    fibonacci(5)
    print("now with generator")
    for x in fibonacci_generator(5):
        print(x)
    print("now with recursion")
    print(fibonacci_rec(5, 0, 1))

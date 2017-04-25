#!/usr/bin/env python

def multipliers(n):
    return [lambda x : x * i for i in range(n)]

my_list = multipliers(3)
print(len(my_list))
print(my_list[1](3))

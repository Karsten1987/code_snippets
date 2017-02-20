#!/usr/bin/env python3
from string import Template

def Main():
    cart = []
    cart.append({'name':'coke', 'price':1.5, 'item':1})
    cart.append({'name':'sprite', 'price':1.5, 'item':1})
    cart.append({'name':'fanta', 'price':1.5, 'item':1})
    cart.append({'name':'water', 'price':1.5, 'item':1})

    t = Template("$item units of product $name costs $price")
    all_items = [t.substitute(x) for x in cart]
    print(all_items)

if __name__ == '__main__':
    Main()

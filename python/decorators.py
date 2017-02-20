#!/usr/bin/env python3

def Tags(*tags):
    def decorator(actual_function):
       def inside(*args, **kwargs):
           code = actual_function(*args, **kwargs)
           for tag in reversed(tags):
               code = "<{0}>{1}</{0}>".format(tag, code)
           return code
       return inside
    return decorator


@Tags("p", "c", "i")
def wrappy(name):
    return name

if __name__ == "__main__":
    print(wrappy("hello"))



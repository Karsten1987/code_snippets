#!/usr/bin/python3
import spam
print(dir(spam))
status = spam.system("ls -l")
print(spam.hello_world())


def my_void_callback():
    print("Hello Void Callback")

def my_int_callback(i):
    print("Hello Int Callback", i)

#spam.set_void_callback(my_void_callback.__call__)
spam.set_void_callback(my_void_callback)
spam.trigger_void_callback()

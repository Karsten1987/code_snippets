#!/usr/bin/env python3

class MyEnterExitClass(object):

    def __enter__(self):
        print("doing entering stuff")
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        print("doing exiting stuff")

    def my_function(self):
        print("Doing cool stuff")

if __name__ == "__main__":

    with MyEnterExitClass() as mee:
        mee.my_function()
    print("out of scope text")

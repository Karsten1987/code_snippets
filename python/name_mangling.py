#!/usr/bin/env python

class MyClass(object):

    def __init__(self):
        print "init MyClass"

    def _single_underscore_method(self):
        print "my single underscore method"

    def __double_underscore_method(self):
        print "my double underscore method"

if __name__ == "__main__":
    mc = MyClass()
    print dir(mc)

    mc._single_underscore_method()
    mc.__double_underscore_method()

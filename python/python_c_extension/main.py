#!/usr/bin/python3
import callbackmodule

def on_callback():
    print("on_callback() in python")

callbackmodule.register_callback(on_callback)
print('Going to invoke the callback now')
callbackmodule.invoke_callback()

class Second(object):
    
    def __init__(self):
        print 'initializing second'

    def say(self, s, vec = []):
        vec.append(s)
        print vec

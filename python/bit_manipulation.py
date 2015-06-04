i = 36

def countBits(i):
    n = 0;
    while i:
        print "{0:b}".format(i)
        print "{0:b}".format(i-1)
        print "{0:b}".format( i&(i-1))
        print "******"
        i = i&(i-1)
        n = n+1
    return n

n = countBits( i )
print 'set bits in ' + str(i) + " " + str(n)

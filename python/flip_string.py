s = ['h','e','l','l','o',' ','w','o','r','l','d','!']
print len(s)
print s[0]

for idx in range(len(s)/2):
    s_old = s[idx]
    s[idx] = s[len(s)-1-idx]
    s[len(s)-1-idx] = s_old

print 'rotated string ', s


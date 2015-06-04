# abcdef rotate 3 ==> defabc
# abcdef rotate 1 ==> fabcde

s = [ 'a','b','c','d','e','f']
d = list(s)
r = 1

idx = 0
for idx in range(len(s)):
    new_idx = (idx+r)%len(s)
    d[new_idx] = s[idx]

print 's: ', s
print 'd: ', d


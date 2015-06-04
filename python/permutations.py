s = 'karsten'

# 7! possibilities
all_perms = []

def permutation( s ):
    if len(s) == 0:
        return ""
    if len(s) == 1:
        return s



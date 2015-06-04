# 1 2 3 5 8 13 21

numbers = []

def fibonacci( lhs, rhs, idx, max_n ):
    numbers.append( lhs+rhs )
    if idx == max_n:
        return
    else:
        idx +=1
        fibonacci( rhs, lhs+rhs, idx, max_n)

fibonacci( 0, 1, 0, 10 )
print numbers


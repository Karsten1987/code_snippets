# your code goes here

def list_comprehension():
        vec = [0, 10, 1, 10, 2, 10, 3, 10, 4, 10, 5, 10]

        vec_filter = [x for x in vec if x != 10]
        print vec_filter

def reverse_vector():
        vec = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

        vec_reverse = [vec[len(vec)-i-1] for i in range(len(vec))]
        print vec_reverse

if __name__ == "__main__":
        list_comprehension()
        reverse_vector()


def iterate_over(strings, deltas):
    for string, delta  in zip(strings, deltas):
        print "{0} and {1}".format(string, delta)

iterate_over(("my_item", "my_other_item"), (1,2))

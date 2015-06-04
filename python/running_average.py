idx     = 0
sum_all = 0

def calculate_average(n):
    global idx, sum_all
    idx = idx + 1
    sum_all = sum_all + n
    print "running average is :", float(sum_all)/idx

def main_loop():
    for _ in range(10):
        n = int( raw_input("enter new number") )
        calculate_average(n)

if __name__ == "__main__":
    main_loop()

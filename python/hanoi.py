#/usr/env python

class Tower(object):

    def __init__(self, n):
        self.pole1 = [x+1 for x in range(n)]
        self.pole2 = []
        self.pole3 = []
        self.n = n
        self.max_width = self.pole1[n-1]

    def print_tower(self):
        for x in range(self.n):
            if len(self.pole1) > x:
                line = str(str(self.pole1[x])*self.pole1[x]).ljust(self.max_width)
            else:
                line = str().ljust(self.max_width)
            if len(self.pole2) > x:
                line += str(self.pole2[x]).ljust(self.max_width)
            else:
                line += str().ljust(self.max_width)
            if len(self.pole3) > x:
                line += str(self.pole3[x]).ljust(self.max_width)
            else:
                line += str().ljust(self.max_width)

            print(line)

if __name__ == "__main__":
    t = Tower(5)
    t.print_tower()

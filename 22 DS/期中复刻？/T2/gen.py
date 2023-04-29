import random
import sys
import os

INT_MAX = 2147483647
INT_MIN = -2147483648


def gen(MAXN=100000):
    n = random.randint(MAXN//3, MAXN)
    nums = [random.randint(INT_MIN, INT_MAX) for _ in range(min(MAXN//3, 1000))]
    print(n)
    print(*random.choices(nums, k=n))


if __name__ == '__main__':
    if len(sys.argv) == 1:
        gen(20)
    else:
        os.makedirs('data', exist_ok=True)
        for i in range(1, int(sys.argv[1]) + 1):
            dataIn = os.path.join('data', '%d.in' % i)
            dataOut = os.path.join('data', '%d.out' % i)
            with open(dataIn, 'w') as f:
                sys.stdout = f
                gen()
                f.close()
            os.system('.\\bin\\std.exe < ./%s > ./%s' % (dataIn, dataOut))

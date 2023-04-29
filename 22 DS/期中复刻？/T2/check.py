import os
import sys
from gen import gen
from colorama import Fore
from alive_progress import alive_bar


CHECK_TIMES = 20
EXE_PATH = '.\\bin\\std.exe'
STD_PATH = '.\\bin\\std.exe'

def check(exe = EXE_PATH):
    with open('test.in', 'w') as f:
        sys.stdout = f
        gen()
        f.close()
    os.system(f'.\\{exe} < .\\test.in > .\\test.out')
    os.system(STD_PATH + ' < .\\test.in > .\\test.ans')
    with open('test.out', 'r') as out, open('test.ans', 'r') as ans:
        if out.read() != ans.read():
            return False
    return True


if __name__ == '__main__':
    # exe = input('Executable file name: ')
    with alive_bar(CHECK_TIMES) as bar:
        for _ in range(CHECK_TIMES):
            if not check():
                sys.stdout = sys.__stdout__
                print(Fore.RED + 'Wrong Answer' + Fore.RESET)
                exit(0)
            bar()
    os.remove('test.in')
    os.remove('test.out')
    os.remove('test.ans')
    sys.stdout = sys.__stdout__
    print(Fore.GREEN + 'Accepted' + Fore.RESET)

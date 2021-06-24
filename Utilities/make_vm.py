"""
Generate the enum code for the VM header file.
"""

def getmin(k):
    if ((k & 0x8000) != 0):
        return (k & 0x7fff)
    else:
        return (k >> 8)

def getmax(k):
    if ((k & 0x8000) != 0):
        return (k & 0x7fff)
    elif ((k & 0x80) == 0):
        return (k & 0xff)
    else:
        return -1;

def getstep(k):
    if ((k & 0x8000) != 0):
        return 1
    elif ((k & 0x80) == 0):
        return 1
    else:
        return ((-k) & 0xff)

def printm(k):
    n = getmin(k)
    m = getmax(k)
    s = getstep(k)
    a = 'M'
    a += str(n)
    if (m > n or m < 0):
        a += 'T'
        if (s > 1):
            a += str(s)
        if (m > 0):
            a += str(m)
        else:
            a += 'N'
    return a

if __name__ == '__main__':
    import sys

    if len(sys.argv) > 1:
        nlist = []
        for i in sys.argv[1:]:
            nlist.append(int(i, 16))
    else:
        nlist = [0x0000, 0x00FF, 0x7F7F, 0x8080, 0x80FF,
                 0x8100, 0x8200, 0x8300, 0x8400, 0x8800]
        nrange = list(range(0,33)) + [63, 64, 99, 100]
        for i in nrange:
            mrange = list(range(i,33)) + [63, 64, 99, 100, 0xff]
            for j in mrange:
                if j < i:
                    continue
                nlist.append((i << 8) | j)
                if j == 0xff and i > 1:
                    nlist.append((i << 8) | (j - i + 1))

    nlist.sort()
    for i in nlist:
        m = printm(i)
        if len(m) <= 9:
            print('    %-9.9s = 0x%4.4X,' % (m, i))

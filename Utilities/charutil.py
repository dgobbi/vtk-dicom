"""
Utility functions for generating character set tables.

This includes functions for reading tables from files,
adjusting the tables, reversing the tables, and printing
the tables.

The generated tables are sparse and use linear compression,
and are printed in a format usable from C++ code.
"""

import bisect
import sys
import string

# replacement character
RCHAR = 0xFFFD

def readtable(fname):
    """Read a text file that contains a mapping table.
    The table is assumed to have two or more columns,
    with '#' for comments.
    """
    f = open(fname, 'r')
    lines = f.readlines()
    f.close()
    maxindex = 0
    for l in lines:
        l = l.strip()
        if l and l[0] != '#':
            columns = l.split()
            maxindex = max(maxindex, int(columns[0],base=0))
    table = [RCHAR]*(maxindex+1)
    for l in lines:
        l = l.strip()
        if l and l[0] != '#':
            columns = l.split()
            if len(columns) > 1:
                table[int(columns[0],base=0)] = int(columns[1],base=0)
    return table

def readlinear(fname):
    """Read a linear table, each line becomes two consecutive elements.
    Comments begin with '#'.
    """
    f = open(fname, 'r')
    lines = f.readlines()
    f.close()
    table = []
    for l in lines:
        l = l.strip()
        if l and l[0] != '#':
            columns = l.split()
            table.append(int(columns[0],base=0))
            table.append(int(columns[1],base=0))
    return table

def readdict(fname):
    """Read a text file that contains a mapping table.
    The table is assumed to have two or more columns,
    with '#' for comments.
    """
    d = {}
    f = open(fname, 'r')
    for l in f.readlines():
        l = l.strip()
        if l and l[0] != '#':
            columns = l.split()
            if len(columns) > 1:
                d[int(columns[0],base=0)] = int(columns[1],base=0)
    f.close()
    return d

def makedict(table, reverse, *special):
    """Turn a table into a dict, since a dict is better for sparse data.
    If "reverse" is set, the dict provides the reverse mapping.
    """
    ranges = []
    dicts = []
    for s in special:
        if type(s) == dict:
            dicts.append(s)
        else:
            ranges.append(s)
    d = {}
    for j in range(len(table)):
        if reverse:
            i = j
            c = table[j]
        else:
            c = j
            i = table[j]
        for r in ranges:
             if c >= r[0] and c <= r[1]:
                  c = 0xFFFD
                  break
        if i == 0xFFFD or c == 0xFFFD:
            continue
        if c not in d:
            d[c] = i
    for s in dicts:
        for c,i in s.items():
            for r in ranges:
                if c >= r[0] and c <= r[1]:
                    c = 0xFFFD
                    break
            if c == 0xFFFD:
                continue
            d[c] = i
    return d

def maketable(d, maxrun=8, maxin=0xFFFF):
    """Given a dict created with "makedict", create a compressed table.
    """
    keys = list(d.keys())
    keys.sort()

    utable = [0]
    vtable = [RCHAR]
    wtable = [RCHAR]
    dtable = []

    i = 0
    while i < len(keys):
        key = keys[i]
        val = d[key]
        assert val != RCHAR
        j = i+1
        jj = 0
        k = RCHAR
        # check for a character run
        while (j < len(keys) and keys[j] == key+(j-i) and
               d[keys[j]] == val+(j-i)):
            j += 1
        if j-i < maxrun:
            k = len(dtable)
            assert k != RCHAR
            j = i+1
            dtable.append(val)
            val = RCHAR
            runlen = 0
            while j < len(keys) and keys[j] - keys[j-1] < maxrun:
                key1 = keys[j-1]
                key2 = keys[j]
                if key2 == key1+1 and d[key2] == d[key1]+1:
                    runlen += 1
                    if runlen == maxrun:
                        dtable = dtable[0:-runlen]
                        j -= runlen
                        break
                else:
                    runlen = 0
                for n in range(key1+1,key2):
                    dtable.append(RCHAR)
                    jj += 1
                dtable.append(d[key2])
                j += 1
            if len(dtable) > k:
                runlen = 1
                for kk in range(k+1,len(dtable)):
                    if dtable[kk] == dtable[kk-1]+1:
                        runlen += 1
                if len(dtable) == k + runlen:
                    val = dtable[k]
                    dtable = dtable[0:k]
                    k = RCHAR
        if utable[-1] == key:
            vtable[-1] = val
            wtable[-1] = k
        else:
            utable.append(key)
            vtable.append(val)
            wtable.append(k)
        utable.append(key+(j+jj-i))
        vtable.append(RCHAR)
        wtable.append(RCHAR)
        i = j

    while utable[-1] > maxin:
        utable = utable[0:-1]
        vtable = vtable[0:-1]
        wtable = wtable[0:-1]

    return [len(utable)] + utable + vtable + wtable + dtable

"""
# simpler code that does not include 'dtable'
i = 0
while i < len(keys):
    key = keys[i]
    val = d[key]
    # look for a run
    j = i+1
    while j < len(keys) and keys[j] == key+(j-i) and d[keys[j]] == val+(j-i):
        j += 1
    if utable[-1] == key:
        vtable[-1] = val
    else:
        utable.append(key)
        vtable.append(val)
    utable.append(key+(j-i))
    vtable.append(RCHAR)
    i = j
"""

def maketable2(table, reverse, *special, **kw):
    """Given a dense table, create a compressed table.
    If "reverse" is set, then the compressed table reverses the input table.
    """
    d = makedict(table, reverse, *special)
    t = maketable(d, **kw)
    try:
        maxin = kw['maxin']
    except KeyError:
        maxin = 0xFFFF
    header = []
    ranges = []
    dicts = []
    for s in special:
        if type(s) == dict:
            dicts.append(s)
        else:
            ranges.append(s)
    header.append(len(ranges))
    if ranges:
        newdata = [ [] ]*len(ranges)
        shift = 0
        for r in ranges:
            shift += r[1] - r[0] + 1
        n = t[0]
        p = 3*n + 1
        t[p:p] = [RCHAR]*shift
        for i in range(2*n+1,3*n+1):
            if t[i] != RCHAR:
                t[i] += shift
                assert t[i] != RCHAR
        for j in range(len(table)):
            if reverse:
                i = j
                v = table[j]
            else:
                i = table[j]
                v = j
            p = 3*n + 1
            for r in ranges:
                if v >= r[0] and v <= r[1]:
                    t[v - r[0] + p] = i
                p += r[1] - r[0] + 1
        for s in dicts:
            for v,i in s.items():
                p = 3*n + 1
                for r in ranges:
                    if v >= r[0] and v <= r[1]:
                        t[v - r[0] + p] = i
                    p += r[1] - r[0] + 1
        p = 3*n + 1
        for r in ranges:
            j = bisect.bisect(t[1:n+1], r[0])
            if t[j] == r[0]:
                t[j+2*n] = p - 3*n - 1
                assert t[j+2*n] != RCHAR
                t[j+n] = RCHAR
            else:
                j += 1
                t.insert(j+2*n, p - 3*n - 1)
                assert t[j+2*n] != RCHAR
                t.insert(j+n, RCHAR)
                t.insert(j, r[0])
                assert t[0] != RCHAR
                n += 1
                p += 3
            header.append(j-1)
            if j+1 >= n or t[j+1] != r[1] + 1:
                t.insert(j+1+2*n, RCHAR)
                t.insert(j+1+n, RCHAR)
                t.insert(j+1, r[1] + 1)
                assert t[j+1] != RCHAR
                n += 1
                p += 3
            p += r[1] - r[0] + 1
        t[0] = n

        while t[n] > maxin:
           del t[3*n]
           del t[2*n]
           del t[1*n]
           n -= 1
           t[0] = n

    return header + t

def printrows(table, fmt, n):
    h = fmt.find('%')
    l = h+1
    while fmt[l] in string.digits:
        l += 1
    w = str(h)
    if l > h+1:
        w = str(h + int(fmt[h+1:l]))
    fmt1 = '%s' + '%' + w + 's,'
    fmt2 = '%s' + fmt + ','
    for k in range(len(table)):
        u = table[k]
        s = ' '
        if k % n == 0:
            s = '\n  '
        if u == RCHAR:
            sys.stdout.write(fmt1 % (s,'RCHAR'))
        else:
            sys.stdout.write(fmt2 % (s,u))

def printtable(name, table, reverse, dtype='unsigned short', maxin=0xFFFF):
    n = table[0]
    htable = table[1:n+1]
    l = table[n+1]
    utable = table[n+2:n+l+2]
    vtable = table[n+l+2:n+2*l+2]
    wtable = table[n+2*l+2:n+3*l+2]
    dtable = table[n+3*l+2:]

    ufmt = '0x%04X'
    ucnt = 8
    cfmt = '%6d'
    ccnt = 8
    ufmt2 = '0x%04X'
    cfmt2 = '%6d'

    if reverse:
        (ffmt2,ffmt) = (ufmt2,ufmt)
    else:
        (ffmt2,ffmt) = (cfmt2,cfmt)
    if not reverse:
        (tfmt2,tfmt,tcnt) = (ufmt2,ufmt,ucnt)
    else:
        (tfmt2,tfmt,tcnt) = (cfmt2,cfmt,ccnt)

    sys.stdout.write('const %s %s[%d] = {' % (dtype, name, len(table)))
    sys.stdout.write('\n  // hot segments (indexes into segment table)')
    printrows([n] + htable, '%d', 8)
    sys.stdout.write('\n  // number of segments')
    printrows([l], '%d', 8)
    sys.stdout.write('\n  // segment table')
    printrows(utable, ffmt2, 8)
    sys.stdout.write('\n  // compressed segments')
    printrows(vtable, tfmt2, 8)
    sys.stdout.write('\n  // uncompressed segments')
    printrows(wtable, tfmt2, 8)

    itable = list(htable)
    for i in range(l):
        if i not in htable:
            if htable and wtable[i] == RCHAR:
                itable.insert(bisect.bisect_left(itable, i), i)
            else:
                itable.append(i)

    for i in itable:
        nextval = maxin+1
        if i+1 < l:
            nextval = utable[i+1]
        s = nextval - utable[i]
        v = vtable[i]
        w = wtable[i]
        if v != RCHAR or w != RCHAR:
            sys.stdout.write(('\n  // ['+ffmt+','+ffmt+']') %
                             (utable[i], nextval-1))
        if v != RCHAR:
            sys.stdout.write((' -> ['+tfmt+','+tfmt+'] # seg %d') % (v,v+s-1,i))
        if w != RCHAR:
            sys.stdout.write(' -v # seg %d at pos %d' % (i,w))
            printrows(dtable[w:w+s], tfmt, tcnt)
    sys.stdout.write('\n};\n')

def searchtable(table, x):
    n = table[0]
    l = table[n+1]
    utable = table[n+2:n+l+2]
    vtable = table[n+l+2:n+2*l+2]
    wtable = table[n+2*l+2:n+3*l+2]
    dtable = table[n+3*l+2:]
    for j in table[1:n+1]:
        if x >= utable[j] and x < utable[j]:
            i = j
            break
    else:
        i = bisect.bisect(utable, x) - 1
    u = utable[i]
    v = vtable[i]
    if v == RCHAR:
        v = wtable[i]
        if v == RCHAR:
            return RCHAR
        return dtable[v + (x - u)]
    elif v == RCHAR:
        return RCHAR
    else:
        return v + (x - u)

def checktable(table, reverse, orig, *dicts):
    for j in range(len(orig)):
        if reverse:
            i = j
            k = orig[j]
        else:
            i = orig[j]
            k = j
        c = searchtable(table, k)
        if k == 0xFFFD:
            if c != RCHAR:
                print("zerofail %d %d %#4.4x" % (i, c, k))
        elif i != c:
            print("matchfail %d %d %#4.4x" % (i, c, k))
    for d in dicts:
        for k,i in d.items():
            c = searchtable(table, k)
            if k == 0xFFFD:
                if c != RCHAR:
                    print("zerofail %d %d %#4.4x" % (i, c, k))
            elif i != c:
                print("matchfail %d %d %#4.4x" % (i, c, k))

def print_table_of_tables(name, table):
    sys.stdout.write(
        'const unsigned short *vtkDICOMCharacterSet::%s[%d] = {\n'
        % (name, len(table)))
    count = 1
    for item in table:
        if item != '0':
            if count != 1:
                sys.stdout.write('\n')
            sys.stdout.write('  %s,\n' % (item,))
            count = 1
        elif count == 1:
            sys.stdout.write('  %s,' % (item,))
            count += 1
        elif count < 24:
            sys.stdout.write(' %s,' % (item,))
            count += 1
        else:
            sys.stdout.write(' %s,\n' % (item,))
            count = 1
    if count != 1:
        sys.stdout.write('\n')
    sys.stdout.write('};\n')

def print_alias_table(atype, name, values):
    n = len(values)
    sys.stdout.write(
        '%s vtkDICOMCharacterSet::%s[%d] = {\n' % (atype, name, n))
    line = ''
    for value in values:
        if isinstance(value, str):
            item = ' \"' + value + '\",'
        else:
            item = ' ' + str(value) + ','
        if len(line) + len(item) > 74:
            sys.stdout.write(' ' + line + '\n')
            line = ''
        line += item
    if line:
        sys.stdout.write(' ' + line + '\n')
    sys.stdout.write('};\n')

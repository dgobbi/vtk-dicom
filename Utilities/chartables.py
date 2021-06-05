"""
Generate C++ character set conversion tables.

This script takes the conversion tables from https://encoding.spec.whatwg.org
as its input, performs some tweaks, and generates forward and reverse
compressed conversion tables.

For conversions in both directions, the code 0xFFFD will indicate a failed
character conversion. See http://www.unicode.org/faq/unsup_char.html

As of yet, this code doesn't provide generic replacements when converting
from unicode (e.g. whitespace of any kind could becomes "space" in the
target encoding) or generic removals (soft hyphen, word joiners, zero-width
space, variation selectors).  These could be handled in the following manner:
If the table produces the replacement character, then the input unicode could
be checked to see if it fits into one of the above categories, and the
appropriate action could be taken.
"""

import bisect
import sys
import string

# replacement character
RCHAR = 0xFFFD

# convenient constants for forward vs. reverse encoding
Forward = False
Reverse = True

# interesting unicode ranges
cjk_punct = [0x3000,0x301F]      # common cjk punctuation
cjk_kana = [0x3041,0x30FF]       # japanese kana blocks
cjk_punct_kana = [0x3000,0x30FF] # puct and kana as one big block
cjk_unified = [0x4E00,0x9FFF]    # cjk unified ideographs
kr_hangul = [0xAC00,0xD7A3]      # korean hangul block

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
        if not d.has_key(c):
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
                print "zerofail", i,c,hex(k)
        elif i != c:
            print "matchfail", i,c,hex(k)
    for d in dicts:
        for k,i in d.items():
            c = searchtable(table, k)
            if k == 0xFFFD:
                if c != RCHAR:
                    print "zerofail", i,c,hex(k)
            elif i != c:
                print "matchfail", i,c,hex(k)


header = \
"""/*=========================================================================
This is an automatically generated file.  Include errata for any changes.
=========================================================================*/"""

sys.stdout.write(header)
sys.stdout.write('\n\n')
sys.stdout.write('#include "vtkDICOMCharacterSetTables.h"\n')
sys.stdout.write('\n')

# ----
# ASCII
# ----

ascii = list(range(0,128))

table = [1] + maketable2(ascii, Forward, maxin=255)
checktable(table, Forward, ascii)
CodePageASCII = table

table = [1] + maketable2(ascii, Reverse)
checktable(table, Reverse, ascii)
CodePageASCII_R = table

sys.stdout.write("// %s\n" % ("ASCII",))
printtable("CodePageASCII", CodePageASCII, Forward, maxin=255)
sys.stdout.write('\n')
sys.stdout.write('// Reverse\n')
printtable("CodePageASCII_R", CodePageASCII_R, Reverse)
sys.stdout.write('\n')

# ----
# JIS X 0201
# ----

j0201 = list(range(0,161)) + list(range(0xFF61,0xFFA0)) + [RCHAR]*32
j0201[ord('\\')] = 0xA5
j0201[ord('~')] = 0x203E
j0201_compat = {
  # allow conversion of backslash, tilde to yen, macron
  ord('\\') : ord('\\'), ord('~') : ord('~'),
}
# allow fullwidth -> halfwidth conversion
for x,u in readdict('whatwg/index-iso-2022-jp-katakana.txt').items():
    j0201_compat[u] = 161 + x
for x in range(94):
    j0201_compat[0xFF01 + x] = 33 + x
j0201_compat[0xFFE3] = 126 # FULLWIDTH MACRON
j0201_compat[0xFFE5] = 92 # FULLWIDTH YEN
j0201_compat[0x3000] = 32 # IDEOGRAPHIC SPACE

table = maketable2(j0201, Forward, maxrun=1, maxin=255)
checktable(table, Forward, j0201)
CodePageJISX0201 = table

table = maketable2(j0201, Reverse, j0201_compat, maxrun=16)
checktable(table, Reverse, j0201)
CodePageJISX0201_R = table

sys.stdout.write("// %s\n" % ("JIS X 0201",))
printtable("CodePageJISX0201", CodePageJISX0201, Forward, maxin=255)
sys.stdout.write('\n')
sys.stdout.write('// Reverse\n')
printtable("CodePageJISX0201_R", CodePageJISX0201_R, Reverse)
sys.stdout.write('\n')


# ----
# ISO 8859 Code Pages
# ----

ISO8859 = {}
CodePageISO8859 = {}
CodePageISO8859_R = {}
comment = {
  1 : "Latin1, Western Europe",
  2 : "Latin2, Central Europe",
  3 : "Latin3, Maltese",
  4 : "Latin4, Northern Europe",
  5 : "Cyrillic",
  6 : "Arabic",
  7 : "Greek",
  8 : "Hebrew",
  9 : "Latin5, Turkish",
  10: "Latin6, Nordic Europe",
  11: "Thai, from TIS-620",
  13: "Latin7, Baltic Rim",
  14: "Latin8, Celtic",
  15: "Latin9, Euro 1",
  16: "Latin10, Euro 2",
}

for i in [1,2,3,4,5,6,7,8,9,10,11,13,14,15,16]:
    if i == 1:
        ISO8859[i] = list(range(0,256))
    elif i == 9:
        ISO8859[i] = (list(range(0,160)) +
                      readtable('whatwg/index-windows-1254.txt')[32:])
    elif i == 11:
        ISO8859[i] = (list(range(0,160)) +
                      readtable('whatwg/index-windows-874.txt')[32:])
    else:
        ISO8859[i] = (list(range(0,128)) +
                      readtable('whatwg/index-iso-8859-%d.txt' % (i,)))

    if i in [2, 3, 4, 10, 13, 14, 16]:
        table = maketable2(ISO8859[i], Forward, [160,255], maxin=255)
    else:
        table = maketable2(ISO8859[i], Forward, maxrun=1, maxin=255)
    table[0] += 1
    table.insert(1, 0)
    checktable(table, Forward, ISO8859[i])
    CodePageISO8859[i] = table

    if i in [2, 3, 4, 10, 13, 14, 16]:
        table = maketable2(ISO8859[i], Reverse, maxrun=16) #[0xA7,0x17E])
    else:
        table = maketable2(ISO8859[i], Reverse, maxrun=1)
    table[0] += 1
    table.insert(1, 0)
    checktable(table, Reverse, ISO8859[i])
    CodePageISO8859_R[i] = table

    sys.stdout.write("// %s\n" % (comment[i],))
    printtable("CodePageISO8859_%d"%(i,), CodePageISO8859[i], Forward, maxin=255)
    sys.stdout.write('\n')
    sys.stdout.write('// Reverse\n')
    printtable("CodePageISO8859_%d_R"%(i,), CodePageISO8859_R[i], Reverse)
    sys.stdout.write('\n')

# ----
# Encodings of Korean
# ----

euckr = readdict('whatwg/index-euc-kr.txt')
KSX1001 = [RCHAR]*(8836 + 8822)
for x in range(0x81,0xFF):
    for y in range(0x41,0xFF):
        i = None
        if x >= 0xA1 and y >= 0xA1:
            i = (x-0xA1)*94 + (y-0xA1)
        elif (y >= 0x41 and y <= 0x5A) or (y >= 0x61 and y <= 0x7A) or y >= 0x81:
            a = x - 0x81
            b = y - 0x41
            if b >= 26:
                b -= 6
                if b >= 52:
                    b -= 6
            if a < 32:
                i = 8836 + a*178 + b
            else:
                i = 8836 + 3008 + a*84 + b
        j = (x-0x81)*190 + (y-0x41)
        try:
            KSX1001[i] = euckr[j]
        except KeyError:
            pass

table = maketable2(KSX1001, Forward, [0,163], [1410,3759])
# [0,163], [1410,3759], [3854,8741], [8836,17657])
checktable(table, Forward, KSX1001)
CodePageKSX1001 = table

table = maketable2(KSX1001, Reverse, cjk_punct, kr_hangul)
checktable(table, Reverse, KSX1001)
CodePageKSX1001_R = table

sys.stdout.write("// Korean KS X 1001:1998")
sys.stdout.write("(codes over 8836 are for CP949 compatibility)\n")
printtable("CodePageKSX1001", CodePageKSX1001, Forward)
sys.stdout.write('\n')
sys.stdout.write('// Reverse\n')
printtable("CodePageKSX1001_R", CodePageKSX1001_R, Reverse)
sys.stdout.write('\n')

# ----
# Encodings of Simplified Chinese
# ----

# For reference: C++ code to decode GBK so GB2312 comes first
"""
  if (a < 0xA1)
  {
    if (b > 0x7F) { b--; }
    a = (a - 0x81)*190 + (b - 0x40) + 8836;
  }
  else if (b < 0xA1)
  {
    if (b > 0x7F) { b--; }
    a = (a - 0xA1)*96 + (b - 0x40) + 8836 + 6080;
  }
  else
  {
    // GB2312
    a = (a - 0xA1)*94 + (b - 0xA1);
  }
"""

# Also use this table for GBK and GB2312
GB18030 = readtable('whatwg/index-gb18030.txt')
# Fix difference between whatwg table and official table
GB18030[6555] = 0xE5E5 # 0x3000, ideographic space (duplicate)
# Change GB18030-2005 to GB18030-2000 (DICOM uses GB18030-2000)
GB18030[7533] = 0xE7C7 # 0x1E3F

# Reorganize the 23940 codes so that GB2312 codes come first, this allows
# us to use the first 8836 entries as a GB2312 table.
GB2312 = []
block2 = list(GB18030[0:6080])
block3 = []
for i in range(6080,6080+190*94,190):
    block3 += GB18030[i:i+96]
    GB2312 += GB18030[i+96:i+190]

GB18030 = GB2312 + block2 + block3

# Add all linear mappings within the BMP to our GB18030 table
LinearGB18030 = readlinear('whatwg/index-gb18030-ranges.txt')
for i in range(0,len(LinearGB18030)-2,2):
    x1 = LinearGB18030[i]
    y = LinearGB18030[i+1]
    x2 = min(LinearGB18030[i+2], 39420)
    GB18030 += list(range(y,y+(x2-x1)))

# For Unicode to GBK mapping, ensure compatibility with the GBK mappings
# that pre-date the GB18030-2000 standard, as described in this table:
gbk_compat = {
    # Compatibility mapping - m with acute
    0x1E3F : 7533,
    # PUA mappings (2) in GB2312
    0xE7C7 : 7533, 0xE7C8 : 7536,
    # PUA mappings (13) in GBK - ideographic description characters
    0xE7E7 : 7672, 0xE7E8 : 7673, 0xE7E9 : 7674, 0xE7EA : 7675, 0xE7EB : 7676,
    0xE7EC : 7677, 0xE7ED : 7678, 0xE7EE : 7679, 0xE7EF : 7680, 0xE7F0 : 7681,
    0xE7F1 : 7682, 0xE7F2 : 7683, 0xE7F3 : 7684,
    # PUA mappings (80) in GBK - various radicals and ideographs
    0xE815 :23766, 0xE816 :23767, 0xE817 :23768, 0xE818 :23769, 0xE819 :23770,
    0xE81A :23771, 0xE81B :23772, 0xE81C :23773, 0xE81D :23774, 0xE81E :23775,
    0xE81F :23776, 0xE820 :23777, 0xE821 :23778, 0xE822 :23779, 0xE823 :23780,
    0xE824 :23781, 0xE825 :23782, 0xE826 :23783, 0xE827 :23784, 0xE828 :23785,
    0xE829 :23786, 0xE82A :23787, 0xE82B :23788, 0xE82C :23789, 0xE82D :23790,
    0xE82E :23791, 0xE82F :23792, 0xE830 :23793, 0xE831 :23794, 0xE832 :23795,
    0xE833 :23796, 0xE834 :23797, 0xE835 :23798, 0xE836 :23799, 0xE837 :23800,
    0xE838 :23801, 0xE839 :23802, 0xE83A :23803, 0xE83B :23804, 0xE83C :23805,
    0xE83D :23806, 0xE83E :23807, 0xE83F :23808, 0xE840 :23809, 0xE841 :23810,
    0xE842 :23811, 0xE843 :23812, 0xE844 :23813, 0xE845 :23814, 0xE846 :23815,
    0xE847 :23816, 0xE848 :23817, 0xE849 :23818, 0xE84A :23819, 0xE84B :23820,
    0xE84C :23821, 0xE84D :23822, 0xE84E :23823, 0xE84F :23824, 0xE850 :23825,
    0xE851 :23826, 0xE852 :23827, 0xE853 :23828, 0xE854 :23829, 0xE855 :23830,
    0xE856 :23831, 0xE857 :23832, 0xE858 :23833, 0xE859 :23834, 0xE85A :23835,
    0xE85B :23836, 0xE85C :23837, 0xE85D :23838, 0xE85E :23839, 0xE85F :23840,
    0xE860 :23841, 0xE861 :23842, 0xE862 :23843, 0xE863 :23844, 0xE864 :23845,
    # Compatibility mappings (8) not present in GB18030
    0x9FB4 :23775, 0x9FB5 :23783, 0x9FB6 :23788, 0x9FB7 :23789, 0x9FB8 :23795,
    0x9FB9 :23812, 0x9FBA :23829, 0x9FBB :23845,
    # Vertical punctuation (10) within GB2312 range
    0xFE10 : 7182, 0xFE11 : 7183, 0xFE12 : 7184, 0xFE13 : 7185, 0xFE14 : 7186,
    0xFE15 : 7187, 0xFE16 : 7188, 0xFE17 : 7189, 0xFE18 : 7190, 0xFE19 : 7191,
    # Points beyond the BMP (6)
    #0x20087 : 23767, 0x20089 : 23768, 0x200CC : 23769, 0x215D7 : 23794,
    #0x2298F : 23804, 0x241FE : 23830,
}

# re-number GBK codes in the above so that GB2312 comes first
for k in gbk_compat.keys():
    v = gbk_compat[k]
    (a,b) = (v/190,v%190)
    if a < 32:
        v += 8836 # make room for GB2312
    elif b < 96:
        v = 8836 + 6080 + (a-32)*96 + b
    else:
        v = (a-32)*94 + (b-96)
    gbk_compat[k] = v

GBKCOMPAT=[RCHAR]*(1 + max(gbk_compat.keys()))
table = maketable2(GBKCOMPAT, Reverse, gbk_compat)
GBKCompatTable = table

def removesegs(table, x, y=0):
    """Remove the final segments from a table, to allow mapping of
    replacement code 0xFFFD as if it were a normal code."""
    m = table[0] + 1
    n = table[m]
    table[m] = n-x
    m += 1
    table[m+n-x-y:m+n-y] = []
    table[m+2*(n-x)-y:m+n-x+n-y] = []
    table[m+3*(n-x)-y:m+2*(n-x)+n-y] = []

table = maketable2(GB18030, Forward, [0,93], [1410,8177])
checktable(table, 0, GB18030)
removesegs(table, 2, 1)
CodePageGB18030 = table

# for compatibility with GBK 1.0, be sure to map old GBK PUA codes
table = maketable2(GB18030, Reverse, cjk_punct, cjk_unified)
checktable(table, 1, GB18030)
removesegs(table, 2)
CodePageGB18030_R = table

sys.stdout.write("// Simplified Chinese GB18030-2000\n")
printtable("CodePageGB18030", CodePageGB18030, Forward)
sys.stdout.write('\n')
sys.stdout.write('// Reverse\n')
printtable("CodePageGB18030_R", CodePageGB18030_R, Reverse)
sys.stdout.write('\n')
sys.stdout.write('// Compatibility overlay for GBK and GB2312\n')
printtable("CodePageGBK_R", GBKCompatTable, Reverse)
sys.stdout.write('\n')

# ----
# Encodings of Japanese
# ----

JISX0208 = readtable('whatwg/index-jis0208.txt')
JISX0208[8836:10716] = range(0xE000,0xE000+(10716-8836)) # EUDC
JISX0208[16] = 0xFFE3 # FULLWIDTH MACRON
JISX0208[28] = 0x2014 # EM DASH
JISX0208[31] = 0xFF3C # FULLWIDTH REVERSE SOLIDUS
JISX0208[32] = 0x301C # WAVE DASH
JISX0208[33] = 0x2016 # DOUBLE VERTICAL LINE
JISX0208[60] = 0x2212 # MINUS SIGN
JISX0208[78] = 0xFFE5 # FULLWIDTH YEN SIGN
JISX0208[80] = 0x00A2 # CENT SIGN
JISX0208[81] = 0x00A3 # POUND SIGN
JISX0208[137] = 0x00AC # NOT SIGN

JISX0212 = readtable('whatwg/index-jis0212.txt')
JISX0212[116] = 0xFF5E # FULLWIDTH TILDE
JISX0212[128] = 0x00A6 # BROKEN BAR

JISX02XX = JISX0208[0:8836] + JISX0212
# remove NEC extensions
JISX02XX[12*94:13*94] = [RCHAR]*94
JISX02XX[88*94:92*94] = [RCHAR]*(94*4)

# The FULLWIDTH TILDE is a problem, because it can map either to
# JIS X 0208 or JIS X 0212, and the former is preferred for CP932.
# Also note that for CP932, PUA 0xE000 to 0xE757 (1880 points) should
# map to the space between the JIS X 0208 table and the CP932 extensions.
# ( also see http://www.unicode.org/L2/L2014/14198-wave-dash.pdf )
j_compat = {
    0xFFE3 : 16, # FULLWIDTH MACRON
    0x203E : 16, # OVERLINE (jisx0213)
    0x2014 : 28, # EM DASH
    0x2015 : 28, # HORIZONTAL BAR
    0xFF3C : 31, # FULLWIDTH REVERSE SOLIDUS
    0x005C : 31, # REVERSE SOLIDUS (jisx0201 compatibility)
    0x301C : 32, # WAVE DASH
    # 0xFF5E : 32, # FULLWIDTH TILDE (cp932)
    0x2016 : 33, # DOUBLE VERTICAL LINE
    0x2225 : 33, # PARALLEL TO (cp932)
    0x2212 : 60, # MINUS SIGN
    0xFF0D : 60, # FULLWIDTH HYPHEN-MINUS (cp932)
    0xFFE5 : 78, # FULLWIDTH YEN SIGN
    0x00A5 : 78, # YEN SIGN (jisx0213)
    0x00A2 : 80, # CENT SIGN
    0xFFE0 : 80, # FULLWIDTH CENT SIGN (cp932)
    0x00A3 : 81, # POUND SIGN
    0xFFE1 : 81, # FULLWIDTH POUND SIGN (cp932)
    0x00AC : 137, # NOT SIGN
    0xFFE2 : 137, # FULLWIDTH NOT SIGN (cp932)
    0x007E : 8952, # TILDE (jisx0201 compatibility)
    0xFFE4 : 8964, # FULLWIDTH BROKEN BAR
    0x525D : 3648, # U+5265 (jouyou kanji compatibility)
    # 0x20B9F : 2561, # U+53F1 (jouyou kanji compatibility)
}

# make a reversible table for CP932
JISX0208_R = ([RCHAR]*(94*12) + JISX0208[12*94:13*94] +
              [RCHAR]*(94*75) + JISX0208[88*94:94*94] +
              range(0xE000,0xE758))
JISX0208_R[32] = 0xFF5E # FULLWIDTH TILDE (in JIS0212)
# remove duplicate mappings
JISX0208_R[1207] = RCHAR # 159 0x2252
JISX0208_R[1208] = RCHAR # 158 0x2261
JISX0208_R[1209] = RCHAR # 166 0x222b
JISX0208_R[1212] = RCHAR # 162 0x221a
JISX0208_R[1213] = RCHAR # 154 0x22a5
JISX0208_R[1214] = RCHAR # 153 0x2220
JISX0208_R[1217] = RCHAR # 165 0x2235
JISX0208_R[1218] = RCHAR # 126 0x2229
JISX0208_R[1219] = RCHAR # 125 0x222a
# the following jouyou kanji have compatibility mappings for JISX0208
JISX0208_R[3405] = 0x5861 # U+586B (in JIS0212)
JISX0208_R[3990] = 0x9830 # U+982C (in JIS0212)
# map halfwidth kana to fullwidth
for x,u in readdict('whatwg/index-iso-2022-jp-katakana.txt').items():
     if u <= 0x3002:
         JISX0208_R[u - 0x3000] = 0xFF61 + x
     elif u <= 0x300D:
         JISX0208_R[u - 0x300C + 53] = 0xFF61 + x
     elif u <= 0x309C:
         JISX0208_R[u - 0x309B + 10] = 0xFF61 + x
     elif u == 0x30FB:
         JISX0208_R[u - 0x30FB + 5] = 0xFF61 + x
     elif u == 0x30FC:
         JISX0208_R[u - 0x30FC + 27] = 0xFF61 + x
     else:
         JISX0208_R[u - 0x30A1 + 376] = 0xFF61 + x

table = maketable2(JISX0208_R, Reverse, maxrun=2)
checktable(table, Reverse, JISX0208_R)
CodePageJISX0208_R = table

# more finicky details: half-width katakana to full-width if JISX0201 is
# not available, full-width katakana to half-width if only JISX0201

table = maketable2(JISX0208, Forward, [0,689], [1410,7807])
checktable(table, Forward, JISX0208)
CodePageJISX0208 = table

table = maketable2(JISX0212, Forward, [1410, 7210])
checktable(table, Forward, JISX0212)
CodePageJISX0212 = table

table = maketable2(JISX02XX, Reverse, cjk_punct_kana, cjk_unified, j_compat)
checktable(table, Reverse, JISX02XX, j_compat)
CodePageJISX_R = table

sys.stdout.write("// Japanese JIS X 0208, plus CP932 compatibility\n")
printtable("CodePageJISX0208", CodePageJISX0208, Forward)
sys.stdout.write('\n')
sys.stdout.write("// Japanese JIS X 0212\n")
printtable("CodePageJISX0212", CodePageJISX0212, Forward)
sys.stdout.write('\n')
sys.stdout.write('// Reverse (values >= 8836 are JIS X 0212)\n')
printtable("CodePageJISX_R", CodePageJISX_R, Reverse)
sys.stdout.write('\n')
sys.stdout.write('// Reverse table overlay with CP932 extensions\n')
printtable("CodePageJISX0208_R", CodePageJISX0208_R, Reverse)
sys.stdout.write('\n')

# ----
# Encodings of Traditional Chinese
# ----

# Read Big5, keep ETEN but ignore HKSCS
# (ETEN adds 408 chars including japanese, cyrillic)
BIG5_HKSCS = readtable('whatwg/index-big5.txt')
BIG5_PRIV1 = list(range(0xEEB8,0xF6B1)) # CP950 compatibility
BIG5_PRIV2 = list(range(0xE311,0xEEB8)) # CP950 compatibility
BIG5_PRIV4 = list(range(0xE000,0xE311)) # CP950 compatibility
BIG5 = BIG5_PRIV1 + BIG5_PRIV2 + BIG5_HKSCS[5024:18997] + BIG5_PRIV4
# These codes in ETEN block map outside BMP, replace with private codes
BIG5[11205] = 0xF7E6 # 0x200CC
BIG5[11207] = 0xF7E8 # 0x2008A
BIG5[11213] = 0xF7EE # 0x27607
# For CP950 compatibility, fill unused slots with EUDC
for i in range(10896,11304):
    if BIG5[i] == 0xFFFD:
        BIG5[i] = i - 10896 + 0xF6B1

# Duplicates must be removed from table before inverting it
BIG5_R = list(BIG5)
# Replace with hangzhou digits from Unicode 3.0
BIG5_R[5287] = 0x3038 # 5512 0x5341
BIG5_R[5288] = 0x3039 # None 0x5344
BIG5_R[5289] = 0x303A # 5599 0x5345
# Remove duplicate cjk characters in ETEN
BIG5_R[10957] = 0xFFFD # 5104 0x3003 (DITTO MARK)
BIG5_R[10958] = 0xFFFD # 11345 0x4edd (ideographic ditto)
# Remove duplicate box-drawing characters
BIG5_R[18975] = 0xFFFD # 5248 0x255e
BIG5_R[18976] = 0xFFFD # 5249 0x256a
BIG5_R[18977] = 0xFFFD # 5250 0x2561
BIG5_R[18991] = 0xFFFD # 5247 0x2550
BIG5_R[18992] = 0xFFFD # 5243 0x256d
BIG5_R[18993] = 0xFFFD # 5244 0x256e
BIG5_R[18994] = 0xFFFD # 5245 0x2570
BIG5_R[18995] = 0xFFFD # 5246 0x256f

# For Unicode to Big5 mapping, we want to provide compatibility with
# various look-alike (or functionally equivalent) characters.  This is
# particularly important because there is so much historic variability
# among the various Big5 and CNS-11643 character tables.
big5_compat = {
    0x00A2 : 5187, # CENT SIGN (map to FULLWIDTH CENT SIGN)
    0x00A3 : 5188, # POUND SIGN (map to FULLWIDTH POUND SIGN)
    0x00A5 : 5185, # YEN SIGN (map to FULLWIDTH YEN SIGN)
    0x2015 : 5046, # HORIZONTAL BAR (map to EN DASH)
    0x2016 : 5178, # DOUBLE VERTICAL LINE (map to PARALLEL TO)
    0x2022 : 5029, # BULLET (map to HYPHENATION POINT)
    0x203E : 5120, # OVERLINE (map to MACRON)
    0x2044 : 5180, # FRACTION SLASH (map to FULLWIDTH SOLIDUS)
    0x223C : 5153, # TILDE OPERATOR (map to FULLWIDTH TILDE)
    0x2609 : 5169, # SUN (map to CIRCLED DOT OPERATOR)
    0x2641 : 5168, # EARTH (map to CIRCLED PLUS)
    0x2733 : 5101, # EIGHT SPOKED ASTERISK (map to FULLWIDTH ASTERISK)
    0x2E9F : 5746, # CJK RADICAL MOTHER (map to look-alike 0x6BCD)
    0x301C : 5153, # WAVE DASH (map to FULLWIDTH TILDE)
    0x3036 : 5186, # CIRCLED POSTAL MARK (map to POSTAL MARK)
    0x3038 : 5287, # HANGZHOU NUMERAL 10 (map to look-alike 0x5341)
    0x3039 : 5288, # HANGZHOU NUMERAL 20 (map to look-alike 0x5344)
    0x303A : 5289, # HANGZHOU NUMERAL 30 (map to look-alike 0x5345)
    0x30FB : 5029, # KATAKANA MIDDLE DOT (map to HYPHENATION POINT)
    0x5344 : 5288, # CJK UNIFIED IDEOGRAPH (map to look-alike numeral)
    0x5F5E : 10226, # CJK IDEOGRAPH (map to variant 0x5F5D)
    0xFE58 : 5048, # SMALL EM DASH (map to EM DASH)
}
# compatibility for CP950 private codes
for i in range(10896,11304):
    big5_compat[i - 10896 + 0xF6B1] = i

table = maketable2(BIG5, 0)
checktable(table, 0, BIG5)
CodePageBig5 = table

table = maketable2(BIG5_R, 1, cjk_punct, cjk_unified, big5_compat)
checktable(table, 1, BIG5_R, big5_compat)
CodePageBig5_R = table

sys.stdout.write("// Traditional Chinese Big5 with ETEN extensions\n")
sys.stdout.write("// Needs special handling for ETEN outside BMP:\n")
sys.stdout.write("// 11205 -> 0x200CC, 11207 -> 0x2008A, 11213 -> 0x27607\n")
printtable("CodePageBig5", CodePageBig5, Forward)
sys.stdout.write('\n')
sys.stdout.write('// Reverse\n')
printtable("CodePageBig5_R", CodePageBig5_R, Reverse)
sys.stdout.write('\n')

# ----
# Windows Code Pages
# ----

CP = {}
CodePageWindows = {}
CodePageWindows_R = {}
comment = {
  874 : "Windows Thai, extends iso-8859-11",
  1250: "Windows Central Europe",
  1251: "Windows Cyrillic",
  1252: "Windows Latin1, extents iso-8859-1",
  1253: "Windows Greek",
  1254: "Windows Turkish, extents iso-8859-9",
  1255: "Windows Hebrew",
  1256: "Windows Arabic",
  1257: "Windows Baltic Rim",
}

for i in [874,1250,1251,1252,1253,1254,1255,1256,1257]:
    CP[i] = (list(range(0,128)) +
             readtable('whatwg/index-windows-%d.txt' % (i,)))

    if i in [1254]:
        table = maketable2(CP[i], Forward, [128,159], maxrun=1, maxin=255)
        table = [0] + table[2:]
    elif i in [1255]:
        table = maketable2(CP[i], Forward, [128,191], maxrun=1, maxin=255)
        table = [0] + table[2:]
    else:
        table = maketable2(CP[i], Forward, maxrun=16, maxin=255)
    table[0] += 1
    table.insert(1, 0)
    checktable(table, Forward, CP[i])
    CodePageWindows[i] = table

    table = maketable2(CP[i], Reverse, maxrun=16)
    table[0] += 1
    table.insert(1, 0)
    checktable(table, Reverse, CP[i])
    CodePageWindows_R[i] = table

    sys.stdout.write("// %s\n" % (comment[i],))
    printtable("CodePageWindows%d"%(i,), CodePageWindows[i], Forward, maxin=255)
    sys.stdout.write('\n')
    sys.stdout.write('// Reverse\n')
    printtable("CodePageWindows%d_R"%(i,), CodePageWindows_R[i], Reverse)
    sys.stdout.write('\n')

# ----
# KOI8 Code Pages
# ----

KOI8 = (list(range(0,128)) +
         readtable('whatwg/index-koi8-u.txt'))
# remove all non-alphabetic characters except nbsp, interpunct, copyright
for i in range(0x80,0xC0):
    if KOI8[i] < 0x400 or KOI8[i] >= 0x500:
        if KOI8[i] not in [0xA0,0xA9,0xB7]:
            KOI8[i] = RCHAR

ftable = maketable2(KOI8, Forward, [160,255], maxin=255)
ftable[0] += 1
ftable.insert(1, 0)
checktable(ftable, Forward, KOI8)

rtable = maketable2(KOI8, Reverse, [0x0400,0x0491])
rtable[0] += 1
rtable.insert(1, 0)
checktable(rtable, Reverse, KOI8)

sys.stdout.write("// koi8 with extra cyrillic letters from koi8-ru\n")
printtable("CodePageKOI8", ftable, Forward, maxin=255)
sys.stdout.write('\n')
sys.stdout.write('// Reverse\n')
printtable("CodePageKOI8_R", rtable, Reverse)
sys.stdout.write('\n')

# this must be consistent with the enum in vtkDICOMCharacterSet.h
ISO_2022   = 32
ISO_IR_6   = 0  # US_ASCII
ISO_IR_13  = 1  # JIS X 0201,  japanese romaji + katakana
ISO_IR_100 = 8  # ISO-8859-1,  latin1, western europe
ISO_IR_101 = 9  # ISO-8859-2,  latin2, central europe
ISO_IR_109 = 10 # ISO-8859-3,  latin3, maltese
ISO_IR_110 = 11 # ISO-8859-4,  latin4, baltic
ISO_IR_144 = 12 # ISO-8859-5,  cyrillic
ISO_IR_127 = 13 # ISO-8859-6,  arabic
ISO_IR_126 = 14 # ISO-8859-7,  greek
ISO_IR_138 = 15 # ISO-8859-8,  hebrew
ISO_IR_148 = 16 # ISO-8859-9,  latin5, turkish
X_LATIN6   = 17 # ISO-8859-10, latin6, nordic
ISO_IR_166 = 18 # ISO-8859-11, thai
X_LATIN7   = 19 # ISO-8859-13, latin7, baltic rim
X_LATIN8   = 20 # ISO-8859-14, latin8, celtic
X_LATIN9   = 21 # ISO-8859-15, latin9, western europe
X_LATIN10  = 22 # ISO-8859-16, latin10, southeastern europe
X_EUCKR    = 24 # euc-kr,      ISO_IR_149 without escape codes
X_GB2312   = 25 # gb2312,      ISO_IR_58 without escape codes
ISO_2022_IR_6   = 32 # US_ASCII
ISO_2022_IR_13  = 33 # JIS X 0201,  japanese katakana
ISO_2022_IR_87  = 34 # JIS X 0208,  japanese 94x94 primary
ISO_2022_IR_159 = 36 # JIS X 0212,  japanese 94x94 secondary
ISO_2022_IR_100 = 40 # ISO-8859-1,  latin1, western europe
ISO_2022_IR_101 = 41 # ISO-8859-2,  latin2, central europe
ISO_2022_IR_109 = 42 # ISO-8859-3,  latin3, maltese
ISO_2022_IR_110 = 43 # ISO-8859-4,  latin4, baltic
ISO_2022_IR_144 = 44 # ISO-8859-5,  cyrillic
ISO_2022_IR_127 = 45 # ISO-8859-6,  arabic
ISO_2022_IR_126 = 46 # ISO-8859-7,  greek
ISO_2022_IR_138 = 47 # ISO-8859-8,  hebrew
ISO_2022_IR_148 = 48 # ISO-8859-9,  latin5, turkish
ISO_2022_IR_166 = 50 # ISO-8859-11, thai
ISO_2022_IR_149 = 56 # the KS X 1001 part of ISO-2022-KR
ISO_2022_IR_58  = 57 # the GB2312 part of ISO-2022-CN
ISO_IR_192 = 64 # UTF-8,       unicode
GB18030    = 65 # gb18030,     chinese with full unicode mapping
GBK        = 66 # gbk,         chinese
X_BIG5     = 67 # big5 + ETEN, traditional chinese
X_EUCJP    = 69 # euc-jp,      unix encoding for japanese
X_SJIS     = 70 # windows-31j, aka shift-jis, code page 932
X_CP874    = 76 # cp1162,      thai (windows-874)
X_CP1250   = 80 # cp1250,      central europe
X_CP1251   = 81 # cp1251,      cyrillic
X_CP1252   = 82 # cp1252,      western europe
X_CP1253   = 83 # cp1253,      greek
X_CP1254   = 84 # cp1254,      turkish
X_CP1255   = 85 # cp1255,      hebrew
X_CP1256   = 86 # cp1256,      arabic
X_CP1257   = 87 # cp1257,      baltic rim
X_KOI8     = 90 # koi,         cyrillic

pages = {
  ISO_IR_6 : ('CodePageASCII', 'CodePageASCII_R'),
  ISO_IR_13 : ('CodePageJISX0201', 'CodePageJISX0201_R'),
  ISO_IR_100 : ('CodePageISO8859_1', 'CodePageISO8859_1_R'),
  ISO_IR_101 : ('CodePageISO8859_2', 'CodePageISO8859_2_R'),
  ISO_IR_109 : ('CodePageISO8859_3', 'CodePageISO8859_3_R'),
  ISO_IR_110 : ('CodePageISO8859_4', 'CodePageISO8859_4_R'),
  ISO_IR_144 : ('CodePageISO8859_5', 'CodePageISO8859_5_R'),
  ISO_IR_127 : ('CodePageISO8859_6', 'CodePageISO8859_6_R'),
  ISO_IR_126 : ('CodePageISO8859_7', 'CodePageISO8859_7_R'),
  ISO_IR_138 : ('CodePageISO8859_8', 'CodePageISO8859_8_R'),
  ISO_IR_148 : ('CodePageISO8859_9', 'CodePageISO8859_9_R'),
  X_LATIN6 : ('CodePageISO8859_10', 'CodePageISO8859_10_R'),
  ISO_IR_166 : ('CodePageISO8859_11', 'CodePageISO8859_11_R'),
  X_LATIN7 : ('CodePageISO8859_13', 'CodePageISO8859_13_R'),
  X_LATIN8 : ('CodePageISO8859_14', 'CodePageISO8859_14_R'),
  X_LATIN9 : ('CodePageISO8859_15', 'CodePageISO8859_15_R'),
  X_LATIN10 : ('CodePageISO8859_16', 'CodePageISO8859_16_R'),
  X_EUCKR : ('CodePageKSX1001', 'CodePageKSX1001_R'),
  X_GB2312 : ('CodePageGB18030', 'CodePageGBK_R'),
  ISO_2022_IR_6 : ('CodePageASCII', 'CodePageASCII_R'),
  ISO_2022_IR_13 : ('CodePageJISX0201', 'CodePageJISX0201_R'),
  ISO_2022_IR_87 : ('CodePageJISX0208', 'CodePageJISX_R'),
  ISO_2022_IR_159 : ('CodePageJISX0212', 'CodePageJISX_R'),
  ISO_2022_IR_100 : ('CodePageISO8859_1', 'CodePageISO8859_1_R'),
  ISO_2022_IR_101 : ('CodePageISO8859_2', 'CodePageISO8859_2_R'),
  ISO_2022_IR_109 : ('CodePageISO8859_3', 'CodePageISO8859_3_R'),
  ISO_2022_IR_110 : ('CodePageISO8859_4', 'CodePageISO8859_4_R'),
  ISO_2022_IR_144 : ('CodePageISO8859_5', 'CodePageISO8859_5_R'),
  ISO_2022_IR_127 : ('CodePageISO8859_6', 'CodePageISO8859_6_R'),
  ISO_2022_IR_126 : ('CodePageISO8859_7', 'CodePageISO8859_7_R'),
  ISO_2022_IR_138 : ('CodePageISO8859_8', 'CodePageISO8859_8_R'),
  ISO_2022_IR_148 : ('CodePageISO8859_9', 'CodePageISO8859_9_R'),
  ISO_2022+X_LATIN6 : ('CodePageISO8859_10', 'CodePageISO8859_10_R'),
  ISO_2022_IR_166 : ('CodePageISO8859_11', 'CodePageISO8859_11_R'),
  ISO_2022+X_LATIN7 : ('CodePageISO8859_13', 'CodePageISO8859_13_R'),
  ISO_2022+X_LATIN8 : ('CodePageISO8859_14', 'CodePageISO8859_14_R'),
  ISO_2022+X_LATIN9 : ('CodePageISO8859_15', 'CodePageISO8859_15_R'),
  ISO_2022+X_LATIN10 : ('CodePageISO8859_16', 'CodePageISO8859_16_R'),
  ISO_2022_IR_149 : ('CodePageKSX1001', 'CodePageKSX1001_R'),
  ISO_2022_IR_58 : ('CodePageGB18030', 'CodePageGBK_R'),
  GB18030 : ('CodePageGB18030', 'CodePageGB18030_R'),
  GBK : ('CodePageGB18030', 'CodePageGBK_R'),
  X_BIG5 : ('CodePageBig5', 'CodePageBig5_R'),
  X_EUCJP : ('CodePageJISX0208', 'CodePageJISX_R'),
  X_SJIS : ('CodePageJISX0208', 'CodePageJISX0208_R'),
  X_CP874 : ('CodePageWindows874', 'CodePageWindows874_R'),
  X_CP1250 : ('CodePageWindows1250', 'CodePageWindows1250_R'),
  X_CP1251 : ('CodePageWindows1251', 'CodePageWindows1251_R'),
  X_CP1252 : ('CodePageWindows1252', 'CodePageWindows1252_R'),
  X_CP1253 : ('CodePageWindows1253', 'CodePageWindows1253_R'),
  X_CP1254 : ('CodePageWindows1254', 'CodePageWindows1254_R'),
  X_CP1255 : ('CodePageWindows1255', 'CodePageWindows1255_R'),
  X_CP1256 : ('CodePageWindows1256', 'CodePageWindows1256_R'),
  X_CP1257 : ('CodePageWindows1257', 'CodePageWindows1257_R'),
  X_KOI8 : ('CodePageKOI8', 'CodePageKOI8_R'),
}

table = [('0','0')]*256
for x,y in pages.items():
    table[x] = y

sys.stdout.write(
    'const unsigned short *vtkDICOMCharacterSet::Table[256] = {\n')
for l in table:
    sys.stdout.write('  %s,\n' % (l[0],))
sys.stdout.write('};\n\n')

sys.stdout.write(
    'const unsigned short *vtkDICOMCharacterSet::Reverse[256] = {\n')
for l in table:
    sys.stdout.write('  %s,\n' % (l[1],))
sys.stdout.write('};\n')

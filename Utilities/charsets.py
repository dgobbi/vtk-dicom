"""
This module is used by chartables.py, which generates compressed
tables for the character sets.  It lists the character sets and
their aliases.
"""

# This must be consistent with the enum in vtkDICOMCharacterSet.h
ISO_2022   = 32
ISO_IR_6   = 0  # US-ASCII
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
ISO_IR_203 = 21 # ISO-8859-15, latin9, western europe
X_LATIN10  = 22 # ISO-8859-16, latin10, southeastern europe
X_EUCKR    = 24 # euc-kr,      ISO_IR_149 without escape codes
X_GB2312   = 25 # gb2312,      ISO_IR_58 without escape codes
ISO_2022_IR_6   = 32 # US-ASCII
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
ISO_2022_IR_203 = 53 # ISO-8859-15, latin9, western europe
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
X_CP1258   = 88 # cp1258,      vietnamese
X_KOI8     = 90 # koi8-u,      cyrillic

# The aliases are taken mainly from IANA
aliases = {

ISO_IR_6 : (
  "ansi_x3.4-1968",
  "ansi_x3.4-1986",
  "ascii",
  "iso-ir-6",
  "iso646-us",
  "us-ascii",
  ),
ISO_IR_13 : (
  "iso-ir-13",
  "iso-ir-14",
  "jis_x0201",
  "x0201",
  ),
ISO_IR_100 : (
  "cp819",
  "csisolatin1",
  "ibm819",
  "iso-8859-1",
  "iso-ir-100",
  "iso8859-1",
  "iso88591",
  "iso_8859-1",
  "iso_8859-1:1987",
  "l1",
  "latin1",
  # documented but incorrect defined term
  "iso-ir 100",
  ),
ISO_IR_101 : (
  "csisolatin2",
  "iso-8859-2",
  "iso-ir-101",
  "iso8859-2",
  "iso88592",
  "iso_8859-2",
  "iso_8859-2:1987",
  "l2",
  "latin2",
  # documented but incorrect defined term
  "iso-ir 101",
  ),
ISO_IR_109 : (
  "csisolatin3",
  "iso-8859-3",
  "iso-ir-109",
  "iso8859-3",
  "iso88593",
  "iso_8859-3",
  "iso_8859-3:1988",
  "l3",
  "latin3",
  # documented but incorrect defined term
  "iso-ir 109",
  ),
ISO_IR_110 : (
  "csisolatin4",
  "iso-8859-4",
  "iso-ir-110",
  "iso8859-4",
  "iso88594",
  "iso_8859-4",
  "iso_8859-4:1988",
  "l4",
  "latin4",
  # documented but incorrect defined term
  "iso-ir 110",
  ),
ISO_IR_144 : (
  "csisolatincyrillic",
  "cyrillic",
  "iso-8859-5",
  "iso-ir-144",
  "iso8859-5",
  "iso88595",
  "iso_8859-5",
  "iso_8859-5:1988",
  # documented but incorrect defined term
  "iso-ir 144",
  ),
ISO_IR_127 : (
  "arabic",
  "asmo-708",
  "csiso88596e",
  "csiso88596i",
  "csisolatinarabic",
  "ecma-114",
  "iso-8859-6",
  "iso-8859-6-e",
  "iso-8859-6-i",
  "iso-ir-127",
  "iso8859-6",
  "iso88596",
  "iso_8859-6",
  "iso_8859-6:1987",
  # documented but incorrect defined term
  "iso-ir 127",
  ),
ISO_IR_126 : (
  "csisolatingreek",
  "ecma-118",
  "elot_928",
  "greek",
  "greek8",
  "iso-8859-7",
  "iso-ir-126",
  "iso8859-7",
  "iso88597",
  "iso_8859-7",
  "iso_8859-7:1987",
  "sun_eu_greek",
  # documented but incorrect defined term
  "iso-ir 126",
  ),
ISO_IR_138 : (
  "csiso88598e",
  "csisolatinhebrew",
  "hebrew",
  "iso-8859-8",
  "iso-8859-8-e",
  "iso-ir-138",
  "iso8859-8",
  "iso88598",
  "iso_8859-8",
  "iso_8859-8:1988",
  # documented but incorrect defined term
  "iso-ir 138",
  ),
ISO_IR_148 : (
  "csisolatin5",
  "iso-8859-9",
  "iso-ir-148",
  "iso8859-9",
  "iso88599",
  "iso_8859-9",
  "iso_8859-9:1989",
  "l5",
  "latin5",
  # documented but incorrect defined term
  "iso-ir 148",
  ),
X_LATIN6 : (
  "csisolatin6",
  "iso-8859-10",
  "iso-ir-157",
  "iso8859-10",
  "iso885910",
  "iso_8859-10",
  "l6",
  "latin6",
  ),
ISO_IR_166 : (
  "dos-874",
  "iso-8859-11",
  "iso-ir-166",
  "iso8859-11",
  "iso885911",
  "tis-620",
  ),
X_LATIN7 : (
  "csisolatin7",
  "iso-8859-13",
  "iso-ir-179",
  "iso8859-13",
  "iso885913",
  "iso_8859-13",
  "l7",
  "latin7",
  ),
X_LATIN8 : (
  "csisolatin8",
  "iso-8859-14",
  "iso-ir-199",
  "iso8859-14",
  "iso885914",
  "iso_8859-14",
  "l8",
  "latin8",
  ),
ISO_IR_203 : (
  "csisolatin9",
  "iso-8859-15",
  "iso-ir-203",
  "iso8859-15",
  "iso885915",
  "iso_8859-15",
  "l9",
  "latin9",
  ),
X_LATIN10 : (
  "csisolatin10",
  "iso-8859-16",
  "iso-ir-226",
  "iso8859-16",
  "iso885916",
  "iso_8859-16",
  "l10",
  "latin10",
  ),
X_EUCKR : (
  "cseuckr",
  "csksc56011987",
  "euc-kr",
  "korean",
  "ksc_5601",
  "ksc5601",
  "ks_c_5601-1987",
  "ks_c_5601-1989",
  "windows-949",
  ),
X_GB2312 : (
  "chinese",
  "csgb2312",
  "csiso58gb231280",
  "gb2312",
  "gb_2312",
  "gb_2312-80",
  ),
ISO_2022_IR_6 : (
  "iso-2022",
  ),
ISO_2022_IR_87 : (
  "csiso2022jp",
  "iso-2022-jp",
  "iso-ir-87",
  "iso2022_jp",
  "jis",
  ),
ISO_2022_IR_159 : (
  "iso-2022-jp-1",
  "iso-2022-jp-2",
  "iso-ir-159",
  "iso2022_jp_1",
  "iso2022_jp_2",
  ),
ISO_2022_IR_149 : (
  "iso-ir-149",
  ),
ISO_2022_IR_58 : (
  "iso-ir-58",
  # documented but incorrect defined term
  "iso 2022 gb2312",
  ),
ISO_IR_192: (
  "iso-ir-192",
  "unicode-1-1-utf-8",
  "utf-8",
  "utf8",
  # documented but incorrect defined term
  "iso 2022 ir 192",
  ),
GB18030 : (
  "gb18030",
  ),
GBK : (
  "gbk",
  "x-gbk",
  # documented but incorrect defined term
  "iso 2022 gbk",
  ),
X_BIG5 : (
  "b5",
  "big5",
  "big5-eten",
  "cn-big5",
  "csbig5",
  "x-x-big5",
  # documented but incorrect defined terms
  "iso 2022 b5",
  "iso 2022 big5",
  ),
X_EUCJP : (
  "cseucpkdfmtjapanese",
  "euc-jp",
  "x-euc-jp",
  ),
X_SJIS : (
  "csshiftjis",
  "ms932",
  "ms_kanji",
  "shift-jis",
  "shift_jis",
  "sjis",
  "windows-31j",
  "x-sjis",
  ),
X_CP874 : (
  "windows-874",
  ),
X_CP1250 : (
  "cp1250",
  "windows-1250",
  "x-cp1250",
  ),
X_CP1251 : (
  "cp1251",
  "windows-1251",
  "x-cp1251",
  ),
X_CP1252 : (
  "cp1252",
  "windows-1252",
  "x-cp1252",
  ),
X_CP1253 : (
  "cp1253",
  "windows-1253",
  "x-cp1253",
  ),
X_CP1254 : (
  "cp1254",
  "windows-1254",
  "x-cp1254",
  ),
X_CP1255 : (
  "cp1255",
  "windows-1255",
  "x-cp1255",
  ),
X_CP1256 : (
  "cp1256",
  "windows-1256",
  "x-cp1256",
  ),
X_CP1257 : (
  "cp1257",
  "windows-1257",
  "x-cp1257",
  ),
X_CP1258 : (
  "cp1258",
  "windows-1258",
  "x-cp1258",
  ),
X_KOI8 : (
  "koi",
  "koi8",
  "koi8-r",
  "koi8-ru",
  "koi8-u",
  ),
}

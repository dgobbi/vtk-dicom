## Character Sets {#characterset}

@brief Decoding and Encoding of Character Sets


## Overview

Even though it would be convenient for all DICOM files to store text
in UTF-8, or even ASCII, the reality is that legacy character encodings
are very common.  Also, it is not uncommon to find DICOM files where
the encoding does not conform perfectly with the standard.  As a general
rule, we want to be forgiving when decoding text in DICOM files, but
we want to conform strictly to the standard when encoding text.


## ASCII and ISO-8859

Many of the ISO-8859 character sets are supported (and extended) by
Microsoft code pages, and have become closely associated with those
code pages.  The most important of these is CP1252 (Windows-1252)
which extends ISO-8859-1 (ISO IR 100).  This code page replaces
C1 control codes, which are unused by the ISO-8859 character sets,
with commonly-used characters such the Euro sign, combined OE and oe,
and left and right quotes (single and double).

### Decoding

Our decoder supports the decoding of these extra code points when the
character set is ISO IR 100.  The rationale is that CP1252 is fully
backwards-compatible with ISO IR 100, and the C1 control codes are not
used by DICOM.  This same rule is applied for ISO IR 148 (via CP1254)
and ISO IR 166 (via CP874). ISO IR 6, however, is decoded strictly
as ASCII.

### Encoding

The extra characters that are supported by the decoder cannot also be
supported by the encoder, since that would create files that do not
conform with the DICOM standard.  Encoding is done strictly according
to the named character set.


## Japanese via ISO 2022

The use of iso-2022 escape sequences for the encoding of Japanese text,
referred to as "JIS encoding" began in 1978 and is still common (with
restrictions) in the form of iso-2022-jp.  DICOM's encoding of Japanese
is also based on JIS encoding, but with different restrictions.

DICOM iso-2022 Japanese differs from iso-2022-jp most significantly
in the optional inclusion, in DICOM, of ISO IR 13 in G1.  This is done
to support the use of half-width katakana in the traditional manner as
described in JIS X 0201 and as previously done in Japanese desktop
computing and industrial computing.  The Specific Character Set defined
term "ISO 2022 IR 13" indicates that the initial state of the decoder
will be ISO IR 14 in G0 and ISO IR 13 in G1.  In this usage, `ESC )I`
will re-designate ISO IR 13 to G1 (though "ISO 2022 IR 13" does not
permit any other character set in G1), and `ESC (J` will re-designate
ISO IR 14 to G0.

The use of ISO IR 13 (and ISO 2022 IR 13) in DICOM in Japan was common at
the turn of the century, but since then it has become increasingly rare.
On the other hand, ISO 2022 IR 87 (the JIS X 0208 character set) is still
used very widely.

### Decoding

Our decoder expands upon the JIS X 0208:1990 repertoire to include extra
characters defined in Microsoft CP932 (including the NEC extension).  If
the defined term ISO 2022 IR 13 is present, then JIS X 0201 is used as
the initial character set.

### Encoding

Encoding of ISO-2022 Japanese in DICOM is usually done with the following
defined terms for Specific Character Set:

1. ISO 2022 IR 13\ISO 2022 IR 87
2. \ISO 2022 IR 87
3. \ISO 2022 IR 87\ISO 2022 IR 159

Notes:

1. This generally implies iso-2022-jp, but requires the use of ISO IR 14
   instead of ASCII, and also requires the use of JIS X 0208:1990 rather than
   any other version (such as JIS X 0208:1978 or JIS X 0208:1983).  This
   provides exactly the same characters as classic shift-jis, with exactly
   the same method for encoding half-width katakana, but with a different
   way of encoding the JIS X 0208 characters.
2. This specifies the most widely used subset of iso-2022-jp, using only ASCII
   and JIS X 0208:1990.  For broad compatibility, this is the best option.
3. This specifies the most widely used subset of iso-2022-jp-2, like the above
   but adding JIS X 0212:1990 for additional characters.  Rarely used.

It is best to avoid the use of ISO 2022 IR 13 (and ISO IR 13), because
it requires ISO IR 14 (not ASCII) in G0, and because half-width katakana
have fallen out of use within the Japanese health care industry.  For (2)
and (3) above, when our encoder encounters half-width katakana, it will
convert them to full-width katakana for ISO 2022 IR 87. For (1), the
half-width katakana will be encoded as-is.

Regarding the structure of the ISO 2022 encoding, our encoder will always
switch G0 to ASCII (or ISO IR 14 if ISO IR 13 in in use) before any ASCII
character, including any control character except ESC.  This includes SPACE
and TAB as well as CR, NL, and FF.

Of course some tricky situations can arise when converting from UTF-8
to ISO 2022 Japanese, or even when converting from Windows CP932, which
contains characters not present in JIS X 0208 or JIS X 0212.  Firstly,
ISO 2022 IR 13 should only be used if half-width katakana are present
in the original text and cannot be avoided.  Secondly, it is important
to note that some characters might be converted to equivalents at
different code points in order to make them compatible with either
JIS X 0208 or JIS X 0212.

The following characters are considered to be compatible by our encoder,
and will be converted if necessary to fit them into an encoding:

1. MACRON and FULLWIDTH MACRON
2. OVERLINE and FULLWIDTH MACRON
3. YEN SIGN and FULLWIDTH YEN SIGN
4. CENT SIGN and FULLWIDTH CENT SIGN
5. POUND SIGN and FULLWIDTH POUND SIGN
6. MINUS SIGN and FULLWIDTH HYPHEN-MINUS
7. NOT SIGN and FULLWIDTH NOT SIGN
8. EM DASH and HORIZONTAL BAR
9. FULLWIDTH TILDE and WAVE DASH
10. PARALLEL TO and DOUBLE VERTICAL LINE


## Korean via ISO 2022

Outside of DICOM, ISO 2022 escape sequences are generally not used in
encodings of Korean.  In fact, the euc-kr encoding is identical to DICOM's
Korean encoding except that it lacks the escape sequences.  Conversely,
DICOM requires the escape sequence `ESC $)C` at the beginning of every
line of text that contains Korean characters.

### Decoding

Though required by the DICOM standard, the escape sequences are not present
in all Korean DICOM files.  Therefore, our decoder will simply remove the
escape sequence wherever it is found, and decode the text using Microsoft
CP949 (which is backwards compatible with euc-kr, which in turn is identical
to DICOM ISO 2022 IR 149 except for the escape sequences).  As compared to
euc-kr, CP949 contains thousands of additional characters.

As well, KS X 1001 (and ISO IR 149) permit Hangul to be stored using 8-byte
codes rather than 2-byte codes.  This eight-byte code stores the character
using four 2-byte component codes, and was necessary because ISO IR 149 did
not contain enough code points for all characters used in Korean.  Our
decoder will convert each of these 8-byte codes into a single Unicode
character.

### Encoding

Our ISO 2022 IR 149 encoder places the escape `ESC $)C` sequence at the front
of every line that uses Korean characters (or any characters from KS X 1001),
as required by DICOM.  Hangul that do not exist in KS X 1001 are decomposed
and stored as 8-byte codes.

The following characters are considered to be compatible by our encoder,
due to the various tables that vendors use to map KS X 1001 to Unicode:

1. MIDDLE DOT and KATAKANA MIDDLE DOT
2. SOFT HYPHEN and EN DASH
3. HORIZONTAL BAR and EM DASH
4. PARALLEL TO and DOUBLE VERTICAL LINE
5. TILDE OPERATOR and WAVE DASH
6. FULLWIDTH CENT SIGN and CENT SIGN
7. FULLWIDTH POUND SIGN and POUND SIGN
8. FULLWIDTH YEN SIGN and YEN SIGN
9. FULLWIDTH NOT SIGN and NOT SIGN
10. FULLWIDTH TILDE and SMALL TILDE
11. CIRCLED DOT OPERATOR and FISHEYE


## Chinese via GB18030

The GB18030 encoding was designed to encompass all Unicode code points.
Every GB18030 code point maps to a unique Unicode code point and
vice-versa, so round-trip encoding of all Unicode is possible.  Since
the ASCII backslash code (0x5c) can appear in GB18030-encoded strings
as the second byte of a two-byte character, special consideration is
applied when decoding multi-value data elements to ensure that 0x5c
is only parsed as a separator when it appears as a single-byte character.

### Decoding

Decoding is done strictly according to the GB18030:2022 mapping tables.
Compared to GB18030:2005, 18 character code points that previously mapped
to the PUA (Unicode Private Use Area) are now mapped to valid Unicode
characters, and 6 other character code points that previously mapped to
the PUA have been retired in favor of new (previously unused) code points
for those same six characters.

### Encoding

As with decoding, encoding is done strictly according to the GB18030:2022
tables.  Unlike our encoders for other character sets, our GB18030
encoder does not perform any compatibility conversions.  This is because
every Unicode code point maps to a unique GB18030 code point.


## Chinese via GBK

The GBK character table is a strict subset of GB18030, and does not
encompass all of Unicode.  Like GB18030, special consideration is used
when scanning GBK strings for backslash, since the second byte of
some two-byte characters can have the value 0x5c.

### Decoding

Decoding is done per the GBK subset of GB18030, with one addition for
compatibility with text that was encoded with Microsoft Code Page 936:
the code 0x80 is mapped to the Euro symbol.

### Encoding

Unlike GB18030, our encoder for GBK includes compatibility mappings
for PUA codes that defined characters in older versions of the GB
conversion tables.  Our encoder does not encode the Euro symbol.
See the section on the GB2312 encoder for compatibility mappings
(all of these are used for GBK except for EM DASH and HORIZONTAL BAR,
since GBK encodes both separately).


## Chinese via ISO 2022 (GB2312)

DICOM's ISO 2022 IR 58 is identical to the popular euc-cn encoding of
GB2312, except that DICOM requires the use of `ESC $)A` at the beginning
of every line containing characters from GB2312.  Unlike GBK and GB18030,
the second byte of a two-byte GB2312 character code will never be
0x5c (ASCII backslash), due to the fact that the high bit is always set.

### Decoding

Decoding is done by removing the `ESC $)A` escape sequence and decoding
as GB2312 in its euc-cn form.  The table used for decoding is a strict
subset of the table defined by GB18030:2022.

### Encoding

Encoding involves adding the `ESC $)A` escape sequence at the beginning
of every line containing Chinese characters, and then encoding as GB2312.

The following encoding equivalencies are used for compatibility with
historical GB2312 to Unicode mapping tables:

1. MIDDLE DOT and KATAKANA MIDDLE DOT
2. EM DASH and HORIZONTAL BAR
3. FULLWIDTH TILDE and WAVE DASH
4. DOUBLE VERTICAL LINE and PARALLEL TO
5. HORIZONTAL ELLIPSIS and MIDLINE HORIZONTAL ELLIPSIS
6. FULLWIDTH CENT SIGN and CENT SIGN
7. FULLWIDTH POUND SIGN and POUND SIGN


## Considerations for UTF-8

When decoding UTF-8 data, there are a small number of important concerns.
Foremost, the UTF-8 sequences must be checked for validity, and each
sequence must decode to a code point between 0x00000 and 0x10FFFF.
UTF-16 surrogate code points must be detected (0xD800 to 0xDFFF),
since these are also invalid in UTF-8.  Finally, any codes in the
Private Use Area (PUA, 0xE000–0xF8FF) might need special consideration.

Our UTF-8 decoder simply re-encodes as UTF-8 after examining the string.
That is, the decoder and the encoder are one and the same, and its
only purpose is to check for invalid UTF-8 byte sequences and invalid
Unicode code points.  The PUA code points are simply passed through,
as are any unassigned code points.

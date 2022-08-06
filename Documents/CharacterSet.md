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
conform with the DICOM standard.  Instead, the encoder will convert
the extra characters to ASCII code points in cases where there is a
suitable replacement.

The conversions that the encoder uses are as follows:

1. Smart quotes become regular ASCII quotes.
2. Special spaces (wide, narrow) become ASCII space.
3. Soft hyphens and invisible spaces disappear.
4. Dashes become ASCII hyphen/minus.
5. Horizontal bar becomes a double-hyphen.
6. Ellipsis becomes ASCII "..."
7. The fraction slash becomes regular ASCII slash.
8. The swung dash becomes ASCII tilde.
9. Anything else becomes ? and sets the error flag.

Note that the resulting string might be longer than the original,
so the length must be checked after encoding if there are constraints
on the number of characters.


## Japanese via ISO 2022

The use of iso-2022 escape sequences for the encoding of Japanese text
was common before its standardization as iso-2022-jp, and many extensions
to iso-2022-jp, both formal and informal, continued to arise until as late
as 2004.  Our decoder aims to broadly support most of these extensions,
while our encoder aims to strictly follow the rules set in the DICOM standard.

DICOM iso-2022 Japanese differs from iso-2022-jp most significantly
in the optional inclusion, in DICOM, of ISO IR 13 in G1.  This is done
to support the use of half-width katakana in the traditional manner as
described in JIS X 0201 and as commonly done in Japanese desktop
computing and industrial computing.

The Specific Character Set defined term "ISO 2022 IR 13" indicates
that the initial state of the decoder will be ISO IR 14 in G0 and
ISO IR 13 in G1.  Furthermore, the decoder returns to the initial
state for every new line of text (that is, after every CRNL).

In this usage, `ESC )I` will re-designate ISO IR 13 to G1 (though it is
not recommended to designate any other character set to G1), and `ESC (J`
will re-designated ISO IR 14 to G0.

### Decoding

Our decoder includes the following extensions to DICOM's ISO 2022
Japanese:

1. Extra characters from Microsoft CP932.
2. `ESC (I` will place ISO IR 13 in G0.
3. `ESC (H` will place ISO IR 14 in G0.
4. `ESC $@` will place ISO IR 87 in G0.
5. `ESC &@ ESC $B` will place ISO IR 87 in G0.
6. All of iso-2022-jp-2 is supported.

Notes:

1. When iso-2022-jp text is encoded on Windows, it can contain characters
   that do not exist in JIS X 0208:1990.  This is because the Windows
   code page for Japanese, CP932, contains these extra characters.  The
   inclusion of these characters in text labelled as "iso-2022-jp" can
   be either accidental or intentional, as in "iso-2022-jp-ms".
2. The popular encodings euc-jp, shift-jis, and CP932 contain half-width
   katakana while iso-2022-jp does not.  To allow conversion of these
   characters to 7-bit iso-2022, the extension 'iso-2022-jp-ext' uses
   `ESC (I` to allow half-width katakana in G0.
3. The use of `ESC (H` to place ISO IR 14 was a non-standard historical
   practice.  It can occur in very old text.
4. The `ESC $@` sequence is for ISO IR 42 (JISC 6226-1978), which predates
   ISO IR 87 and is a strict subset of ISO IR 87.  Support of this escape
   sequence is required by iso-2022-jp.
5. With the introduction of JIS X 0212:1990, JIS X 0208:1983 was updated
   to JIS X 0208:1990 with minor revisions.  Rather than register a new
   iso-ir number for the JIS X 0208:1990, a new compound escape code
   `ESC &@ ESC $B` was adopted, though it is rarely used.
6. Since iso-2022-jp-2 is the most commonly-used extension to iso-2022-jp,
   supporting it in full seemed apropos.

The JIS X 0213 standard and its encodings iso-2022-jp-3 and
iso-2022-jp-2004 are not supported.  They are rarely used and they
conflict with the informal iso-2022-jp-ms extension.

### Encoding

Encoding of ISO-2022 Japanese in DICOM is usually done with the following
defined terms for Specific Character Set:

1. ISO 2022 IR 13\ISO 2022 IR 87
2. \ISO 2022 IR 87
3. \ISO 2022 IR 87\ISO 2022 IR 159

Notes:

1. This generally implies iso-2022-jp, but requires the use of romaji instead
   of ASCII, and also requires the use of JIS X 0208:1900 rather than
   any other version (such as JIS X 0208-1978 or JIS X 0208-1983).  This
   provides exactly the same characters as classic shift-jis, with exactly
   the same method for encoding romaji and half-width katakana, but with a
   different way of encoding the JIS X 0208 characters.
2. This specifies the most widely used subset of iso-2022-jp, using only ASCII
   and JIS X 0208:1900.  For broad compatibility, this is the best.
3. This specifies the most widely used subset of iso-2022-jp-2, like the above
   but adding JIS X 0212:1990 for additional characters.

It is preferred to avoid the use of ISO 2022 IR 13 (and ISO IR 13),
both because it requires the use of romaji (not ASCII) in G0, and
because half-width katakana are not supported by either iso-2022-jp
or by iso-2022-jp-2.

For (2) and (3) above, when our encoder encounters half-width katakana,
it will convert them to full-width katakana for ISO 2022 IR 87. For (1),
or whenever ISO IR 13 is present, the half-width katakana will be
encoded as-is.

Regarding the structure of the ISO 2022 encoding, our encoder will always
switch G0 to ASCII (or romaji if ISO IR 13) before any ASCII character,
including any control character except ESC.  This includes SPACE and TAB
as well as CR, NL, and FF.

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
3. REVERSE SOLIDUS and FULLWIDTH REVERSE SOLIDUS
4. YEN SIGN and FULLWIDTH YEN SIGN
5. CENT SIGN and FULLWIDTH CENT SIGN
6. POUND SIGN and FULLWIDTH POUND SIGN
7. MINUS SIGN and FULLWIDTH HYPHEN-MINUS
8. NOT SIGN and FULLWIDTH NOT SIGN
9. EM DASH and HORIZONTAL BAR
10. FULLWIDTH TILDE and WAVE DASH
11. TILDE and FULLWIDTH TILDE
12. PARALLEL TO and DOUBLE VERTICAL LINE

The use of the romaji character set (implied by the ISO IR 2022 13
defined term) causes some specific issues regarding compatibility
mapping, since it does not contain tilde or backslash (REVERSE SOLIDUS).
So when encoding to ISO 2022 with romaji in G0, tilde is converted to
FULLWIDTH TILDE (in JIS X 0212) and backslash is converted to
FULLWIDTH REVERSE SOLIDUS (in JIS X 0208).  This is done to avoid tilde
and backslash from appearing as MACRON and YEN, respectively.

This romaji-specific compatibility mapping is yet another reason to
avoid the use of ISO IR 13 unless half-width katakana are absolutely
necessary.


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


## Chinese via GB18030

The GB18030 encoding was designed to encompass all Unicode code points.
Every GB18030 code point maps to a unique Unicode code point and
vice-versa.  Since some GB18030 character codes map to the the
Private Use Area (PUA) of Unicode, there are some special considerations
for the use of GB18030 as discussed below.  Also, it must be noted that
searching for ASCII backslash (0x5c) in GB18030-encoded strings must be
done with care, as some two-byte character codes have 0x5c as the
second byte.

### Decoding

Decoding is done strictly according to the GB18030:2000 mapping tables.
A small number of GB18030 characters map to locations in the Unicode
PUA region, and will therefore only display correctly when used with
a Chinese font that was designed for GB18030 (or for the GBK standard,
which GB18030 extends).

The Unicode 4.1 standard of 2005 added official code points for the
characters that GB18030 maps to the PUA, so in the absence of fonts
that include the correct glyphs at the PUA code points, those PUA
code points can be mapped to Unicode 4.1 code points for display.
Our decoder does not perform this additional mapping, since this
would break round-trip mapping using the official GB18030:2000 tables.

### Encoding

As with decoding, encoding is done strictly according to the GB18030:2000
tables.  Unlike our encoders for other character sets, our GB18030
encoder does not perform any compatibility conversions.  This is because
every Unicode code point maps to a unique GB18030 code point.


## Chinese via GBK

The GBK character table is a strict subset of GB18030, and does not
encompass all of Unicode.  Like GB18030, special consideration is needed
for scanning GBK strings for backslash, since the second byte of
some two-byte characters might have the value 0x5c.

### Decoding

The GBK table maps some code points to the Unicode PUA, so the same PUA
concerns apply to GBK as apply to GB18030.

### Encoding

Unlike GB18030, our encoder for GBK includes several compatibility
conversions.  One conversion (for Unicode 0x1E3F) is related to
GB18030:2005, 24 are for characters that were added to Unicode in 2005,
and the remainder are to support round-trip mapping for Unicode strings
containing PUA code points that were present in older versions of the
GBK mapping tables.


## Chinese via ISO 2022

DICOM's ISO 2022 IR 58 is identical to the popular euc-cn encoding of
GB2312, except that DICOM requires the use of `ESC $)A` at the beginning
of every line containing characters from GB2312.  Unlike GBK and GB18030,
the second byte of a two-byte GB2312 character code will never be
0x5c (ASCII backslash).

### Decoding

Decoding is done by removing the `ESC $)A` escape sequence and decoding
as GB2312 in its euc-cn form.  The table used for decoding is a strict
subset of the table defined by GB18030:2000.

### Encoding

Encoding involves adding the `ESC $)A` escape sequence at the beginning
of every line containing Chinese characters, and also provides the
relevant subset of the compatibility conversions that are done for GBK.


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

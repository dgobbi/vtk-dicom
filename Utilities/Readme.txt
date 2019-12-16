## Utilities for VTK-DICOM

The scripts and text files in this directory are used to generate and
maintain certain source files.  Most importantly, the *makedict.py*
script is used to update the DICOM dictionary used by VTK-DICOM.

## Manifest

The following files should be present in this directory:

```
  chartables.py -- update vtkDICOMCharacterSetTables.cxx
  makedict.py -- update vtkDICOMDictHash.cxx
  make_vm.py -- update vtkDICOMVM.cxx
  parseuid.py -- update vtkDICOMUtilitiesUIDTable.cxx
  parsedic.py -- read dictionary entries stored in .dic files
  parsetpl.py -- read dictionary entries stored in .tpl files
  nemadict.txt -- the dictionary entries defined by the DICOM standard
  nemauids.txt -- the UIDs defined by the DICOM standard
```

## DICOM Updates

New versions of the DICOM standard are published several times a year.
New releases of VTK-DICOM, though less frequent, should be updated to
reflect the most recent version of the standard. VTK-DICOM does not,
of course, provide every feature that is described in the standard,
but we at least want to Part 6, the Data Dictionary, since we can do
so mechanically.

DICOM Part 6 provides tables that list the identifiers that have meaning
within the standard.  Broadly, these identifiers can be divided into
attribute keys (or tags), and object identifiers (or UIDs).

The attribute tables are replicated in the file *nemadict.txt*, which
has the following format:

```
(0028,0030)    # the tag as a (group,element) hexadecimal pair
Pixel Spacing  # the name of the attribute
PixelSpacing   # a key (like the name, but usable as a C identifier)
DS             # the VR (value representation, gives the data type)
2              # the VM (value multiplicity, gives the array length)
               # additional flags, for example RET for retired attributes
```

The UID tables are replicated in the file *nemauids.txt*, which has
the following format:

```
1.2.840.10008.5.1.4.1.1.4  # the UID
MR Image Storage           # the object or class
SOP Class                  # the kind of object or class
PS3.4                      # additional info (optional)
```

To update VTK-DICOM from the standard, it is first necessary to update
nemadict.txt and nemauids.txt.  Then, the VTK-DICOM source code can
be updated as follows:

```
python makedict.py nemadict.txt > vtkDICOMDictHash.cxx 
python makedict.py nemadict.txt --header > vtkDICOMDictHash.h
python parseuid.py nemauids.txt > vtkDICOMUtilitiesUIDTable.cxx
```

The script make_vm.py was used to generate vtkDICOMVM.h, which provides
a list of constants that are required by vtkDICOMDictHash.cxx.  It is not
necessary to re-run make_vm.py.

## Character Sets

The DICOM standard refers to several character sets, all of which are
supported by VTK-DICOM.  New character sets are unlikely to be added to
the standard.  However, in the unlikely event that someone desires to
update the character set tables used by VTK-DICOM, it can be done as
follows.

First, the character set conversion tables must be downloaded from
https://encoding.spec.whatwg.org/ and placed in a folder called *whatwg*.
The following tables are used:

```
index-big5.txt
index-euc-kr.txt
index-gb18030-ranges.txt
index-gb18030.txt
index-iso-2022-jp-katakana.txt
index-iso-8859-10.txt
index-iso-8859-13.txt
index-iso-8859-14.txt
index-iso-8859-15.txt
index-iso-8859-16.txt
index-iso-8859-2.txt
index-iso-8859-3.txt
index-iso-8859-4.txt
index-iso-8859-5.txt
index-iso-8859-6.txt
index-iso-8859-7.txt
index-iso-8859-8.txt
index-jis0208.txt
index-jis0212.txt
index-koi8-r.txt
index-koi8-u.txt
index-windows-1250.txt
index-windows-1251.txt
index-windows-1252.txt
index-windows-1253.txt
index-windows-1254.txt
index-windows-1255.txt
index-windows-1256.txt
index-windows-1257.txt
index-windows-1258.txt
index-windows-874.txt
```

Then, the following command can be used to update the source code,
assuming that the whatwg directory is within the current directory:

```
python chartables.py > vtkDICOMCharacterSetTables.cxx
```

Note that if any character sets are added or removed, it is necessary to
modify vtkDICOMCharacterSet.h and vtkDICOMCharacterSet.cxx as well.

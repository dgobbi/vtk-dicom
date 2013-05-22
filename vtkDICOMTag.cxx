/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2013 David Gobbi
  All rights reserved.
  See Copyright.txt or http://www.cognitive-antics.net/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkDICOMTag.h"

ostream& operator<<(ostream& o, const vtkDICOMTag& a)
{
  // This is easier than saving the stream state, changing it to write
  // hexadecimal, and then restoring the state, and it also doesn't
  // require including iomanip.h

  char text[12];
  int t[2];
  t[0] = a.GetGroup();
  t[1] = a.GetElement();
  char *cp = text;
  *cp++ = '(';
  for (int j = 0; j < 2; j++)
    {
    for (int i = 12; i >= 0; i -= 4)
      {
      char d = ((t[j] >> i) & 0x000F);
      *cp++ = (d < 10 ? '0' + d : 'A' - 10 + d);
      }
    *cp++ = ',';
    }
  cp[-1] = ')';
  *cp = '\0';

  o << text;

  return o;
}

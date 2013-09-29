#include "vtkDICOMVR.h"
#include "vtkDICOMValue.h"

#include <sstream>

#include <string.h>
#include <stdlib.h>

// macro for performing tests
#define TestAssert(t) \
if (!(t)) \
{ \
  cout << exename << ": Assertion Failed: " << #t << "\n"; \
  cout << __FILE__ << ":" << __LINE__ << "\n"; \
  cout.flush(); \
  rval |= 1; \
}

int main(int argc, char *argv[])
{
  int rval = 0;
  const char *exename = (argc > 0 ? argv[0] : "TestDICOMVR");

  // remove path portion of exename
  const char *cp = exename + strlen(exename);
  while (cp != exename && cp[-1] != '\\' && cp[-1] != '/') { --cp; }
  exename = cp;

  { // Test default constructor.
  vtkDICOMVR vr;
  TestAssert(!vr.IsValid());
  }

  { // Test the individual VRs
  vtkDICOMVR vrAE("AE");
  TestAssert(vrAE == vtkDICOMVR::AE);
  TestAssert(strcmp(vrAE.GetText(), "AE") == 0);
  TestAssert(vrAE.GetType() == VTK_CHAR);

  vtkDICOMVR vrAS("AS");
  TestAssert(vrAS == vtkDICOMVR::AS);
  TestAssert(strcmp(vrAS.GetText(), "AS") == 0);
  TestAssert(vrAS.GetType() == VTK_CHAR);

  vtkDICOMVR vrAT("AT");
  TestAssert(vrAT == vtkDICOMVR::AT);
  TestAssert(strcmp(vrAT.GetText(), "AT") == 0);
  TestAssert(vrAT.GetType() == VTK_DICOM_TAG);

  vtkDICOMVR vrCS("CS");
  TestAssert(vrCS == vtkDICOMVR::CS);
  TestAssert(strcmp(vrCS.GetText(), "CS") == 0);
  TestAssert(vrCS.GetType() == VTK_CHAR);

  vtkDICOMVR vrDA("DA");
  TestAssert(vrDA == vtkDICOMVR::DA);
  TestAssert(strcmp(vrDA.GetText(), "DA") == 0);
  TestAssert(vrDA.GetType() == VTK_CHAR);

  vtkDICOMVR vrDS("DS");
  TestAssert(vrDS == vtkDICOMVR::DS);
  TestAssert(strcmp(vrDS.GetText(), "DS") == 0);
  TestAssert(vrDS.GetType() == VTK_CHAR);

  vtkDICOMVR vrDT("DT");
  TestAssert(vrDT == vtkDICOMVR::DT);
  TestAssert(strcmp(vrDT.GetText(), "DT") == 0);
  TestAssert(vrDT.GetType() == VTK_CHAR);

  vtkDICOMVR vrFD("FD");
  TestAssert(vrFD == vtkDICOMVR::FD);
  TestAssert(strcmp(vrFD.GetText(), "FD") == 0);
  TestAssert(vrFD.GetType() == VTK_DOUBLE);

  vtkDICOMVR vrFL("FL");
  TestAssert(vrFL == vtkDICOMVR::FL);
  TestAssert(strcmp(vrFL.GetText(), "FL") == 0);
  TestAssert(vrFL.GetType() == VTK_FLOAT);

  vtkDICOMVR vrIS("IS");
  TestAssert(vrIS == vtkDICOMVR::IS);
  TestAssert(strcmp(vrIS.GetText(), "IS") == 0);
  TestAssert(vrIS.GetType() == VTK_CHAR);

  vtkDICOMVR vrLO("LO");
  TestAssert(vrLO == vtkDICOMVR::LO);
  TestAssert(strcmp(vrLO.GetText(), "LO") == 0);
  TestAssert(vrLO.GetType() == VTK_CHAR);

  vtkDICOMVR vrLT("LT");
  TestAssert(vrLT == vtkDICOMVR::LT);
  TestAssert(strcmp(vrLT.GetText(), "LT") == 0);
  TestAssert(vrLT.GetType() == VTK_CHAR);

  vtkDICOMVR vrOB("OB");
  TestAssert(vrOB == vtkDICOMVR::OB);
  TestAssert(strcmp(vrOB.GetText(), "OB") == 0);
  TestAssert(vrOB.GetType() == VTK_UNSIGNED_CHAR);

  vtkDICOMVR vrOF("OF");
  TestAssert(vrOF == vtkDICOMVR::OF);
  TestAssert(strcmp(vrOF.GetText(), "OF") == 0);
  TestAssert(vrOF.GetType() == VTK_FLOAT);

  vtkDICOMVR vrOW("OW");
  TestAssert(vrOW == vtkDICOMVR::OW);
  TestAssert(strcmp(vrOW.GetText(), "OW") == 0);
  TestAssert(vrOW.GetType() == VTK_SHORT);

  vtkDICOMVR vrPN("PN");
  TestAssert(vrPN == vtkDICOMVR::PN);
  TestAssert(strcmp(vrPN.GetText(), "PN") == 0);
  TestAssert(vrPN.GetType() == VTK_CHAR);

  vtkDICOMVR vrSH("SH");
  TestAssert(vrSH == vtkDICOMVR::SH);
  TestAssert(strcmp(vrSH.GetText(), "SH") == 0);
  TestAssert(vrSH.GetType() == VTK_CHAR);

  vtkDICOMVR vrSL("SL");
  TestAssert(vrSL == vtkDICOMVR::SL);
  TestAssert(strcmp(vrSL.GetText(), "SL") == 0);
  TestAssert(vrSL.GetType() == VTK_INT);

  vtkDICOMVR vrSQ("SQ");
  TestAssert(vrSQ == vtkDICOMVR::SQ);
  TestAssert(strcmp(vrSQ.GetText(), "SQ") == 0);
  TestAssert(vrSQ.GetType() == VTK_DICOM_ITEM);

  vtkDICOMVR vrSS("SS");
  TestAssert(vrSS == vtkDICOMVR::SS);
  TestAssert(strcmp(vrSS.GetText(), "SS") == 0);
  TestAssert(vrSS.GetType() == VTK_SHORT);

  vtkDICOMVR vrST("ST");
  TestAssert(vrST == vtkDICOMVR::ST);
  TestAssert(strcmp(vrST.GetText(), "ST") == 0);
  TestAssert(vrST.GetType() == VTK_CHAR);

  vtkDICOMVR vrTM("TM");
  TestAssert(vrTM == vtkDICOMVR::TM);
  TestAssert(strcmp(vrTM.GetText(), "TM") == 0);
  TestAssert(vrTM.GetType() == VTK_CHAR);

  vtkDICOMVR vrUI("UI");
  TestAssert(vrUI == vtkDICOMVR::UI);
  TestAssert(strcmp(vrUI.GetText(), "UI") == 0);
  TestAssert(vrUI.GetType() == VTK_CHAR);

  vtkDICOMVR vrUL("UL");
  TestAssert(vrUL == vtkDICOMVR::UL);
  TestAssert(strcmp(vrUL.GetText(), "UL") == 0);
  TestAssert(vrUL.GetType() == VTK_UNSIGNED_INT);

  vtkDICOMVR vrUN("UN");
  TestAssert(vrUN == vtkDICOMVR::UN);
  TestAssert(strcmp(vrUN.GetText(), "UN") == 0);
  TestAssert(vrUN.GetType() == VTK_UNSIGNED_CHAR);

  vtkDICOMVR vrUS("US");
  TestAssert(vrUS == vtkDICOMVR::US);
  TestAssert(strcmp(vrUS.GetText(), "US") == 0);
  TestAssert(vrUS.GetType() == VTK_UNSIGNED_SHORT);

  vtkDICOMVR vrUT("UT");
  TestAssert(vrUT == vtkDICOMVR::UT);
  TestAssert(strcmp(vrUT.GetText(), "UT") == 0);
  TestAssert(vrUT.GetType() == VTK_CHAR);
  }

  return rval;
}

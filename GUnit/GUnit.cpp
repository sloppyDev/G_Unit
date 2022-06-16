#include "gUnit.h"

wxIMPLEMENT_APP(gUnit);

gUnit::gUnit()
{}

gUnit::~gUnit()
{}

bool gUnit::OnInit()
{
   frame1 = new Main();
   frame1->Show();
   return true;
}

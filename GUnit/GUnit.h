#ifndef GUNIT_H
#define GUNIT_H

#include "wx/wx.h"

#include "Main.h"

struct gUnit : public wxApp
{
   gUnit();
   ~gUnit();

   Main* frame1 = nullptr;

   virtual bool OnInit();
};

#endif

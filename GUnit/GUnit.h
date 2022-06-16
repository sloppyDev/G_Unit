#ifndef GUNIT_H
#define GUNIT_H

#include "wx/wx.h"

#include "Main.h"

class gUnit : public wxApp
{
public:
   gUnit();
   ~gUnit();

private: 
   Main* frame1 = nullptr;

public:
   virtual bool OnInit();
};

#endif

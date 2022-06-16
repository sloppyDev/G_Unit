#ifndef MAIN_H
#define MAIN_H

#include "wx/wx.h"

class Main : public wxFrame
{
public:
   Main();
   ~Main();

public:
   wxButton* button = nullptr;
   wxTextCtrl* textBox = nullptr;
   wxListBox* listBox = nullptr;

   void OnButtonClicked(wxCommandEvent& evt);

   wxDECLARE_EVENT_TABLE();
};

#endif

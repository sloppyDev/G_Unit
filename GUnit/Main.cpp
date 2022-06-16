#include "Main.h"

wxBEGIN_EVENT_TABLE(Main, wxFrame)
   EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()
Main::Main() : wxFrame(nullptr, wxID_ANY, "G Unit", wxPoint(30, 30), wxSize(800, 600))
{
   button = new wxButton(this, 10001, "Click Me!", wxPoint(10, 10), wxSize(150, 50));
   textBox = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
   listBox = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}

Main::~Main()
{}

void Main::OnButtonClicked(wxCommandEvent& evt)
{
   listBox->AppendString(textBox->GetValue());
   evt.Skip();
}

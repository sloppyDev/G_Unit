#include "Main.h"



wxBEGIN_EVENT_TABLE(Main, wxFrame)
EVT_MENU(wxID_OPEN, Main::OnOpen)
EVT_MENU(wxID_EXIT, Main::OnExit)
EVT_LISTBOX(GCODE_ID, Main::OnListSelect)
EVT_TIMER(TIMER_ID, Main::OnTimer)
EVT_BUTTON(RUN_ID, Main::OnRun)
EVT_BUTTON(HOLD_ID, Main::OnHold)
EVT_BUTTON(RESUME_ID, Main::OnResume)
EVT_BUTTON(RESET_ID, Main::OnReset)
wxEND_EVENT_TABLE()
Main::Main() : wxFrame(nullptr, wxID_ANY, "G Unit", 
   wxPoint(50, 50), 
   wxSize(1000, 800), 
   wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER),
   status(IDLE),
   gcodeIndex(0)
{
   menuBar = new wxMenuBar();
   fileMenu = new wxMenu();
   fuckYouMenu = new wxMenu("You");
   wxMenu* barMenu = new wxMenu();

   fileMenu->Append(wxID_OPEN, _T("&Open"));
   fileMenu->Append(wxID_ANY, _T("--------"));
   fileMenu->Append(wxID_EXIT, _T("&Exit"));

   menuBar->Append(fileMenu, "File");
   menuBar->Append(fuckYouMenu, "Fuck");
   SetMenuBar(menuBar);

   wxPanel* panel = new wxPanel(this);

   // --------------
   // ---- LOGO ----
   // --------------
   wxInitAllImageHandlers();
   logoBmp = wxBitmap("C:\\Users\\selik\\Documents\\projects\\plasmaCutter\\logo.png", wxBITMAP_TYPE_PNG);
   logoBitmap = new wxStaticBitmap(
      panel, 
      wxID_ANY, 
      logoBmp, 
      wxPoint(borderSize, borderSize), 
      logoSize);

   // -----------------------
   // ---- GCode Listbox ----
   // -----------------------
   gcodeListBox = new wxListBox(
     panel,
     GCODE_ID,
     wxPoint(borderSize, 2*borderSize + logoSize.y),
     gcodeListSize);

   // --------------------------
   // ---- Critical Buttons ----
   // --------------------------
   // RUN
   runButton = new wxButton(
      panel,
      RUN_ID,
      "RUN",
      wxPoint(borderSize, 3*borderSize + gcodeListSize.y + logoSize.y),
      buttonSize);

   // HOLD
   holdButton = new wxButton(
      panel,
      HOLD_ID,
      "HOLD",
      wxPoint(2*borderSize + buttonSize.x, 3*borderSize + gcodeListSize.y + logoSize.y),
      buttonSize);

   // RESUME
   resumeButton = new wxButton(
      panel,
      RESUME_ID,
      "RESUME",
      wxPoint(borderSize , 4*borderSize + gcodeListSize.y + logoSize.y + buttonSize.y),
      buttonSize);

   // RESET
   resetButton = new wxButton(
      panel,
      RESET_ID,
      "RESET",
      wxPoint(2*borderSize + buttonSize.x, 4*borderSize + gcodeListSize.y + logoSize.y + buttonSize.y),
      buttonSize);

   holdButton->Enable(false);
   resumeButton->Enable(false);
   resetButton->Enable(false);

   // ---------------------
   // ---- Status Text ----
   // ---------------------
   machineStatusText = new wxStaticText(
      panel,
      MACHINE_STATUS_ID,
      "IDLE",
      wxPoint(460, 0),
      wxSize(40, 15));

   // ----------------------
   // ---- Update Timer ----
   // ----------------------
   updateTimer = new wxTimer(this, TIMER_ID);
   updateTimer->Start(100);
}

Main::~Main()
{}

void Main::OnRun(wxCommandEvent& evt)
{
   status = STATUS::RUNNING;
   machineStatusText->SetLabelText("RUNNING");

   runButton->Enable(false);
   holdButton->Enable(true);
   resumeButton->Enable(false);
   resetButton->Enable(false);

   evt.Skip();
}

void Main::OnHold(wxCommandEvent& evt)
{
   status = STATUS::HOLDING;
   machineStatusText->SetLabelText("HOLDING");

   runButton->Enable(false);
   holdButton->Enable(false);
   resumeButton->Enable(true);
   resetButton->Enable(true);

   evt.Skip();
}

void Main::OnResume(wxCommandEvent& evt)
{
   status = STATUS::RUNNING;
   machineStatusText->SetLabelText("RUNNING");

   runButton->Enable(false);
   holdButton->Enable(true);
   resumeButton->Enable(false);
   resetButton->Enable(false);

   evt.Skip();
}

void Main::OnReset(wxCommandEvent& evt)
{
   status = STATUS::IDLE;
   machineStatusText->SetLabelText("IDLE");
   gcodeIndex = 0;

   runButton->Enable(true);
   holdButton->Enable(false);
   resumeButton->Enable(false);
   resetButton->Enable(false);

   
   fillListBox();
   gcodeListBox->SetSelection(0);

   evt.Skip();
}

void Main::OnTimer(wxTimerEvent& evt)
{
   if (status == STATUS::RUNNING)
   {
      gcodeIndex++;
      if (gcodeIndex >= gStrings.size())
      {
         gcodeIndex = 0;
      }
   }
   else if (status == STATUS::IDLE)
   {
      gcodeIndex = 0;
   }
   if (gcodeListBox->GetCount() > 0 && gcodeIndex > 0 && status != STATUS::HOLDING)
   {
      fillListBox();
      gcodeListBox->SetSelection(0);
   }
   evt.Skip();
}

void Main::OnOpen(wxCommandEvent& evt)
{
   // File Selection
   wxFileDialog openFileDialog(this);

   if (openFileDialog.ShowModal() == wxID_CANCEL)
   {
      return;
   }

   // Reading G Code
   gStrings.clear();
   std::string gString = "";
   std::fstream file;
   file.open(std::string(openFileDialog.GetPath()), std::ios::in);

   if (file.is_open())
   {
      while (std::getline(file, gString))
      {
         gStrings.push_back(gString);
      }
      file.close();
   }

   // Displaying G Code
   fillListBox();

   evt.Skip();
}

void Main::OnExit(wxCommandEvent& evt)
{
   Close(true);
   evt.Skip();
}

void Main::OnListSelect(wxCommandEvent& evt)
{
   gcodeListBox->SetSelection(0);
   evt.Skip();
}

void Main::fillListBox()
{
   unsigned int listLength{ 33 };
   for (unsigned int i = gcodeIndex; i < listLength + gcodeIndex; i++)
   {
      if (gStrings.size() >= i + 1)
      {
         if (gcodeListBox->GetCount() == listLength)
            gcodeListBox->SetString(i - gcodeIndex, gStrings[i]);
         else
            gcodeListBox->Append(gStrings[i]);
      }
   }
}

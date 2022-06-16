#ifndef MAIN_H
#define MAIN_H

#include <fstream>
#include <iostream>
#include <vector>

#include "wx/wx.h"

enum STATUS
{
   IDLE,
   RUNNING,
   HOLDING
};

enum
{
   RUN_ID,
   HOLD_ID,
   RESUME_ID,
   RESET_ID,
   GCODE_ID,
   TIMER_ID,
   MACHINE_STATUS_ID
};

struct Main : public wxFrame
{
   Main();
   ~Main();

   // ----------------------
   // ---- GUI Elements ----
   // ----------------------
   // ---- Visible ----
   wxMenuBar* menuBar;
   wxMenu* fileMenu;
   wxMenu* fuckYouMenu;

   // Logo
   wxStaticBitmap* logoBitmap;

   // Critical Buttons
   wxButton* runButton;
   wxButton* holdButton;
   wxButton* resumeButton;
   wxButton* resetButton;

   // Status
   wxStaticText* machineStatusText;
   wxListBox* gcodeListBox;

   wxStaticText* machineCoordText;
   wxStaticText* machineXPosText;
   wxStaticText* machineYPosText;
   wxStaticText* machineZPosText;

   wxStaticText* workingCoordText;
   wxStaticText* workingXPosText;
   wxStaticText* workingYPosText;
   wxStaticText* workingZPosText;

   wxStaticText* lineCountText;
   wxStaticText* percentCompleteText;

   // Background
   wxTimer* updateTimer;

   // -------------------
   // ---- Callbacks ----
   // -------------------
   void OnRun(wxCommandEvent& evt);
   void OnHold(wxCommandEvent& evt);
   void OnResume(wxCommandEvent& evt);
   void OnReset(wxCommandEvent& evt);
   void OnTimer(wxTimerEvent& evt);

   void OnOpen(wxCommandEvent& evt);
   void OnExit(wxCommandEvent& evt);
   void OnListSelect(wxCommandEvent& evt);

   // -------------------------
   // ---- Utility Methods ----
   // -------------------------
   void fillListBox();

   // --------------------------
   // ---- Member Variables ----
   // --------------------------
   STATUS status;
   wxBitmap logoBmp;
   std::vector<std::string> gStrings;
   unsigned int gcodeIndex;

   // Sizes
   unsigned int borderSize{ 10 };
   wxSize logoSize = wxSize(350, 90);
   wxSize gcodeListSize = wxSize(350, 510);
   wxSize buttonSize = wxSize(170, 45);

   wxDECLARE_EVENT_TABLE();
};

#endif

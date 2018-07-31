#include <wx/wx.h>
#include <string>
#include "ce_ai.h"
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);
	void OnTimer(wxTimerEvent& event);
	int Write(string mes);
private:
	int m_data[60];
	wxStaticText *m_lbl;
	wxTextCtrl *m_txt;
	CE_Ai *m_ai;
	wxTimer m_timer;
	wxDECLARE_EVENT_TABLE();
};
const int ID_LABEL = 102;
const int ID_TXT = 103;
const int ID_TIMER = 104;
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_TIMER(ID_TIMER, MyFrame::OnTimer)
wxEND_EVENT_TABLE()
MyFrame::MyFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(250, 150))
		, m_timer(this, ID_TIMER)
{
	m_lbl = new wxStaticText(this, ID_LABEL, wxT("Analog input:"), wxPoint(20,15), wxSize(100,25));
	m_txt = new wxTextCtrl(this, ID_TXT, wxT("0"), wxPoint(140,10), wxSize(50,25));	
	m_ai = new CE_Ai(5);
	Centre();
	for (int i = 0; i < 60; i++) m_data[i] = 0;
	m_timer.Start(1000);
}

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)
bool MyApp::OnInit()
{
    MyFrame *myFrame = new MyFrame(wxT("Energy Monitor"));
    myFrame->Show(true);

    return true;
}
void MyFrame::OnTimer(wxTimerEvent& WXUNUSED(event))
{
	static int i = 0;
	i=++i%60;	

	float a = 2275; // offset = 4095.0 / 1.8 = 2275 N/V;
	float k = 2.53;  // scale factor = (20 * 230) / (0.8*2275) => 2.53 VA/N
	float val = m_ai->Read();
	float w = k*(val - a);

	m_data[i] = int(w);
	string str = "";
	for (int j = 0, k = i+1;; j++,k++) {
		k %= 60;
		str += "[" + to_string(j + 1) + "," + to_string(m_data[k]) + "]";
		if (j >= 59) break;
		str += ",";
	}
	m_txt->Clear();
	m_txt->AppendText(wxString::Format(wxT("%d"), m_data[i]));
	this->Write(str);
}
int MyFrame::Write(string mes)
{
	ofstream wfile;
	int r = -1;
	string fpath = "./eseconds.php";
	wfile.open(fpath.c_str(), std::fstream::out);
	if (wfile.is_open()) {
		wfile << mes << endl;
		r = 0;
	}
	wfile.close();
	return r;
}
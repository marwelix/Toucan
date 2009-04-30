/////////////////////////////////////////////////////////////////////////////////
// Author:      Steven Lamerton
// Copyright:   Copyright (C) 2006-2009 Steven Lamerton
// Licence:     GNU GPL 2 (See readme for more info
/////////////////////////////////////////////////////////////////////////////////

#include <wx/fileconf.h>
#include <wx/tokenzr.h>
#include <wx/datetime.h>
#include <wx/stdpaths.h>
#include <wx/utils.h>
#include <wx/filename.h>

#include "variables.h"
#include "toucan.h"

wxString Normalise(wxString strFilePath){
	wxString token;
	wxString strReturn = wxEmptyString;
	wxDateTime now = wxDateTime::Now();  
	wxStringTokenizer tkz(strFilePath, wxT("@"), wxTOKEN_STRTOK);
	bool previousmatched = true;
	while(tkz.HasMoreTokens()){
        token = tkz.GetNextToken();
		wxString strValue, read;
		if(token == wxT("date")){
			token = now.FormatISODate();
			strReturn += token;
			previousmatched = true;
		}
		else if(token == wxT("time")){
			token = now.Format(wxT("%H")) + wxT("-") +  now.Format(wxT("%M"));
			strReturn += token;
			previousmatched = true;
		}
		else if(token == wxT("YYYY")){
			token = now.Format(wxT("%Y"));
			strReturn += token;
			previousmatched = true;
		}
		else if(token == wxT("MM")){
			token = now.Format(wxT("%m"));
			strReturn += token;
			previousmatched = true;
		}
		else if(token == wxT("DD")){
			token = now.Format(wxT("%d"));
			strReturn += token;
			previousmatched = true;
		}
		else if(token == wxT("hh")){
			token = now.Format(wxT("%H"));
			strReturn += token;
			previousmatched = true;
		}
		else if(token == wxT("mm")){
			token = now.Format(wxT("%M"));
			strReturn += token;
			previousmatched = true;
		}
		else if(token == wxT("drive")){
			strReturn += wxPathOnly(wxStandardPaths::Get().GetExecutablePath()).Left(2);
			previousmatched = true;
		}
		else if(token == wxT("docs")){
			strReturn += wxStandardPaths::Get().GetDocumentsDir();
			previousmatched = true;
		}
		else if(token == wxT("volume")){
			#ifdef __WXMSW__
				wxString strName = wxEmptyString;
				WCHAR volumeLabel[256]; 
				GetVolumeInformation(wxGetApp().GetSettingsPath().Left(3), volumeLabel, sizeof(volumeLabel), NULL, 0, NULL, NULL, 0);
				strName.Printf(wxT("%s"),volumeLabel); 
				strReturn += strName;
			#endif
			previousmatched = true;
		}
		else if(token == wxT("label")){
		 	wxFileConfig* autorun = new wxFileConfig(wxT(""), wxT(""), wxGetApp().GetSettingsPath().Left(3) + wxFILE_SEP_PATH + wxT("autorun.inf"));
			wxString label = autorun->Read(wxT("Autorun/Label"));
			strReturn += label;
			delete autorun;
			previousmatched = true;
		}
		else if(wxGetEnv(token , &strValue)){
			strReturn += strValue;
			previousmatched = true;
		}
		else if(wxGetApp().m_Variables_Config->Read(token + wxT("/") + wxGetFullHostName(), &read) != false && wxGetApp().m_Variables_Config->GetNumberOfGroups() != 0){
			strReturn += read;
			previousmatched = true;
		}
		else if(wxGetApp().m_Variables_Config->Read(token + wxT("/") + _("Other"), &read) != false && wxGetApp().m_Variables_Config->GetNumberOfGroups() != 0){
			strReturn += read;
			previousmatched = true;
		}
		else{
			if(previousmatched){
				strReturn += token;
			}
			else{
				strReturn = strReturn + wxT("@") + token;
			}
			//This time we did not match
			previousmatched = false;
		}
	}

	if(strReturn.Length() == 2 && strReturn.Right(1) == wxT(":")){
		strReturn += wxFILE_SEP_PATH;
	}	
	wxFileName flReturn(strReturn);
	if(flReturn.IsOk()){
		return strReturn;
	}
	else{
		return wxEmptyString;
	}
}

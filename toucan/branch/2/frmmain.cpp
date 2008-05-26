/////////////////////////////////////////////////////////////////////////////////
// Author:      Steven Lamerton
// Copyright:   Copyright (C) 2006-2008 Steven Lamerton
// License:     GNU GPL 2 (See readme for more info)
/////////////////////////////////////////////////////////////////////////////////

#include <wx/wx.h>

#include "toucan.h"
#include "virtualdirtreectrl.h"
#include "dragndrop.h"

#include "frmmain.h"
#include "frmprogress.h"
#include "frmrestore.h"

#include "secure.h"
#include "securedata.h"

#include "syncdata.h"
#include "sync.h"

#include "backupdata.h"
#include "backupprocess.h"
#include "backupfunctions.h"

#include "script.h"
#include "waitthread.h"

//Implement frmMain
IMPLEMENT_CLASS( frmMain, wxFrame )


//frmMain event table
BEGIN_EVENT_TABLE( frmMain, wxFrame )

	EVT_CLOSE( frmMain::OnCloseWindow )

	EVT_COMBOBOX( ID_SYNC_JOB_SELECT, frmMain::OnSyncJobSelectSelected )

	EVT_BUTTON( ID_SYNC_OK, frmMain::OnSyncOKClick )
	
	EVT_BUTTON( ID_SYNC_PREVIEW, frmMain::OnSyncPreviewClick )

	EVT_BUTTON( ID_SYNC_JOB_SAVE, frmMain::OnSyncJobSaveClick )
	
	EVT_BUTTON( ID_BACKUP_JOB_SAVE, frmMain::OnBackupJobSaveClick )
	
	EVT_BUTTON( ID_BACKUP_JOB_ADD, frmMain::OnBackupJobAddClick )

	EVT_BUTTON( ID_BACKUP_JOB_REMOVE, frmMain::OnBackupJobRemoveClick )
	
	EVT_COMBOBOX( ID_BACKUP_JOB_SELECT, frmMain::OnBackupJobSelectSelected )

	EVT_BUTTON( ID_SYNC_JOB_ADD, frmMain::OnSyncJobAddClick )

	EVT_BUTTON( ID_SYNC_JOB_REMOVE, frmMain::OnSyncJobRemoveClick )

	EVT_BUTTON( ID_SYNC_SOURCE_BTN, frmMain::OnSyncSourceBtnClick )

	EVT_BUTTON( ID_SYNC_DEST_BTN, frmMain::OnSyncDestBtnClick )

	EVT_BUTTON( ID_BACKUP_OK, frmMain::OnBackupOKClick )
	
	EVT_BUTTON( ID_BACKUP_RESTORE, frmMain::OnBackupRestoreClick )
	
	EVT_BUTTON( ID_BACKUP_PREVIEW, frmMain::OnBackupPreviewClick )

	EVT_BUTTON( ID_BACKUP_LOCATION, frmMain::OnBackupLocationClick )

	EVT_BUTTON( ID_BACKUP_ADD, frmMain::OnBackupAddClick )

	EVT_BUTTON( ID_BACKUP_REMOVE, frmMain::OnBackupRemoveClick )
	
	EVT_BUTTON( ID_SECURE_OK, frmMain::OnSecureOKClick )
	
	EVT_BUTTON( ID_SECURE_PREVIEW, frmMain::OnSecurePreviewClick )

	EVT_COMBOBOX( ID_SECURE_JOB_SELECT, frmMain::OnSecureJobSelectSelected )

	EVT_BUTTON( ID_SECURE_JOB_SAVE, frmMain::OnSecureJobSaveClick )

	EVT_BUTTON( ID_SECURE_JOB_ADD, frmMain::OnSecureJobAddClick )

	EVT_BUTTON( ID_SECURE_JOB_REMOVE, frmMain::OnSecureJobRemoveClick )

	EVT_BUTTON( ID_SECURE_ADD, frmMain::OnSecureAddClick )

	EVT_BUTTON( ID_SECURE_REMOVE, frmMain::OnSecureRemoveClick )

	EVT_COMBOBOX( ID_RULES_COMBO, frmMain::OnRulesComboSelected )

	EVT_BUTTON( ID_RULES_SAVE, frmMain::OnRulesSaveClick )

	EVT_BUTTON( ID_RULES_ADD, frmMain::OnRulesAddClick )

	EVT_BUTTON( ID_RULES_REMOVE, frmMain::OnRulesRemoveClick )

	EVT_BUTTON( ID_RULES_ADD_FILEEXCLUDE, frmMain::OnRulesAddFileexcludeClick )

	EVT_BUTTON( ID_RULES_REMOVE_FILEEXCLUDE, frmMain::OnRulesRemoveFileexcludeClick )

	EVT_BUTTON( ID_RULES_ADD_FOLDEREXCLUDE, frmMain::OnRulesAddFolderexcludeClick )

	EVT_BUTTON( ID_RULES_REMOVE_FOLDEREXCLUDE, frmMain::OnRulesRemoveFolderexcludeClick )

	EVT_BUTTON( ID_RULES_ADD_LOCATIONINCLUDE, frmMain::OnRulesAddLocationincludeClick )

	EVT_BUTTON( ID_RULES_REMOVE_LOCATIONINCLUDE, frmMain::OnRulesRemoveLocationincludeClick )

	EVT_BUTTON( ID_RULES_ADD_FILEDELETE, frmMain::OnRulesAddFiledeleteClick )

	EVT_BUTTON( ID_RULES_REMOVE_FILEDELETE, frmMain::OnRulesRemoveFiledeleteClick )
	
	EVT_BUTTON(ID_SCRIPT_EXECUTE, frmMain::OnScriptExecute)
	
	EVT_BUTTON(ID_PVAR_ADD, frmMain::OnPvarAddClick )
	
	EVT_BUTTON(ID_PVAR_REMOVE, frmMain::OnPvarRemoveClick )
	
	EVT_BUTTON(ID_PVAR_ADDITEM, frmMain::OnPvarAddItemClick )
	
	EVT_BUTTON(ID_PVAR_REMOVEITEM, frmMain::OnPvarRemoveItemClick )
	
	EVT_COMBOBOX(ID_PVAR_NAME, frmMain::OnPvarNameSelected )
	
	EVT_BUTTON( ID_SCRIPT_SAVE, frmMain::OnScriptSaveClick )

	EVT_BUTTON( ID_SCRIPT_ADD, frmMain::OnScriptAddClick )

	EVT_BUTTON( ID_SCRIPT_REMOVE, frmMain::OnScriptRemoveClick )
	
	EVT_COMBOBOX(ID_SCRIPT_NAME, frmMain::OnScriptSelected )
	
	EVT_LIST_ITEM_ACTIVATED(ID_PVAR_LIST, frmMain::OnPvarListActivated )

END_EVENT_TABLE()


//Constructor
frmMain::frmMain()
{
	Init();
}

frmMain::frmMain( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
	Init();
	Create( parent, id, caption, pos, size, style );
}

//Creator
bool frmMain::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
	wxFrame::Create( parent, id, caption, pos, size, style );
	CreateControls();
	Centre();
	return true;
}


//Destructor
frmMain::~frmMain()
{
	GetAuiManager().UnInit();
}

//frmMain initialisation
void frmMain::Init()
{
	m_Notebook = NULL;
	m_Sync_Job_Select = NULL;
	m_Sync_Rules = NULL;
	m_Sync_Source_Txt = NULL;
	m_Sync_Source_Tree = NULL;
	m_Sync_Dest_Txt = NULL;
	m_Sync_Dest_Tree = NULL;
	m_Sync_Function = NULL;
	m_Sync_Timestamp = NULL;
	m_Sync_Attributes = NULL;
	m_Sync_Ignore_Readonly = NULL;
	m_Sync_Ignore_DaylightS = NULL;
	m_Backup_Job_Select = NULL;
	m_Backup_Rules = NULL;
	m_Backup_Location = NULL;
	m_Backup_DirCtrl = NULL;
	m_Backup_TreeCtrl = NULL;
	m_Backup_Function = NULL;
	m_Backup_Format = NULL;
	m_Backup_Ratio = NULL;
	m_Backup_Pass = NULL;
	m_Backup_Repass = NULL;
	m_Secure_Rules = NULL;
	m_Secure_Job_Select = NULL;
	m_Secure_DirCtrl = NULL;
	m_Secure_TreeCtrl = NULL;
	m_Secure_Function = NULL;
	m_Secure_Format = NULL;
	m_Secure_Pass = NULL;
	m_Secure_Repass = NULL;
	m_Rules_Combo = NULL;
	m_Rules_FileExclude = NULL;
	m_Rules_FolderExclude = NULL;
	m_Rules_LocationInclude = NULL;
	m_Rules_FileDelete = NULL;
	m_Script_Rich = NULL;
	
	m_BackupLocations = new wxArrayString();
	m_SecureLocations = new wxArrayString();
	
}

//Create controls
void frmMain::CreateControls()
{
	//Create a pointer so that we have something to add the items to	
	frmMain* itemFrame1 = this;

	//Set the form up as managed by AUI
	GetAuiManager().SetManagedWindow(this);

	//Cretae the root AUI notebook
	m_Notebook = new wxAuiNotebook( itemFrame1, ID_AUINOTEBOOK, wxDefaultPosition, wxDefaultSize, wxAUI_NB_SCROLL_BUTTONS|wxNO_BORDER );

	//The sync panel
	wxPanel* itemPanel6 = new wxPanel( m_Notebook, ID_PANEL_SYNC, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
	itemPanel6->SetSizer(itemBoxSizer7);

	wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer7->Add(itemBoxSizer8, 1, wxGROW|wxALL, 0);
	wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer8->Add(itemBoxSizer9, 0, wxGROW|wxALL, 5);

	//Top sizer
	
	wxBoxSizer* itemBoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer8->Add(itemBoxSizer28, 0, wxGROW|wxALL, 5);
	
	wxBoxSizer* itemBoxSizer001 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer28->Add(itemBoxSizer001, 0, wxGROW|wxALL, 0);	

	//Job section
	wxStaticBox* itemStaticBoxSizer10Static = new wxStaticBox(itemPanel6, wxID_ANY, _("Job Name"));
	wxStaticBoxSizer* itemStaticBoxSizer10 = new wxStaticBoxSizer(itemStaticBoxSizer10Static, wxHORIZONTAL);
	itemBoxSizer001->Add(itemStaticBoxSizer10, 0, wxALIGN_TOP|wxALL, 5);
	wxArrayString m_Sync_Job_SelectStrings;
	m_Sync_Job_Select = new wxComboBox( itemPanel6, ID_SYNC_JOB_SELECT, _T(""), wxDefaultPosition, wxDefaultSize, m_Sync_Job_SelectStrings, wxCB_DROPDOWN );
	itemStaticBoxSizer10->Add(m_Sync_Job_Select, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton12 = new wxBitmapButton( itemPanel6, ID_SYNC_JOB_SAVE, itemFrame1->GetBitmapResource(wxT("save.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemStaticBoxSizer10->Add(itemBitmapButton12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton13 = new wxBitmapButton( itemPanel6, ID_SYNC_JOB_ADD, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemStaticBoxSizer10->Add(itemBitmapButton13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton14 = new wxBitmapButton( itemPanel6, ID_SYNC_JOB_REMOVE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemStaticBoxSizer10->Add(itemBitmapButton14, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//Rules section
	wxStaticBox* itemStaticBoxSizer15Static = new wxStaticBox(itemPanel6, wxID_ANY, _("Rules"));
	wxStaticBoxSizer* itemStaticBoxSizer15 = new wxStaticBoxSizer(itemStaticBoxSizer15Static, wxHORIZONTAL);
	itemBoxSizer001->Add(itemStaticBoxSizer15, 0, wxALIGN_TOP|wxALL|wxGROW, 5);
	wxArrayString m_Sync_RulesStrings;
	m_Sync_Rules = new wxComboBox( itemPanel6, ID_SYNC_RULES, _T(""), wxDefaultPosition, wxDefaultSize, m_Sync_RulesStrings, wxCB_DROPDOWN );
	itemStaticBoxSizer15->Add(m_Sync_Rules, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5);

	//Options section
	wxArrayString m_Sync_FunctionStrings;
	m_Sync_FunctionStrings.Add(_("Copy"));
	m_Sync_FunctionStrings.Add(_("Update"));
	m_Sync_FunctionStrings.Add(_("Mirror (Copy)"));
	m_Sync_FunctionStrings.Add(_("Mirror (Update)"));
	m_Sync_FunctionStrings.Add(_("Equalise"));
	m_Sync_Function = new wxRadioBox( itemPanel6, ID_SYNC_FUNCTION, _("Function"), wxDefaultPosition, wxDefaultSize, m_Sync_FunctionStrings, 1, wxRA_SPECIFY_COLS );
	m_Sync_Function->SetSelection(0);
	itemBoxSizer28->Add(m_Sync_Function, 0, wxALIGN_TOP|wxALL, 5);

	wxStaticBox* itemStaticBoxSizer30Static = new wxStaticBox(itemPanel6, wxID_ANY, _("Other"));
	wxStaticBoxSizer* itemStaticBoxSizer30 = new wxStaticBoxSizer(itemStaticBoxSizer30Static, wxVERTICAL);
	itemBoxSizer28->Add(itemStaticBoxSizer30, 0, wxALIGN_TOP|wxALL, 5);
	m_Sync_Timestamp = new wxCheckBox( itemPanel6, ID_SYNC_TIMESTAMP, _("Retain Timestamps"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Sync_Timestamp->SetValue(false);
	itemStaticBoxSizer30->Add(m_Sync_Timestamp, 0, wxALIGN_LEFT|wxALL, 5);

	m_Sync_Attributes = new wxCheckBox( itemPanel6, ID_SYNC_ATTRIB, _("Retain Attributes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Sync_Attributes->SetValue(false);
	itemStaticBoxSizer30->Add(m_Sync_Attributes, 0, wxALIGN_LEFT|wxALL, 5);

	m_Sync_Ignore_Readonly = new wxCheckBox( itemPanel6, ID_SYNC_IGNORERO, _("Ignore Read-Only"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Sync_Ignore_Readonly->SetValue(false);
	itemStaticBoxSizer30->Add(m_Sync_Ignore_Readonly, 0, wxALIGN_LEFT|wxALL, 5);

	m_Sync_Ignore_DaylightS = new wxCheckBox( itemPanel6, ID_SYNC_IGNOREDS, _("Ignore Daylight Savings"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Sync_Ignore_DaylightS->SetValue(false);
	itemStaticBoxSizer30->Add(m_Sync_Ignore_DaylightS, 0, wxALIGN_LEFT|wxALL, 5);
	
	
	wxBoxSizer* itemBoxSizer002 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer28->Add(itemBoxSizer002, 1, wxGROW|wxALL|wxALIGN_CENTER_VERTICAL, 5);	
	
	wxButton* itemButtonSyncOK = new wxButton( itemPanel6, ID_SYNC_OK, _("OK"));
	itemBoxSizer002->Add(itemButtonSyncOK, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	wxButton* itemButtonSyncPreview = new wxButton( itemPanel6, ID_SYNC_PREVIEW , _("Preview"));
	itemBoxSizer002->Add(itemButtonSyncPreview, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer8->Add(itemBoxSizer17, 1, wxGROW|wxALL, 5);
	wxBoxSizer* itemBoxSizer18 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer17->Add(itemBoxSizer18, 1, wxGROW|wxALL, 5);
	wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer18->Add(itemBoxSizer19, 0, wxGROW|wxALL, 5);
	
	//Source section
	m_Sync_Source_Txt = new wxTextCtrl( itemPanel6, ID_SYNC_SOURCE_TXT, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer19->Add(m_Sync_Source_Txt, 1, wxALIGN_TOP|wxALL, 5);

	wxButton* itemButton21 = new wxButton( itemPanel6, ID_SYNC_SOURCE_BTN, _("..."), wxDefaultPosition, wxSize(25, 25), 0 );
	itemBoxSizer19->Add(itemButton21, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_Sync_Source_Tree = new wxVirtualDirTreeCtrl( itemPanel6, ID_SYNC_SOURCE_TREE, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS |wxTR_LINES_AT_ROOT|wxTR_HIDE_ROOT|wxTR_SINGLE );
	itemBoxSizer18->Add(m_Sync_Source_Tree, 1, wxGROW|wxALL, 5);

	wxBoxSizer* itemBoxSizer23 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer17->Add(itemBoxSizer23, 1, wxGROW|wxALL, 5);
	wxBoxSizer* itemBoxSizer24 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer23->Add(itemBoxSizer24, 0, wxGROW|wxALL, 5);

	//Destination section
	m_Sync_Dest_Txt = new wxTextCtrl( itemPanel6, ID_SYNC_DEST_TXT, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer24->Add(m_Sync_Dest_Txt, 1, wxALIGN_TOP|wxALL, 5);

	wxButton* itemButton26 = new wxButton( itemPanel6, ID_SYNC_DEST_BTN, _("..."), wxDefaultPosition, wxSize(25, 25), 0 );
	itemBoxSizer24->Add(itemButton26, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_Sync_Dest_Tree = new wxVirtualDirTreeCtrl( itemPanel6, ID_SYNC_DEST_TREE, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS |wxTR_LINES_AT_ROOT|wxTR_HIDE_ROOT|wxTR_SINGLE  );
	itemBoxSizer23->Add(m_Sync_Dest_Tree, 1, wxGROW|wxALL, 5);

	//Backup section
	
	
	wxPanel* itemPanel35 = new wxPanel( m_Notebook, ID_PANEL_BACKUP, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* itemBoxSizer36 = new wxBoxSizer(wxVERTICAL);
	itemPanel35->SetSizer(itemBoxSizer36);
	
	wxBoxSizer* BackupTop = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer36->Add(BackupTop, 0, wxALIGN_LEFT|wxALL, 5);
	
	wxBoxSizer* BackupRow1 = new wxBoxSizer(wxHORIZONTAL);
	BackupTop->Add(BackupRow1, 0, wxALIGN_LEFT|wxALL, 0);
	//Jobs section
	wxStaticBox* itemStaticBoxSizer38Static = new wxStaticBox(itemPanel35, wxID_ANY, _("Job Name"));
	wxStaticBoxSizer* itemStaticBoxSizer38 = new wxStaticBoxSizer(itemStaticBoxSizer38Static, wxHORIZONTAL);
	BackupRow1->Add(itemStaticBoxSizer38, 0, wxALIGN_TOP|wxALL, 5);
	wxArrayString m_Backup_Job_SelectStrings;
	m_Backup_Job_Select = new wxComboBox( itemPanel35, ID_BACKUP_JOB_SELECT, _T(""), wxDefaultPosition, wxDefaultSize, m_Backup_Job_SelectStrings, wxCB_DROPDOWN );
	itemStaticBoxSizer38->Add(m_Backup_Job_Select, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton0012 = new wxBitmapButton( itemPanel35, ID_BACKUP_JOB_SAVE, itemFrame1->GetBitmapResource(wxT("save.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemStaticBoxSizer38->Add(itemBitmapButton0012, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton0013 = new wxBitmapButton( itemPanel35, ID_BACKUP_JOB_ADD, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemStaticBoxSizer38->Add(itemBitmapButton0013, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton0014 = new wxBitmapButton( itemPanel35, ID_BACKUP_JOB_REMOVE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemStaticBoxSizer38->Add(itemBitmapButton0014, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	wxArrayString m_Backup_FunctionStrings;
	m_Backup_FunctionStrings.Add(_("Complete"));
	m_Backup_FunctionStrings.Add(_("Update"));
	m_Backup_FunctionStrings.Add(_("Incremental"));
	m_Backup_Function = new wxRadioBox( itemPanel35, ID_BACKUP_FUNCTION, _("Type"), wxDefaultPosition, wxDefaultSize, m_Backup_FunctionStrings, 1, wxRA_SPECIFY_COLS );
	m_Backup_Function->SetSelection(0);
	BackupRow1->Add(m_Backup_Function, 0, wxALIGN_TOP|wxALL, 5);

	wxArrayString m_Backup_FormatStrings;
	m_Backup_FormatStrings.Add(_("Zip"));
	m_Backup_FormatStrings.Add(_("7-Zip"));
	m_Backup_Format = new wxRadioBox( itemPanel35, ID_BACKUP_FORMAT, _("Format"), wxDefaultPosition, wxDefaultSize, m_Backup_FormatStrings, 1, wxRA_SPECIFY_COLS );
	m_Backup_Format->SetSelection(0);
	BackupRow1->Add(m_Backup_Format, 0, wxALIGN_TOP|wxALL, 5);

	wxArrayString m_Backup_RatioStrings;
	m_Backup_RatioStrings.Add(_("Low"));
	m_Backup_RatioStrings.Add(_("Normal"));
	m_Backup_RatioStrings.Add(_("Maximum"));
	m_Backup_Ratio = new wxRadioBox( itemPanel35, ID_BACKUP_RATIO, _("Compression Ratio"), wxDefaultPosition, wxDefaultSize, m_Backup_RatioStrings, 1, wxRA_SPECIFY_COLS );
	m_Backup_Ratio->SetSelection(1);
	BackupRow1->Add(m_Backup_Ratio, 0, wxALIGN_TOP|wxALL, 5);

	wxStaticBox* itemStaticBoxSizer65Static = new wxStaticBox(itemPanel35, wxID_ANY, _("Other"));
	wxStaticBoxSizer* itemStaticBoxSizer65 = new wxStaticBoxSizer(itemStaticBoxSizer65Static, wxVERTICAL);
	BackupRow1->Add(itemStaticBoxSizer65, 0, wxALIGN_TOP|wxALL, 5);

	m_Backup_IsPass = new wxCheckBox(itemPanel35, ID_BACKUP_ISPASS, _("Password?"));
	itemStaticBoxSizer65->Add(m_Backup_IsPass, 0, wxALIGN_TOP|wxALL, 5);

	//Buttons
	wxBoxSizer* itemBoxSizer005 = new wxBoxSizer(wxVERTICAL);
	BackupRow1->Add(itemBoxSizer005, 1, wxGROW|wxALL|wxALIGN_CENTER_VERTICAL, 5);	
	
	wxButton* itemButtonBackupOK = new wxButton( itemPanel35, ID_BACKUP_OK, _("OK"));
	itemBoxSizer005->Add(itemButtonBackupOK, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	wxButton* itemButtonBackupPreview = new wxButton( itemPanel35, ID_BACKUP_PREVIEW , _("Preview"));
	itemBoxSizer005->Add(itemButtonBackupPreview, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);	
	
	wxButton* itemButtonBackupRestore = new wxButton( itemPanel35, ID_BACKUP_RESTORE , _("Restore"));
	itemBoxSizer005->Add(itemButtonBackupRestore, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);	


	wxBoxSizer* BackupRow2 = new wxBoxSizer(wxHORIZONTAL);
	BackupTop->Add(BackupRow2, 0, wxEXPAND, 0);	
	
	//Rules section	
	wxStaticBox* itemStaticBoxSizer42Static = new wxStaticBox(itemPanel35, wxID_ANY, _("Rules"));
	wxStaticBoxSizer* itemStaticBoxSizer42 = new wxStaticBoxSizer(itemStaticBoxSizer42Static, wxHORIZONTAL);
	BackupRow2->Add(itemStaticBoxSizer42, 0, wxALL, 5);

	wxArrayString m_Backup_RulesStrings;
	m_Backup_Rules = new wxComboBox( itemPanel35, ID_BACKUP_RULES, _T(""), wxDefaultPosition, wxDefaultSize, m_Backup_RulesStrings, wxCB_DROPDOWN );
	itemStaticBoxSizer42->Add(m_Backup_Rules, 0, wxALL, 5);
	
	//Backup location
	
	wxStaticBox* BackupLocationStatic = new wxStaticBox(itemPanel35, wxID_ANY, _("Backup Location"));
	wxStaticBoxSizer* BackupLocationSizer = new wxStaticBoxSizer(BackupLocationStatic, wxHORIZONTAL);
	BackupRow2->Add(BackupLocationSizer, 1, wxALL, 5);

	m_Backup_Location = new wxTextCtrl( itemPanel35, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxDefaultSize, 0 );
	BackupLocationSizer->Add(m_Backup_Location,1, wxALL, 5);

	wxButton* itemButton49 = new wxButton( itemPanel35, ID_BACKUP_LOCATION, _("..."), wxDefaultPosition, wxSize(25, -1), 0 );
	BackupLocationSizer->Add(itemButton49, 0, wxALL, 5);
	
	//Start of everything else

	wxBoxSizer* itemBoxSizer50 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer36->Add(itemBoxSizer50, 0, wxALIGN_LEFT|wxALL, 5);
	itemBoxSizer50->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

	wxStaticText* itemStaticText52 = new wxStaticText( itemPanel35, wxID_STATIC, _("Files to Backup"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer50->Add(itemStaticText52, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

	wxBoxSizer* itemBoxSizer53 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer36->Add(itemBoxSizer53, 1, wxGROW|wxALL, 5);
	m_Backup_DirCtrl = new wxGenericDirCtrl( itemPanel35, ID_BACKUP_DIRCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxBORDER_THEME, _T("All files (*.*)|*.*"), 0 );
	itemBoxSizer53->Add(m_Backup_DirCtrl, 1, wxGROW|wxALL, 5);

	wxBoxSizer* itemBoxSizer55 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer53->Add(itemBoxSizer55, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	wxBitmapButton* itemBitmapButton56 = new wxBitmapButton( itemPanel35, ID_BACKUP_ADD, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer55->Add(itemBitmapButton56, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton57 = new wxBitmapButton( itemPanel35, ID_BACKUP_REMOVE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer55->Add(itemBitmapButton57, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	m_Backup_TreeCtrl = new wxVirtualDirTreeCtrl( itemPanel35, ID_BACKUP_TREECTRL, wxDefaultPosition, wxSize(100, 100), wxTR_HAS_BUTTONS |wxTR_LINES_AT_ROOT|wxTR_HIDE_ROOT|wxTR_SINGLE );
	itemBoxSizer53->Add(m_Backup_TreeCtrl, 1, wxGROW|wxALL, 5);

	wxBoxSizer* itemBoxSizer59 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer53->Add(itemBoxSizer59, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	wxBitmapButton* itemBitmapButton60 = new wxBitmapButton( itemPanel35, ID_BACKUP_ADDVAR, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer59->Add(itemBitmapButton60, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	
	//Secure

	wxPanel* itemPanel68 = new wxPanel( m_Notebook, ID_PANEL_SECURE, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* itemBoxSizer69 = new wxBoxSizer(wxVERTICAL);
	itemPanel68->SetSizer(itemBoxSizer69);

	wxBoxSizer* itemBoxSizer87 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer69->Add(itemBoxSizer87, 0, wxALIGN_LEFT|wxALL, 5);
	
	wxBoxSizer* itemBoxSizer3000 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer87->Add(itemBoxSizer3000, 0, wxALIGN_LEFT|wxALL, 0);	
	
	//Jobs section

	wxStaticBox* itemStaticBoxSizer73Static = new wxStaticBox(itemPanel68, wxID_ANY, _("Job Name"));
	wxStaticBoxSizer* itemStaticBoxSizer73 = new wxStaticBoxSizer(itemStaticBoxSizer73Static, wxHORIZONTAL);
	itemBoxSizer3000->Add(itemStaticBoxSizer73, 0, wxALIGN_TOP|wxALL, 5);
	wxArrayString m_Secure_Job_SelectStrings;
	m_Secure_Job_Select = new wxComboBox( itemPanel68, ID_SECURE_JOB_SELECT, _T(""), wxDefaultPosition, wxDefaultSize, m_Secure_Job_SelectStrings, wxCB_DROPDOWN );
	itemStaticBoxSizer73->Add(m_Secure_Job_Select, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton75 = new wxBitmapButton( itemPanel68, ID_SECURE_JOB_SAVE, itemFrame1->GetBitmapResource(wxT("save.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemStaticBoxSizer73->Add(itemBitmapButton75, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton76 = new wxBitmapButton( itemPanel68, ID_SECURE_JOB_ADD, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemStaticBoxSizer73->Add(itemBitmapButton76, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton77 = new wxBitmapButton( itemPanel68, ID_SECURE_JOB_REMOVE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemStaticBoxSizer73->Add(itemBitmapButton77, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	//Rules section

	wxStaticBox* itemStaticBoxSizer71Static = new wxStaticBox(itemPanel68, wxID_ANY, _("Rules"));
	wxStaticBoxSizer* itemStaticBoxSizer71 = new wxStaticBoxSizer(itemStaticBoxSizer71Static, wxHORIZONTAL);
	itemBoxSizer3000->Add(itemStaticBoxSizer71, 1, wxALIGN_TOP|wxALL|wxGROW, 5);
	wxArrayString m_Secure_RulesStrings;
	m_Secure_Rules = new wxComboBox( itemPanel68, ID_SECURE_RULES, _T(""), wxDefaultPosition, wxDefaultSize, m_Secure_RulesStrings, wxCB_DROPDOWN );
	itemStaticBoxSizer71->Add(m_Secure_Rules, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	//Options
	
	wxBoxSizer* itemBoxSizer3001 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer87->Add(itemBoxSizer3001, 0, wxALIGN_LEFT|wxALL, 0);	
	
	wxArrayString m_Secure_FunctionStrings;
	m_Secure_FunctionStrings.Add(_("Encrypt"));
	m_Secure_FunctionStrings.Add(_("Decrypt"));
	m_Secure_Function = new wxRadioBox( itemPanel68, ID_SECURE_FUNCTION, _("Function"), wxDefaultPosition, wxDefaultSize, m_Secure_FunctionStrings, 1, wxRA_SPECIFY_COLS );
	m_Secure_Function->SetSelection(0);
	itemBoxSizer3001->Add(m_Secure_Function, 1, wxGROW|wxALIGN_TOP|wxALL, 5);

	wxArrayString m_Secure_FormatStrings;
	m_Secure_FormatStrings.Add(_("Rijndael"));
	m_Secure_FormatStrings.Add(_("Blowfish (Decrypt Only)"));
	m_Secure_Format = new wxRadioBox( itemPanel68, ID_SECURE_FORMAT, _("Format"), wxDefaultPosition, wxDefaultSize, m_Secure_FormatStrings, 1, wxRA_SPECIFY_COLS );
	m_Secure_Format->SetSelection(0);
	itemBoxSizer3001->Add(m_Secure_Format, 0, wxALIGN_TOP|wxALL, 5);

	/*wxStaticBox* itemStaticBoxSizer90Static = new wxStaticBox(itemPanel68, wxID_ANY, _("Password (Repeated)"));
	wxStaticBoxSizer* itemStaticBoxSizer90 = new wxStaticBoxSizer(itemStaticBoxSizer90Static, wxVERTICAL);
	itemBoxSizer87->Add(itemStaticBoxSizer90, 0, wxALIGN_TOP|wxALL, 5);
	m_Secure_Pass = new wxTextCtrl( itemPanel68, ID_SECURE_PASS, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	m_Secure_Pass->SetMinSize(wxSize(125, -1));
	itemStaticBoxSizer90->Add(m_Secure_Pass, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	m_Secure_Repass = new wxTextCtrl( itemPanel68, ID_SECURE_REPASS, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	itemStaticBoxSizer90->Add(m_Secure_Repass, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	m_Secure_Repass->SetMinSize(wxSize(125, -1));*/
	
	wxBoxSizer* itemBoxSizer3002 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer87->Add(itemBoxSizer3002, 1, wxGROW|wxALL|wxALIGN_CENTER_VERTICAL, 5);	
	
	wxButton* itemButtonSecureOK = new wxButton( itemPanel68, ID_SECURE_OK, _("OK"));
	itemBoxSizer3002->Add(itemButtonSecureOK, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	wxButton* itemButtonSecurePreview = new wxButton( itemPanel68, ID_SECURE_PREVIEW , _("Preview"));
	itemBoxSizer3002->Add(itemButtonSecurePreview, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);	

	//Main secure stuff
	wxBoxSizer* itemBoxSizer78 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer69->Add(itemBoxSizer78, 1, wxGROW|wxALL, 5);
	
	
	m_Secure_DirCtrl = new wxGenericDirCtrl( itemPanel68, ID_SECURE_DIRCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
	itemBoxSizer78->Add(m_Secure_DirCtrl, 1, wxGROW|wxALL, 5);

	wxBoxSizer* itemBoxSizer80 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer78->Add(itemBoxSizer80, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	wxBitmapButton* itemBitmapButton81 = new wxBitmapButton( itemPanel68, ID_SECURE_ADD, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer80->Add(itemBitmapButton81, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton82 = new wxBitmapButton( itemPanel68, ID_SECURE_REMOVE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer80->Add(itemBitmapButton82, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	m_Secure_TreeCtrl = new wxVirtualDirTreeCtrl( itemPanel68, ID_SECURE_TREECTRL, wxDefaultPosition, wxSize(100, 100), wxTR_HAS_BUTTONS |wxTR_LINES_AT_ROOT|wxTR_HIDE_ROOT|wxTR_SINGLE );
	itemBoxSizer78->Add(m_Secure_TreeCtrl, 1, wxGROW|wxALL, 5);

	wxBoxSizer* itemBoxSizer84 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer78->Add(itemBoxSizer84, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	wxBitmapButton* itemBitmapButton85 = new wxBitmapButton( itemPanel68, ID_SECURE_ADDVAR, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer84->Add(itemBitmapButton85, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton86 = new wxBitmapButton( itemPanel68, ID_SECURE_MAKERELATIVE, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer84->Add(itemBitmapButton86, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	
	//Rules section!!! (Not rules for backup)

	wxPanel* itemPanel93 = new wxPanel( m_Notebook, ID_RULES, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* itemBoxSizer94 = new wxBoxSizer(wxVERTICAL);
	itemPanel93->SetSizer(itemBoxSizer94);

	wxBoxSizer* itemBoxSizer95 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer94->Add(itemBoxSizer95, 0, wxALIGN_LEFT|wxALL, 5);
	wxStaticText* itemStaticText96 = new wxStaticText( itemPanel93, wxID_STATIC, _("Rules name"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer95->Add(itemStaticText96, 0, wxALIGN_LEFT|wxALL, 5);

	wxBoxSizer* itemBoxSizer97 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer95->Add(itemBoxSizer97, 0, wxALIGN_LEFT|wxALL, 5);
	wxArrayString m_Rules_ComboStrings;
	m_Rules_Combo = new wxComboBox( itemPanel93, ID_RULES_COMBO, _T(""), wxDefaultPosition, wxDefaultSize, m_Rules_ComboStrings, wxCB_READONLY );
	itemBoxSizer97->Add(m_Rules_Combo, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton99 = new wxBitmapButton( itemPanel93, ID_RULES_SAVE, itemFrame1->GetBitmapResource(wxT("save.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer97->Add(itemBitmapButton99, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton100 = new wxBitmapButton( itemPanel93, ID_RULES_ADD, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer97->Add(itemBitmapButton100, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton101 = new wxBitmapButton( itemPanel93, ID_RULES_REMOVE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer97->Add(itemBitmapButton101, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer102 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer94->Add(itemBoxSizer102, 1, wxGROW|wxALL, 5);
	wxStaticText* itemStaticText103 = new wxStaticText( itemPanel93, wxID_STATIC, _("Files to exclude (file name, path or extension)"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer102->Add(itemStaticText103, 0, wxALIGN_LEFT|wxALL, 5);

	wxBoxSizer* itemBoxSizer104 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer102->Add(itemBoxSizer104, 1, wxGROW|wxALL, 5);
	wxArrayString m_Rules_FileExcludeStrings;
	m_Rules_FileExclude = new wxListBox( itemPanel93, ID_RULE_FILE_EXCLUDE, wxDefaultPosition, wxDefaultSize, m_Rules_FileExcludeStrings, wxLB_SINGLE );
	itemBoxSizer104->Add(m_Rules_FileExclude, 1, wxGROW|wxALL, 5);

	wxBoxSizer* itemBoxSizer106 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer104->Add(itemBoxSizer106, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	wxBitmapButton* itemBitmapButton107 = new wxBitmapButton( itemPanel93, ID_RULES_ADD_FILEEXCLUDE, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer106->Add(itemBitmapButton107, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton108 = new wxBitmapButton( itemPanel93, ID_RULES_REMOVE_FILEEXCLUDE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer106->Add(itemBitmapButton108, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer109 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer94->Add(itemBoxSizer109, 1, wxGROW|wxALL, 5);
	wxStaticText* itemStaticText110 = new wxStaticText( itemPanel93, wxID_STATIC, _("Folders to exclude (folder name or path)"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer109->Add(itemStaticText110, 0, wxALIGN_LEFT|wxALL, 5);

	wxBoxSizer* itemBoxSizer111 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer109->Add(itemBoxSizer111, 1, wxGROW|wxALL, 5);
	wxArrayString m_Rules_FolderExcludeStrings;
	m_Rules_FolderExclude = new wxListBox( itemPanel93, ID_RULES_FOLDER_EXCLUDE, wxDefaultPosition, wxDefaultSize, m_Rules_FolderExcludeStrings, wxLB_SINGLE );
	itemBoxSizer111->Add(m_Rules_FolderExclude, 1, wxGROW|wxALL, 5);

	wxBoxSizer* itemBoxSizer113 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer111->Add(itemBoxSizer113, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	wxBitmapButton* itemBitmapButton114 = new wxBitmapButton( itemPanel93, ID_RULES_ADD_FOLDEREXCLUDE, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer113->Add(itemBitmapButton114, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton115 = new wxBitmapButton( itemPanel93, ID_RULES_REMOVE_FOLDEREXCLUDE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer113->Add(itemBitmapButton115, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBoxSizer* itemBoxSizer116 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer94->Add(itemBoxSizer116, 1, wxGROW|wxALL, 5);
	wxStaticText* itemStaticText117 = new wxStaticText( itemPanel93, wxID_STATIC, _("Locations to always include (file/folder name, path or  file extension)"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer116->Add(itemStaticText117, 0, wxALIGN_LEFT|wxALL, 5);

	wxBoxSizer* itemBoxSizer118 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer116->Add(itemBoxSizer118, 1, wxGROW|wxALL, 5);
	wxArrayString m_Rules_LocationIncludeStrings;
	m_Rules_LocationInclude = new wxListBox( itemPanel93, ID_RULES_LOCATION_INCLUDE, wxDefaultPosition, wxDefaultSize, m_Rules_LocationIncludeStrings, wxLB_SINGLE );
	itemBoxSizer118->Add(m_Rules_LocationInclude, 1, wxGROW|wxALL, 5);

	wxBoxSizer* itemBoxSizer120 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer118->Add(itemBoxSizer120, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	wxBitmapButton* itemBitmapButton121 = new wxBitmapButton( itemPanel93, ID_RULES_ADD_LOCATIONINCLUDE, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer120->Add(itemBitmapButton121, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton122 = new wxBitmapButton( itemPanel93, ID_RULES_REMOVE_LOCATIONINCLUDE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	itemBoxSizer120->Add(itemBitmapButton122, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	//Portable variables

	wxPanel* itemPanel130 = new wxPanel( m_Notebook, ID_PANEL4, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );

	wxBoxSizer* PvarAll = new wxBoxSizer(wxVERTICAL);
    itemPanel130->SetSizer(PvarAll);

    wxBoxSizer* PvarTop = new wxBoxSizer(wxHORIZONTAL);
    PvarAll->Add(PvarTop, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemPanel130, wxID_STATIC, _("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
    PvarTop->Add(itemStaticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString m_Pvar_NameStrings;
    m_Pvar_Name = new wxComboBox( itemPanel130, ID_PVAR_NAME, _T(""), wxDefaultPosition, wxDefaultSize, m_Pvar_NameStrings, wxCB_DROPDOWN );
    PvarTop->Add(m_Pvar_Name, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
    wxBitmapButton* PvarAdd = new wxBitmapButton( itemPanel130, ID_PVAR_ADD, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    PvarTop->Add(PvarAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBitmapButton* PvarRemove = new wxBitmapButton( itemPanel130, ID_PVAR_REMOVE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    PvarTop->Add(PvarRemove, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* PvarBottom = new wxBoxSizer(wxHORIZONTAL);
    PvarAll->Add(PvarBottom, 1, wxGROW|wxALL, 5);

    m_Pvar_List = new wxListCtrl( itemPanel130, ID_PVAR_LIST, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
    PvarBottom->Add(m_Pvar_List, 1, wxGROW|wxALL, 5);

    wxBoxSizer* PvarRight = new wxBoxSizer(wxVERTICAL);
    PvarBottom->Add(PvarRight, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* PvarAddItem = new wxBitmapButton( itemPanel130, ID_PVAR_ADDITEM, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    PvarRight->Add(PvarAddItem, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBitmapButton* PvarRemoveItem = new wxBitmapButton( itemPanel130, ID_PVAR_REMOVEITEM, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    PvarRight->Add(PvarRemoveItem, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	//Scripting

	wxPanel* itemPanel131 = new wxPanel( m_Notebook, ID_PANEL6, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* itemBoxSizer132 = new wxBoxSizer(wxVERTICAL);
	itemPanel131->SetSizer(itemBoxSizer132);
	
	wxBoxSizer* itemBoxSizer140 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer132->Add(itemBoxSizer140, 0, wxALIGN_LEFT|wxALL, 5);

	wxStaticBox* ScriptStaticBox = new wxStaticBox(itemPanel131, wxID_ANY, _("Script Name"));
	wxStaticBoxSizer* ScriptStaticBoxSizer = new wxStaticBoxSizer(ScriptStaticBox, wxHORIZONTAL);
	itemBoxSizer140->Add(ScriptStaticBoxSizer, 0, wxALIGN_TOP|wxALL, 5);


	wxArrayString itemComboBox134Strings;
	wxComboBox* m_Script_Name = new wxComboBox( itemPanel131, ID_SCRIPT_NAME, _T(""), wxDefaultPosition, wxDefaultSize, itemComboBox134Strings, wxCB_DROPDOWN );
	ScriptStaticBoxSizer->Add(m_Script_Name, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	wxBitmapButton* itemBitmapButton135 = new wxBitmapButton( itemPanel131, ID_SCRIPT_SAVE, itemFrame1->GetBitmapResource(wxT("save.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	ScriptStaticBoxSizer->Add(itemBitmapButton135, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton136 = new wxBitmapButton( itemPanel131, ID_SCRIPT_ADD, itemFrame1->GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	ScriptStaticBoxSizer->Add(itemBitmapButton136, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton137 = new wxBitmapButton( itemPanel131, ID_SCRIPT_REMOVE, itemFrame1->GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
	ScriptStaticBoxSizer->Add(itemBitmapButton137, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* itemButton142 = new wxButton( itemPanel131, ID_SCRIPT_EXECUTE, _("Execute"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer140->Add(itemButton142, 0, wxALIGN_TOP|wxALL, 10);

	wxBoxSizer* itemBoxSizer138 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer132->Add(itemBoxSizer138, 1, wxGROW|wxALL, 5);
	m_Script_Rich = new wxRichTextCtrl( itemPanel131, ID_SCRIPT_RICH, _T(""), wxDefaultPosition, wxSize(100, 100), wxWANTS_CHARS );
	itemBoxSizer138->Add(m_Script_Rich, 1, wxGROW|wxALL, 5);

	//Settings


	wxPanel* itemPanel143 = new wxPanel( m_Notebook, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL );

	wxBoxSizer* itemBoxSizer1000 = new wxBoxSizer(wxVERTICAL);
	itemPanel143->SetSizer(itemBoxSizer1000);


	wxString m_Settings_TabsStrings[] = {
		_("Icons + Text"),
		_("Text")
	};
	m_Settings_TabStyle = new wxRadioBox (itemPanel143, ID_SETTINGS_TABSTYLE, _("Tab style (requires restart)"), wxDefaultPosition, wxDefaultSize,2,  m_Settings_TabsStrings,2 ,wxRA_SPECIFY_ROWS);
	itemBoxSizer1000->Add(m_Settings_TabStyle, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);	
	
	wxStaticBox* LanguageStaticBox = new wxStaticBox(itemPanel143, wxID_ANY, _("Language"));
	wxStaticBoxSizer* LanguageStaticBoxSizer = new wxStaticBoxSizer(LanguageStaticBox, wxHORIZONTAL);
	itemBoxSizer1000->Add(LanguageStaticBoxSizer, 0, wxALIGN_TOP|wxALL, 5);
	wxArrayString m_Settings_LanguageStrings = GetLanguages();
	m_Settings_Language = new wxComboBox( itemPanel143, ID_SETTINGS_LANGUAGE, _T(""), wxDefaultPosition, wxDefaultSize, m_Settings_LanguageStrings, wxCB_DROPDOWN );
	m_Settings_Language->SetMinSize(wxSize(125, -1));
	LanguageStaticBoxSizer->Add(m_Settings_Language, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5);
	m_Settings_Language->SetStringSelection(wxLocale::FindLanguageInfo(wxGetApp().m_Settings->GetLanguageCode())->Description);
	

	m_Settings_TabStyle->SetStringSelection(wxGetApp().m_Settings->GetTabStyle());

	//Add the panels
	wxBitmap syncbitmap = GetBitmapResource(wxT("sync.png"));
	wxBitmap backupbitmap = GetBitmapResource(wxT("backup.png"));
	wxBitmap securebitmap = GetBitmapResource(wxT("secure.png"));
	wxBitmap settingsbitmap = GetBitmapResource(wxT("settings.png"));
	
	if(wxGetApp().m_Settings->GetTabStyle() == _("Text")){
		syncbitmap = wxNullBitmap;
		backupbitmap = wxNullBitmap;
		securebitmap = wxNullBitmap;
		settingsbitmap = wxNullBitmap;
	}

	m_Notebook->AddPage(itemPanel6, _("Sync"), false, syncbitmap);
	m_Notebook->AddPage(itemPanel35, _("Backup"), false, backupbitmap);
	m_Notebook->AddPage(itemPanel68, _("Secure"), false, securebitmap);
	m_Notebook->AddPage(itemPanel93, _("Rules"), false);
	m_Notebook->AddPage(itemPanel130, _("Portable Variables"), false);
	m_Notebook->AddPage(itemPanel131, _("Scripting"), false);
	m_Notebook->AddPage(itemPanel143, _("Settings"), false, settingsbitmap);

	itemFrame1->GetAuiManager().AddPane(m_Notebook, wxAuiPaneInfo()
	                                    .Name(_T("Pane3")).Centre().CaptionVisible(false).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false).PaneBorder(false));

	GetAuiManager().Update();

	//Set the settings

	unsigned int i = 0;
	unsigned int count = m_Notebook->GetPageCount();
	while(m_Notebook->GetPageText(m_Notebook->GetSelection()) != wxGetApp().m_Settings->GetPosition()){
		i ++;
		if(i < count){
			m_Notebook->AdvanceSelection();
		}
		else{
			m_Notebook->SetSelection(0);
			break;
		}
	}

	//Set the drag and drop targets
	m_Sync_Source_Txt->SetDropTarget(new DnDFileTreeText(m_Sync_Source_Txt, m_Sync_Source_Tree));
	m_Sync_Dest_Txt->SetDropTarget(new DnDFileTreeText(m_Sync_Dest_Txt, m_Sync_Dest_Tree));
	
	m_Sync_Source_Tree->SetDropTarget(new DnDFileTreeText(m_Sync_Source_Txt, m_Sync_Source_Tree));
	m_Sync_Dest_Tree->SetDropTarget(new DnDFileTreeText(m_Sync_Dest_Txt, m_Sync_Dest_Tree));
	
	m_Backup_TreeCtrl->SetDropTarget(new DnDFileTree(m_Backup_TreeCtrl));
	m_Secure_TreeCtrl->SetDropTarget(new DnDFileTree(m_Secure_TreeCtrl));
	
	m_Sync_Source_Tree->SetSync(true);
	m_Sync_Dest_Tree->SetSync(true);

	//Set up the rules boxes
	SetRulesBox(m_Sync_Rules);
	SetRulesBox(m_Backup_Rules);
	SetRulesBox(m_Secure_Rules);
	SetRulesBox(m_Rules_Combo);

	//Set up the jobs boxes
	SetJobsBox(m_Sync_Job_Select, _("Sync"));
	SetJobsBox(m_Backup_Job_Select, _("Backup"));
	SetJobsBox(m_Secure_Job_Select, _("Secure"));
	
	//Set the portable variables box
	SetVariablesBox(m_Pvar_Name);
	
	wxListItem column;
	m_Pvar_List->InsertColumn(0, column);
	m_Pvar_List->InsertColumn(1, column);
	
	this->SetIcon(wxIcon(wxT("Toucan.ico"), wxBITMAP_TYPE_ICO));
}

//Show tooltips
bool frmMain::ShowToolTips()
{
	return true;
}

//Get bitmap resources
wxBitmap frmMain::GetBitmapResource( const wxString& name )
{
	wxUnusedVar(name);
	if (name == _T("save.png")) {
		wxBitmap bitmap(_T("save.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	} 
	else if (name == _T("add.png")) {
		wxBitmap bitmap(_T("add.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	} 
	else if (name == _T("ok.png")) {
		wxBitmap bitmap(_T("ok.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("preview.png")) {
		wxBitmap bitmap(_T("preview.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("remove.png")) {
		wxBitmap bitmap(_T("remove.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("sync.png")) {
		wxBitmap bitmap(_T("sync.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("backup.png")) {
		wxBitmap bitmap(_T("backup.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("secure.png")) {
		wxBitmap bitmap(_T("secure.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("settings.png")) {
		wxBitmap bitmap(_T("settings.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	return wxNullBitmap;
}

//Get icon resources
wxIcon frmMain::GetIconResource( const wxString& name )
{
	wxUnusedVar(name);
	return wxNullIcon;
}


/*!
* wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BACKUP_ADD
*/

void frmMain::OnBackupAddClick(wxCommandEvent& event)
{
	wxCursor cursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(cursor);
	m_BackupLocations->Add(m_Backup_DirCtrl->GetPath());
	m_Backup_TreeCtrl->AddNewPath(m_Backup_DirCtrl->GetPath());
	wxCursor stdcursor(wxCURSOR_ARROW);
	this->SetCursor(stdcursor);
}


/*!
* wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BACKUP_REMOVE
*/

void frmMain::OnBackupRemoveClick(wxCommandEvent& event)
{
	//Checks to see if it is a top level item that is being removed
	if (m_Backup_TreeCtrl->GetItemParent(m_Backup_TreeCtrl->GetSelection()) == m_Backup_TreeCtrl->GetRootItem()) {
		//Iterate throught the global list and remove the item
		for (unsigned int i = 0; i < m_BackupLocations->Count() - 1; i++) {
			if (m_BackupLocations->Item(i) == m_Backup_TreeCtrl->GetItemText(m_Backup_TreeCtrl->GetSelection())) {
				m_BackupLocations->RemoveAt(i);
			}
			if (m_BackupLocations->Item(i).AfterLast(wxFILE_SEP_PATH) == m_Backup_TreeCtrl->GetItemText(m_Backup_TreeCtrl->GetSelection())) {
				m_BackupLocations->RemoveAt(i);
			}
		}
		m_Backup_TreeCtrl->Delete(m_Backup_TreeCtrl->GetSelection());
	}
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SECURE_ADD
 */

void frmMain::OnSecureAddClick(wxCommandEvent& event)
{
	wxCursor cursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(cursor);
	//Add path to the global list and to the virtualdirtreectrl
	m_SecureLocations->Add(m_Secure_DirCtrl->GetPath());
	m_Secure_TreeCtrl->AddNewPath(m_Secure_DirCtrl->GetPath());
	wxCursor stdcursor(wxCURSOR_ARROW);
	this->SetCursor(stdcursor);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SECURE_REMOVE
 */

void frmMain::OnSecureRemoveClick(wxCommandEvent& event)
{
	//Checks to see if it is a top level item that is being removed
	if (m_Secure_TreeCtrl->GetItemText(m_Secure_TreeCtrl->GetItemParent(m_Secure_TreeCtrl->GetSelection())) == m_Secure_TreeCtrl->GetItemText(m_Secure_TreeCtrl->GetRootItem())) {
		m_Secure_TreeCtrl->Delete(m_Secure_TreeCtrl->GetSelection());
		//Iterate throught the global list and remove the item		
		for (unsigned int i = 0; i < m_SecureLocations->Count(); i++) {
			if (m_SecureLocations->Item(i) == m_Secure_TreeCtrl->GetItemText(m_Secure_TreeCtrl->GetSelection())) {
				m_SecureLocations->RemoveAt(i);
			}
			if (m_SecureLocations->Item(i).AfterLast(wxFILE_SEP_PATH) == m_Secure_TreeCtrl->GetItemText(m_Secure_TreeCtrl->GetSelection())) {
				m_SecureLocations->RemoveAt(i);
			}
		}
	}
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SYNC_SOURCE_BTN
 */

void frmMain::OnSyncSourceBtnClick(wxCommandEvent& event)
{

	//Need to replace this with a better browser
	wxDirDialog dialog(this,_("Please select the source folder."), m_Sync_Source_Txt->GetValue());
	if (dialog.ShowModal() == wxID_OK) {
		wxCursor cursor(wxCURSOR_ARROWWAIT);
		this->SetCursor(cursor);
		m_Sync_Source_Tree->DeleteAllItems();
		m_Sync_Source_Tree->AddRoot(_("Hidden root"));
		m_Sync_Source_Tree->SetRoot(dialog.GetPath());
		m_Sync_Source_Tree->AddNewPath(dialog.GetPath());
		m_Sync_Source_Txt->SetValue(dialog.GetPath());
		wxCursor cursorstd(wxCURSOR_ARROW);
		this->SetCursor(cursorstd);
	}
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SYNC_DEST_BTN
 */

void frmMain::OnSyncDestBtnClick(wxCommandEvent& event)
{
	//Need to replace this with a better browser	
	wxDirDialog dialog(this,_("Please select the desination folder."), m_Sync_Dest_Txt->GetValue());
	if (dialog.ShowModal() == wxID_OK) {
		wxCursor cursor(wxCURSOR_ARROWWAIT);
		this->SetCursor(cursor);
		m_Sync_Dest_Tree->DeleteAllItems();
		m_Sync_Dest_Tree->AddRoot(_("Hidden root"));
		m_Sync_Dest_Tree->SetRoot(dialog.GetPath());
		m_Sync_Dest_Tree->AddNewPath(dialog.GetPath());
		m_Sync_Dest_Txt->SetValue(dialog.GetPath());
		wxCursor stdcursor(wxCURSOR_ARROW);
		this->SetCursor(stdcursor);
	}
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_ADD_FILEEXCLUDE
 */

void frmMain::OnRulesAddFileexcludeClick(wxCommandEvent& event)
{
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("File to exclude"), _("This dialog needs to be replaced"));
	if (dialog->ShowModal() == wxID_OK) {
		m_Rules_FileExclude->Append(dialog->GetValue());
	}
	delete dialog;
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_REMOVE_FILEEXCLUDE
 */

void frmMain::OnRulesRemoveFileexcludeClick(wxCommandEvent& event)
{
	m_Rules_FileExclude->Delete(m_Rules_FileExclude->GetSelection());
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_ADD_FOLDEREXCLUDE
 */

void frmMain::OnRulesAddFolderexcludeClick(wxCommandEvent& event)
{
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("Folder to exclude"), _("This dialog needs to be replaced"));
	if (dialog->ShowModal() == wxID_OK) {
		m_Rules_FolderExclude->Append(dialog->GetValue());
	}
	delete dialog;
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_REMOVE_FOLDEREXCLUDE
 */

void frmMain::OnRulesRemoveFolderexcludeClick(wxCommandEvent& event)
{
	m_Rules_FolderExclude->Delete(m_Rules_FolderExclude->GetSelection());
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_ADD_LocationInclude
 */

void frmMain::OnRulesAddFiledeleteClick(wxCommandEvent& event)
{
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("File to Delete"), _("This dialog needs to be replaced"));
	if (dialog->ShowModal() == wxID_OK) {
		m_Rules_FileDelete->Append(dialog->GetValue());
	}
	delete dialog;
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_REMOVE_LocationInclude
 */

void frmMain::OnRulesRemoveFiledeleteClick(wxCommandEvent& event)
{
	m_Rules_LocationInclude->Delete(m_Rules_FileDelete->GetSelection());
}



/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_SAVE
 */

void frmMain::OnRulesSaveClick(wxCommandEvent& event)
{
	//Get all of the form data into arraystrings
	wxArrayString arrLocationsInclude, arrFolderExclude, arrFileExclude, arrFileDelete;
	for (unsigned int i = 0; i < m_Rules_LocationInclude->GetCount(); i++) {
		arrLocationsInclude.Add(m_Rules_LocationInclude->GetString(i));
	}
	for (unsigned int j = 0; j < m_Rules_FolderExclude->GetCount(); j++) {
		arrFolderExclude.Add(m_Rules_FolderExclude->GetString(j));
	}
	for (unsigned int k = 0; k < m_Rules_FileExclude->GetCount(); k++) {
		arrFileExclude.Add(m_Rules_FileExclude->GetString(k));
	}

	//Create the rule set and add the arraystrings to it
	Rules rules;
	rules.SetLocationsToInclude(arrLocationsInclude);
	rules.SetFilesToExclude(arrFileExclude);
	rules.SetFoldersToExclude(arrFolderExclude);
	//rules.SetFilesToDelete(arrFileDelete);
	if (m_Rules_Combo->GetStringSelection() != wxEmptyString) {
		rules.TransferToFile(m_Rules_Combo->GetStringSelection());
	} else {
		ErrorBox(_("You must select a name for this set of Rules"));
	}
	//Set up the rules boxes
	SetRulesBox(m_Sync_Rules);
	SetRulesBox(m_Backup_Rules);
	SetRulesBox(m_Secure_Rules);

}



/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_ADD
 */

void frmMain::OnRulesAddClick(wxCommandEvent& event)
{
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("File to include"), _("This dialog needs to be replaced"));
	if (dialog->ShowModal() == wxID_OK) {
		m_Rules_Combo->AppendString(dialog->GetValue());
		m_Rules_Combo->SetStringSelection(dialog->GetValue());
		m_Rules_LocationInclude->Clear();
		m_Rules_FileExclude->Clear();
		m_Rules_FolderExclude->Clear();
	}
	delete dialog;
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_REMOVE
 */

void frmMain::OnRulesRemoveClick(wxCommandEvent& event)
{
	m_Rules_Combo->Delete(m_Rules_Combo->GetSelection());
	m_Rules_LocationInclude->Clear();
	m_Rules_FileExclude->Clear();
	m_Rules_FolderExclude->Clear();
	wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Rules.ini"));
	config->DeleteGroup(m_Rules_Combo->GetStringSelection());
	delete config;
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_RULES_COMBO
 */

void frmMain::OnRulesComboSelected(wxCommandEvent& event)
{
	//Clear the existing rules
	m_Rules_LocationInclude->Clear();
	m_Rules_FileExclude->Clear();
	m_Rules_FolderExclude->Clear();
	
	//Create a new rule set
	Rules rules;
	if (rules.TransferFromFile(m_Rules_Combo->GetStringSelection())) {
		//Loop through the array of rules and add them to the form
		for (unsigned int i = 0; i < rules.GetLocationsToIncude().GetCount(); i++) {
			m_Rules_LocationInclude->Append(rules.GetLocationsToIncude().Item(i));
		}
		for (unsigned int j = 0; j < rules.GetFilesToExclude().GetCount(); j++) {
			m_Rules_FileExclude->Append(rules.GetFilesToExclude().Item(j));
		}
		for (unsigned int k = 0; k < rules.GetFoldersToExclude().GetCount(); k++) {
			m_Rules_FolderExclude->Append(rules.GetFoldersToExclude().Item(k));
		}
	}

}



/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SECURE_JOB_SAVE
 */

void frmMain::OnSecureJobSaveClick(wxCommandEvent& event)
{
	wxCursor cursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(cursor);
	//Create the securedata and fill it, surpressing any warning as the user may want to save before finished
	SecureData data;
	if (data.TransferFromForm(this, false)) {
		if (m_Secure_Job_Select->GetStringSelection() != wxEmptyString) {
			data.TransferToFile(m_Secure_Job_Select->GetStringSelection());
		} else {
			ErrorBox(_("Please chose a job to save to"));
		}
	}
	//Create a new fileconfig and write the extra fields to it
	wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
	config->Write(m_Secure_Job_Select->GetStringSelection() + wxT("/Rules"),  m_Secure_Rules->GetStringSelection());
	config->Write(m_Secure_Job_Select->GetStringSelection() + wxT("/Type"),  _("Secure"));
	delete config;
	wxCursor stdcursor(wxCURSOR_ARROW);
	this->SetCursor(stdcursor);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SECURE_JOB_ADD
 */

void frmMain::OnSecureJobAddClick(wxCommandEvent& event)
{
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("Job name"));
	if (dialog->ShowModal() == wxID_OK) {
		m_Secure_Job_Select->Append(dialog->GetValue());
		m_Secure_Job_Select->SetStringSelection(dialog->GetValue());
	}
	delete dialog;
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SECURE_JOB_REMOVE
 */

void frmMain::OnSecureJobRemoveClick(wxCommandEvent& event)
{
	if (m_Secure_Job_Select->GetStringSelection() != wxEmptyString) {
		wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
		config->DeleteGroup(m_Secure_Job_Select->GetStringSelection());
		m_Secure_Job_Select->Delete(m_Secure_Job_Select->GetSelection());
		delete config;
	}
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_SECURE_JOB_SELECT
 */

void frmMain::OnSecureJobSelectSelected(wxCommandEvent& event)
{
	wxCursor cursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(cursor);
	SecureData data;
	if (data.TransferFromFile(m_Secure_Job_Select->GetStringSelection())) {
		data.TransferToForm(this);
		wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
		m_Secure_Rules->SetStringSelection(config->Read(m_Secure_Job_Select->GetStringSelection() + wxT("/Rules")));
		delete config;
	}
	wxCursor stdcursor(wxCURSOR_ARROW);
	this->SetCursor(stdcursor);
}




/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SYNC_JOB_SAVE
 */

void frmMain::OnSyncJobSaveClick(wxCommandEvent& event)
{
	wxCursor cursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(cursor);
	SyncData data;
	if (data.TransferFromForm(this)) {
		if (m_Sync_Job_Select->GetStringSelection() != wxEmptyString) {
			data.TransferToFile(m_Sync_Job_Select->GetStringSelection());
		} else {
			ErrorBox(_("Please chose a job to save to"));
		}
	}
	wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Jobs.ini") );
	config->Write(m_Sync_Job_Select->GetStringSelection() + wxT("/Rules"),  m_Sync_Rules->GetStringSelection());
	config->Write(m_Sync_Job_Select->GetStringSelection() + wxT("/Type"),  _("Sync"));
	config->Flush();
	delete config;
	wxCursor stdcursor(wxCURSOR_ARROW);
	this->SetCursor(stdcursor);
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BACKUP_JOB_SAVE
 */

void frmMain::OnBackupJobSaveClick(wxCommandEvent& event)
{
	wxCursor cursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(cursor);
	BackupData data;
	if (data.TransferFromForm(this, false)) {
		if (m_Backup_Job_Select->GetStringSelection() != wxEmptyString) {
			data.TransferToFile(m_Backup_Job_Select->GetStringSelection());
		} 
		else {
			ErrorBox(_("Please chose a job to save to"));
		}
	}
	wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
	config->Write(m_Backup_Job_Select->GetStringSelection() + wxT("/Rules"),  m_Backup_Rules->GetStringSelection());
	config->Write(m_Backup_Job_Select->GetStringSelection() + wxT("/Type"),  _("Backup"));
	config->Flush();
	delete config;
	wxCursor stdcursor(wxCURSOR_ARROW);
	this->SetCursor(stdcursor);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SYNC_JOB_ADD
 */

void frmMain::OnSyncJobAddClick(wxCommandEvent& event)
{
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("Job name"));
	if (dialog->ShowModal() == wxID_OK) {
		m_Sync_Job_Select->Append(dialog->GetValue());
		m_Sync_Job_Select->SetStringSelection(dialog->GetValue());
	}
	delete dialog;
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SYNC_JOB_REMOVE
 */

void frmMain::OnSyncJobRemoveClick(wxCommandEvent& event)
{
	if (m_Sync_Job_Select->GetStringSelection() != wxEmptyString) {
		wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
		config->DeleteGroup(m_Sync_Job_Select->GetStringSelection());
		m_Sync_Job_Select->Delete(m_Sync_Job_Select->GetSelection());
	}
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_SYNC_JOB_SELECT
 */

void frmMain::OnSyncJobSelectSelected(wxCommandEvent& event)
{
	wxCursor cursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(cursor);
	SyncData data;
	if (data.TransferFromFile(m_Sync_Job_Select->GetStringSelection())) {
		//data.Output();
		data.TransferToForm(this);
		wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
		m_Sync_Rules->SetStringSelection(config->Read(m_Sync_Job_Select->GetStringSelection() + wxT("/Rules")));
		delete config;
	}
	wxCursor stdcursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(stdcursor);
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_ADD_FILEINCLUDE
 */

void frmMain::OnRulesAddLocationincludeClick(wxCommandEvent& event)
{
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("Location to include"), _("This dialog needs to be replaced"));
	if (dialog->ShowModal() == wxID_OK) {
		m_Rules_LocationInclude->Append(dialog->GetValue());
	}
	delete dialog;
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_RULES_REMOVE_FILEINCLUDE
 */

void frmMain::OnRulesRemoveLocationincludeClick(wxCommandEvent& event)
{
	m_Rules_FileDelete->Delete(m_Rules_LocationInclude->GetSelection());
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BACKUP_LOCATION
 */

void frmMain::OnBackupLocationClick(wxCommandEvent& event)
{
	if(m_Backup_Function->GetStringSelection() == _("Incremental")){
		wxDirDialog dialog(this,_("Please select the folder to store your backups"),m_Backup_Location->GetValue());
		if (dialog.ShowModal() == wxID_OK){
			m_Backup_Location->SetValue(dialog.GetPath());
		}
	}
	else{
		wxFileDialog dialog(this,_("Please choose a file to backup to"), wxPathOnly(m_Backup_Location->GetValue()), wxEmptyString, wxT("7 Zip (*.7z)|*.7z|Zip Files (*.zip)|*.zip|All Files (*.*)|*.*"), wxFD_SAVE);
		if (dialog.ShowModal() == wxID_OK) {
			m_Backup_Location->SetValue(dialog.GetPath());
		}
	}
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BACKUP_JOB_ADD
 */

void frmMain::OnBackupJobAddClick(wxCommandEvent& event)
{
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("Job name"));
	if (dialog->ShowModal() == wxID_OK) {
		m_Backup_Job_Select->Append(dialog->GetValue());
		m_Backup_Job_Select->SetStringSelection(dialog->GetValue());
	}
	delete dialog;
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BACKUP_JOB_REMOVE
 */

void frmMain::OnBackupJobRemoveClick(wxCommandEvent& event)
{
	if (m_Backup_Job_Select->GetStringSelection() != wxEmptyString) {
		wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
		config->DeleteGroup(m_Backup_Job_Select->GetStringSelection());
		m_Backup_Job_Select->Delete(m_Backup_Job_Select->GetSelection());
		delete config;
	}
}


/*!
 * wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_BACKUP_JOB_SELECT
 */

void frmMain::OnBackupJobSelectSelected(wxCommandEvent& event)
{
	wxCursor cursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(cursor);
	BackupData data;
	if (data.TransferFromFile(m_Backup_Job_Select->GetStringSelection())) {
		data.TransferToForm(this);
		wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
		m_Backup_Rules->SetStringSelection(config->Read(m_Backup_Job_Select->GetStringSelection() + wxT("/Rules")));
		delete config;
	}
	wxCursor stdcursor(wxCURSOR_ARROWWAIT);
	this->SetCursor(stdcursor);
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SYNC_OK
 */

void frmMain::OnSyncOKClick(wxCommandEvent& event)
{
	SyncData data;
	if (data.TransferFromForm(this)) {
		data.TransferToFile(wxT("LastSyncJob"));
	}
	wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Jobs.ini") );
	config->Write(wxT("LastSyncJob/Rules"),  m_Sync_Rules->GetStringSelection());
	config->Write(wxT("LastSyncJob/Type"),  _("Sync"));
	config->Flush();
	delete config;
	wxArrayString arrScript;
	arrScript.Add(wxT("Sync \"LastSyncJob\""));
	ParseScript(arrScript);
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SYNC_PREVIEW
 */

void frmMain::OnSyncPreviewClick(wxCommandEvent& event)
{
	wxString strPath = m_Sync_Source_Txt->GetValue();
	/*Stupid horrible hack as folders do not have a trailing slash whereas roots do, nasty horrible code that needs to be changed
	in the future in the vdtc code*/
	if (strPath[strPath.length()-1] == wxFILE_SEP_PATH) {
		strPath = strPath.Left(strPath.Length() - 1); 
	}
	m_Sync_Source_Txt->SetValue(strPath);
	strPath = m_Sync_Dest_Txt->GetValue();
	if (strPath[strPath.length()-1] == wxFILE_SEP_PATH) {
		strPath = strPath.Left(strPath.Length() - 1); 
	}
	m_Sync_Dest_Txt->SetValue(strPath);
	m_Sync_Dest_Tree->DeleteAllItems();
	m_Sync_Dest_Tree->AddRoot(_("Hidden root"));
	m_Sync_Dest_Tree->SetRoot(m_Sync_Dest_Txt->GetValue());
	m_Sync_Dest_Tree->SetRootOpp(m_Sync_Source_Txt->GetValue());
	m_Sync_Dest_Tree->SetPreview(true);
	m_Sync_Dest_Tree->SetMode(m_Sync_Function->GetStringSelection());
	m_Sync_Dest_Tree->AddNewPath(m_Sync_Dest_Txt->GetValue());
			
	//Code for equalise function
	if(m_Sync_Function->GetStringSelection() == _("Equalise")){
		m_Sync_Source_Tree->DeleteAllItems();
		m_Sync_Source_Tree->AddRoot(_("Hidden root"));
		m_Sync_Source_Tree->SetRoot(m_Sync_Source_Txt->GetValue());
		m_Sync_Source_Tree->SetRootOpp(m_Sync_Dest_Txt->GetValue());
		m_Sync_Source_Tree->SetPreview(true);
		m_Sync_Source_Tree->SetMode(m_Sync_Function->GetStringSelection());
		m_Sync_Source_Tree->AddNewPath(m_Sync_Source_Txt->GetValue());
	}
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BACKUP_OK
 */

void frmMain::OnBackupOKClick(wxCommandEvent& event)
{
	BackupData data;
	if (data.TransferFromForm(this, true)) {
		data.TransferToFile(wxT("LastBackupJob"));
		wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
		config->Write(wxT("LastBackupJob/Rules"),  m_Backup_Rules->GetStringSelection());
		config->Write(wxT("LastBackupJob/Type"),  _("Backup"));
		config->Flush();
		delete config;
		wxArrayString arrScript;
		arrScript.Add(wxT("Backup \"LastBackupJob\""));
		ParseScript(arrScript);
	}
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BACKUP_PREVIEW
 */

void frmMain::OnBackupPreviewClick(wxCommandEvent& event)
{
	//Create a new rule set and populate it from the form
	Rules rules;
	if (m_Backup_Rules->GetStringSelection() != wxEmptyString) {
		rules.TransferFromFile(m_Backup_Rules->GetStringSelection());
	}
	//Set up the tree ctrl for previewing
	m_Backup_TreeCtrl->SetPreview(true);
	m_Backup_TreeCtrl->SetRules(rules);
	//Delete all items and re-add the root
	m_Backup_TreeCtrl->DeleteAllItems();
	m_Backup_TreeCtrl->AddRoot(wxT("Hidden root"));
	for (unsigned int i = 0; i < m_BackupLocations->GetCount(); i++) {
		//Loop through all the the filenames listed in the array and read them to the tree
		m_Backup_TreeCtrl->AddNewPath(m_BackupLocations->Item(i));
	}
	//Turn off preview
	m_Secure_TreeCtrl->SetPreview(false);
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BACKUP_RESTORE
 */

void frmMain::OnBackupRestoreClick(wxCommandEvent& event)
{
	frmRestore *window = new frmRestore(NULL, ID_FRMRESTORE, _("Restore"));	
	window->ShowModal();
}

void frmMain::OnCloseWindow(wxCloseEvent& event)
{
	wxGetApp().m_Settings->SetPosition(m_Notebook->GetPageText(m_Notebook->GetSelection()));
	wxGetApp().m_Settings->SetTabStyle(m_Settings_TabStyle->GetStringSelection());
	wxGetApp().m_Settings->SetLanguageCode(wxLocale::FindLanguageInfo(m_Settings_Language->GetStringSelection())->CanonicalName);
	wxGetApp().m_Settings->TransferToFile();
	delete m_BackupLocations;
	delete m_SecureLocations;
	wxGetApp().MainWindow->Destroy();
	wxGetApp().ProgressWindow->Destroy();
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SECURE_OK
 */

void frmMain::OnSecureOKClick(wxCommandEvent& event)
{
	SecureData data;
	if (data.TransferFromForm(this, true)) {
		data.TransferToFile(wxT("LastSecureJob"));
		//Create a new fileconfig and write the extra fields to it
		wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""),  wxGetApp().GetSettingsPath()+ wxT("Jobs.ini"));
		config->Write(wxT("LastSecureJob/Rules"),  m_Secure_Rules->GetStringSelection());
		config->Write(wxT("LastSecureJob/Type"),  _("Secure"));
		delete config;
		wxArrayString arrScript;
		arrScript.Add(wxT("Secure \"LastSecureJob\""));
		ParseScript(arrScript);	
	}
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_SECURE_PREVIEW
 */

void frmMain::OnSecurePreviewClick(wxCommandEvent& event)
{
	//Create a new rule set and populate it from the form
	Rules rules;
	if (m_Secure_Rules->GetStringSelection() != wxEmptyString) {
		rules.TransferFromFile(m_Secure_Rules->GetStringSelection());
	}
	//Set up the tree ctrl for previewing
	m_Secure_TreeCtrl->SetPreview(true);
	m_Secure_TreeCtrl->SetRules(rules);
	//Delete all items and re-add the root
	m_Secure_TreeCtrl->DeleteAllItems();
	m_Secure_TreeCtrl->AddRoot(wxT("Hidden root"));
	for (unsigned int i = 0; i < m_SecureLocations->GetCount(); i++) {
		//Loop through all the the filenames listed in the array and readd them to the tree
		m_Secure_TreeCtrl->AddNewPath(m_SecureLocations->Item(i));
	}
	//Turn off preview
	m_Secure_TreeCtrl->SetPreview(false);
}

///////////////////////////////////////////////////////////
//The portable variables stuff, still under construction!//
///////////////////////////////////////////////////////////


void frmMain::OnPvarAddClick(wxCommandEvent& event)
{	
    wxTextEntryDialog dialog(this, _("Please enter the name for the new portable variable"), _("New Portable Variable") ,wxEmptyString, wxOK|wxCANCEL);
	if(dialog.ShowModal() == wxID_OK){
        wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Variables.ini") );
        if(!config->HasGroup(dialog.GetValue())){
            m_Pvar_List->ClearAll();
            wxListItem column;
            m_Pvar_List->InsertColumn(0, column);
            m_Pvar_List->InsertColumn(1, column);
            config->Write(dialog.GetValue() + wxT("/") + wxGetFullHostName() , wxEmptyString);
            config->Write(dialog.GetValue() + wxT("/") + _("Other") , wxEmptyString);
            config->Flush();
            m_Pvar_Name->Append(dialog.GetValue());
            m_Pvar_Name->SetStringSelection(dialog.GetValue());
            m_Pvar_List->InsertItem(0, wxT("Test"));
            m_Pvar_List->SetItem(0, 0, wxGetFullHostName() );
            m_Pvar_List->InsertItem(1, wxT("Test"));
            m_Pvar_List->SetItem(1, 0, _("Other"));
        }
        else{
            ErrorBox(_("There is already a Portable Variable with this name."));
        }
    }
}

void frmMain::OnPvarRemoveClick(wxCommandEvent& event)
{	
	wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Variables.ini"));
	config->DeleteGroup(m_Pvar_Name->GetValue());
	config->Flush();
	m_Pvar_Name->Delete(m_Pvar_Name->GetSelection());
	m_Pvar_Name->SetValue(wxEmptyString);
	m_Pvar_List->ClearAll();
	wxListItem column;
	m_Pvar_List->InsertColumn(0, column);
	m_Pvar_List->InsertColumn(1, column);
}

void frmMain::OnPvarNameSelected(wxCommandEvent& event)
{	
	m_Pvar_List->DeleteAllItems();
	
	wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Variables.ini"));
    config->SetPath(m_Pvar_Name->GetValue());
    
	long dummy;
    wxString str;
    int i = 0;
	
    bool bCont = config->GetFirstEntry(str, dummy);
    while ( bCont ) {
        m_Pvar_List->InsertItem(i, wxT("Test"));
        m_Pvar_List->SetItem(i, 0, str);
		//Return the config to the top level
        config->SetPath(wxT("/"));
        wxString strTest = config->Read(m_Pvar_Name->GetValue() + wxT("/") + str, wxT("Cannot Find Value"));
        m_Pvar_List->SetItem(i, 1, strTest);
		//Put the config location back
        config->SetPath(m_Pvar_Name->GetValue());    
        bCont = config->GetNextEntry(str, dummy);
        i++;
    }
	m_Pvar_List->SetColumnWidth(0, -1);
	m_Pvar_List->SetColumnWidth(1, -1);
    delete config;
}

void frmMain::OnPvarAddItemClick(wxCommandEvent& event)
{	
	int j = m_Pvar_List->GetItemCount();
	m_Pvar_List->InsertItem(j, wxT("Test"));
	m_Pvar_List->SetItem(j, 0, wxGetFullHostName() );
	wxString caption = _("Choose a directory");
	wxString wildcard = _("All Files (*.*)|*.*");
	wxString defaultFilename = wxEmptyString;
	wxString defaultDir = wxT("/");
	wxString strPath;
	wxDirDialog dialog(this, caption, defaultDir);
	if (dialog.ShowModal() == wxID_OK){
		m_Pvar_List->SetItem(j, 1, dialog.GetPath());
	}
	else{
		m_Pvar_List->SetItem(j, 1, wxEmptyString);
	}
	wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Variables.ini") );
	config->Write(m_Pvar_Name->GetValue() + wxT("/") + wxGetFullHostName() , dialog.GetPath());
	config->Flush();
	delete config;
}

void frmMain::OnPvarRemoveItemClick(wxCommandEvent& event)
{	
	wxString selected;
	long item = -1;
	for ( ;; )
	{
		item = m_Pvar_List->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if ( item == -1 )
		break;
		selected = m_Pvar_List->GetItemText(item);
		m_Pvar_List->DeleteItem(item);
	}
	wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Variables.ini") );
	config->DeleteEntry(m_Pvar_Name->GetValue() + wxT("/") + selected);
	config->Flush();
	delete config;
}

void frmMain::OnPvarListActivated(wxListEvent& event)
{	
	long item = -1;
	for ( ;; )
	{
		item = m_Pvar_List->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if ( item == -1 )
		break;
		
		wxListItem PreviousColumn1;
		PreviousColumn1.m_itemId = item;
		PreviousColumn1.m_col = 1;
		PreviousColumn1.m_mask = wxLIST_MASK_TEXT;
		m_Pvar_List->GetItem(PreviousColumn1);
		wxString strPreviousColumn1 = PreviousColumn1.m_text;
		wxTextEntryDialog location(this, _("Please insert the location you want to point to."), _("Location"), strPreviousColumn1, wxOK);
		if(location.ShowModal() == wxID_OK){
			m_Pvar_List->SetItem(item , 1, location.GetValue());
		}
		m_Pvar_List->SetColumnWidth(0, -1);
		m_Pvar_List->SetColumnWidth(1, -1);
		wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Variables.ini") );
		config->Write(m_Pvar_Name->GetValue() + wxT("/") + m_Pvar_List->GetItemText(item), location.GetValue());
		config->Flush();
		delete config;
	}
}

void frmMain::OnScriptExecute(wxCommandEvent& event)
{	
	wxArrayString arrLines;
	for(signed int i = 0; i < m_Script_Rich->GetNumberOfLines(); i++){
		arrLines.Add(m_Script_Rich->GetLineText(i));
	}
	ParseScript(arrLines);
}

void frmMain::OnScriptSelected(wxCommandEvent& event)
{	
	wxFileConfig *config = new wxFileConfig(wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Scripts.ini"));
	wxString strFile = config->Read(m_Script_Name->GetStringSelection() + wxT("/") + wxT("Script"));
	wxArrayString arrContents = StringToArrayString(strFile, wxT("#"));
	for(unsigned int i = 0; i < arrContents.Count(); i++){
		m_Script_Rich->AppendText(arrContents.Item(i));
	}
	delete config;	
}

void frmMain::OnScriptSaveClick(wxCommandEvent& event)
{	
	wxArrayString arrContents;
	for(signed int i = 0; i < m_Script_Rich->GetNumberOfLines(); i++){
		arrContents.Add(m_Script_Rich->GetLineText(i));
	}
	wxFileConfig *config = new wxFileConfig(wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Scripts.ini"));
	config->Write(m_Script_Name->GetStringSelection() + wxT("/") + wxT("Script"), ArrayStringToString(arrContents, wxT("#")));
	config->Flush();
	delete config;
	
}

void frmMain::OnScriptRemoveClick(wxCommandEvent& event)
{	
	wxFileConfig *config = new wxFileConfig(wxT(""), wxT(""), wxGetApp().GetSettingsPath() + wxT("Scripts.ini"));
	config->DeleteGroup(m_Script_Name->GetStringSelection());
	m_Script_Name->Delete(m_Script_Name->GetSelection());
}

void frmMain::OnScriptAddClick(wxCommandEvent& event)
{	
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("Script name"));
	if (dialog->ShowModal() == wxID_OK) {
		m_Script_Name->Append(dialog->GetValue());
		m_Script_Name->SetStringSelection(dialog->GetValue());
	}
	delete dialog;
}

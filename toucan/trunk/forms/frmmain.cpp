/////////////////////////////////////////////////////////////////////////////////
// Author:      Steven Lamerton
// Copyright:   Copyright (C) 2006-2009 Steven Lamerton
// License:     GNU GPL 2 (See readme for more info)
/////////////////////////////////////////////////////////////////////////////////

#include <wx/stdpaths.h>
#include <wx/aboutdlg.h>
#include <wx/fileconf.h>
#include <wx/html/helpctrl.h>
#include <wx/listctrl.h>
#include <wx/fontpicker.h>
#include <wx/dir.h>
#include <wx/gbsizer.h>
#include <wx/wx.h>

#include "frmmain.h"
#include "frmprogress.h"
#include "frmvariable.h"
#include "../toucan.h"
#include "../dragndrop.h"
#include "../script.h"
#include "../basicfunctions.h"
#include "../settings.h"
#include "../variables.h"
#include "../data/securedata.h"
#include "../data/backupdata.h"
#include "../sync/syncdata.h"
#include "../controls/extendeddirctrl.h"
#include "../controls/virtualdirtreectrl.h"

//frmMain event table
BEGIN_EVENT_TABLE(frmMain, wxFrame)

	//Sync
	EVT_BUTTON(ID_SYNC_OK, frmMain::OnSyncOKClick)
	EVT_BUTTON(ID_SYNC_PREVIEW, frmMain::OnSyncPreviewClick)	
	EVT_BUTTON(ID_SYNC_SOURCE_EXPAND, frmMain::OnSyncSourceExpandClick)
	EVT_BUTTON(ID_SYNC_DEST_EXPAND, frmMain::OnSyncDestExpandClick)
	EVT_BUTTON(ID_SYNC_JOB_ADD, frmMain::OnSyncJobAddClick)
	EVT_BUTTON(ID_SYNC_JOB_REMOVE, frmMain::OnSyncJobRemoveClick)
	EVT_BUTTON(ID_SYNC_JOB_SAVE, frmMain::OnSyncJobSaveClick)
	EVT_COMBOBOX(ID_SYNC_JOB_SELECT, frmMain::OnSyncJobSelectSelected)
	EVT_BUTTON(ID_SYNC_SOURCE_BTN, frmMain::OnSyncSourceBtnClick)
	EVT_BUTTON(ID_SYNC_DEST_BTN, frmMain::OnSyncDestBtnClick)
	EVT_TREE_ITEM_RIGHT_CLICK(ID_SYNC_SOURCE_TREE, frmMain::OnSyncSourceTreeRightClick)
	EVT_TREE_ITEM_RIGHT_CLICK(ID_SYNC_DEST_TREE, frmMain::OnSyncDestTreeRightClick)
	EVT_TREE_ITEM_GETTOOLTIP(ID_SYNC_SOURCE_TREE, frmMain::OnSyncTreeCtrlTooltip)
	EVT_TREE_ITEM_GETTOOLTIP(ID_SYNC_DEST_TREE, frmMain::OnSyncTreeCtrlTooltip)

	//Backup
	EVT_BUTTON(ID_BACKUP_OK, frmMain::OnBackupOKClick)
	EVT_BUTTON(ID_BACKUP_PREVIEW, frmMain::OnBackupPreviewClick)
	EVT_BUTTON(ID_BACKUP_LOCATION, frmMain::OnBackupLocationClick)
	EVT_BUTTON(ID_BACKUP_ADD, frmMain::OnBackupAddClick)
	EVT_BUTTON(ID_BACKUP_REMOVE, frmMain::OnBackupRemoveClick)
	EVT_BUTTON(ID_BACKUP_EXPAND, frmMain::OnBackupExpandClick)	
	EVT_BUTTON(ID_BACKUP_JOB_SAVE, frmMain::OnBackupJobSaveClick)
	EVT_BUTTON(ID_BACKUP_JOB_ADD, frmMain::OnBackupJobAddClick)
	EVT_BUTTON(ID_BACKUP_JOB_REMOVE, frmMain::OnBackupJobRemoveClick)
	EVT_BUTTON(ID_BACKUP_ADDVAR, frmMain::OnBackupAddVarClick)
	EVT_COMBOBOX(ID_BACKUP_JOB_SELECT, frmMain::OnBackupJobSelectSelected)
	EVT_COMMAND_SCROLL_CHANGED(ID_BACKUP_RATIO, frmMain::OnBackupRatioChanged)
	EVT_TREE_ITEM_GETTOOLTIP(ID_BACKUP_TREECTRL, frmMain::OnBackupTreeCtrlTooltip)
	EVT_TREE_ITEM_RIGHT_CLICK(ID_BACKUP_TREECTRL, frmMain::OnBackupTreeRightClick)
	EVT_RADIOBOX(ID_BACKUP_FUNCTION, frmMain::OnBackupFunctionSelected)

	//Secure
	EVT_BUTTON(ID_SECURE_OK, frmMain::OnSecureOKClick)
	EVT_BUTTON(ID_SECURE_PREVIEW, frmMain::OnSecurePreviewClick)
	EVT_COMBOBOX(ID_SECURE_JOB_SELECT, frmMain::OnSecureJobSelectSelected)
	EVT_BUTTON(ID_SECURE_JOB_SAVE, frmMain::OnSecureJobSaveClick)
	EVT_BUTTON(ID_SECURE_JOB_ADD, frmMain::OnSecureJobAddClick)
	EVT_BUTTON(ID_SECURE_JOB_REMOVE, frmMain::OnSecureJobRemoveClick)
	EVT_BUTTON(ID_SECURE_ADD, frmMain::OnSecureAddClick)
	EVT_BUTTON(ID_SECURE_REMOVE, frmMain::OnSecureRemoveClick)
	EVT_BUTTON(ID_SECURE_EXPAND, frmMain::OnSecureExpandClick)	
	EVT_BUTTON(ID_SECURE_ADDVAR, frmMain::OnSecureAddVarClick)	
	EVT_TREE_ITEM_GETTOOLTIP(ID_SECURE_TREECTRL, frmMain::OnSecureTreeCtrlTooltip)
	EVT_TREE_ITEM_RIGHT_CLICK(ID_SECURE_TREECTRL, frmMain::OnSecureTreeRightClick)
	
	//Rules
	EVT_COMBOBOX(ID_RULES_COMBO, frmMain::OnRulesComboSelected)
	EVT_BUTTON(ID_RULES_SAVE, frmMain::OnRulesSaveClick)
	EVT_BUTTON(ID_RULES_ADD, frmMain::OnRulesAddClick)
	EVT_BUTTON(ID_RULES_REMOVE, frmMain::OnRulesRemoveClick)
	EVT_BUTTON(ID_RULES_ADD_FILEEXCLUDE, frmMain::OnRulesAddFileexcludeClick)
	EVT_BUTTON(ID_RULES_REMOVE_FILEEXCLUDE, frmMain::OnRulesRemoveFileexcludeClick)
	EVT_BUTTON(ID_RULES_ADD_FOLDEREXCLUDE, frmMain::OnRulesAddFolderexcludeClick)
	EVT_BUTTON(ID_RULES_REMOVE_FOLDEREXCLUDE, frmMain::OnRulesRemoveFolderexcludeClick)
	EVT_BUTTON(ID_RULES_ADD_LOCATIONINCLUDE, frmMain::OnRulesAddLocationincludeClick)
	EVT_BUTTON(ID_RULES_REMOVE_LOCATIONINCLUDE, frmMain::OnRulesRemoveLocationincludeClick)
	
	//Portable Variables
	EVT_BUTTON(ID_VARIABLES_ADD, frmMain::OnVariablesAddClick)
	EVT_BUTTON(ID_VARIABLES_REMOVE, frmMain::OnVariablesRemoveClick)
	EVT_BUTTON(ID_VARIABLES_ADDITEM, frmMain::OnVariablesAddItemClick)
	EVT_BUTTON(ID_VARIABLES_REMOVEITEM, frmMain::OnVariablesRemoveItemClick)
	EVT_COMBOBOX(ID_VARIABLES_NAME, frmMain::OnVariablesNameSelected)
	EVT_LIST_ITEM_ACTIVATED(ID_VARIABLES_LIST, frmMain::OnVariablesListActivated)
	
	//Script
	EVT_BUTTON(ID_SCRIPT_EXECUTE, frmMain::OnScriptExecute)
	EVT_BUTTON(ID_SCRIPT_SAVE, frmMain::OnScriptSaveClick)
	EVT_BUTTON(ID_SCRIPT_ADD, frmMain::OnScriptAddClick)
	EVT_BUTTON (ID_SCRIPT_REMOVE, frmMain::OnScriptRemoveClick)
	EVT_COMBOBOX(ID_SCRIPT_NAME, frmMain::OnScriptSelected)
	
	//Other
	EVT_CLOSE(frmMain::OnCloseWindow)
	EVT_BUTTON(wxID_ABOUT, frmMain::OnAboutClick)
	EVT_BUTTON(wxID_APPLY, frmMain::OnSettingsApplyClick)
	EVT_AUINOTEBOOK_PAGE_CHANGED(ID_AUINOTEBOOK, frmMain::OnTabChanged)
	
	//Menu
	EVT_MENU(ID_MENU_FILEEXCLUDE_EXTENSION, frmMain::OnMenuFileExcludeExtensionClick)
	EVT_MENU(ID_MENU_FILEEXCLUDE_NAME, frmMain::OnMenuFileExcludeNameClick)
	EVT_MENU(ID_MENU_LOCATIONINCLUDE_EXTENSION, frmMain::OnMenuLocationIncludeExtensionClick)
	EVT_MENU(ID_MENU_LOCATIONINCLUDE_NAME, frmMain::OnMenuLocationIncludeNameClick)
	EVT_MENU(ID_MENU_FOLDEREXCLUDE_NAME, frmMain::OnMenuFolderExcludeNameClick)
	
END_EVENT_TABLE()

//Constructor
frmMain::frmMain(){
	//Set up the sizes and so forth
	int height, width, x, y;
	wxClientDisplayRect(&x, &y, &width, &height);

	wxPoint position((int)(wxGetApp().m_Settings->GetX() * width), (int)(wxGetApp().m_Settings->GetY() * height));
	wxSize size((int)(wxGetApp().m_Settings->GetWidth() * width), (int)(wxGetApp().m_Settings->GetHeight() * height));
	long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMAXIMIZE|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX;

	Init();
	wxFrame::Create(NULL, ID_AUIFRAME, wxT("Toucan"), position, size, style);
	CreateControls();
}

//Destructor
frmMain::~frmMain(){
	delete m_BackupLocations;
	delete m_SecureLocations;
	m_auiManager.UnInit();
}

//frmMain initialisation
void frmMain::Init(){
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
	m_Secure_Pass = NULL;
	m_Secure_Repass = NULL;
	m_Rules_Name = NULL;
	m_Rules_FileExclude = NULL;
	m_Rules_FolderExclude = NULL;
	m_Rules_LocationInclude = NULL;
	m_Rules_FileDelete = NULL;
	m_Script_Rich = NULL;
	
	menuTree = NULL;
	menuRules = NULL;

	m_BackupLocations = new wxArrayString();
	m_SecureLocations = new wxArrayString();
}

void frmMain::CreateControls(){	
	//Set our min size
	this->SetMinSize(wxSize(800, 480));

	//Set the font from the settings
	wxFont font;
	font.SetNativeFontInfo(wxGetApp().m_Settings->GetFont());
	this->SetFont(font);

	//Set the form up as managed by AUI
	m_auiManager.SetManagedWindow(this);

	//Create the root AUI notebook
	m_Notebook = new wxAuiNotebook(this, ID_AUINOTEBOOK, wxDefaultPosition, wxDefaultSize, wxAUI_NB_SCROLL_BUTTONS|wxNO_BORDER);

	//Sync
	wxPanel* SyncPanel = new wxPanel(m_Notebook, ID_PANEL_SYNC, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL);
	wxBoxSizer* SyncSizer = new wxBoxSizer(wxVERTICAL);
	SyncPanel->SetSizer(SyncSizer);

	wxBoxSizer* SyncTopSizer = new wxBoxSizer(wxHORIZONTAL);
	SyncSizer->Add(SyncTopSizer, 0, wxEXPAND|wxALL, 5);

	//Sync - Jobs
	wxBoxSizer* SyncJobsRulesSizer = new wxBoxSizer(wxVERTICAL);
	SyncTopSizer->Add(SyncJobsRulesSizer, 0, wxGROW|wxALL, 0);	

	wxStaticBox* SyncJobs = new wxStaticBox(SyncPanel, wxID_ANY, _("Job Name"));
	wxStaticBoxSizer* SyncJobsSizer = new wxStaticBoxSizer(SyncJobs, wxHORIZONTAL);
	SyncJobsRulesSizer->Add(SyncJobsSizer, 0, wxALIGN_TOP|wxALL, 5);

	wxArrayString m_Sync_Job_SelectStrings;
	m_Sync_Job_Select = new wxComboBox(SyncPanel, ID_SYNC_JOB_SELECT, _T(""), wxDefaultPosition, wxDefaultSize, m_Sync_Job_SelectStrings, wxCB_DROPDOWN|wxCB_READONLY);
	m_Sync_Job_Select->SetMinSize(wxSize(125, -1));
	SyncJobsSizer->Add(m_Sync_Job_Select, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* SyncJobSave = new wxBitmapButton(SyncPanel, ID_SYNC_JOB_SAVE, GetBitmapResource(wxT("save.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	SyncJobsSizer->Add(SyncJobSave, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* SyncJobAdd = new wxBitmapButton(SyncPanel, ID_SYNC_JOB_ADD, GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	SyncJobsSizer->Add(SyncJobAdd, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* SyncJobRemove = new wxBitmapButton(SyncPanel, ID_SYNC_JOB_REMOVE, GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	SyncJobsSizer->Add(SyncJobRemove, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//Sync - Rules
	wxStaticBox* SyncRules = new wxStaticBox(SyncPanel, wxID_ANY, _("Rules"));
	wxStaticBoxSizer* SyncRulesSizer = new wxStaticBoxSizer(SyncRules, wxHORIZONTAL);
	SyncJobsRulesSizer->Add(SyncRulesSizer, 0, wxALIGN_TOP|wxALL|wxGROW, 5);

	wxArrayString m_Sync_RulesStrings;
	m_Sync_Rules = new wxComboBox(SyncPanel, ID_SYNC_RULES, _T(""), wxDefaultPosition, wxDefaultSize, m_Sync_RulesStrings, wxCB_DROPDOWN|wxCB_READONLY);
	SyncRulesSizer->Add(m_Sync_Rules, 1, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5);

	//Sync - Options
	wxArrayString m_Sync_FunctionStrings;
	m_Sync_FunctionStrings.Add(_("Copy"));
	m_Sync_FunctionStrings.Add(_("Update"));
	m_Sync_FunctionStrings.Add(_("Mirror"));
	m_Sync_FunctionStrings.Add(_("Equalise"));
	m_Sync_FunctionStrings.Add(_("Move"));
	m_Sync_FunctionStrings.Add(_("Clean"));
	m_Sync_Function = new wxRadioBox(SyncPanel, ID_SYNC_FUNCTION, _("Function"), wxDefaultPosition, wxDefaultSize, m_Sync_FunctionStrings, 4, wxRA_SPECIFY_ROWS);
	m_Sync_Function->SetSelection(0);
	SyncTopSizer->Add(m_Sync_Function, 0, wxALIGN_TOP|wxALL, 5);

	wxStaticBox* SyncOther = new wxStaticBox(SyncPanel, wxID_ANY, _("Other"));
	wxStaticBoxSizer* SyncOtherSizer = new wxStaticBoxSizer(SyncOther, wxVERTICAL);
	SyncTopSizer->Add(SyncOtherSizer, 0, wxALIGN_TOP|wxALL, 5);

	m_Sync_Timestamp = new wxCheckBox(SyncPanel, ID_SYNC_TIMESTAMP, _("Retain Timestamps"));
	m_Sync_Timestamp->SetValue(false);
	SyncOtherSizer->Add(m_Sync_Timestamp, 0, wxALIGN_LEFT|wxALL, 5);

	m_Sync_Attributes = new wxCheckBox(SyncPanel, ID_SYNC_ATTRIB, _("Retain Attributes"));
	m_Sync_Attributes->SetValue(false);
	SyncOtherSizer->Add(m_Sync_Attributes, 0, wxALIGN_LEFT|wxALL, 5);

	m_Sync_Ignore_Readonly = new wxCheckBox(SyncPanel, ID_SYNC_IGNORERO, _("Ignore Read-Only"));
	m_Sync_Ignore_Readonly->SetValue(false);
	SyncOtherSizer->Add(m_Sync_Ignore_Readonly, 0, wxALIGN_LEFT|wxALL, 5);

	m_Sync_Ignore_DaylightS = new wxCheckBox(SyncPanel, ID_SYNC_IGNOREDS, _("Ignore Daylight Savings"));
	m_Sync_Ignore_DaylightS->SetValue(false);
	SyncOtherSizer->Add(m_Sync_Ignore_DaylightS, 0, wxALIGN_LEFT|wxALL, 5);

	wxBoxSizer* SyncButtonsSizer = new wxBoxSizer(wxVERTICAL);
	SyncTopSizer->Add(SyncButtonsSizer, 1, wxGROW|wxALL|wxALIGN_CENTER_VERTICAL, 5);	

	wxButton* SyncOKButton = new wxButton(SyncPanel, ID_SYNC_OK, _("OK"));
	SyncButtonsSizer->Add(SyncOKButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* SyncPreviewButton = new wxButton(SyncPanel, ID_SYNC_PREVIEW , _("Preview"));
	SyncButtonsSizer->Add(SyncPreviewButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//Sync - Main
    wxGridBagSizer* SyncMainSizer = new wxGridBagSizer(0, 0);
	SyncMainSizer->AddGrowableCol(0);
	SyncMainSizer->AddGrowableCol(2);
	SyncMainSizer->AddGrowableRow(2);
	SyncSizer->Add(SyncMainSizer, 1, wxEXPAND|wxALL, 5);

	wxStaticText* SyncSourceText = new wxStaticText(SyncPanel, wxID_STATIC, _("Source"));
	SyncMainSizer->Add(SyncSourceText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL, 5);

	m_Sync_Source_Txt = new wxTextCtrl(SyncPanel, ID_SYNC_SOURCE_TXT);
	SyncMainSizer->Add(m_Sync_Source_Txt, wxGBPosition(1, 0), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxButton* SyncSourceButton = new wxButton(SyncPanel, ID_SYNC_SOURCE_BTN, wxT("..."), wxDefaultPosition, wxSize(25, -1));
	SyncMainSizer->Add(SyncSourceButton, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL, 5);

	m_Sync_Source_Tree = new wxVirtualDirTreeCtrl(SyncPanel, ID_SYNC_SOURCE_TREE, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_HIDE_ROOT|wxTR_SINGLE|wxBORDER_THEME);
	SyncMainSizer->Add(m_Sync_Source_Tree, wxGBPosition(2, 0), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxBitmapButton* SyncSourceExpand = new wxBitmapButton(SyncPanel, ID_SYNC_SOURCE_EXPAND, GetBitmapResource(wxT("expandall.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	SyncMainSizer->Add(SyncSourceExpand, wxGBPosition(2, 1), wxGBSpan(1, 1), wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	wxStaticText* SyncDestText = new wxStaticText(SyncPanel, wxID_STATIC, _("Destination"));
	SyncMainSizer->Add(SyncDestText, wxGBPosition(0, 2), wxGBSpan(1, 1), wxALL, 5);

	m_Sync_Dest_Txt = new wxTextCtrl(SyncPanel, ID_SYNC_DEST_TXT);
	SyncMainSizer->Add(m_Sync_Dest_Txt, wxGBPosition(1, 2), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxButton* SyncDestButton = new wxButton(SyncPanel, ID_SYNC_DEST_BTN, wxT("..."), wxDefaultPosition, wxSize(25, -1));
	SyncMainSizer->Add(SyncDestButton, wxGBPosition(1, 3), wxGBSpan(1, 1), wxALL, 5);

	m_Sync_Dest_Tree = new wxVirtualDirTreeCtrl(SyncPanel, ID_SYNC_DEST_TREE, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_HIDE_ROOT|wxTR_SINGLE|wxBORDER_THEME);
	SyncMainSizer->Add(m_Sync_Dest_Tree, wxGBPosition(2, 2), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxBitmapButton* SyncDestExpand = new wxBitmapButton(SyncPanel, ID_SYNC_DEST_EXPAND, GetBitmapResource(wxT("expandall.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	SyncMainSizer->Add(SyncDestExpand, wxGBPosition(2, 3), wxGBSpan(1, 1), wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	//Backup
	wxPanel* BackupPanel = new wxPanel(m_Notebook, ID_PANEL_BACKUP, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL);
	wxBoxSizer* BackupSizer = new wxBoxSizer(wxVERTICAL);
	BackupPanel->SetSizer(BackupSizer);

	wxBoxSizer* BackupTopSizer = new wxBoxSizer(wxHORIZONTAL);
	BackupSizer->Add(BackupTopSizer, 0, wxALIGN_LEFT|wxALL, 5);

	//Backup - Jobs
	wxBoxSizer* BackupJobsRulesSizer = new wxBoxSizer(wxVERTICAL);
	BackupTopSizer->Add(BackupJobsRulesSizer, 0, wxALIGN_LEFT|wxALL, 0);

	wxStaticBox* BackupJobs= new wxStaticBox(BackupPanel, wxID_ANY, _("Job Name"));
	wxStaticBoxSizer* BackupJobsSizer = new wxStaticBoxSizer(BackupJobs, wxHORIZONTAL);
	BackupJobsRulesSizer->Add(BackupJobsSizer, 0, wxALIGN_TOP|wxALL, 5);

	wxArrayString m_Backup_Job_SelectStrings;
	m_Backup_Job_Select = new wxComboBox(BackupPanel, ID_BACKUP_JOB_SELECT, _T(""), wxDefaultPosition, wxDefaultSize, m_Backup_Job_SelectStrings, wxCB_DROPDOWN|wxCB_READONLY);
	m_Backup_Job_Select->SetMinSize(wxSize(125, -1));
	BackupJobsSizer->Add(m_Backup_Job_Select, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* BackupJobSave = new wxBitmapButton(BackupPanel, ID_BACKUP_JOB_SAVE, GetBitmapResource(wxT("save.png")));
	BackupJobsSizer->Add(BackupJobSave, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* BackupJobAdd = new wxBitmapButton(BackupPanel, ID_BACKUP_JOB_ADD, GetBitmapResource(wxT("add.png")));
	BackupJobsSizer->Add(BackupJobAdd, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* BackupJobRemove = new wxBitmapButton(BackupPanel, ID_BACKUP_JOB_REMOVE, GetBitmapResource(wxT("remove.png")));
	BackupJobsSizer->Add(BackupJobRemove, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//Backup - Rules
	wxStaticBox* BackupRules = new wxStaticBox(BackupPanel, wxID_ANY, _("Rules"));
	wxStaticBoxSizer* BackupRulesSizer = new wxStaticBoxSizer(BackupRules, wxHORIZONTAL);
	BackupJobsRulesSizer->Add(BackupRulesSizer, 0, wxALL|wxEXPAND, 5);

	wxArrayString m_Backup_RulesStrings;
	m_Backup_Rules = new wxComboBox(BackupPanel, ID_BACKUP_RULES, _T(""), wxDefaultPosition, wxDefaultSize, m_Backup_RulesStrings, wxCB_DROPDOWN|wxCB_READONLY);
	BackupRulesSizer->Add(m_Backup_Rules, 1, wxALL, 5);

	//Backup - Options
	wxArrayString m_Backup_FunctionStrings;
	m_Backup_FunctionStrings.Add(_("Complete"));
	m_Backup_FunctionStrings.Add(_("Update"));
	m_Backup_FunctionStrings.Add(_("Differential"));
	m_Backup_FunctionStrings.Add(_("Restore"));
	m_Backup_Function = new wxRadioBox(BackupPanel, ID_BACKUP_FUNCTION, _("Type"), wxDefaultPosition, wxDefaultSize, m_Backup_FunctionStrings, 1, wxRA_SPECIFY_COLS);
	m_Backup_Function->SetSelection(0);
	BackupTopSizer->Add(m_Backup_Function, 0, wxALIGN_TOP|wxALL, 5);

	wxArrayString m_Backup_FormatStrings;
	m_Backup_FormatStrings.Add(wxT("Zip"));
	m_Backup_FormatStrings.Add(wxT("7-Zip"));
	m_Backup_Format = new wxRadioBox(BackupPanel, ID_BACKUP_FORMAT, _("Format"), wxDefaultPosition, wxDefaultSize, m_Backup_FormatStrings, 1, wxRA_SPECIFY_COLS);
	m_Backup_Format->SetSelection(0);
	BackupTopSizer->Add(m_Backup_Format, 0, wxALIGN_TOP|wxALL, 5);

	wxStaticBox* BackupRatio = new wxStaticBox(BackupPanel, wxID_ANY, _("Compression Level"));
	wxStaticBoxSizer* BackupRatioSizer = new wxStaticBoxSizer(BackupRatio, wxVERTICAL);
	BackupTopSizer->Add(BackupRatioSizer, 0, wxALIGN_TOP|wxALL, 5);

	m_Backup_Ratio_Text = new wxStaticText(BackupPanel, wxID_STATIC, _("Default"));
	BackupRatioSizer->Add(m_Backup_Ratio_Text);

	m_Backup_Ratio = new wxSlider(BackupPanel, ID_BACKUP_RATIO, 3, 0, 5);
	BackupRatioSizer->Add(m_Backup_Ratio);

	wxStaticBox* BackupOther = new wxStaticBox(BackupPanel, wxID_ANY, _("Other"));
	wxStaticBoxSizer* BackupOtherSizer = new wxStaticBoxSizer(BackupOther, wxVERTICAL);
	BackupTopSizer->Add(BackupOtherSizer, 0, wxALIGN_TOP|wxALL, 5);

	m_Backup_IsPass = new wxCheckBox(BackupPanel, ID_BACKUP_ISPASS, _("Password"));
	BackupOtherSizer->Add(m_Backup_IsPass, 0, wxALIGN_TOP|wxALL, 5);

	wxBoxSizer* BackupButtonsSizer = new wxBoxSizer(wxVERTICAL);
	BackupTopSizer->Add(BackupButtonsSizer, 1, wxGROW|wxALL|wxALIGN_CENTER_VERTICAL, 5);	

	wxButton* BackupOKButton = new wxButton(BackupPanel, ID_BACKUP_OK, _("OK"));
	BackupButtonsSizer->Add(BackupOKButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* BackupPreviewButton = new wxButton(BackupPanel, ID_BACKUP_PREVIEW , _("Preview"));
	BackupButtonsSizer->Add(BackupPreviewButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);	

	//Backup - Main
    wxGridBagSizer* BackupMainSizer = new wxGridBagSizer(0, 0);
	BackupMainSizer->AddGrowableCol(0);
	BackupMainSizer->AddGrowableCol(2);
	BackupMainSizer->AddGrowableRow(3);
	BackupSizer->Add(BackupMainSizer, 1, wxEXPAND|wxALL, 5);

	wxStaticText* BackupComputerStatic = new wxStaticText(BackupPanel, wxID_ANY, _("Computer"));
	BackupMainSizer->Add(BackupComputerStatic, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL, 5);

	m_Backup_DirCtrl = new ExtendedDirCtrl(BackupPanel, ID_BACKUP_DIRCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
	m_Backup_DirCtrl->ShowHidden(true);
	BackupMainSizer->Add(m_Backup_DirCtrl, wxGBPosition(1, 0), wxGBSpan(3, 1), wxEXPAND|wxALL, 5);

	wxBoxSizer* BackupAddRemoveSizer = new wxBoxSizer(wxVERTICAL);
	BackupMainSizer->Add(BackupAddRemoveSizer, wxGBPosition(1, 1), wxGBSpan(3, 1), wxALIGN_CENTRE_VERTICAL|wxALL, 0);

	wxBitmapButton*BackupAdd = new wxBitmapButton(BackupPanel, ID_BACKUP_ADD, GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	BackupAddRemoveSizer->Add(BackupAdd, 0, wxALL, 5);

	wxBitmapButton* BackupRemove = new wxBitmapButton(BackupPanel, ID_BACKUP_REMOVE, GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	BackupAddRemoveSizer->Add(BackupRemove, 0, wxALL, 5);

	wxStaticText* BackupLocationStatic = new wxStaticText(BackupPanel, wxID_ANY, _("Backup Location"));
	BackupMainSizer->Add(BackupLocationStatic, wxGBPosition(0, 2), wxGBSpan(1, 1), wxALL, 5);

	m_Backup_Location = new wxTextCtrl(BackupPanel, ID_BACKUP_LOCATION_TEXT);
	BackupMainSizer->Add(m_Backup_Location, wxGBPosition(1, 2), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxButton* BackupLocationButton = new wxButton(BackupPanel, ID_BACKUP_LOCATION, wxT("..."), wxDefaultPosition, wxSize(25, -1), 0);
	BackupMainSizer->Add(BackupLocationButton, wxGBPosition(1, 3), wxGBSpan(1, 1), wxALL, 5);

	wxStaticText* BackupFilesStatic = new wxStaticText(BackupPanel, wxID_ANY, _("Files to Backup"));
	BackupMainSizer->Add(BackupFilesStatic, wxGBPosition(2, 2), wxGBSpan(1, 1), wxALL, 5);

	m_Backup_TreeCtrl = new wxVirtualDirTreeCtrl(BackupPanel, ID_BACKUP_TREECTRL, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_HIDE_ROOT|wxTR_SINGLE|wxBORDER_THEME);
	BackupMainSizer->Add(m_Backup_TreeCtrl, wxGBPosition(3, 2), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxBoxSizer* BackupAddExpandSizer = new wxBoxSizer(wxVERTICAL);
	BackupMainSizer->Add(BackupAddExpandSizer, wxGBPosition(3, 3), wxGBSpan(1, 1), wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	wxBitmapButton* BackupAddVar = new wxBitmapButton(BackupPanel, ID_BACKUP_ADDVAR, GetBitmapResource(wxT("addvar.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	BackupAddExpandSizer->Add(BackupAddVar, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

	wxBitmapButton* BackupExpand = new wxBitmapButton(BackupPanel, ID_BACKUP_EXPAND, GetBitmapResource(wxT("expandall.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	BackupAddExpandSizer->Add(BackupExpand, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 10);

	//Secure
	wxPanel* SecurePanel = new wxPanel(m_Notebook, ID_PANEL_SECURE, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL);
	wxBoxSizer* SecureSizer = new wxBoxSizer(wxVERTICAL);
	SecurePanel->SetSizer(SecureSizer);

	wxBoxSizer* SecureTopSizer = new wxBoxSizer(wxHORIZONTAL);
	SecureSizer->Add(SecureTopSizer, 0, wxALIGN_LEFT|wxALL, 5);

	//Secure - Jobs
	wxBoxSizer* SecureJobsRulesSizer = new wxBoxSizer(wxVERTICAL);
	SecureTopSizer->Add(SecureJobsRulesSizer, 0, wxGROW|wxALL, 0);	

	wxStaticBox* SecureJobs = new wxStaticBox(SecurePanel, wxID_ANY, _("Job Name"));
	wxStaticBoxSizer* SecureJobsSizer = new wxStaticBoxSizer(SecureJobs, wxHORIZONTAL);
	SecureJobsRulesSizer->Add(SecureJobsSizer, 0, wxALIGN_TOP|wxALL, 5);

	wxArrayString m_Secure_Job_SelectStrings;
	m_Secure_Job_Select = new wxComboBox(SecurePanel, ID_SECURE_JOB_SELECT, _T(""), wxDefaultPosition, wxDefaultSize, m_Secure_Job_SelectStrings, wxCB_DROPDOWN|wxCB_READONLY);
	m_Secure_Job_Select->SetMinSize(wxSize(125, -1));	
	SecureJobsSizer->Add(m_Secure_Job_Select, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* SecureJobSave = new wxBitmapButton(SecurePanel, ID_SECURE_JOB_SAVE, GetBitmapResource(wxT("save.png")));
	SecureJobsSizer->Add(SecureJobSave, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* SecureJobAdd = new wxBitmapButton(SecurePanel, ID_SECURE_JOB_ADD, GetBitmapResource(wxT("add.png")));
	SecureJobsSizer->Add(SecureJobAdd, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* SecureJobRemove = new wxBitmapButton(SecurePanel, ID_SECURE_JOB_REMOVE, GetBitmapResource(wxT("remove.png")));
	SecureJobsSizer->Add(SecureJobRemove, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//Secure - Rules
	wxStaticBox* SecureRules = new wxStaticBox(SecurePanel, wxID_ANY, _("Rules"));
	wxStaticBoxSizer* SecureRulesSizer = new wxStaticBoxSizer(SecureRules, wxHORIZONTAL);
	SecureJobsRulesSizer->Add(SecureRulesSizer, 1, wxALIGN_TOP|wxALL|wxEXPAND, 5);

	wxArrayString m_Secure_RulesStrings;
	m_Secure_Rules = new wxComboBox(SecurePanel, ID_SECURE_RULES, _T(""), wxDefaultPosition, wxDefaultSize, m_Secure_RulesStrings, wxCB_DROPDOWN|wxCB_READONLY);
	SecureRulesSizer->Add(m_Secure_Rules, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//Secure - Options
	wxArrayString m_Secure_FunctionStrings;
	m_Secure_FunctionStrings.Add(_("Encrypt"));
	m_Secure_FunctionStrings.Add(_("Decrypt"));
	m_Secure_Function = new wxRadioBox(SecurePanel, ID_SECURE_FUNCTION, _("Function"), wxDefaultPosition, wxDefaultSize, m_Secure_FunctionStrings, 1, wxRA_SPECIFY_COLS);
	m_Secure_Function->SetSelection(0);
	SecureTopSizer->Add(m_Secure_Function, 0, wxALIGN_TOP|wxALL, 5);

	wxBoxSizer* SecureButtonsSizer = new wxBoxSizer(wxVERTICAL);
	SecureTopSizer->Add(SecureButtonsSizer, 1, wxGROW|wxALL|wxALIGN_CENTER_VERTICAL, 5);	

	wxButton* SecureOKButton = new wxButton(SecurePanel, ID_SECURE_OK, _("OK"));
	SecureButtonsSizer->Add(SecureOKButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* SecurePreviewButton = new wxButton(SecurePanel, ID_SECURE_PREVIEW , _("Preview"));
	SecureButtonsSizer->Add(SecurePreviewButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);	

	//Secure - Main
	wxGridBagSizer* SecureMainSizer = new wxGridBagSizer(0, 0);
	SecureMainSizer->AddGrowableCol(0);
	SecureMainSizer->AddGrowableCol(2);
	SecureMainSizer->AddGrowableRow(1);
	SecureSizer->Add(SecureMainSizer, 1, wxEXPAND|wxALL, 5);
	
	wxStaticText* SecureComputerStatic = new wxStaticText(SecurePanel, wxID_ANY, _("Computer"));
	SecureMainSizer->Add(SecureComputerStatic, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL, 5);

	m_Secure_DirCtrl = new ExtendedDirCtrl(SecurePanel, ID_SECURE_DIRCTRL, _T(""), wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
	m_Secure_DirCtrl->ShowHidden(true);	
	SecureMainSizer->Add(m_Secure_DirCtrl, wxGBPosition(1, 0), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxBoxSizer* SecureAddRemoveSizer = new wxBoxSizer(wxVERTICAL);
	SecureMainSizer->Add(SecureAddRemoveSizer, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALIGN_CENTRE_VERTICAL|wxALL, 0);

	wxBitmapButton* SecureAdd = new wxBitmapButton(SecurePanel, ID_SECURE_ADD, GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	SecureAddRemoveSizer->Add(SecureAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* SecureRemove = new wxBitmapButton(SecurePanel, ID_SECURE_REMOVE, GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	SecureAddRemoveSizer->Add(SecureRemove, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
	
	wxStaticText* SecureFilesStatic = new wxStaticText(SecurePanel, wxID_ANY, _("Files to Secure"));
	SecureMainSizer->Add(SecureFilesStatic, wxGBPosition(0, 2), wxGBSpan(1, 1), wxALL, 5);

	m_Secure_TreeCtrl = new wxVirtualDirTreeCtrl(SecurePanel, ID_SECURE_TREECTRL, wxDefaultPosition, wxDefaultSize, wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_HIDE_ROOT|wxTR_SINGLE|wxBORDER_THEME);
	SecureMainSizer->Add(m_Secure_TreeCtrl, wxGBPosition(1, 2), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxBoxSizer* SecureAddExpandSizer = new wxBoxSizer(wxVERTICAL);
	SecureMainSizer->Add(SecureAddExpandSizer, wxGBPosition(1, 3), wxGBSpan(1, 1), wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	wxBitmapButton* SecureAddVar = new wxBitmapButton(SecurePanel, ID_SECURE_ADDVAR, GetBitmapResource(wxT("addvar.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	SecureAddExpandSizer->Add(SecureAddVar, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0);

	wxBitmapButton* SecureExpand = new wxBitmapButton(SecurePanel, ID_SECURE_EXPAND, GetBitmapResource(wxT("expandall.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	SecureAddExpandSizer->Add(SecureExpand, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 10);

	//Rules
	wxPanel* RulesPanel = new wxPanel(m_Notebook, ID_PANEL_RULES, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL);
	wxBoxSizer* RulesSizer = new wxBoxSizer(wxVERTICAL);
	RulesPanel->SetSizer(RulesSizer);

	//Rules - Name
	wxStaticBox* RulesName = new wxStaticBox(RulesPanel, wxID_ANY, _("Name"));
	wxStaticBoxSizer* RulesNameSizer = new wxStaticBoxSizer(RulesName, wxHORIZONTAL);
	RulesSizer->Add(RulesNameSizer, 0, wxALIGN_TOP|wxTOP|wxLEFT, 10);

	wxArrayString m_Rules_ComboStrings;
	m_Rules_Name = new wxComboBox(RulesPanel, ID_RULES_COMBO, _T(""), wxDefaultPosition, wxDefaultSize, m_Rules_ComboStrings, wxCB_READONLY);
	m_Rules_Name->SetMinSize(wxSize(125, -1));	
	RulesNameSizer->Add(m_Rules_Name, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* RulesNameSave = new wxBitmapButton(RulesPanel, ID_RULES_SAVE, GetBitmapResource(wxT("save.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	RulesNameSizer->Add(RulesNameSave, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* RulesNameAdd = new wxBitmapButton(RulesPanel, ID_RULES_ADD, GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	RulesNameSizer->Add(RulesNameAdd, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* RulesNameRemove = new wxBitmapButton(RulesPanel, ID_RULES_REMOVE, GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	RulesNameSizer->Add(RulesNameRemove, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	//Rules - Main
	wxGridBagSizer* RulesMainSizer = new wxGridBagSizer(0, 0);
	RulesMainSizer->AddGrowableRow(1);
	RulesMainSizer->AddGrowableRow(3);
	RulesMainSizer->AddGrowableRow(5);
	RulesMainSizer->AddGrowableCol(0);
	RulesSizer->Add(RulesMainSizer, 1, wxEXPAND|wxALL, 5);

	wxStaticText* RulesFilesExStatic = new wxStaticText(RulesPanel, wxID_STATIC, _("Files to exclude (file name, path or extension)"), wxDefaultPosition, wxDefaultSize, 0);
	RulesMainSizer->Add(RulesFilesExStatic, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL, 5);

	wxArrayString m_Rules_FileExcludeStrings;
	m_Rules_FileExclude = new wxListBox(RulesPanel, ID_RULE_FILE_EXCLUDE, wxDefaultPosition, wxDefaultSize, m_Rules_FileExcludeStrings, wxLB_SINGLE|wxBORDER_THEME);
	RulesMainSizer->Add(m_Rules_FileExclude, wxGBPosition(1, 0), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxBoxSizer* RulesFileExButtonSizer = new wxBoxSizer(wxVERTICAL);
	RulesMainSizer->Add(RulesFileExButtonSizer, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	wxBitmapButton* RulesFileExAdd = new wxBitmapButton(RulesPanel, ID_RULES_ADD_FILEEXCLUDE, GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	RulesFileExButtonSizer->Add(RulesFileExAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* RulesFileExRem = new wxBitmapButton(RulesPanel, ID_RULES_REMOVE_FILEEXCLUDE, GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	RulesFileExButtonSizer->Add(RulesFileExRem, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* RulesFolderExStatic = new wxStaticText(RulesPanel, wxID_STATIC, _("Folders to exclude (folder name or path)"), wxDefaultPosition, wxDefaultSize, 0);
	RulesMainSizer->Add(RulesFolderExStatic, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALL, 5);

	wxArrayString m_Rules_FolderExcludeStrings;
	m_Rules_FolderExclude = new wxListBox(RulesPanel, ID_RULES_FOLDER_EXCLUDE, wxDefaultPosition, wxDefaultSize, m_Rules_FolderExcludeStrings, wxLB_SINGLE|wxBORDER_THEME);
	RulesMainSizer->Add(m_Rules_FolderExclude, wxGBPosition(3, 0), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxBoxSizer* RulesFolderExButtonSizer = new wxBoxSizer(wxVERTICAL);
	RulesMainSizer->Add(RulesFolderExButtonSizer, wxGBPosition(3, 1), wxGBSpan(1, 1), wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	wxBitmapButton* RulesFolderExAdd = new wxBitmapButton(RulesPanel, ID_RULES_ADD_FOLDEREXCLUDE, GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	RulesFolderExButtonSizer->Add(RulesFolderExAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* RulesFolderExRem = new wxBitmapButton(RulesPanel, ID_RULES_REMOVE_FOLDEREXCLUDE, GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	RulesFolderExButtonSizer->Add(RulesFolderExRem, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxStaticText* RulesIncludeStatic = new wxStaticText(RulesPanel, wxID_STATIC, _("Locations to always include (file/folder name, path or  file extension)"), wxDefaultPosition, wxDefaultSize, 0);
	RulesMainSizer->Add(RulesIncludeStatic, wxGBPosition(4, 0), wxGBSpan(1, 1), wxALL, 5);

	wxArrayString m_Rules_LocationIncludeStrings;
	m_Rules_LocationInclude = new wxListBox(RulesPanel, ID_RULES_LOCATION_INCLUDE, wxDefaultPosition, wxDefaultSize, m_Rules_LocationIncludeStrings, wxLB_SINGLE|wxBORDER_THEME);
	RulesMainSizer->Add(m_Rules_LocationInclude, wxGBPosition(5, 0), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxBoxSizer* RulesIncludeButtonSizer = new wxBoxSizer(wxVERTICAL);
	RulesMainSizer->Add(RulesIncludeButtonSizer, wxGBPosition(5, 1), wxGBSpan(1, 1), wxALIGN_CENTRE_VERTICAL|wxALL, 5);

	wxBitmapButton* RulesIncludeAdd = new wxBitmapButton(RulesPanel, ID_RULES_ADD_LOCATIONINCLUDE, GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	RulesIncludeButtonSizer->Add(RulesIncludeAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	wxBitmapButton* RulesIncludeRem= new wxBitmapButton(RulesPanel, ID_RULES_REMOVE_LOCATIONINCLUDE, GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	RulesIncludeButtonSizer->Add(RulesIncludeRem, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	//Variables
	wxPanel* VariablesPanel = new wxPanel(m_Notebook, ID_PANEL_VARIABLES, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL);

	wxBoxSizer* VariablesSizer = new wxBoxSizer(wxVERTICAL);
    VariablesPanel->SetSizer(VariablesSizer);

    wxBoxSizer* VariablesTop = new wxBoxSizer(wxHORIZONTAL);
    VariablesSizer->Add(VariablesTop, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* VariablesStatic = new wxStaticText(VariablesPanel, wxID_STATIC, _("Name"));
    VariablesTop->Add(VariablesStatic, 0, wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 10);

    wxArrayString arrVariables;
    m_Variables_Name = new wxComboBox(VariablesPanel, ID_VARIABLES_NAME, _T(""), wxDefaultPosition, wxDefaultSize, arrVariables, wxCB_DROPDOWN|wxCB_READONLY);
	m_Variables_Name->SetMinSize(wxSize(125, -1));
	VariablesTop->Add(m_Variables_Name, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
    wxBitmapButton* VariablesAdd = new wxBitmapButton(VariablesPanel, ID_VARIABLES_ADD, GetBitmapResource(wxT("add.png")));
	VariablesTop->Add(VariablesAdd, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBitmapButton* VariablesRemove = new wxBitmapButton(VariablesPanel, ID_VARIABLES_REMOVE, GetBitmapResource(wxT("remove.png")));
    VariablesTop->Add(VariablesRemove, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* VariablesMain = new wxBoxSizer(wxHORIZONTAL);
    VariablesSizer->Add(VariablesMain, 1, wxGROW|wxALL, 5);

    m_Variables_List = new wxListCtrl(VariablesPanel, ID_VARIABLES_LIST, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT|wxBORDER_THEME);
    VariablesMain->Add(m_Variables_List, 1, wxGROW|wxALL, 5);

    wxBoxSizer* VariablesRight = new wxBoxSizer(wxVERTICAL);
    VariablesMain->Add(VariablesRight, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* VariablesAddItem = new wxBitmapButton(VariablesPanel, ID_VARIABLES_ADDITEM, GetBitmapResource(wxT("add.png")));
    VariablesRight->Add(VariablesAddItem, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBitmapButton* VariablesRemoveItem = new wxBitmapButton(VariablesPanel, ID_VARIABLES_REMOVEITEM, GetBitmapResource(wxT("remove.png")));
    VariablesRight->Add(VariablesRemoveItem, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	//Scripting
	wxPanel* itemPanel131 = new wxPanel( m_Notebook, ID_PANEL_SCRIPT, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL);
	wxBoxSizer* itemBoxSizer132 = new wxBoxSizer(wxVERTICAL);
	itemPanel131->SetSizer(itemBoxSizer132);
	
	wxBoxSizer* itemBoxSizer140 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer132->Add(itemBoxSizer140, 0, wxALIGN_LEFT|wxALL, 5);

	wxStaticBox* ScriptStaticBox = new wxStaticBox(itemPanel131, wxID_ANY, _("Name"));
	wxStaticBoxSizer* ScriptStaticBoxSizer = new wxStaticBoxSizer(ScriptStaticBox, wxHORIZONTAL);
	itemBoxSizer140->Add(ScriptStaticBoxSizer, 0, wxALIGN_TOP|wxALL, 5);

	wxArrayString itemComboBox134Strings;
	m_Script_Name = new wxComboBox( itemPanel131, ID_SCRIPT_NAME, _T(""), wxDefaultPosition, wxDefaultSize, itemComboBox134Strings, wxCB_DROPDOWN|wxCB_READONLY);
	m_Script_Name->SetMinSize(wxSize(125, -1));
	ScriptStaticBoxSizer->Add(m_Script_Name, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	wxBitmapButton* itemBitmapButton135 = new wxBitmapButton( itemPanel131, ID_SCRIPT_SAVE, GetBitmapResource(wxT("save.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	ScriptStaticBoxSizer->Add(itemBitmapButton135, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton136 = new wxBitmapButton( itemPanel131, ID_SCRIPT_ADD, GetBitmapResource(wxT("add.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	ScriptStaticBoxSizer->Add(itemBitmapButton136, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* itemBitmapButton137 = new wxBitmapButton( itemPanel131, ID_SCRIPT_REMOVE, GetBitmapResource(wxT("remove.png")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	ScriptStaticBoxSizer->Add(itemBitmapButton137, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* itemButton142 = new wxButton( itemPanel131, ID_SCRIPT_EXECUTE, _("Execute"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer140->Add(itemButton142, 0, wxALIGN_TOP|wxALL, 10);

	wxBoxSizer* itemBoxSizer138 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer132->Add(itemBoxSizer138, 1, wxGROW|wxALL, 5);
	m_Script_Rich = new wxTextCtrl( itemPanel131, ID_SCRIPT_RICH, _T(""), wxDefaultPosition, wxSize(100, 100), wxTE_MULTILINE|wxBORDER_THEME);
	itemBoxSizer138->Add(m_Script_Rich, 1, wxGROW|wxALL, 5);

	//Settings
	wxPanel* SettingsPanel = new wxPanel(m_Notebook, ID_PANEL_SETTINGS, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL);

    wxGridBagSizer* SettingsSizer = new wxGridBagSizer(0, 0);
	SettingsPanel->SetSizer(SettingsSizer);

	wxStaticBox* FieldsStaticBox = new wxStaticBox(SettingsPanel, wxID_ANY, _("Remember Entered Information"));
	wxStaticBoxSizer* FieldsStaticBoxSizer = new wxStaticBoxSizer(FieldsStaticBox, wxVERTICAL);
	int x, y;
	FieldsStaticBox->GetTextExtent(_("Remember Entered Information"), &x, &y);
	FieldsStaticBoxSizer->SetMinSize(wxSize(x + 20, -1));
	SettingsSizer->Add(FieldsStaticBoxSizer, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

	m_Settings_RememberSync = new wxCheckBox(SettingsPanel, ID_SETTINGS_REMEMBERSYNC, _("Sync"));
	FieldsStaticBoxSizer->Add(m_Settings_RememberSync, 0, wxALIGN_TOP|wxALL, 5);

	m_Settings_RememberBackup = new wxCheckBox(SettingsPanel, ID_SETTINGS_REMEMBERBACKUP, _("Backup"));
	FieldsStaticBoxSizer->Add(m_Settings_RememberBackup, 0, wxALIGN_TOP|wxALL, 5);

	m_Settings_RememberSecure = new wxCheckBox(SettingsPanel, ID_SETTINGS_REMEMBERSECURE, _("Secure"));
	FieldsStaticBoxSizer->Add(m_Settings_RememberSecure, 0, wxALIGN_TOP|wxALL, 5);

	wxStaticBox* LanguageStaticBox = new wxStaticBox(SettingsPanel, wxID_ANY, _("Language"));
	wxStaticBoxSizer* LanguageStaticBoxSizer = new wxStaticBoxSizer(LanguageStaticBox, wxHORIZONTAL);
	SettingsSizer->Add(LanguageStaticBoxSizer, wxGBPosition(1, 0), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);

	wxArrayString m_Settings_LanguageStrings = GetLanguages();
	m_Settings_Language = new wxComboBox(SettingsPanel, ID_SETTINGS_LANGUAGE, _T(""), wxDefaultPosition, wxDefaultSize, m_Settings_LanguageStrings, wxCB_DROPDOWN|wxCB_READONLY);
	m_Settings_Language->SetMinSize(wxSize(125, -1));
	m_Settings_Language->SetStringSelection(wxLocale::FindLanguageInfo(wxGetApp().m_Settings->GetLanguageCode())->Description);
	LanguageStaticBoxSizer->Add(m_Settings_Language, 1, wxALL|wxEXPAND, 5);

	wxArrayString arrTabStyles;
	arrTabStyles.Add(_("Icons and Text"));
	arrTabStyles.Add(_("Text"));
	m_Settings_TabStyle = new wxRadioBox(SettingsPanel, ID_SETTINGS_TABSTYLE, _("Tab style"), wxDefaultPosition, wxDefaultSize, arrTabStyles, 2, wxRA_SPECIFY_ROWS);
	m_Settings_TabStyle->SetStringSelection(wxGetApp().m_Settings->GetTabStyle());
	SettingsSizer->Add(m_Settings_TabStyle, wxGBPosition(2, 0), wxGBSpan(1, 1), wxEXPAND|wxALL, 5);
	
	wxButton* ApplySettings = new wxButton(SettingsPanel, wxID_APPLY, _("Apply"));
	SettingsSizer->Add(ApplySettings, wxGBPosition(3, 0), wxGBSpan(1, 1), wxALL, 5);

	wxStaticBox* FontStaticBox = new wxStaticBox(SettingsPanel, wxID_ANY, _("Font"));
	wxStaticBoxSizer* FontStaticBoxSizer = new wxStaticBoxSizer(FontStaticBox, wxHORIZONTAL);
	SettingsSizer->Add(FontStaticBoxSizer, wxGBPosition(0, 1), wxGBSpan(1, 1), wxALL, 5);

	m_Settings_Font = new wxFontPickerCtrl(SettingsPanel, ID_SETTINGS_FONT, wxNullFont, wxDefaultPosition, wxDefaultSize, 0);
	m_Settings_Font->SetSelectedFont(font);
	FontStaticBoxSizer->Add(m_Settings_Font, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStaticBox* OtherBox = new wxStaticBox(SettingsPanel, wxID_ANY, _("Other"));
	wxStaticBoxSizer* OtherStaticBoxSizer = new wxStaticBoxSizer(OtherBox, wxHORIZONTAL);
	SettingsSizer->Add(OtherStaticBoxSizer, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALL, 5);
	
	m_Settings_EnableTooltips = new wxCheckBox(SettingsPanel, ID_SETTINGS_ENABLETOOLTIPS, _("Enable Tooltips"));
	m_Settings_EnableTooltips->SetValue(true);
	OtherStaticBoxSizer->Add(m_Settings_EnableTooltips, 0, wxALIGN_TOP|wxALL, 5);

	//Help
	wxPanel* HelpPanel = new wxPanel(m_Notebook, ID_PANEL_HELP, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxTAB_TRAVERSAL);
	
	wxBoxSizer* HelpSizer = new wxBoxSizer(wxVERTICAL);
	HelpPanel->SetSizer(HelpSizer);
	
	wxButton* AboutButton = new wxButton(HelpPanel, wxID_ABOUT, _("About"));
	HelpSizer->Add(AboutButton, 0, wxALIGN_TOP|wxALL, 5);

	m_HelpWindow = new wxHtmlHelpWindow;
    wxGetApp().m_Help->SetHelpWindow(m_HelpWindow); 
    wxGetApp().m_Help->AddBook(wxPathOnly(wxStandardPaths::Get().GetExecutablePath()) + wxFILE_SEP_PATH + wxT("toucan.htb"));
    m_HelpWindow->Create(HelpPanel, ID_HELP, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxNO_BORDER, wxHF_CONTENTS|wxHF_INDEX|wxHF_SEARCH);
	m_HelpWindow->DisplayContents();
	HelpSizer->Add(m_HelpWindow, 1, wxALIGN_TOP|wxTOP|wxEXPAND, 5);

	//Add the panels
	wxBitmap syncbitmap, backupbitmap, securebitmap, settingsbitmap, scriptbitmap, rulesbitmap, pvarsbitmap, helpbitmap;
	
	if(wxGetApp().m_Settings->GetTabStyle() == _("Icons and Text")){
		syncbitmap = GetBitmapResource(wxT("sync.png"));
		backupbitmap = GetBitmapResource(wxT("backup.png"));
		securebitmap = GetBitmapResource(wxT("secure.png"));
		settingsbitmap = GetBitmapResource(wxT("settings.png"));
		scriptbitmap = GetBitmapResource(wxT("script.png"));
		rulesbitmap = GetBitmapResource(wxT("rules.png"));
		pvarsbitmap = GetBitmapResource(wxT("pvars.png"));
		helpbitmap = GetBitmapResource(wxT("help.png"));
	}

	m_Notebook->AddPage(SyncPanel, _("Sync"), false, syncbitmap);
	m_Notebook->AddPage(BackupPanel, _("Backup"), false, backupbitmap);
	m_Notebook->AddPage(SecurePanel, _("Secure"), false, securebitmap);
	m_Notebook->AddPage(RulesPanel, _("Rules"), false, rulesbitmap);
	m_Notebook->AddPage(VariablesPanel, _("Variables"), false, pvarsbitmap);
	m_Notebook->AddPage(itemPanel131, _("Script"), false, scriptbitmap);
	m_Notebook->AddPage(SettingsPanel, _("Settings"), false, settingsbitmap);
	m_Notebook->AddPage(HelpPanel, _("Help"), false, helpbitmap);

	this->m_auiManager.AddPane(m_Notebook, wxAuiPaneInfo()
	                                    .Name(_T("Pane3")).Centre().CaptionVisible(false).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false).PaneBorder(false));

	m_auiManager.Update();

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
	
	m_Settings_RememberSync->SetValue(wxGetApp().m_Settings->GetRememberSync());
	m_Settings_RememberBackup->SetValue(wxGetApp().m_Settings->GetRememberBackup());
	m_Settings_RememberSecure->SetValue(wxGetApp().m_Settings->GetRememberSecure());
	m_Settings_EnableTooltips->SetValue(wxGetApp().m_Settings->GetEnableTooltips());

	//Set the drag and drop targets
	m_Sync_Source_Txt->SetDropTarget(new DnDFileTreeText(m_Sync_Source_Txt, m_Sync_Source_Tree));
	m_Sync_Dest_Txt->SetDropTarget(new DnDFileTreeText(m_Sync_Dest_Txt, m_Sync_Dest_Tree));
	
	m_Sync_Source_Tree->SetDropTarget(new DnDFileTreeText(m_Sync_Source_Txt, m_Sync_Source_Tree));
	m_Sync_Dest_Tree->SetDropTarget(new DnDFileTreeText(m_Sync_Dest_Txt, m_Sync_Dest_Tree));
	
	m_Backup_TreeCtrl->SetDropTarget(new DnDFileTree(m_Backup_TreeCtrl));
	m_Secure_TreeCtrl->SetDropTarget(new DnDFileTree(m_Secure_TreeCtrl));

	//Set up the rules boxes
	SetRulesBox(m_Sync_Rules);
	SetRulesBox(m_Backup_Rules);
	SetRulesBox(m_Secure_Rules);
	SetRulesBox(m_Rules_Name);

	//Set up the jobs boxes
	SetJobsBox(m_Sync_Job_Select, wxT("Sync"));
	SetJobsBox(m_Backup_Job_Select, wxT("Backup"));
	SetJobsBox(m_Secure_Job_Select, wxT("Secure"));
	
	//Set the variables box
	SetVariablesBox(m_Variables_Name);
	
	//Set the scripts box
	SetScriptsBox(m_Script_Name);
	
	wxListItem column;
	m_Variables_List->InsertColumn(0, column);
	m_Variables_List->InsertColumn(1, column);
	
	//Add some blank items to the combo box to allow deselection
	m_Sync_Rules->Append(wxEmptyString);
	m_Backup_Rules->Append(wxEmptyString);
	m_Secure_Rules->Append(wxEmptyString);
	
	m_Sync_Dest_Tree->SetSync(true);
	m_Sync_Source_Tree->SetSync(true);
	
	//Set the tooltips if required
	if(wxGetApp().m_Settings->GetEnableTooltips()){
		//Sync
		SyncJobSave->SetToolTip(_("Save"));
		SyncJobAdd->SetToolTip(_("Add"));
		SyncJobRemove->SetToolTip(_("Remove"));
		SyncSourceExpand->SetToolTip(_("Expand All"));
		SyncDestExpand->SetToolTip(_("Expand All"));
		//Backup
		BackupJobSave->SetToolTip(_("Save"));
		BackupJobAdd->SetToolTip(_("Add"));
		BackupJobRemove->SetToolTip(_("Remove"));
		BackupAdd->SetToolTip(_("Add"));
		BackupRemove->SetToolTip(_("Remove"));
		BackupAddVar->SetToolTip(_("Insert Variable"));
		BackupExpand->SetToolTip(_("Expand All"));
		//Secure
		SecureJobSave->SetToolTip(_("Save"));
		SecureJobAdd->SetToolTip(_("Add"));
		SecureJobRemove->SetToolTip(_("Remove"));
		SecureAdd->SetToolTip(_("Add"));
		SecureRemove->SetToolTip(_("Remove"));
		SecureAddVar->SetToolTip(_("Insert Variable"));
		SecureExpand->SetToolTip(_("Expand All"));
		//Rules
		RulesNameSave->SetToolTip(_("Save"));
		RulesNameAdd->SetToolTip(_("Add"));
		RulesNameRemove->SetToolTip(_("Remove"));
		RulesFileExAdd->SetToolTip(_("Add"));
		RulesFileExRem->SetToolTip(_("Remove"));
		RulesFolderExAdd->SetToolTip(_("Add"));
		RulesFolderExRem->SetToolTip(_("Remove"));
		RulesIncludeAdd->SetToolTip(_("Add"));
		RulesIncludeRem->SetToolTip(_("Remove"));
		//Variables
		VariablesAdd->SetToolTip(_("Add"));
		VariablesRemove->SetToolTip(_("Remove"));
		VariablesAddItem->SetToolTip(_("Add"));
		VariablesRemoveItem->SetToolTip(_("Remove"));
		//Scripting
		itemBitmapButton135->SetToolTip(_("Save"));
		itemBitmapButton136->SetToolTip(_("Add"));
		itemBitmapButton137->SetToolTip(_("Remove"));
	}

	this->SetIcon(wxIcon(wxPathOnly(wxStandardPaths::Get().GetExecutablePath()) + wxFILE_SEP_PATH + wxT("Toucan.ico"), wxBITMAP_TYPE_ICO));	

	if(wxGetApp().m_Settings->GetWidth() < 1 && wxGetApp().m_Settings->GetHeight() < 1){
		Iconize(false);
	}

	if(wxGetApp().m_Jobs_Config->Exists(wxT("SyncRemember")) && wxGetApp().m_Settings->GetRememberSync()){
		SyncData data;
		data.SetName(wxT("SyncRemember"));
		data.TransferFromFile();
		data.TransferToForm(this);
		m_Sync_Job_Select->SetStringSelection(wxGetApp().m_Jobs_Config->Read(wxT("SyncRemember/Name")));
	}
	if(wxGetApp().m_Jobs_Config->Exists(wxT("BackupRemember")) && wxGetApp().m_Settings->GetRememberBackup()){
		BackupData data;
		data.SetName(wxT("BackupRemember"));
		data.TransferFromFile();		
		data.TransferToForm(this);
		m_Backup_Job_Select->SetStringSelection(wxGetApp().m_Jobs_Config->Read(wxT("BackupRemember/Name")));
	}
	if(wxGetApp().m_Jobs_Config->Exists(wxT("SecureRemember")) && wxGetApp().m_Settings->GetRememberSecure()){
		SecureData data;
		data.SetName(wxT("SecureRemember"));
		data.TransferFromFile();
		data.TransferToForm(this);
		m_Secure_Job_Select->SetStringSelection(wxGetApp().m_Jobs_Config->Read(wxT("SecureRemember/Name")));
	}
}

//Get bitmap resources
wxBitmap frmMain::GetBitmapResource(const wxString& name){
	wxString strPath = wxPathOnly(wxStandardPaths::Get().GetExecutablePath()) + wxFILE_SEP_PATH;
	if (name == _T("save.png")) {
		wxBitmap bitmap(strPath + _T("save.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	} 
	else if (name == _T("add.png")) {
		wxBitmap bitmap(strPath + _T("add.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	} 
	else if (name == _T("expandall.png")) {
		wxBitmap bitmap(strPath + _T("expandall.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	} 
	else if (name == _T("ok.png")) {
		wxBitmap bitmap(strPath + _T("ok.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("preview.png")) {
		wxBitmap bitmap(strPath + _T("preview.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("remove.png")) {
		wxBitmap bitmap(strPath + _T("remove.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("sync.png")) {
		wxBitmap bitmap(strPath + _T("sync.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("backup.png")) {
		wxBitmap bitmap(strPath + _T("backup.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("secure.png")) {
		wxBitmap bitmap(strPath + _T("secure.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("settings.png")) {
		wxBitmap bitmap(strPath + _T("settings.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("rules.png")) {
		wxBitmap bitmap(strPath + _T("rules.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("script.png")) {
		wxBitmap bitmap(strPath + _T("script.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("pvars.png")) {
		wxBitmap bitmap(strPath + _T("pvars.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("addvar.png")) {
		wxBitmap bitmap(strPath + _T("addvar.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	else if (name == _T("help.png")) {
		wxBitmap bitmap(strPath + _T("help.png"), wxBITMAP_TYPE_PNG);
		return bitmap;
	}
	return wxNullBitmap;
}

//ID_BACKUP_ADD
void frmMain::OnBackupAddClick(wxCommandEvent& WXUNUSED(event)){
	wxBusyCursor cursor;
	m_Backup_TreeCtrl->SetPreview(false);
	wxArrayString arrPaths = m_Backup_DirCtrl->GetSelectedPaths();
	int added = arrPaths.GetCount();
	int existing = m_BackupLocations->GetCount();
	if(m_Backup_Function->GetStringSelection() == _("Differential") && added + existing > 1){
		wxMessageBox(_("Differential only supports one folder"), _("Error"), wxICON_ERROR);
		return;
	}
	for(unsigned int i = 0; i < arrPaths.Count(); i++){
		m_BackupLocations->Add(arrPaths.Item(i));
		m_Backup_TreeCtrl->AddNewPath(arrPaths.Item(i));		
	}
}

//ID_SECURE_ADD
void frmMain::OnSecureAddClick(wxCommandEvent& WXUNUSED(event)){
	wxBusyCursor cursor;
	m_Secure_TreeCtrl->SetPreview(false);
	wxArrayString arrPaths = m_Secure_DirCtrl->GetSelectedPaths();
	for(unsigned int i = 0; i < arrPaths.Count(); i++){
		m_SecureLocations->Add(arrPaths.Item(i));
		m_Secure_TreeCtrl->AddNewPath(arrPaths.Item(i));		
	}
}

//ID_BACKUP_REMOVE
void frmMain::OnBackupRemoveClick(wxCommandEvent& WXUNUSED(event)){
	//Checks to see if it is a top level item that is being removed
	if (m_Backup_TreeCtrl->GetItemParent(m_Backup_TreeCtrl->GetSelection()) == m_Backup_TreeCtrl->GetRootItem()){
		//A loop to compare to normalised and non-normalised files
		for(unsigned int i = 0; i < m_BackupLocations->GetCount(); i++){
			if(Normalise(Normalise(m_BackupLocations->Item(i))) == m_Backup_TreeCtrl->GetItemText(m_Backup_TreeCtrl->GetSelection())){
				m_BackupLocations->RemoveAt(i);
			}
		}
		m_Backup_TreeCtrl->Delete(m_Backup_TreeCtrl->GetSelection());
	}
}

//ID_SECURE_REMOVE
void frmMain::OnSecureRemoveClick(wxCommandEvent& WXUNUSED(event)){
	//Checks to see if it is a top level item that is being removed
	if (m_Secure_TreeCtrl->GetItemParent(m_Secure_TreeCtrl->GetSelection()) == m_Secure_TreeCtrl->GetRootItem()){
		//A loop to compare to normalised and non-normalised files
		for(unsigned int i = 0; i < m_SecureLocations->GetCount(); i++){
			if(Normalise(Normalise(m_SecureLocations->Item(i))) == m_Secure_TreeCtrl->GetItemText(m_Secure_TreeCtrl->GetSelection())){
				m_SecureLocations->RemoveAt(i);
			}
		}
		m_Secure_TreeCtrl->Delete(m_Secure_TreeCtrl->GetSelection());
	}
}

//ID_SYNC_SOURCE_BTN
void frmMain::OnSyncSourceBtnClick(wxCommandEvent& WXUNUSED(event)){
	//Need to replace this with a better browser
	wxDirDialog dialog(this,_("Please select the source folder."), Normalise(Normalise(m_Sync_Source_Txt->GetValue())));
	if (dialog.ShowModal() == wxID_OK) {
		wxBusyCursor cursor;
		m_Sync_Source_Tree->DeleteAllItems();
		m_Sync_Source_Tree->AddRoot(wxT("Hidden root"));
		m_Sync_Source_Tree->AddNewPath(Normalise(Normalise(dialog.GetPath())));
		m_Sync_Source_Txt->SetValue(dialog.GetPath());
	}
}

//ID_SYNC_DEST_BTN
void frmMain::OnSyncDestBtnClick(wxCommandEvent& WXUNUSED(event)){
	//Need to replace this with a better browser	
	wxDirDialog dialog(this,_("Please select the desination folder."), Normalise(Normalise(m_Sync_Dest_Txt->GetValue())));
	if (dialog.ShowModal() == wxID_OK) {
		wxBusyCursor cursor;
		m_Sync_Dest_Tree->DeleteAllItems();
		m_Sync_Dest_Tree->AddRoot(wxT("Hidden root"));
		m_Sync_Dest_Tree->AddNewPath(Normalise(Normalise(dialog.GetPath())));
		m_Sync_Dest_Txt->SetValue(dialog.GetPath());
	}
}

//ID_RULES_ADD_FILEEXCLUDE
void frmMain::OnRulesAddFileexcludeClick(wxCommandEvent& WXUNUSED(event)){
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("File to exclude"), wxEmptyString);
	if (dialog->ShowModal() == wxID_OK) {
		m_Rules_FileExclude->Append(dialog->GetValue());
	}
	delete dialog;
}

//ID_RULES_ADD_FOLDEREXCLUDE
void frmMain::OnRulesAddFolderexcludeClick(wxCommandEvent& WXUNUSED(event)){
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("Folder to exclude"),wxEmptyString);
	if (dialog->ShowModal() == wxID_OK) {
		m_Rules_FolderExclude->Append(dialog->GetValue());
	}
	delete dialog;
}

//ID_RULES_REMOVE_FILEEXCLUDE
void frmMain::OnRulesRemoveFileexcludeClick(wxCommandEvent& WXUNUSED(event)){
	m_Rules_FileExclude->Delete(m_Rules_FileExclude->GetSelection());
}

//ID_RULES_REMOVE_FOLDEREXCLUDE
void frmMain::OnRulesRemoveFolderexcludeClick(wxCommandEvent& WXUNUSED(event)){
	m_Rules_FolderExclude->Delete(m_Rules_FolderExclude->GetSelection());
}

//ID_RULES_SAVE
void frmMain::OnRulesSaveClick(wxCommandEvent& WXUNUSED(event)){
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
	if(m_Rules_Name->GetStringSelection() != wxEmptyString){
		rules.TransferToFile(m_Rules_Name->GetStringSelection());
	}
	else{
		wxMessageBox(_("You must select a name for this set of Rules"), _("Error"), wxICON_ERROR);
	}
	//Store what the old selected rules were
	wxString sync, backup, secure;
	sync = m_Sync_Rules->GetStringSelection();
	backup = m_Backup_Rules->GetStringSelection();
	secure = m_Secure_Rules->GetStringSelection();
	//Set up the rules boxes
	SetRulesBox(m_Sync_Rules);
	SetRulesBox(m_Backup_Rules);
	SetRulesBox(m_Secure_Rules);
	//Set them to old values
	m_Sync_Rules->SetStringSelection(sync);
	m_Backup_Rules->SetStringSelection(backup);
	m_Secure_Rules->SetStringSelection(secure);
}

//ID_RULES_ADD
void frmMain::OnRulesAddClick(wxCommandEvent& WXUNUSED(event)){
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("You must select a name for this set of Rules"), wxEmptyString);
	if (dialog->ShowModal() == wxID_OK) {
		m_Rules_Name->AppendString(dialog->GetValue());
		m_Rules_Name->SetStringSelection(dialog->GetValue());
		m_Rules_LocationInclude->Clear();
		m_Rules_FileExclude->Clear();
		m_Rules_FolderExclude->Clear();
	}
	delete dialog;
}

//ID_RULES_REMOVE
void frmMain::OnRulesRemoveClick(wxCommandEvent& WXUNUSED(event)){
	m_Rules_LocationInclude->Clear();
	m_Rules_FileExclude->Clear();
	m_Rules_FolderExclude->Clear();
	wxGetApp().m_Rules_Config->DeleteGroup(m_Rules_Name->GetStringSelection());
	wxGetApp().m_Rules_Config->Flush();
	m_Rules_Name->Delete(m_Rules_Name->GetSelection());
}

//ID_RULES_COMBO
void frmMain::OnRulesComboSelected(wxCommandEvent& WXUNUSED(event)){
	//Clear the existing rules
	m_Rules_LocationInclude->Clear();
	m_Rules_FileExclude->Clear();
	m_Rules_FolderExclude->Clear();
	
	//Create a new rule set
	Rules rules;
	if (rules.TransferFromFile(m_Rules_Name->GetStringSelection())) {
		//Loop through the array of rules and add them to the form
		for (unsigned int i = 0; i < rules.GetLocationsToInclude().GetCount(); i++) {
			m_Rules_LocationInclude->Append(rules.GetLocationsToInclude().Item(i));
		}
		for (unsigned int j = 0; j < rules.GetFilesToExclude().GetCount(); j++) {
			m_Rules_FileExclude->Append(rules.GetFilesToExclude().Item(j));
		}
		for (unsigned int k = 0; k < rules.GetFoldersToExclude().GetCount(); k++) {
			m_Rules_FolderExclude->Append(rules.GetFoldersToExclude().Item(k));
		}
	}
	SetTitleBarText();
}

//ID_SYNC_JOB_SAVE
void frmMain::OnSyncJobSaveClick(wxCommandEvent& WXUNUSED(event)){
	JobSave(m_Sync_Job_Select->GetStringSelection(), m_Sync_Rules->GetStringSelection(), wxT("Sync"));
}

//ID_BACKUP_JOB_SAVE
void frmMain::OnBackupJobSaveClick(wxCommandEvent& WXUNUSED(event)){
	JobSave(m_Backup_Job_Select->GetStringSelection(), m_Backup_Rules->GetStringSelection(), wxT("Backup"));
}

//ID_SECURE_JOB_SAVE
void frmMain::OnSecureJobSaveClick(wxCommandEvent& WXUNUSED(event)){
	JobSave(m_Secure_Job_Select->GetStringSelection(), m_Secure_Rules->GetStringSelection(), wxT("Secure"));
}

//ID_SYNC_JOB_ADD
void frmMain::OnSyncJobAddClick(wxCommandEvent& WXUNUSED(event)){
	JobAdd(m_Sync_Job_Select);
}

//ID_BACKUP_JOB_ADD
void frmMain::OnBackupJobAddClick(wxCommandEvent& WXUNUSED(event)){
	JobAdd(m_Backup_Job_Select);
}

//ID_SECURE_JOB_ADD
void frmMain::OnSecureJobAddClick(wxCommandEvent& WXUNUSED(event)){
	JobAdd(m_Secure_Job_Select);
}

//ID_SYNC_JOB_REMOVE
void frmMain::OnSyncJobRemoveClick(wxCommandEvent& WXUNUSED(event)){
	JobRemove(m_Sync_Job_Select);	
}

//ID_BACKUP_JOB_REMOVE
void frmMain::OnBackupJobRemoveClick(wxCommandEvent& WXUNUSED(event)){
	JobRemove(m_Backup_Job_Select);
}

//ID_SECURE_JOB_REMOVE
void frmMain::OnSecureJobRemoveClick(wxCommandEvent& WXUNUSED(event)){
	JobRemove(m_Secure_Job_Select);
}

//ID_BACKUP_JOB_SELECT
void frmMain::OnBackupJobSelectSelected(wxCommandEvent& WXUNUSED(event)){
	JobLoad(m_Backup_Job_Select->GetStringSelection(), m_Backup_Rules, wxT("Backup"));
}

//ID_SECURE_JOB_SELECT
void frmMain::OnSecureJobSelectSelected(wxCommandEvent& WXUNUSED(event)){
	JobLoad(m_Secure_Job_Select->GetStringSelection(), m_Secure_Rules, wxT("Secure"));
}

//ID_SYNC_JOB_SELECT
void frmMain::OnSyncJobSelectSelected(wxCommandEvent& WXUNUSED(event)){
	JobLoad(m_Sync_Job_Select->GetStringSelection(), m_Sync_Rules, wxT("Sync"));
}

//ID_RULES_ADD_FILEINCLUDE
void frmMain::OnRulesAddLocationincludeClick(wxCommandEvent& WXUNUSED(event)){
	wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("Location to include"),wxEmptyString);
	if (dialog->ShowModal() == wxID_OK) {
		m_Rules_LocationInclude->Append(dialog->GetValue());
	}
	delete dialog;
}

//ID_RULES_REMOVE_FILEINCLUDE
void frmMain::OnRulesRemoveLocationincludeClick(wxCommandEvent& WXUNUSED(event)){
	m_Rules_LocationInclude->Delete(m_Rules_LocationInclude->GetSelection());
}

//ID_BACKUP_LOCATION
void frmMain::OnBackupLocationClick(wxCommandEvent& WXUNUSED(event)){
	if(m_Backup_Function->GetStringSelection() == _("Differential")){
		wxDirDialog dialog(this,_("Please select the folder to store your backups"),m_Backup_Location->GetValue());
		if (dialog.ShowModal() == wxID_OK){
			m_Backup_Location->SetValue(dialog.GetPath());
		}
	}
	else if(m_Backup_Function->GetStringSelection() == _("Restore")){
		wxDirDialog dialog(this,_("Restore into:"),m_Backup_Location->GetValue());
		if (dialog.ShowModal() == wxID_OK){
			m_Backup_Location->SetValue(dialog.GetPath());
		}
	}
	else{
		wxString strWildcard;
		if(m_Backup_Format->GetStringSelection() == wxT("7-Zip")){
			strWildcard = wxT("7 Zip (*.7z)|*.7z|All Files (*.*)|*.*");
		}
		else if(m_Backup_Format->GetStringSelection() == wxT("Zip")){
			strWildcard = wxT("Zip Files (*.zip)|*.zip|All Files (*.*)|*.*");
		}		
		wxFileDialog dialog(this,_("Please choose a file to backup to"), wxPathOnly(m_Backup_Location->GetValue()), wxEmptyString, strWildcard, wxFD_SAVE);
		if (dialog.ShowModal() == wxID_OK) {
			m_Backup_Location->SetValue(dialog.GetPath());
		}
	}
}

//ID_SYNC_OK
void frmMain::OnSyncOKClick(wxCommandEvent& WXUNUSED(event)){
	Run(m_Sync_Rules->GetStringSelection(), wxT("Sync"));
}

//ID_BACKUP_OK
void frmMain::OnBackupOKClick(wxCommandEvent& WXUNUSED(event)){
	if(m_Backup_Function->GetStringSelection() == _("Differential") && m_BackupLocations->GetCount() > 1){
		wxMessageBox(_("Differential only supports one folder"), _("Error"), wxICON_ERROR);
		return;
	}
	//Differential needs a folder to store its files in
	if(m_Backup_Function->GetStringSelection() ==_("Differential") && m_Backup_Location->GetValue() != wxEmptyString){
		if(m_Backup_Location->GetValue().Right(3) == wxT(".7z") || m_Backup_Location->GetValue().Right(4) == wxT(".zip")){
			wxMessageBox(_("Please select the folder to store your backups"), _("Error"), wxICON_ERROR);
			return;
		}
	}
	Run(m_Backup_Rules->GetStringSelection(), wxT("Backup"));
}

//ID_SECURE_OK
void frmMain::OnSecureOKClick(wxCommandEvent& WXUNUSED(event)){
	Run(m_Secure_Rules->GetStringSelection(), wxT("Secure"));
	m_Secure_DirCtrl->ReCreateTree();
}

//ID_SYNC_PREVIEW
void frmMain::OnSyncPreviewClick(wxCommandEvent& WXUNUSED(event)){
	wxBusyCursor cursor;
	m_Notebook->Disable();
	//Get the rules
	Rules rules;
	if (m_Sync_Rules->GetStringSelection() != wxEmptyString) {
		rules.TransferFromFile(m_Sync_Rules->GetStringSelection());
	}	
	m_Sync_Dest_Tree->SetRules(rules);
	m_Sync_Dest_Tree->DeleteAllItems();
	m_Sync_Dest_Tree->AddRoot(wxT("Hidden root"));
	m_Sync_Dest_Tree->SetPreview(true);
	m_Sync_Dest_Tree->SetSync(true);
	m_Sync_Dest_Tree->AddNewPath(Normalise(Normalise(m_Sync_Dest_Txt->GetValue())));

	if(m_Sync_Function->GetStringSelection() == _("Equalise")){
		m_Sync_Source_Tree->SetRules(rules);
		m_Sync_Source_Tree->DeleteAllItems();
		m_Sync_Source_Tree->AddRoot(wxT("Hidden root"));
		m_Sync_Source_Tree->SetSync(true);
		m_Sync_Source_Tree->SetPreview(true);
		m_Sync_Source_Tree->AddNewPath(Normalise(Normalise(m_Sync_Source_Txt->GetValue())));
	}
	m_Notebook->Enable();
}

//ID_BACKUP_PREVIEW
void frmMain::OnBackupPreviewClick(wxCommandEvent& WXUNUSED(event)){
	//Create a new rule set and populate it from the form
	Rules rules;
	if(m_Backup_Rules->GetStringSelection() != wxEmptyString){
		rules.TransferFromFile(m_Backup_Rules->GetStringSelection());
	}
	//Set up the tree ctrl for previewing
	m_Backup_TreeCtrl->SetSync(false);
	m_Backup_TreeCtrl->SetPreview(true);
	m_Backup_TreeCtrl->SetRules(rules);
	//Delete all items and re-add the root
	m_Backup_TreeCtrl->DeleteAllItems();
	m_Backup_TreeCtrl->AddRoot(wxT("Hidden root"));
	for (unsigned int i = 0; i < m_BackupLocations->GetCount(); i++){
		//Loop through all the the filenames listed in the array and read them to the tree
		m_Backup_TreeCtrl->AddNewPath(Normalise(Normalise(m_BackupLocations->Item(i))));
	}
}

//ID_SECURE_PREVIEW
void frmMain::OnSecurePreviewClick(wxCommandEvent& WXUNUSED(event)){
	//Create a new rule set and populate it from the form
	Rules rules;
	if(m_Secure_Rules->GetStringSelection() != wxEmptyString){
		rules.TransferFromFile(m_Secure_Rules->GetStringSelection());
	}
	//Set up the tree ctrl for previewing
	m_Secure_TreeCtrl->SetSync(false);
	m_Secure_TreeCtrl->SetPreview(true);
	m_Secure_TreeCtrl->SetRules(rules);
	//Delete all items and re-add the root
	m_Secure_TreeCtrl->DeleteAllItems();
	m_Secure_TreeCtrl->AddRoot(wxT("Hidden root"));
	for (unsigned int i = 0; i < m_SecureLocations->GetCount(); i++) {
		//Loop through all the the filenames listed in the array and readd them to the tree
		m_Secure_TreeCtrl->AddNewPath(Normalise(Normalise(m_SecureLocations->Item(i))));
	}
}

void frmMain::OnCloseWindow(wxCloseEvent& WXUNUSED(event)){
	int height, width, x, y;
	wxClientDisplayRect(&x, &y, &width, &height);
	
	wxGetApp().m_Settings->SetHeight((double)(this->GetSize().GetHeight())/(height));
	wxGetApp().m_Settings->SetWidth((double)(this->GetSize().GetWidth())/(width));
	wxGetApp().m_Settings->SetX((double)(this->GetScreenPosition().x)/(width));
	wxGetApp().m_Settings->SetY((double)(this->GetScreenPosition().y)/(height));
	wxGetApp().m_Settings->SetPosition(m_Notebook->GetPageText(m_Notebook->GetSelection()));

	wxGetApp().m_Settings->TransferToFile();	

	wxGetApp().MainWindow->Destroy();
	wxGetApp().ProgressWindow->Destroy();
}

//ID_VARIABLES_ADD
void frmMain::OnVariablesAddClick(wxCommandEvent& WXUNUSED(event)){	
    wxTextEntryDialog dialog(this, _("Please enter the name for the new portable variable"), _("New Portable Variable") ,wxEmptyString, wxOK|wxCANCEL);
	if(dialog.ShowModal() == wxID_OK){
        if(!wxGetApp().m_Variables_Config->HasGroup(dialog.GetValue())){
            m_Variables_List->ClearAll();
            wxListItem column;
            m_Variables_List->InsertColumn(0, column);
            m_Variables_List->InsertColumn(1, column);
            wxGetApp().m_Variables_Config->Write(dialog.GetValue() + wxT("/") + wxGetFullHostName() , wxEmptyString);
            wxGetApp().m_Variables_Config->Write(dialog.GetValue() + wxT("/") + _("Other") , wxEmptyString);
            wxGetApp().m_Variables_Config->Flush();
            m_Variables_Name->Append(dialog.GetValue());
            m_Variables_Name->SetStringSelection(dialog.GetValue());
            m_Variables_List->InsertItem(0, wxT("Test"));
            m_Variables_List->SetItem(0, 0, wxGetFullHostName());
            m_Variables_List->InsertItem(1, wxT("Test"));
            m_Variables_List->SetItem(1, 0, _("Other"));
        }
        else{
            wxMessageBox(_("There is already a Portable Variable with this name."), _("Error"), wxICON_ERROR);
        }
    }
}

//ID_VARIABLES_REMOVE
void frmMain::OnVariablesRemoveClick(wxCommandEvent& WXUNUSED(event)){	
	wxGetApp().m_Variables_Config->DeleteGroup(m_Variables_Name->GetValue());
	wxGetApp().m_Variables_Config->Flush();
	m_Variables_Name->Delete(m_Variables_Name->GetSelection());
	m_Variables_Name->SetValue(wxEmptyString);
	m_Variables_List->ClearAll();
	wxListItem column;
	m_Variables_List->InsertColumn(0, column);
	m_Variables_List->InsertColumn(1, column);
}

//ID_VARIABLES_NAME
void frmMain::OnVariablesNameSelected(wxCommandEvent& WXUNUSED(event)){	
	m_Variables_List->DeleteAllItems();
	
    wxGetApp().m_Variables_Config->SetPath(m_Variables_Name->GetValue());
    
	long dummy;
    wxString str;
    int i = 0;
	
    bool bCont = wxGetApp().m_Variables_Config->GetFirstEntry(str, dummy);
    while(bCont) {
        m_Variables_List->InsertItem(i, wxT("Test"));
        m_Variables_List->SetItem(i, 0, str);
		//Return the config to the top level
        wxGetApp().m_Variables_Config->SetPath(wxT("/"));
        wxString strTest = wxGetApp().m_Variables_Config->Read(m_Variables_Name->GetValue() + wxT("/") + str, wxT("Cannot Find Value"));
        m_Variables_List->SetItem(i, 1, strTest);
		//Put the config location back
        wxGetApp().m_Variables_Config->SetPath(m_Variables_Name->GetValue());    
        bCont = wxGetApp().m_Variables_Config->GetNextEntry(str, dummy);
        i++;
    }
	m_Variables_List->SetColumnWidth(0, -1);
	m_Variables_List->SetColumnWidth(1, -1);
	SetTitleBarText();
    wxGetApp().m_Variables_Config->SetPath(wxT("/"));
}

//ID_VARIABLES_ADDITEM
void frmMain::OnVariablesAddItemClick(wxCommandEvent& WXUNUSED(event)){	
	int j = m_Variables_List->GetItemCount();
	m_Variables_List->InsertItem(j, wxT("Test"));
	m_Variables_List->SetItem(j, 0, wxGetFullHostName());
	wxString caption = _("Choose a directory");
	wxString wildcard = wxT("All Files (*.*)|*.*");
	wxString defaultFilename = wxEmptyString;
	wxString defaultDir = wxT("/");
	wxString strPath;
	wxDirDialog dialog(this, caption, defaultDir);
	if (dialog.ShowModal() == wxID_OK){
		m_Variables_List->SetItem(j, 1, dialog.GetPath());
	}
	else{
		m_Variables_List->SetItem(j, 1, wxEmptyString);
	}
	wxGetApp().m_Variables_Config->Write(m_Variables_Name->GetValue() + wxT("/") + wxGetFullHostName() , dialog.GetPath());
	wxGetApp().m_Variables_Config->Flush();
}

//ID_VARIABLES_REMOVEITEM
void frmMain::OnVariablesRemoveItemClick(wxCommandEvent& WXUNUSED(event)){	
	wxString selected;
	long item = -1;
	for ( ;;)
	{
		item = m_Variables_List->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if ( item == -1)
		break;
		selected = m_Variables_List->GetItemText(item);
		m_Variables_List->DeleteItem(item);
	}
	wxGetApp().m_Variables_Config->DeleteEntry(m_Variables_Name->GetValue() + wxT("/") + selected);
	wxGetApp().m_Variables_Config->Flush();
}

//ID_VARIABLES_LIST
void frmMain::OnVariablesListActivated(wxListEvent& WXUNUSED(event)){	
	long item = -1;
	for ( ;;)
	{
		item = m_Variables_List->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
		if ( item == -1)
		break;
		
		wxListItem PreviousColumn1;
		PreviousColumn1.m_itemId = item;
		PreviousColumn1.m_col = 1;
		PreviousColumn1.m_mask = wxLIST_MASK_TEXT;
		m_Variables_List->GetItem(PreviousColumn1);
		wxString strPreviousColumn1 = PreviousColumn1.m_text;
		wxTextEntryDialog location(this, _("Please insert the location you want to point to."), _("Location"), strPreviousColumn1, wxOK);
		if(location.ShowModal() == wxID_OK){
			m_Variables_List->SetItem(item , 1, location.GetValue());
		}
		m_Variables_List->SetColumnWidth(0, -1);
		m_Variables_List->SetColumnWidth(1, -1);
		wxGetApp().m_Variables_Config->Write(m_Variables_Name->GetValue() + wxT("/") + m_Variables_List->GetItemText(item), location.GetValue());
		wxGetApp().m_Variables_Config->Flush();
	}
}

//ID_SCRIPT_EXECUTE
void frmMain::OnScriptExecute(wxCommandEvent& WXUNUSED(event)){	
	wxArrayString arrLines;
	for(signed int i = 0; i < m_Script_Rich->GetNumberOfLines(); i++){
		arrLines.Add(m_Script_Rich->GetLineText(i));
	}
	wxGetApp().m_Script->SetScript(arrLines);
	wxGetApp().m_Script->Execute();
}

//ID_SCRIPT_NAME
void frmMain::OnScriptSelected(wxCommandEvent& WXUNUSED(event)){	
	m_Script_Rich->Clear();
	wxString strFile = 	wxGetApp().m_Scripts_Config->Read(m_Script_Name->GetStringSelection() + wxT("/") + wxT("Script"));
	//Remove trailing | if it exists
	if(strFile.Right(1) == wxT("|")){
		strFile = strFile.Left(strFile.Length() - 1);
		if(strFile.Length() == 0){
			return;
		}
	}
	//We should now have a nicely formatted array of one command per line
	wxArrayString arrContents = StringToArrayString(strFile, wxT("|"));
	//If we have more then one item then we need to add line breaks between them
	if(arrContents.GetCount() > 1){
		unsigned int i;
		for(i = 0; i < arrContents.Count() - 1; i++){
			m_Script_Rich->AppendText(arrContents.Item(i) + wxT("\n"));
		}
		m_Script_Rich->AppendText(arrContents.Item(i));
		SetTitleBarText();
	}
	//If only one item then just add it
	else if(arrContents.GetCount() == 1){
		m_Script_Rich->AppendText(arrContents.Item(0));		
	}
}

//ID_SCRIPT_SAVE
void frmMain::OnScriptSaveClick(wxCommandEvent& WXUNUSED(event)){	
	wxArrayString arrContents;
	for(signed int i = 0; i < m_Script_Rich->GetNumberOfLines(); i++){
		arrContents.Add(m_Script_Rich->GetLineText(i));
	}
	wxGetApp().m_Scripts_Config->Write(m_Script_Name->GetStringSelection() + wxT("/") + wxT("Script"), ArrayStringToString(arrContents, wxT("|")));
	wxGetApp().m_Scripts_Config->Flush();
}

//ID_SCRIPT_REMOVE
void frmMain::OnScriptRemoveClick(wxCommandEvent& WXUNUSED(event)){	
	wxGetApp().m_Scripts_Config->DeleteGroup(m_Script_Name->GetStringSelection());
	wxGetApp().m_Scripts_Config->Flush();
	m_Script_Name->Delete(m_Script_Name->GetSelection());
}

//ID_SCRIPT_ADD
void frmMain::OnScriptAddClick(wxCommandEvent& WXUNUSED(event)){	
	wxTextEntryDialog* dialog = new wxTextEntryDialog(this, _("Please enter the name for the new script"), _("New Script") ,wxEmptyString, wxOK|wxCANCEL);
	if (dialog->ShowModal() == wxID_OK) {
		m_Script_Name->Append(dialog->GetValue());
		m_Script_Name->SetStringSelection(dialog->GetValue());
	}
	delete dialog;
}

//ID_BACKUP_RATIO
void frmMain::OnBackupRatioChanged(wxScrollEvent& WXUNUSED(event)){
	SetSliderText();
}

//ID_BACKUP_ADDVAR
void frmMain::OnBackupAddVarClick(wxCommandEvent& WXUNUSED(event)){
	frmVariable* window = new frmVariable(NULL, ID_FRMVARIABLE, _("Insert Variable"));
	if(window->ShowModal() == wxID_OK){
		m_BackupLocations->Add(window->m_Location_Text->GetValue());
		m_Backup_TreeCtrl->AddNewPath(Normalise(Normalise(window->m_Preview_Text->GetValue())));
	}
	delete window;
}

//ID_SECURE_ADDVAR
void frmMain::OnSecureAddVarClick(wxCommandEvent& WXUNUSED(event)){
	frmVariable* window = new frmVariable(NULL, ID_FRMVARIABLE, _("Insert Variable"));
	if(window->ShowModal() == wxID_OK){
		m_SecureLocations->Add(window->m_Location_Text->GetValue());
		m_Secure_TreeCtrl->AddNewPath(Normalise(Normalise(window->m_Preview_Text->GetValue())));
	}
	delete window;	
}

//wxID_ABOUT
void frmMain::OnAboutClick(wxCommandEvent& WXUNUSED(event)){
	wxAboutDialogInfo info;
	info.SetName(wxT("Toucan"));
	info.SetVersion(wxT("2.2.0 Pre-Release 1"));
	info.SetCopyright(wxT("(C) 2006-2009 Steven Lamerton \nName by Danny Mensingh\nMain icons by Neorame\nOther icons by Silvestre Herrera\nExtra thanks to Jorgen Bodde for his awesome wxVirtualDirTreeCtrl\n7Zip and ccrypt are by their respective teams.\nAll items (C) their owners."));
	info.SetWebSite(wxT("http://portableapps.com/toucan"));
	info.SetLicense(wxT("Toucan and its component parts are all licensed under the GNU GPL Version 2 or a compatible license."));
	info.SetTranslators(GetTranslatorNames());
	wxAboutBox(info);
}

//ID_BACKUP_TREECTRL
void frmMain::OnBackupTreeCtrlTooltip(wxTreeEvent& event){
	if(m_Backup_TreeCtrl->GetItemParent(event.GetItem()) == m_Backup_TreeCtrl->GetRootItem()){
		for(unsigned int i = 0; i < m_BackupLocations->GetCount(); i++){
			if(Normalise(Normalise(m_BackupLocations->Item(i))) == m_Backup_TreeCtrl->GetItemText(event.GetItem())){
				event.SetToolTip(m_BackupLocations->Item(i));
			}
		}
	}
}

//ID_SECURE_TREECTRL
void frmMain::OnSecureTreeCtrlTooltip(wxTreeEvent& event){
	if(m_Secure_TreeCtrl->GetItemParent(event.GetItem()) == m_Secure_TreeCtrl->GetRootItem()){
		for(unsigned int i = 0; i < m_SecureLocations->GetCount(); i++){
			if(Normalise(Normalise(m_SecureLocations->Item(i))) == m_Secure_TreeCtrl->GetItemText(event.GetItem())){
				event.SetToolTip(m_SecureLocations->Item(i));
			}
		}
	}	
}

//ID_SYNC_SOURCE_TREE
void frmMain::OnSyncSourceTreeRightClick(wxTreeEvent& event){
	menuTree = m_Sync_Source_Tree;
	menuRules = m_Sync_Rules;
	CreateMenu(event);
}

//ID_SYNC_DEST_TREE
void frmMain::OnSyncDestTreeRightClick(wxTreeEvent& event){
	menuTree = m_Sync_Dest_Tree;
	menuRules = m_Sync_Rules;
	CreateMenu(event);
}

//ID_BACKUP_TREECTRL
void frmMain::OnBackupTreeRightClick(wxTreeEvent& event){
	menuTree = m_Backup_TreeCtrl;
	menuRules = m_Backup_Rules;
	CreateMenu(event);
}

//ID_SECURE_TREECTRL
void frmMain::OnSecureTreeRightClick(wxTreeEvent& event){
	menuTree = m_Secure_TreeCtrl;
	menuRules = m_Secure_Rules;
	CreateMenu(event);
}

//ID_SYNC_SOURCE_EXPAND
void frmMain::OnSyncSourceExpandClick(wxCommandEvent& WXUNUSED(event)){
	m_Sync_Source_Tree->NeatExpandAll(this);
}

//ID_SYNC_DEST_EXPAND
void frmMain::OnSyncDestExpandClick(wxCommandEvent& WXUNUSED(event)){
	m_Sync_Dest_Tree->NeatExpandAll(this);
}

//ID_BACKUP_EXPAND
void frmMain::OnBackupExpandClick(wxCommandEvent& WXUNUSED(event)){
	m_Backup_TreeCtrl->NeatExpandAll(this);
}

//ID_SECURE_EXPAND
void frmMain::OnSecureExpandClick(wxCommandEvent& WXUNUSED(event)){
	m_Secure_TreeCtrl->NeatExpandAll(this);
}

//ID_AUINOTEBOOK
void frmMain::OnTabChanged(wxAuiNotebookEvent& WXUNUSED(event)){
	SetTitleBarText();
}

void frmMain::SetTitleBarText(){
	wxString strTitle = wxT("Toucan - ");
	if(m_Notebook->GetPageText(m_Notebook->GetSelection()) == _("Sync")){
		strTitle = strTitle + m_Sync_Job_Select->GetStringSelection();
	}
	else if(m_Notebook->GetPageText(m_Notebook->GetSelection()) == _("Backup")){
		strTitle = strTitle + m_Backup_Job_Select->GetStringSelection();
	}
	else if(m_Notebook->GetPageText(m_Notebook->GetSelection()) == _("Secure")){
		strTitle = strTitle + m_Secure_Job_Select->GetStringSelection();
	}
	else if(m_Notebook->GetPageText(m_Notebook->GetSelection()) == _("Script")){
		strTitle = strTitle + m_Script_Name->GetStringSelection();
	}
	else if(m_Notebook->GetPageText(m_Notebook->GetSelection()) == _("Rules")){
		strTitle = strTitle + m_Rules_Name->GetStringSelection();
	}
	else if(m_Notebook->GetPageText(m_Notebook->GetSelection()) == _("Variables")){
		strTitle = strTitle +m_Variables_Name->GetStringSelection();
	}	
	if(strTitle == wxT("Toucan - ")){
		this->SetTitle(wxT("Toucan"));
	}
	else{
		this->SetTitle(strTitle);
	}
}

void frmMain::JobAdd(wxComboBox* box){
	wxTextEntryDialog dialog(this, wxEmptyString, _("Job name"));
	if (dialog.ShowModal() == wxID_OK){
		box->Append(dialog.GetValue());
		box->SetStringSelection(dialog.GetValue());
	}
	SetTitleBarText();
	ClearToDefault();
}

void frmMain::JobRemove(wxComboBox* box){
	if (box->GetStringSelection() != wxEmptyString) {
		wxGetApp().m_Jobs_Config->DeleteGroup(box->GetStringSelection());
		wxGetApp().m_Jobs_Config->Flush();
		box->Delete(box->GetSelection());
	}	
	SetTitleBarText();
	ClearToDefault();
}

void frmMain::JobSave(const wxString name, const wxString rules, const wxString type){
	wxBusyCursor cursor;
	RootData* data;
	if(type == wxT("Sync")){
		data = new SyncData();
	}
	else if(type == wxT("Backup")){
		data = new BackupData();
	}
	else if(type == wxT("Secure")){
		data = new SecureData();
	}
	else{
		return;
	}
	data->SetName(name);
	if (data->TransferFromForm()){
		if (data->GetName() != wxEmptyString) {
			data->TransferToFile();
			wxGetApp().m_Jobs_Config->Write(data->GetName() + wxT("/Rules"),  rules);
			wxGetApp().m_Jobs_Config->Write(data->GetName() + wxT("/Type"),  type);
			wxGetApp().m_Jobs_Config->Flush();
		}
		else {
			wxMessageBox(_("Please chose a job to save to"), _("Error"), wxICON_ERROR);
		}
	} 
	delete data;
}

void frmMain::JobLoad(const wxString name, wxComboBox* rules, const wxString type){
	wxBusyCursor cursor;
	ClearToDefault();
	RootData* data;
	if(type == wxT("Sync")){
		data = new SyncData();
	}
	else if(type == wxT("Backup")){
		data = new BackupData();
	}
	else if(type == wxT("Secure")){
		data = new SecureData();
	}
	else{
		return;
	}
	data->SetName(name);
	if (data->TransferFromFile()){
		data->TransferToForm();
		rules->SetStringSelection(wxGetApp().m_Jobs_Config->Read(data->GetName() + wxT("/Rules")));
	}
	SetTitleBarText();
}

void frmMain::ClearToDefault(){
	if(m_Notebook->GetPageText(m_Notebook->GetSelection()) == _("Sync")){
		m_Sync_Function->SetStringSelection(_("Copy"));
		m_Sync_Timestamp->SetValue(false);
		m_Sync_Attributes->SetValue(false);
		m_Sync_Ignore_Readonly->SetValue(false);
		m_Sync_Ignore_DaylightS->SetValue(false);
		m_Sync_Rules->SetStringSelection(wxEmptyString);
		m_Sync_Source_Txt->SetValue(wxEmptyString);
		m_Sync_Dest_Txt->SetValue(wxEmptyString);
		m_Sync_Source_Tree->DeleteAllItems();
		m_Sync_Dest_Tree->DeleteAllItems();
		m_Sync_Source_Tree->SetPreview(false);
		m_Sync_Dest_Tree->SetPreview(false);
	}
	if(m_Notebook->GetPageText(m_Notebook->GetSelection()) == _("Backup")){
		m_Backup_Function->SetStringSelection(_("Complete"));
		m_Backup_Format->SetStringSelection(wxT("Zip"));
		m_Backup_Ratio->SetValue(3);
		m_Backup_IsPass->SetValue(false);
		m_Backup_Location->SetValue(wxEmptyString);
		m_Backup_TreeCtrl->DeleteAllItems();
		m_BackupLocations->Clear();
		m_Backup_TreeCtrl->SetPreview(false);
	}
	if(m_Notebook->GetPageText(m_Notebook->GetSelection()) == _("Secure")){
		m_Secure_Function->SetStringSelection(_("Encrypt"));
		m_Secure_Rules->SetStringSelection(wxEmptyString);
		m_Secure_TreeCtrl->DeleteAllItems();
		m_SecureLocations->Clear();
		m_Backup_TreeCtrl->SetPreview(false);
	}
}

void frmMain::Run(const wxString rules, const wxString type){
	RootData* data;
	if(type == wxT("Sync")){
		data = new SyncData();
	}
	else if(type == wxT("Backup")){
		data = new BackupData();
	}
	else if(type == wxT("Secure")){
		data = new SecureData();
	}
	else{
		return;
	}
	data->SetName(wxT("Last") + type + wxT("Job"));
	if(data->TransferFromForm()){
		if(data->NeededFieldsFilled()){
			if(data->TransferToFile()){
				wxGetApp().m_Jobs_Config->Write(wxT("Last") + type + wxT("Job/Rules"),  rules);
				wxGetApp().m_Jobs_Config->Write(wxT("Last") + type + wxT("Job/Type"),  type);
				wxGetApp().m_Jobs_Config->Flush();	
				wxArrayString arrScript;
				arrScript.Add(type + wxT(" \"Last") + type + wxT("Job\""));
				wxGetApp().SetAbort(false);
				wxGetApp().m_Script->SetScript(arrScript);
				wxGetApp().m_Script->Execute();
			}
		}
		else{
			wxMessageBox(_("Not all of the required fields are filled"), _("Error"), wxICON_ERROR);
		}
	}
	delete data;
}

void frmMain::CreateMenu(wxTreeEvent& event){
	menuTree->SelectItem(event.GetItem());
	wxString strMenuTitle = menuRules->GetStringSelection();
	if(strMenuTitle == wxEmptyString){
		//If no rules are selected then return
		return;
	}
	wxMenu menu(strMenuTitle);
	if(wxFileExists(m_Secure_TreeCtrl->GetFullPath(event.GetItem()).GetFullPath())){
		menu.Append(ID_MENU_FILEEXCLUDE_EXTENSION, _("Exclude by extension"));
		menu.Append(ID_MENU_FILEEXCLUDE_NAME, _("Exclude by name"));
		menu.Append(ID_MENU_LOCATIONINCLUDE_EXTENSION, _("Include by extension"));
		menu.Append(ID_MENU_LOCATIONINCLUDE_NAME, _("Include by name"));
	}	
	else if(wxDirExists(m_Secure_TreeCtrl->GetFullPath(event.GetItem()).GetFullPath())){
		menu.Append(ID_MENU_FOLDEREXCLUDE_NAME, _("Exclude by name"));
		menu.Append(ID_MENU_LOCATIONINCLUDE_NAME, _("Include by name"));
	}	
	this->PopupMenu(&menu, event.GetPoint() + menuTree->GetPosition());
}

//ID_MENU_FILEEXCLUDE_EXTENSION
void frmMain::OnMenuFileExcludeExtensionClick(wxCommandEvent& WXUNUSED(event)){
	if(menuRules->GetStringSelection() != wxEmptyString){
		Rules rules;
		rules.TransferFromFile(menuRules->GetStringSelection());
		wxArrayString arrFileExclude = rules.GetFilesToExclude();
		arrFileExclude.Add(wxT(".") + menuTree->GetFullPath(menuTree->GetSelection()).GetExt());
		rules.SetFilesToExclude(arrFileExclude);
		rules.TransferToFile(menuRules->GetStringSelection());
	}	
}

//ID_MENU_FILEEXCLUDE_NAME
void frmMain::OnMenuFileExcludeNameClick(wxCommandEvent& WXUNUSED(event)){
	if(menuRules->GetStringSelection() != wxEmptyString){
		Rules rules;
		rules.TransferFromFile(menuRules->GetStringSelection());
		wxArrayString arrFileExclude = rules.GetFoldersToExclude();
		arrFileExclude.Add(menuTree->GetItemText(menuTree->GetSelection()));
		rules.SetFoldersToExclude(arrFileExclude);
		rules.TransferToFile(menuRules->GetStringSelection());
	}	
}

//ID_MENU_LOCATIONINCLUDE_EXTENSION
void frmMain::OnMenuLocationIncludeExtensionClick(wxCommandEvent& WXUNUSED(event)){
	if(menuRules->GetStringSelection() != wxEmptyString){
		Rules rules;
		rules.TransferFromFile(menuRules->GetStringSelection());
		wxArrayString arrLocationInclude = rules.GetLocationsToInclude();
		arrLocationInclude.Add(wxT(".") + menuTree->GetFullPath(menuTree->GetSelection()).GetExt());
		rules.SetLocationsToInclude(arrLocationInclude);
		rules.TransferToFile(menuRules->GetStringSelection());
	}		
}

//ID_MENU_LOCATIONINCLUDE_NAME
void frmMain::OnMenuLocationIncludeNameClick(wxCommandEvent& WXUNUSED(event)){
	if(menuRules->GetStringSelection() != wxEmptyString){
		Rules rules;
		rules.TransferFromFile(menuRules->GetStringSelection());
		wxArrayString arrLocationInclude = rules.GetLocationsToInclude();
		arrLocationInclude.Add(menuTree->GetItemText(menuTree->GetSelection()));
		rules.SetLocationsToInclude(arrLocationInclude);
		rules.TransferToFile(menuRules->GetStringSelection());
	}		
}

//ID_MENU_FOLDEREXCLUDE_NAME
void frmMain::OnMenuFolderExcludeNameClick(wxCommandEvent& WXUNUSED(event)){
	if(menuRules->GetStringSelection() != wxEmptyString){
		Rules rules;
		rules.TransferFromFile(menuRules->GetStringSelection());
		wxArrayString arrFolderExclude = rules.GetFoldersToExclude();
		arrFolderExclude.Add(menuTree->GetItemText(menuTree->GetSelection()));
		rules.SetFoldersToExclude(arrFolderExclude);
		rules.TransferToFile(menuRules->GetStringSelection());
	}		
}

void frmMain::OnSyncTreeCtrlTooltip(wxTreeEvent& event){
	wxVirtualDirTreeCtrl* tree = static_cast<wxVirtualDirTreeCtrl*> (event.GetEventObject());
	VdtcTreeItemBase* item = static_cast<VdtcTreeItemBase*> (tree->GetItemData(event.GetItem()));

	if(item->GetColour() == wxColour(wxT("Blue"))){
		event.SetToolTip(_("Copied "));
	}
	else if(item->GetColour() == wxColour(wxT("Grey"))){
		event.SetToolTip(_("Deleted "));
	}
	else if(item->GetColour() == wxColour(wxT("Green"))){
		event.SetToolTip(_("Overwritten"));
	}
	else if(item->GetColour() == wxColour(wxT("Red"))){
		event.SetToolTip(_("If needed"));
	}
}

void frmMain::OnBackupFunctionSelected(wxCommandEvent& event){
	if(event.GetString() == _("Restore")){
		wxWindow::FindWindowById(ID_BACKUP_PREVIEW)->Disable();
	}
	else{
		wxWindow::FindWindowById(ID_BACKUP_PREVIEW)->Enable();	
	}
}


void frmMain::SetSliderText(){
	switch(m_Backup_Ratio->GetValue()){
		case 0:
			m_Backup_Ratio_Text->SetLabel(_("None"));
			break;
		case 1:
			m_Backup_Ratio_Text->SetLabel(_("Fastest"));
			break;
		case 2:
			m_Backup_Ratio_Text->SetLabel(_("Fast"));
			break;
		case 3:
			m_Backup_Ratio_Text->SetLabel(_("Default"));
			break;
		case 4:
			m_Backup_Ratio_Text->SetLabel(_("Maximum"));
			break;
		case 5:
			m_Backup_Ratio_Text->SetLabel(_("Ultra"));
			break;
	}
}

wxArrayString frmMain::GetLanguages(){
	wxArrayString arrLang;
	wxString strPath = wxPathOnly(wxStandardPaths::Get().GetExecutablePath()) + wxFILE_SEP_PATH + wxT("lang") + wxFILE_SEP_PATH;
	wxDir dir(strPath);
	wxString strFilename;
	bool blDir = dir.GetFirst(&strFilename);
	if(blDir){
		do {
			if(wxDirExists(strPath + strFilename))
			{
				if(wxFileExists(strPath + strFilename + wxFILE_SEP_PATH + wxT("lang.ini"))){
					wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), strPath + strFilename + wxFILE_SEP_PATH + wxT("lang.ini"));
					wxString strLanguage = config->Read(wxT("General/LanguageCode"));
					arrLang.Add(wxLocale::FindLanguageInfo(strLanguage)->Description);
				}
			}
		}
		while (dir.GetNext(&strFilename));
	} 
	return arrLang;
}

wxArrayString frmMain::GetTranslatorNames(){
	wxArrayString arrNames;
	wxString strPath = wxPathOnly(wxStandardPaths::Get().GetExecutablePath()) + wxFILE_SEP_PATH + wxT("lang") + wxFILE_SEP_PATH;
	wxDir dir(strPath);
	wxString strFilename;
	bool blDir = dir.GetFirst(&strFilename);
	if(blDir){
		do {
			if(wxDirExists(strPath + strFilename))
			{
				if(wxFileExists(strPath + strFilename + wxFILE_SEP_PATH + wxT("lang.ini"))){
					wxFileConfig *config = new wxFileConfig( wxT(""), wxT(""), strPath + strFilename + wxFILE_SEP_PATH + wxT("lang.ini"));
					arrNames.Add(config->Read(wxT("General/Translator")));
				}
			}
		}
		while (dir.GetNext(&strFilename));
	} 
	return arrNames;
}

void frmMain::OnSettingsApplyClick(wxCommandEvent& WXUNUSED(event)){
	wxGetApp().m_Settings->SetPosition(m_Notebook->GetPageText(m_Notebook->GetSelection()));
	wxGetApp().m_Settings->SetTabStyle(m_Settings_TabStyle->GetStringSelection());
	wxGetApp().m_Settings->SetLanguageCode(wxLocale::FindLanguageInfo(m_Settings_Language->GetStringSelection())->CanonicalName);
	wxGetApp().m_Settings->SetFont(m_Settings_Font->GetSelectedFont().GetNativeFontInfoDesc());
	wxGetApp().m_Settings->SetRememberSync(m_Settings_RememberSync->GetValue());
	wxGetApp().m_Settings->SetRememberBackup(m_Settings_RememberBackup->GetValue());
	wxGetApp().m_Settings->SetRememberSecure(m_Settings_RememberSecure->GetValue());
	wxGetApp().m_Settings->SetEnableTooltips(m_Settings_EnableTooltips->GetValue());
	
	if(wxGetApp().m_Settings->GetRememberSync()){
		SyncData data;
		data.SetName(wxT("SyncRemember"));
		data.TransferFromForm();
		data.TransferToFile();
		wxGetApp().m_Jobs_Config->Write(wxT("SyncRemember/Name"), m_Sync_Job_Select->GetStringSelection());
		wxGetApp().m_Jobs_Config->Flush();
	}
	if(wxGetApp().m_Settings->GetRememberBackup()){	
		BackupData bdata;
		bdata.SetName(wxT("BackupRemember"));
		bdata.TransferFromForm();
		bdata.TransferToFile();
		wxGetApp().m_Jobs_Config->Write(wxT("BackupRemember/Name"), m_Backup_Job_Select->GetStringSelection());
		wxGetApp().m_Jobs_Config->Flush();
	}
	if(wxGetApp().m_Settings->GetRememberSecure()){
		SecureData sdata;
		sdata.SetName(wxT("SecureRemember"));
		sdata.TransferFromForm();
		sdata.TransferToFile();
		wxGetApp().m_Jobs_Config->Write(wxT("SecureRemember/Name"), m_Secure_Job_Select->GetStringSelection());
		wxGetApp().m_Jobs_Config->Flush();
	}

	//Set the height and width to be relative to allow Toucan to fit properly when resolution is changed
	int height, width, x, y;
	wxClientDisplayRect(&x, &y, &width, &height);
	
	wxGetApp().m_Settings->SetHeight((double)(this->GetSize().GetHeight())/(height));
	wxGetApp().m_Settings->SetWidth((double)(this->GetSize().GetWidth())/(width));
	wxGetApp().m_Settings->SetX((double)(this->GetScreenPosition().x)/(width));
	wxGetApp().m_Settings->SetY((double)(this->GetScreenPosition().y)/(height));
	
	wxGetApp().m_Settings->TransferToFile();
	wxGetApp().RebuildForm();	
}

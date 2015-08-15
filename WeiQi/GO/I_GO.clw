; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSetAddrDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "i_go.h"
LastPage=0

ClassCount=6
Class1=CI_GOApp
Class2=CAboutDlg
Class3=CI_GODoc
Class4=CI_GOView
Class5=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class6=CSetAddrDlg
Resource3=IDD_DIALOG_ADDR

[CLS:CI_GOApp]
Type=0
BaseClass=CWinApp
HeaderFile=I_GO.h
ImplementationFile=I_GO.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=I_GO.cpp
ImplementationFile=I_GO.cpp
LastObject=CAboutDlg

[CLS:CI_GODoc]
Type=0
BaseClass=CDocument
HeaderFile=I_GODoc.h
ImplementationFile=I_GODoc.cpp

[CLS:CI_GOView]
Type=0
BaseClass=CView
HeaderFile=I_GOView.h
ImplementationFile=I_GOView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_ADDR]
Type=1
Class=CSetAddrDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_IPADDRESS1,SysIPAddress32,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_BUTTON_START
Command2=ID_BUTTON_SETADDR
Command3=ID_BUTTON_PASS
Command4=ID_GAME_DM
Command5=ID_APP_ABOUT
Command6=ID_BUTTON_EXIT
CommandCount=6

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_BUTTON_START
Command3=ID_BUTTON_SETADDR
Command4=ID_BUTTON_PASS
Command5=ID_GAME_DM
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CSetAddrDlg]
Type=0
HeaderFile=SetAddrDlg.h
ImplementationFile=SetAddrDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_IPADDRESS1
VirtualFilter=dWC


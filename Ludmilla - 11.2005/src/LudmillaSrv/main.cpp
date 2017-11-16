//******************************************************************************
#include "header.h"
#include "myheader.h"
//==============================================================================
// ����������� ���������� ����������:
HINSTANCE hInstance;
//------------------------------------------------------------------------------
CSCfgP * SCfgP;
CSCtrlP * SCtrlP;
CService * Service;
//------------------------------------------------------------------------------
// ���������� ��� �������
CPCTSTR SERVICE_NAME = "WDDG Ludmilla";

// �������� ��� �������
CPCTSTR SERVICE_DISPLAY_NAME = "\"WDDG Ludmilla\" service";

// Image path of child process
CPCTSTR SERVER_PROGRAM_IMAGE =	//"C:\\Windows\\System32\\cmd.exe";
								"LudMilla.exe";
// Name of pipe for server program StdOut
CPCTSTR SERVER_PROGRAM_STDOUT_PIPE = "LudaStdOutPipe";

// Name of pipe for server program StdIn
CPCTSTR SERVER_PROGRAM_STDIN_PIPE = "LudaStdInPipe";

// Name of pipe for server program StdOut for service
CPCTSTR SERVER_PROGRAM_STDOUT_PIPE_INTERNAL = "LudaStdOutPipeInt";

// Name of pipe for server program StdIn for service
CPCTSTR SERVER_PROGRAM_STDIN_PIPE_INTERNAL = "LudaStdInPipeInt";

// Capture of communication window
CPCTSTR SERVER_PROGRAM_NAME = "WDDG Ludmilla";

// ��������� ����
CPCTSTR MAINWND_CAPTION = "\"WDDG Ludmilla\" Service Extension";

// Command to kill child of pervious service
PTSTR KILL_STEPSON_CMD = "TASKKILL /IM LudMilla.exe /F";
//==============================================================================
// Program entry point
#pragma warning(disable: 4100) // unreferenced formal parameter
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	::hInstance = hInstance;
	SetLastError(0);
	bool service = false;
	if (lstrcmpi(lpCmdLine, "-service") == 0)
		service = true;

	CCmdLine * cmd_line = NULL;
	try
	{
		if (!service)
		{
			SCfgP = new CSCfgP();
			SCtrlP =  new CSCtrlP();
			if (lstrlen(lpCmdLine) == 0) // GUI
			{
				CMainWnd main_wnd;
				main_wnd.Show(NULL);
			}
			else // Command line
			{
				cmd_line = new CCmdLine();
				cmd_line->ProcessCmdLine(lpCmdLine);
				cmd_line->ShowReport();
			}
		}
		else // service
		{
			Service = new CService();
			Service->main();
		}
	}
	catch (CError &e)
	{
		if (service)
		{
			e.ToEventLog();
			//e.ToGUI(NULL, SERVICE_DISPLAY_NAME, MB_OK|MB_ICONERROR|MB_SERVICE_NOTIFICATION);
		}
		else
			e.Info();
		if (cmd_line != NULL)
			cmd_line->ShowReport();
		return e.GetCode();
	}
	return -1;
}
#pragma warning(default: 4100) // unreferenced formal parameter
//******************************************************************************

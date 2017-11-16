//******************************************************************************
#include "header.h"
#include "../myheader.h"
//==============================================================================
volatile DWORD					CService::CurrentState = SERVICE_STOPPED;
volatile SERVICE_STATUS_HANDLE	CService::ServiceStatusHandle = 0;
volatile HANDLE					CService::hStopEvent = INVALID_HANDLE_VALUE;
volatile DWORD					CService::Win32ExitCode = NO_ERROR;
SERVICE_STATUS					CService::ServiceStatus;
CPCTSTR							CService::service_name = SERVICE_NAME;
CPCTSTR							CService::service_display_name = SERVICE_DISPLAY_NAME;
CRunner*						CService::runner = NULL;
volatile bool					CService::stop_command = false;
//==============================================================================
							// ������� ������:
//------------------------------------------------------------------------------
// ������� ������� �������
void CService::main()
{
	SERVICE_TABLE_ENTRY DispatchTable[] =
	{
		{(LPSTR)service_name, CService::ServiceMain},
		{NULL, NULL}
	};

	chf(FALSE, StartServiceCtrlDispatcher(DispatchTable));
}
//------------------------------------------------------------------------------
// ����� ����� �������
VOID WINAPI CService::ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{

	ServiceStatusHandle = 0;
	restart:
	Win32ExitCode = NO_ERROR;
	try
	{
		// ����������� ���������� ������:
		if (ServiceStatusHandle == 0)
			ServiceStatusHandle = RegisterServiceCtrlHandler(service_name, CService::Handler);
		if (ServiceStatusHandle == 0)
			throwe("RegisterServiceCtrlHandler");

		ReportStatusToSCMgr(SERVICE_START_PENDING, 3000);
		ServiceInitialization();

		ReportStatusToSCMgr(SERVICE_RUNNING, 0);
		//DebugBreak();
		ServiceRun(dwArgc, lpszArgv);

		ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);
	}
	catch(CError &e)
	{
		// ������ � �������
		Win32ExitCode = e.GetCode();
		if (ServiceStatusHandle != 0 && CurrentState != SERVICE_STOPPED)
			try // ������� ���������� ������, ���� �� �������
				{ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);}
			catch(CError &eine) // ������ � ������ :(
				{MessageError(eine);} // ������� � ������ ������
		MessageError(e);  //������� �� ������
	}

	if (ServiceStatusHandle != 0)
		try
		{
			ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);

			// ������������ ������:
			ServiceStop();
			runner->Stop();
			for (int i=0; i<10; i++)
			{
				ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);
				if (runner->WaitForChild(1000))
					break;
			}
			ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);
			runner->Kill();
			ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);
			delete runner;
			runner = NULL;

			ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);

			if (hStopEvent != INVALID_HANDLE_VALUE)
				ch(CloseHandle(hStopEvent));
			hStopEvent = INVALID_HANDLE_VALUE;

			ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);
		}
		catch(CError &e) // ������ ��� ������� �������� �������
			{MessageError(e);}

	// windows bug: is service _stops_ with error it is ok for win.
	// but windows must restart our service. so i force "abnormal termination"
	//if (Win32ExitCode != NO_ERROR)
	if (!stop_command)
		goto restart;
		//ExitProcess(err);
	else
		if (ServiceStatusHandle != 0)
			try
				{ReportStatusToSCMgr(SERVICE_STOPPED, 0);}
			catch(CError &e) // ������ ��� �������� �������
				{MessageError(e);}
}
//------------------------------------------------------------------------------
							// ���������� ������:
//------------------------------------------------------------------------------
// ���������� ������
VOID WINAPI CService::Handler(DWORD fdwControl)
{
	// ����������� �������:
	switch(fdwControl)
	{
		case SERVICE_CONTROL_SHUTDOWN:
		case SERVICE_CONTROL_STOP: // ���������� ������
			ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);
			stop_command = true; // �� �������������, � ���������� - ������� ������
			ServiceStop();
			return;

		case SERVICE_CONTROL_INTERROGATE: // �������� ��������� �������
			break;

		default: // �������� �������
			break;
	}
	ReportStatusToSCMgr(CurrentState, 0);
}
//------------------------------------------------------------------------------
// �������� ������ SCM'��
void CService::ReportStatusToSCMgr(DWORD dwCurrentState, DWORD dwWaitHint)
{
	volatile static DWORD dwCheckPoint = 0;

	CurrentState = dwCurrentState;

	ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCurrentState = dwCurrentState;
	ServiceStatus.dwWin32ExitCode = Win32ExitCode;
	//ServiceStatus.dwServiceSpecificExitCode = -1;
	ServiceStatus.dwWaitHint = dwWaitHint;
	ServiceStatus.dwControlsAccepted = (dwCurrentState == SERVICE_RUNNING) ?
								SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN : 0;
	if ( (dwCurrentState==SERVICE_RUNNING) || (dwCurrentState==SERVICE_STOPPED) )
		ServiceStatus.dwCheckPoint = dwCheckPoint = 0;
	else
		ServiceStatus.dwCheckPoint = ++dwCheckPoint;

	// ������� ������ ������� SCM'��:
	chf(FALSE, SetServiceStatus(ServiceStatusHandle, &ServiceStatus));
}
//------------------------------------------------------------------------------
// �������������� ������
void CService::ServiceInitialization()
{
	ReportStatusToSCMgr(SERVICE_START_PENDING, 3000);

	// create the event object:
	if (  ( hStopEvent=CreateEvent(NULL, TRUE, FALSE, NULL) ) == NULL  )
		throwe("CreateEvent");

	ReportStatusToSCMgr(SERVICE_START_PENDING, 3000);

	// ������ ��'����, ������� �������� ���������
	runner = new CRunner();

	ReportStatusToSCMgr(SERVICE_START_PENDING, 3000);

//	// �������� ������
//
//	ReportStatusToSCMgr(SERVICE_START_PENDING, 3000);
}
//------------------------------------------------------------------------------
// ������� ��������� �������
#pragma warning(disable: 4100) // unreferenced formal parameter
void CService::ServiceRun(DWORD dwArgc, LPTSTR *lpszArgv)
	// ����������� �� �������������� hStopEvent
{
	runner->Start(hStopEvent);
}
#pragma warning(default: 4100) // unreferenced formal parameter
//------------------------------------------------------------------------------
// ������������� ������
void CService::ServiceStop()
	// ������������ hStopEvent ��������� ServiceRun
{
	// ������������ ������
	if (hStopEvent != INVALID_HANDLE_VALUE)
		SetEvent(hStopEvent);
	ReportStatusToSCMgr(SERVICE_STOP_PENDING, 3000);
}
//------------------------------------------------------------------------------
// MessageBox � ������� �� ������, �������� � ������
inline void CService::MessageError(CError &e)
{
	//e.ToGUI(NULL, service_display_name, MB_OK|MB_ICONERROR|MB_SERVICE_NOTIFICATION);
	e.ToEventLog();
}
//******************************************************************************

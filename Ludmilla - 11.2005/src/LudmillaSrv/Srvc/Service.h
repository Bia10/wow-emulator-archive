//******************************************************************************
class CService // ���������� ������
{
public:						// ������� ������:

	// ������� ������� �������
	static void main();

	// ����� ����� �������
	static VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpszArgv);

							// ������� ���������:

	// ���������� ��� �������
	static CPCTSTR service_name;

	// �������� ��� �������
	static CPCTSTR service_display_name;

protected:					// ���������� ������:

	// ���������� ������
	static VOID WINAPI Handler(DWORD fdwControl);

	// �������� ������ SCM'��
	static void ReportStatusToSCMgr(DWORD dwCurrentState, DWORD dwWaitHint);

	// �������������� ������
	static void ServiceInitialization();

	// ������� ��������� �������
	static void ServiceRun(DWORD dwArgc, LPTSTR *lpszArgv);

	// ������������� ������
	static void ServiceStop();

	// ���� _DEBUG - ������� MessageBox � ������� �� ������, �������� � ������
	inline static void MessageError(CError &e);

							// ���������� ������:

	// ��������� ������
	volatile static DWORD					CurrentState;
	volatile static SERVICE_STATUS_HANDLE	ServiceStatusHandle;
	volatile static HANDLE					hStopEvent;
	volatile static DWORD					Win32ExitCode;
	static SERVICE_STATUS					ServiceStatus;

	// �������� ������� "������������"
	volatile static bool stop_command;

	// �����, ����������� ������
	static CRunner *runner;
};
//******************************************************************************

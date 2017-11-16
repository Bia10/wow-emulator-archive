//******************************************************************************
enum EPalcaPosition // Rotating line position
{
	epp_h = 1,	// -
	epp_hv = 2,	// '\'
	epp_v = 3,  // |
	epp_vh = 4	// /
};
//------------------------------------------------------------------------------
class CPalka // Rotating prograss line
{
public:
	char Get() const
		{
			switch (state)
			{
				case epp_h:  return '-';
				case epp_hv: return '\\';
				case epp_v:  return '|';
				case epp_vh: return '/';
				default: throwe("invalid state");
			}
		};
	void Next()
		{
			switch (state)
			{
				case epp_h:  state = epp_hv;
					break;
				case epp_hv:  state = epp_v;
					break;
				case epp_v:  state = epp_vh;
					break;
				case epp_vh:  state = epp_h;
					break;
			}
		};
	CPalka() { state = epp_h; };
protected:
	EPalcaPosition state;
};
//==============================================================================
class CMainWnd // ������� ����
{
public:						// ������� ������:

	// ������� � ���������� ����
	void Show(HWND hParent);

	// ������ �����������
	CMainWnd();

	// ���������� ������
	~CMainWnd();

protected:					// ���������� ������:

	// ���������� ����
	HWND hWnd;

	// ��������� ������
	CPalka palka;

							// ���������� ������:

	// Allocs (with "new") string with remote host name, or NULL
	char* GetRemoteHost();

	// ����������� ���� ���������
	bool ChEnableWindow(HWND hWnd, bool enable);

	// �������� ����� �������� ���������
	HWND ChGetDlgItem(int id);

	// ����������� ���� ��������� �� id
	bool ChEnableWindowID(int id, bool enable);

	// ������� �� ����
	bool ChIsCheckedID(int id);

	// �������, ��� ������ ���
	static void Running(void* data);

	// ���������� ������ "����������"
	void EnableControlGroup(bool enable);

	// ���������� ������ "��������"
	void EnableRemoteGroup(bool enable, bool labletrue = false);

	// ���������� ��������� ��������� ����������
	void OnInit();

	// ���������������� ������
	void OnRegister();

	// ������� ������
	void OnUnRegister();

	// ��������� ������
	void OnStart();

	// ���������� ������
	void OnStop();

	// Connect to server
	void OnConnect();

	// Disconnect from server
	void OnDisconnect();

	// Send command to server
	void OnCommand();

	// Login into remote machine
	void OnLogin();

	// Logout from remote machine
	void OnLogout();

	// ������� ��������� ����������� ����
	static INT_PTR CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

							// ���������� ���������

	// ��������� ����
	static CPCTSTR caption;
};
//******************************************************************************

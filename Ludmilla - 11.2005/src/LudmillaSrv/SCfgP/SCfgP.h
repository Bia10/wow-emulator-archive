//******************************************************************************
typedef void (*PNotifyFunc)(); // ������ �������
//==============================================================================
class CSCfgP // Service Configuration Program
{
public:						// ������� ������:

	// Gets current module name and installs it
	void InstallSelf();

	// ������������� ������ � �������
	void Install(CPCSTR FileName, char *host = NULL);

	// ��������� ������
	void Begin(void(*notify)(void*), void* data, char *host = NULL);

	// ������������� ������
	void End(void(*notify)(void*), void* data, char *host = NULL);

	// ������� ������
	void Remove(char *host = NULL);

	// ��������� ������ �������
	void GetInfo(bool &exists, bool &running, char *host = NULL);

protected:					// ���������� ���������:

	// ���������� ��� �������
	static CPCTSTR service_name;

	// �������� ��� �������
	static CPCTSTR service_display_name;
};
//******************************************************************************

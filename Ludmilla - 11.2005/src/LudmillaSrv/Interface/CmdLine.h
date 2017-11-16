//******************************************************************************
class CCmdLine // ������ ���������� ������
{
public:						// ������� ������:

	// ���������� ��������� ��������� ������
	void ProcessCmdLine(int argc, char* argv[]);
	void ProcessCmdLine(LPSTR lpCmdLine);

	// �������� ����� � ������
	void ShowReport();

	// �����������
	CCmdLine();

	// ������ ����������
	~CCmdLine();

protected:					// ���������� ������:

	// �������� ������ � ������
	void AddToReport(char *str);

	// �� ���������� �� str �� cmd?
	bool CmpCmd(char *str, char *cmd);

	// ����������� �� str �� lasts � buf
	void GetFirstStr(char *&str, char first, char *lasts, char *buf);

	// ���������� ���� �������� ��������� ������
	void ProcessCmd(char *cmd);

// ���������� ���������� ��������:

	// -i[nstall][:file[@host]]
	void TranslateInstall(char *str);
	void ProcessInstall(char *file, char *host);

	// -b[egin][@host]
	void TranslateBegin(char *str);
	void ProcessBegin(char *host);

	// -e[nd][@host]
	void TranslateEnd(char *str);
	void ProcessEnd(char *host);

	// -r[emove][@host]
	void TranslateRemove(char *str);
	void ProcessRemove(char *host);

// ���������� ��������:

	// -c[ommand]:cmd[@host]
	void TranslateCommand(char *str);
	void ProcessCommand(char *cmd, char *host);

// ������ � �����:

	// -login:[user[:pass]]@host ��� -li
	void TranslateLogin(char *str);
	void ProcessLogin(char *user, char *pass, char *host);

	// -lo[gout]@host
	void TranslateLogout(char *str);
	void ProcessLogout(char *host);

// ��������������� �������:

	// -keys ��� -k
	void TranslateKeys(char *str);

	// -help ��� -h ��� -?
	void TranslateHelp(char *str);

	void TranslateQuiet(char *str);

							// ���������� ������:

	// ����� � ������
	char * report;

};
//==============================================================================
extern CCmdLine CmdLine;
//******************************************************************************

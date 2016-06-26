#include "stdafx.h"
#include "Synthesizer.h"


Synthesizer::Synthesizer()
{
}


Synthesizer::~Synthesizer()
{
}
bool Synthesizer::runTool(std::wstring FullPathToExe, std::wstring Parameters, size_t SecondsToWait) {
	SECURITY_ATTRIBUTES sa;
	printf("\n->Start of parent execution.\n");
	// Set the bInheritHandle flag so pipe handles are inherited. 
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;
	// Create a pipe for the child process's STDERR. 
	if (!CreatePipe(&g_hChildStd_ERR_Rd, &g_hChildStd_ERR_Wr, &sa, 0)) {
		exit(1);
	}
	// Ensure the read handle to the pipe for STDERR is not inherited.
	if (!SetHandleInformation(g_hChildStd_ERR_Rd, HANDLE_FLAG_INHERIT, 0)) {
		exit(1);
	}
	// Create a pipe for the child process's STDOUT. 
	if (!CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &sa, 0)) {
		exit(1);
	}
	// Ensure the read handle to the pipe for STDOUT is not inherited
	if (!SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0)) {
		exit(1);
	}
	// Create the child process. 
	PROCESS_INFORMATION piProcInfo = CreateChildProcess(FullPathToExe, Parameters, SecondsToWait);

	// Read from pipe that is the standard output for child process. 
	printf("\n->Contents of child process STDOUT:\n\n");
	ReadFromPipe(piProcInfo);

	printf("\n->End of parent execution.\n");

	// The remaining open handles are cleaned up when this process terminates. 
	// To avoid resource leaks in a larger application, 
	//   close handles explicitly.
	return 0;
}

// Create a child process that uses the previously created pipes
//  for STDERR and STDOUT.
PROCESS_INFORMATION Synthesizer::CreateChildProcess(std::wstring FullPathToExe, std::wstring Parameters, size_t SecondsToWait) {
	// Set the text I want to run
	size_t iMyCounter = 0, iReturnVal = 0, iPos = 0;
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;
	bool bSuccess = FALSE;

	// Set up members of the PROCESS_INFORMATION structure. 
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	// Set up members of the STARTUPINFO structure. 
	// This structure specifies the STDERR and STDOUT handles for redirection.
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	siStartInfo.hStdError = g_hChildStd_ERR_Wr;
	siStartInfo.hStdOutput = g_hChildStd_OUT_Wr;
	siStartInfo.dwFlags |= STARTF_USESTDHANDLES;


	//========= Modify Parameters ========//
	std::wstring sTempStr = L"";

	/* - NOTE - You should check here to see if the exe even exists */

	/* Add a space to the beginning of the Parameters */
	if (Parameters.size() != 0)
	{
		if (Parameters[0] != L' ')
		{
			Parameters.insert(0, L" ");
		}
	}

	/* The first parameter needs to be the exe itself */
	sTempStr = FullPathToExe;
	iPos = sTempStr.find_last_of(L"\\");
	sTempStr.erase(0, iPos + 1);

	Parameters = sTempStr.append(Parameters);

	/* CreateProcessW can modify Parameters thus we allocate needed memory */
	wchar_t * pwszParam = new wchar_t[Parameters.size() + 1];
	if (pwszParam == 0)
	{
		exit(1);
	}
	const wchar_t* pchrTemp = Parameters.c_str();
	wcscpy_s(pwszParam, Parameters.size() + 1, pchrTemp);
	//====================================//

	bSuccess = CreateProcessW(
		FullPathToExe.c_str(),
		pwszParam,
		0,
		0,
		false,
		CREATE_DEFAULT_ERROR_MODE,
		0,
		pathToExecutable.c_str(),
		&siStartInfo,
		&piProcInfo);

	CloseHandle(g_hChildStd_ERR_Wr);
	CloseHandle(g_hChildStd_OUT_Wr);
	// If an error occurs, exit the application. 
	if (!bSuccess) {
		exit(1);
	}
	return piProcInfo;
}

// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT. 
// Stop when there is no more data. 
void Synthesizer::ReadFromPipe(PROCESS_INFORMATION piProcInfo) {
	DWORD dwRead;
	CHAR chBuf[BUFSIZE];
	bool bSuccess = FALSE;
	std::string out = "", err = "";
	for (;;) {
		bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) break;

		std::string s(chBuf, dwRead);
		out += s;
	}
	dwRead = 0;
	for (;;) {
		bSuccess = ReadFile(g_hChildStd_ERR_Rd, chBuf, BUFSIZE, &dwRead, NULL);
		if (!bSuccess || dwRead == 0) break;

		std::string s(chBuf, dwRead);
		err += s;

	}
	std::cout << "stdout:" << out << std::endl;
	std::cout << "stderr:" << err << std::endl;
}
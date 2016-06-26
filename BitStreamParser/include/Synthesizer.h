#pragma once
#include <string>
#include <iostream>
#include <windows.h> 
#include <stdio.h>
#pragma warning( disable : 4800 ) // stupid warning about bool
#define BUFSIZE 4096

class Synthesizer
{
public:
	Synthesizer();
	~Synthesizer();
	bool runTool(std::wstring FullPathToExe, std::wstring Parameters, size_t SecondsToWait);
private:
	HANDLE g_hChildStd_OUT_Rd = NULL;
	HANDLE g_hChildStd_OUT_Wr = NULL;
	HANDLE g_hChildStd_ERR_Rd = NULL;
	HANDLE g_hChildStd_ERR_Wr = NULL;
	std::wstring pathToExecutable = L"C:\\Users\\Nick\\Desktop\\NickTop\\HomeWork\\MASc\\FPGAAutomationImplementation\\BitStreamParser\\BitStreamParser\\Xilinx\\SingleItemTest\\";;

	PROCESS_INFORMATION CreateChildProcess(std::wstring FullPathToExe, std::wstring Parameters, size_t SecondsToWait);
	void ReadFromPipe(PROCESS_INFORMATION piProcInfo);
};


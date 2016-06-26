// BitStreamParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <iostream>
#include <fstream>
#include <windows.h>
#include <AccCtrl.h>
#include <Aclapi.h>
#include <strsafe.h>
#include <set>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <boost/filesystem.hpp>
#include "Synthesizer.h"
#include "BitStreamAnalyzer.h"

//Command Line : sch2hdl -batch C:/Users/Nick/Desktop/NickTop/HomeWork/MASc/FPGAAutomationImplementation/BitStreamParser/BitStreamParser/Xilinx/SingleItemTest/sch2HdlBatchFile
//Command Line : xst -ifn C:/Users/Nick/Desktop/NickTop/HomeWork/MASc/FPGAAutomationImplementation/BitStreamParser/BitStreamParser/Xilinx/SingleItemTest/item.xst -ofn C:/Users/Nick/Desktop/NickTop/HomeWork/MASc/FPGAAutomationImplementation/BitStreamParser/BitStreamParser/Xilinx/SingleItemTest/item.syr
//Command Line : ngdbuild -dd _ngo -nt timestamp -uc item.ucf -p xa3s100e-vqg100-4 item.ngc item.ngd
//Command Line : C : \Xilinx\14.7\ISE_DS\ISE\bin\nt64\unwrapped\ngdbuild.exe - dd _ngo - nt timestamp - uc item.ucf - p xa3s100e - vqg100 - 4 item.ngc item.ngd
//Command Line : map - p xa3s100e - vqg100 - 4 - cm area - ir off - pr off - c 100 - o item_map.ncd item.ngd item.pcf
//Command Line : par - w - ol high - t 1 item_map.ncd item.ncd item.pcf
//Command Line : trce - v 3 - s 4 - n 3 - fastpaths - xml item.twx item.ncd - o item.twr item.pcf - ucf item.ucf
//Command Line : bitgen - f item.ut item.ncd

std::string path = "C:\\Users\\Nick\\Desktop\\NickTop\\HomeWork\\MASc\\FPGAAutomationImplementation\\BitStreamParser\\BitStreamParser\\Xilinx\\SingleItemTest\\";
std::wstring wPath = L"C:\\Users\\Nick\\Desktop\\NickTop\\HomeWork\\MASc\\FPGAAutomationImplementation\\BitStreamParser\\BitStreamParser\\Xilinx\\SingleItemTest\\";;


void convertSchematicToHDL() {
	printf("Executing sch2hdl\n");
	system(("sch2hdl -batch " + path + "sch2HdlBatchFile").c_str());
}
size_t ExecuteProcess(std::wstring FullPathToExe, std::wstring Parameters, size_t SecondsToWait)
{
	size_t iMyCounter = 0, iReturnVal = 0, iPos = 0;
	DWORD dwExitCode = 0;
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
		return 1;
	}
	const wchar_t* pchrTemp = Parameters.c_str();
	wcscpy_s(pwszParam, Parameters.size() + 1, pchrTemp);

	/* CreateProcess API initialization */
	STARTUPINFOW siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

	if (CreateProcessW(
		FullPathToExe.c_str(),
		pwszParam,
		0,
		0,
		false,
		CREATE_DEFAULT_ERROR_MODE,
		0,
		wPath.c_str(),
		&siStartupInfo,
		&piProcessInfo) != false)
	{
		/* Watch the process. */
		dwExitCode = WaitForSingleObject(piProcessInfo.hProcess, (SecondsToWait * 1000));
	}
	else
	{
		/* CreateProcess failed */
		iReturnVal = GetLastError();
	}

	/* Free memory */
	delete[]pwszParam;
	pwszParam = 0;

	/* Release handles */
	CloseHandle(piProcessInfo.hProcess);
	CloseHandle(piProcessInfo.hThread);

	return iReturnVal;
}

void runXilinxTool(std::wstring FullPathToExe, std::wstring Parameters, size_t SecondsToWait) {
	Synthesizer syn;
	syn.runTool(FullPathToExe, Parameters, SecondsToWait);
}
void makeDirectories() {
	std::string outputFolder = path + "xst";
	CreateDirectoryA(outputFolder.c_str(), NULL);
	outputFolder = path + "xst/projnav.tmp";
	CreateDirectoryA(outputFolder.c_str(), NULL);
}
void makeInitFiles() {
	std::ofstream prjFile;
	prjFile.open(path + "item.prj");
	prjFile << "vhdl work \"item.vhf\"";
	prjFile.close();

	std::ofstream syrFile;
	syrFile.open(path + "item.syr");
	syrFile.close();

	std::ofstream xstFile;
	xstFile.open(path + "item.xst");
	xstFile << "set -tmpdir \"xst/projnav.tmp\"\n";
	xstFile << "set -xsthdpdir \"xst\"\n";
	xstFile << "run\n";
	xstFile << ("-ifn " + path + "item.prj\n").c_str();
	xstFile << "-ifmt mixed\n";
	xstFile << "-ofn item\n";
	xstFile << "-ofmt NGC\n";
	xstFile << "-p xa3s100e-4-vqg100\n";
	xstFile << "-top item\n";
	xstFile << "-opt_mode Speed\n";
	xstFile << "-opt_level 1\n";
	xstFile << "-iuc NO\n";
	xstFile << "-keep_hierarchy No\n";
	xstFile << "-netlist_hierarchy As_Optimized\n";
	xstFile << "-rtlview Yes\n";
	xstFile << "-glob_opt AllClockNets\n";
	xstFile << "-read_cores YES\n";
	xstFile << "-write_timing_constraints NO\n";
	xstFile << "-cross_clock_analysis NO\n";
	xstFile << "-hierarchy_separator /\n";
	xstFile << "-bus_delimiter <>\n";
	xstFile << "-case Maintain\n";
	xstFile << "-slice_utilization_ratio 100\n";
	xstFile << "-bram_utilization_ratio 100\n";
	xstFile << "-verilog2001 YES\n";
	xstFile << "-fsm_extract YES -fsm_encoding Auto\n";
	xstFile << "-safe_implementation No\n";
	xstFile << "-fsm_style LUT\n";
	xstFile << "-ram_extract Yes\n";
	xstFile << "-ram_style Auto\n";
	xstFile << "-rom_extract Yes\n";
	xstFile << "-mux_style Auto\n";
	xstFile << "-decoder_extract YES\n";
	xstFile << "-priority_extract Yes\n";
	xstFile << "-shreg_extract YES\n";
	xstFile << "-shift_extract YES\n";
	xstFile << "-xor_collapse YES\n";
	xstFile << "-rom_style Auto\n";
	xstFile << "-auto_bram_packing NO\n";
	xstFile << "-mux_extract Yes\n";
	xstFile << "-resource_sharing YES\n";
	xstFile << "-async_to_sync NO\n";
	xstFile << "-mult_style Auto\n";
	xstFile << "-iobuf YES\n";
	xstFile << "-max_fanout 100000\n";
	xstFile << "-bufg 24\n";
	xstFile << "-register_duplication YES\n";
	xstFile << "-register_balancing No\n";
	xstFile << "-slice_packing YES\n";
	xstFile << "-optimize_primitives NO\n";
	xstFile << "-use_clock_enable Yes\n";
	xstFile << "-use_sync_set Yes\n";
	xstFile << "-use_sync_reset Yes\n";
	xstFile << "-iob Auto\n";
	xstFile << "-equivalent_register_removal YES\n";
	xstFile << "-slice_utilization_ratio_maxmargin 5\n";
	xstFile.close();

	std::ofstream utFile;
	utFile.open(path + "item.ut");
	utFile << "-w\n";
	utFile << "-g DebugBitstream:No\n";
	utFile << "-g Binary:yes\n";
	utFile << "-g CRC:Enable\n";
	utFile << "-g ConfigRate:1\n";
	utFile << "-g ProgPin:PullUp\n";
	utFile << "-g DonePin:PullUp\n";
	utFile << "-g TckPin:PullUp\n";
	utFile << "-g TdiPin:PullUp\n";
	utFile << "-g TdoPin:PullUp\n";
	utFile << "-g TmsPin:PullUp\n";
	utFile << "-g UnusedPin:PullDown\n";
	utFile << "-g UserID:0xFFFFFFFF\n";
	utFile << "-g DCMShutdown:Disable\n";
	utFile << "-g StartUpClk:CClk\n";
	utFile << "-g DONE_cycle:4\n";
	utFile << "-g GTS_cycle:5\n";
	utFile << "-g GWE_cycle:6\n";
	utFile << "-g LCK_cycle:NoWait\n";
	utFile << "-g Security:None\n";
	utFile << "-g DonePipe:Yes\n";
	utFile << "-g DriveDone:No\n";
	utFile.close();
}

void deleteResources(std::set<std::string> files) {
	for (std::set<std::string>::iterator it = files.begin(); it != files.end(); ++it) {
		boost::filesystem::remove_all((path + *it).c_str());
	}
}
std::set<std::string> listOfFiles(std::string fileName) {
	system(("dir Xilinx\\SingleItemTest /b > " + fileName).c_str());
	std::ifstream tempFile;
	tempFile.open(fileName);
	std::string X;
	std::set<std::string> fileNameSet;
	if (tempFile.is_open()) {
		while (std::getline(tempFile, X)) {
			fileNameSet.insert(X);
		}
	}
	else {
		std::cerr << "Failed to open " + fileName + "\n";
		exit(0);
	}
	return fileNameSet;
}
std::set<std::string> setDifferences(std::set<std::string> a, std::set<std::string> b) {
	using namespace std;
	set<string> result;
	set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(result, result.begin()));
	return result;
}
void incrementUCF() {
	std::set<std::string> files;
	files.insert("item.ucf");
	deleteResources(files);
	std::ofstream ucfFile;
	ucfFile.open(path + "item.ucf");
	int xValue = 0, yValue = 43;
	ucfFile << "INST \"XLXI_11\" BEL = F;\n";
	ucfFile << "INST \"XLXI_11\" LOC = SLICE_X" << xValue << "Y" << yValue <<";";
	ucfFile.close();
}
bool synthesizeDesign() {
	convertSchematicToHDL();
	std::wstring xstPath = L"C:\\Xilinx\\14.7\\ISE_DS\\ISE\\bin\\nt\\xst.exe";
	std::wstring ngdPath = L"C:\\Xilinx\\14.7\\ISE_DS\\ISE\\bin\\nt\\ngdbuild.exe";
	std::wstring mapPath = L"C:\\Xilinx\\14.7\\ISE_DS\\ISE\\bin\\nt\\map.exe";
	std::wstring trcePath = L"C:\\Xilinx\\14.7\\ISE_DS\\ISE\\bin\\nt\\trce.exe";
	std::wstring parPath = L"C:\\Xilinx\\14.7\\ISE_DS\\ISE\\bin\\nt\\par.exe";
	std::wstring bitgenPath = L"C:\\Xilinx\\14.7\\ISE_DS\\ISE\\bin\\nt\\bitgen.exe";
	std::wstring xstArgs = L"-ifn C:/Users/Nick/Desktop/NickTop/HomeWork/MASc/FPGAAutomationImplementation/BitStreamParser/BitStreamParser/Xilinx/SingleItemTest/item.xst -ofn C:/Users/Nick/Desktop/NickTop/HomeWork/MASc/FPGAAutomationImplementation/BitStreamParser/BitStreamParser/Xilinx/SingleItemTest/item.syr";
	std::wstring ngdArgs = L"-dd _ngo -nt timestamp -uc item.ucf -p xa3s100e-vqg100-4 item.ngc item.ngd";
	std::wstring mapArgs = L"-p xa3s100e-vqg100-4 -cm area -ir off -pr off -c 100 -o item_map.ncd item.ngd item.pcf";
	std::wstring parArgs = L"-ol high -t 1 item_map.ncd item.ncd item.pcf";
	std::wstring trceArgs = L"-v 3 -s 4 -n 3 -fastpaths -xml item.twx item.ncd -o item.twr item.pcf -ucf item.ucf";
	std::wstring bitgenArgs = L"-f item.ut item.ncd";
	ExecuteProcess(xstPath, xstArgs, 10);
	ExecuteProcess(ngdPath, ngdArgs, 10);
	ExecuteProcess(mapPath, mapArgs, 10);
	ExecuteProcess(parPath, parArgs, 10);
	ExecuteProcess(trcePath, trceArgs, 10);
	ExecuteProcess(bitgenPath, bitgenArgs, 10);
	return true;
}
void readBitFile() {
	BitStreamAnalyzer bitAn;
	bitAn.readBitFile(path + "item.bin");
}
int main()
{
	printf("Checking if processor is available...");
	if (system(NULL)) puts("Ok");
	else exit(EXIT_FAILURE);
	std::set<std::string> initialSet = listOfFiles("initialFiles.txt");
	makeDirectories();
	makeInitFiles();
	incrementUCF();
	synthesizeDesign();
	std::set<std::string> afterNGD = listOfFiles("finishedFileList.txt");
	std::set<std::string> result;
	readBitFile();
	result = setDifferences(initialSet, afterNGD);
	deleteResources(result);
	return 0;
}

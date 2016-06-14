// BitStreamParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <iostream>
#include <fstream>
#include <sddl.h>
#include <windows.h>
#include <AccCtrl.h>
#include <Aclapi.h>

//Command Line : sch2hdl -batch C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/sch2HdlBatchFile
//Command Line : xst -ifn C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.xst -ofn C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.syr
//Command Line : ngdbuild - dd _ngo - nt timestamp - uc item.ucf - p xa3s100e - vqg100 - 4 "item.ngc" item.ngd
//Command Line : C : \Xilinx\14.7\ISE_DS\ISE\bin\nt64\unwrapped\ngdbuild.exe - dd _ngo - nt timestamp - uc item.ucf - p xa3s100e - vqg100 - 4 item.ngc item.ngd
//Command Line : map - p xa3s100e - vqg100 - 4 - cm area - ir off - pr off - c 100 - o item_map.ncd item.ngd item.pcf
//Command Line : par - w - ol high - t 1 item_map.ncd item.ncd item.pcf
//Command Line : trce - v 3 - s 4 - n 3 - fastpaths - xml item.twx item.ncd - o item.twr item.pcf - ucf item.ucf
//Command Line : bitgen - f item.ut item.ncd

void convertSchematicToHDL() {
	printf("Executing sch2hdl\n");
	system("sch2hdl -batch C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/sch2HdlBatchFile");
}
void CreateDirectoryWithUserFullControlACL(std::string path)
{
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
	PSID everyone_sid = NULL;
	AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID,
		0, 0, 0, 0, 0, 0, 0, &everyone_sid);

	EXPLICIT_ACCESS ea;
	ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
	ea.grfAccessPermissions = SPECIFIC_RIGHTS_ALL | STANDARD_RIGHTS_ALL;
	ea.grfAccessMode = SET_ACCESS;
	ea.grfInheritance = NO_INHERITANCE;
	ea.Trustee.TrusteeForm = TRUSTEE_IS_SID;
	ea.Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
	ea.Trustee.ptstrName = (LPWSTR)everyone_sid;

	PACL acl = NULL;
	SetEntriesInAcl(1, &ea, NULL, &acl);

	PSECURITY_DESCRIPTOR sd = (PSECURITY_DESCRIPTOR)LocalAlloc(LPTR,
		SECURITY_DESCRIPTOR_MIN_LENGTH);
	InitializeSecurityDescriptor(sd, SECURITY_DESCRIPTOR_REVISION);
	SetSecurityDescriptorDacl(sd, TRUE, acl, FALSE);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = sd;
	sa.bInheritHandle = FALSE;

	CreateDirectoryA(path.c_str(), &sa);

	FreeSid(everyone_sid);
	LocalFree(sd);
	LocalFree(acl);
}
void callXST() {
	printf("\n\nExecuting Synthesis\n");
	std::string outputFolder = "C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/xst";
	CreateDirectoryWithUserFullControlACL(outputFolder);
	outputFolder = "C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/xst/projnav.tmp";
	CreateDirectoryWithUserFullControlACL(outputFolder);
	//CreateDirectoryA((outputFolder + "xst/").c_str(), &sa);
	//CreateDirectoryA((outputFolder + "xst/projnav.tmp").c_str(), &sa);
	system("xst -ifn C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.xst -ofn C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.syr");
}
void makeInitFiles() {
	std::ofstream prjFile;
	prjFile.open("C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.prj");
	prjFile << "vhdl work \"item.vhf\"";
	prjFile.close();

	std::ofstream syrFile;
	syrFile.open("C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.syr");
	syrFile.close();

	std::ofstream xstFile;
	xstFile.open("C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.xst");
	xstFile << "set -tmpdir \"xst/projnav.tmp\"\n";
	xstFile << "set -xsthdpdir \"xst\"\n";
	xstFile << "run\n";
	xstFile << "-ifn item.prj\n";
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
}
void deleteFiles() {
	std::remove("C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.prj");
	std::remove("C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.syr");
	std::remove("C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/item.xst");
}
int main()
{
	printf("Checking if processor is available...");
	if (system(NULL)) puts("Ok");
	else exit(EXIT_FAILURE);
	deleteFiles();
	makeInitFiles();
	convertSchematicToHDL();
	callXST();
	return 0;
}


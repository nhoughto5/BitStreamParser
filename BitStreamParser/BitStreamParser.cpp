// BitStreamParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

//Command Line : sch2hdl -batch C:/Users/Nick/Documents/XilinxProjects/SingleItemTest/sch2HdlBatchFile
//Command Line : xst - ifn "C:/Users/Nick/Documents/Xilinx Projects/SingleItemTest/item.xst" - ofn "C:/Users/Nick/Documents/Xilinx Projects/SingleItemTest/item.syr"
//Command Line : ngdbuild - dd _ngo - nt timestamp - uc item.ucf - p xa3s100e - vqg100 - 4 "item.ngc" item.ngd
//Command Line : C : \Xilinx\14.7\ISE_DS\ISE\bin\nt64\unwrapped\ngdbuild.exe - dd _ngo - nt timestamp - uc item.ucf - p xa3s100e - vqg100 - 4 item.ngc item.ngd
//Command Line : map - p xa3s100e - vqg100 - 4 - cm area - ir off - pr off - c 100 - o item_map.ncd item.ngd item.pcf
//Command Line : par - w - ol high - t 1 item_map.ncd item.ncd item.pcf
//Command Line : trce - v 3 - s 4 - n 3 - fastpaths - xml item.twx item.ncd - o item.twr item.pcf - ucf item.ucf
//Command Line : bitgen - f item.ut item.ncd



void callXST() {
	printf("Executing command XST -h...\n");

	system("xst -h");
}

int main()
{
	int i;
	printf("Checking if processor is available...");
	if (system(NULL)) puts("Ok");
	else exit(EXIT_FAILURE);
	callXST();
	return 0;
}


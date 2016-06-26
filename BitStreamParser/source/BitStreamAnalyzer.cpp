#include "stdafx.h"
#include <stdio.h>
#include <ctype.h>
#include <iomanip>
#include <unordered_map>
#include "CoutRedirect.h"
#include "BitStreamAnalyzer.h"
#define BUFFER_CAPACITY 512

BitStreamAnalyzer::BitStreamAnalyzer()
{
}


BitStreamAnalyzer::~BitStreamAnalyzer()
{
}

void BitStreamAnalyzer::readBitFile(std::string binFilePath) {
	std::clock_t    start;
	start = std::clock();
	using namespace std;
	const char * inputFile = binFilePath.c_str();
	unsigned char x;
	std::ifstream input(inputFile, std::ios::binary);
	input >> std::noskipws;
	std::stringstream buffer;

	//Read entire hex file into buffer
	while (input >> x) {
		buffer << std::hex << std::setw(2) << std::setfill('0')	<< (int)x;
	}
	std::string content = buffer.str();
	int strL = content.length();
	for (int i = 0; i < strL; i += 2) {
		hexValues.push_back(content.substr(i,2));
	}
	buffer.clear();
	content.clear();
	return;
}

void binary_to_string(const unsigned char* source, unsigned int length, std::string& destination)
{
	destination.clear();
	for (unsigned int i = 0; i < length; i++)
	{
		char digit[3];
		sprintf(digit, "%02x", source[i]);
		destination.append(digit);
	}
}
#include "stdafx.h"
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include "CoutRedirect.h"
#include "BitStreamAnalyzer.h"
#include "enums.h"
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
	unsigned char x;
	std::ifstream input(binFilePath.c_str(), std::ios::binary);
	input >> std::noskipws;
	std::stringstream buffer;

	//Read entire hex file into buffer
	while (input >> x) {
		buffer << std::hex << std::setw(2) << std::setfill('0')	<< (int)x;
	}
	std::string content = buffer.str();
	int strL = content.length();

	//Split file into vector of bytes
	for (int i = 0; i < strL; i += 2) {
		hexByteValues.push_back(content.substr(i,2));
	}
	buffer.clear();
	content.clear();
	return;
}

lutOffsetResponse BitStreamAnalyzer::getByteOffSet() {
	std::vector<int> results;
	int numBytesKeyword = 4;
	std::string temp, stringRet;

	for (int i = 0; i < hexByteValues.size() - numBytesKeyword; ++i) {
		for (int j = 0; j < numBytesKeyword; ++j) {
			temp += hexByteValues[i + j];
		}
		if (boost::iequals(temp, LUT_Hex_Codes[0])) {
			results.push_back(i);
			stringRet = temp;
		}
		else if (boost::iequals(temp, LUT_Hex_Codes[1])) {
			results.push_back(i);
			stringRet = temp;
		}
		else if (boost::iequals(temp, LUT_Hex_Codes[2])) {
			results.push_back(i);
			stringRet = temp;
		}
		else if (boost::iequals(temp, LUT_Hex_Codes[3])) {
			results.push_back(i);
			stringRet = temp;
		}
		else if (boost::iequals(temp, LUT_Hex_Codes[4])) {
			results.push_back(i);
			stringRet = temp;
		}
		else if (boost::iequals(temp, LUT_Hex_Codes[5])) {
			results.push_back(i);
			stringRet = temp;
		}
		else if (boost::iequals(temp, LUT_Hex_Codes[6])) {
			results.push_back(i);
			stringRet = temp;
		}
		else {
			stringRet = "NA";
		}
		temp.clear();
	}

	int intRet;
	if (results.size() != 1) {
		intRet = -1;
	}
	else intRet = results[0];
	lutOffsetResponse ret;
	ret.offset = intRet;
	ret.hexCode = stringRet;
	return ret;
}
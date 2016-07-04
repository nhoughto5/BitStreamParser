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
		if (boost::iequals(temp, "FFF0FFFF")) {
			results.push_back(i);
			stringRet = "FF F0 FF FF";
		}
		else if (boost::iequals(temp, "FFFFFAFA")) {
			results.push_back(i);
			stringRet = "FF FF FA FA";
		}
		else if (boost::iequals(temp, "FAFAFFFF")) {
			results.push_back(i);
			stringRet = "FA FA FF FF";
		}
		else if (boost::iequals(temp, "FFFFFFCC")) {
			results.push_back(i);
			stringRet = "FF FF FF CC";
		}
		else if (boost::iequals(temp, "FFCCFFFF")) {
			results.push_back(i);
			stringRet = "FF CC FF FF";
		}
		else if (boost::iequals(temp, "FCFCFFFF")) {
			results.push_back(i);
			stringRet = "FC FC FF FF";
		}
		else if (boost::iequals(temp, "FFFFFCFC")) {
			results.push_back(i);
			stringRet = "FF FF FC FC";
		}
		else if (boost::iequals(temp, "FFFFEEEE")) {
			results.push_back(i);
			stringRet = "FF FF EE EE";
		}
		else if (boost::iequals(temp, "EEEEFFFF")) {
			results.push_back(i);
			stringRet = "EE EE FF FF";
		}
		else if (boost::iequals(temp, "EEEEFFFF")) {
			results.push_back(i);
			stringRet = "FF FF FF F0";
		}
		else {
			
		}
		temp.clear();
	}

	int intRet;
	if (results.size() != 1) {
		intRet = -1;
		stringRet = "NA";
	}
	else intRet = results[0];
	lutOffsetResponse ret;
	ret.offset = intRet;
	ret.hexCode = stringRet;
	return ret;
}
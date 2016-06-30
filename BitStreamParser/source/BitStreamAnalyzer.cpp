#include "stdafx.h"
#include <stdio.h>
#include <iomanip>
#include <algorithm>
#include "CoutRedirect.h"
#include "BitStreamAnalyzer.h"
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

	//Split file into vector of bytes
	for (int i = 0; i < strL; i += 2) {
		hexByteValues.push_back(content.substr(i,2));
	}
	buffer.clear();
	content.clear();
	return;
}

std::vector<int> BitStreamAnalyzer::getByteOffSet(std::string keyWord) {
	//std::remove_if(keyWord.begin(), keyWord.end(), isspace);
	keyWord.erase(std::remove(keyWord.begin(), keyWord.end(), ' '), keyWord.end());
	int keyWordLength = keyWord.length();
	std::vector<int> results;
	if (keyWordLength % 2 != 0) {
		std::cerr << "BitFile Search Keyword is not a multiple of a bytes\n";
		exit(0);
	}
	int numBytesKeyword = keyWordLength / 2;
	std::string temp;
	for (int i = 0; i < hexByteValues.size() - numBytesKeyword; ++i) {
		for (int j = 0; j < numBytesKeyword; ++j) {
			temp += hexByteValues[i + j];
		}
		if (boost::iequals(temp, keyWord)) {
			results.push_back(i);
		}
		temp.clear();
	}
	return results;
}
#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <boost/algorithm/string.hpp>
class BitStreamAnalyzer
{
public:
	BitStreamAnalyzer();
	~BitStreamAnalyzer();

	void readBitFile(std::string binFilePath);
	std::vector<int> getByteOffSet(std::string keyWord);
private:
	std::vector<std::string> hexByteValues;
};


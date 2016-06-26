#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>
class BitStreamAnalyzer
{
public:
	BitStreamAnalyzer();
	~BitStreamAnalyzer();

	void readBitFile(std::string binFilePath);
private:
	std::vector<std::string> hexValues;
};


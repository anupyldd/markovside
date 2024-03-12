#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <random>
#include <istream>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cctype>

class MarkovSide
{
public:

	MarkovSide() = default;
	MarkovSide(const std::string& fileName, unsigned int nGram);

	void Generate(unsigned int length);
	void GenerateFrom(unsigned int length, const std::wstring& prompt);
	void SaveToFile();
	void LoadFile(const std::string& fileName);	// loads in a new file to replace current
	void SetNGram(unsigned int inNGram);

private:

	void ReadFile(const std::string& fileName);
	void CleanText();
	void CreateChain();
	std::string ChooseWord();

private:

	unsigned int nGram = 0;
	std::vector<std::wstring> fileContents;
	std::unordered_map<std::wstring, std::unordered_map<std::wstring, float>> dict;
	std::wstring generatedTxt;
};


#include "MarkovSide.h"

MarkovSide::MarkovSide(const std::string& fileName, unsigned int nGram)
	: nGram(nGram)
{
	ReadFile(fileName);
	CleanText();
	CreateChain();
}

void MarkovSide::Generate(unsigned int length)
{
	std::wstring text,
				 curr,	// add space since all dict entries are with spaces
				 next;
	std::random_device rd;
	std::mt19937 rng(rd());

	std::uniform_int_distribution<int> d(0, dict.size() - 1);
	auto it = dict.begin();
	std::advance(it, d(rng));
	curr = it->first;
	if (!curr.empty()) curr.pop_back();	// to remove extra space in the end

	GenerateFrom(length, curr);
}

void MarkovSide::GenerateFrom(unsigned int length, const std::wstring& prompt)
{
	std::wstring text, 
				 curr = prompt + L" ",	// add space since all dict entries are with spaces
				 next;
	text += curr;

	std::random_device rd;
	std::mt19937 rng(rd());
	
	for (size_t i = 0; i < length; i++)
	{
		size_t size = dict.at(curr).size();
		std::vector<std::wstring> paths;
		paths.reserve(size);
		for (auto const& [key, val] : dict.at(curr))
		{
			paths.push_back(key);
		}
		std::uniform_int_distribution<int> distr(0, paths.size() - 1);
		next = paths.at(distr(rng));
		text += next;
		curr = next;
	}
	text += L'\n';
	generatedTxt = text;
	std::wcout << generatedTxt << '\n';
}

void MarkovSide::SaveToFile()
{
}

void MarkovSide::LoadFile(const std::string& fileName)
{
}

void MarkovSide::SetNGram(unsigned int inNGram)
{
	nGram = inNGram;
	CreateChain();
}

void MarkovSide::ReadFile(const std::string& fileName)
{
	std::wifstream file(fileName);
	file.imbue(std::locale("en_US.UTF8"));
	std::wstring word;
	while (file >> word)
	{
		fileContents.push_back(word);
		word.clear();
	}
}

void MarkovSide::CleanText()
{
	std::wstring punct = L",.\"\'!@#$%^&*(){}?/;`~:<>+=-\\";
	for (std::wstring& word : fileContents)
	{
		//removing punctuation
		word.erase(std::remove_if(word.begin(), word.end(), [punct](auto c) { return punct.find_first_of(c) != punct.npos; }), word.end());
		//everything to lowercase
		std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });
	}
}

void MarkovSide::CreateChain()
{
	std::wstring curr, next;
	size_t size = fileContents.size();
	for (size_t i = 0; i < size - nGram - 1; i++)
	{
		size_t len = nGram + i;
		for (size_t j = i; j < len; j++)
		{
			curr += fileContents[j] + L" ";
			next += fileContents[j + nGram] + L" ";
		}
		if (dict.contains(curr))
		{
			dict[curr][next] = 1;
		}
		else
		{
			if (dict[curr].contains(next))
			{
				dict[curr][next]++;
			}
			else
			{
				dict[curr][next] = 1;
			}
		}
		
		curr.clear();
		next.clear();
	}
	/*for (auto& [key, val] : dict)
	{
		for (auto& [k, v] : val)
		{
			v /= dict.at(key).size();
		}
	}*/

	//output the whole dict
	for (auto const& [key, val] : dict)
	{
		for (auto const& [k, v] : val)
		{
			//std::wcout << key << L" : " << k << L" - " << v << '\n';
		}
	}
}

std::string MarkovSide::ChooseWord()
{
	return std::string();
}

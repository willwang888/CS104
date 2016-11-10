#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

int main(int argc, char* argv[])
{
	std::ifstream inputDictionaryFile{ argv[1] };
	std::vector<std::string> wordVector;
	std::string word;
	
	while(inputDictionaryFile >> word)
	{
		if(word != "" && !isdigit(word[0]))
		wordVector.push_back(word);
	}
	inputDictionaryFile.close();

	std::ofstream outputDictionaryFile{ argv[1] };
	for(const auto& word : wordVector)
	{
		outputDictionaryFile << word << std::endl;
	}
	outputDictionaryFile.close();

	return 0;
}
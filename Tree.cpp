#include "Tree.h"

Tree::Tree() 
{
	root = new Node();
}

Tree::~Tree()
{
	delete root;
}

void Tree::build(std::string inputString)
{
	inputStr = inputString;

	root->subscribe(this);

	std::string output = strBlank;

	output = root->build(inputString);

	if (output != strBlank)
	{
		update(strTooManyArgsMsg);
	}
}

double Tree::evaluate(std::string inputVariableValues)
{
	std::vector<std::string> vectorOfVariables = findAllVariables();
	std::vector<int> vectorOfVariableValues;
	std::string readString = strBlank;
	std::string remainingString = inputVariableValues;
	int indexOfFirstSpace = 0;

	while (remainingString.length() > 0)
	{
		indexOfFirstSpace = remainingString.find_first_of(strSpace);

		while (indexOfFirstSpace == 0)
		{
			if (inputVariableValues.length() > 1)
			{
				inputVariableValues = inputVariableValues.substr(1);
			}
			else
			{
				inputVariableValues = strBlank;
			}

			indexOfFirstSpace = inputVariableValues.find_first_of(strSpace);
		}

		if (indexOfFirstSpace != std::string::npos)
		{
			readString = remainingString.substr(0, indexOfFirstSpace);
			remainingString = remainingString.substr(indexOfFirstSpace + 1);
		}
		else
		{
			readString = remainingString;
			remainingString = strBlank;
		}

		int arrayOfCharactersLength = inputVariableValues.length();
		int* arrayOfCharacters = new int[arrayOfCharactersLength];
		int actualIndexOfParsedSymbols = 0;
		char currentlyParsedSymbol = charSpace;

		for (int i = 0; i < readString.length(); i++)
		{
			currentlyParsedSymbol = readString[i];

			if (currentlyParsedSymbol >= char0 && currentlyParsedSymbol <= char9)
			{
				arrayOfCharacters[actualIndexOfParsedSymbols] = currentlyParsedSymbol;
				actualIndexOfParsedSymbols++;
			}
			else
			{
				arrayOfCharactersLength--;

				update(strSkippedMsg + currentlyParsedSymbol);
			}
		}

		if (actualIndexOfParsedSymbols > 0)
		{
			readString = strBlank;
		}
		else
		{
			readString = str1;
			update(strTooFewArgsMsg);
		}

		for (int i = 0; i < actualIndexOfParsedSymbols; i++)
		{
			readString += arrayOfCharacters[i];
		}

		vectorOfVariableValues.push_back(stoi(readString));
	}

	while (vectorOfVariableValues.size() < vectorOfVariables.size())
	{
		vectorOfVariableValues.push_back(stoi(str1));
		update(strTooFewArgsMsg);
	}

	if (vectorOfVariableValues.size() > vectorOfVariables.size())
	{
		update(strTooManyArgsMsg);
	}

	return root->evaluate(vectorOfVariables, vectorOfVariableValues);
}

void Tree::subscribe(Subscriber* subscriber)
{
	subscribers.push_back(subscriber);
}

void Tree::unsubscribe(Subscriber* subscriber)
{
	subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
}

void Tree::update(std::string message) 
{
	for (Subscriber* subscriber : subscribers)
	{
		subscriber->update(message);
	}
}

Tree& Tree::operator=(const Tree& other)
{
	delete root;

	Node* newRoot = other.root->copyAll();

	root = newRoot;

	inputStr = other.inputStr;
	subscribers = other.subscribers;

	return *this;
}

Tree* Tree::operator+(Tree& other)
{
	Tree* thisCopy = new Tree();
	Tree* otherCopy = new Tree();

	*thisCopy = *this;
	*otherCopy = other;

	if (thisCopy->root->join(otherCopy->root))
	{
		delete thisCopy;
		thisCopy->root = otherCopy->root;
	}

	return thisCopy;
}

std::vector<std::string> Tree::findAllVariables()
{
	std::vector<std::string> arrayOfVariables;

	return root->findAllVariables(arrayOfVariables);
}

std::string Tree::toString()
{
	return root->toStringAll();
}

std::string Tree::toStringVisible()
{
	return root->toStringAll();
}
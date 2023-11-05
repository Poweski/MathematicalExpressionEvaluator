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
		update(tooManyArgsMsg);
	}
}

std::vector<std::string> Tree::findAllVariables()
{
	std::vector<std::string> arrayOfVariables;

	return root->findAllVariables(arrayOfVariables);
}

double Tree::evaluate(std::string inputVariableValues)
{
	//zabezpieczyc sie przed nieprawidlowa iloscia wartosci
	std::vector<std::string> arrayOfVariables = findAllVariables();
	std::vector<int> arrayOfVariableValues;

	std::string readString = strBlank, remainingString = inputVariableValues;

	int indexOfFirstSpace = inputVariableValues.find_first_of(strSpace);

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

		remainingString = inputVariableValues;

		if (indexOfFirstSpace != std::string::npos)
		{
			readString = remainingString.substr(0, indexOfFirstSpace);
			remainingString = remainingString.substr(indexOfFirstSpace + 1);
		}
		else
		{
			remainingString = strBlank;

			if (inputVariableValues.length() > 0) 
			{ 
				readString = inputVariableValues; 
			}
			else 
			{ 
				readString = str1; 

				update(tooFewArgsMsg);
			} 
		}

		arrayOfVariableValues.push_back(stoi(readString));
	}

	return root->evaluate(arrayOfVariables, arrayOfVariableValues);
}

void Tree::join(std::string inputString)
{
	Node* secondRoot;

	secondRoot = new Node();

	secondRoot->subscribe(this);

	secondRoot->build(inputString);

	root->join(secondRoot);
}

std::string Tree::toString()
{
	return root->toStringAll();
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
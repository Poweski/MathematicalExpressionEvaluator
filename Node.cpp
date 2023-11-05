#include "Node.h"

Node::Node()
{
	nodeType = UNDEFINED;
	value = strBlank;
	numberOfChildren = defaultNumberOfChildren;
	children = nullptr;
}

Node::~Node()
{
	delete children;
}

std::string Node::build(std::string inputString)
{
	std::string readString, remainingString;

	int indexOfFirstSpace = inputString.find_first_of(strSpace);

	while (indexOfFirstSpace == 0)
	{
		if (inputString.length() > 1)
		{
			inputString = inputString.substr(1);
		}
		else
		{
			inputString = strBlank;
		}

		indexOfFirstSpace = inputString.find_first_of(strSpace);
	}
	
	if (indexOfFirstSpace != std::string::npos)
	{
		readString = inputString.substr(0, indexOfFirstSpace);
		remainingString = inputString.substr(indexOfFirstSpace + 1);
	}
	else 
	{
		remainingString = strBlank;

		if (inputString.length() > 0) 
		{ 
			readString = inputString; 
		}
		else 
		{ 
			readString = str1;

			notify(tooFewArgsMsg);
		} 
	}

	int arrayOfCharactersLength = readString.length();
	int* arrayOfCharacters = new int[arrayOfCharactersLength];
	int actualIndexOfParsedSymbols = 0;
	char currentlyParsedSymbol = charSpace;

	for (int i = 0; i < readString.length(); i++)
	{
		currentlyParsedSymbol = readString[i];

		if (currentlyParsedSymbol >= char0 && currentlyParsedSymbol <= char9 || 
			currentlyParsedSymbol >= chara && currentlyParsedSymbol <= charz || 
			currentlyParsedSymbol >= charA && currentlyParsedSymbol <= charZ || 
			currentlyParsedSymbol == charPlus || currentlyParsedSymbol == charMinus || 
			currentlyParsedSymbol == charMult || currentlyParsedSymbol == charDiv)
		{
			arrayOfCharacters[actualIndexOfParsedSymbols] = currentlyParsedSymbol;
			actualIndexOfParsedSymbols++;
		}
		else
		{
			arrayOfCharactersLength--;

			notify(skippedMsg + currentlyParsedSymbol);
		}
	}

	std::string resultValue = strBlank;

	for (int i = 0; i < arrayOfCharactersLength; i++)
	{
		resultValue += arrayOfCharacters[i];
	}

	value = resultValue;

	bool numberFlag = true, variableFlag = false;
	bool additionFlag = false, subtractionFlag = false, multiplicationFlag = false, divisionFlag = false;
	bool sinFlag = false, cosFlag = false;

	if (actualIndexOfParsedSymbols > 0) 
	{ 
		currentlyParsedSymbol = arrayOfCharacters[0]; 
	}

	if (arrayOfCharactersLength == 1)
	{
		if (currentlyParsedSymbol == charPlus) 
		{ 
			additionFlag = true; 
		}
		if (currentlyParsedSymbol == charMinus) 
		{ 
			subtractionFlag = true; 
		}
		if (currentlyParsedSymbol == charMult) 
		{ 
			multiplicationFlag = true;
		}
		if (currentlyParsedSymbol == charDiv) 
		{ 
			divisionFlag = true; 
		}

		if (!(currentlyParsedSymbol >= char0 && currentlyParsedSymbol <= char9)) 
		{
			numberFlag = false; 
		}

		if (currentlyParsedSymbol >= chara && currentlyParsedSymbol <= charz ||
			currentlyParsedSymbol >= charA && currentlyParsedSymbol <= charZ) 
		{
			variableFlag = true;
		}
	}
	else if (arrayOfCharactersLength == lengthOfTrigonometricFunctionName)
	{
		if (arrayOfCharacters[0] == chars && arrayOfCharacters[1] == chari && arrayOfCharacters[2] == charn) 
		{ 
			sinFlag = true;
		}
		if (arrayOfCharacters[0] == charc && arrayOfCharacters[1] == charo && arrayOfCharacters[2] == chars) 
		{ 
			cosFlag = true; 
		}
	}

	for (int i = 0; i < arrayOfCharactersLength; i++)
	{
		currentlyParsedSymbol = arrayOfCharacters[i];

		if (!(currentlyParsedSymbol >= char0 && currentlyParsedSymbol <= char9)) 
		{ 
			numberFlag = false; 
		}
	}

	if (numberFlag == false && additionFlag == false && subtractionFlag == false && 
		multiplicationFlag == false && divisionFlag == false && sinFlag == false && cosFlag == false)
	{
		variableFlag = true; 
	}

	delete[] arrayOfCharacters;

	if (numberFlag)
	{
		nodeType = NUMBER;
		numberOfChildren = defaultNumberOfChildren;
		return remainingString;
	}
	else if (variableFlag)
	{
		nodeType = VARIABLE;
		numberOfChildren = defaultNumberOfChildren;
		return remainingString;
	}
	else if (additionFlag)
	{
		nodeType = ADDITION;
		return creatingChildrenOfBinaryOperator(remainingString);
	}
	else if (subtractionFlag)
	{
		nodeType = SUBTRACTION;
		return creatingChildrenOfBinaryOperator(remainingString);
	}
	else if (multiplicationFlag)
	{
		nodeType = MULTIPLICATION;
		return creatingChildrenOfBinaryOperator(remainingString);
	}
	else if (divisionFlag)
	{
		nodeType = DIVISION;
		return creatingChildrenOfBinaryOperator(remainingString);
	}
	else if (sinFlag)
	{
		nodeType = SIN;
		return creatingChildOfUnaryOperator(remainingString);
	}
	else if (cosFlag)
	{
		nodeType = COS;
		return creatingChildOfUnaryOperator(remainingString);
	}
}

std::string Node::creatingChildrenOfBinaryOperator(std::string remainingString)
{
	numberOfChildren = numberOfChildrenOfBinaryOperator;
	children = new Node * [numberOfChildrenOfBinaryOperator];
	children[0] = new Node();
	children[0]->subscribe(subscribers.at(0));
	remainingString = children[0]->build(remainingString);
	children[1] = new Node();
	children[1]->subscribe(subscribers.at(0));
	return children[1]->build(remainingString);
}

std::string Node::creatingChildOfUnaryOperator(std::string remainingString)
{
	numberOfChildren = numberOfChildrenOfUnaryOperator;
	children = new Node * [numberOfChildrenOfUnaryOperator];
	children[0] = new Node();
	children[0]->subscribe(subscribers.at(0));
	return children[0]->build(remainingString);
}

std::vector<std::string> Node::findAllVariables(std::vector<std::string> vectorOfVariables)
{
	bool occurenceFlag = true;
	
	switch (nodeType)
	{
	case VARIABLE:

		for (std::vector<std::string>::iterator it = vectorOfVariables.begin(); it != vectorOfVariables.end(); ++it)
		{
			if (*it == value) 
			{ 
				occurenceFlag = false;
			}
		}

		if (occurenceFlag)
		{ 
			vectorOfVariables.push_back(value); 
		}

		break;

	case ADDITION: 
		vectorOfVariables = findAllVariablesInBinaryOperator(vectorOfVariables);
		break;
	case SUBTRACTION: 		
		vectorOfVariables = findAllVariablesInBinaryOperator(vectorOfVariables);
		break;
	case MULTIPLICATION: 
		vectorOfVariables = findAllVariablesInBinaryOperator(vectorOfVariables);
		break;
	case DIVISION: 
		vectorOfVariables = findAllVariablesInBinaryOperator(vectorOfVariables);
		break;
	case SIN: 
		vectorOfVariables = findAllVariablesInUnaryOperator(vectorOfVariables);
		break;
	case COS: 
		vectorOfVariables = findAllVariablesInUnaryOperator(vectorOfVariables);
		break;
	default: 
		break;
	}

	return vectorOfVariables;
}

std::vector<std::string> Node::findAllVariablesInBinaryOperator(std::vector<std::string> vectorOfVariables)
{
	vectorOfVariables = children[0]->findAllVariables(vectorOfVariables);
	vectorOfVariables = children[1]->findAllVariables(vectorOfVariables);

	return vectorOfVariables;
}

std::vector<std::string> Node::findAllVariablesInUnaryOperator(std::vector<std::string> vectorOfVariables)
{
	vectorOfVariables = children[0]->findAllVariables(vectorOfVariables);

	return vectorOfVariables;
}

double Node::evaluate(std::vector<std::string> vectorOfVariables, std::vector<int> vectorOfVariableValues)
{
	double result = 0;
	int index = 0;

	switch (nodeType)
	{
	case NUMBER: result = std::stold(value);
		break;
	case VARIABLE: 
		
		for (std::vector<std::string>::iterator it = vectorOfVariables.begin(); it != vectorOfVariables.end(); ++it)
		{
			if (*it == value) 
			{ 
				return (double)(vectorOfVariableValues.at(index));
			}

			index++;
		}

		break;

	case ADDITION: 
		result = children[0]->evaluate(vectorOfVariables, vectorOfVariableValues) + children[1]->evaluate(vectorOfVariables, vectorOfVariableValues);
		break;
	case SUBTRACTION: 
		result = children[0]->evaluate(vectorOfVariables, vectorOfVariableValues) - children[1]->evaluate(vectorOfVariables, vectorOfVariableValues);
		break;
	case MULTIPLICATION: 
		result = children[0]->evaluate(vectorOfVariables, vectorOfVariableValues) * children[1]->evaluate(vectorOfVariables, vectorOfVariableValues);
		break;
	case DIVISION: 

		if (children[1]->evaluate(vectorOfVariables, vectorOfVariableValues) != 0)
		{
			result = children[0]->evaluate(vectorOfVariables, vectorOfVariableValues) / children[1]->evaluate(vectorOfVariables, vectorOfVariableValues);
		}
		else
		{
			result = children[0]->evaluate(vectorOfVariables, vectorOfVariableValues) / 1;

			notify(divisionBy0Msg);
		}
		
		break;

	case SIN: 
		result = sin(children[0]->evaluate(vectorOfVariables, vectorOfVariableValues));
		break;
	case COS: 
		result = cos(children[0]->evaluate(vectorOfVariables, vectorOfVariableValues));
		break;
	default: 
		break;
	}

	return result;
}

bool Node::join(Node* secondRoot)
{
	switch (nodeType)
	{
	case NUMBER: 
		return true;
		break;
	case VARIABLE: 
		return true;
		break;
	case ADDITION:
		joinInBinaryOperator(secondRoot);
		break;
	case SUBTRACTION:
		joinInBinaryOperator(secondRoot);
		break;
	case MULTIPLICATION:
		joinInBinaryOperator(secondRoot);
		break;
	case DIVISION:
		joinInBinaryOperator(secondRoot);
		break;
	case SIN:
		joinInUnaryOperator(secondRoot);
		break;
	case COS:
		joinInUnaryOperator(secondRoot);
		break;
	default: 
		return true;
		break;
	}
}

void Node::joinInBinaryOperator(Node* secondRoot)
{
	if (children[1]->join(secondRoot))
	{
		children[1] = secondRoot;
	}
}

void Node::joinInUnaryOperator(Node* secondRoot)
{
	if (children[0]->join(secondRoot))
	{
		children[0] = secondRoot;
	}
}

std::string Node::toStringAll()
{
	std::string result = toString() + strSpace;

	for (int i = 0; i < numberOfChildren; i++)
	{
		result += children[i]->toStringAll();
	}

	return result;
}

std::string Node::toString()
{
	return value;
}

void Node::subscribe(Subscriber* subscriber) 
{
	subscribers.push_back(subscriber);
}

void Node::unsubscribe(Subscriber* subscriber) 
{
	subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
}

void Node::notify(std::string message)
{
	for (Subscriber* subscriber : subscribers) 
	{
		subscriber->update(message);
	}
}
#include "Mediator.h"

Mediator::Mediator()
{
	tree = new Tree();

	msg = strBlank;

	divisionBy0Flag = false;
	tooFewArgsFlag = false;
	tooManyArgsFlag = false;
	characterSkippedFlag = false;
}

Mediator::~Mediator()
{
	delete tree;
}

void Mediator::run()
{
	std::cout << strHelpMsg + newLine << std::endl;

	std::string order = strBlank;
	std::string remaining = strBlank;

	bool doesTreeExist = false;

	while (order != strStop)
	{
		std::string input;

		std::getline(std::cin, input);

		int spacePosition = input.find(charSpace);

		if (spacePosition != std::string::npos) 
		{
			order = input.substr(0, spacePosition);
			remaining = input.substr(spacePosition + 1);
		}
		else 
		{
			order = input;
			remaining = strBlank;
		}

		if (order == strHelp)
		{
			std::cout << strHelpEnterMsg << std::endl;
			std::cout << strHelpVarsMsg << std::endl;
			std::cout << strHelpPrintMsg << std::endl;
			std::cout << strHelpCompMsg << std::endl;
			std::cout << strHelpJoinMsg << std::endl;
			std::cout << strHelpStopMsg + newLine << std::endl;
		}
		else if (order == strEnter) 
		{ 
			doesTreeExist = true;

			enter(remaining); 
		}
		else if (order == strVars) 
		{ 
			if (doesTreeExist)
			{
				vars(); 
			}
			else
			{
				std::cout << strEnterWarning << std::endl;
			}
		}
		else if (order == strPrint) 
		{ 
			if (doesTreeExist)
			{
				print(); 
			}
			else
			{
				std::cout << strEnterWarning << std::endl;
			}
		}
		else if (order == strComp) 
		{
			if (doesTreeExist)
			{
				comp(remaining); 
			}
			else
			{
				std::cout << strEnterWarning << std::endl;
			}
		}
		else if (order == strJoin) 
		{ 
			if (doesTreeExist)
			{
				join(remaining);
			}
			else
			{
				std::cout << strEnterWarning << std::endl;
			}
		}
		else if (order == strStop) 
		{

		}
		else 
		{
			std::cout << strInvalidCommand << std::endl;
			std::cout << strHelpMsg + newLine << std::endl;
		}
	}
}

void Mediator::enter(std::string inputString)
{
	tree->unsubscribe(this);
		
	tree->subscribe(this);

	tree->build(inputString);

	if (isMsgMarked())
	{
		printMsg();
		resetFlags();
	}
}

void Mediator::vars()
{
	std::vector<std::string> arrayOfVariables = tree->findAllVariables();

	std::string result = strBlank;

	for (std::vector<std::string>::iterator it = arrayOfVariables.begin(); it != arrayOfVariables.end(); ++it)
	{
		result += *it + strSpace;
	}

	if (result == strBlank)
	{
		std::cout << strVariables << strNone << std::endl;
	}
	else
	{
		std::cout << strVariables << result << std::endl;
	}
}

void Mediator::print()
{
	std::cout << strExpression << tree->toString() << std::endl;
}

void Mediator::comp(std::string inputVariableValues)
{
	double result = tree->evaluate(inputVariableValues);

	if (isMsgMarked())
	{
		printMsg();
		resetFlags();
	}

	std::cout << strResult << result << std::endl;
}

void Mediator::join(std::string inputString)
{
	Tree* secondTree = new Tree();
	Tree* result = new Tree();

	secondTree->subscribe(this);

	secondTree->build(inputString);

	result = *tree + *secondTree;

	delete tree;
	delete secondTree;

	tree = result;	
	
	if (isMsgMarked())
	{
		printMsg();
		resetFlags();
	}
}

void Mediator::update(std::string message)
{
	if (message == strDivisionBy0Msg)
	{
		divisionBy0Flag = true;
	}
	else if (message == strTooFewArgsMsg)
	{
		tooFewArgsFlag = true;
	}
	else if (message == strTooManyArgsMsg)
	{
		tooManyArgsFlag = true;
	}
	else
	{
		characterSkippedFlag = true;

		int spacePosition = message.find(charSpace);

		message = message.substr(spacePosition + 1);

		spacePosition = message.find(charSpace);

		if (spacePosition != std::string::npos)
		{
			msg += message.substr(spacePosition + 1) + strSpace;
		}
	}
}

void Mediator::printMsg()
{

	if (divisionBy0Flag == true)
	{
		std::cout << strDivisionBy0Msg << std::endl;
	}
	if (tooFewArgsFlag == true)
	{
		std::cout << strTooFewArgsMsg << std::endl;
	}
	if (tooManyArgsFlag == true)
	{
		std::cout << strTooManyArgsMsg << std::endl;
	}
	if (characterSkippedFlag == true)
	{
		std::cout << strSkippedMsg + msg << std::endl;
	}

	if (isMsgMarked())
	{
		std::cout << strExpressionProcessed << tree->toStringVisible() << std::endl;
	}
}

bool Mediator::isMsgMarked()
{
	if (divisionBy0Flag == true || tooFewArgsFlag == true || tooManyArgsFlag == true || characterSkippedFlag == true)
	{
		return true;
	}

	return false;
}

void Mediator::resetFlags()
{
	msg = strBlank;

	divisionBy0Flag = false;
	tooFewArgsFlag = false;
	tooManyArgsFlag = false;
	characterSkippedFlag = false;
}
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
	std::string prompt = strBlank;
	std::string remaining = strBlank;

	bool doesTreeExist = false;

	while (prompt != strStop)
	{
		std::string input;

		std::getline(std::cin, input);

		int spacePosition = input.find(charSpace);

		if (spacePosition != std::string::npos) 
		{
			prompt = input.substr(0, spacePosition);
			remaining = input.substr(spacePosition + 1);
		}
		else 
		{
			prompt = input;
		}

		if (prompt == strEnter) 
		{ 
			doesTreeExist = true;

			enter(remaining); 
		}
		else if (prompt == strVars) 
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
		else if (prompt == strPrint) 
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
		else if (prompt == strComp) 
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
		else if (prompt == strJoin) 
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
		else if (prompt == strStop) 
		{

		}
		else 
		{
			std::cout << strInvalidCommand << std::endl;
		}
	}
}

void Mediator::enter(std::string inputString)
{
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
		result += *it + tab;
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

}

void Mediator::printMsg()
{

	if (divisionBy0Flag == true)
	{
		std::cout << divisionBy0Msg << std::endl;
	}
	if (tooFewArgsFlag == true)
	{
		std::cout << tooFewArgsMsg << std::endl;
	}
	if (tooManyArgsFlag == true)
	{
		std::cout << tooManyArgsMsg << std::endl;
	}
	if (characterSkippedFlag == true)
	{
		std::cout << skippedMsg + msg << std::endl;
	}

	if (isMsgMarked())
	{
		std::cout << strExpressionProcessed << tree->toString() << std::endl;
	}
}

void Mediator::update(std::string message)
{
	if (message == divisionBy0Msg)
	{
		divisionBy0Flag = true;
	}
	else if (message == tooFewArgsMsg)
	{
		tooFewArgsFlag = true;
	}
	else if (message == tooManyArgsMsg)
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
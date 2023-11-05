#pragma once
#include <iostream>
#include <string>
#include "Tree.h"

class Mediator : public Subscriber
{
private:

	Tree* tree;

	std::string msg;

	bool divisionBy0Flag;

	bool tooFewArgsFlag;

	bool tooManyArgsFlag;

	bool characterSkippedFlag;


	bool isMsgMarked();

	void printMsg();

	void resetFlags();


public:

	Mediator();

	~Mediator();

	void run();

	void enter(std::string inputString);

	void vars();

	void print();

	void comp(std::string inputVariableValues);

	void join(std::string inputString);

	void update(std::string message);
};

const std::string strStop = "stop";
const std::string strEnter = "enter";
const std::string strVars = "vars";
const std::string strPrint = "print";
const std::string strComp = "comp";
const std::string strJoin = "join";
const std::string strInvalidCommand = "invalid command!";
const std::string strResult = "result: ";
const std::string strExpression = "expression: ";
const std::string strVariables = "variables: ";
const std::string strNone = "NONE";
const std::string strEnterWarning = "first enter an expression!";
const std::string strExpressionProcessed = "expression being processed: ";
const std::string tab = "\t";

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

	void update(std::string message) override;
};

const std::string strStop = "stop";
const std::string strEnter = "enter";
const std::string strVars = "vars";
const std::string strPrint = "print";
const std::string strComp = "comp";
const std::string strJoin = "join";
const std::string strHelp = "/?";
const std::string strInvalidCommand = "invalid command!";
const std::string strResult = "result: ";
const std::string strExpression = "expression: ";
const std::string strVariables = "variables: ";
const std::string strNone = "NONE";
const std::string strEnterWarning = "first enter an expression!";
const std::string strExpressionProcessed = "expression being processed: ";
const std::string strHelpMsg = "type /? to list available commands";
const std::string strHelpEnterMsg = "enter <formula> - the program tries to create a tree based on the given expression";
const std::string strHelpVarsMsg = "vars - prints all variables from the entered expression";
const std::string strHelpPrintMsg = "print - prints the currently entered expression in prefix form";
const std::string strHelpCompMsg = "comp <var0> <var1>...<varN> - calculation of the value of the entered formula";
const std::string strHelpJoinMsg = "join <formula> - the program creates a tree and adds it to the existing one";
const std::string strHelpStopMsg = "stop - stops the program";

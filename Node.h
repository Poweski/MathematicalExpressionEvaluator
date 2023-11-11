#pragma once
#include <string>
#include <vector>
#include "Subscriber.h"

enum NodeType
{
	UNDEFINED,
	NUMBER,
	VARIABLE,
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	SIN,
	COS
};

class Node
{
private:

	NodeType nodeType;

	std::string value;

	std::string visibleValue;

	int numberOfChildren;

	bool isVisible;

	Node** children;

	std::vector<Subscriber*> subscribers;


	std::string creatingChildrenOfBinaryOperator(std::string remainingString);

	std::string creatingChildOfUnaryOperator(std::string remainingString);

	std::vector<std::string> findAllVariablesInBinaryOperator(std::vector<std::string> vectorOfVariables);

	std::vector<std::string> findAllVariablesInUnaryOperator(std::vector<std::string> vectorOfVariables);

	void joinInBinaryOperator(Node* secondRoot);

	void joinInUnaryOperator(Node* secondRoot);

	void notify(std::string message);


public:

	Node();

	~Node();

	std::string build(std::string inputString);

	std::string toStringAll();

	std::string toString();

	std::vector<std::string> findAllVariables(std::vector<std::string> arrayOfVariables);

	double evaluate(std::vector<std::string> vectorOfVariables, std::vector<int> vectorOfVariableValues);

	bool join(Node* secondRoot);

	void subscribe(Subscriber* subscriber);

	void unsubscribe(Subscriber* subscriber);

	Node* copyAll();
};

const int defaultNumberOfChildren = 0;
const int numberOfChildrenOfUnaryOperator = 1;
const int numberOfChildrenOfBinaryOperator = 2;
const int lengthOfTrigonometricFunctionName = 3;

const char char0 = '0';
const char char9 = '9';
const char chara = 'a';
const char charA = 'A';
const char charz = 'z';
const char charZ = 'Z';
const char charPlus = '+';
const char charMinus = '-';
const char charMult = '*';
const char charDiv = '/';
const char chars = 's';
const char chari = 'i';
const char charn = 'n';
const char charc = 'c';
const char charo = 'o';
const char charSpace = ' ';

const std::string strBlank = "";
const std::string strSpace = " ";
const std::string strEqualSign = "=";
const std::string strLeftBracket = "(";
const std::string strRightBracket = ")";
const std::string str1 = "1";
const std::string newLine = "\n";
const std::string tab = "\t";

const std::string strCurled = "(curled)";
const std::string strSkippedMsg = "symbol skipped: ";
const std::string strDivisionBy0Msg = "division by 0!";
const std::string strTooFewArgsMsg = "too few arguments!";
const std::string strTooManyArgsMsg = "too many arguments!";

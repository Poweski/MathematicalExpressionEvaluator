#pragma once
#include <string>
#include <vector>
#include "Node.h"

class Tree : public Subscriber
{
private:

	Node* root;

	std::string inputStr;

	std::vector<Subscriber*> subscribers;


public:

	Tree();

	~Tree();

	std::string toString();

	std::vector<std::string> findAllVariables();

	double evaluate(std::string inputVariableValues);

	void build(std::string inputString);

	void join(std::string inputString);

	void subscribe(Subscriber* subscriber);

	void unsubscribe(Subscriber* subscriber);

	void update(std::string message);
};

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

	void build(std::string inputString);

	double evaluate(std::string inputVariableValues);

	void subscribe(Subscriber* subscriber);

	void unsubscribe(Subscriber* subscriber);

	void update(std::string message) override;

	Tree& operator=(const Tree& other);

	Tree* operator+(Tree& other);		

	std::vector<std::string> findAllVariables();

	std::string toString();

	std::string toStringVisible();
};

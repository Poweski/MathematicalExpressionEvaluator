#pragma once
#include <string>

class Subscriber 
{
public:
    virtual void update(std::string message) {};
};

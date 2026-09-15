#pragma once
#include <iostream>
#include <vector>
#include "patterns/Observer.h"

class Subject
{
private:
    std::vector<Observer*> observers;

public:
    void attach(Observer* observer);
    void detach(const Observer* observer);
    void notifyAll() const;
};
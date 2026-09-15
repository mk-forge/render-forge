#include "patterns/Subject.h"

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(const Observer* observer) {
    for (size_t i = 0; i < observers.size(); ++i) {
        if (observers[i] == observer) {
            observers.erase(observers.begin() + i);
            return;
        }
    }
}

void Subject::notifyAll() const {
    for (Observer* observer : observers) {
        observer->update();
    }
}
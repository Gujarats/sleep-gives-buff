#pragma once
using namespace std;

enum class NeedsType {
    kSleep = 0,
    kHungry = 1
};

class Needs {
private:
    uint8_t currentValue;
    NeedsType needsType;
public:
    const static uint8_t maxValue = 100;
    const static uint8_t minValue = 0;

    Needs() = default;
	virtual ~Needs() = default;

	Needs(NeedsType a_needType)	
	{
        needsType = a_needType;
        currentValue = maxValue;
    }

    NeedsType getNeedsType(){
        return needsType; 
    }

    uint8_t* getNeedsValue(){
        return &currentValue;
    }

};



#include <gui/model/FakeHardware.hpp>

static unsigned int nextRand()
{
    static unsigned int seed = 0;
    seed = ((214013 * (unsigned int)(seed) + 2531011) >> 16);
    return seed;
}

FakeHardware::FakeHardware() :
    desiredValue(0),
    currentValue(0)
{
}

int FakeHardware::readCurrentValue()
{
    if (currentValue < desiredValue && (nextRand() % 20) > 18)
    {
        currentValue++;
    }
    return currentValue;
}

int FakeHardware::readCurrentValueOffline()
{
    for (volatile int i = 0; i < 1 << 30; i++)
    {
    }
    return readCurrentValue();
}

void FakeHardware::increaseDesiredValue()
{
    desiredValue += 10;
}

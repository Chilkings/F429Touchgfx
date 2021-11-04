#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <touchgfx/Utils.hpp>
#include <gui/model/FakeHardware.hpp>

Model::Model() : modelListener(0)
{
}

void Model::tick()
{
    int currentValue = readCurrentValue();
    modelListener->setCurrentValue(currentValue);
}

void Model::increaseDesiredValue()
{
    hardware.increaseDesiredValue();
}

int Model::readCurrentValue()
{
    return hardware.readCurrentValue();
}

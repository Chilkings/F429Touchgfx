#ifndef FAKE_HARDWARE_HPP
#define FAKE_HARDWARE_HPP

class FakeHardware
{
public:
    FakeHardware();

    // can be called directly from ui task
    int readCurrentValue();

    // should be called from separate task, and ui informed by intertask messaging - UNUSED for this example
    int readCurrentValueOffline();

    void increaseDesiredValue();
private:
    int desiredValue;
    int currentValue;
};

#endif /* FAKE_HARDWARE_HPP */

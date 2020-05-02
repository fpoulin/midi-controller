#include "PotHandler.h"

PotHandler::PotHandler(uint8_t min, uint8_t max) : _min(min), _max(max) {}

uint8_t PotHandler::getMin()
{
    return _min;
}

uint8_t PotHandler::getMax()
{
    return _max;
}
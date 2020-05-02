#pragma once

class BtnHandler
{
public:
    BtnHandler();
    virtual void onClick() = 0;
    virtual ~BtnHandler() = 0;
};

inline BtnHandler::~BtnHandler() {}
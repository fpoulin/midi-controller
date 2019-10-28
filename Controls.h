#pragma once

class Controls
{
private:
    unsigned long _debounce = 0;
    bool _btn1Pressed = false;
    bool _btn2Pressed = false;
    bool _btn3Pressed = false;
    void (*_onClickBtn1)(void);
    void (*_onClickBtn2)(void);
    void (*_onClickBtn3)(void);
    void (*_onChangeKnob1)(uint8_t oldValue, uint8_t newValue);
    void (*_onChangeKnob2)(uint8_t oldValue, uint8_t newValue);
    void (*_onChangeKnob3)(uint8_t oldValue, uint8_t newValue);
    void (*_onChangeKnob4)(uint8_t oldValue, uint8_t newValue);
    void (*_onChangeLinear)(uint8_t oldValue, uint8_t newValue);
public:
    Controls();
    void loop();
    void setHandleBtn1(void (*onClick)(void));
    void setHandleBtn2(void (*onClick)(void));
    void setHandleBtn3(void (*onClick)(void));
    void setHandleKnob1(void (*onChange)(uint8_t oldValue, uint8_t newValue));
    void setHandleKnob2(void (*onChange)(uint8_t oldValue, uint8_t newValue));
    void setHandleKnob3(void (*onChange)(uint8_t oldValue, uint8_t newValue));
    void setHandleKnob4(void (*onChange)(uint8_t oldValue, uint8_t newValue));
    void setHandleLinear(void (*onChange)(uint8_t oldValue, uint8_t newValue));
};
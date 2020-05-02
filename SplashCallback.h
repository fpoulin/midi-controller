#pragma once

// functionoid for a callback invoked at the end of the splash animation
class SplashCallback
{
public:
  virtual void onSplashEnd() = 0;
  virtual ~SplashCallback() = 0;
};

inline SplashCallback::~SplashCallback() {}
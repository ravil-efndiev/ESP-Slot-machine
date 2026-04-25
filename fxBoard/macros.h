#pragma once

// #define SM_DEBUG

#ifdef SM_DEBUG 
  #define SM_USE_DEBUG Serial.begin(9600)

  #define SM_PRINT(v) Serial.print(v)
  #define SM_PRINTLN(v) Serial.println(v)
#else
  #define SM_USE_DEBUG

  #define SM_PRINT(v)
  #define SM_PRINTLN(v)
#endif


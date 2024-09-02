#pragma once
class cbt
{
  // Num elements that the CBT can hold
  uint32_t numElements = 0;

  // Last level size 
  uint32_t lastLevelSize = 0;

  // Number of Graphics buffers used to represent the CBT
  uint32_t bufferCount = 0;

  // Graphics buffer used to store CBT
  uint64_t bufferArray[2];
};


// NOTE: Auto-Generated File!

#include "script/scriptTable.h"

namespace P64 { class Object; }

namespace P64::Script
{
__CODE_DECL__

  ScriptEntry codeTable[] = {
__CODE_ENTRIES__
  };

  uint16_t codeSizeTable[] = {
__CODE_SIZE_ENTRIES__
  };

  constinit ScriptEntry codeDummy{};

  ScriptEntry& getCodeByIndex(uint32_t idx)
  {
    if (idx < sizeof(codeTable)/sizeof(codeTable[0])) {
      return codeTable[idx];
    }
    return codeDummy;
  }

  uint16_t getCodeSizeByIndex(uint32_t idx)
  {
    if (idx < sizeof(codeTable)/sizeof(codeTable[0])) {
      return codeSizeTable[idx];
    }
    return 0;
  }
}

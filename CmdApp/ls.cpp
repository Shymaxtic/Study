#include "CmdMap.h"

int ls(int argc, char** argv) {
    for (uint8_t i = 0; i < argc; ++i) {
      Serial.print(argv[i]);
    }
    return 0;
}

REGISTER_CMD(ls);

#ifndef __CMD_MAP_H__
#define __CMD_MAP_H__

#include "Arduino.h"
#include "HardwareSerial.h"

#include <stdio.h>
#include <string.h>

#define D_MAX_CMD_LEN   64
#define D_CMD_SECTION   ".myCmdSection"

typedef int (*fptr) (int argc, char** argv);

typedef struct cmd_map_t {
    const char cmd[D_MAX_CMD_LEN];
    fptr f;
} cmd_map_t;

#define REGISTER_CMD(cmd)           \
    cmd_map_t cmd##ptr __attribute__((section(D_CMD_SECTION))) = {#cmd, &cmd}; 

extern cmd_map_t __start_myCmdSection;
extern cmd_map_t __stop_myCmdSection;

extern int HandleCmd(char* cmd);


#endif //__CMD_MAP_H__
    

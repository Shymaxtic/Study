#include "CmdMap.h"

int HandleCmd(char* cmd) {
    char** argv;
    // Count argc
    char* tmp = cmd;
    uint8_t count = 0;
    while (*tmp != NULL) {
      if (*tmp == ' ') {
          count++;          
      }
      tmp++;
    }
    count++;
    argv = (char**)malloc(sizeof(char*) * count);
    uint8_t i = 0;
    if (argv) {
          char *token = strtok(cmd, " ");
          while (i < count && token != NULL) {
            *(argv + i++) = strdup(token);
            token = strtok(NULL, " ");      
          } 
    }
    for (cmd_map_t *it = &__start_myCmdSection; it < &__stop_myCmdSection; ++it) {
        if (strcmp(argv[0], it->cmd) == 0) {
            int ret = (it->f)(i, (char**)argv);
            for (uint8_t j = 0; j < i; ++j) {
              free(argv[j]);
            }
            free(argv);
            return ret;
        }
    }
    Serial.println("Cannot find command.");
    return -1;
}

#ifndef ZMIENNE_H_
#define ZMIENNE_H_

const char DEV_NAME[] = "dev_name";
char devName[30] = {};
const char PARAM_CMD1[] = "cmd1";
inline constexpr char *MAGIC_SWITCH_ON = "magicswitchon";
uint8_t MagicSwitchOn = OFF_;
const char* BEHAVIOUR_KEY = "behaviour";
int32_t behaviour = 0;
const char* FILTER_KEY = "filter value";
uint32_t filter = 3000;
const char* LIMIT_KEY = "limit value";
uint32_t limit = 50000;
const char SELECT_MODE[] = "select_mode";
uint32_t selectMode = 0;

uint32_t debounce = 3;
int32_t difference = 0;
uint32_t margin = 1000;
bool status1 = false;
bool status2 = false;
unsigned long czas1 = 0;
unsigned long czas2 = 0;

#endif
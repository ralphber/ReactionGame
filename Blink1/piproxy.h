
#pragma once

#if _WIN32 || _WIN64
#include "winpi.h"
#else
#include <wiringPi.h>
#endif
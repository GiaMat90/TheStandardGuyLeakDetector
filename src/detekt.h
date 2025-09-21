#pragma once

#include "detektor.h"

/* macro substituition of operator new with a placement new with debugging info */
#define new new(where(__FILE__, __func__, __LINE__))




#include "../kernel/panic/panic.h"

#define kassert(x) ({ (x) ? 0 : assertion_failure("Assertion `%s' failed\n", #x); })
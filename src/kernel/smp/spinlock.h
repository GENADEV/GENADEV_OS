#ifndef ATOMIC_LOCK_H
#define ATOMIC_LOCK_H

#include <stdbool.h>

void aquire_lock(bool *lock);
void release_lock(bool *lock);

#endif // ATOMIC_LOCK_H
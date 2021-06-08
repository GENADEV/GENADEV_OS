#include "spinlock.h"

void aquire_lock(bool *lock)
{
    while(__atomic_test_and_set(lock, __ATOMIC_ACQUIRE));
}

void release_lock(bool *lock)
{
    __atomic_clear(lock, __ATOMIC_RELEASE);
}
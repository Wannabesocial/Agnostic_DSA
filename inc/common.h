/**
 * A common file among all DSA files.
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

// Rename Base types to a more readable one
typedef uint32_t u32;
typedef uint64_t u64;

// Units to measure digital data
#define KiloByte(n) ((n) * (1lu << 10))
#define MegaByte(n) ((n) * (1lu << 20))
#define GigaByte(n) ((n) * (1lu << 30))

#endif
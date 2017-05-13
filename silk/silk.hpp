#ifndef __TRACEGENERATOR_HPP__
#define __TRACEGENERATOR_HPP__

#include"memoryUnit.hpp"
#include"tracer.hpp"

// must include a cpp instead of hpp file because of templates
#include"leakageFunctions.cpp" 


#include"leakageDistributionFunctions.hpp"

// Unsigned types
typedef MemoryUnit<uint8_t>  U8;
typedef MemoryUnit<uint16_t> U16;
typedef MemoryUnit<uint32_t> U32;
typedef MemoryUnit<uint64_t> U64;

// Signed types
typedef MemoryUnit<int8_t>  S8;
typedef MemoryUnit<int16_t> S16;
typedef MemoryUnit<int32_t> S32;
typedef MemoryUnit<int64_t> S64;

#endif //__TRACEGENERATOR_HPP__

// generated from rosidl_generator_c/resource/msg__struct.h.template
// generated code does not contain a copyright notice

#ifndef ADAS_PIPELINE__MSG__SOURCE_PARAMETERS__STRUCT_H_
#define ADAS_PIPELINE__MSG__SOURCE_PARAMETERS__STRUCT_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// include message dependencies
// dir
#include "rosidl_generator_c/string.h"

/// Struct of message adas_pipeline/SourceParameters
typedef struct adas_pipeline__msg__SourceParameters
{
  int32_t inputmode;
  int32_t device;
  rosidl_generator_c__String dir;
  float fps;
  bool paused;
} adas_pipeline__msg__SourceParameters;

/// Struct for an array of messages
typedef struct adas_pipeline__msg__SourceParameters__Array
{
  adas_pipeline__msg__SourceParameters * data;
  size_t size;
  size_t capacity;
} adas_pipeline__msg__SourceParameters__Array;

#endif  // ADAS_PIPELINE__MSG__SOURCE_PARAMETERS__STRUCT_H_

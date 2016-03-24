// generated from rosidl_generator_c/resource/msg__functions.c.template
// generated code does not contain a copyright notice

#include "adas_pipeline/msg/source_parameters__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// include message dependencies
// dir
#include "rosidl_generator_c/string_functions.h"

bool
adas_pipeline__msg__SourceParameters__init(adas_pipeline__msg__SourceParameters * msg)
{
  if (!msg) {
    return false;
  }
  // inputmode
  // device
  // dir
  rosidl_generator_c__String__init(&msg->dir);
  // fps
  // paused
  return true;
}

void
adas_pipeline__msg__SourceParameters__fini(adas_pipeline__msg__SourceParameters * msg)
{
  if (!msg) {
    return;
  }
  // inputmode
  // device
  // dir
  rosidl_generator_c__String__fini(&msg->dir);
  // fps
  // paused
}

adas_pipeline__msg__SourceParameters *
adas_pipeline__msg__SourceParameters__create()
{
  adas_pipeline__msg__SourceParameters * msg = malloc(sizeof(adas_pipeline__msg__SourceParameters));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(adas_pipeline__msg__SourceParameters));
  bool success = adas_pipeline__msg__SourceParameters__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
adas_pipeline__msg__SourceParameters__destroy(adas_pipeline__msg__SourceParameters * msg)
{
  if (msg) {
    adas_pipeline__msg__SourceParameters__fini(msg);
  }
  free(msg);
}


bool
adas_pipeline__msg__SourceParameters__Array__init(adas_pipeline__msg__SourceParameters__Array * array, size_t size)
{
  if (!array) {
    return false;
  }
  adas_pipeline__msg__SourceParameters * data = NULL;
  if (size) {
    data = malloc(sizeof(adas_pipeline__msg__SourceParameters) * size);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = adas_pipeline__msg__SourceParameters__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        adas_pipeline__msg__SourceParameters__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
adas_pipeline__msg__SourceParameters__Array__fini(adas_pipeline__msg__SourceParameters__Array * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      adas_pipeline__msg__SourceParameters__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

adas_pipeline__msg__SourceParameters__Array *
adas_pipeline__msg__SourceParameters__Array__create(size_t size)
{
  adas_pipeline__msg__SourceParameters__Array * array = malloc(sizeof(adas_pipeline__msg__SourceParameters__Array));
  if (!array) {
    return NULL;
  }
  bool success = adas_pipeline__msg__SourceParameters__Array__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
adas_pipeline__msg__SourceParameters__Array__destroy(adas_pipeline__msg__SourceParameters__Array * array)
{
  if (array) {
    adas_pipeline__msg__SourceParameters__Array__fini(array);
  }
  free(array);
}

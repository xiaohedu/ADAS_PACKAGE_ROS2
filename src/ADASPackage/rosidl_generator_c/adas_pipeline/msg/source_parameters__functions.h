// generated from rosidl_generator_c/resource/msg__functions.h.template
// generated code does not contain a copyright notice

#ifndef adas_pipeline__msg__source_parameters__functions_h_
#define adas_pipeline__msg__source_parameters__functions_h_

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_generator_c/visibility_control.h"
#include "adas_pipeline/msg/rosidl_generator_c__visibility_control.h"

#include "adas_pipeline/msg/source_parameters__struct.h"

/// Initialize adas_pipeline/SourceParameters message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(adas_pipeline__msg__SourceParameters)) before
 * or use adas_pipeline__msg__SourceParameters__create() to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline
bool
adas_pipeline__msg__SourceParameters__init(adas_pipeline__msg__SourceParameters * msg);

/// Finalize adas_pipeline/SourceParameters message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline
void
adas_pipeline__msg__SourceParameters__fini(adas_pipeline__msg__SourceParameters * msg);

/// Create adas_pipeline/SourceParameters message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls adas_pipeline__msg__SourceParameters__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline
adas_pipeline__msg__SourceParameters *
adas_pipeline__msg__SourceParameters__create();

/// Destroy adas_pipeline/SourceParameters message.
/**
 * It calls adas_pipeline__msg__SourceParameters__fini() and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline
void
adas_pipeline__msg__SourceParameters__destroy(adas_pipeline__msg__SourceParameters * msg);


/// Initialize array of adas_pipeline/SourceParameters messages.
/**
 * It allocates the memory for the number of elements and
 * calls adas_pipeline__msg__SourceParameters__init() for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline
bool
adas_pipeline__msg__SourceParameters__Array__init(adas_pipeline__msg__SourceParameters__Array * array, size_t size);

/// Finalize array of adas_pipeline/SourceParameters messages.
/**
 * It calls adas_pipeline__msg__SourceParameters__fini() for each element of the array and
 * frees the memory for the number of elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline
void
adas_pipeline__msg__SourceParameters__Array__fini(adas_pipeline__msg__SourceParameters__Array * array);

/// Create array of adas_pipeline/SourceParameters messages.
/**
 * It allocates the memory for the array and
 * calls adas_pipeline__msg__SourceParameters__Array__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline
adas_pipeline__msg__SourceParameters__Array *
adas_pipeline__msg__SourceParameters__Array__create(size_t size);

/// Destroy array of adas_pipeline/SourceParameters messages.
/**
 * It calls adas_pipeline__msg__SourceParameters__Array__fini() on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline
void
adas_pipeline__msg__SourceParameters__Array__destroy(adas_pipeline__msg__SourceParameters__Array * array);

#endif  // adas_pipeline__msg__source_parameters__functions_h_

// generated from rosidl_typesupport_introspection_c/resource/msg__type_support.c.template


#include "adas_pipeline/msg/source_parameters__introspection_type_support.h"

// providing offsetof()
#include <stddef.h>

#include <rosidl_generator_c/message_type_support.h>

#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"

#include "adas_pipeline/msg/source_parameters__struct.h"

static const rosidl_typesupport_introspection_c__MessageMember adas_pipeline__msg__rosidl_typesupport_introspection_c__SourceParameters_message_member_array[5] = {
  {
    "inputmode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(adas_pipeline__msg__SourceParameters, inputmode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "device",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(adas_pipeline__msg__SourceParameters, device),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "dir",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(adas_pipeline__msg__SourceParameters, dir),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "fps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(adas_pipeline__msg__SourceParameters, fps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "paused",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOL,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(adas_pipeline__msg__SourceParameters, paused),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers adas_pipeline__msg__rosidl_typesupport_introspection_c__SourceParameters_message_members = {
  "adas_pipeline",  // package name
  "SourceParameters",  // message name
  5,  // number of fields
  adas_pipeline__msg__rosidl_typesupport_introspection_c__SourceParameters_message_member_array  // message members
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t adas_pipeline__msg__rosidl_typesupport_introspection_c__SourceParameters_message_type_support_handle = {
  0,
  &adas_pipeline__msg__rosidl_typesupport_introspection_c__SourceParameters_message_members
};

const rosidl_message_type_support_t *
rosidl_get_message_type_support__adas_pipeline__msg__SourceParameters()
{
  if (!adas_pipeline__msg__rosidl_typesupport_introspection_c__SourceParameters_message_type_support_handle.typesupport_identifier) {
    adas_pipeline__msg__rosidl_typesupport_introspection_c__SourceParameters_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &adas_pipeline__msg__rosidl_typesupport_introspection_c__SourceParameters_message_type_support_handle;
}

// generated from rosidl_typesupport_opensplice_cpp/resource/visibility_control.h.in

#ifndef __adas_pipeline__msg__dds_opensplice__visibility_control__h__
#define __adas_pipeline__msg__dds_opensplice__visibility_control__h__

#if __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_adas_pipeline \
      __attribute__ ((dllexport))
    #define ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_IMPORT_adas_pipeline \
      __attribute__ ((dllimport))
  #else
    #define ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_adas_pipeline \
      __declspec(dllexport)
    #define ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_IMPORT_adas_pipeline \
      __declspec(dllimport)
  #endif
  #ifdef ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_BUILDING_DLL_adas_pipeline
    #define ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_adas_pipeline \
      ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_adas_pipeline
  #else
    #define ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_adas_pipeline \
      ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_IMPORT_adas_pipeline
  #endif
#else
  #define ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_adas_pipeline
  #define ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_adas_pipeline
#endif

#if __cplusplus
}
#endif

#endif  // __adas_pipeline__msg__dds_opensplice__visibility_control__h__

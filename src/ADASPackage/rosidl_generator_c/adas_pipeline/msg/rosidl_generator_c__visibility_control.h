// generated from rosidl_generator_c/resource/rosidl_generator_c__visibility_control.h.in

#ifndef adas_pipeline__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL__H_
#define adas_pipeline__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL__H_

#if __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_C_EXPORT_adas_pipeline \
      __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_C_IMPORT_adas_pipeline \
      __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_C_EXPORT_adas_pipeline \
      __declspec(dllexport)
    #define ROSIDL_GENERATOR_C_IMPORT_adas_pipeline \
      __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_C_BUILDING_DLL_adas_pipeline
    #define ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline \
      ROSIDL_GENERATOR_C_EXPORT_adas_pipeline
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline \
      ROSIDL_GENERATOR_C_IMPORT_adas_pipeline
  #endif
#else
  #define ROSIDL_GENERATOR_C_EXPORT_adas_pipeline \
    __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_C_IMPORT_adas_pipeline
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline \
      __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_C_PUBLIC_adas_pipeline
  #endif
#endif

#if __cplusplus
}
#endif

#endif  // adas_pipeline__MSG__ROSIDL_GENERATOR_C__VISIBILITY_CONTROL__H_

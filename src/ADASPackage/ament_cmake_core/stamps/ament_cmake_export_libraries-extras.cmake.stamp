# generated from ament_cmake_export_libraries/cmake/template/ament_cmake_export_libraries.cmake.in

set(_exported_library_targets "adas_pipeline__rosidl_generator_c;adas_pipeline__rosidl_typesupport_opensplice_cpp;adas_pipeline__rosidl_typesupport_introspection_c;adas_pipeline__rosidl_typesupport_introspection_cpp")
set(_exported_absolute_libraries "/usr/lib/libcmxml.so;/usr/lib/libcommonserv.so;/usr/lib/libdcpsgapi.so;/usr/lib/libdcpssac.so;/usr/lib/libddsconfparser.so;/usr/lib/libddsconf.so;/usr/lib/libddsdatabase.so;/usr/lib/libddsi2.so;/usr/lib/libddskernel.so;/usr/lib/libddsosnet.so;/usr/lib/libddsos.so;/usr/lib/libddsserialization.so;/usr/lib/libddsuser.so;/usr/lib/libddsutil.so;/usr/lib/libdurability.so;/usr/lib/libspliced.so;/usr/lib/libdcpssacpp.so")
set(_exported_library_names "")

# find_library() targets relative to this CMake file
# and add the libraries to adas_pipeline_LIBRARIES
if(NOT "${_exported_library_targets} " STREQUAL " ")
  # loop over library targets
  # but remember related build configuration keyword if available
  list(LENGTH _exported_library_targets _length)
  set(_i 0)
  while(_i LESS _length)
    list(GET _exported_library_targets ${_i} _arg)
    if("${_arg}" MATCHES "^debug|optimized|general$")
      # remember build configuration keyword
      # and get following library target
      set(_cfg "${_arg}")
      math(EXPR _i "${_i} + 1")
      if(_i EQUAL _length)
        message(FATAL_ERROR "Package 'adas_pipeline' passes the build configuration keyword '${_cfg}' as the last exported target")
      endif()
      list(GET _exported_library_targets ${_i} _library_target)
    else()
      # the value is a library target without a build configuration keyword
      set(_cfg "")
      set(_library_target "${_arg}")
    endif()
    math(EXPR _i "${_i} + 1")

    # search for library relative to this CMake file
    set(_lib "NOTFOUND")
    find_library(
      _lib NAMES "${_library_target}"
      PATHS "${adas_pipeline_DIR}/../../../lib"
      NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH
    )

    if(NOT _lib)
      # warn about not existing library and ignore it
      message(FATAL_ERROR "Package 'adas_pipeline' exports the library '${_library_target}' which couldn't be found")
    elseif(NOT IS_ABSOLUTE "${_lib}")
      # the found library must be an absolute path
      message(FATAL_ERROR "Package 'adas_pipeline' found the library '${_library_target}' at '${_lib}' which is not an absolute path")
    elseif(NOT EXISTS "${_lib}")
      # the found library must exist
      message(FATAL_ERROR "Package 'adas_pipeline' found the library '${_lib}' which doesn't exist")
    else()
      list(APPEND adas_pipeline_LIBRARIES ${_cfg} "${_lib}")
    endif()
  endwhile()
endif()

# append absolute libraries to adas_pipeline_LIBRARIES
if(NOT "${_exported_absolute_libraries} " STREQUAL " ")
  # loop over absolute libraries
  # but remember related build configuration keyword if available
  list(LENGTH _exported_absolute_libraries _length)
  set(_i 0)
  while(_i LESS _length)
    list(GET _exported_absolute_libraries ${_i} _arg)
    if("${_arg}" MATCHES "^debug|optimized|general$")
      # remember build configuration keyword
      # and get following absolute library
      set(_cfg "${_arg}")
      math(EXPR _i "${_i} + 1")
      if(_i EQUAL _length)
        message(FATAL_ERROR "Package 'adas_pipeline' passes the build configuration keyword '${_cfg}' as the last exported target")
      endif()
      list(GET _exported_absolute_libraries ${_i} _absolute_library)
    else()
      # the value is an absolute library without a build configuration keyword
      set(_cfg "")
      set(_absolute_library "${_arg}")
    endif()
    math(EXPR _i "${_i} + 1")

    if(NOT EXISTS "${_absolute_library}")
      # the found library must exist
      message(WARNING "Package 'adas_pipeline' exports the library '${_absolute_library}' which doesn't exist")
    else()
      list(APPEND adas_pipeline_LIBRARIES ${_cfg} "${_absolute_library}")
    endif()
  endwhile()
endif()

# find_library() library names with optional LIBRARY_DIRS
# and add the libraries to adas_pipeline_LIBRARIES
if(NOT "${_exported_library_names} " STREQUAL " ")
  # loop over library names
  # but remember related build configuration keyword if available
  list(LENGTH _exported_library_names _length)
  set(_i 0)
  while(_i LESS _length)
    list(GET _exported_library_names ${_i} _arg)
    if("${_arg}" MATCHES "^debug|optimized|general$")
      # remember build configuration keyword
      # and get following library name
      set(_cfg "${_arg}")
      math(EXPR _i "${_i} + 1")
      if(_i EQUAL _length)
        message(FATAL_ERROR "Package 'adas_pipeline' passes the build configuration keyword '${_cfg}' as the last exported target")
      endif()
      list(GET _exported_library_names ${_i} _library)
    else()
      # the value is a library target without a build configuration keyword
      set(_cfg "")
      set(_library "${_arg}")
    endif()
    math(EXPR _i "${_i} + 1")

    # extract optional LIBRARY_DIRS from library name
    string(REPLACE ":" ";" _library_dirs "${_library}")
    list(GET _library_dirs 0 _library_name)
    list(REMOVE_AT _library_dirs 0)

    set(_lib "NOTFOUND")
    if(NOT _library_dirs)
      # search for library in the common locations
      find_library(
        _lib
        NAMES "${_library_name}"
      )
      if(NOT _lib)
        # warn about not existing library and later ignore it
        message(WARNING "Package 'adas_pipeline' exports library '${_library_name}' which couldn't be found")
      endif()
    else()
      # search for library in the specified directories
      find_library(
        _lib
        NAMES "${_library_name}"
        PATHS ${_library_dirs}
        NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH
      )
      if(NOT _lib)
        # warn about not existing library and later ignore it
        message(WARNING "Package 'adas_pipeline' exports library '${_library_name}' with LIBRARY_DIRS '${_library_dirs}' which couldn't be found")
      endif()
    endif()
    if(_lib)
      list(APPEND adas_pipeline_LIBRARIES ${_cfg} "${_lib}")
    endif()
  endwhile()
endif()

# deduplicate adas_pipeline_LIBRARIES
# while maintaining library order
# as well as build configuration keywords
# TODO

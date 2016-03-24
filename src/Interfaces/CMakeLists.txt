cmake_minimum_required(VERSION 2.8.3)

project(adas_interfaces)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
endif()

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/SourceParameters.msg"
  "msg/LDWParameters.msg"
  DEPENDENCIES builtin_interfaces
)

ament_package()

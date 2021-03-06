cmake_minimum_required(VERSION 2.8.3)

project(adas_pipeline)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rmw REQUIRED)
find_package(rmw_implementation_cmake REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
find_package(GLIB COMPONENTS gio gobject gmodule gthread REQUIRED)
find_package(GStreamer COMPONENTS gstreamer-app REQUIRED)
find_package(X11 REQUIRED)
find_package(ZeroMQ REQUIRED)
find_package(CUDA REQUIRED)
find_package(Protobuf REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(adas_interfaces REQUIRED)



include_directories(include ${Boost_INCLUDE_DIRS} ${GSTREAMER_BASE_INCLUDE_DIRS} ${GSTREAMER_INCLUDE_DIRS} )

link_directories(${GSTREAMER_LIBRARIES})

FILE(GLOB_RECURSE SRCS_LaneDetect LDW/LaneDetector/*.cpp LDW/LaneDetector/*.cc LDW/LaneDetector/*.c )


 # A single program that builds the complete pipeline for ADAS
 
 add_executable(ADAS_Pipeline_Manager
  ADAS_Pipeline_Manager.cpp LDW/Process_LaneDetectorSim.cpp Aux/adasdebugapplication.pb.cc 	
  ${SRCS_LaneDetect})

 ament_target_dependencies(ADAS_Pipeline_Manager
   				"rclcpp"
   				"std_msgs"
    			        "example_interfaces"
				"adas_interfaces"
   				"sensor_msgs"
    			        "OpenCV"			
    			)
  target_link_libraries(ADAS_Pipeline_Manager ${Boost_LIBRARIES} ${GSTREAMER_LIBRARIES} ${GLIB_LIBRARIES} ${GLIB_GOBJECT_LIBRARIES} ${GLIB_GIO_LIBRARIES} ${GLIB_GMODULE_LIBRARIES} ${GLIB_GTHREAD_LIBRARIES} ${OpenCV_LIBS} ${CUDA_LIBS} ${GSTREAMER_APP_LIBRARIES} ${X11_LIBRARIES} ${ZeroMQ_LIBRARIES} ${PROTOBUF_LIBRARY}  )
     
  
 
  install(TARGETS   
    ADAS_Pipeline_Manager
    DESTINATION bin)


#call_for_each_rmw_implementation(targets GENERATE_DEFAULT)

ament_package()

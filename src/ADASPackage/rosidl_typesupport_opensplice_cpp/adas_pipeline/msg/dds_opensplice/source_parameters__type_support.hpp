// generated from rosidl_typesupport_opensplice_cpp/resource/msg__type_support.hpp.template

#ifndef __adas_pipeline__msg__dds_opensplice__source_parameters__type_support__hpp__
#define __adas_pipeline__msg__dds_opensplice__source_parameters__type_support__hpp__

#include "adas_pipeline/msg/source_parameters__struct.hpp"
#include "adas_pipeline/msg/dds_opensplice/ccpp_SourceParameters_.h"
#include "adas_pipeline/msg/dds_opensplice/visibility_control.h"

namespace DDS
{
class DomainParticipant;
class DataReader;
class DataWriter;
}  // namespace DDS

namespace adas_pipeline
{

namespace msg
{

namespace typesupport_opensplice_cpp
{

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_adas_pipeline
extern void register_type__SourceParameters(
  DDS::DomainParticipant * participant,
  const char * type_name);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_adas_pipeline
extern void convert_ros_message_to_dds(
  const adas_pipeline::msg::SourceParameters& ros_message,
  adas_pipeline::msg::dds_::SourceParameters_& dds_message);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_adas_pipeline
extern void publish__SourceParameters(
  DDS::DataWriter * topic_writer,
  const void * untyped_ros_message);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_adas_pipeline
extern void convert_dds_message_to_ros(
  const adas_pipeline::msg::dds_::SourceParameters_& dds_message,
  adas_pipeline::msg::SourceParameters& ros_message);

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_PUBLIC_adas_pipeline
extern bool take__SourceParameters(
  DDS::DataReader * topic_reader,
  bool ignore_local_publications,
  void * untyped_ros_message,
  bool * taken);

}  // namespace typesupport_opensplice_cpp

}  // namespace msg

}  // namespace adas_pipeline

#endif  // __adas_pipeline__msg__dds_opensplice__source_parameters__type_support__hpp__

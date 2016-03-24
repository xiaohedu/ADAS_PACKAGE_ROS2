// generated from rosidl_typesupport_opensplice_cpp/resource/msg__type_support.cpp.template

#include <limits>
#include <stdexcept>

#include <u_instanceHandle.h>

#include <rosidl_generator_c/message_type_support.h>
// this is defined in the rosidl_typesupport_opensplice_cpp package and
// is in the include/rosidl_typesupport_opensplice_cpp/impl folder
#include <rosidl_generator_cpp/message_type_support.hpp>
#include <rosidl_typesupport_opensplice_cpp/visibility_control.h>

#include "adas_pipeline/msg/source_parameters__struct.hpp"
#include "adas_pipeline/msg/dds_opensplice/source_parameters__type_support.hpp"
#include "adas_pipeline/msg/dds_opensplice/ccpp_SourceParameters_.h"
#include "rosidl_typesupport_opensplice_cpp/identifier.hpp"
#include <rosidl_typesupport_opensplice_cpp/message_type_support.h>

// forward declaration of message dependencies and their conversion functions

namespace adas_pipeline
{

namespace msg
{

namespace typesupport_opensplice_cpp
{

using __dds_msg_type = adas_pipeline::msg::dds_::SourceParameters_;
using __ros_msg_type = adas_pipeline::msg::SourceParameters;

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_adas_pipeline
const char *
register_type__SourceParameters(
  void * untyped_participant,
  const char * type_name)
{
  if (!untyped_participant) {
    return "untyped participant handle is null";
  }
  if (!type_name) {
    return "type name handle is null";
  }
  DDS::DomainParticipant * participant =
    static_cast<DDS::DomainParticipant *>(untyped_participant);

  adas_pipeline::msg::dds_::SourceParameters_TypeSupport type_support;
  DDS::ReturnCode_t status = type_support.register_type(participant, type_name);
  switch (status) {
    case DDS::RETCODE_ERROR:
      return "adas_pipeline::msg::dds_::SourceParameters_TypeSupport.register_type: "
             "an internal error has occurred";
    case DDS::RETCODE_BAD_PARAMETER:
      return "adas_pipeline::msg::dds_::SourceParameters_TypeSupport.register_type: "
             "bad domain participant or type name parameter";
    case DDS::RETCODE_OUT_OF_RESOURCES:
      return "adas_pipeline::msg::dds_::SourceParameters_TypeSupport.register_type: "
             "out of resources";
    case DDS::RETCODE_PRECONDITION_NOT_MET:
      return "adas_pipeline::msg::dds_::SourceParameters_TypeSupport.register_type: "
             "already registered with a different TypeSupport class";
    case DDS::RETCODE_OK:
      return nullptr;
    default:
      return "adas_pipeline::msg::dds_::SourceParameters_TypeSupport.register_type: unknown return code";
  }
}

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_adas_pipeline
void
convert_ros_message_to_dds(const __ros_msg_type & ros_message, __dds_msg_type & dds_message)
{
  // field.name inputmode
  dds_message.inputmode_ = ros_message.inputmode;

  // field.name device
  dds_message.device_ = ros_message.device;

  // field.name dir
  dds_message.dir_ = ros_message.dir.c_str();

  // field.name fps
  dds_message.fps_ = ros_message.fps;

  // field.name paused
  dds_message.paused_ = ros_message.paused;

}

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_adas_pipeline
const char *
publish__SourceParameters(
  void * untyped_topic_writer,
  const void * untyped_ros_message)
{
  DDS::DataWriter * topic_writer = static_cast<DDS::DataWriter *>(untyped_topic_writer);

  const __ros_msg_type & ros_message = *(const __ros_msg_type *)untyped_ros_message;
  __dds_msg_type dds_message;
  convert_ros_message_to_dds(ros_message, dds_message);

  adas_pipeline::msg::dds_::SourceParameters_DataWriter * data_writer =
    adas_pipeline::msg::dds_::SourceParameters_DataWriter::_narrow(topic_writer);
  DDS::ReturnCode_t status = data_writer->write(dds_message, DDS::HANDLE_NIL);
  switch (status) {
    case DDS::RETCODE_ERROR:
      return "adas_pipeline::msg::dds_::SourceParameters_DataWriter.write: "
             "an internal error has occurred";
    case DDS::RETCODE_BAD_PARAMETER:
      return "adas_pipeline::msg::dds_::SourceParameters_DataWriter.write: "
             "bad handle or instance_data parameter";
    case DDS::RETCODE_ALREADY_DELETED:
      return "adas_pipeline::msg::dds_::SourceParameters_DataWriter.write: "
             "this adas_pipeline::msg::dds_::SourceParameters_DataWriter has already been deleted";
    case DDS::RETCODE_OUT_OF_RESOURCES:
      return "adas_pipeline::msg::dds_::SourceParameters_DataWriter.write: "
             "out of resources";
    case DDS::RETCODE_NOT_ENABLED:
      return "adas_pipeline::msg::dds_::SourceParameters_DataWriter.write: "
             "this adas_pipeline::msg::dds_::SourceParameters_DataWriter is not enabled";
    case DDS::RETCODE_PRECONDITION_NOT_MET:
      return "adas_pipeline::msg::dds_::SourceParameters_DataWriter.write: "
             "the handle has not been registered with this adas_pipeline::msg::dds_::SourceParameters_DataWriter";
    case DDS::RETCODE_TIMEOUT:
      return "adas_pipeline::msg::dds_::SourceParameters_DataWriter.write: "
             "writing resulted in blocking and then exceeded the timeout set by the "
             "max_blocking_time of the ReliabilityQosPolicy";
    case DDS::RETCODE_OK:
      return nullptr;
    default:
      return "adas_pipeline::msg::dds_::SourceParameters_DataWriter.write: unknown return code";
  }
}

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_adas_pipeline
void
convert_dds_message_to_ros(const __dds_msg_type & dds_message, __ros_msg_type & ros_message)
{
  // field.name inputmode
  ros_message.inputmode =
    dds_message.inputmode_;

  // field.name device
  ros_message.device =
    dds_message.device_;

  // field.name dir
  ros_message.dir =
    dds_message.dir_;

  // field.name fps
  ros_message.fps =
    dds_message.fps_;

  // field.name paused
  ros_message.paused =
    dds_message.paused_ == TRUE;

}

ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT_adas_pipeline
const char *
take__SourceParameters(
  void * untyped_topic_reader,
  bool ignore_local_publications,
  void * untyped_ros_message,
  bool * taken,
  void * sending_publication_handle)
{
  if (untyped_ros_message == 0) {
    return "invalid ros message pointer";
  };

  DDS::DataReader * topic_reader = static_cast<DDS::DataReader*>(untyped_topic_reader);

  adas_pipeline::msg::dds_::SourceParameters_DataReader * data_reader =
    adas_pipeline::msg::dds_::SourceParameters_DataReader::_narrow(topic_reader);

  adas_pipeline::msg::dds_::SourceParameters_Seq dds_messages;
  DDS::SampleInfoSeq sample_infos;
  DDS::ReturnCode_t status = data_reader->take(
    dds_messages,
    sample_infos,
    1,
    DDS::ANY_SAMPLE_STATE,
    DDS::ANY_VIEW_STATE,
    DDS::ANY_INSTANCE_STATE);

  const char * errs = nullptr;
  bool ignore_sample = false;

  switch (status) {
    case DDS::RETCODE_ERROR:
      errs = "adas_pipeline::msg::dds_::SourceParameters_DataReader.take: "
             "an internal error has occurred";
      goto finally;
    case DDS::RETCODE_ALREADY_DELETED:
      errs = "adas_pipeline::msg::dds_::SourceParameters_DataReader.take: "
             "this adas_pipeline::msg::dds_::SourceParameters_DataReader has already been deleted";
      goto finally;
    case DDS::RETCODE_OUT_OF_RESOURCES:
      errs = "adas_pipeline::msg::dds_::SourceParameters_DataReader.take: "
             "out of resources";
      goto finally;
    case DDS::RETCODE_NOT_ENABLED:
      errs = "adas_pipeline::msg::dds_::SourceParameters_DataReader.take: "
             "this adas_pipeline::msg::dds_::SourceParameters_DataReader is not enabled";
      goto finally;
    case DDS::RETCODE_PRECONDITION_NOT_MET:
      errs = "adas_pipeline::msg::dds_::SourceParameters_DataReader.take: "
             "a precondition is not met, one of: "
             "max_samples > maximum and max_samples != LENGTH_UNLIMITED, or "
             "the two sequences do not have matching parameters (length, maximum, release), or "
             "maximum > 0 and release is false.";
      goto finally;
    case DDS::RETCODE_NO_DATA:
      *taken = false;
      errs = nullptr;
      goto finally;
    case DDS::RETCODE_OK:
      break;
    default:
      errs = "adas_pipeline::msg::dds_::SourceParameters_DataReader.take: unknown return code";
      goto finally;
  }

  {
    DDS::SampleInfo & sample_info = sample_infos[0];
    if (!sample_info.valid_data) {
      // skip sample without data
      ignore_sample = true;
    } else {
      DDS::InstanceHandle_t sender_handle = sample_info.publication_handle;
      auto sender_gid = u_instanceHandleToGID(sender_handle);
      if (ignore_local_publications) {
        // compare the system id from the sender and this receiver
        // if they are equal the sample has been sent from this process and should be ignored
        DDS::InstanceHandle_t receiver_handle = topic_reader->get_instance_handle();
        auto receiver_gid = u_instanceHandleToGID(receiver_handle);
        ignore_sample = sender_gid.systemId == receiver_gid.systemId;
      }
      // This is nullptr when being used with plain rmw_take, so check first.
      if (sending_publication_handle) {
        *static_cast<DDS::InstanceHandle_t *>(sending_publication_handle) = sender_handle;
      }
    }
  }

  if (!ignore_sample) {
    __ros_msg_type & ros_message = *(__ros_msg_type *)untyped_ros_message;
    convert_dds_message_to_ros(dds_messages[0], ros_message);
    *taken = true;
  } else {
    *taken = false;
  }

finally:
  // Ensure the loan is returned.
  status = data_reader->return_loan(dds_messages, sample_infos);
  switch (status) {
    case DDS::RETCODE_ERROR:
      return "adas_pipeline::msg::dds_::SourceParameters_DataReader.return_loan: "
             "an internal error has occurred";
    case DDS::RETCODE_ALREADY_DELETED:
      return "adas_pipeline::msg::dds_::SourceParameters_DataReader.return_loan: "
             "this adas_pipeline::msg::dds_::SourceParameters_DataReader has already been deleted";
    case DDS::RETCODE_OUT_OF_RESOURCES:
      return "adas_pipeline::msg::dds_::SourceParameters_DataReader.return_loan: "
             "out of resources";
    case DDS::RETCODE_NOT_ENABLED:
      return "adas_pipeline::msg::dds_::SourceParameters_DataReader.return_loan: "
             "this adas_pipeline::msg::dds_::SourceParameters_DataReader is not enabled";
    case DDS::RETCODE_PRECONDITION_NOT_MET:
      return "adas_pipeline::msg::dds_::SourceParameters_DataReader.return_loan: "
             "a precondition is not met, one of: "
             "the data_values and info_seq do not belong to a single related pair, or "
             "the data_values and info_seq were not obtained from this "
             "adas_pipeline::msg::dds_::SourceParameters_DataReader";
    case DDS::RETCODE_OK:
      return nullptr;
    default:
      return "adas_pipeline::msg::dds_::SourceParameters_DataReader.return_loan failed with "
             "unknown return code";
  }

  return errs;
}

static message_type_support_callbacks_t callbacks = {
  "adas_pipeline",
  "SourceParameters",
  &register_type__SourceParameters,
  &publish__SourceParameters,
  &take__SourceParameters
};

static rosidl_message_type_support_t handle = {
  rosidl_typesupport_opensplice_cpp::typesupport_opensplice_identifier,
  &callbacks
};

}  // namespace typesupport_opensplice_cpp

}  // namespace msg

}  // namespace adas_pipeline

namespace rosidl_typesupport_opensplice_cpp
{

template<>
ROSIDL_TYPESUPPORT_OPENSPLICE_CPP_EXPORT
const rosidl_message_type_support_t *
get_message_type_support_handle_opensplice<
  adas_pipeline::msg::SourceParameters
>()
{
  return &adas_pipeline::msg::typesupport_opensplice_cpp::handle;
}

}  // namespace rosidl_typesupport_opensplice_cpp

// generated from rosidl_generator_cpp/resource/msg__struct.hpp.template
// generated code does not contain a copyright notice

#ifndef ADAS_PIPELINE__MSG__SOURCE_PARAMETERS__STRUCT_HPP_
#define ADAS_PIPELINE__MSG__SOURCE_PARAMETERS__STRUCT_HPP_

#include <array>
#include <memory>
#include <string>
#include <vector>

// include message dependencies

#ifndef _WIN32
# define DEPRECATED_adas_pipeline_msg_SourceParameters __attribute__((deprecated))
#else
# define DEPRECATED_adas_pipeline_msg_SourceParameters __declspec(deprecated)
#endif

namespace adas_pipeline
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SourceParameters_
{
  using Type = SourceParameters_<ContainerAllocator>;

  SourceParameters_()
  {
  }
  explicit SourceParameters_(const ContainerAllocator & _alloc)
  {
    (void)_alloc;
  }

  // field types and members
  using _inputmode_type =
      int32_t;
  _inputmode_type inputmode;
  using _device_type =
      int32_t;
  _device_type device;
  using _dir_type =
      std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _dir_type dir;
  using _fps_type =
      float;
  _fps_type fps;
  using _paused_type =
      bool;
  _paused_type paused;

  // setters for named parameter idiom
  Type * set__inputmode(
    const int32_t & _arg)
  {
    this->inputmode = _arg;
    return this;
  }
  Type * set__device(
    const int32_t & _arg)
  {
    this->device = _arg;
    return this;
  }
  Type * set__dir(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->dir = _arg;
    return this;
  }
  Type * set__fps(
    const float & _arg)
  {
    this->fps = _arg;
    return this;
  }
  Type * set__paused(
    const bool & _arg)
  {
    this->paused = _arg;
    return this;
  }

  // constants

  // pointer types
  using RawPtr =
    adas_pipeline::msg::SourceParameters_<ContainerAllocator> *;
  using ConstRawPtr =
    const adas_pipeline::msg::SourceParameters_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<adas_pipeline::msg::SourceParameters_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<adas_pipeline::msg::SourceParameters_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
    adas_pipeline::msg::SourceParameters_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<adas_pipeline::msg::SourceParameters_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
    adas_pipeline::msg::SourceParameters_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<adas_pipeline::msg::SourceParameters_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<adas_pipeline::msg::SourceParameters_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<adas_pipeline::msg::SourceParameters_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED_adas_pipeline_msg_SourceParameters
    std::shared_ptr<adas_pipeline::msg::SourceParameters_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED_adas_pipeline_msg_SourceParameters
    std::shared_ptr<adas_pipeline::msg::SourceParameters_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SourceParameters_ & other) const
  {
    if (this->inputmode != other.inputmode) {
      return false;
    }
    if (this->device != other.device) {
      return false;
    }
    if (this->dir != other.dir) {
      return false;
    }
    if (this->fps != other.fps) {
      return false;
    }
    if (this->paused != other.paused) {
      return false;
    }
    return true;
  }
  bool operator!=(const SourceParameters_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SourceParameters_

// alias to use template instance with default allocator
using SourceParameters =
    adas_pipeline::msg::SourceParameters_<std::allocator<void>>;

// constants requiring out of line definition

}  // namespace msg

}  // namespace adas_pipeline

#endif  // ADAS_PIPELINE__MSG__SOURCE_PARAMETERS__STRUCT_HPP_

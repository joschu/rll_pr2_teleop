/* Auto-generated by genmsg_cpp for file /home/joschu/Dropbox/myros/sixense/msg/CalibPaddle.msg */
#ifndef SIXENSE_MESSAGE_CALIBPADDLE_H
#define SIXENSE_MESSAGE_CALIBPADDLE_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "geometry_msgs/Transform.h"

namespace sixense
{
template <class ContainerAllocator>
struct CalibPaddle_ {
  typedef CalibPaddle_<ContainerAllocator> Type;

  CalibPaddle_()
  : transform()
  , buttons()
  , joy()
  , trigger(0.0)
  {
    buttons.assign(false);
    joy.assign(0.0);
  }

  CalibPaddle_(const ContainerAllocator& _alloc)
  : transform(_alloc)
  , buttons()
  , joy()
  , trigger(0.0)
  {
    buttons.assign(false);
    joy.assign(0.0);
  }

  typedef  ::geometry_msgs::Transform_<ContainerAllocator>  _transform_type;
   ::geometry_msgs::Transform_<ContainerAllocator>  transform;

  typedef boost::array<uint8_t, 7>  _buttons_type;
  boost::array<uint8_t, 7>  buttons;

  typedef boost::array<float, 2>  _joy_type;
  boost::array<float, 2>  joy;

  typedef float _trigger_type;
  float trigger;


  ROS_DEPRECATED uint32_t get_buttons_size() const { return (uint32_t)buttons.size(); }
  ROS_DEPRECATED uint32_t get_joy_size() const { return (uint32_t)joy.size(); }
private:
  static const char* __s_getDataType_() { return "sixense/CalibPaddle"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "9aa188f8a684b5f86f071eb093833ed5"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "geometry_msgs/Transform transform\n\
bool[7] buttons\n\
float32[2] joy\n\
float32 trigger\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Transform\n\
# This represents the transform between two coordinate frames in free space.\n\
\n\
Vector3 translation\n\
Quaternion rotation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, transform);
    ros::serialization::serialize(stream, buttons);
    ros::serialization::serialize(stream, joy);
    ros::serialization::serialize(stream, trigger);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, transform);
    ros::serialization::deserialize(stream, buttons);
    ros::serialization::deserialize(stream, joy);
    ros::serialization::deserialize(stream, trigger);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(transform);
    size += ros::serialization::serializationLength(buttons);
    size += ros::serialization::serializationLength(joy);
    size += ros::serialization::serializationLength(trigger);
    return size;
  }

  typedef boost::shared_ptr< ::sixense::CalibPaddle_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::sixense::CalibPaddle_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct CalibPaddle
typedef  ::sixense::CalibPaddle_<std::allocator<void> > CalibPaddle;

typedef boost::shared_ptr< ::sixense::CalibPaddle> CalibPaddlePtr;
typedef boost::shared_ptr< ::sixense::CalibPaddle const> CalibPaddleConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::sixense::CalibPaddle_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::sixense::CalibPaddle_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace sixense

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::sixense::CalibPaddle_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::sixense::CalibPaddle_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::sixense::CalibPaddle_<ContainerAllocator> > {
  static const char* value() 
  {
    return "9aa188f8a684b5f86f071eb093833ed5";
  }

  static const char* value(const  ::sixense::CalibPaddle_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x9aa188f8a684b5f8ULL;
  static const uint64_t static_value2 = 0x6f071eb093833ed5ULL;
};

template<class ContainerAllocator>
struct DataType< ::sixense::CalibPaddle_<ContainerAllocator> > {
  static const char* value() 
  {
    return "sixense/CalibPaddle";
  }

  static const char* value(const  ::sixense::CalibPaddle_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::sixense::CalibPaddle_<ContainerAllocator> > {
  static const char* value() 
  {
    return "geometry_msgs/Transform transform\n\
bool[7] buttons\n\
float32[2] joy\n\
float32 trigger\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Transform\n\
# This represents the transform between two coordinate frames in free space.\n\
\n\
Vector3 translation\n\
Quaternion rotation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space. \n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
\n\
";
  }

  static const char* value(const  ::sixense::CalibPaddle_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::sixense::CalibPaddle_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::sixense::CalibPaddle_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.transform);
    stream.next(m.buttons);
    stream.next(m.joy);
    stream.next(m.trigger);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct CalibPaddle_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sixense::CalibPaddle_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::sixense::CalibPaddle_<ContainerAllocator> & v) 
  {
    s << indent << "transform: ";
s << std::endl;
    Printer< ::geometry_msgs::Transform_<ContainerAllocator> >::stream(s, indent + "  ", v.transform);
    s << indent << "buttons[]" << std::endl;
    for (size_t i = 0; i < v.buttons.size(); ++i)
    {
      s << indent << "  buttons[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.buttons[i]);
    }
    s << indent << "joy[]" << std::endl;
    for (size_t i = 0; i < v.joy.size(); ++i)
    {
      s << indent << "  joy[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.joy[i]);
    }
    s << indent << "trigger: ";
    Printer<float>::stream(s, indent + "  ", v.trigger);
  }
};


} // namespace message_operations
} // namespace ros

#endif // SIXENSE_MESSAGE_CALIBPADDLE_H


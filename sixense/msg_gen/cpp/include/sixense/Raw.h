/* Auto-generated by genmsg_cpp for file /home/joschu/Dropbox/myros/sixense/msg/Raw.msg */
#ifndef SIXENSE_MESSAGE_RAW_H
#define SIXENSE_MESSAGE_RAW_H
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

#include "std_msgs/Header.h"

namespace sixense
{
template <class ContainerAllocator>
struct Raw_ {
  typedef Raw_<ContainerAllocator> Type;

  Raw_()
  : header()
  , pos()
  , quat()
  , buttons()
  , analog()
  {
    pos.assign(0);
    quat.assign(0);
    buttons.assign(0);
    analog.assign(0);
  }

  Raw_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , pos()
  , quat()
  , buttons()
  , analog()
  {
    pos.assign(0);
    quat.assign(0);
    buttons.assign(0);
    analog.assign(0);
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef boost::array<int16_t, 6>  _pos_type;
  boost::array<int16_t, 6>  pos;

  typedef boost::array<int16_t, 8>  _quat_type;
  boost::array<int16_t, 8>  quat;

  typedef boost::array<uint8_t, 2>  _buttons_type;
  boost::array<uint8_t, 2>  buttons;

  typedef boost::array<int16_t, 6>  _analog_type;
  boost::array<int16_t, 6>  analog;


  ROS_DEPRECATED uint32_t get_pos_size() const { return (uint32_t)pos.size(); }
  ROS_DEPRECATED uint32_t get_quat_size() const { return (uint32_t)quat.size(); }
  ROS_DEPRECATED uint32_t get_buttons_size() const { return (uint32_t)buttons.size(); }
  ROS_DEPRECATED uint32_t get_analog_size() const { return (uint32_t)analog.size(); }
private:
  static const char* __s_getDataType_() { return "sixense/Raw"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "abda63674ce89e542bda766f5d8939f7"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "Header header\n\
int16[6] pos\n\
int16[8] quat\n\
uint8[2] buttons\n\
int16[6] analog\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, header);
    ros::serialization::serialize(stream, pos);
    ros::serialization::serialize(stream, quat);
    ros::serialization::serialize(stream, buttons);
    ros::serialization::serialize(stream, analog);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, header);
    ros::serialization::deserialize(stream, pos);
    ros::serialization::deserialize(stream, quat);
    ros::serialization::deserialize(stream, buttons);
    ros::serialization::deserialize(stream, analog);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(header);
    size += ros::serialization::serializationLength(pos);
    size += ros::serialization::serializationLength(quat);
    size += ros::serialization::serializationLength(buttons);
    size += ros::serialization::serializationLength(analog);
    return size;
  }

  typedef boost::shared_ptr< ::sixense::Raw_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::sixense::Raw_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct Raw
typedef  ::sixense::Raw_<std::allocator<void> > Raw;

typedef boost::shared_ptr< ::sixense::Raw> RawPtr;
typedef boost::shared_ptr< ::sixense::Raw const> RawConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::sixense::Raw_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::sixense::Raw_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace sixense

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::sixense::Raw_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::sixense::Raw_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::sixense::Raw_<ContainerAllocator> > {
  static const char* value() 
  {
    return "abda63674ce89e542bda766f5d8939f7";
  }

  static const char* value(const  ::sixense::Raw_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xabda63674ce89e54ULL;
  static const uint64_t static_value2 = 0x2bda766f5d8939f7ULL;
};

template<class ContainerAllocator>
struct DataType< ::sixense::Raw_<ContainerAllocator> > {
  static const char* value() 
  {
    return "sixense/Raw";
  }

  static const char* value(const  ::sixense::Raw_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::sixense::Raw_<ContainerAllocator> > {
  static const char* value() 
  {
    return "Header header\n\
int16[6] pos\n\
int16[8] quat\n\
uint8[2] buttons\n\
int16[6] analog\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
";
  }

  static const char* value(const  ::sixense::Raw_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::sixense::Raw_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::sixense::Raw_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::sixense::Raw_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.pos);
    stream.next(m.quat);
    stream.next(m.buttons);
    stream.next(m.analog);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Raw_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sixense::Raw_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::sixense::Raw_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "pos[]" << std::endl;
    for (size_t i = 0; i < v.pos.size(); ++i)
    {
      s << indent << "  pos[" << i << "]: ";
      Printer<int16_t>::stream(s, indent + "  ", v.pos[i]);
    }
    s << indent << "quat[]" << std::endl;
    for (size_t i = 0; i < v.quat.size(); ++i)
    {
      s << indent << "  quat[" << i << "]: ";
      Printer<int16_t>::stream(s, indent + "  ", v.quat[i]);
    }
    s << indent << "buttons[]" << std::endl;
    for (size_t i = 0; i < v.buttons.size(); ++i)
    {
      s << indent << "  buttons[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.buttons[i]);
    }
    s << indent << "analog[]" << std::endl;
    for (size_t i = 0; i < v.analog.size(); ++i)
    {
      s << indent << "  analog[" << i << "]: ";
      Printer<int16_t>::stream(s, indent + "  ", v.analog[i]);
    }
  }
};


} // namespace message_operations
} // namespace ros

#endif // SIXENSE_MESSAGE_RAW_H


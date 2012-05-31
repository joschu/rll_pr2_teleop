; Auto-generated. Do not edit!


(cl:in-package sixense-msg)


;//! \htmlinclude Calib.msg.html

(cl:defclass <Calib> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (paddles
    :reader paddles
    :initarg :paddles
    :type (cl:vector sixense-msg:CalibPaddle)
   :initform (cl:make-array 2 :element-type 'sixense-msg:CalibPaddle :initial-element (cl:make-instance 'sixense-msg:CalibPaddle))))
)

(cl:defclass Calib (<Calib>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Calib>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Calib)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sixense-msg:<Calib> is deprecated: use sixense-msg:Calib instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Calib>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:header-val is deprecated.  Use sixense-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'paddles-val :lambda-list '(m))
(cl:defmethod paddles-val ((m <Calib>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:paddles-val is deprecated.  Use sixense-msg:paddles instead.")
  (paddles m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Calib>) ostream)
  "Serializes a message object of type '<Calib>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'paddles))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Calib>) istream)
  "Deserializes a message object of type '<Calib>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'paddles) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'paddles)))
    (cl:dotimes (i 2)
    (cl:setf (cl:aref vals i) (cl:make-instance 'sixense-msg:CalibPaddle))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Calib>)))
  "Returns string type for a message object of type '<Calib>"
  "sixense/Calib")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Calib)))
  "Returns string type for a message object of type 'Calib"
  "sixense/Calib")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Calib>)))
  "Returns md5sum for a message object of type '<Calib>"
  "fe7d2498aeb3109f9719aedbc9c48dc3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Calib)))
  "Returns md5sum for a message object of type 'Calib"
  "fe7d2498aeb3109f9719aedbc9c48dc3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Calib>)))
  "Returns full string definition for message of type '<Calib>"
  (cl:format cl:nil "Header header~%CalibPaddle[2] paddles~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sixense/CalibPaddle~%geometry_msgs/Transform transform~%bool[7] buttons~%float32[2] joy~%float32 trigger~%~%================================================================================~%MSG: geometry_msgs/Transform~%# This represents the transform between two coordinate frames in free space.~%~%Vector3 translation~%Quaternion rotation~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Calib)))
  "Returns full string definition for message of type 'Calib"
  (cl:format cl:nil "Header header~%CalibPaddle[2] paddles~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: sixense/CalibPaddle~%geometry_msgs/Transform transform~%bool[7] buttons~%float32[2] joy~%float32 trigger~%~%================================================================================~%MSG: geometry_msgs/Transform~%# This represents the transform between two coordinate frames in free space.~%~%Vector3 translation~%Quaternion rotation~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Calib>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'paddles) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Calib>))
  "Converts a ROS message object to a list"
  (cl:list 'Calib
    (cl:cons ':header (header msg))
    (cl:cons ':paddles (paddles msg))
))

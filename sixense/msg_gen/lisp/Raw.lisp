; Auto-generated. Do not edit!


(cl:in-package sixense-msg)


;//! \htmlinclude Raw.msg.html

(cl:defclass <Raw> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pos
    :reader pos
    :initarg :pos
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 6 :element-type 'cl:fixnum :initial-element 0))
   (quat
    :reader quat
    :initarg :quat
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 8 :element-type 'cl:fixnum :initial-element 0))
   (buttons
    :reader buttons
    :initarg :buttons
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 2 :element-type 'cl:fixnum :initial-element 0))
   (analog
    :reader analog
    :initarg :analog
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 6 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass Raw (<Raw>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Raw>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Raw)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sixense-msg:<Raw> is deprecated: use sixense-msg:Raw instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Raw>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:header-val is deprecated.  Use sixense-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <Raw>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:pos-val is deprecated.  Use sixense-msg:pos instead.")
  (pos m))

(cl:ensure-generic-function 'quat-val :lambda-list '(m))
(cl:defmethod quat-val ((m <Raw>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:quat-val is deprecated.  Use sixense-msg:quat instead.")
  (quat m))

(cl:ensure-generic-function 'buttons-val :lambda-list '(m))
(cl:defmethod buttons-val ((m <Raw>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:buttons-val is deprecated.  Use sixense-msg:buttons instead.")
  (buttons m))

(cl:ensure-generic-function 'analog-val :lambda-list '(m))
(cl:defmethod analog-val ((m <Raw>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:analog-val is deprecated.  Use sixense-msg:analog instead.")
  (analog m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Raw>) ostream)
  "Serializes a message object of type '<Raw>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'pos))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'quat))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'buttons))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'analog))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Raw>) istream)
  "Deserializes a message object of type '<Raw>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:setf (cl:slot-value msg 'pos) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'pos)))
    (cl:dotimes (i 6)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'quat) (cl:make-array 8))
  (cl:let ((vals (cl:slot-value msg 'quat)))
    (cl:dotimes (i 8)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  (cl:setf (cl:slot-value msg 'buttons) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'buttons)))
    (cl:dotimes (i 2)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  (cl:setf (cl:slot-value msg 'analog) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'analog)))
    (cl:dotimes (i 6)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Raw>)))
  "Returns string type for a message object of type '<Raw>"
  "sixense/Raw")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Raw)))
  "Returns string type for a message object of type 'Raw"
  "sixense/Raw")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Raw>)))
  "Returns md5sum for a message object of type '<Raw>"
  "abda63674ce89e542bda766f5d8939f7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Raw)))
  "Returns md5sum for a message object of type 'Raw"
  "abda63674ce89e542bda766f5d8939f7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Raw>)))
  "Returns full string definition for message of type '<Raw>"
  (cl:format cl:nil "Header header~%int16[6] pos~%int16[8] quat~%uint8[2] buttons~%int16[6] analog~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Raw)))
  "Returns full string definition for message of type 'Raw"
  (cl:format cl:nil "Header header~%int16[6] pos~%int16[8] quat~%uint8[2] buttons~%int16[6] analog~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Raw>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'pos) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'quat) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'buttons) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'analog) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Raw>))
  "Converts a ROS message object to a list"
  (cl:list 'Raw
    (cl:cons ':header (header msg))
    (cl:cons ':pos (pos msg))
    (cl:cons ':quat (quat msg))
    (cl:cons ':buttons (buttons msg))
    (cl:cons ':analog (analog msg))
))

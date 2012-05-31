; Auto-generated. Do not edit!


(cl:in-package sixense-msg)


;//! \htmlinclude CalibPaddle.msg.html

(cl:defclass <CalibPaddle> (roslisp-msg-protocol:ros-message)
  ((transform
    :reader transform
    :initarg :transform
    :type geometry_msgs-msg:Transform
    :initform (cl:make-instance 'geometry_msgs-msg:Transform))
   (buttons
    :reader buttons
    :initarg :buttons
    :type (cl:vector cl:boolean)
   :initform (cl:make-array 7 :element-type 'cl:boolean :initial-element cl:nil))
   (joy
    :reader joy
    :initarg :joy
    :type (cl:vector cl:float)
   :initform (cl:make-array 2 :element-type 'cl:float :initial-element 0.0))
   (trigger
    :reader trigger
    :initarg :trigger
    :type cl:float
    :initform 0.0))
)

(cl:defclass CalibPaddle (<CalibPaddle>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CalibPaddle>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CalibPaddle)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name sixense-msg:<CalibPaddle> is deprecated: use sixense-msg:CalibPaddle instead.")))

(cl:ensure-generic-function 'transform-val :lambda-list '(m))
(cl:defmethod transform-val ((m <CalibPaddle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:transform-val is deprecated.  Use sixense-msg:transform instead.")
  (transform m))

(cl:ensure-generic-function 'buttons-val :lambda-list '(m))
(cl:defmethod buttons-val ((m <CalibPaddle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:buttons-val is deprecated.  Use sixense-msg:buttons instead.")
  (buttons m))

(cl:ensure-generic-function 'joy-val :lambda-list '(m))
(cl:defmethod joy-val ((m <CalibPaddle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:joy-val is deprecated.  Use sixense-msg:joy instead.")
  (joy m))

(cl:ensure-generic-function 'trigger-val :lambda-list '(m))
(cl:defmethod trigger-val ((m <CalibPaddle>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader sixense-msg:trigger-val is deprecated.  Use sixense-msg:trigger instead.")
  (trigger m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CalibPaddle>) ostream)
  "Serializes a message object of type '<CalibPaddle>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'transform) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if ele 1 0)) ostream))
   (cl:slot-value msg 'buttons))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'joy))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'trigger))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CalibPaddle>) istream)
  "Deserializes a message object of type '<CalibPaddle>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'transform) istream)
  (cl:setf (cl:slot-value msg 'buttons) (cl:make-array 7))
  (cl:let ((vals (cl:slot-value msg 'buttons)))
    (cl:dotimes (i 7)
    (cl:setf (cl:aref vals i) (cl:not (cl:zerop (cl:read-byte istream))))))
  (cl:setf (cl:slot-value msg 'joy) (cl:make-array 2))
  (cl:let ((vals (cl:slot-value msg 'joy)))
    (cl:dotimes (i 2)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'trigger) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CalibPaddle>)))
  "Returns string type for a message object of type '<CalibPaddle>"
  "sixense/CalibPaddle")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CalibPaddle)))
  "Returns string type for a message object of type 'CalibPaddle"
  "sixense/CalibPaddle")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CalibPaddle>)))
  "Returns md5sum for a message object of type '<CalibPaddle>"
  "9aa188f8a684b5f86f071eb093833ed5")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CalibPaddle)))
  "Returns md5sum for a message object of type 'CalibPaddle"
  "9aa188f8a684b5f86f071eb093833ed5")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CalibPaddle>)))
  "Returns full string definition for message of type '<CalibPaddle>"
  (cl:format cl:nil "geometry_msgs/Transform transform~%bool[7] buttons~%float32[2] joy~%float32 trigger~%~%================================================================================~%MSG: geometry_msgs/Transform~%# This represents the transform between two coordinate frames in free space.~%~%Vector3 translation~%Quaternion rotation~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CalibPaddle)))
  "Returns full string definition for message of type 'CalibPaddle"
  (cl:format cl:nil "geometry_msgs/Transform transform~%bool[7] buttons~%float32[2] joy~%float32 trigger~%~%================================================================================~%MSG: geometry_msgs/Transform~%# This represents the transform between two coordinate frames in free space.~%~%Vector3 translation~%Quaternion rotation~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CalibPaddle>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'transform))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'buttons) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'joy) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CalibPaddle>))
  "Converts a ROS message object to a list"
  (cl:list 'CalibPaddle
    (cl:cons ':transform (transform msg))
    (cl:cons ':buttons (buttons msg))
    (cl:cons ':joy (joy msg))
    (cl:cons ':trigger (trigger msg))
))

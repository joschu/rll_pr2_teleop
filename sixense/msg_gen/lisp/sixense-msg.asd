
(cl:in-package :asdf)

(defsystem "sixense-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "Raw" :depends-on ("_package_Raw"))
    (:file "_package_Raw" :depends-on ("_package"))
    (:file "CalibPaddle" :depends-on ("_package_CalibPaddle"))
    (:file "_package_CalibPaddle" :depends-on ("_package"))
    (:file "Calib" :depends-on ("_package_Calib"))
    (:file "_package_Calib" :depends-on ("_package"))
  ))
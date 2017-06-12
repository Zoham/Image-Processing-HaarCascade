LOCAL_PATH := $(call my-dir)

	include $(CLEAR_VARS)

	#opencv
	OPENCVROOT:= C:\OpenCV-3.2.0-android-sdk
	OPENCV_CAMERA_MODULES:=on
	OPENCV_INSTALL_MODULES:=on
	OPENCV_LIB_TYPE:=SHARED
	OPENCV_CAMERA_MODULES := on OPENCV_INSTALL_MODULES := on
	include ${OPENCVROOT}/sdk/native/jni/OpenCV.mk

	LOCAL_SRC_FILES := edu_hon5037tamu_detection_OpencvClass.cpp

	LOCAL_LDLIBS += -llog
	LOCAL_MODULE := MyOpencvLibs


	include $(BUILD_SHARED_LIBRARY)

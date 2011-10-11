cmake_minimum_required(VERSION 2.8)
PROJECT(coincounter-vcom)
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(wxWidgets COMPONENTS core base adv REQUIRED)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
INCLUDE("${wxWidgets_USE_FILE}")

SET(SRCS main.cpp coincounter_gui.cpp frmMain.cpp frmAbout.cpp imageCanvas.cpp meanshiftsegmentation.cpp)

ADD_EXECUTABLE(coincounter ${SRCS})
TARGET_LINK_LIBRARIES(coincounter ${OpenCV_LIBS} ${wxWidgets_LIBRARIES})

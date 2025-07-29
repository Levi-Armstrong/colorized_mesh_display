cmake_minimum_required(VERSION 3.10)
project(colorized_mesh_display)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(rclcpp REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_msgs REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(rviz_common REQUIRED)

find_package(Qt5 ${rviz_QT_VERSION} EXACT REQUIRED Widgets)
add_definitions(-DQT_NO_KEYWORDS)

###########
## Build ##
###########

## Colorized Mesh Shape Library
add_library(${PROJECT_NAME} SHARED
  include/${PROJECT_NAME}/colorized_mesh_display.h
  src/colorized_mesh_visual.cpp
  src/colorized_mesh_display.cpp
)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Widgets)
target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                                                  "$<INSTALL_INTERFACE:include>")
ament_target_dependencies(${PROJECT_NAME} PUBLIC
  rclcpp
  pcl_conversions
  pcl_msgs
  pcl_ros
  rviz_common)

# Test Node
add_executable(${PROJECT_NAME}_test_node src/colorized_mesh_display_test.cpp)
target_link_libraries(${PROJECT_NAME}_test_node ${PROJECT_NAME})
ament_target_dependencies(${PROJECT_NAME}_test_node
  rclcpp
  pcl_conversions
  pcl_msgs
  pcl_ros
  rviz_common)

#############
## Install ##
#############

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets DESTINATION lib)
ament_export_targets(${PROJECT_NAME}-targets HAS_LIBRARY_TARGET)

# install library
install(
  TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_test_node
  EXPORT ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
  INCLUDES
  DESTINATION include)

install(DIRECTORY icons DESTINATION share/${PROJECT_NAME}/)

pluginlib_export_plugin_description_file(rviz_common plugin_description.xml)
ament_package()

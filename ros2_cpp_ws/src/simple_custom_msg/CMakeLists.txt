cmake_minimum_required(VERSION 3.8)
project(simple_custom_msg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Needed to create custom interfaces (msg / srv)
find_package(rosidl_default_generators REQUIRED)

# C++ nodes
include_directories(include)

add_executable(custom_msg_publisher src/custom_msg_publisher.cpp)
ament_target_dependencies(custom_msg_publisher rclcpp)

install(
  DIRECTORY include
  DESTINATION include
)

install(TARGETS
  custom_msg_publisher
  DESTINATION lib/${PROJECT_NAME}
)

# Custom msg and srv
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/CustomMsg.msg"
)

# Link custom interfaces to nodes (ROS_VERSION >= humble)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(custom_msg_publisher "${cpp_typesupport_target}")


# With foxy uncomment the following lines:
# rosidl_target_interfaces(custom_msg_publisher
#  ${PROJECT_NAME} 'rosidl_typesupport_cpp')


ament_export_dependencies(rosidl_default_runtime)

ament_package()

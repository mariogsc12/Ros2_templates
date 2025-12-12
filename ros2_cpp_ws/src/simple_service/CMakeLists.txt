cmake_minimum_required(VERSION 3.8)
project(simple_service)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

# Needed to declare custom service / msg / action
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/AddTwoInts.srv"
  # DEPENDENCIES geometry_msgs
)

# Create executables
add_executable(client src/client.cpp)
ament_target_dependencies(client rclcpp std_msgs)
add_executable(server src/server.cpp)
ament_target_dependencies(server rclcpp std_msgs)

# Install include folder
include_directories(include)  # Important to found the include folder
install(
  DIRECTORY include
  DESTINATION include
)

# Install executables
install(TARGETS
  client
  server
  DESTINATION lib/${PROJECT_NAME}
)

# If we have nodes and msg / srv in same pkgs we need to link them
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(client "${cpp_typesupport_target}") 
target_link_libraries(server "${cpp_typesupport_target}") 

ament_package()

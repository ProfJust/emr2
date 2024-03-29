cmake_minimum_required(VERSION 3.8)
project(emr2)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# ===>>>>> Add used Librarys ===>>>>
# fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)

add_executable(talkerNode   src/minimal_publisher.cpp)
ament_target_dependencies(talkerNode rclcpp std_msgs)

# ===>>>>> Add Executable and Dependencies ===>>>>
add_executable(listenerNode src/minimal_subscriber.cpp)
ament_target_dependencies(listenerNode rclcpp std_msgs)

add_executable(turtlesim_taste   src/turtlesim_taste.cpp)
ament_target_dependencies(turtlesim_taste rclcpp std_msgs geometry_msgs)

add_executable(hello_moveit_ur  src/hello_moveit_ur.cpp)
ament_target_dependencies(hello_moveit_ur moveit_ros_planning_interface)

target_include_directories(talkerNode PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(talkerNode PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

# ===>>>>> Add target ===>>>>
install(TARGETS talkerNode
                listenerNode
                turtlesim_taste
                hello_moveit_ur
  DESTINATION lib/${PROJECT_NAME})

# ===>>>>> Add Folder for Launch-Files ===>>>>
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

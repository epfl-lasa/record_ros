cmake_minimum_required(VERSION 2.8.3)
project(record_ros)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED roscpp message_generation rosbag std_msgs)
find_package(Boost REQUIRED COMPONENTS regex )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -O3 -std=c++11 -mtune=native -fPIC -Wall")        ## Optimize

add_service_files(
   FILES
   String_cmd.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp message_runtime std_msgs
#  DEPENDS system_lib
)


###########
## Build ##
###########

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


set(HEADER_FILES ${INCLUDE_DIR}/record_ros/record.h )

set(SRC_FILES  ${SRC_DIR}/record.cpp
               ${SRC_DIR}/record_node.cpp
)

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${INCLUDE_DIR}
    ${INCLUDE_STATS}
    ${Boost_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${Boost_REGEX_LIBRARY})


add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencpp ${PROJECT_NAME}_generate_messages_cpp)

cmake_minimum_required(VERSION 3.0.2)
project(mi_prime_paquete)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  turtlesim
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES mi_prime_paquete
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)



add_executable(publicador src/publicador.cpp)
target_link_libraries(publicador  
   ${catkin_LIBRARIES}
)


add_executable(sub_pose src/suscriptor.cpp)
target_link_libraries(sub_pose  
   ${catkin_LIBRARIES}
)

add_executable(pub_sub src/pub_sub.cpp)
target_link_libraries(pub_sub  
   ${catkin_LIBRARIES}
)

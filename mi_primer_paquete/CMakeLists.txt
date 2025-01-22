cmake_minimum_required(VERSION 3.0.2)
project(mi_primer_paquete)


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


# Define un ejecutable llamado "publicador" a partir del archivo fuente "src/publicador.cpp".
add_executable(publicador src/publicador.cpp)

# Especifica las bibliotecas con las que el ejecutable "publicador" debe enlazarse.
# Aquí se enlaza con las bibliotecas definidas en la variable `${catkin_LIBRARIES}`.
# que engloba a todos los paquetes de ROS
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

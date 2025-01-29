cmake_minimum_required(VERSION 3.0.2)
project(proyecto_1)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  nav_msgs
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
add_executable(cuadrado src/cuadrado.cpp)

target_link_libraries(cuadrado  
   ${catkin_LIBRARIES}
)

add_executable(control_angulo src/control_angulo.cpp)

target_link_libraries(control_angulo  
   ${catkin_LIBRARIES}
)


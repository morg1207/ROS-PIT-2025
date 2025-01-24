### Comandos para lanzar este paquete

### Crear espacio de trabajo
```bash
mkdir -p ~/catkin_ws/src
```


#### Clonar repositorio
```bash
cd ~/catkin_ws/src
git clone https://github.com/morg1207/ROS-PIT-2025.git
```

#### Descargar dependencias
```bash
cd ~/catkin_ws 
sudo apt update
rosdep init
rosdep update --rosdistro $ROS_DISTRO
rosdep install -i --from-path src --rosdistro $ROS_DISTRO -y
```

#### Compilar
```bash
cd ~/catkin_ws 
```

#### Lanzar roscore y simulacion

```bash
roscore
rosrun turtlesim turtlesim_node
```

#### Lanzar ejemplos

```bash
rosrun mi_primer_paquete publicador #lanzar publicador
rosrun mi_primer_paquete sub_pose #lanzar suscriptor
rosrun mi_primer_paquete pub_sub #lanzar suscriptor y publicador
```
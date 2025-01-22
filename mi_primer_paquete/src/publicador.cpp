#include "ros/ros.h"  // Incluye la biblioteca principal de ROS para C++
#include "geometry_msgs/Twist.h"  // Incluye el mensaje tipo Twist para controlar la velocidad

int main(int argc, char **argv)
{
  // Inicializa el nodo ROS llamado "nodo_publicador" con los argumentos de la línea de comandos
  ros::init(argc, argv, "nodo_publicador");

  // Crea un objeto de tipo NodeHandle, que permite interactuar con el sistema ROS
  ros::NodeHandle n;

  // Crea un publicador que enviará mensajes de tipo geometry_msgs::Twist al tema "turtle1/cmd_vel"
  // El segundo parámetro "10" es el tamaño de la cola del buffer de mensajes
  ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);

  // Define la tasa a la cual se ejecutará el bucle principal (10 Hz)
  ros::Rate loop_rate(10);

  // Crea un mensaje de tipo Twist
  geometry_msgs::Twist cmd_vel_msg;

  // Asigna valores a las componentes de velocidad lineal y angular
  cmd_vel_msg.linear.x = 0.5;  // Velocidad lineal en el eje X (m/s)
  cmd_vel_msg.angular.z = 0.5;  // Velocidad angular en el eje Z (rad/s)

  // Bucle principal que continuará ejecutándose mientras ROS esté en funcionamiento
  while (ros::ok())
  {
    // Imprime un mensaje en la consola para indicar que se está publicando un mensaje de velocidad
    std::cout<< "Publicando velocidad en tortuga"<< std::endl;

    // Publica el mensaje de velocidad en el tema "turtle1/cmd_vel"
    cmd_vel_pub.publish(cmd_vel_msg);
    
    // Pausa el bucle para cumplir con la tasa de actualización de 10 Hz
    loop_rate.sleep();
  }

  // El código nunca llega aquí porque el bucle while es infinito, pero se retorna 0 para indicar ejecución exitosa
  return 0;
}

#include "ros/ros.h"               // Biblioteca principal de ROS
#include "std_msgs/String.h"       // Biblioteca para mensajes de tipo String

// Función callback que se ejecuta cuando se recibe un mensaje en el tópico
void mensajeCallback(const std_msgs::String::ConstPtr& msg)
{
    // Imprime el mensaje recibido en consola
    ROS_INFO("Mensaje recibido: %s", msg->data.c_str());
}

int main(int argc, char **argv)
{
    // Inicializa el nodo ROS con el nombre "nodo_suscriptor"
    ros::init(argc, argv, "nodo_suscriptor");

    // Crea un NodeHandle para interactuar con ROS
    ros::NodeHandle nh;

    // Declara un suscriptor al tópico "mi_topico"
    // El mensaje recibido será de tipo std_msgs::String y se procesará con la función "mensajeCallback"
    ros::Subscriber sub = nh.subscribe("mi_topico", 10, mensajeCallback);

    // Mantiene el nodo activo y procesando mensajes entrantes
    ros::spin();

    return 0;
}

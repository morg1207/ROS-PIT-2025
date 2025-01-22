#include "ros/ros.h"               // Biblioteca principal de ROS
#include "std_msgs/String.h"       // Biblioteca para mensajes de tipo String

int main(int argc, char **argv)
{
    // Inicializa el nodo ROS con el nombre "nodo_publicador"
    ros::init(argc, argv, "nodo_publicador");

    // Crea un NodeHandle para interactuar con ROS
    ros::NodeHandle nh;

    // Declara un publicador al tópico "mi_topico"
    // El mensaje publicado será de tipo std_msgs::String y tendrá una cola de tamaño 10
    ros::Publisher pub = nh.advertise<std_msgs::String>("mi_topico", 10);

    // Configura la frecuencia del bucle principal en 10 Hz
    ros::Rate loop_rate(10);

    // Contador para generar datos dinámicos
    int contador = 0;

    // Bucle principal del nodo
    while (ros::ok()) {
        // Crea un mensaje del tipo std_msgs::String
        std_msgs::String msg;

        // Llena el mensaje con datos (en este caso, un texto dinámico)
        std::stringstream ss;
        ss << "Mensaje número: " << contador++;
        msg.data = ss.str();

        // Publica el mensaje en el tópico
        ROS_INFO("Publicando: %s", msg.data.c_str());
        pub.publish(msg);

        // Espera para mantener la frecuencia especificada
        loop_rate.sleep();
    }

    return 0;
}

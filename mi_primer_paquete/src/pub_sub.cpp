#include "ros/ros.h"                // Biblioteca principal para trabajar con ROS.
#include "turtlesim/Pose.h"         // Biblioteca para trabajar con el mensaje Pose de turtlesim.
#include "geometry_msgs/Twist.h"    // Biblioteca para trabajar con el mensaje Twist (comandos de velocidad).

turtlesim::Pose pose_turtle; // Variable global para almacenar la posición actual de la tortuga.

// Callback que se ejecuta cada vez que se recibe un mensaje en el tópico "/turtle1/pose".
void poseCallback(const turtlesim::Pose::ConstPtr& msg) {
    // Actualiza la posición de la tortuga usando los datos recibidos.
    pose_turtle.x = msg->x;
    pose_turtle.y = msg->y;

    // Imprime la posición de la tortuga en consola con tres decimales de precisión.
    ROS_INFO("Se la posicion de la tortuga en x = [%.3f] y = [%.3f]", pose_turtle.x, pose_turtle.y);
}

int main(int argc, char **argv) {
    // Inicializa el nodo ROS con el nombre "nodo_suscriptor".
    ros::init(argc, argv, "nodo_publicador_suscriptor");

    // Mensaje informativo que indica que el nodo se ha inicializado.
    ROS_INFO("Se inicializo el nodo suscriptor");

    // Crea un NodeHandle para interactuar con el sistema ROS.
    ros::NodeHandle n;

    // Declaración del suscriptor al tópico "/turtle1/pose".
    // Se utiliza una cola de tamaño 10 y se asigna la función callback "poseCallback".
    ros::Subscriber pose_sub = n.subscribe("/turtle1/pose", 1, poseCallback);

    // Declaración del publicador al tópico "/turtle1/cmd_vel" con una cola de tamaño 1.
    // Este publicador enviará mensajes de tipo geometry_msgs::Twist para controlar la tortuga.
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);

    // Frecuencia del bucle principal en Hz (10 ciclos por segundo).
    ros::Rate loop_rate(10);

    // Mensaje de tipo Twist para controlar la velocidad de la tortuga.
    geometry_msgs::Twist cmd_vel_msg;

    // Configuración de las velocidades lineal y angular de la tortuga.
    cmd_vel_msg.linear.x = 0.5;  // Velocidad lineal en el eje X (m/s).
    cmd_vel_msg.angular.z = 0.5; // Velocidad angular alrededor del eje Z (rad/s).

    // Bucle principal que se ejecuta mientras ROS esté activo.
    while (ros::ok()) {
        // Mensaje informativo que indica que se está publicando la velocidad.
        ROS_INFO("Publicando velocidad");

        // Publica el mensaje de velocidad en el tópico "/turtle1/cmd_vel".
        cmd_vel_pub.publish(cmd_vel_msg);

        // Procesa los callbacks pendientes (incluye la función poseCallback).
        ros::spinOnce();

        // Duerme para mantener la frecuencia especificada (10 Hz).
        loop_rate.sleep();
    }

    // El siguiente mensaje no se ejecutará en este caso porque el bucle while
    // mantiene el nodo activo hasta que se cierra ROS.
    ROS_INFO("Despues del spin");

    return 0; // Finaliza la ejecución del programa.
}

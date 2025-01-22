#include "ros/ros.h" // Biblioteca principal para trabajar con ROS.
#include "turtlesim/Pose.h" // Mensaje específico que contiene la posición de la tortuga.

turtlesim::Pose pose_turtle; // Variable global para almacenar la posición actual de la tortuga.

// Callback que se ejecuta cuando se recibe un mensaje en el tópico /turtle1/pose.
void poseCallback(const turtlesim::Pose::ConstPtr& msg) {
    // Se asignan los valores de x e y del mensaje recibido a la variable global pose_turtle.
    pose_turtle.x = msg->x;
    pose_turtle.y = msg->y;

    // Se imprime la posición de la tortuga en la consola.
    ROS_INFO("Se la posicion de la tortuga en x = [%.3f] y = [%.3f]", pose_turtle.x, pose_turtle.y);
}

int main(int argc, char **argv) {
    // Inicializa el nodo ROS con el nombre "nodo_suscriptor".
    ros::init(argc, argv, "nodo_suscriptor");

    // Mensaje informativo para indicar que el nodo ha sido inicializado.
    ROS_INFO("Se inicializo el nodo suscriptor");

    // Crea un NodeHandle que permite interactuar con el sistema ROS.
    ros::NodeHandle n;

    // Crea un suscriptor que escucha en el tópico "/turtle1/pose" con una cola de tamaño 10.
    // Cuando hay un nuevo mensaje, ejecuta la función callback poseCallback.
    ros::Subscriber pose_sub = n.subscribe("/turtle1/pose", 1, poseCallback);

    // Eliminar ros::spin() hace que el nodo termine antes de procesar los callbacks.
    ros::spin(); // Mantiene el nodo activo para procesar los mensajes.

    // Este mensaje no se imprimirá correctamente porque el nodo termina antes de llegar aquí.
    ROS_INFO("Despues del spin");

    return 0; // Finaliza la ejecución del programa.
}

#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

nav_msgs::Odometry odom_msg;
double yaw = 0.0; // Almacena el ángulo de orientación en radianes
bool flag_orientacion_inicial=false;

// Callback para recibir la odometría y extraer el ángulo yaw
void poseCallback(const nav_msgs::Odometry::ConstPtr& msg) {
    odom_msg = *msg;

    // Obtener el quaternion de la odometría
    tf2::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w
    );

    // Convertir quaternion a RPY (roll, pitch, yaw)
    tf2::Matrix3x3 m(q);
    double roll, pitch;
    m.getRPY(roll, pitch, yaw); // Solo nos interesa yaw

    ROS_INFO("Posicion: x = %.3f, y = %.3f, yaw = %.3f rad", 
             odom_msg.pose.pose.position.x, 
             odom_msg.pose.pose.position.y, 
             yaw);
    falg_orientacion_inicial = true;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "nodo_hacer_cuadrado");
    ROS_INFO("Se inicializo el nodo");

    ros::NodeHandle n("~");

    // Obtener el ángulo de giro deseado en grados (default: 90°)
    double angulo_deseado;
    if (!n.getParam("angulo_deseado", angulo_deseado)) {
        ROS_WARN("Parametro /angulo_deseado no encontrado. Usando valor por defecto: 90°");
        angulo_deseado = 90.0;
    }
    ROS_INFO("Angulo objetivo: %.1f grados", angulo_deseado);

    // Convertir ángulo a radianes
    double angulo_deseado_rad = angulo_deseado * M_PI / 180.0;

    // Configurar el suscriptor a la odometría
    ros::Subscriber odom_sub = n.subscribe("/odom", 1, poseCallback);

    // Publicador para enviar comandos de velocidad
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

    // Configurar la frecuencia de control
    ros::Rate loop_rate(10);

    geometry_msgs::Twist cmd_vel_msg;

    // Control proporcional (P) para alcanzar el ángulo deseado
    double Kp = 1.5; // Ganancia proporcional
    bool objetivo_alcanzado = false;

    while(!orientacion_inicial){
        ros::spinOnce();
    };

    ROS_INFO("Orientacion inicial: %.3f rad", yaw);

    double error=0;

    while (ros::ok() && !objetivo_alcanzado) {
        // Calcular el error (diferencia entre el ángulo deseado y la orientación actual)
        error = angulo_deseado_rad - (yaw);

        // Control proporcional (P)
        double control = Kp * error;

        // Limitar la velocidad angular máxima
        double max_angular_vel = 1.0; // rad/s
        cmd_vel_msg.angular.z = std::max(-max_angular_vel, std::min(max_angular_vel, control));

        // Publicar la velocidad
        cmd_vel_pub.publish(cmd_vel_msg);

        ROS_INFO("Error: %.3f rad, Control: %.3f rad/s", error, cmd_vel_msg.angular.z);

        // Si el error es suficientemente pequeño, detener el robot
        if (fabs(error) < 0.05) {
            cmd_vel_msg.angular.z = 0.0;
            cmd_vel_pub.publish(cmd_vel_msg);
            objetivo_alcanzado = true;
            ROS_INFO("Angulo alcanzado. Robot detenido.");
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

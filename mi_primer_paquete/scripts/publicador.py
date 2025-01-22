#!/usr/bin/env python3
import rospy                              # Importa la librería principal de ROS para Python.
from geometry_msgs.msg import Twist       # Importa el mensaje Twist para enviar comandos de velocidad.

# Función principal del publicador
def publicador():
    rospy.init_node('publicador', anonymous=True)  
    # Inicializa un nodo llamado "publicador".
    # El parámetro `anonymous=True` permite que el nodo tenga un identificador único si se lanzan múltiples instancias.

    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=10)  
    # Declara un publicador que publicará mensajes en el tópico "/turtle1/cmd_vel".
    # El mensaje que se publicará será de tipo `Twist`, y se usa una cola con un tamaño máximo de 10 mensajes.

    rate = rospy.Rate(10)  
    # Establece la frecuencia de publicación en 10 Hz (10 veces por segundo).

    cmd_vel_msg = Twist()  
    # Crea un mensaje de tipo `Twist` para enviar comandos de velocidad lineal y angular.

    cmd_vel_msg.linear.x = 0.5  
    # Establece la velocidad lineal en el eje X a 0.5 unidades.

    cmd_vel_msg.angular.z = 0.5  
    # Establece la velocidad angular en el eje Z a 0.5 radianes/segundo.

    while not rospy.is_shutdown():  
        # Bucle principal que se ejecutará mientras ROS esté activo y no se haya solicitado una interrupción.

        pub.publish(cmd_vel_msg)  
        # Publica el mensaje `cmd_vel_msg` en el tópico "/turtle1/cmd_vel".

        rospy.loginfo('Publicando')  
        # Imprime un mensaje en la consola indicando que se está publicando información.

        rate.sleep()  
        # Pausa el bucle para mantener la frecuencia de 10 Hz.

# Punto de entrada principal del script
if __name__ == '__main__':
    try:
        publicador()  
        # Llama a la función principal del publicador.
    except rospy.ROSInterruptException:  
        # Captura excepciones si ROS se interrumpe de forma inesperada.
        pass

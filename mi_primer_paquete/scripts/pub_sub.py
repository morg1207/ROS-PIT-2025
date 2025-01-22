#!/usr/bin/env python3
import rospy                             # Importa la librería principal de ROS para Python.
from turtlesim.msg import Pose           # Importa el tipo de mensaje Pose del paquete turtlesim.
from geometry_msgs.msg import Twist      # Importa el tipo de mensaje Twist para comandos de velocidad.

# Función callback para manejar los mensajes recibidos en el tópico "/turtle1/pose"
def poseCallback(data):
    rospy.loginfo("La posicion de la tortuga")  
    # Muestra un mensaje en la consola indicando que se recibió la posición de la tortuga.
    # Nota: Actualmente, no se están utilizando los datos de la posición (`data`).

# Función principal que combina el suscriptor y el publicador
def suscriptor():
    rospy.init_node('suscriptor', anonymous=True)  
    # Inicializa un nodo ROS con el nombre "suscriptor".
    # El parámetro `anonymous=True` asegura que el nodo tenga un identificador único si se lanzan múltiples instancias.

    sub = rospy.Subscriber('/turtle1/pose', Pose, poseCallback)  
    # Declara un suscriptor que escucha al tópico "/turtle1/pose".
    # El mensaje recibido será de tipo `Pose` y será procesado por la función `poseCallback`.

    pub = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=1)  
    # Declara un publicador que enviará mensajes al tópico "/turtle1/cmd_vel".
    # El mensaje publicado será de tipo `Twist` y tendrá una cola de tamaño 10.

    rate = rospy.Rate(10)  
    # Configura la frecuencia de ejecución del bucle principal en 10 Hz (10 veces por segundo).

    cmd_vel_msg = Twist()  
    # Crea un mensaje de tipo `Twist` para enviar comandos de velocidad lineal y angular.

    cmd_vel_msg.linear.x = 0.5  
    # Establece la velocidad lineal en el eje X a 0.5 unidades (por ejemplo, metros/segundo).

    cmd_vel_msg.angular.z = 0.5  
    # Establece la velocidad angular en el eje Z a 0.5 radianes/segundo.

    while not rospy.is_shutdown():  
        # Bucle principal que se ejecuta mientras ROS esté activo y no se haya solicitado una interrupción.

        pub.publish(cmd_vel_msg)  
        # Publica el mensaje `cmd_vel_msg` en el tópico "/turtle1/cmd_vel".

        rospy.loginfo('Publicando')  
        # Muestra un mensaje en la consola indicando que se está publicando información.

        rate.sleep()  
        # Pausa el bucle para mantener la frecuencia de ejecución configurada (10 Hz).

# Punto de entrada principal del script
if __name__ == '__main__':
    try:
        suscriptor()  
        # Llama a la función principal `suscriptor`.
    except rospy.ROSInterruptException:  
        # Maneja posibles interrupciones de ROS de forma segura.
        pass

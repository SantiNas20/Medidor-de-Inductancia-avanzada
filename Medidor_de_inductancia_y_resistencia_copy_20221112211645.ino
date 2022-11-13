
double Pulso, Frecuencia, Capacitancia, Inductancia; //...Declaramos variables
void setup(){
 
  Serial.begin(115200);//Definimos el puerto
  pinMode(11, INPUT);//Entrada de la salida del comparador
  pinMode(13, OUTPUT);//Salida a través de una resistencia de 150 ohmios a través del circuito LC
  Serial.println("MEDIDOR DE INDUCTANCIA Y RESISTENCIA");//...Imprimimos por pantalla
  delay(200);//Retardo que se utiliza
  Serial.println("BIENVENIDO AL PROGRAMA");//...Imprimimos por pantalla
  delay(200);// Retardo que se utiliza
}
void loop(){
  digitalWrite(13, HIGH);//Aplicamos un pulso en alto al pin digital 13 para cargar el circuito con 5 milisegundos
  delay(5);// Tiempo que se da para cargar el inductor
  digitalWrite(13,LOW);//Aplicamos un pulso en bajo al pin digital 13 
  delayMicroseconds(100); //Se le da un retardo para asegurarnos que el circuito este ocilando 
  Pulso = pulseIn(11,HIGH,5000);//Medimos el periodo del pulso de entrada de ocilacion correspondiente a la del circuito
  if(Pulso > 0.1){ // se crea un if si no se produjo un tiempo de espera y tomó una lectura
    
    
  
  Capacitancia = 2.E-6; // Definimos el valor del condesador-se utilizo dos condensadores de 1uF
  
  
  Frecuencia = 1.E6/(2*Pulso);//Operacion para hallar la frecuencia del inductor
  Inductancia = 1./(Capacitancia*Frecuencia*Frecuencia*4.*3.14159*3.14159);//Operacion para hallar la inductanica del inductor 
  Inductancia *= 1E6; //Resultados 

  //Serial print
  Serial.print("Su pulso es:");//Imprimimos por pantalla el pulso 
  Serial.print( Pulso );//Aqui es donde se muestran los datos de pulso
  Serial.print("\tFrecuencia Hz:");// Imprimimos por pantalla la frecuencia
  Serial.print( Frecuencia);//Aqui es donde se muestran los datos de frecuencia
  Serial.print("\tInductancia uH:");// Imprimimos por pantalla la inductancia 
  Serial.println( Inductancia );//Aqui es donde se muestran los datos de inductancia
  delay(10);// Se utiliza un retraso de 10 milisegundos el cual imprimira por pantalla los datos 

  
 }


 //---------------CODIGO DE LA INTERFAZ GRAFICA (PHYTON)-------------------//

from tkinter import*
import tkinter #librería tkinter
import serial,time


##CONEXIÓN AL ESP32
esp = serial.Serial("COM5",115200)
esp_leido=esp.readline().decode('utf-8')
print(esp_leido)
esp.close()


esp = serial.Serial("COM5",115200)
esp_leido=esp.readline().decode('utf-8')



##FUNCIÓN DEL BOTÓN


def Mostrarvalores():

    global txt2

##VALORES

  ##PULSO, FRECUENCIA, INDUCTANCIA

    txt2.delete(0,'end')
    txt2.insert(0,esp_leido)



    
ventana=Tk() # la clase para crear la interfaz

ventana.title("MEDIDOR DE INDUCTANCIA") #La parte del titulo


##ventana.geometry("600x300") #Dimensiona la ventana

ventana.resizable(0,0) #Dimensiona el ancho y el alto

ventana.config(bg="white") #función bg sirve para cambiar el fondo de ventana

##Ventana dentro de la Raiz

miFrame=Frame()

miFrame.pack(side="left", anchor='n')

miFrame.config(bg="light blue")

miFrame.config(width="500", height="300")

miFrame.config(bd=10)

miFrame.config(relief="groove")



##ETIQUETAS Y BOTONES
    

lbl1= Label(ventana, text="PULSO", bg="light green") ## ETIQUETA PRIMER NUMERO
lbl1.place(x=10, y=10, width=100, height=30)



lbl2= Label(ventana, text="FRECUENCIA(Hz)", bg="yellow") ##ETIQUETA SEGUNDO NUMERO
lbl2.place(x=150, y=10, width=100, height=30)


lbl3= Label(ventana, text="INDUCTANCIA", bg="orange") ##ETIQUETA TERCER 3 NUMERO
lbl3.place(x=300, y=10, width=100, height=30)


##MOSTRAR RESULTADOS EN LA CAJA DE TEXTO

txt2= Entry(ventana,  bg="white") ## CAJA DE TEXTO (VALORES)
txt2.place(x=10, y=60, width=400, height=30)



#BOTÓN MOSTRAR VALORES


btn = Button(miFrame, text="CALCULAR " , command=Mostrarvalores)
btn.config(bg="red")
btn.place(x=20, y=100, width=150, height=30 )

 


##IMAGEN

miFrame2=Frame()

miFrame2.pack(side="left", anchor='n')

miFrame2.config(bg="white")

miFrame2.config(width="650", height="300")

miFrame2.config(bd=10)

miFrame2.config(relief="groove")



miImagen=PhotoImage(file="MEDIDOR.png")

Label(miFrame2, image=miImagen).place(x=0, y=0)





ventana.mainloop()

}


 

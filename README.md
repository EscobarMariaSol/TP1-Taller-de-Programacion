# Trabajo Práctico 1 - Taller de Programación I - (75.42/95.08)
# Informe de Resolución


**Nombre:**  Escobar Benitez Maria Soledad

**Padrón:**  97877

**Repositorio:** [Link GitHub!](https://github.com/EscobarMariaSol/TP1-Taller-de-Programacion)

**Fecha de entrega:** 20/10/2020


## Introducción

En este ejercicio se deberán desarrollar dos programas: uno emisor (o cliente),
y otro receptor (o servidor) de un mensaje cifrado.
El programa emisor deberá leer mensajes por entrada estándar y enviarlos 
cifrados, mientras que el receptor deberá descifrarlos y mostrarlos por salida 
estándar.
Para cifrar los mensajes se deberán implementar tres cifradores distintos, 
Cesar, Vigenere y Rivest Cipher 4.
El mensaje a cifrar será recibido a través de la entrada estándar y luego de
ser enviado y descifrado será comunicado a través de salida estándar.

## Esquema de Resolución

Para la resolución de este trabajo práctico se decidió tomar la sugerencia 
dada por la cátedra y pensar en una resolución por partes. 
Se decidió comenzar elaborando primero cada tipo de cifrador, los mismos
se implementaron como un tipo de dato abstracto, cada uno.
Luego, con la idea de abstraer un poco tanto al servidor como al cliete, se 
decidió implementar un manejador que sirviera como intermediario entre el 
cliente, o servidor, y cada uno de los cifradores, de esta manera simplemente 
se recibe el método a utilizar para cifrar, junto a su respectiva clave, y el 
cliente, o servidor, le da esa información al manejador y el mismo se encarga 
de precesar esa información.
Siguiendo ese mismo lineamiento, se decide tambien implementar un manejador 
que administre la entrada y salida de información dentro del programa, por lo 
que tanto el cliente como el servidor, no deben lidiar con esos detalles.
Para abstraer un poco más el uso e intercambio de información se decidió 
además implementar un tipo de dato correspondiente a un arreglo, el cual 
facilita el almacenamiento del mensaje de manera dinámica, sin necesidad de
tener que cargarlo completamente en memoria.
Para este punto, cada TDA implementado contaba con sus pequeñas pruebas 
que avalaran que su comportamiento cumpliera con lo esperado.
Una vez se tuvieron todas las pequeñas partes se comenzó con la implementación 
de los sockets para luego probarlos comenzando con la implementación del 
cliente y el servidor.



La imagen a continuación intenta representar qué entidades tienen comunicación
, podemos ver claramente como los cifradores sólo tienen contacto con su 
manejador y que tanto el servidor como el cliente no conocen de su existencia, 
lo mismo sucede con los sockets y el resto de las entidades, pues los mismos 
sólo se utilizan para establecer la comunicación entre el cliente y el 
servidor y nada más.
![TDAs](https://github.com/EscobarMariaSol/TP1-Taller-de-Programacion/blob/main/img/TP1-Diagrama-1.png)



Por otro lado tenemos la siguiente imagen que intenta representar el flujo 
que siguen los programas, a alto nivel.
Vemos como tanto el cliente y el servidor son disparados por su 
correspondiente main, luego vemos como es el flujo de la comunicación, 
el ingreso y salida del mensaje y en qué momento se realiza la codificación 
y decodificación del mensaje, a través del manejador de cifradores.
![Flujo](https://github.com/EscobarMariaSol/TP1-Taller-de-Programacion/blob/main/img/TP1-Diagrama-2.png)


## TDAs Implementados
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



En la Sección a continuación se contará con un poco más de detalles el 
motivo de creación y uso de cada uno de los TDAs implementados, para mayor 
detalle acerca de las primitivas de los TDAs y su funcionamiento, se encuentra 
en los correspondiente archivos de encabezado su documentación.

## TDAs Implementados

### Encoder Cesar, Vigenere y RC4

Cada cifrador está representado como un tipo de dato abstracto que se encarga 
de encapsular su comportamiento y guardar el estado de las variables o 
atributos que se utilizan a lo largo de su vida útil, de esta manera se
logra abstraer completamente, a los TDAs usuarios, de cómo se realiza el
cifrado de los mensajes, que de hecho para los encoders, no se trata de 
mensajes, sino que simplemente se dedican a cifrar bytes.

1. **Cesar:** La estructura del codificador Cesar cuenta con un único atributo 
    que corresponde a la clave que se utiliza a la hora de codificar un byte.
    La interfaz de este cifrador es la siguiente:
    ```C
    typedef struct {
    uint32_t key;
    }cesar_encoder_t;
    int cesarEncoderCreate(cesar_encoder_t *encoder, uint32_t key);
    unsigned char cesarEncoderEncode(cesar_encoder_t *self, unsigned char element);
    unsigned char cesarEncoderDecode(cesar_encoder_t *self, unsigned char element);
    ```
2. **Vigenere:** La estructura del codificador Vigenere cuenta con atributos 
    como la clave (key) y la posición actual de la clave en la que se 
    encuentra (key_pos) de esta manera se puede codificar o decodificar un 
    mensaje completo, llamando al método del encoder las veces que sean 
    necesarias. 
    Este cifrador cuenta con la siguiente interfaz:
    ```C
    typedef struct {
    char *key;
    int key_pos;
    }vigenere_encoder_t;
    int vigenereEncoderCreate(vigenere_encoder_t *encoder, char *key);
    unsigned char vigenereEncoderEncode(vigenere_encoder_t *self, 
    unsigned char vigenereEncoderDecode(vigenere_encoder_t *self, unsigned char element);
    ```
3. **RC4:** La estructura del codificador RC4 cuenta con atributos como el 
    arreglo (stream) que se utilizará para realizar la codificación y 
    decodificación y los índices i y j, que corresponden a los indices del 
    stream a utilizar para codificar cada byte, guardando el estado del 
    codificador luego de cada llamado, permitiendo así codificar y decodificar 
    un mensaje de cualquier longitud con multiples llamados.
    Este cifrador cuenta con la siguiente interfaz, que como se puede observar 
    es la más simple de todas, ya que para codificar y decodificar se utiliza 
    el mismo método.
    ```C
    typedef struct {
    unsigned char stream[256];
    uint8_t i, j;
    }rc4_encoder_t;
    int rc4EncoderCreate(rc4_encoder_t *encoder, unsigned char *key);
    unsigned char rc4EncoderEncode(rc4_encoder_t *self, unsigned char element);
    ```

### Encoder Handler

Este es un manejador que se encarga de recibir un mensaje y codificarlo o 
decodificarlo, utilizando el cifrador que se le ha especificado al momento 
de su creación. El mismo recibe un Array desde el Cliente o el Servidor y 
lo recorre, llamando al método adecuado de su cifrador para cada byte del 
mensaje recibido y guardando el resultado en un nuevo array que luego 
devolverá al usuario que lo llamó. Con esta implementación se ha logrado 
que tando el Cliente como el Servidor reciban un Array con el mensaje 
cifrado o descifrado, sin necesidad de conocer su contenido o la manera en 
que han sido cifrados, de hecho ni siquiera conocen de la existencia de más 
de un cifrador, simplemente se comunican con el manejador y este les resuelve 
su solicitud.
Este TDA posee la siguiente interfaz:
```C
typedef struct {
    cesar_encoder_t cesar_encoder;
    vigenere_encoder_t vigenere_encoder;
    rc4_encoder_t rc4_encoder;
    const char *type;
}encoder_handler_t;
int encoderHandlerCreate(encoder_handler_t *handler, const char *type, const char *key);
array_t *encoderHandlerEncode(encoder_handler_t *self, array_t *message);
array_t *encoderHandlerDecode(encoder_handler_t *self, array_t *message);
void encoderHandlerDestroy(encoder_handler_t *self);
```
**Encoder Handler:** La estructura del manejador de cifradores cuenta con 
atributos como el tipo de cifrador que se utilizará a la hora de realizar 
la codificación y decodificación de mensajes además de contar con un 
atributo con cada tipo de encoder, en el cual almacenará el encoder 
utilizado o NULL en caso de los no utilizados.

### Array

Este TDA es creado con el propósito de encapsular la reserva y redimensión de 
memoria para almacenar los mensajes que se envian y reciben. La idea es que 
ninguno de los otros TDAs involucrados deba preocuparse por almacenar un 
mensaje con su tamaño exacto o peor, tener que estar redimensionando el 
espacio de memoria asignado, para que el mensaje sea guardado completamente.
Es así como los TDAs como Cliente, Servidor, Encoder o IO handler, sólo 
envian y reciben mensajes almacenados en un Array, en el cual pueden copiar 
tantos bytes como quieran sin preocuparse de nada más, contando además con 
la posibilidad de consultar su tamaño, sin tener que guardar o recibir ese 
dato desde el inicio. También nos permite consultar el contenido de cada 
posición del arreglo, como lo hariamos con un arreglo tradicional.
La interfaz del TDA es la siguiente:
```C
typedef struct {
    unsigned char *buffer;
    size_t size;
    uint32_t pos;
}array_t;
array_t* arrayCreate(size_t size);
int arrayAdd(array_t *self, const unsigned char *msg, size_t len);
unsigned char *arrayGetContent(array_t *self);
unsigned char arrayGetElement(array_t *self, size_t pos);
size_t arrayGetSize(array_t *self);
void arrayDestroy(array_t * self);
```
**Array:** La estructura del array cuenta con atributos como un buffer 
que será en el cual se almacenará la información, el tamaño del buffer y 
la posición del buffer en la que se encuentra posicionado.

### Input Output Handler

Como se recibe un mensaje por entrada estándar y luego debe mostrarse el 
mensaje descifrado por salida estándar, se pensó en crear un manejador que 
se encargue de manejar estos movimientos, dejando fuera del conocimiento de 
los detalles de implementación de lectura y escritura, tanto al Cliente como 
al Servidor, que son quienes reciben y envian los mensajes. Este TDA se 
encarga de abrir un archivo o la entrada estandar, leer el contenido y 
almacenarlo en un Array, para luego devolverlo al Cliente, como así también 
recibe un array desde el Servidor y se encarga de mandarlo a salida estándar.
Este TDA cuenta con la siguiente interfaz:
```C
typedef struct {
    FILE *file;
}io_handler_t;
int ioHandlerCreate(io_handler_t *handler, const char *path);
array_t *ioHandlerGetMessage(io_handler_t * self);
int ioHandlerSetMessage(io_handler_t * self, array_t *message);
void ioHandlerDestroy(io_handler_t * self);
```
**IO Handler:** La estructura del manejador de entrada y salida cuenta con 
un único atributo correspondiente al file en el cual deberá escribir o 
desde el cual deberá leer según corresponda.

### Socket

Para la implementación de los sockets, encargados de establecer la comunicación 
entre el Cliente y el Servidor, se ha decidido implementar la siguiente 
interfaz, tratando de mantener un alto nivel de abstracción entre el usuario 
y el funcionamiento detrás del socket.

```C
typedef struct {
	uint16_t fd;
}socket_t;
int socketCreate(socket_t* socket, const char* host, const char* port, uint16_t type);
int socketAccept(socket_t* self, socket_t* accept_socket);
int socketSend(socket_t* self, const unsigned char* buffer, size_t size);
int socketRecv(socket_t* self, unsigned char *buffer, size_t size);
void socketDestroy(socket_t* self);
```

-**Socket:** La estructura del socket es muy sencilla, ya que sólo cuenta con
un único atributo correspondiente al file descriptor que le es asignado.

-**Socket Create:** Para la creación de un socket, sea cliente o servidor, se 
utiliza una única función, la cual devolverá un socket listo para iniciar 
la comunicación, abstrayendo así completamente al usuario de tener que 
acudir a otra función para establecer la conexión.

-**Socket Accept:** En el caso del socket utilizado como Servidor, se utiliza la 
función accept para aceptar un nuevo cliente cuando el servidor esté listo.

-**Socket Send & Recv:** Estas funciones son utilizadas a la hora de enviar y 
recibir información desde el Cliente y el Servidor.

-**Socket Destroy:** Esta última función se encarga de destruir un socket, la 
misma cierra el canal de comunicación establecido por el socket, ya sea para 
enviar o recibir información, y luego cierra el file descriptor asociado al 
socket.

### Client

Para la creación del Cliente se decide proveer la siguiente interfaz, en la 
cual se refleja la idea de abstraer al programa principal, main, de toda 
funcionalidad, es por esto que la única responsabilidad que recaé sobre él es 
realizar un llamado a la función que corre al Cliente.

```C
typedef struct {
	socket_t socket;
	encoder_handler_t encoder;
}client_t;
int clientRun(const char *host, const char *port, const char *method, const char *key);
int clientStart(client_t *client, const char *host, const char *port, const char *method, const char *key);
int clientSendMessage(client_t *self);
void clientFinish(client_t *self);
```

-**Client:** La estructura del cliente cuenta con atributos como el socket, 
encargado de establecer la comunicación con el servidor, y el encoder, que 
codificará el mensaje que recibe el cliente para luego enviarse al servidor.

-**Client Run:** Es la función que inicia la ejecución de un cliente, la cual 
se encargará de crear un cliente, llamando a **clientStart**, recibir un 
mensaje, enviarlo al servidor a través del llamado a **clientSenMessage** y 
luego liberar los recursos utilizados llamando a **clientFinish** el cual 
liberará todos los recursos de manera ordenada y se podrá dar por finalizada 
la ejecución del programa.

### Server

Al igual que con el Cliente, aquí se ha buscado abstraer completamente al 
programa principal, del funcionamiento y la lógica detrás del servidor por 
lo que se le ha delegado únicamente la función de realizar un llamado al 
servidor para indicar que debe iniciar su ejecución.

```C
typedef struct {
	socket_t self_socket;
    socket_t accept_socket;
	encoder_handler_t encoder;
}server_t;
int serverRun(const char *port, const char *method, const char *key);
int serverStart(server_t *server, const char *port, const char *method, const char *key);
int serverAccept(server_t *server);
int serverReceiveMessage(server_t *self);
void serverFinish(server_t *self);
```

-**Servidor:** La estructura del servidor cuenta con atributos como el 
socket, desde el cual estará disponible para la conexión con el cliente, 
el socket aceptador, el cual será el canal de comunicación para la 
recepción de información y el encoder que utilizará para descifrar la 
información recibida.

-**Server Run:** Es la función encargada de iniciar la ejecución del servidor, 
para esto comienza llamando a **serverStart**, la cual creará un nuevo 
servidor y lo dejará escuchando en el puerto deseado, luego aceptará un 
cliente haciendo un llamado a **serverAccept**. Una vez se tenga a un cliente 
conectado se recibirá un mensaje, haciendo uso de la función 
**serverReceiveMessage** y una vez finalizado este proceso, se llamará a 
**serverFinish** para liberar todos los recursos utilizados y dar por 
finalizada la ejecución.
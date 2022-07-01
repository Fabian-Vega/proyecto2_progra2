# proyecto2_progra2
## **Readme.md (English)**
### **What does the Graph library do?**
The Graph library provides the user with the necessary templates to create and costumize graphs for the usage it desires and are between the capabilities of the library.

### **Members** 
    * Alejandro Barboza Taylor                        C10886
    * Fabian Vega Meza                                C08369  
    * Kenneth Daniel Villalobos Solis                 C18548

### **User Manual**
For the correct implementation of the library's templates, everytime the templates from the library are used, the user must specify the data type, the content of the vertex, their links, the data type of the links and the content or weight they may have. Any fault of this specifications will be taken as a non valid pointer or a 0, depending on the case.
To create a graph, the constructor receives an initial capacity, that will have a default in case of ommission, and boolean parameter to determine if the graph is directed or not(true->directed/false->non-directed).
The graph has the = operator overloaded to be used, to swap and assign the data from one graph to another. 
The () operator is also overloaded, and it receives two vertexes, and it will return the link weight between them. 
The function getNeighbors receives a vertex, and it will return a Vertex** of all the neighbors.
To construct a Vecter object, it will need the data that it will contain and the amount of links that it has(defaults to 0). 
To construct a Link object, it can be initialized without any parameters, or the Vertex* origin, weigth and Vertex* connection can be specified. 


### **¿What does the app do?**
App is a social network that utilizes the Graph library to create indicators such as vertex and links to specify both friends or user profiles and the relationships they have with other users. Each profile will hold the name of the user, and all the other users that its conected to and their specifir type of relationship. The user will be able to add or delete profiles, and also add, delete or modify the link between them. 

### **User Manual**
For the correct functioning of the app, every entry of data must be with the right data type, in this case String, otherwise, it will be taken as an invalid entry or 0 by default. The user will not be able to delete inexistent links between profiles, or access profiles that have already been deleted. To enter a new profile, the user will only need to input the string name to represented, and the app will only show the profiles that are still available. 



## **Readme.md (Español)**
### **Qué hace la biblioteca graph?** 
The librería Graph provee al usuario con las plantillas necesarias para crear y personalizar grafos para el uso que se desee implementar y estén dentro de las capacidades de la biblioteca.


### **Integrantes** 
    * Alejandro Barboza Taylor                        C10886
    * Fabian Vega Meza                                C08369  
    * Kenneth Daniel Villalobos Solis                 C18548

### **Manual de Uso**
Para la correcta implementación de las plantillas de la biblioteca, cada vez que se utilicen las plantillas de la biblioteca, el usuario debe especificar el tipo de datos, el contenido de los vértices, sus enlaces, el tipo de datos de los enlaces y el contenido o peso que puedan tener. Cualquier omision de estas especificaciones se tomará como un puntero no válido o un 0, según el caso.
Para crear un Graph, el constructor recibe una capacidad inicial, que tendrá un valor por defecto en caso de omisión, y un parámetro booleano para determinar si el grafo es dirigido o no (true->dirigido/false->no dirigido).
El gráfico tiene el operador = sobrecargado para ser usado, para intercambiar y asignar los datos de un gráfico a otro.
El operador () también está sobrecargado, recibe dos vértices y devolverá el peso del enlace entre ellos.
La función getNeighbors recibe un vértice y devolverá un vértice** de todos los vecinos.
Para construir un objeto Vecter, necesitará los datos que contendrá y la cantidad de enlaces que tiene (predeterminado en 0).
Para construir un objeto de Link, se puede inicializar sin ningún parámetro, o se puede especificar el origen del vértice*, el peso y la conexión del vértice*.

### **¿Qué hace la aplicación?**
App es una red social que utiliza la biblioteca de gráficos para crear indicadores como vértices y enlaces para especificar perfiles de amigos o usuarios y las relaciones que tienen con otros usuarios. Cada perfil contendrá el nombre del usuario y todos los demás usuarios a los que está conectado y su tipo de relación. El usuario podrá añadir o eliminar perfiles, así como añadir, eliminar o modificar las relaciones entre ellos.

### **Manual de Uso**
Para el correcto funcionamiento de App, cada entrada de datos debe ser con el tipo de datos correcto, en este caso String, de lo contrario, se tomará como una entrada no válida o 0 por defecto. El usuario no podrá eliminar enlaces inexistentes entre perfiles, ni acceder a perfiles que ya hayan sido eliminados. Para ingresar un nuevo perfil, el usuario solo necesitará ingresar el nombre de la cadena para representar, y la aplicación solo mostrará los perfiles que aún están disponibles.

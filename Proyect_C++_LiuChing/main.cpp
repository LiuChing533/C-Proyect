/*
    Autor: Liu Ching Richard
    Fecha: 30 de Julio 2023
    Descripcion: Proyecto, Software para Pasamaneria.
*/

#include <iostream> //entrada y salida basicas
#include <limits> //para filtrar los valores ingresados
#include <fstream> //manejo de archivos
#include <string> //usar strings
#include <set> //almacena elementos y verifica que no hayan duplicados
#include <sstream> //conversion entre cadenas de caracteres y otros tipos de datos
#include <cctype> //conversion entre mayusculas y minusculas
#include <iomanip> //setw y setfill para que aparezcan ceros a la izquierda
#include <vector> // Incluir la biblioteca para usar vector
#include <stdexcept> // Para indicar errores y excepciones
#include <ctime> // Para poder tener diferentes numeros aleatorios
#include <cstdlib> // Para generar numeros aleatorios con srand
#include <algorithm> // Funciones que realizan operaciones comunes como busqueda, ordenamiento, eliminacion, etc.

using namespace std;

// Estructura para representar un producto
struct Producto {
    string codigo;
    string nombre;
    int cantidad;
};

// Definicion de prototipos
bool esNumero();
bool esCodigoValido();
void consultarProducto(const set<int>& codigosExistentes);
bool codigoExiste(const string& codigo, const string& nombreArchivo);
void agregarProducto();
void eliminarProducto();
string actualizarCantidad(const string& codigo, int cantidad, vector<Producto>& productos);
void generarPedido();
void enviarPedido();
void reporteInventario();
void reportePedidosPendientes();

// Definicion de Variables
bool salida = true;
bool salida2 = true;
string codigoProducto;

// Funcion Digite ENTER
void enter(){
    cout << "Presiona ENTER para continuar..." << endl;
    system("pause > nul");
}

int main(){

    system("cls"); //Limpiar Pantalla
    system("title Proyecto Liu Ching Richard"); // Cambiar Titulo de la consola

    // Declarar Variables
    int var;

    do {
        system("cls");
        // Creacion del menu
        cout << "Software para Pasamaner\xA1" << "a \n" << endl;
        cout << "1. Inventario productos" << endl;
        cout << "2. Generar pedido" << endl;
        cout << "3. Enviar Pedido" << endl;
        cout << "4. Reporte Inventario" << endl;
        cout << "5. Reporte Pedidos Pendientes" << endl;
        cout << "6. Salir del Programa" << endl;
        if (cin >> var) {

            // Crear la funcion que tiene cada opcion
            switch (var){
            // Inventario productos
                case 1: {

                    // almacenar los codigos existentes y verificar duplicados
                    set<int> codigosExistentes;
                    bool salida2 = true;
                    int var2;
                    do {

                        system("cls");
                        // Creacion del menu de la primera opcion
                        cout << "Inventario productos \n" << endl;
                        cout << "1. Ingresar producto" << endl;
                        cout << "2. Consultar producto (Por c\xA2\digo)" << endl;
                        cout << "3. Eliminar producto" << endl;
                        cout << "4. Volver al men\xA3 principal" << endl;
                        if (cin >> var2) {

                            // Crear la funcion que tiene cada opcion
                            switch (var2){
                            // Ingresar producto
                                case 1: {

                                    agregarProducto();

                                }break;
                                // Consultar producto
                                case 2: {

                                    char continuar;
                                    while (true) {
                                        consultarProducto(codigosExistentes);

                                        // Limpiar el buffer de entrada despues de llamar a consultarProducto
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                        cout << "Desea consultar otro producto? (S/N): ";
                                        cin >> continuar;
                                        continuar = toupper(continuar);
                                        cin.ignore(); // Limpiar el buffer del salto de linea

                                        if (continuar != 'S') {
                                            break; // Salir del bucle si el usuario no desea consultar otro producto
                                        }
                                    }

                                }break;
                                // Eliminar producto
                                case 3: {

                                    eliminarProducto();

                                }break;

                                case 4: {
                                    salida2 = false;
                                }break;
                                default: {
                                    cout << "Opci\xA2n inv\xA0lida, vuelva a intentarlo"<<endl;
                                    enter();
                                }break;
                            }
                        } else {
                            cout << "Opci\xA2n inv\xA0lida, vuelva a intentarlo"<<endl;
                            cin.clear();                                         // Restablecer el estado de cin
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar caracteres restantes
                            enter();
                        }
                    } while(salida2);

                }break;
                // Generar pedido
                case 2: {

                    generarPedido();

                }break;
                // Enviar Pedido
                case 3: {

                    enviarPedido();

                }break;
                // Reporte Inventario
                case 4: {

                    reporteInventario();

                }break;
                // Reporte Pedidos Pendientes
                case 5: {

                    reportePedidosPendientes();

                }break;

                case 6: {
                    salida = false;
                }break;
                default: {
                    cout << "Opci\xA2n inv\xA0lida, vuelva a intentarlo"<<endl;
                    enter();
                }break;
            }
        } else {
            cout << "Opci\xA2n inv\xA0lida, vuelva a intentarlo"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            enter();
        }
    } while(salida);
}

// Funcion para verificar si una cadena representa un numero de 4 digitos
bool esCodigoValido(const string& str) {
    if (str.length() != 4)
        return false;

    for (char c : str) {
        if (!isdigit(c))
            return false;
    }

    return true;
}
// Funcion para verificar si el codigo ya existe en el archivo
bool codigoExiste(const string& codigo, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    string linea;

    while (getline(archivo, linea)) {
        string codigoExistente = linea.substr(0, 4);
        if (codigo == codigoExistente) {
            return true;
        }
    }

    return false;
}

// Funcion para ingresar y verificar los datos de un producto
void agregarProducto() {
    string nombreArchivo = "Productos.txt";
    ofstream archivo(nombreArchivo, ios::app);

    try {
        if (!archivo.is_open()) {
            throw runtime_error("Error al abrir el archivo.");
        }

        Producto nuevoProducto;

        do {
            try {
                string codigo;
                cout << "Ingrese el c\xA2\digo de 4 d\xA1\gitos: ";
                cin >> codigo;

                if (!esCodigoValido(codigo)) {
                    throw invalid_argument("C\xA2\digo inv\xA0lido. Ingrese un c\xA2\digo v\xA0lido.");
                }

                if (codigoExiste(codigo, nombreArchivo)) {
                    throw runtime_error("El c\xA2\digo ya existe en el archivo. Ingrese un c\xA2\digo diferente.");
                }

                nuevoProducto.codigo = codigo;
                break;
            } catch (const exception& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Error: " << e.what() << endl;
            }
        } while (true);

        cin.ignore();
        cout << "Ingrese el nombre del producto: ";
        getline(cin, nuevoProducto.nombre);

        do {
            cout << "Ingrese la cantidad disponible: ";
            cin >> nuevoProducto.cantidad;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Cantidad inv\xA0lida. Ingrese un n\xA3mero v\xA0lido. \n";
                enter();
            } else {
                break;
            }
        } while (true);

        // Escribir el producto en el archivo
        archivo << nuevoProducto.codigo << "," << nuevoProducto.nombre << "," << nuevoProducto.cantidad << "\n";
        archivo.close();

        cout << "Producto agregado correctamente al archivo. \n" << endl;
        enter();

        cout << "Desea agregar otro producto? (S/N): ";
        char respuesta;
        cin >> respuesta;
        respuesta=toupper(respuesta);

        if (respuesta == 'S') {
            system("cls");
            agregarProducto();
        }
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

// Funcion para consultar un producto por su codigo
void consultarProducto(const set<int>& codigosExistentes) {
    system("cls");

     try {
        ifstream archivo("Productos.txt");
        if (!archivo.is_open()) {
            throw runtime_error("Error al abrir el archivo.");
        }

        //Leer el archivo y almacenar los datos en un vector de productos
        vector<Producto> productos;
        string linea;

        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string codigo, nombre;
            int cantidad;
            getline(ss, codigo, ',');
            getline(ss, nombre, ',');
            ss >> cantidad;
            productos.push_back({codigo, nombre, cantidad});
        }

        //Consultar el codigo de 4 digitos y obtener el producto correspondiente
        string codigoConsultado;
        bool codigoEsValido = false;

        while (!codigoEsValido) {
            cout << "Ingrese el c\xA2\digo de 4 d\xA1gitos que desea consultar: ";
            cin >> codigoConsultado;

            // Asegurarse de que el codigo consultado tenga exactamente 4 digitos
            if (!esCodigoValido(codigoConsultado)) {
                throw invalid_argument("El c\xA2\digo debe tener 4 d\xA1gitos num\x82ricos. Intente nuevamente.");
            } else {
                codigoEsValido = true;
            }
        }

        bool encontrado = false;
        for (const auto& producto : productos) {
            if (producto.codigo == codigoConsultado) {
                cout << "C\xA2\digo del producto: " << producto.codigo << endl;
                cout << "Nombre del producto: " << producto.nombre << endl;
                cout << "Cantidad disponible: " << producto.cantidad << endl;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "Producto no encontrado." << endl;
        }
        return;
    } catch (const exception& e) {
        cerr << "Excepci\xA2n: " << e.what() << endl;
        return;
    }
}

// Funcion para eliminar un producto por codigo
void eliminarProducto() {
    string nombreArchivo = "Productos.txt";

    try {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            throw runtime_error("Error al abrir el archivo.");
        }

        string codigo;
        Producto productoAEliminar;
        vector<string> lineasRestantes;
        bool productoEncontrado = false;

        do {
            try {
                cout << "Ingrese el c\xA2\digo del producto que desea eliminar: ";
                cin >> codigo;

                if (!esCodigoValido(codigo)) {
                    throw runtime_error("C\xA2\digo inv\xA0lido. Ingrese un c\xA2\digo v\xA0lido.");
                }

                if (!codigoExiste(codigo, nombreArchivo)) {
                    throw runtime_error("El c\xA2\digo no existe en el archivo.");
                }

                // Leer los datos del producto que se eliminara (sacado de internet)
                string linea;
                while (getline(archivo, linea)) {
                    string codigoExistente = linea.substr(0, 4);
                    if (codigo != codigoExistente) {
                        lineasRestantes.push_back(linea);
                    } else {
                        productoAEliminar.codigo = codigoExistente;

                        // Obtener la posicion de la primera y segunda coma en la linea
                        size_t posPrimeraComa = linea.find(',');
                        size_t posSegundaComa = linea.find(',', posPrimeraComa + 1);

                        // El nombre esta despues del codigo y de la primera coma
                        productoAEliminar.nombre = linea.substr(posPrimeraComa + 1, posSegundaComa - posPrimeraComa - 1);

                        // La cantidad esta despues de la segunda coma
                        try {
                            productoAEliminar.cantidad = stoi(linea.substr(posSegundaComa + 1));
                        } catch (const invalid_argument& e) {
                            productoAEliminar.cantidad = 0;
                        }

                        productoEncontrado = true;
                    }
                }
                archivo.clear();
                archivo.seekg(0, ios::beg); // Regresar al principio del archivo (sacado de internet)

                break;
            } catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << e.what() << endl;
            }
        } while (true);

        archivo.close();

        if (!productoEncontrado) {
            throw runtime_error("El producto no se encontr\xA2 en el archivo.");
        }

        // Escribir el contenido actualizado en el archivo original
        ofstream archivoSalida(nombreArchivo);
        if (!archivoSalida.is_open()) {
            throw runtime_error("Error al abrir el archivo para escritura.");
        }

        for (const auto& linea : lineasRestantes) {
            archivoSalida << linea << "\n";
        }

        archivoSalida.close();

        // Mostrar informacion del producto a eliminar
        cout << "\nInformaci\xA2n del producto a eliminar:\n";
        cout << "C\xA2\digo: " << productoAEliminar.codigo << endl;
        cout << "Nombre: " << productoAEliminar.nombre << endl;
        cout << "Cantidad: " << productoAEliminar.cantidad << endl;

        cout << "\nEst\xA0 seguro de que desea eliminar este producto? (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        confirmacion=toupper(confirmacion);

        if (confirmacion == 'S') {
            cout << "Producto eliminado correctamente del archivo.\n";
        } else {
            if (productoEncontrado) {
                // Agregar el producto nuevamente al archivo
                ofstream archivoSalida(nombreArchivo, ios_base::app);
                archivoSalida << productoAEliminar.codigo << "," << productoAEliminar.nombre << "," << productoAEliminar.cantidad << "\n";
                archivoSalida.close();
                cout << "Eliminaci\xA2n cancelada. El producto ha sido restaurado en el archivo.\n";
            } else {
                cout << "No se encontr\xA2 el producto en el archivo. No se realizaron cambios.\n";
            }
        }

        enter();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Desea ELIMINAR otro producto? (S/N): ";
        char respuesta;
        cin >> respuesta;
        respuesta=toupper(respuesta);

        if (respuesta == 'S') {
            system("cls");
            eliminarProducto();
        }
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
}

// Funcion para actualizar la cantidad de productos (sacado de internet)
string actualizarCantidad(const string& codigo, int cantidad, vector<Producto>& productos) {
    string resultado;
    for (auto& producto : productos) {
        if (producto.codigo == codigo) {
            producto.cantidad -= cantidad;
        }
        resultado += producto.codigo + "," + producto.nombre + "," + to_string(producto.cantidad) + "\n";
    }
    return resultado;
}

// Funcion para generar los pedidos
void generarPedido() {
    string nombreArchivoProductos = "Productos.txt";
    string nombreArchivoPedidos = "Pedidos.txt";

    try {
        ofstream archivoPedidos(nombreArchivoPedidos, ios::app);
        if (!archivoPedidos.is_open()) {
            throw runtime_error("Error al abrir el archivo de pedidos para escritura.");
        }

        vector<Producto> productosDisponibles;

        // Leer los productos disponibles del archivo "Productos.txt"
        ifstream archivoProductos(nombreArchivoProductos);
        if (!archivoProductos.is_open()) {
            throw runtime_error("Error al abrir el archivo de productos.");
        }

        string linea;
        while (getline(archivoProductos, linea)) {
            Producto producto;
            producto.codigo = linea.substr(0, 4);

            size_t posPrimeraComa = linea.find(',');
            size_t posSegundaComa = linea.find(',', posPrimeraComa + 1);

            producto.nombre = linea.substr(posPrimeraComa + 1, posSegundaComa - posPrimeraComa - 1);

            string cantidadStr = linea.substr(posSegundaComa + 1);
            producto.cantidad = stoi(cantidadStr);

            productosDisponibles.push_back(producto);
        }

        archivoProductos.close();

        // Generar un codigo de pedido aleatorio
        srand(static_cast<unsigned int>(time(0)));
        int codigoPedido = rand() % 10000;

        // Solicitar el nombre para el pedido
        system("cls");
        string nombrePedido;
        if (nombrePedido.empty()) {
            cout << "Ingrese el nombre para el pedido: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nombrePedido);
        }

        vector<Producto> productosPedido;
        do {
            Producto productoPedido;

            // Solicitar el codigo del producto a agregar
            do {
                try {
                    string codigo;
                    cout << "Ingrese el c\xA2\digo de 4 d\xA1gitos del producto a agregar: ";
                    cin >> codigo;

                    if (!esCodigoValido(codigo)) {
                        throw invalid_argument("C\xA2\digo inv\xA0lido. Ingrese un c\xA2\digo v\xA0lido.");
                    }

                    if (!codigoExiste(codigo, nombreArchivoProductos)) {
                        throw runtime_error("El c\xA2\digo no existe en el archivo de productos.");
                    }

                    // Buscar el producto disponible en el vector (sacado de internet)
                    auto it = find_if(productosDisponibles.begin(), productosDisponibles.end(), [codigo](const Producto& p) { return p.codigo == codigo; });

                    if (it != productosDisponibles.end()) {
                        productoPedido.codigo = it->codigo;
                        productoPedido.nombre = it->nombre;

                        cout << "Producto a agregar:\n";
                        cout << "C\xA2\digo: " << productoPedido.codigo << endl;
                        cout << "Nombre: " << productoPedido.nombre << endl;

                        break;
                    } else {
                        throw runtime_error("El c\xA2\digo existe en el archivo, pero no se encontr\xA2 en la lista de productos disponibles.");
                    }
                } catch (const exception& e) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cerr << "Error: " << e.what() << endl;
                }
            } while (true);

            // Solicitar la cantidad del producto a agregar (sacado de internet)
            do {
                try {
                    auto it = find_if(productosDisponibles.begin(), productosDisponibles.end(), [productoPedido](const Producto& p) { return p.codigo == productoPedido.codigo; });

                    if (it == productosDisponibles.end()) {
                        throw runtime_error("El c\xA2\digo del producto no es v\xA0lido.");
                    }

                    cout << "Ingrese la cantidad a agregar del producto (Hay: " << it->cantidad << "): ";
                    cin >> productoPedido.cantidad;

                    if (productoPedido.cantidad <= 0) {
                        throw invalid_argument("La cantidad debe ser mayor a 0.");
                    }

                    // Verificar que la cantidad a agregar no exceda la cantidad disponible (sacado de internet)
                    auto itDisponible = find_if(productosDisponibles.begin(), productosDisponibles.end(), [productoPedido](const Producto& p) { return p.codigo == productoPedido.codigo; });

                    if (itDisponible != productosDisponibles.end() && productoPedido.cantidad > itDisponible->cantidad) {
                        throw runtime_error("La cantidad a agregar excede la cantidad disponible.");
                    }

                    break;
                } catch (const exception& e) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cerr << "Error: " << e.what() << endl;
                }
            } while (true);

            productosPedido.push_back(productoPedido);

            // Imprimir un resumen de lo que lleva
            cout << "\nResumen del pedido actual:\n";
            cout << left << setw(10) << "C\xA2\digo" << setw(30) << "Nombre del producto" << setw(10) << "Cantidad" << endl;
            cout << setfill('-') << setw(52) << "-" << setfill(' ') << endl;

            for (const auto& productoPedido : productosPedido) {
                cout << left << setw(10) << productoPedido.codigo << setw(30) << productoPedido.nombre << setw(10) << productoPedido.cantidad << endl;
            }

            // Preguntar si se desea agregar otro producto
            cout << "Desea agregar otro producto al pedido? (S/N): ";
            char respuesta;
            cin >> respuesta;
            respuesta = toupper(respuesta);
            if (respuesta != 'S') {
                break;
            }
        } while (true);

        // Actualizar el vector con las cantidades despues del pedido
        for (const auto& productoPedido : productosPedido) {
            string datosActualizados = actualizarCantidad(productoPedido.codigo, productoPedido.cantidad, productosDisponibles);
            // Actualizar el archivo "Productos.txt"
            ofstream archivoProductos(nombreArchivoProductos);
            if (!archivoProductos.is_open()) {
                throw runtime_error("Error al abrir el archivo de productos para escritura.");
            }
            archivoProductos << datosActualizados;
            archivoProductos.close();

            // Guardar la informacion del producto en el archivo "Pedidos.txt"
            archivoPedidos << setfill('0') << setw(4) << codigoPedido << "," << nombrePedido << "," << productoPedido.codigo << "," << productoPedido.cantidad << "," << "N\n";
        }

        archivoPedidos.close();

        nombrePedido.clear(); // Para cambiar nombre en pedidos distintos

        cout << "Pedido generado correctamente.\n";
        enter();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// Funcion para enviar pedidos
void enviarPedido() {

    char seguir;
    do {

        system("cls");
        string codigoPedido;

        while (true) {
            try {
                cout << "Ingrese el c\xA2\digo del pedido a enviar: ";
                cin >> codigoPedido;

                if (!esCodigoValido(codigoPedido)) {
                    throw invalid_argument("C\xA2\digo de pedido inv\xA0lido. Debe ser un n\xA3mero de 4 d\xA1gitos.");
                }

                break;
            } catch (const invalid_argument& ia) {
                cout << ia.what() << " Por favor, intente de nuevo.\n" << endl;
            }
    }

        ifstream inputFile("Pedidos.txt");

        if (!inputFile) {
            cout << "Error al abrir el archivo de pedidos." << endl;
            enter();
            return;
        }

        vector<string> lines;
        string line;

        bool pedidoEncontrado = false;
        bool pedidoParaEnviar = false;

        while (getline(inputFile, line)) {
            string codigoEnArchivo = line.substr(0, 4); // Obtener los primeros 4 caracteres (codigo de pedido)
            if (codigoEnArchivo == codigoPedido) {
                pedidoEncontrado = true;
                if (line.back() == 'N') {
                    if (!pedidoParaEnviar) {
                        cout << "Desea enviar este pedido? (S/N): ";
                        char respuesta;
                        cin >> respuesta;
                        respuesta=toupper(respuesta);

                        if (respuesta == 'S') {
                            pedidoParaEnviar = true;
                        }
                    }

                    if (pedidoParaEnviar) {
                        line.back() = 'S';
                    }
                } else {
                    cout << "El pedido con c\xA2\digo " << codigoPedido << " ya ha sido enviado anteriormente." << endl;
                }
            }

            lines.push_back(line);

        }

        inputFile.close();

        if (!pedidoEncontrado) {
            cout << "Pedido no encontrado." << endl;
            enter();
            return;
        }

        ofstream outputFile("Pedidos.txt");
        if (!outputFile) {
            cout << "Error al abrir el archivo de pedidos para escritura." << endl;
            enter();
            return;
        }

        for (const auto& line : lines) {
            outputFile << line << endl;
        }

        outputFile.close();

        cout << "El pedido con c\xA2\digo " << codigoPedido << " ha sido enviado. \n" << endl;
        enter();

        cout << "Desea enviar otro pedido? (S/N): ";
        cin >> seguir;
        seguir = toupper(seguir);
    } while (seguir == 'S');
}

// Funcion para hacer el reporte de inventario
void reporteInventario() {
    system("cls");
    ifstream archivoProductos("Productos.txt");

    if (!archivoProductos.is_open()) {
        cout << "Error al abrir el archivo de productos." << endl;
        return;
    }

    cout << "Reporte de Inventario\n" << endl;
    cout << left << setw(20) << "C\xA2\digo Producto" << setw(30) << "Nombre Producto" << setw(20) << "Cantidad Disponible" << endl;
    cout << setfill('-') << setw(72) << "-" << setfill(' ') << endl;

    string linea;
    while (getline(archivoProductos, linea)) {
        string codigo = linea.substr(0, 4);

        size_t posPrimeraComa = linea.find(',');
        size_t posSegundaComa = linea.find(',', posPrimeraComa + 1);

        string nombre = linea.substr(posPrimeraComa + 1, posSegundaComa - posPrimeraComa - 1);
        string cantidadStr = linea.substr(posSegundaComa + 1);
        int cantidad = stoi(cantidadStr);

        cout << left << setw(20) << codigo << setw(30) << nombre << setw(20) << cantidad << endl;
    }

    archivoProductos.close();

    cout << "" << endl;
    enter();
}

// Funcion para reporte de pedidos pendientes
void reportePedidosPendientes() {
    system("cls");
    ifstream archivoPedidos("Pedidos.txt");

    if (!archivoPedidos.is_open()) {
        cout << "Error al abrir el archivo de pedidos." << endl;
        return;
    }

    cout << "Reporte de Pedidos Pendientes\n" << endl;
    cout << left << setw(20) << "C\xA2\digo Pedido" << setw(30) << "Nombre Pedido" << setw(20) << "C\xA2\digo Producto" << setw(15) << "Cantidad" << setw(10) << "Enviado" << endl;
    cout << setfill('-') << setw(95) << "-" << setfill(' ') << endl;

    string linea;
    while (getline(archivoPedidos, linea)) {
        if (linea.back() == 'N') {
            string codigoPedido = linea.substr(0, 4);

            size_t posPrimeraComa = linea.find(',');
            size_t posSegundaComa = linea.find(',', posPrimeraComa + 1);
            size_t posTerceraComa = linea.find(',', posSegundaComa + 1);
            size_t posCuartaComa = linea.find(',', posTerceraComa + 1);

            string nombrePedido = linea.substr(posPrimeraComa + 1, posSegundaComa - posPrimeraComa - 1);
            string codigoProducto = linea.substr(posSegundaComa + 1, posTerceraComa - posSegundaComa - 1);
            string cantidadStr = linea.substr(posTerceraComa + 1, posCuartaComa - posTerceraComa - 1);
            int cantidad = stoi(cantidadStr);

            cout << left << setw(20) << codigoPedido << setw(30) << nombrePedido << setw(20) << codigoProducto << setw(15) << cantidad << setw(10) << "N" << endl;
        }
    }
    cout << "" << endl;
    enter();

    archivoPedidos.close();
}

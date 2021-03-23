#include <iostream>
#include <list>
#include <string>

/**>
 * @brief En la clase motores de define el destructor de los Observadores(motores) y se crea la funcion de actualizar
 */
class Motores {
public:
    virtual ~Motores(){};
    virtual void Actualizar(const std::string &message_from_subject) = 0;
};

/**>
 * @brief En la clase carro se crea el destructor del objeto carro(observado) junto con su lista de observadores y el metodo de notificacion. Tambien una funcion para agregar y eliminar observadores
 */
class carro {
public:
    virtual ~carro(){};
    virtual void Agregar(Motores *observer) = 0;
    virtual void Eliminar(Motores *observer) = 0;
    virtual void Notificar() = 0;
};

/**>
 * @brief Se crea la clase observado que contiene los metodos del objeto observado en este caso el carro
 */
class Observado : public carro {
public:
    virtual ~Observado() {
        std::cout << "APAGANDO CARRO.\n";
    }
    /**>
     * @brief el metodo append permite agregar un nuevo observador a la lista del observado(carro)
     * @param observer objeto que sera el nuevo observador
     */
    void Agregar(Motores *observer) override {
        list_observer_.push_back(observer);
    }
    /**>
     * @brief metodo que permite eliminar a los observadores de un determinadao observado.
     * @param observer Objeto observador que se desea eliminar de la lista de los observadores
     */
    void Eliminar(Motores *observer) override {
        list_observer_.remove(observer);
    }
    /**>
     * @brief metodo que permite noficarle a los observadores alguna accion que haya ocurrido en el observado.
     */
    void Notificar() override {
        std::list<Motores *>::iterator iterator = list_observer_.begin();
        while (iterator != list_observer_.end()) {
            (*iterator)->Actualizar(message_);
            ++iterator;
        }
    }
    /**>
     * @brief Este metodo permite crear ;ps mensajes que se le enviaran a los observadores.
     * @param message variable de texto que contiene el menseja a enviar
     */
    void CrearMensaje(std::string message = "") {
        this->message_ = message;
        Notificar();
    }

private:
    std::list<Motores *> list_observer_;
    std::string message_;
};

/**>
 * @brief Esta clase contiene los metodos de los observadores(motores)
 */

class Observadores :public Motores {
public:
    Observadores(Observado &subject) : carro_(subject) {
        this->carro_.Agregar(this);
        std::cout << "MOTOR NUMERO" << " " << ++Observadores::numero_motor_ << " " << "ENCENDIDO.\n";
        this->numero_ = Observadores::numero_motor_;
    }
    virtual ~Observadores() {
        std::cout << "APAGANDO MOTOR NUMERO " << this->numero_ <<".\n";
    }
    /**>
     * ESte metodo permite al observador(motores) estar consultado sobre los cambios realizados en el observado(carro)
     * @param notificacion_carro mensaje que se enviara en caso de que se desee notificar un cambio
     */
    void Actualizar(const std::string &notificacion_carro) override {
        mensaje_ = notificacion_carro;
        Visualizar();
    }
    /**>
     * @brief Este metodo permite quitar a un observador de la lista de los observadores
     */
    void Eliminar_Lista() {
        carro_.Eliminar(this);
        std::cout << "MOTOR " << numero_ << " " << "FUERA DE SERVICIO.\n";
    }
    /**>
     * @brief ESte metodo permite visualizar las notificaciones enviadas a los observadores
     */
    void Visualizar() {
        std::cout << "MOTOR \"" << this->numero_ << "\": NOTIFICACION DE " << this->mensaje_ << "\n";
    }

private:
    std::string mensaje_;
    Observado &carro_;
    static int numero_motor_;
    int numero_;
};

int Observadores::numero_motor_ = 0;
/**>
 * @brief EL metetodo simulador permite simular una situacion particular en donde un carro es el observado y 5 motores los observadores.
 */
void Simulador() {
    Observado *carro1 = new Observado;
    Observadores *motor1 = new Observadores(*carro1);
    Observadores *motor2 = new Observadores(*carro1);
    Observadores *motor3 = new Observadores(*carro1);
    Observadores *motor4;
    Observadores *motor5;

    carro1->CrearMensaje("ARRANQUE");
    motor3->Eliminar_Lista();

    carro1->CrearMensaje("ACELERACION");
    motor4 = new Observadores(*carro1);

    motor2->Eliminar_Lista();
    motor5 = new Observadores(*carro1);

    carro1->CrearMensaje("FRENADO");
    motor5->Eliminar_Lista();
    motor4->Eliminar_Lista();
    motor1->Eliminar_Lista();

    delete motor5;
    delete motor4;
    delete motor3;
    delete motor2;
    delete motor1;
    delete carro1;
}
/**>
 * Funcion principal que permite ejecutar el simulador
 * @return
 */
int main() {
    Simulador();
    return 0;
}
#include <iostream>

#include <iostream>
#include <list>
#include <string>

class Motores {
public:
    virtual ~Motores(){};
    virtual void Update(const std::string &message_from_subject) = 0;
};

class carro {
public:
    virtual ~carro(){};
    virtual void Attach(Motores *observer) = 0;
    virtual void Detach(Motores *observer) = 0;
    virtual void Notify() = 0;
};


class Subject : public carro {
public:
    virtual ~Subject() {
        std::cout << "APAGANDO CARRO.\n";
    }
    void Attach(Motores *observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(Motores *observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
        std::list<Motores *>::iterator iterator = list_observer_.begin();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }
    void CreateMessage(std::string message = "") {
        this->message_ = message;
        Notify();
    }

private:
    std::list<Motores *> list_observer_;
    std::string message_;
};

class Observer : public Motores {
public:
    Observer(Subject &subject) : carro_(subject) {
        this->carro_.Attach(this);
        std::cout << "MOTOR NUMERO" << " " << ++Observer::numero_motor_ << " " << "ENCENDIDO.\n";
        this->numero_ = Observer::numero_motor_;
    }
    virtual ~Observer() {
        std::cout << "APAGANDO MOTOR NUMERO " << this->numero_ <<".\n";
    }

    void Update(const std::string &notificacion_carro) override {
        mensaje_ = notificacion_carro;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        carro_.Detach(this);
        std::cout << "MOTOR " << numero_ << " " << "FUERA DE SERVICIO.\n";
    }
    void PrintInfo() {
        std::cout << "MOTOR \"" << this->numero_ << "\": NOTIFICACION DE --> " << this->mensaje_ << "\n";
    }

private:
    std::string mensaje_;
    Subject &carro_;
    static int numero_motor_;
    int numero_;
};

int Observer::numero_motor_ = 0;

void Simulador() {
    Subject *carro1 = new Subject;
    Observer *motor1 = new Observer(*carro1);
    Observer *motor2 = new Observer(*carro1);
    Observer *motor3 = new Observer(*carro1);
    Observer *motor4;
    Observer *motor5;

    carro1->CreateMessage("ARRANQUE");
    motor3->RemoveMeFromTheList();

    carro1->CreateMessage("ACELERACION");
    motor4 = new Observer(*carro1);

    motor2->RemoveMeFromTheList();
    motor5 = new Observer(*carro1);

    carro1->CreateMessage("FRENADO");
    motor5->RemoveMeFromTheList();
    motor4->RemoveMeFromTheList();
    motor1->RemoveMeFromTheList();

    delete motor5;
    delete motor4;
    delete motor3;
    delete motor2;
    delete motor1;
    delete carro1;
}
int main() {
    Simulador();
    return 0;
}
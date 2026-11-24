#include <iostream>
#include <string>
#include <exception>
using namespace std;

class ExceptieVehicul : public exception {
public:
    const char* what() const noexcept override {
        return "Pret prea mic!";
    }
};

class Vehicul {
protected:
    const int id;
    string marca;
    float pret;

public:
    static const float PRET_MINIM;

    Vehicul() : id(0), marca("Dacia"), pret(10000) {}

    Vehicul(int idV, string marcaV, float pretV)
        : id(idV), marca(marcaV), pret(pretV) {
        if (pret < PRET_MINIM) {
            throw ExceptieVehicul();
        }
    }

    virtual void afisare() {
        cout << endl << "Id: " << id;
        cout << endl << "Marca: " << marca;
        cout << endl << "Pret: " << pret;
    }

    virtual float getTaxa() = 0;

    virtual ~Vehicul() {}
};

const float Vehicul::PRET_MINIM = 1000;

class Masina : public Vehicul {
private:
    float procentTaxa;

public:
    Masina() : Vehicul() {
        procentTaxa = 0;
    }

    Masina(int idV, string marcaV, float pretV, float procentTaxaV)
        : Vehicul(idV, marcaV, pretV) {
        procentTaxa = procentTaxaV;
    }

    void afisare() override {
        Vehicul::afisare();
        cout << endl << "Procent taxa: " << procentTaxa;
    }

    float getTaxa() override {
        return pret * procentTaxa / 100;
    }
};

class OperatiiVehicul {
public:
    virtual float adunarePreturi(float a, float b) = 0;
    virtual float scaderePreturi(float a, float b) = 0;
    virtual ~OperatiiVehicul() {}
};

class CalculatorVehicul : public OperatiiVehicul {
public:
    float adunarePreturi(float a, float b) override {
        return a + b;
    }

    float scaderePreturi(float a, float b) override {
        return a - b;
    }
};

int main() {
    Vehicul* vectorVehicule[3] = { nullptr, nullptr, nullptr };

    try {
        vectorVehicule[0] = new Masina(1, "BMW", 50000, 10);
        vectorVehicule[1] = new Masina(2, "Audi", 60000, 15);
        vectorVehicule[2] = new Masina(3, "Dacia", 20000, 5);

        for (int i = 0; i < 3; i++) {
            vectorVehicule[i]->afisare();
            cout << endl << "Taxa: " << vectorVehicule[i]->getTaxa() << endl;
            delete vectorVehicule[i];
            vectorVehicule[i] = nullptr;
        }

        Vehicul* pVehicul = new Masina();
        pVehicul->afisare();
        cout << endl;
        delete pVehicul;

        OperatiiVehicul* calcul = new CalculatorVehicul();

        cout << endl << "Suma preturi: " << calcul->adunarePreturi(50000, 20000);
        cout << endl << "Diferenta preturi: " << calcul->scaderePreturi(50000, 20000) << endl;

        delete calcul;
    }
    catch (const exception& e) {
        cout << endl << "Eroare: " << e.what() << endl;
        for (int i = 0; i < 3; i++) {
            delete vectorVehicule[i];
        }
    }

    return 0;
}
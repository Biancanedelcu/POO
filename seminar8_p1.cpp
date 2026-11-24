#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
using namespace std;

class ExceptieSalariu : public exception {
public:
    const char* what() const noexcept override {
        return "Salariu prea mic!";
    }
};

class Angajat {
protected:
    const int id;
    string nume;
    float salariu;

public:
    static const float SALARIU_MINIM;

    Angajat() : id(0), nume("Necunoscut"), salariu(3000) {}

    Angajat(int idA, string numeA, float salariuA)
        : id(idA), nume(numeA), salariu(salariuA) {
        if (salariu < SALARIU_MINIM) {
            throw ExceptieSalariu();
        }
    }

    virtual void afisare() {
        cout << endl << "Id: " << id;
        cout << endl << "Nume: " << nume;
        cout << endl << "Salariu: " << salariu;
    }

    virtual float getBonus() = 0;

    virtual ~Angajat() {}
};

const float Angajat::SALARIU_MINIM = 2500;

class AngajatPermanent : public Angajat {
private:
    float procentBonus;

public:
    AngajatPermanent() : Angajat() {
        procentBonus = 0;
    }

    AngajatPermanent(int idA, string numeA,
        float salariuA, float procentBonusA)
        : Angajat(idA, numeA, salariuA) {
        procentBonus = procentBonusA;
    }

    void afisare() override {
        Angajat::afisare();
        cout << endl << "Procent bonus: " << procentBonus;
    }

    float getBonus() override {
        return salariu * procentBonus / 100;
    }
};

class OperatiiSalariu {
public:
    virtual float calculSalariuNet(float salariu) = 0;
    virtual float calculSalariuAnual(float salariu) = 0;
    virtual ~OperatiiSalariu() {}
};

class CalculatorSalariu : public OperatiiSalariu {
public:
    float calculSalariuNet(float salariu) override {
        return salariu * 0.65f;
    }

    float calculSalariuAnual(float salariu) override {
        return salariu * 12;
    }
};

int main() {
    try {
        Angajat* vectorAngajati[3];

        vectorAngajati[0] =
            new AngajatPermanent(1, "Ion", 4000, 10);
        vectorAngajati[1] =
            new AngajatPermanent(2, "Maria", 5000, 15);
        vectorAngajati[2] =
            new AngajatPermanent(3, "Andrei", 6000, 20);

        for (int i = 0; i < 3; i++) {
            vectorAngajati[i]->afisare();
            cout << endl << "Bonus: "
                 << vectorAngajati[i]->getBonus();
            cout << endl;
            delete vectorAngajati[i];
        }

        Angajat* pAngajat = new AngajatPermanent();
        pAngajat->afisare();
        delete pAngajat;

        OperatiiSalariu* calcul = new CalculatorSalariu();

        cout << endl << "Salariu net: "
             << calcul->calculSalariuNet(5000);
        cout << endl << "Salariu anual: "
             << calcul->calculSalariuAnual(5000);

        delete calcul;
    }
    catch (const exception& e) {
        cout << endl << e.what();
    }

    return 0;
}
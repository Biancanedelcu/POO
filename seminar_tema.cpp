#include<iostream>
#include<string>

using namespace std;

class ExceptieCustom : public exception {
private:
	string mesaj;
public:
	ExceptieCustom(const char* mesaj) : mesaj(mesaj) {}

	const char* what() const noexcept override {
		return mesaj.c_str();
	}
};

class Produs {
protected:
	const int id;
	string denumire;
	float pret;
public:
	static const float PRET_MINIM;
	Produs() : id(0), denumire("Laptop"), pret(5000) {
	}

	Produs(int idP, string denumireP, float pretP) : id(idP), denumire(denumireP), pret(pretP) {
		if (pret < PRET_MINIM) {
			throw ExceptieCustom("Pret prea mic!");
		}
	}

	virtual void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret: " << this->pret;
	}

	virtual float getProcentReducere() = 0;

	virtual ~Produs() {
	}
};

const float Produs::PRET_MINIM = 1;

class ProdusRedus : public Produs {
private:
	float procentReducere;
public:
	ProdusRedus() : Produs() {
		this->procentReducere = 0;
	}

	ProdusRedus(int idP, string denumireP, float pretP, float procentReducereP) : Produs(idP, denumireP, pretP) {
		this->procentReducere = procentReducereP;
	}

	void afisare() override {
		this->Produs::afisare();
		cout << endl << "Procent Reducere: " << this->procentReducere << "%";
	}

	float getProcentReducere() override {
		return this->procentReducere;
	}
};

class Operatie {
public:
	virtual int adunare(int a, int b) = 0;
	virtual int scadere(int a, int b) = 0;
	virtual int inmultire(int a, int b) = 0;
	virtual float impartire(int a, int b) = 0;
	virtual ~Operatie() {}
};

class Calculator : public Operatie {
public:
	Calculator() {
	}

	int adunare(int a, int b) override {
		return a + b;
	}

	int scadere(int a, int b) override {
		return a - b;
	}

	int inmultire(int a, int b) override {
		return a * b;
	}

	float impartire(int a, int b) override {
		if (b == 0) {
			throw ExceptieCustom("Impartire la zero!");
		}
		return (float)a / b;
	}
};

int main() {
	Calculator calc;
	cout << "Adunare: " << calc.adunare(10, 5) << endl;
	cout << "Scadere: " << calc.scadere(10, 5) << endl;
	cout << "Inmultire: " << calc.inmultire(10, 5) << endl;
	
	try {
		cout << "Impartire: " << calc.impartire(10, 4) << endl;
		cout << "Impartire la zero: " << calc.impartire(10, 0) << endl;
	}
	catch (const ExceptieCustom& e) {
		cout << "Eroare: " << e.what() << endl;
	}

	return 0;
}
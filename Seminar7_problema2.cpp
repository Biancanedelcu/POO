#include<iostream>
#include<string>

using namespace std;

enum Utilizare { GAMING = 9, OFFICE = 3, ULTRABOOK = 6 };

class Laptop {
private:
	const int id;
	float pret;
	string model;
	Utilizare utilizare;
	int nrNuclee;
	float* frecventeNuclee;
	static int nrLaptopuri;

public:
	Laptop() : id(++nrLaptopuri) {
		this->model = "Model standard";
		this->pret = 0;
		this->nrNuclee = 0;
		this->frecventeNuclee = nullptr;
		this->utilizare = OFFICE;
	}

	Laptop(string model, float pret, int nrNuclee, float* frecvente, Utilizare utilizare) : id(++nrLaptopuri) {
		this->model = model;
		this->pret = pret;
		this->nrNuclee = nrNuclee;
		this->frecventeNuclee = new float[this->nrNuclee];
		for (int i = 0; i < this->nrNuclee; i++) {
			this->frecventeNuclee[i] = frecvente[i];
		}
		this->utilizare = utilizare;

		delete[] frecvente;
	}

	Laptop(const Laptop& copie) : id(++nrLaptopuri) {
		this->pret = copie.pret;
		this->model = copie.model;
		this->utilizare = copie.utilizare;
		this->nrNuclee = copie.nrNuclee;

		if (copie.frecventeNuclee != nullptr) {
			this->frecventeNuclee = new float[copie.nrNuclee];
			for (int i = 0; i < copie.nrNuclee; i++) {
				this->frecventeNuclee[i] = copie.frecventeNuclee[i];
			}
		}
		else {
			this->frecventeNuclee = nullptr;
		}
	}

	void operator=(const Laptop& copie) {
		this->model = copie.model;
		this->pret = copie.pret;
		this->utilizare = copie.utilizare;
		this->nrNuclee = copie.nrNuclee;

		if (this->frecventeNuclee != nullptr) {
			delete[] this->frecventeNuclee;
			this->frecventeNuclee = nullptr;
		}

		if (copie.frecventeNuclee != nullptr) {
			this->frecventeNuclee = new float[copie.nrNuclee];
			for (int i = 0; i < copie.nrNuclee; i++) {
				this->frecventeNuclee[i] = copie.frecventeNuclee[i];
			}
		}
		else {
			this->frecventeNuclee = nullptr;
		}
	}

	void afisareLaptop() {
		cout << endl << this->id << ". Laptopul " << this->model << " costa " << this->pret << " lei, este pentru ";
		if (this->utilizare == OFFICE) cout << "OFFICE";
		if (this->utilizare == GAMING) cout << "GAMING";
		if (this->utilizare == ULTRABOOK) cout << "ULTRABOOK";
		cout << " si are " << this->nrNuclee << " nuclee cu frecventele: ";
		if (this->frecventeNuclee != nullptr && this->nrNuclee > 0) {
			for (int i = 0; i < this->nrNuclee - 1; i++) {
				cout << this->frecventeNuclee[i] << " GHz, ";
			}
			cout << this->frecventeNuclee[this->nrNuclee - 1] << " GHz.";
		}
	}

	~Laptop() {
		if (this->frecventeNuclee != nullptr) {
			delete[] this->frecventeNuclee;
		}
	}

	void operator+=(float valoareDeAdaugat) {
		this->pret += valoareDeAdaugat;
	}

	bool operator>(const Laptop& l) {
		return this->pret > l.pret;
	}

	bool operator>=(int x) const {
		if (this->nrNuclee >= x)
			return true;
		return false;
	}

	bool operator<=(int x) const {
		if (this->pret <= x)
			return true;
		return false;
	}

	bool operator!() {
		return this->pret > 0;
	}

	float operator()(int nrElemente) {
		float s = 0, ma = 0;
		for (int i = 0; i < this->nrNuclee; i++)
			s += this->frecventeNuclee[i];
		if (this->nrNuclee != 0)
			ma = s / this->nrNuclee;

		return ma;
	}

	float& operator[](int index) {
		if (index >= 0 && index < this->nrNuclee) {
			return this->frecventeNuclee[index];
		}
		else
			throw exception();
	}

	friend void operator<<(ostream& out, Laptop l) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << l.id;
		out << endl << "Model: " << l.model;
		out << endl << "Pret: " << l.pret;
		out << endl << "Utilizare: ";
		if (l.utilizare == OFFICE) out << "OFFICE";
		if (l.utilizare == GAMING) out << "GAMING";
		if (l.utilizare == ULTRABOOK) out << "ULTRABOOK";
		out << endl << "Nr nuclee: " << l.nrNuclee;

		if (l.frecventeNuclee != nullptr && l.nrNuclee > 0) {
			out << endl << "Frecvente nuclee: ";
			for (int i = 0; i < l.nrNuclee - 1; i++) {
				out << l.frecventeNuclee[i] << " GHz, ";
			}
			out << l.frecventeNuclee[l.nrNuclee - 1] << " GHz.";
		}
	}

	friend void operator>>(istream& in, Laptop& l) {
		cout << endl << "Pret: ";
		in >> l.pret;

		cout << endl << "Model: ";
		in >> l.model;

		cout << endl << "Utilizare (3-OFFICE, 6-ULTRABOOK, 9-GAMING): ";
		int util;
		in >> util;
		if (util == 3) l.utilizare = OFFICE;
		if (util == 9) l.utilizare = GAMING;
		if (util == 6) l.utilizare = ULTRABOOK;

		cout << endl << "Nr nuclee: ";
		in >> l.nrNuclee;

		cout << endl << "Frecvente nuclee: ";
		if (l.frecventeNuclee != nullptr) {
			delete[] l.frecventeNuclee;
			l.frecventeNuclee = nullptr;
		}

		l.frecventeNuclee = new float[l.nrNuclee];
		for (int i = 0; i < l.nrNuclee; i++) {
			cout << endl << "Frecventa[" << i << "]: ";
			in >> l.frecventeNuclee[i];
		}
	}

	Laptop operator++(int) {
		Laptop copie = *this;
		this->pret++;

		return copie;
	}

	Laptop operator++() {
		this->pret++;
		return *this;
	}

	explicit operator int() {
		return this->nrNuclee;
	}

	explicit operator string() {
		return this->model;
	}
};

int Laptop::nrLaptopuri = 0;

int main() {
	Laptop lenovo;
	lenovo.afisareLaptop();

	float* frecvente = new float[4] { 3.2, 3.5, 4.1, 4.5 };
	Laptop* rog = new Laptop("Asus ROG", 5500, 4, frecvente, GAMING);
	rog->afisareLaptop();

	if (!lenovo) {
		cout << endl << "Pretul este mai mare decat 0!";
	}
	else {
		cout << endl << "Pretul este mai mic sau egal cu 0!";
	}

	cout << endl << endl;
	if ((*rog) >= 4) {
		cout << "Laptopul are minim 4 nuclee";
	}
	else {
		cout << "Laptopul are sub 4 nuclee";
	}

	cout << endl << endl << "Media frecventelor este de " << (*rog)(4) << " GHz";
	cout << endl << endl;

	if (lenovo <= 3000) {
		cout << "Acest laptop costa pana in 3000 de lei";
	}
	else {
		cout << "Acest laptop este mai scump de 3000 de lei!";
	}

	for (int i = 0; i < 4; i++) {
		cout << endl << "Frecventele dublate sunt: " << (*rog)[i] * 2 << " ";
	}

	Laptop l1 = lenovo++;
	Laptop l2 = ++lenovo;

	cout << l1;
	cout << l2;

	cout << endl << (int)l2;
	cout << endl << (int)(lenovo);
	cout << endl << endl << string(lenovo);

	delete rog;

	return 0;
}
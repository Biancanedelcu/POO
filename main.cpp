#include<iostream>
#include<string>

using namespace std;

enum GenLiterar { SF = 8, ROMAN = 4, ISTORIE = 2 };

class Carte {
private:
	const int id;
	float pret;
	string titlu;
	GenLiterar gen;
	int nrCapitole;
	float* paginiPerCapitol;
	static int nrCarti;

public:
	Carte() : id(++nrCarti) {
		this->titlu = "Necunoscut";
		this->pret = 0;
		this->nrCapitole = 0;
		this->paginiPerCapitol = nullptr;
		this->gen = ROMAN;
	}

	Carte(string titlu, float pret, int nrCapitole, float* pagini, GenLiterar gen) : id(++nrCarti) {
		this->titlu = titlu;
		this->pret = pret;
		this->nrCapitole = nrCapitole;
		this->paginiPerCapitol = new float[this->nrCapitole];
		for (int i = 0; i < this->nrCapitole; i++) {
			this->paginiPerCapitol[i] = pagini[i];
		}
		this->gen = gen;

		delete[] pagini;
	}

	Carte(const Carte& copie) : id(++nrCarti) {
		this->pret = copie.pret;
		this->titlu = copie.titlu;
		this->gen = copie.gen;
		this->nrCapitole = copie.nrCapitole;

		if (copie.paginiPerCapitol != nullptr) {
			this->paginiPerCapitol = new float[copie.nrCapitole];
			for (int i = 0; i < copie.nrCapitole; i++) {
				this->paginiPerCapitol[i] = copie.paginiPerCapitol[i];
			}
		}
		else {
			this->paginiPerCapitol = nullptr;
		}
	}

	void operator=(const Carte& copie) {
		this->titlu = copie.titlu;
		this->pret = copie.pret;
		this->gen = copie.gen;
		this->nrCapitole = copie.nrCapitole;

		if (this->paginiPerCapitol != nullptr) {
			delete[] this->paginiPerCapitol;
			this->paginiPerCapitol = nullptr;
		}

		if (copie.paginiPerCapitol != nullptr) {
			this->paginiPerCapitol = new float[copie.nrCapitole];
			for (int i = 0; i < copie.nrCapitole; i++) {
				this->paginiPerCapitol[i] = copie.paginiPerCapitol[i];
			}
		}
		else {
			this->paginiPerCapitol = nullptr;
		}
	}

	void afisareCarte() {
		cout << endl << this->id << ". Cartea " << this->titlu << " costa " << this->pret << " lei, este de genul ";
		if (this->gen == ROMAN) cout << "ROMAN";
		if (this->gen == SF) cout << "SF";
		if (this->gen == ISTORIE) cout << "ISTORIE";
		cout << " si are " << this->nrCapitole << " capitole: ";
		if (this->paginiPerCapitol != nullptr && this->nrCapitole > 0) {
			for (int i = 0; i < this->nrCapitole - 1; i++) {
				cout << this->paginiPerCapitol[i] << " pagini, ";
			}
			cout << this->paginiPerCapitol[this->nrCapitole - 1] << " pagini.";
		}
	}

	~Carte() {
		if (this->paginiPerCapitol != nullptr) {
			delete[] this->paginiPerCapitol;
		}
	}

	void operator+=(float valoareDeAdaugat) {
		this->pret += valoareDeAdaugat;
	}

	bool operator>(const Carte& c) {
		return this->pret > c.pret;
	}

	bool operator>=(int x) const {
		if (this->nrCapitole >= x)
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
		for (int i = 0; i < this->nrCapitole; i++)
			s += this->paginiPerCapitol[i];
		if (this->nrCapitole != 0)
			ma = s / this->nrCapitole;

		return ma;
	}

	float& operator[](int index) {
		if (index >= 0 && index < this->nrCapitole) {
			return this->paginiPerCapitol[index];
		}
		else
			throw exception();
	}

	friend void operator<<(ostream& out, Carte c) {
		out << endl << "Operator de afisare: ";
		out << endl << "Id: " << c.id;
		out << endl << "Titlu: " << c.titlu;
		out << endl << "Pret: " << c.pret;
		out << endl << "Gen: ";
		if (c.gen == ROMAN) out << "ROMAN";
		if (c.gen == SF) out << "SF";
		if (c.gen == ISTORIE) out << "ISTORIE";
		out << endl << "Nr capitole: " << c.nrCapitole;

		if (c.paginiPerCapitol != nullptr && c.nrCapitole > 0) {
			out << endl << "Pagini per capitol: ";
			for (int i = 0; i < c.nrCapitole - 1; i++) {
				out << c.paginiPerCapitol[i] << " pagini, ";
			}
			out << c.paginiPerCapitol[c.nrCapitole - 1] << " pagini.";
		}
	}

	friend void operator>>(istream& in, Carte& c) {
		cout << endl << "Pret: ";
		in >> c.pret;

		cout << endl << "Titlu: ";
		in >> c.titlu;

		cout << endl << "Gen (2-ISTORIE, 4-ROMAN, 8-SF): ";
		int genCitit;
		in >> genCitit;
		if (genCitit == 4) c.gen = ROMAN;
		if (genCitit == 8) c.gen = SF;
		if (genCitit == 2) c.gen = ISTORIE;

		cout << endl << "Nr capitole: ";
		in >> c.nrCapitole;

		cout << endl << "Pagini per capitol: ";
		if (c.paginiPerCapitol != nullptr) {
			delete[] c.paginiPerCapitol;
			c.paginiPerCapitol = nullptr;
		}

		c.paginiPerCapitol = new float[c.nrCapitole];
		for (int i = 0; i < c.nrCapitole; i++) {
			cout << endl << "Pagini[" << i << "]: ";
			in >> c.paginiPerCapitol[i];
		}
	}

	Carte operator++(int) {
		Carte copie = *this;
		this->pret++;

		return copie;
	}

	Carte operator++() {
		this->pret++;
		return *this;
	}

	explicit operator int() {
		return this->nrCapitole;
	}

	explicit operator string() {
		return this->titlu;
	}
};

int Carte::nrCarti = 0;

int main() {
	Carte roman;
	roman.afisareCarte();

	float* pagini = new float[3] { 25.0, 32.5, 40.0 };
	Carte* dune = new Carte("Dune", 65, 3, pagini, SF);
	dune->afisareCarte();

	if (!roman) {
		cout << endl << "Pretul este mai mare decat 0!";
	}
	else {
		cout << endl << "Pretul este mai mic sau egal cu 0!";
	}

	cout << endl << endl;
	if ((*dune) >= 3) {
		cout << "Cartea are minim 3 capitole";
	}
	else {
		cout << "Cartea are sub 3 capitole";
	}

	cout << endl << endl << "Media paginilor per capitol este de " << (*dune)(3);
	cout << endl << endl;

	if (roman <= 50) {
		cout << "Aceasta carte costa pana in 50 de lei";
	}
	else {
		cout << "Aceasta carte este mai scumpa de 50 de lei!";
	}

	for (int i = 0; i < 3; i++) {
		cout << endl << "Paginile dublate sunt: " << (*dune)[i] * 2 << " ";
	}

	Carte c1 = roman++;
	Carte c2 = ++roman;

	cout << c1;
	cout << c2;

	cout << endl << (int)c2;
	cout << endl << (int)(roman);
	cout << endl << endl << string(roman);

	delete dune;

	return 0;
}
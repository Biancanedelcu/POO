#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

// Enum 
enum Dificultate { USOR, MEDIU, DIFICIL };

class RetetaCulinara
{
private:
	const int id;
	float pretEstimativ;
	string denumire;
	int nrPasi;
	float* timpPasi; //vector dinamic echivalent cu cantitati
	Dificultate nivelDificultate;
	static int nrRetete;

public:
	// Constructor fara param
	RetetaCulinara() : id(++nrRetete)
	{
		this->denumire = "Reteta Necunoscuta";
		this->pretEstimativ = 0.0f;
		this->nrPasi = 0;
		this->timpPasi = nullptr;
		this->nivelDificultate = USOR;
	}

	// Constructor cu parametri
	RetetaCulinara(string denumire, float pretEstimativ, int nrPasi, const float* timpi, Dificultate nivelDificultate) : id(++nrRetete)
	{
		this->denumire = denumire;
		this->pretEstimativ = pretEstimativ;
		this->nrPasi = nrPasi;

		if (this->nrPasi > 0 && timpi != nullptr)
		{
			this->timpPasi = new float[this->nrPasi];
			for (int i = 0; i < this->nrPasi; i++)
			{
				this->timpPasi[i] = timpi[i];
			}
		}
		else
		{
			this->nrPasi = 0;
			this->timpPasi = nullptr;
		}

		this->nivelDificultate = nivelDificultate;
	}

	//Afisare reteta
	void afisareReteta() const
	{
		cout << "\n[ID " << this->id << "] Reteta: " << this->denumire
			<< " | Cost estimat: " << this->pretEstimativ << " RON | Dificultate: ";

		if (this->nivelDificultate == USOR) cout << "USOR";
		else if (this->nivelDificultate == MEDIU) cout << "MEDIU";
		else if (this->nivelDificultate == DIFICIL) cout << "DIFICIL";

		cout << " | Pasi de preparare (" << this->nrPasi << "): ";
		for (int i = 0; i < this->nrPasi; i++)
		{
			cout << this->timpPasi[i] << " min, ";
		}
		cout << endl;
	}

	//getteri
	string getDenumire() const
	{
		return this->denumire;
	}

	float getPretEstimativ() const
	{
		return this->pretEstimativ;
	}

	int getNrPasi() const
	{
		return this->nrPasi;
	}

	Dificultate getNivelDificultate() const
	{
		return this->nivelDificultate;
	}

	float* getTimpPasi() const
	{
		if (this->nrPasi == 0 || this->timpPasi == nullptr) return nullptr;

		float* copieTimpi = new float[this->nrPasi];
		for (int i = 0; i < this->nrPasi; i++)
		{
			copieTimpi[i] = this->timpPasi[i];
		}
		return copieTimpi;
	}

	//setteri
	void setDenumire(string denumireNoua)
	{
		this->denumire = denumireNoua;
	}

	void setPretEstimativ(float pretNou)
	{
		if (pretNou > 0)
			this->pretEstimativ = pretNou;
		else
			throw exception();
	}

	void setNrPasi(int nrPasiNou)
	{
		if (nrPasiNou > 0)
			this->nrPasi = nrPasiNou;
		else
			throw exception();
	}

	void setNivelDificultate(Dificultate dificultateNoua)
	{
		if (dificultateNoua == USOR || dificultateNoua == MEDIU || dificultateNoua == DIFICIL)
			this->nivelDificultate = dificultateNoua;
		else
			throw exception();
	}

	void setTimpPasi(const float* timpiNoi, int nrPasiNou)
	{
		setNrPasi(nrPasiNou);

		if (this->timpPasi != nullptr)
		{
			delete[] this->timpPasi;
		}

		this->timpPasi = new float[this->nrPasi];
		for (int i = 0; i < this->nrPasi; i++)
		{
			this->timpPasi[i] = timpiNoi[i];
		}
	}

	// Destructor
	~RetetaCulinara()
	{
		if (this->timpPasi != nullptr)
		{
			delete[] this->timpPasi;
		}
	}
};

int RetetaCulinara::nrRetete = 0;

int main()
{
	// Testare constructor fara param
	RetetaCulinara retetaImplicita;
	retetaImplicita.afisareReteta();

	// Testare constructor cu parametri
	float timpiInitiali[3] = { 10.5f, 15.0f, 5.0f };
	RetetaCulinara* carbonara = new RetetaCulinara("Paste Carbonara", 35.5f, 3, timpiInitiali, USOR);

	carbonara->afisareReteta();

	cout << "\nModificare date reteta cu setters" << endl;

	carbonara->setDenumire("Paste Bolognese");

	try {
		carbonara->setPretEstimativ(45.0f);
	}
	catch (...) {
		cout << "EROARE: Pretul estimat trebuie sa fie pozitiv!" << endl;
	}

	carbonara->setNivelDificultate(MEDIU);

	try {
		carbonara->setNrPasi(4);
	}
	catch (...) {
		cout << "err: Numarul de pasi trebuie sa fie mai mare decat 0!" << endl;
	}

	//Set noii timpi pentru pași
	float timpiNoi[4] = { 12.0f, 20.0f, 10.0f, 5.0f };
	carbonara->setTimpPasi(timpiNoi, 4);

	//Afisare prin getter
	cout << "\nReteta modificata se numeste: " << carbonara->getDenumire()
		<< "\nPret estimat: " << carbonara->getPretEstimativ() << " RON"
		<< "\nDificultate: ";

	if (carbonara->getNivelDificultate() == USOR) cout << "USOR";
	if (carbonara->getNivelDificultate() == MEDIU) cout << "MEDIU";
	if (carbonara->getNivelDificultate() == DIFICIL) cout << "DIFICIL";

	cout << "\nDurata pasi (" << carbonara->getNrPasi() << " pasi): ";

	float* timpiPreluati = carbonara->getTimpPasi();
	for (int i = 0; i < carbonara->getNrPasi(); i++)
	{
		cout << timpiPreluati[i] << " min, ";
	}
	cout << endl;

	// Eliberare memorie
	delete[] timpiPreluati;
	delete carbonara;

	return 0;
}
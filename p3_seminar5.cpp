#include <iostream>
using namespace std;
#pragma warning(4996)

enum tipLaptop { Gaming=1, Office=2 };
class Laptop
{
private:
	const int id;
	string marca;
	int nrComponente;
	float* preturiComponente;
	tipLaptop tip;

public:
	static int nrLaptopuri;

	//c fara param
	Laptop():id(++nrLaptopuri) //mai intai pui id 1 gen si dupa restaurantul se creeazi, intai id dupa nr restaurante
	{
		this->marca = "Anonim";
		this->nrComponente = 0;
		this->preturiComponente = nullptr;
		this->tip = Office;
		
	}

	//c cu param
	Laptop(int idDat, string marcaDat, int nrComponenteDat, float* preturiComponenteDat, tipLaptop tipDat) :id(idDat)
	{
		this->marca = marcaDat;
		this->nrComponente = nrComponenteDat;
		this->preturiComponente = new float[nrComponenteDat];
		for (int i = 0;i < nrComponenteDat;i++)
		{
			this->preturiComponente[i] = preturiComponenteDat[i];
		}

		this->tip = tipDat;

		nrLaptopuri++;
	}

	//metoda afisare
	void afisareLaptop()
	{
		cout << "Id: " << this->id << endl;
		cout << "Marca: " << this->marca << endl;
		cout << "Nr componente: " << this->nrComponente << endl;

		if (nrComponente >= 0 && preturiComponente != nullptr)
		{
			cout << "Preturi: ";
			for (int i = 0;i < nrComponente;i++)
			{
				cout << this->preturiComponente[i] << " ";
			}
			cout << endl;
		}
		else
		{
			"Nu are preturi";
		}

		cout << "Tip: ";
		if (this->tip ==Gaming )
		{
			cout << Gaming;
		}
		else
		{
			cout << Office;
		}
		cout << endl << endl;
	}

	//get pt nrComponente
	int getNrComponente()
	{
		return this->nrComponente;
	}

	//set pt nrComponente
	void setNrComponente(int nrComponenteNou)
	{
		if (nrComponenteNou >= 0)
		{
			this->nrComponente = nrComponenteNou;
		}
		else
		{
			throw "Val Negativa";
		}
	}

	//get pointer
	float* getPreturiComponente()
	{
		if (this->nrComponente >0 && preturiComponente != nullptr)
		{
			float* copiePreturi =new float [nrComponente]; //aici creezi
			for (int i = 0;i < nrComponente;i++)
			{
				copiePreturi[i] = this->preturiComponente[i];
			}
			return copiePreturi;
		}	
	}

	//set pointer
	void setPreturiComponente(float* preturiComponenteNoi, int nrComponenteNou)
	{
		if (preturiComponenteNoi != nullptr && nrComponenteNou >= 0)
		{
			setNrComponente(nrComponenteNou);

			if (this->preturiComponente != nullptr)
			{
				delete[] this->preturiComponente;
			}

			this->preturiComponente = new float[this->nrComponente]; //aloci spatiu de memorie
			for (int i = 0;i < this->nrComponente;i++)
			{
				this->preturiComponente[i] = preturiComponenteNoi[i];
			}
		}
		
	}
	

	//constr de copiere
	Laptop(const Laptop& c) :id(++nrLaptopuri)
	{
		
		{
			this->marca = c.marca;
			this->nrComponente = c.nrComponente;

			if (c.nrComponente > 0 && c.preturiComponente != nullptr)
			{
				this->preturiComponente = new float[c.nrComponente];
				for (int i = 0;i < c.nrComponente;i++)
				{
					this->preturiComponente[i] = c.preturiComponente[i];
				}
			}
			this->tip = c.tip;
		}
	}

	//op =
	Laptop& operator = (const Laptop & c)
	{
		if (this != &c)
		{
			if (preturiComponente != nullptr && nrComponente >= 0)
			{
				delete[] this->preturiComponente;

			}
			this->marca = c.marca;
			this->nrComponente = c.nrComponente;
			this->tip = c.tip;
			if (preturiComponente != nullptr && nrComponente >= 0)
			{
                this->preturiComponente = new float[c.nrComponente];
				for (int i = 0; i < c.nrComponente; i++)
				{
					this->preturiComponente[i] = c.preturiComponente[i];
				}
			}
			else
			{
				this->preturiComponente = nullptr;
			}
		}
		return*this;
	}
	
	//destructor
	~Laptop()
	{
		delete[] this->preturiComponente;
	}


 };
int Laptop::nrLaptopuri = 0;

int main()
{
	// fara param
	Laptop l;
	l.afisareLaptop();

	//cu param
	float preturi[]{ 100.0, 200.0, 300.0 };
	Laptop l1(2, "Lenovo", 3, preturi, Office);
	l1.afisareLaptop();

	//set pt nrComponente nou, afisat nr nou dupa cu get.
	try
	{
		l.setNrComponente(-2);
	}
	catch (...)
	{
		"Nr componente negativ";
	}
	cout << "Nr componente nou este: " << l.getNrComponente() << endl;

	//set pt pointer
	float preturiNoi[]{ 150.0, 120.0, 135.0 };
	l.setPreturiComponente(preturiNoi, 3);
	l.afisareLaptop();

	//comstr copiere
	Laptop l2 = l1;
	l2.afisareLaptop();

	// op egal
	l = l1;
	l.afisareLaptop();


	//afisare laptopuri creeate
	cout << "Total laptopuri creeate: " << Laptop::nrLaptopuri << endl;
}
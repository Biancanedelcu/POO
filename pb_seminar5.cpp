#include<iostream>
using namespace std;
#pragma warning(4996)

enum tipRestaurant { CLASIC=1, FASTFOOD=2}; //.
class Restaurant
{
private:
	const int id;
	string denumire;
	int nrMese;
	float* vectorPreturi;
	tipRestaurant tip; //.
public:
	static int nrRestaurante;

	//c fara param
	Restaurant() :id(++nrRestaurante)
	{
		this->denumire = "Anonim";
		this->nrMese = 0;
		this->vectorPreturi = nullptr;
		this->tip = FASTFOOD; //.
	}

	//c cu param
	Restaurant(int idDat, string denumireData, int nrMeseDat, float* vectorPreturiDat, tipRestaurant tipDat) :id(idDat)
	{
		this->denumire = denumireData;
		this->nrMese = nrMeseDat;
		this->vectorPreturi = new float[nrMeseDat];
		for (int i = 0;i < nrMeseDat;i++)
		{
			this->vectorPreturi[i] = vectorPreturiDat[i];
		}
		this->tip = tipDat; //.
		nrRestaurante++; //mai intai pui tu ce id vrei, dupa se mareste nr de restaurante creeate
	}

	//metoda afisare restaurant
	void afisarerestaurant()
	{
		cout << "id: " << this->id << endl;
		cout << "Denumire: " << this->denumire << endl;
		cout << "Nr mese: " << this->nrMese << endl;

		if (this->nrMese > 0 && this->vectorPreturi!= nullptr) //prima verificare
		{
			cout << "Preturi: " << endl;
				for (int i = 0;i < this->nrMese - 1;i++)
				{
					cout << this->vectorPreturi[i] << ", ";
				}
				cout << this->vectorPreturi[this->nrMese - 1] << "."; // Afișare ultimul element
		}

		cout <<endl<< "Tip Restaurant: ";
		if (this->tip == CLASIC)
		{
			cout << "CLASIC";

		}
		else
		{
			cout << "FASTFOOD";
		}

		cout << endl;
	}

	//get pt nrMese
	int getNrMese()
	{
		return this->nrMese;
	}

	//set pt nrMese
	void setNrMese(int nrMeseNou)
	{
		if (nrMeseNou >= 0)
		{
			this->nrMese = nrMeseNou;
		}
		else 
		{
			throw "Val Negativa!";
		}
	}

	//get pt pointer
	float* getVectorPreturi()
	{
		if (this->nrMese >= 0 && this->vectorPreturi != nullptr) //a doua verificare
		{
			float* copieVector = new float[this->nrMese];
			for (int i = 0;i < this->nrMese;i++)
			{
				copieVector[i] = this->vectorPreturi[i];
			}
			return copieVector;
		}
		else
		{
			return nullptr;
		}
	}

	//set pt pointer
	void setVectorPreturi(float* vector, int nrMeseNou)
	{
		setNrMese(nrMeseNou);
		if (this->nrMese >= 0 && vector != nullptr)
		{
			this->vectorPreturi = new float[this->nrMese];
				for (int i = 0;i < nrMese;i++)
				{
					this->vectorPreturi[i] = vector[i];
				}
		}
		else
		{
			this->nrMese = 0;
			this->vectorPreturi = nullptr;
		}
	}

	//CONSTR DE COPIERE
	Restaurant(const Restaurant& c) :id(++nrRestaurante)
	{
		this->denumire = c.denumire;
		this->nrMese = c.nrMese;

		if (c.nrMese > 0 && c.vectorPreturi != nullptr)
		{
			this->vectorPreturi = new float[c.nrMese];
			for (int i = 0;i < c.nrMese;i++)
			{
				this->vectorPreturi[i] = c.vectorPreturi[i];
			}
		}
		else
		{
			this->vectorPreturi = nullptr;
		}
		this->tip = c.tip;
	}

	Restaurant& operator=(const Restaurant& c)  //dif fata de cel de copiere e doar & operator= si nu incrementezi id nrrest
	{
		if (this != &c) // si asta //evitam autoatribuire adica r1=r1
		{
			if (this->vectorPreturi != nullptr)
			{
				delete[] this->vectorPreturi;
				this->vectorPreturi = nullptr;
			}
			this->denumire = c.denumire;
			
			if (c.nrMese > 0 && c.vectorPreturi != nullptr)
			{
				this->vectorPreturi = new float[c.nrMese];
				for (int i = 0;i < c.nrMese;i++)
				{
					this->vectorPreturi[i] = c.vectorPreturi[i];
				}
			}
			else
			{
				this->vectorPreturi = nullptr;
			}

			this->tip = c.tip;
		}
		return*this; //dif e asta 
	}

	//destructor
	~Restaurant()
	{
		delete[] vectorPreturi;
	}

};
int Restaurant::nrRestaurante = 0;

int main()
{
	//constr fara param
	Restaurant r;
	r.afisarerestaurant();

	//CU param
	float preturi[]{10.0,11.0,12.0 };
	Restaurant r1(2, "NUJ", 3, preturi, FASTFOOD);
	r1.afisarerestaurant();

	try
	{
		r.setNrMese(-2);
	}
	catch(...)
	{
		cout << endl << "Nr mese negativ!" << endl;;
	}
	cout << "Nr mese nou este: " << r.getNrMese() << endl;

	//set vector preturi nou
	float preturiNoi[]{ 20.0,21.0,22.0 };
	r1.setVectorPreturi(preturiNoi, 3);
	r1.afisarerestaurant();
	cout << "preturi noi: " << r1.getVectorPreturi() << endl;

	//c de copiere //creezi un ob nou prin copierea unuia existent
	Restaurant r2 = r1;
	r2.afisarerestaurant();

	//op =
	r1 = r2;

	//cate restaurante am creeat
	cout << "Total Restaurante: " << Restaurant::nrRestaurante << endl;
	return 0;
}
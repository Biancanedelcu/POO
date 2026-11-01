#include<iostream>
using namespace std;
#pragma warning(4996)

enum TipMagazin {Haine=1, Mancare=2};
class Magazin
{
private:
	const int id;
	string denumire;
	int nrProduse;
	float* preturi;
	TipMagazin tip;

public:
	static int nrMagazine;

	//c fara param
	Magazin():id(++nrMagazine)
	{
		this->denumire = "Necunoscut";
		this->nrProduse = 0;
		this->preturi = nullptr;
		this->tip = Haine;
	}

	//c cu parametrii
	Magazin(int idDat, string denumireData, int nrProduseDat, float* preturiDat, TipMagazin tipDat) :id(idDat)
	{
		this->denumire = denumireData;
		this->nrProduse = nrProduseDat;
		this->preturi = new float[nrProduseDat];
		for (int i = 0;i < nrProduseDat;i++)
		{
			this->preturi[i] = preturiDat[i];
		}
		this->tip = tipDat;
		nrMagazine++;
	}

	//c de copiere
	Magazin(const Magazin& c):id(++nrMagazine)
	{
		this->denumire = c.denumire;
		this->nrProduse = c.nrProduse;

		if (c.preturi != nullptr && c.nrProduse >= 0)
		{
			this->preturi = new float[c.nrProduse];
			for (int i = 0;i < c.nrProduse;i++)
			{
				this->preturi[i] = c.preturi[i];
			}
		}
		this->tip = c.tip;
	}

	//op =
	Magazin& operator =(const Magazin& c)
	{
		if (this != &c)
		{
			this->denumire = c.denumire;
			this->nrProduse = c.nrProduse;

			if (c.preturi != nullptr && c.nrProduse >= 0)
			{
				delete[] this->preturi;

				this->preturi = new float[c.nrProduse];
				for (int i = 0;i < c.nrProduse;i++)
				{
					this->preturi[i] = c.preturi[i];
				}
			}
			else
			{
				this->preturi = nullptr;
			}
			this->tip = c.tip;
		}
		return *this;
	}

	//get pt nrprod
	int getNrProd()
	{
		return this->nrProduse;
	}

	//set nr prod
	void setNrProd(int nrProduseNou)
	{
		if (nrProduseNou >= 0)
		{
			this->nrProduse = nrProduseNou;
		}
		else
		{
			throw"val negativa";
		}
	}

	void afisare()
	{
		cout << "Id: " << this->id << endl;
		cout << "Denumire:" << this->denumire << endl;
		cout << "Nr prod: " << this->nrProduse << endl;

		if (preturi != nullptr && nrProduse >= 0)
		{
			cout << "Pret: ";

			for (int i = 0;i < nrProduse;i++)
			{
				cout << this->preturi[i] << " ";
			}
		}


		cout << endl << "Tip: ";
		if (this->tip == Haine)
		{
			cout << Haine;
		}
		else
		{
			cout << Mancare;
		}
		cout << endl << endl;


	}

	//get pt pointer
	float* getPreturi()
	{
		if (preturi != nullptr && nrProduse >= 0)
		{
			float* copiePreturi = new float[this->nrProduse];
			for (int i = 0;i < this->nrProduse;i++)
			{
				copiePreturi[i] = this->preturi[i];
			}
			return copiePreturi;
		}
	}

	//set pt pointer
	void setPreturi(float* preturiNoi, int nrProduseNou)
	{
		if (preturiNoi != nullptr && nrProduseNou >= 0)
		{
			setNrProd(nrProduseNou);

			if (this->preturi != nullptr)
			{

				delete[] this->preturi;
			}

			this->preturi = new float[this->nrProduse];
			for (int i = 0;i < this->nrProduse;i++)
			{
				this->preturi[i] = preturiNoi[i];
			}
		}
	}

	//destructor
	~Magazin()
	{
		delete[] this->preturi;
	}





};
int Magazin::nrMagazine = 0;

int main()
{
	// c fara param
	Magazin c1;
	c1.afisare();

	//cu param
	float valori[]{ 10.0, 20.0, 30.0 };
	Magazin c2(2, "Profi", 3, valori, Mancare);
	c2.afisare();

	//c copiere
	Magazin c3 = c2;
	c3.afisare();

	//op egal
	c2 = c1;
	c2.afisare();

	//set si o sa arati ce ai nou cu get
	try
	{
		c1.setNrProd(-2);
	}
	catch (...)
	{
		"Val negativa";
	}
	cout << "Nr produse noi: " << c1.getNrProd() << endl;

	//set
	c1.setNrProd(2);
	cout << "Nr produse noi: " << c1.getNrProd() << endl;

	//set pointer
	float valoriNoi[]{ 50.0, 40.0, 10.0 };
	c1.setPreturi(valoriNoi, 3);
	c1.afisare();

	//cate magazine am creeat
	cout << "Total Magazine Creeate: " << Magazin::nrMagazine << endl;

}
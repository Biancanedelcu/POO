#include<iostream>
using namespace std;
#include<string>
#pragma warning(disable:4996)

class SenzorPoluare
{
private:
	string adresa;
	long timpDeFunctionare;
	int nrInregistrari;
	int* valori;
	const int idSenzor;
	static string producator;

public:
	//constr fara param
	SenzorPoluare() :idSenzor(0)
	{
		this->adresa = "N/A";
		this->timpDeFunctionare = 0;
		this->nrInregistrari = 0;
		this->valori = NULL;
		

	}

	//comstr cu 3 param
	SenzorPoluare(int idSenzorDat, int nrInregistrariDate, int* valoriDate) :idSenzor(idSenzorDat)
	{
		this->nrInregistrari = nrInregistrariDate;
		this->valori=new int[nrInregistrariDate];
		for (int i = 0;i < nrInregistrariDate;i++)
		{
			this->valori[i] = valoriDate[i];
		}
		this->adresa = "N/A";
		this->timpDeFunctionare = 0;

	}

	//constr de copiere
	SenzorPoluare(const SenzorPoluare& sursa):idSenzor(sursa.idSenzor)
	{
		this->adresa = sursa.adresa;
		this->timpDeFunctionare = sursa.timpDeFunctionare;
		this->nrInregistrari = sursa.nrInregistrari;
		this->valori = new int[sursa.nrInregistrari];
		for (int i = 0;i < sursa.nrInregistrari;i++)
		{
			this->valori[i] = sursa.valori[i];
		}
	}

	

	//destructor
	~SenzorPoluare()
	{
		delete[] this->valori;
	}

	//get
	int getNrInregistrari() const
	{
		return this->nrInregistrari;
	}

	int* getValori() const
	{
		int* copieValori = new int[this->nrInregistrari];
		for (int i = 0;i < this->nrInregistrari;i++)
		{
			copieValori[i]=this->valori[i] ;
		}
		return copieValori;
	}
	

	//set
	void setValori(int* valoriNoi, int nrInregistrariNoi)
	{
		if (valoriNoi != NULL && nrInregistrariNoi > 0)
		{
			delete[] this->valori;
			this->nrInregistrari = nrInregistrariNoi;
			this->valori = new int[this->nrInregistrari];
			for (int i = 0;i < this->nrInregistrari;i++)
			{


				if (valoriNoi[i] >= 1 && valoriNoi[i] <= 100)
				{
					this->valori[i] = valoriNoi[i];
				}
				else
				{
					this->valori[i] = 0;
				}

			}
	    }
	}



};
string SenzorPoluare::producator = "airly";

int main()
{
	SenzorPoluare c;

	int valori[] = { 1,2,3 };
	SenzorPoluare c1(1, 3, valori);

	SenzorPoluare c2(c1);

	c1.getNrInregistrari();
	c1.setValori(valori, 3);
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class Produs
{
private:
	float pret;
	string denumire;

public:
	Produs()
	{
		this->pret = 0;
		this->denumire = "Necunoscut";
	}

	Produs(float pret, string denumire)
	{
		this->pret = pret;
		this->denumire = denumire;
	}

	float getPret()
	{
		return this->pret;
	}

	string getDenumire()
	{
		return this->denumire;
	}

	~Produs()
	{
	}
};

class CosCumparaturi
{
private:
	Produs* produse;
	string numeClient;
	int puncteFidelitate;
	int nrProduse;

public:
	CosCumparaturi()
	{
		this->numeClient = "Anonim";
		this->puncteFidelitate = 0;
		this->nrProduse = 0;
		this->produse = nullptr;
	}

	CosCumparaturi(string numeClient, int puncteFidelitate, int nrProduse, float* preturi, string* denumiri)
	{
		this->numeClient = numeClient;
		this->puncteFidelitate = puncteFidelitate;
		this->nrProduse = nrProduse;
		if (nrProduse > 0 && preturi != nullptr && denumiri != nullptr)
		{
			this->produse = new Produs[nrProduse];
			for (int i = 0; i < nrProduse; i++)
			{
				this->produse[i] = Produs(preturi[i], denumiri[i]);
			}
		}
		else
		{
			this->produse = nullptr;
		}
	}

	CosCumparaturi(const CosCumparaturi& c)
	{
		this->numeClient = c.numeClient;
		this->puncteFidelitate = c.puncteFidelitate;
		this->nrProduse = c.nrProduse;
		if (c.produse != nullptr && c.nrProduse > 0)
		{
			this->produse = new Produs[c.nrProduse];
			for (int i = 0; i < c.nrProduse; i++)
			{
				this->produse[i] = c.produse[i];
			}
		}
		else
		{
			this->produse = nullptr;
		}
	}

	CosCumparaturi& operator=(const CosCumparaturi& c)
	{
		if (this != &c)
		{
			if (this->produse != nullptr)
			{
				delete[] this->produse;
				this->produse = nullptr;
			}
			this->numeClient = c.numeClient;
			this->puncteFidelitate = c.puncteFidelitate;
			this->nrProduse = c.nrProduse;
			if (c.produse != nullptr && c.nrProduse > 0)
			{
				this->produse = new Produs[c.nrProduse];
				for (int i = 0; i < c.nrProduse; i++)
				{
					this->produse[i] = c.produse[i];
				}
			}
		}
		return *this;
	}

	~CosCumparaturi()
	{
		if (this->produse != nullptr)
		{
			delete[] this->produse;
			this->produse = nullptr;
		}
	}

	bool operator>=(int pragPuncte)
	{
		return this->puncteFidelitate >= pragPuncte;
	}

	bool operator!()
	{
		return this->nrProduse == 0;
	}

	CosCumparaturi& operator+=(int puncteBonus)
	{
		this->puncteFidelitate += puncteBonus;
		return *this;
	}

	float operator()(int nrElemente)
	{
		float total = 0;
		if (this->produse != nullptr)
		{
			int limita = (nrElemente < this->nrProduse) ? nrElemente : this->nrProduse;
			for (int i = 0; i < limita; i++)
			{
				total += this->produse[i].getPret();
			}
		}
		return total;
	}

	CosCumparaturi& operator--()
	{
		if (this->nrProduse > 0)
		{
			this->nrProduse--;
		}
		return *this;
	}

	CosCumparaturi operator--(int)
	{
		CosCumparaturi copie = *this;
		if (this->nrProduse > 0)
		{
			this->nrProduse--;
		}
		return copie;
	}

	friend ostream& operator<<(ostream& out, const CosCumparaturi& c);
};

ostream& operator<<(ostream& out, const CosCumparaturi& c)
{
	out << c.numeClient << " are " << c.puncteFidelitate << " puncte de fidelitate si " << c.nrProduse << " produse in cos:";
	if (c.produse != nullptr)
	{
		for (int i = 0; i < c.nrProduse; i++)
		{
			out << endl << "Produs " << i + 1 << ":";
			out << endl << "    ->Denumire: " << c.produse[i].getDenumire();
			out << endl << "    ->Pret: " << c.produse[i].getPret() << " lei.";
		}
	}
	return out;
}

int main()
{
	float* preturi1 = new float[3] { 349.99f, 129.50f, 45.00f };
	string* denumiri1 = new string[3] { "Casti Wireless", "Tastatura Mecanica", "Mousepad Gaming" };

	CosCumparaturi c1("Dumitrescu Elena", 420, 3, preturi1, denumiri1);
	cout << c1;

	cout << endl << endl;
	float* preturi2 = new float[2] { 4299.00f, 89.90f };
	string* denumiri2 = new string[2] { "Laptop Ultrabook", "Husa Protectie" };

	CosCumparaturi c2("Marin Vlad", 1150, 2, preturi2, denumiri2);
	cout << c2;

	cout << endl << endl;
	if (c2 >= 1000)
	{
		cout << "Clientul are statut VIP (reducere 15%).";
	}
	else
	{
		cout << "Clientul are statut Standard.";
	}

	cout << endl << endl;
	if (!c1)
	{
		cout << "Cosul de cumparaturi este gol.";
	}
	else
	{
		cout << "Cosul de cumparaturi contine produse.";
	}

	cout << endl << endl;
	c1 += 250;
	cout << "Dupa bonusul de campanie: " << c1;

	cout << endl << endl;
	cout << "Valoarea totala a produselor din cosul c1 este " << c1(3) << " lei.";

	cout << endl << endl;
	--c1;
	cout << "Dupa eliminarea ultimului produs: " << c1;

	delete[] preturi1;
	delete[] denumiri1;
	delete[] preturi2;
	delete[] denumiri2;

	return 0;
}
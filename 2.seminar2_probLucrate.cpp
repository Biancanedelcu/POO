#include <iostream>

using namespace std;

//Functie care numara cate elemente pare exista in vctor
int numaraElementePare(const int* v, int n)
{
    int contor = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i] % 2 == 0)
        {
            contor++;
        }
    }
    return contor;
}

// Ins valoarea 'val'imediat dupa fiecare numar par
void insereazaDupaPare(int*& v, int& n, int val)
{
    int pare = numaraElementePare(v, n);
    if (pare == 0) return; // Daca nu avem numere pare, vectorul ramane neschimbat

    int dimNoua = n + pare;
    int* vNou = new int[dimNoua];

    int j = 0; //Indice pentru noul vector
    for (int i = 0; i < n; i++)
    {
        vNou[j++] = v[i]; //Copiem elementul curent

        //Daca elementul curent este par, adaugam si valoarea noua
        if (v[i] % 2 == 0)
        {
            vNou[j++] = val;
        }
    }

    delete[] v;
    v = vNou;
    n = dimNoua;
}

void afiseaza(const int* v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "v[" << i << "] = " << v[i] << "\n";
    }
}

int main()
{
    int n;
    cout << "Dimensiune vector: ";
    cin >> n;

    int* v = new int[n];
    cout << "Introduceti elementele:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "v[" << i << "] = ";
        cin >> v[i];
    }

    int valoareGrefata;
    cout << "\nCe valoare adaugi dupa numerele pare? ";
    cin >> valoareGrefata;

    insereazaDupaPare(v, n, valoareGrefata);

    cout << "\nVectorul modificat:\n";
    afiseaza(v, n);

    delete[] v;
    return 0;
}
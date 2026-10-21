#include <iostream>

using namespace std;

//Functie care elimina elementul de pe pozitia 'pos' prin deplasare la stanga
void eliminaElement(int* v, int& n, int pos)
{
    // Mutam toate elementele de dupa 'pos' cu o pozitie la stanga
    for (int i = pos; i < n - 1; i++)
    {
        v[i] = v[i + 1];
    }

    // Scad dimensiunea logica a vectorului
    n--;
}

void afiseazaVector(const int* v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "v[" << i << "] = " << v[i] << "\n";
    }
}

int main()
{
    int n = 6;
    int* v = new int[n];

    cout << "Introduceti elementele vectorului:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "v[" << i << "] = ";
        cin >> v[i];
    }

    cout << "\nVectorul initial:\n";
    afiseazaVector(v, n);

    int pozitie;
    cout << "\nIntroduceti pozitia de sters (0 - " << n - 1 << "): ";
    cin >> pozitie;

    if (pozitie < 0 || pozitie >= n)
    {
        cout << "Pozitie invalida!\n";
    }
    else
    {
        eliminaElement(v, n, pozitie);
        cout << "\nVectorul dupa stergere:\n";
        afiseazaVector(v, n);
    }

    // Eliberam memoria alocata la inceput
    delete[] v;

    return 0;
}

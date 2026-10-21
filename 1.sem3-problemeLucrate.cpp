#include <iostream>
#include <string>

using namespace std;

class Film
{
private:
    const int idFilm;
    string titlu;
    int durataMinute;
    double notaIMDB;

    static int totalFilmeInregistrate;

public:
    // constructor fara parametri
    Film() : idFilm(++totalFilmeInregistrate)
    {
        titlu = "Fara titlu";
        durataMinute = 0;
        notaIMDB = 0.0;
    }

    // Constructor cu parametri
    Film(string titlu, int durataMinute, double notaIMDB) : idFilm(++totalFilmeInregistrate)
    {
        this->titlu = titlu;
        this->durataMinute = durataMinute;
        this->notaIMDB = notaIMDB;
    }

    // Getteri pentru acces la atribute
    string getTitlu() const
    {
        return titlu;
    }

    int getDurata() const
    {
        return durataMinute;
    }

    double getNota() const
    {
        return notaIMDB;
    }

    // Metoda de verificare (filme de lung metraj, de ex>= 120 minute)
    bool esteLungMetraj() const
    {
        return durataMinute >= 120;
    }
};

// Initializare membru static
int Film::totalFilmeInregistrate = 0;

int main()
{
    int nrFilme = 5;

    // Alocam un tablou dinamic de pointeri la obiecte de tip Film
    Film** colectie = new Film * [nrFilme];

    colectie[0] = new Film("Inception", 148, 8.8);
    colectie[1] = new Film("Whiplash", 106, 8.5);
    colectie[2] = new Film("Interstellar", 169, 8.7);
    colectie[3] = new Film("The Lion King", 88, 8.5);
    colectie[4] = new Film("The Dark Knight", 152, 9.0);

    cout << "Filmele cu o durata de cel putin 120 de minute sunt:\n";
    for (int i = 0; i < nrFilme; i++)
    {
        if (colectie[i]->esteLungMetraj())
        {
            cout << "- " << colectie[i]->getTitlu()
                << " (" << colectie[i]->getDurata() << " min)\n";
        }
    }

    // Curatarea memoriei alocate
    for (int i = 0; i < nrFilme; i++)
    {
        delete colectie[i];
    }
    delete[] colectie;

    return 0;
}
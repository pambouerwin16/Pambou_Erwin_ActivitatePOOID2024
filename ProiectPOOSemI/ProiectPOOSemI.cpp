#include <iostream>
#include <string>

using namespace std;

// Cele 3 clase initiale for fi Proprietate, Apartament, Parcare deoarece contin initialele mele P (Pambou) si respectiv E (Erwin-Emmanuel)

//Prima clasa, contie P si E (ProPriEtatE)
class Proprietate
{
private:
    const int ID; //atribut constant
    static int nrProprietati; //atribut static
    float pret;
    string locatie;
    int nrFacilitati;
    string* facilitati; //atribut pointer cu memorie pe HEAP
    //Declaram atributele clasei in zona publica conform cerintei

public:
    #pragma region Constructor/Destructori
    //Constructor1 - Default - fara parametrii
    Proprietate(): ID(++nrProprietati)
    {
        pret = 0.0f;
        locatie = "Necunoscut";
        nrFacilitati = 0;
        facilitati = nullptr;
    }

    //Constructor2 - cu un parametru
    Proprietate(string locatieprop): ID(++nrProprietati)
    {
        pret = 0.0f;
        locatie = locatieprop;
        nrFacilitati = 0;
        facilitati = nullptr;
    }

    //Constructor3 - cu 4 parametrii
    Proprietate(float pretprop, string locatieprop, int nrfacprop, string* facilitatiprop): ID(++nrProprietati)
    {
        pret = pretprop;
        locatie = locatieprop;
        nrFacilitati = nrfacprop;
        facilitati = new string[nrFacilitati];
        for (int i = 0; i < nrFacilitati; i++)
        {
            facilitati[i] = facilitatiprop[i];
        }
        delete[] facilitatiprop; //Eliberam memoria alocata pentru vectorul de facilitati primit ca parametru;
    }
    //Destructor
    ~Proprietate()
    {
        if(facilitati != nullptr)
        {
            delete[] facilitati;
        }
    }
    #pragma endregion
    #pragma region Metode/Functii
    //Metoda pentru afisare a obiectului optionala - pentru a ajuta demonstrarea functionarii constructorilor in main
    void Afisare()
    {
        cout << "Proprietate nr " << ID << ":" << endl;
        cout << "Pret: " << pret << endl;
        cout << "Locatie: " << locatie << endl;
        if (nrFacilitati <= 0 || facilitati == nullptr) //Nu incercam sa afisam facilitatile daca proprietatea nu detine
        {
            cout << "Nicio facilitate disponibila" << endl;
        }
        else
        {
            cout << "Facilitati:" << endl << "{" << endl;
            for (int i = 0; i < nrFacilitati; i++)
            {
                cout << facilitati[i] << endl;
            }
            cout << "}" << endl;
        }
        cout << endl;
    }

    //Functie statica pentru procesare -> Aplicare discount pe pretul proprietatii
    static void AplicareDiscount(float disc, Proprietate& p)
    {
        if (disc > 0)
        {
            p.pret = p.pret * ((100 - disc) / 100);
        }
    }
    #pragma endregion
    #pragma region Getteri/Setteri
    //Setter pentru pret
    void SetPret(float p)
    {
        pret = p;
    }
    //Setter pentru locatie
    void SetLocatie(string loc)
    {
        locatie = loc;
    }
    //Setter pentru numarul facilitatilor
    void SetNrFacilitati(int nrfac)
    {
        nrFacilitati = nrfac;
    }
    //Setter pentru facilitati (modifica si numarul facilitatilor)
    void SetFacilitati(string* fc, int nrfc)
    {
        if(facilitati!= nullptr)
        {
            delete[] facilitati;
        }
        
        facilitati = new string[nrfc];

        for(int i = 0; i < nrfc; i++)
        {
            facilitati[i]=fc[i];
        }
        nrFacilitati = nrfc;
        delete[] fc;
    }
    //Getter pentru pret
    float GetPret()
    {
        return pret;
    }
    //Getter pentru locatie
    string GetLocatie()
    {
        return locatie;
    }
    //Getter pentru numarul facilitatilor
    int GetNrFacilitati()
    {
        return nrFacilitati;
    }
    //Getter pentru facilitati
    string* GetFacilitati() const
    {
        return facilitati;//Am ales sa returnez un pointer constant la array-ul facilitatilor pentru cateva motive: 1. sa nu fie nevoie de procesare in plus pentru a crea o copie pe care sa o returnez, 2. pentru ca dezalocarea sa revina destructorului clasei si nu la alegerea apelatorului
    }
    #pragma endregion
};

//Initializare atribut static
int Proprietate::nrProprietati = 0;

//Clasa a doua, contine P si E (aPartamEnt)
class Apartament
{
    //Decalram atributele in zona publica
public:
    const int ID;
    static int nrApartamente;
    int nrCamere;
    float intretinere;
    int nrLocuitori;
    string* locuitori;

    #pragma region Constructori/Destructori
    //Constructor1 - Default - fara parametrii
    Apartament(): ID(++nrApartamente)
    {
        nrCamere = 0;
        intretinere = 0.0f;
        nrLocuitori = 0;
        locuitori = nullptr;
    }

    //Constructor2 - cu un parametru
    Apartament(int nrcam): ID(++nrApartamente)
    {
        nrCamere = nrcam;
        intretinere = 0.0f;
        nrLocuitori = 0;
        locuitori = nullptr;
    }

    //Constructor3 - cu 4 parametrii
    Apartament(int nrcam, float intr, int nrloc, string* loc): ID(++nrApartamente)
    {
        nrCamere = nrcam;
        intretinere = intr;
        nrLocuitori = nrloc;
        locuitori = new string[nrLocuitori];

        for (int i = 0; i < nrLocuitori; i++)
        {
            locuitori[i] = loc[i];
        }
        delete[] loc; //Eliberm memoria vectorului primit ca parametru alocat in main
    }
    #pragma endregion
    #pragma region Metode/Functii
    //Functie statica pentru afisare, primeste ca parametru obiectul care vrem sa fie afisat
    static void Afisare(Apartament& a)
    {
        cout << "Apartament nr " << a.ID << ":" << endl;
        cout << "Numar camere: " << a.nrCamere << endl;
        cout << "Intretinere: " << a.intretinere << endl;
        cout << "Locuitori:" << endl;
        if (a.nrLocuitori <= 0 || a.locuitori == nullptr) //Daca nu avem locuitori nu incercam sa-i afisam
        {
            cout << "Apartamentul nu este locuit" << endl;
        }
        else
        {
            cout << "{" << endl;
            for (int i = 0; i < a.nrLocuitori; i++)
            {
                cout << a.locuitori[i] << endl;
            }
            cout << "}" << endl;
        }
        cout << endl;
    }
    #pragma endregion
    #pragma region Getteri/Setteri
    //Setter pentru numarul camerelor
    void SetNrCamere(int nr)
    {
        nrCamere = nr;
    }
    //Setter pentru intretinere
    void SetIntretinere(float suma)
    {
        intretinere = suma;
    }
    //Setter pentru numarul locuitorilor
    void SetNrLocuitori(int nr)
    {
        nrLocuitori = nr;
    }
    //Setter pentru locuitori (modifica si numarul locuitorilor)
    void SetLocuitori(string* loc, int nrlc)
    {
        if(locuitori != nullptr)
        {
            delete[] locuitori;
        }

        locuitori = new string[nrlc];

        for(int i = 0; i < nrlc; i++)
        {
            locuitori[i] = loc[i];
        }
        nrLocuitori = nrlc;

        delete[] loc;
    }
    //Getter pentru numarul camerelor
    int GetNrCamere()
    {
        return nrCamere;
    }
    //Getter pentru suma intretinere
    float GetIntretinere()
    {
        return intretinere;
    }
    //Getter pentru numarul locuitorilor
    int NrLocuitori()
    {
        return nrLocuitori;
    }
    //Getter pentru locuitori
    string* GetLocuitori() const
    {
        return locuitori;
    }
    #pragma endregion
};

// Initializare atribut static
int Apartament::nrApartamente = 0;

//Clasa 3 - contine P si E (ParcarE)
class Parcare
{
    //Declaram atributele in zona publica conform cerintei
public:
    const int ID; //atribut constant
    static int nrParcari; //atribut static
    unsigned int capacitateLocuri;
    unsigned int locuriOcupate;
    unsigned int* idMasini;
    //Atribut pointer ce va aloca spatiu un HEAP - id-ul propriul fiecarei masini, nu id pentru evidenta

    //Constructor1 - Default - fara parametrii
    Parcare(): ID(++nrParcari)
    {
        capacitateLocuri = 0;
        locuriOcupate = 0;
        idMasini = nullptr;
    }

    //Constructor2 - cu un parametru
    Parcare(unsigned int cap): ID(++nrParcari)
    {
        capacitateLocuri = cap;
        locuriOcupate = 0;
        idMasini = nullptr;
    }

    //Constructor3 - cu 3 parametrii
    Parcare(unsigned int cap, unsigned int ocup, unsigned int* mas): ID(++nrParcari)
    {
        capacitateLocuri = cap;
        locuriOcupate = ocup;
        idMasini = new unsigned int[ocup];

        for (int i = 0; i < ocup; i++)
        {
            idMasini[i] = mas[i];
        }
    }

    //Functie statica pentru procesare - pentru evacuare masina specifica din parcare
    static void EvacuareMasina(unsigned int idMas, Parcare& p)
    {
        cout << "Incercam evacuarea masinii cu ID " << idMas << " din parcare..." << endl;
        int valid = 0;
        //Initializam numerul datilor in care se regaseste id-ul masini cerute in parcare - ex: un sofer plateste mai multe locuri de parcare
        if (p.locuriOcupate <= 0 || p.idMasini != nullptr) //Intai verificam daca parcarea este goala
        {
            //Vrem sa aflam daca masina respectiva se afla in parcare
            for (int i = 0; i < p.locuriOcupate; i++)
            {
                if (idMas == p.idMasini[i])
                {
                    valid++;
                }
            }
            unsigned int* listaMasNoua = new unsigned int[p.locuriOcupate - valid];
            //Alocam un vector auxiliar pentru a stoca elementele pe care le dorim din vectorul id-urilor masinilor
            if (valid > 0) //Daca masina exista inregistrata macar o data (poate un sofer plateste 2 locuri de parcare)
            {
                int pas = 0;
                for (int i = 0; i < p.locuriOcupate; i++)
                {
                    if (idMas != p.idMasini[i])
                    {
                        listaMasNoua[i - pas] = p.idMasini[i];
                        //Ne asiguram ca nu sarim peste vreun element al vectorului auxiliar de id-uri  in cazul in care a fost sarita masina evacuata
                    }
                    else
                    {
                        pas++;
                    }
                }
                delete[] p.idMasini; //Eliberam memoria ce contine vectorul vechi
                p.idMasini = listaMasNoua;
                //Asignam vectorul nou ca noul vector al obiectului - nu eliberam aceasta memorie deoarece este folosita de obiect acum
                p.locuriOcupate = p.locuriOcupate - valid; //Actualizam numarul total de locuri ocupate din parcare
                cout << "Am reusit evacuarea masinii " << idMas << " din parcare." << endl;
            }
            else
            {
                cout << "Masina cu ID " << idMas << " nu a fost gasita in parcare." << endl;
            }
        }
        else
        {
            cout << "Parcarea este goala, nu putem evacua masina." << endl;
        }
        cout << endl;
    }

    void Afisare()
    {
        cout << "Parcare ID " << ID << endl;
        cout << "Capacitate parcare (locuri): " << capacitateLocuri << endl;
        cout << "Locuri ocupate: " << locuriOcupate << endl;
        cout << "Lista masini in parcare(IDs): " << endl;
        if (locuriOcupate <= 0 || idMasini == nullptr)
        {
            cout << "Parcarea este goala." << endl;
        }
        else
        {
            cout << "{" << endl;
            for (int i = 0; i < locuriOcupate; i++)
            {
                cout << idMasini[i] << endl;
            }
            cout << "}" << endl;
        }
        cout << endl;
    }
};

//Initializam atributul static
int Parcare::nrParcari = 0;

void main()
{
    Proprietate prop1(1200.0f, "Bd. Nicolae Balcescu 23a, Bl. Bla, Ap. Bla", 3,
                      new string[3]{"Termoficare", "Canalizare", "Izolare"});
    Proprietate prop2("Str. Panselelor nr. 12, Bl. Bla, Ap. Bla");
    Proprietate prop3;

    Proprietate::AplicareDiscount(20, prop1);

    prop1.Afisare();
    prop2.Afisare();
    prop3.Afisare();

    Apartament ap1(3, 443.27f, 3, new string[3]{"Popescu Mariana", "Popescu Beniamin", "Popescu Popescu"});
    Apartament ap2(3);
    Apartament ap3;

    Apartament::Afisare(ap1);
    Apartament::Afisare(ap2);
    Apartament::Afisare(ap3);

    Parcare parcare1(10, 4, new unsigned int[4]{1234, 435, 562, 435});
    Parcare parcare2(12);
    Parcare parcare3;

    Parcare::EvacuareMasina(435, parcare1);

    parcare1.Afisare();
    parcare2.Afisare();
    parcare3.Afisare();
}

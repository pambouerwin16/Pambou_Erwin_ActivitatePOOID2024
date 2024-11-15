#include <iostream>
#include <pplwin.h>
#include <string>

//Declaram inainte clasele si functia prietena pentru a anunta compilatorul ca acestea exista
class Proprietate;
class Parcare;
class Apartament;
void AfisareComplex(const Proprietate& p, const Apartament& a, const Parcare& parc);

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

public:
    friend void AfisareProprietate(const Proprietate& p);
    friend void AfisareComplex(const Proprietate& p, const Apartament& a, const Parcare& parc);
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

    //Copy Constructor
    Proprietate(const Proprietate& prop): ID(++nrProprietati), pret(prop.pret), locatie(prop.locatie),
                                          nrFacilitati(prop.nrFacilitati)
    {
        facilitati = new string[nrFacilitati];
        for (int i = 0; i < nrFacilitati; i++)
        {
            facilitati[i] = prop.facilitati[i];
        }
    }

    //Destructor
    ~Proprietate()
    {
        if (facilitati != nullptr)
        {
            delete[] facilitati;
        }
        nrProprietati--;
    }
    #pragma endregion
    #pragma region Metode/Functii
    //Metoda pentru afisare a obiectului optionala - pentru a ajuta demonstrarea functionarii constructorilor in main

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
        if (facilitati != nullptr)
        {
            delete[] facilitati;
        }

        facilitati = new string[nrfc];

        for (int i = 0; i < nrfc; i++)
        {
            facilitati[i] = fc[i];
        }
        nrFacilitati = nrfc;
        delete[] fc;
    }

    int GetID() const
    {
        return ID;
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
        return facilitati;
        //Am ales sa returnez un pointer constant la array-ul facilitatilor pentru cateva motive: 1. sa nu fie nevoie de procesare in plus pentru a crea o copie pe care sa o returnez, 2. pentru ca dezalocarea sa revina destructorului clasei si nu la alegerea apelatorului
    }

    //Setter static pentru numarul proprietatilor(atentie cum e folosit, este public deoarece cerinta vrea sa dea acces la acel atribut privat static)
    static void SetNrProp(const int nrp)
    {
        nrProprietati = nrp;
    }

    //Getter static pentru numarul proprietatilor
    static int GetNrProp()
    {
        return nrProprietati;
    }
    #pragma endregion
	#pragma region Overloads
    //Supraincarcare operator de atribuire
    Proprietate& operator=(const Proprietate& p)
    {
        if(this != &p)
        {
            pret = p.pret;
            locatie = p.locatie;
            nrFacilitati = p.nrFacilitati;
            if(facilitati != nullptr)
            {
                delete[] facilitati;
            }

            facilitati = new string[nrFacilitati];
            
            for(int i = 0; i < nrFacilitati; i++)
            {
                facilitati[i] = p.facilitati[i];
            }
        }
        return *this;
    }
    //Supraincarcare operator index
    string& operator[](int index)
    {
        if(index >= 0 && index < nrFacilitati)
        {
            return facilitati[index];
        }
        throw "Index out of range";
    }
    //Supraincarcare operator compariate (mai mic)
    bool operator<(const Proprietate& p)const
    {
        return pret < p.pret;
    }
    //Supraincarcare operator egalitate
    bool operator==(const Proprietate& p)const
    {
        return pret == p.pret;
    }
	#pragma endregion
};

//Initializare atribut static
int Proprietate::nrProprietati = 0;

//Clasa a doua, contine P si E (aPartamEnt)
class Apartament
{
private:
    const int ID;
    static int nrApartamente;
    int nrCamere;
    float intretinere;
    int nrLocuitori;
    string* locuitori;

public:
    friend void AfisareComplex(const Proprietate& p, const Apartament& a, const Parcare& parc);
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

    //Copy Constructor
    Apartament(const Apartament& ap): ID(++nrApartamente), nrCamere(ap.nrCamere), intretinere(ap.intretinere),
                                      nrLocuitori(ap.nrLocuitori)
    {
        locuitori = new string[nrLocuitori];

        for (int i = 0; i < nrLocuitori; i++)
        {
            locuitori[i] = ap.locuitori[i];
        }
    }

    //Destructor
    ~Apartament()
    {
        if (locuitori != nullptr)
        {
            delete[] locuitori;
        }
        nrApartamente--;
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
        if (locuitori != nullptr)
        {
            delete[] locuitori;
        }

        locuitori = new string[nrlc];

        for (int i = 0; i < nrlc; i++)
        {
            locuitori[i] = loc[i];
        }
        nrLocuitori = nrlc;

        delete[] loc;
    }

    int GetID() const
    {
        return ID;
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

    //Setter static pentru numarul apartamentelor
    static void SetNrApartamente(int nr)
    {
        nrApartamente = nr;
    }

    //Getter static pentru numarul apartamentelor
    static int GetNrApartamente()
    {
        return nrApartamente;
    }
    #pragma endregion
    #pragma region Overloads
    //Supraincarcare operator atribuire
    Apartament& operator=(const Apartament& a)
    {
        if(this != &a)
        {
            nrCamere = a.nrCamere;
            intretinere = a.intretinere;
            nrLocuitori = a.nrLocuitori;

            if(locuitori != nullptr)
            {
                delete[] locuitori;
            }

            locuitori = new string[nrLocuitori];
            
            for(int i = 0; i < nrLocuitori; i++)
            {
                locuitori[i] = a.locuitori[i];
            }
        }
        return *this;
    }
    //Supraincarcare operator index
    string& operator[](int index)
    {
        if(index >= 0 && index < nrLocuitori)
        {
            return locuitori[index];
        }
        throw "Index out of range";
    }
    #pragma endregion
};

// Initializare atribut static
int Apartament::nrApartamente = 0;

//Clasa 3 - contine P si E (ParcarE)
class Parcare
{
private:
    const int ID; //atribut constant
    static int nrParcari; //atribut static
    unsigned int capacitateLocuri;
    unsigned int locuriOcupate;
    unsigned int* idMasini;

public:
    friend void AfisareComplex(const Proprietate& p, const Apartament& a, const Parcare& parc);
    //Atribut pointer ce va aloca spatiu un HEAP - id-ul propriul fiecarei masini, nu id pentru evidenta
    #pragma region Constructori/Destructori
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

    //Copy Constructor
    Parcare(const Parcare& parc): ID(++nrParcari), capacitateLocuri(parc.capacitateLocuri),
                                  locuriOcupate(parc.locuriOcupate)
    {
        idMasini = new unsigned int[locuriOcupate];

        for (int i = 0; i < locuriOcupate; i++)
        {
            idMasini[i] = parc.idMasini[i];
        }
    }

    //Destructor
    ~Parcare()
    {
        if (idMasini != nullptr)
        {
            delete[] idMasini;
        }
        nrParcari--;
    }
    #pragma endregion
    #pragma region Metode/Functii
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
    #pragma endregion
    #pragma region Getteri/Setteri
    //Setter pentru capacitate locuri
    void SetCapacitateLocuri(unsigned int caploc)
    {
        capacitateLocuri = caploc;
    }

    //Setter pentru locuri ocupate
    void SetLocuriOcupate(unsigned int lococup)
    {
        locuriOcupate = lococup;
    }

    //Setter pentru masini
    void SetIdMasini(unsigned int* listaid, int ocup)
    {
        if (idMasini != nullptr)
        {
            delete[] idMasini;
        }

        idMasini = new unsigned int[ocup];

        for (int i = 0; i < ocup; i++)
        {
            idMasini[i] = listaid[i];
        }

        locuriOcupate = ocup;
    }

    int GetID() const
    {
        return ID;
    }

    //Getter pentru capacitatea locurilor
    unsigned int GetCapacitateLocuri()
    {
        return capacitateLocuri;
    }

    //Getter pentru numarul locurilor ocupate
    unsigned int GetLocuriOcupate()
    {
        return locuriOcupate;
    }

    //Getter pentru idurile masinilor din parcare
    unsigned int* GetIdMasini() const
    {
        return idMasini;
    }

    //Setter static pentru numarul parcarilor
    static void SetNrParcari(int nr)
    {
        nrParcari = nr;
    }

    //Getter static pentru numarul parcarilor
    static int GetNrParcari()
    {
        return nrParcari;
    }
    #pragma endregion
    #pragma region Overloads
    Parcare& operator=(const Parcare &p)
    {
        if(this != &p)
        {
            capacitateLocuri = p.capacitateLocuri;
            locuriOcupate = p.locuriOcupate;
            if(idMasini != nullptr)
            {
                delete[] idMasini;
            }

            idMasini = new unsigned int[locuriOcupate];

            for(unsigned int i = 0; i < locuriOcupate; i++)
            {
                idMasini[i] = p.idMasini[i];
            }
        }
        return *this;
    }
    #pragma endregion
    //Supraincarcare operator index
    int operator[](unsigned int index)
    {
        if(index >= 0 && index < locuriOcupate)
        {
            return idMasini[index];
        }
        throw "Index out of range";
    }
};

//Initializam atributul static
int Parcare::nrParcari = 0;


void AfisareProprietate(const Proprietate& p)
{
    cout << "Proprietatea nr " << p.ID << ":" << endl;
    cout << "Pret: " << p.pret << endl;
    cout << "Locatie: " << p.locatie << endl;
    cout << "Numar Facilitati: " << p.nrFacilitati << endl;
    cout << "Facilitati:" << endl;
    if (p.nrFacilitati > 0 || p.facilitati != nullptr)
    {
        cout << "{" << endl;
        for (int i = 0; i < p.nrFacilitati; i++)
        {
            cout << p.facilitati[i] << endl;
        }
        cout << "}" << endl;
    }
    else
    {
        cout << "Nicio facilitate disponibila..." << endl;
    }
    cout << endl;
}

void AfisareComplex(const Proprietate& p, const Apartament& a, const Parcare& parc)
{
    cout << "Informatii complex:" << endl;

    cout << "Proprietatea nr " << p.ID << ":" << endl;
    cout << "Pret: " << p.pret << endl;
    cout << "Locatie: " << p.locatie << endl;
    cout << "Numar Facilitati: " << p.nrFacilitati << endl;
    cout << "Facilitati:" << endl;
    if (p.nrFacilitati > 0 || p.facilitati != nullptr)
    {
        cout << "{" << endl;
        for (int i = 0; i < p.nrFacilitati; i++)
        {
            cout << p.facilitati[i] << endl;
        }
        cout << "}" << endl;
    }
    else
    {
        cout << "Nicio facilitate disponibila..." << endl;
    }
    cout << endl;

    cout << "Apartamentul nr " << a.ID << ":" << endl;
    cout << "Numar Camere: " << a.nrCamere << endl;
    cout << "Intretinere: " << a.intretinere << endl;
    cout << "Numar Locuitori: " << a.nrLocuitori << endl;
    cout << "Facilitati:" << endl;
    if (a.nrLocuitori > 0 || a.locuitori != nullptr)
    {
        cout << "{" << endl;
        for (int i = 0; i < a.nrLocuitori; i++)
        {
            cout << a.locuitori[i] << endl;
        }
        cout << "}" << endl;
    }
    else
    {
        cout << "Apartamentul nu este locuit..." << endl;
    }
    cout << endl;

    cout << "Parcarea nr " << parc.ID << endl;
    cout << "Capacitate parcare: " << parc.capacitateLocuri << endl;
    cout << "Numar locuri de parcare ocupate: " << parc.locuriOcupate << endl;
    cout << "Masini parcate (ID-uri):" << endl;
    if (parc.locuriOcupate > 0 || parc.idMasini != nullptr)
    {
        cout << "{" << endl;
        for (int i = 0; i < parc.locuriOcupate; i++)
        {
            cout << parc.idMasini[i] << endl;
        }
        cout << "}" << endl;
    }
    else
    {
        cout << "Parcarea este goala..." << endl;
    }
    cout << endl;
}


void main()
{
    Proprietate prop1(1200.0f, "Bd. Nicolae Balcescu 23a, Bl. Bla, Ap. Bla", 3,
                      new string[3]{"Termoficare", "Canalizare", "Izolare"});
    Proprietate prop2("Str. Panselelor nr. 12, Bl. Bla, Ap. Bla");
    Proprietate prop3;

    Apartament ap1(3, 443.27f, 3, new string[3]{"Popescu Mariana", "Popescu Beniamin", "Popescu Popescu"});
    Apartament ap2(3);
    Apartament ap3;


    Parcare parcare1(10, 3, new unsigned int[3]{1234, 435, 562});
    Parcare parcare2(12);
    Parcare parcare3;

    cout << "Initial avem " << Proprietate::GetNrProp() << " proprietati, " << Apartament::GetNrApartamente() <<
        " apartamente si " << Parcare::GetNrParcari() << " parcari." << endl << endl;

    AfisareProprietate(prop1);
    AfisareProprietate(prop2);
    AfisareProprietate(prop3);

    Proprietate::AplicareDiscount(20, prop1);

    cout << "Initial parcarea nr " << parcare1.GetID() << " contine " << parcare1.GetLocuriOcupate() <<
        " masini parcate. ID-urile masinilor parcate sunt:";
    const unsigned int* masini = parcare1.GetIdMasini();
    for (int i = 0; i < parcare1.GetLocuriOcupate(); i++)
    {
        cout << " " << masini[i];
        if (i != parcare1.GetLocuriOcupate() - 1)
        {
            cout << ",";
        }
    }
    cout << "." << endl << endl;

    Parcare::EvacuareMasina(435, parcare1);

    AfisareComplex(prop1, ap1, parcare1);

    cout<<"Atribuire...."<<endl;
    
    prop3 = prop1;
    ap3 = ap1;
    parcare3 = parcare1;
    AfisareComplex(prop3,ap3,parcare3);

    cout<<"Facilitatea 3, elementul nr "<<1<<": "<<prop3[0]<<endl;
    cout<<"Apartament 3, elementul nr "<<3<<": "<<ap3[2]<<endl;
    cout<<"Parcarea 3, elementul nr "<<2<<": "<<parcare3[1]<<endl;

    cout<<"Proprietate mai ieftina dintre 1 si 3 este: "<<(prop1<prop3?"prop1":"prop3")<<endl;
}

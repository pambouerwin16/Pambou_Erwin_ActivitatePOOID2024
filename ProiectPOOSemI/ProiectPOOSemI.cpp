#include <iostream>

using namespace std;

// Cele 3 clase initiale for fi Proprietate, Apartament, Parcare deoarece contin initialele mele P (Pambou) si respectiv E (Erwin-Emmanuel)

class Proprietate
{
    private:
    const int ID;
    static int nrProprietati;
    float pret;
    string locatie;
    int nrFacilitati;
    string* facilitati;
    
    public:
    
    Proprietate():ID(++nrProprietati)
    {
        pret = 0.0f;
        locatie = "Necunoscut";
        nrFacilitati = 0;
        facilitati = nullptr;
    }
    Proprietate(string locatieprop): ID(++nrProprietati)
    {
        pret = 0.0f;
        locatie = locatieprop;
        nrFacilitati = 0;
        string* facilitati = nullptr;
    }
    Proprietate(float pretprop, string locatieprop, int nrfacprop, string* facilitatiprop):ID(++nrProprietati)
    {
        pret = pretprop;
        locatie = locatieprop;
        nrFacilitati = nrfacprop;
        facilitati = new string[nrFacilitati];
        for(int i =0; i<nrFacilitati;i++)
        {
            facilitati[i] = facilitatiprop[i];
        }
        delete[] facilitatiprop;
    }
    ~Proprietate()
    {
        if(facilitati!= nullptr)
        {
            delete[] facilitati;    
        }
    }



#pragma region Getters
    int GetID()const
    {
        return ID;
    }
    int GetNrProprietati()const
    {
        return nrProprietati;
    }
    float GetPretProprietate()const
    {
        return pret;
    }
    int GetNrFacilitati()const
    {
        return nrFacilitati;
    }
    string* GetFacilitati()const
    {
        return facilitati;
    }
    static int GetNrProprietati()
    {
        return nrProprietati;
    }
#pragma endregion
#pragma region Setters
    void SetPret(float newprice)
    {
        if(newprice >= 0)
        {
            pret = newprice;
        }
        throw "Invalid price";
    }
    void SetLocatie(string newlocation)
    {
        if(!locatie.empty())
        {
            locatie = newlocation;
        }
        else
        {
            throw "Invalid property location";
        }
    }
    void SetFacilitati(int nrfacnou ,string* listafac)
    {
        nrFacilitati = nrfacnou;
        if(facilitati != nullptr)
        {
            delete[] facilitati;
        }
        facilitati = new string[nrFacilitati];
        for(int i = 0; i< nrFacilitati; i++)
        {
            facilitati[i] = listafac[i];
        }
        delete[] listafac;
    }
#pragma endregion
#pragma region Methods
    void Afisare()
    {
        cout << "Proprietate nr "<< ID<<":"<<endl;
        cout << "Pret: "<< pret << endl;
        cout << "Locatie: "<< locatie << endl;
        if(nrFacilitati <= 0)
        {
            cout<<"Nicio facilitate disponibila" << endl;
        }
        else
        {
        cout << "Facilitati:"<<endl<<"{"<<endl;
        for(int i = 0; i < nrFacilitati ; i++)
        {
            cout<< facilitati[i] << endl;
        }
        cout << "}" << endl;

        cout << endl;
        }
    }

#pragma endregion
};

// 2
static void AplicareDiscount(float disc, Proprietate &p)
{
    if(disc>0)
    {
        float pret = p.GetPretProprietate();
        pret = pret*(disc/100);
        p.SetPret(pret);
    }
}
static Proprietate ComparareMaiScump(Proprietate *p1, Proprietate *p2)
{
    if(p1->pret >= p2->pret)
    {
        return *p1;
    }
    else
    {
        return *p2;
    }
}


class Apartament
{
    
};
int Proprietate::nrProprietati = 0;

void main()
{
    Proprietate p(1500.0f,"Str. Nicolae Balcescu 23a, Bl Bla, Ap Bla",3,new string[]{"Termoficare","Canalizare","Izolare"});
    p.Afisare();
}

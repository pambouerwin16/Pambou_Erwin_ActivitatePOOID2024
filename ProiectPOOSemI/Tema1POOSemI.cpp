#include <iostream>

using namespace std;

class Autobuz
{
    static int nrAutobuze;
    const int idAutobuz;
    int capacitate;
    int nrPersoaneImbarcate;
    char* producator;

public:
    Autobuz():idAutobuz(++nrAutobuze)
    {
        capacitate = 0;
        nrPersoaneImbarcate = 0;
        producator = nullptr;
    }
    Autobuz(int cap, int nrPers, char* prod):idAutobuz(++nrAutobuze)
    {
        try
        {
            if(cap >= 0)
            {
                capacitate = cap;
            }
            else
            {
                throw invalid_argument("Capacitate invalida...");
            }
        
            if(nrPers >= 0)
            {
                if(nrPers <= capacitate)
                {
                    nrPersoaneImbarcate = nrPers;
                }
                else
                {
                    throw invalid_argument("Numarul de persoane imbarcate introdus este mai mare decat capacitatea autobuzului...");
                }
            }
            else
            {
                throw invalid_argument("Numar persoane imbarcate invalid. Acesta poate lua doar valori pozitive...");
            }

            if(prod != nullptr)
            {
                if(prod[0] != '\0')
                {
                    int len = strlen(prod)+1;
                    producator = new char[len];
                    
                    for(int i = 0; i < len; i++)
                    {
                        producator[i] = prod[i];
                    }
                }
                else
                {
                    throw invalid_argument("Numele producatorului este gol...");
                }
            }
            else
            {
                throw invalid_argument("Numele producatorului este null...");
            }
        }
        catch (...)
        {
            cout<<"Exceptie intalnita la crearea obiectului cu ID-ul "<<idAutobuz<<endl;
            if(producator != nullptr)
                delete[] producator;
            throw;
        }
    }
    
    ~Autobuz()
    {
        if(producator != nullptr)
            delete[] producator;
        nrAutobuze--;
    }

    Autobuz(const Autobuz& a):idAutobuz(++nrAutobuze)
    {
        try
        {
            capacitate = a.capacitate;
            nrPersoaneImbarcate = a.nrPersoaneImbarcate;

            if(a.producator != nullptr)
            {
                int len = strlen(a.producator)+1;
                producator = new char[len];
                
                for(int i = 0; i < len; i++)
                {
                    producator[i] = a.producator[i];
                }
            }
            else
            {
                throw invalid_argument("Numele producatorului este null, nu poate fi copit.");
            }
        }
        catch (...)
        {
            cout<<"Exceptie intalnita in copy constructor, la copierea autobuzului cu ID "<<a.idAutobuz<<endl;
            if(producator != nullptr)
                delete[] producator;
            throw;
        }
    }

    Autobuz& operator=(const Autobuz& a)
    {
        try
        {
            if(this != &a)
            {
                capacitate = a.capacitate;
                nrPersoaneImbarcate = a.nrPersoaneImbarcate;
                
                if(producator != nullptr)
                    delete[] producator;
                
                if(a.producator != nullptr)
                {
                    int len = strlen(a.producator)+1;
                    producator = new char[len];
            
                    for(int i = 0; i < len; i++)
                    {
                        producator[i] = a.producator[i];
                    }
                }
                else
                {
                    producator = nullptr;
                }
            }
            else
            {
                throw invalid_argument("A fost incercata auto-atribuirea");
            }
        }
        catch (invalid_argument&)
        {
            cout<<"Exceptie intalnita la copierea autobuzului cu ID "<<a.idAutobuz<<endl;
            throw;
        }
        
        return *this;
    }

    const char* GetProducator() const
    {
        return producator;
    }

    int GetNrLocuriLibere()
    {
        try
        {
            return capacitate>=nrPersoaneImbarcate?(capacitate-nrPersoaneImbarcate):throw exception("Capacitate invalida sau numar de persoane invalid");
        }
        catch (exception&)
        {
            cout<<"Exceptie intampinata la cautarea numarului de locuri liebre";
            throw;
        }
    }

    void SetProducator(const char* p)
    {
        if(p != nullptr)
        {
            int len = strlen(p)+1;

            for(int i = 0; i < len ; i++)
            {
                producator[i] = p[i];
            }
        }
    }
};
int Autobuz::nrAutobuze = 0;

void main()
{
    try
    {
        char* p = new char[3]("ab");
        Autobuz a1(7,2,p);
        p[0] = 'x';
        Autobuz a2 = a1;
        a2.SetProducator(p);
        cout<<"producator1: "<<a1.GetProducator()<<endl;
        cout<<"producator2: "<<a2.GetProducator()<<endl;
        a2 = a1;
        cout<<"producator1: "<<a1.GetProducator()<<endl;
        cout<<"producator2: "<<a2.GetProducator()<<endl;
        cout<<"locuri libere in autobuz: "<<a2.GetNrLocuriLibere()<<endl;
    }
    catch (exception& e)
    {
        cout<<e.what()<<endl;
    }
    catch (...)
    {
        cout<<"A fost prinsa o eroare necunoscuta"<<endl;
    }

}
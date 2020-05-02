#include <iostream>
#include <fstream>
using namespace std;

class Nod
{
public:
    int valoare;
    Nod *dr;
    Nod *st;
    int inaltime;
};



int inaltime(Nod *N)
{
    if (N == NULL)
        return 0;
    return N->inaltime;
}


Nod* newNod(int valoare)
{
    Nod* nod = new Nod();
    nod->valoare = valoare;
    nod->dr = NULL;
    nod->st = NULL;
    nod->inaltime = 1;
    return(nod);
}


Nod *stRotate(Nod *y)
{
    ///cout<<"stRotate\n";
///cout<<"valoare "<<y->valoare<<endl;
    Nod *x = y->dr;
    Nod *T2 = x->st;

    x->st = y;
    y->dr = T2;

    y->inaltime = max(inaltime(y->dr),
                      inaltime(y->st)) + 1;
    x->inaltime = max(inaltime(x->dr),
                      inaltime(x->st)) + 1;


///cout<<"valoare "<<x->valoare<<endl;
    return x;
}


Nod *drRotate(Nod *x)
{
    ///cout<<"drRotate\n";
///cout<<"valoare "<<x->valoare<<endl;
    Nod *y = x->st;
    Nod *T2 = y->dr;


    y->dr = x;
    x->st = T2;

    x->inaltime = max(inaltime(x->dr),
                      inaltime(x->st)) + 1;
    y->inaltime = max(inaltime(y->dr),
                      inaltime(y->st)) + 1;

///cout<<"valoare "<<y->valoare<<endl;
    return y;
}


int echilibru(Nod *N)
{
    if (N == NULL)
        return 0;
    return inaltime(N->dr) - inaltime(N->st);
}


Nod* inserare(Nod* Nod, int valoare)
{

    if (Nod == NULL)
        return(newNod(valoare));
    if (valoare <=Nod->valoare)
        Nod->dr = inserare(Nod->dr, valoare);
    else if (valoare > Nod->valoare)
        Nod->st = inserare(Nod->st, valoare);
    else
        return Nod;

    Nod->inaltime = 1 + max(inaltime(Nod->dr),
                            inaltime(Nod->st));


    int echi = echilibru(Nod);



    if (echi > 1 && valoare < Nod->dr->valoare)
        return stRotate(Nod);


    if (echi < -1 && valoare >= Nod->st->valoare)
        return drRotate(Nod);


    if (echi > 1 && valoare > Nod->dr->valoare)
    {
        Nod->dr = drRotate(Nod->dr);
        return stRotate(Nod);
    }


    if (echi < -1 && valoare <= Nod->st->valoare)
    {
        Nod->st = stRotate(Nod->st);
        return drRotate(Nod);
    }


    return Nod;
}





Nod * valoaremin(Nod* nod)
{
    Nod* curent = nod;


    while (curent->dr != NULL)
        curent = curent->dr;

    return curent;
}


Nod* stergeNod(Nod* radacina, int valoare)
{


    if (radacina == NULL)
        return radacina;


    if ( valoare < radacina->valoare )
        radacina->dr = stergeNod(radacina->dr, valoare);


    else if( valoare > radacina->valoare )
        radacina->st = stergeNod(radacina->st, valoare);


    else
    {

        if( (radacina->dr == NULL) ||
                (radacina->st == NULL) )
        {
            Nod *temp;

            if(radacina->dr)
                temp = radacina->dr;

            else
                temp=radacina->st;

            if (temp == NULL)
            {
                temp = radacina;
                radacina = NULL;
            }
            else
                *radacina = *temp;

            free(temp);
        }
        else
        {

            Nod* temp = valoaremin(radacina->st);


            radacina->valoare = temp->valoare;


            radacina->st = stergeNod(radacina->st,
                                     temp->valoare);
        }
    }


    if (radacina == NULL)
        return radacina;


    radacina->inaltime = 1 + max(inaltime(radacina->dr),
                                 inaltime(radacina->st));


    int echi = echilibru(radacina);


    if (echi > 1 &&
            echilibru(radacina->dr) >= 0)
        return stRotate(radacina);


    if (echi > 1 &&
            echilibru(radacina->dr) < 0)
    {
        radacina->dr = drRotate(radacina->dr);
        return stRotate(radacina);
    }


    if (echi < -1 &&
            echilibru(radacina->st) <= 0)
        return drRotate(radacina);


    if (echi < -1 &&
            echilibru(radacina->st) > 0)
    {
        radacina->st = stRotate(radacina->st);
        return drRotate(radacina);
    }

    return radacina;
}


int main()
{
    ifstream in("abce.in");
    ofstream out("abce.out");

    int n;
    in >> n;
    int* Noduri = new int[10000001];
    for(int i = 0; i < 10000001; i++)
    {
        Noduri[i] =0;
    }
    int nr1, nr2;
    Nod *radacina = NULL;
    while (in>>nr1)
    {
        switch (nr1)
        {
        case 1:

            in >> nr2;
            Noduri[nr2]++;
            /// out<<nr2<<endl;
            radacina = inserare(radacina, nr2);

            break;
        case 2:
            out<<"Numarul sters a aparut de "<<Noduri[nr2]<<" ori\n";
            in >> nr2;
            while(Noduri[nr2]>0)
            {
                radacina = stergeNod(radacina, nr2);
                Noduri[nr2]--;
            }
            break;
        case 3:
            in >> nr2;
            if(Noduri[nr2]>0)
            {

                out<<1<<endl;
            }
            else
            {
                out<<0<<endl;
            }

            break;
        case 4:
        {

            int flag=0;

            in >> nr2;



            int i=1000001;
            for( i=nr2; i<=1000001; ++i)
                if(Noduri[i]>=1)
                {
                    out<<i<<endl;
                    flag=1;
                    break;
                }


            if(flag==0)
                out<<-1<<endl;
            break;
        }

        case 5:
        {

            int flag=0;

            in >> nr2;


            int i=1000001;
            for( i=nr2; i>0; --i)
                if(Noduri[i]>=1)
                {
                    out<<i<<endl;
                    flag=1;
                    break;
                }

            if(flag==0)
                out<<-1<<endl;

            break;
        }
        case 6:
        {



            in >> nr2;
            int nr3;
            in >> nr3;

            for(int i=nr2+1; i<nr3; ++i)
                if(Noduri[i]>0)
                    out<<i<<" ";
            out<<endl;
            break;
        }


        default:
            out << "nu ati introdus un numar de la 1 la 6 " << endl;
        }
    }
    return 0;
}

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

HANDLE kolor = GetStdHandle( STD_OUTPUT_HANDLE );


class Statek
{
    protected:
    int liczba_pol;
    int pozostale_maszty;
    bool odgadniety; /// czy wgl potrzebne
    int n;
    int m;
    int p;
    int r;
    char lit;

    public:
        //void dzwiek_zatopienia()=0; ////?????????????
        virtual void trafienie()=0;
        virtual void tworzenie(int T[10][10])=0;
        int litery(char &);
};

int Statek:: litery(char &m)
	{
		switch(m)
			{
				case 'a' :return 0; break;
				case 'b' :return 1; break;
				case 'c' :return 2; break;
				case 'd' :return 3; break;
				case 'e' :return 4; break;
				case 'f' :return 5; break;
				case 'g' :return 6; break;
				case 'h' :return 7; break;
				case 'i' :return 8; break;
				case 'j' :return 9; break;
				case 'A' :return 0; break;
				case 'B' :return 1; break;
				case 'C' :return 2; break;
				case 'D' :return 3; break;
				case 'E' :return 4; break;
				case 'F' :return 5; break;
				case 'G' :return 6; break;
				case 'H' :return 7; break;
				case 'I' :return 8; break;
				case 'J' :return 9; break;
				default: return 10;
			}
	}



class Jednomasztowy: public Statek
{
public:

    void trafienie();
    void tworzenie(int K[10][10])=0;
};

///Potrzebny te¿ warunek na nie wyjscie poza tablice, bo juz nie losuje od 0 do 9, a obok wybranego wczesniej pola,
///ktore moglo byc przy krawedzi

void Jednomasztowy:: trafienie()
    {
        pozostale_maszty--;
        //if(!pozostale_maszty)
        //{
            SetConsoleTextAttribute( kolor, 10 );
            cout<<"Jednomasztowy trafiony zatopiony."<<endl;
            Beep(600,300);
            Beep(600,300);
        //}
        //else
        //    cout<<"Trafiony"<<endl; ///o co chodzi? ma jeden maszt tylko i tak
    }



class JComp: public Jednomasztowy
{
    public:
        JComp(int liczba)
        {
            liczba_pol=liczba;
            pozostale_maszty=liczba;
        }

    ///void trafienie();
    void tworzenie(int K[10][10]);
};

void JComp:: tworzenie(int K[10][10])
    {
        ///Pierwsze pole
        do
        {
            n=rand()%10;
            m=rand()%10;
            //K[n-1][m-1]=1;
        }
        while(K[n][m]!=0 ||
              K[n-1][m-1]!=0  || K[n][m-1]!=0  || K[n+1][m-1]!=0  || K[n-1][m]!=0  || K[n-1][m+1]!=0  || K[n][m+1]!=0  || K[n+1][m+1]!=0 || K[n+1][m]!=0 );
        K[n][m]=1;
    }

class JUser: public Jednomasztowy
{
    public:
        JUser(int liczba)
        {
            liczba_pol=liczba;
            pozostale_maszty=liczba;
        }

    void tworzenie(int K[10][10]);
};

void JUser:: tworzenie(int K[10][10])
    {
        SetConsoleTextAttribute( kolor, 14 );
        cout<<"Wprowadz poprawne wspolrzedne jednomasztowego (liczba, litera): "<<endl;
        ///Pierwsze pole
        do
        {
            SetConsoleTextAttribute( kolor, 6 );
            cout<<"Pierwsze pole: ";
            cin>>m>>lit;

            n=litery(lit);
            m--;
        }
        while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
              //|| (n-1>=0 && K[m][n-1]!=0) || (m-1>=0 && K[m-1][n]!=0) || (n+1<10 && K[m][n+1]!=0) || (m+1<10 && K[m+1][n]!=0)///pola sąsiednie w pionie i poziomie mogą być tylko puste);
              ||  (K[m-1][n-1]==4 || K[m-1][n-1]==2 || K[m-1][n-1]==3) || (K[m-1][n+1]==4 || K[m-1][n+1]==2 || K[m-1][n+1]==3) || (K[m+1][n-1]==4 || K[m+1][n-1]==2 || K[m+1][n-1]==3) || (K[m+1][n+1]==4 || K[m+1][n+1]==2 || K[m+1][n+1]==3) );///pola po ukosie koniecznie puste muszą być
            ///albo zajęte przez maszt tego samego okrętu - nie będzie sytuacji stykania tylko różkiem z resztą okrętu, bo w następny kroku sprawdzę, czy boki przlegają

        K[m][n]=1;
    }



class Dwumasztowy: public Statek
{
    public:

    void trafienie();
    void tworzenie(int K[10][10])=0;

};

void Dwumasztowy:: trafienie()
    {
        pozostale_maszty--;
        if(!pozostale_maszty)
        {
            SetConsoleTextAttribute( kolor, 10 );
            cout<<"Dwumasztowy trafiony zatopiony."<<endl;
            Beep(600,300);
            Beep(600,300);
        }
        else
            {
                SetConsoleTextAttribute( kolor, 2 );
                cout<<"Trafiony"<<endl;
                Beep(600,900);
            }
    }



class DComp: public Dwumasztowy
{
    public:
        DComp(int liczba)
        {
            liczba_pol=liczba;
            pozostale_maszty=liczba;
        }

    void tworzenie(int K[10][10]);
};

void DComp:: tworzenie(int K[10][10])
    {
        ///Pierwsze pole
        do
        {
            n=rand()%10;
            m=rand()%10;
        }
        while(K[n][m]!=0 ||
              K[n-1][m-1]!=0 || K[n][m-1]!=0 || K[n+1][m-1]!=0 || K[n-1][m]!=0 || K[n-1][m+1]!=0 || K[n][m+1]!=0 || K[n+1][m+1]!=0 || K[n+1][m]!=0);
        K[n][m]=2;


        ///Drugie pole: warunek nie stapniecia na wybrane juz pole i zeby wybrac sasiada ow pola koniecznie
        do
        {
            p=n-1+rand()%(n+1-(n-1)+1); /// wybor p od n-1 do n+1
            r=m-1+rand()%(m+1-(m-1)+1); /// wybor r od m-1 do m+1
        }
        while(K[p][r]!=0 ||
              (p==n+1 && r==m+1) || (p==n+1 && r==m-1) || (p==n-1 && r==m+1) || (p==n-1 && r==m-1)|| ///zabezpieczenie ukosow pierwszy raz potrzebne w tym miejscu
              n<0 || n>9 || m<0 || m>9 ||
              (K[p-1][r-1]!=0 && K[p-1][r-1]!=2) || (K[p][r-1]!=0 && K[p][r-1]!=2) || (K[p+1][r-1]!=0 && K[p+1][r-1]!=2) || (K[p-1][r]!=0 && K[p-1][r]!=2) || (K[p-1][r+1]!=0 && K[p-1][r+1]!=2) || (K[p][r+1]!=0 && K[p][r+1]!=2) || (K[p+1][r+1]!=0 && K[p+1][r+1]!=2) || (K[p+1][r]!=0 && K[p+1][r]!=2));
                                /// dodatkowy warunek - nie moga byc wybrane po ukosie
        K[p][r]=2;

    }

class DUser: public Dwumasztowy
{
    public:
        DUser(int liczba)
        {
            liczba_pol=liczba;
            pozostale_maszty=liczba;
        }


    void tworzenie(int K[10][10]);
};

void DUser:: tworzenie(int K[10][10])
    {
        SetConsoleTextAttribute( kolor, 14 );
        cout<<"Wprowadz poprawne wspolrzedne dwumasztowego (dwa razy: liczba, litera): "<<endl;
        ///Pierwsze pole
        do
        {
            SetConsoleTextAttribute( kolor, 6 );
            cout<<"Pierwsze pole: ";
            cin>>m>>lit;

            n=litery(lit);
            m--;
        }
        while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
              || (n-1>=0 && K[m][n-1]!=0) || (m-1>=0 && K[m-1][n]!=0) || (n+1<10 && K[m][n+1]!=0) || (m+1<10 && K[m+1][n]!=0)///pola sąsiednie w pionie mogą być tylko puste);
              ||  (K[m-1][n-1]==1 || K[m-1][n-1]==4 || K[m-1][n-1]==3) || (K[m-1][n+1]==1 || K[m-1][n+1]==4 || K[m-1][n+1]==3) || (K[m+1][n-1]==1 || K[m+1][n-1]==4 || K[m+1][n-1]==3) || (K[m+1][n+1]==1 || K[m+1][n+1]==4 || K[m+1][n+1]==3) );///pola po ukosie koniecznie puste muszą być
            ///albo zajęte przez maszt tego samego okrętu - nie będzie sytuacji stykania tylko różkiem z resztą okrętu, bo w następny kroku sprawdzę, czy boki przlegają

        K[m][n]=2;


        ///Drugie pole: warunek nie stapniecia na wybrane juz pole i zeby wybrac sasiada ow pola koniecznie
        do
        {
            SetConsoleTextAttribute( kolor, 6 );
            cout<<"Drugie pole: ";
            cin>>m>>lit;

            n=litery(lit);
            m--;
        }
        while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
             || (K[m][n-1]==1 || K[m][n-1]==4 || K[m][n-1]==3) || (K[m-1][n]==1 || K[m-1][n]==4 || K[m-1][n]==3) || (K[m][n+1]==1 || K[m][n+1]==4 || K[m][n+1]==3) || (K[m+1][n]==1 || K[m+1][n]==4 || K[m+1][n]==3) ///pola sąsiednie w pionie mogą być tylko puste albo zajęte przez inny maszt obecnego statku
             ||  (K[m-1][n-1]==1 || K[m-1][n-1]==4 || K[m-1][n-1]==3) || (K[m-1][n+1]==1 || K[m-1][n+1]==4 || K[m-1][n+1]==3) || (K[m+1][n-1]==1 || K[m+1][n-1]==4 || K[m+1][n-1]==3) || (K[m+1][n+1]==1 || K[m+1][n+1]==4 || K[m+1][n+1]==3) ///pola po ukosie koniecznie puste muszą być
            ///albo zajęte przez maszt tego samego okrętu - nie będzie sytuacji stykania tylko różkiem z resztą okrętu, bo w następny kroku sprawdzę, czy boki przlegają
            || (K[m][n-1]!=2 && K[m-1][n]!=2 && K[m][n+1]!=2 && K[m+1][n]!=2)  );/// sprawdzenie, czy przynajmniej jedno z sąsiednich pól było zajęte przez obecny statek - czy choć jednym bokiem go dotykamy, żeby nie odskoczyć

        K[m][n]=2;

    }



class Trojmasztowy: public Statek
{
    public:

    void trafienie();
    void tworzenie(int K[10][10])=0;
};

void Trojmasztowy:: trafienie()
    {
        pozostale_maszty--;
        if(!pozostale_maszty)
        {
            SetConsoleTextAttribute( kolor, 10 );
            cout<<"Trojmasztowy trafiony zatopiony."<<endl;
            Beep(600,300);
            Beep(600,300);
        }
        else
            {
                SetConsoleTextAttribute( kolor, 2 );
                cout<<"Trafiony"<<endl;
                Beep(600,900);
            }
    }

class TComp: public Trojmasztowy
{
    public:
        TComp(int liczba)
        {
            liczba_pol=liczba;
            pozostale_maszty=liczba;
        }


    void tworzenie(int K[10][10]);
};


void TComp:: tworzenie(int K[10][10])
{
    ///Pierwsze pole
    do
    {
        n=rand()%10;
        m=rand()%10;
    }
    while(K[n][m]!=0 ||
          (K[n-1][m-1]!=0 && K[n-1][m-1]!=3) || (K[n][m-1]!=0 && K[n][m-1]!=3) || (K[n+1][m-1]!=0 && K[n+1][m-1]!=3) || (K[n-1][m]!=0 && K[n-1][m]!=3) || (K[n-1][m+1]!=0 && K[n-1][m+1]!=3) || (K[n][m+1]!=0 && K[n][m+1]!=3) || (K[n+1][m+1]!=0 && K[n+1][m+1]!=3) || (K[n+1][m]!=0 && K[n+1][m]!=3));
    K[n][m]=3;

    ///Drugie pole: warunek nie stapniecia na wybrane juz pole i zeby wybrac sasiada ow pola koniecznie
    do
    {
        p=n-1+rand()%(n+1-(n-1)+1); /// wybor p od n-1 do n+1
        r=m-1+rand()%(m+1-(m-1)+1); /// wybor r od m-1 do m+1
    }
    while(K[p][r]!=0 ||
          (p==n+1 && r==m+1) || (p==n+1 && r==m-1) || (p==n-1 && r==m+1) || (p==n-1 && r==m-1)||
          n<0 || n>9 || m<0 || m>9 ||
          (K[p-1][r-1]!=0 && K[p-1][r-1]!=3) || (K[p][r-1]!=0 && K[p][r-1]!=3) || (K[p+1][r-1]!=0 && K[p+1][r-1]!=3) || (K[p-1][r]!=0 && K[p-1][r]!=3) || (K[p-1][r+1]!=0 && K[p-1][r+1]!=3) || (K[p][r+1]!=0 && K[p][r+1]!=3) || (K[p+1][r+1]!=0 && K[p+1][r+1]!=3) || (K[p+1][r]!=0 && K[p+1][r]!=3));
                            /// dodatkowy warunek - nie moga byc wybrane po ukosie
    K[p][r]=3;

    /// Trzecie pole:
    do
    {
        n=p-1+rand()%(p+1-(p-1)+1); /// wybor n od p-1 do p+1
        m=r-1+rand()%(r+1-(r-1)+1); /// wybor m od r-1 do r+1
    }
    while(K[n][m]!=0 ||
          (p==n+1 && r==m+1) || (p==n+1 && r==m-1) || (p==n-1 && r==m+1) || (p==n-1 && r==m-1)||
          n<0 || n>9 || m<0 || m>9 ||
          (K[n-1][m-1]!=0 && K[n-1][m-1]!=3) || (K[n][m-1]!=0 && K[n][m-1]!=3) || (K[n+1][m-1]!=0 && K[n+1][m-1]!=3) || (K[n-1][m]!=0 && K[n-1][m]!=3) || (K[n-1][m+1]!=0 && K[n-1][m+1]!=3) || (K[n][m+1]!=0 && K[n][m+1]!=3) || (K[n+1][m+1]!=0 && K[n+1][m+1]!=3) || (K[n+1][m]!=0 && K[n+1][m]!=3));
    K[n][m]=3;
}

class TUser: public Trojmasztowy
{
    public:
        TUser(int liczba)
            {
                liczba_pol=liczba;
                pozostale_maszty=liczba;
            }


    void tworzenie(int K[10][10]);
};


void TUser:: tworzenie(int K[10][10])
{
    SetConsoleTextAttribute( kolor, 14 );
    cout<<"Wprowadz poprawne wspolrzedne trojmasztowego (trzy razy: liczba, litera): "<<endl;
    ///Pierwsze pole
    do
    {
        SetConsoleTextAttribute( kolor, 6 );
        cout<<"Pierwsze pole: ";
        cin>>m>>lit;

        n=litery(lit);
        m--;
    }
    while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
    || (n-1>=0 && K[m][n-1]!=0) || (m-1>=0 && K[m-1][n]!=0) || (n+1<10 && K[m][n+1]!=0) || (m+1<10 && K[m+1][n]!=0)///pola sąsiednie w pionie mogą być tylko puste);
    || (K[m-1][n-1]==1 || K[m-1][n-1]==2 || K[m-1][n-1]==4) || (K[m-1][n+1]==1 || K[m-1][n+1]==2 || K[m-1][n+1]==4) || (K[m+1][n-1]==1 || K[m+1][n-1]==2 || K[m+1][n-1]==4) || (K[m+1][n+1]==1 || K[m+1][n+1]==2 || K[m+1][n+1]==4) );///pola po ukosie koniecznie puste muszą być

    K[m][n]=3;

    ///Drugie pole: warunek nie stapniecia na wybrane juz pole i zeby wybrac sasiada ow pola koniecznie
    do
    {
        SetConsoleTextAttribute( kolor, 6 );
        cout<<"Drugie pole: ";
        cin>>m>>lit;

        n=litery(lit);
        m--;
    }
    while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
             || (K[m][n-1]==1 || K[m][n-1]==2 || K[m][n-1]==4) || (K[m-1][n]==1 || K[m-1][n]==2 || K[m-1][n]==4) || (K[m][n+1]==1 || K[m][n+1]==2 || K[m][n+1]==4) || (K[m+1][n]==1 || K[m+1][n]==2 || K[m+1][n]==4) ///pola sąsiednie w pionie mogą być tylko puste albo zajęte przez inny maszt obecnego statku
             ||  (K[m-1][n-1]==1 || K[m-1][n-1]==2 || K[m-1][n-1]==4) || (K[m-1][n+1]==1 || K[m-1][n+1]==2 || K[m-1][n+1]==4) || (K[m+1][n-1]==1 || K[m+1][n-1]==2 || K[m+1][n-1]==4) || (K[m+1][n+1]==1 || K[m+1][n+1]==2 || K[m+1][n+1]==4) ///pola po ukosie koniecznie puste muszą być
            ///albo zajęte przez maszt tego samego okrętu - nie będzie sytuacji stykania tylko różkiem z resztą okrętu, bo w następny kroku sprawdzę, czy boki przlegają
            || (K[m][n-1]!=3 && K[m-1][n]!=3 && K[m][n+1]!=3 && K[m+1][n]!=3)  );/// sprawdzenie, czy przynajmniej jedno z sąsiednich pól było zajęte przez obecny statek - czy choć jednym bokiem go dotykamy, żeby nie odskoczyć

    K[m][n]=3;

    /// Trzecie pole:
    do
    {
        SetConsoleTextAttribute( kolor, 6 );
        cout<<"Trzecie pole: ";
        cin>>m>>lit;

        n=litery(lit);
        m--;
    }
    while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
    || (K[m][n-1]==1 || K[m][n-1]==2 || K[m][n-1]==4) || (K[m-1][n]==1 || K[m-1][n]==2 || K[m-1][n]==4) || (K[m][n+1]==1 || K[m][n+1]==2 || K[m][n+1]==4) || (K[m+1][n]==1 || K[m+1][n]==2 || K[m+1][n]==4) ///pola sąsiednie w pionie mogą być tylko puste albo zajęte przez inny maszt obecnego statku
    ||  (K[m-1][n-1]==1 || K[m-1][n-1]==2 || K[m-1][n-1]==4) || (K[m-1][n+1]==1 || K[m-1][n+1]==2 || K[m-1][n+1]==4) || (K[m+1][n-1]==1 || K[m+1][n-1]==2 || K[m+1][n-1]==4) || (K[m+1][n+1]==1 || K[m+1][n+1]==2 || K[m+1][n+1]==4) ///pola po ukosie koniecznie puste muszą być
    ///albo zajęte przez maszt tego samego okrętu - nie będzie sytuacji stykania tylko różkiem z resztą okrętu, bo w następny kroku sprawdzę, czy boki przlegają
    || (K[m][n-1]!=3 && K[m-1][n]!=3 && K[m][n+1]!=3 && K[m+1][n]!=3)  );/// sprawdzenie, czy przynajmniej jedno z sąsiednich pól było zajęte przez obecny statek - czy choć jednym bokiem go dotykamy, żeby nie odskoczyć


    K[m][n]=3;
}

class Czteromasztowy: public Statek
{
    public:

    void trafienie();
    void tworzenie(int K[10][10])=0;

};

void Czteromasztowy:: trafienie()
    {
        pozostale_maszty--;
        if(!pozostale_maszty)
        {
            SetConsoleTextAttribute( kolor, 10 );
            cout<<"Czteromasztowy trafiony zatopiony."<<endl;
            Beep(600,300);
            Beep(600,300);
        }
        else
            {
                SetConsoleTextAttribute( kolor, 2 );
                cout<<"Trafiony"<<endl;
                Beep(600,900);
            }
    }

class CComp: public Czteromasztowy
{
    public:
        CComp(int liczba)
        {
            liczba_pol=liczba;
            pozostale_maszty=liczba;
        }


    void tworzenie(int K[10][10]);
};

void CComp:: tworzenie(int K[10][10])
    {
        ///Pierwsze pole
        ///nie trzeba while'a, bo to pierwsze pole, jakie wgl zostanie wybrane - zaczynamy od cztromasztowca cale losowanie
        n=rand()%10;
        m=rand()%10;
        K[n][m]=4;

        ///Drugie pole: warunek nie stapniecia na wybrane juz pole i zeby wybrac sasiada ow pola koniecznie
        do
        {
            p=(n-1)+rand()%(n+1-(n-1)+1); /// wybor p od n-1 do n+1
            r=(m-1)+rand()%(m+1-(m-1)+1); /// wybor r od m-1 do m+1
        }
        while(K[p][r]!=0 ||
              (p==n+1 && r==m+1) || (p==n+1 && r==m-1) || (p==n-1 && r==m+1) || (p==n-1 && r==m-1)||
              n<0 || n>9 || m<0 || m>9 ||
              (K[p-1][r-1]!=0 && K[p-1][r-1]!=4) || (K[p][r-1]!=0 && K[p][r-1]!=4) || (K[p+1][r-1]!=0 && K[p+1][r-1]!=4) || (K[p-1][r]!=0 && K[p-1][r]!=4) || (K[p-1][r+1]!=0 && K[p-1][r+1]!=4) || (K[p][r+1]!=0 && K[p][r+1]!=4) || (K[p+1][r+1]!=0 && K[p+1][r+1]!=4) || (K[p+1][r]!=0 && K[p+1][r]!=4));
                                /// dodatkowy warunek - nie moga byc wybrane po ukosie
        K[p][r]=4;

        /// Trzecie pole:
        do
        {
            n=p-1+rand()%(p+1-(p-1)+1); /// wybor n od p-1 do p+1
            m=r-1+rand()%(r+1-(r-1)+1); /// wybor m od r-1 do r+1
        }
        while(K[n][m]!=0 || (p==n+1 && r==m+1) || (p==n+1 && r==m-1) || (p==n-1 && r==m+1) || (p==n-1 && r==m-1)|| n<0 ||
              n>9 || m<0 || m>9 ||
              (K[n-1][m-1]!=0 && K[n-1][m-1]!=4) || (K[n][m-1]!=0 && K[n][m-1]!=4) || (K[n+1][m-1]!=0 && K[n+1][m-1]!=4) || (K[n-1][m]!=0 && K[n-1][m]!=4) || (K[n-1][m+1]!=0 && K[n-1][m+1]!=4) || (K[n][m+1]!=0 && K[n][m+1]!=4) || (K[n+1][m+1]!=0 && K[n+1][m+1]!=4) || (K[n+1][m]!=0 && K[n+1][m]!=4));
        K[n][m]=4;

        ///Czwarte pole:
        do
        {
            p=n-1+rand()%(n+1-(n-1)+1); /// wybor p od n-1 do n+1
            r=m-1+rand()%(m+1-(m-1)+1); /// wybor r od m-1 do m+1
        }
        while(K[p][r]!=0 ||
              (p==n+1 && r==m+1) || (p==n+1 && r==m-1) || (p==n-1 && r==m+1) || (p==n-1 && r==m-1)||
              n<0 || n>9 || m<0 || m>9 ||
              (K[p-1][r-1]!=0 && K[p-1][r-1]!=4) || (K[p][r-1]!=0 && K[p][r-1]!=4) || (K[p+1][r-1]!=0 && K[p+1][r-1]!=4) || (K[p-1][r]!=0 && K[p-1][r]!=4) || (K[p-1][r+1]!=0 && K[p-1][r+1]!=4) || (K[p][r+1]!=0 && K[p][r+1]!=4) || (K[p+1][r+1]!=0 && K[p+1][r+1]!=4) || (K[p+1][r]!=0 && K[p+1][r]!=4));
        K[p][r]=4;
    }

class CUser: public Czteromasztowy
{
    public:
        CUser(int liczba)
        {
            liczba_pol=liczba;
            pozostale_maszty=liczba;
        }

    void tworzenie(int K[10][10]);
};

void CUser:: tworzenie(int K[10][10])
    {
        ///Pierwsze pole
        ///nie trzeba while'a, bo to pierwsze pole, jakie wgl zostanie wybrane - zaczynamy od cztrepmasztowca cale losowanie
        SetConsoleTextAttribute( kolor, 14 );
        cout<<"Wprowadz poprawne wspolrzedne czteromasztowego (cztery razy: liczba, litera): "<<endl;
        do
        {
            SetConsoleTextAttribute( kolor, 6 );
            cout<<"Pierwsze pole: ";
            cin>>m>>lit;
            /*while(!isdigit(m))
            {
                SetConsoleTextAttribute( kolor, 12 );

                cout<<"Poprawna kolejnosc danych to: liczba, litera. Podaj jeszcze raz: ";
                cin>>m>>lit;
            }*/

            n=litery(lit);
            m--;
        }
        while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
              || (n-1>=0 && K[m][n-1]!=0) || (m-1>=0 && K[m-1][n]!=0) || (n+1<10 && K[m][n+1]!=0) || (m+1<10 && K[m+1][n]!=0)///pola sąsiednie w pionie mogą być tylko puste);
              ||  (K[m-1][n-1]==1 || K[m-1][n-1]==2 || K[m-1][n-1]==3) || (K[m-1][n+1]==1 || K[m-1][n+1]==2 || K[m-1][n+1]==3) || (K[m+1][n-1]==1 || K[m+1][n-1]==2 || K[m+1][n-1]==3) || (K[m+1][n+1]==1 || K[m+1][n+1]==2 || K[m+1][n+1]==3) );///pola po ukosie koniecznie puste muszą być
            ///albo zajęte przez maszt tego samego okrętu - nie będzie sytuacji stykania tylko różkiem z resztą okrętu, bo w następny kroku sprawdzę, czy boki przlegają

        K[m][n]=4;

        ///Drugie pole: warunek nie stapniecia na wybrane juz pole i zeby wybrac sasiada ow pola koniecznie
        do
        {
            SetConsoleTextAttribute( kolor, 6 );
            cout<<"Drugie pole: ";
            cin>>m>>lit;

            n=litery(lit);
            m--;
        }
        while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
             || (K[m][n-1]==1 || K[m][n-1]==2 || K[m][n-1]==3) || (K[m-1][n]==1 || K[m-1][n]==2 || K[m-1][n]==3) || (K[m][n+1]==1 || K[m][n+1]==2 || K[m][n+1]==3) || (K[m+1][n]==1 || K[m+1][n]==2 || K[m+1][n]==3) ///pola sąsiednie w pionie mogą być tylko puste albo zajęte przez inny maszt obecnego statku
             ||  (K[m-1][n-1]==1 || K[m-1][n-1]==2 || K[m-1][n-1]==3) || (K[m-1][n+1]==1 || K[m-1][n+1]==2 || K[m-1][n+1]==3) || (K[m+1][n-1]==1 || K[m+1][n-1]==2 || K[m+1][n-1]==3) || (K[m+1][n+1]==1 || K[m+1][n+1]==2 || K[m+1][n+1]==3) ///pola po ukosie koniecznie puste muszą być
            ///albo zajęte przez maszt tego samego okrętu - nie będzie sytuacji stykania tylko różkiem z resztą okrętu, bo w następny kroku sprawdzę, czy boki przlegają
            || (K[m][n-1]!=4 && K[m-1][n]!=4 && K[m][n+1]!=4 && K[m+1][n]!=4)  );/// sprawdzenie, czy przynajmniej jedno z sąsiednich pól było zajęte przez obecny statek - czy choć jednym bokiem go dotykamy, żeby nie odskoczyć
        K[m][n]=4;

        /// Trzecie pole:
        do
        {
            SetConsoleTextAttribute( kolor, 6 );
            cout<<"Trzecie pole: ";
            cin>>m>>lit;

            n=litery(lit);
            m--;
        }
        while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
             || (K[m][n-1]==1 || K[m][n-1]==2 || K[m][n-1]==3) || (K[m-1][n]==1 || K[m-1][n]==2 || K[m-1][n]==3) || (K[m][n+1]==1 || K[m][n+1]==2 || K[m][n+1]==3) || (K[m+1][n]==1 || K[m+1][n]==2 || K[m+1][n]==3) ///pola sąsiednie w pionie mogą być tylko puste albo zajęte przez inny maszt obecnego statku
             ||  (K[m-1][n-1]==1 || K[m-1][n-1]==2 || K[m-1][n-1]==3) || (K[m-1][n+1]==1 || K[m-1][n+1]==2 || K[m-1][n+1]==3) || (K[m+1][n-1]==1 || K[m+1][n-1]==2 || K[m+1][n-1]==3) || (K[m+1][n+1]==1 || K[m+1][n+1]==2 || K[m+1][n+1]==3) ///pola po ukosie koniecznie puste muszą być
            ///albo zajęte przez maszt tego samego okrętu - nie będzie sytuacji stykania tylko różkiem z resztą okrętu, bo w następny kroku sprawdzę, czy boki przlegają
            || (K[m][n-1]!=4 && K[m-1][n]!=4 && K[m][n+1]!=4 && K[m+1][n]!=4)  );/// sprawdzenie, czy przynajmniej jedno z sąsiednich pól było zajęte przez obecny statek - czy choć jednym bokiem go dotykamy, żeby nie odskoczyć
        K[m][n]=4;

        ///Czwarte pole:
        do
        {
            SetConsoleTextAttribute( kolor, 6 );
            cout<<"Czwarte pole: ";
            cin>>m>>lit;

            n=litery(lit);
            m--;
            ///Jeśli któryś z boków przylega do istniejącego już masztu, to akceptujemy ukośne dotknięcie swoich,
            /// tylko takie całkiem różkiem zetknięte z pozostałymi nie są przepisowe. Sprawdzamy tylko
            ///czy nie ma ukośnych dotknięć z obcymi masztami.
            /*if(K[m][n-1]==4 && K[m-1][n]==4 && K[m][n+1]==4 && K[m+1][n]==4)
            {

            }*/

        }
       while(K[m][n]!=0 || n<0 || n>9 || m<0 || m>9
             || (K[m][n-1]==1 || K[m][n-1]==2 || K[m][n-1]==3) || (K[m-1][n]==1 || K[m-1][n]==2 || K[m-1][n]==3) || (K[m][n+1]==1 || K[m][n+1]==2 || K[m][n+1]==3) || (K[m+1][n]==1 || K[m+1][n]==2 || K[m+1][n]==3) ///pola sąsiednie w pionie mogą być tylko puste albo zajęte przez inny maszt obecnego statku
             ||  (K[m-1][n-1]==1 || K[m-1][n-1]==2 || K[m-1][n-1]==3) || (K[m-1][n+1]==1 || K[m-1][n+1]==2 || K[m-1][n+1]==3) || (K[m+1][n-1]==1 || K[m+1][n-1]==2 || K[m+1][n-1]==3) || (K[m+1][n+1]==1 || K[m+1][n+1]==2 || K[m+1][n+1]==3) ///pola po ukosie koniecznie puste muszą być
            ///albo zajęte przez maszt tego samego okrętu - nie będzie sytuacji stykania tylko różkiem z resztą okrętu, bo w następny kroku sprawdzę, czy boki przlegają
            || (K[m][n-1]!=4 && K[m-1][n]!=4 && K[m][n+1]!=4 && K[m+1][n]!=4)  );/// sprawdzenie, czy przynajmniej jedno z sąsiednich pól było zajęte przez obecny statek - czy choć jednym bokiem go dotykamy, żeby nie odskoczyć
        K[m][n]=4;
    }


class Plansza
{
    friend class Gra;

    public:
    int Kratka [10][10];

    Plansza()
    {
        for(int g=0;g<10;g++)
            {
                for(int h=0;h<10;h++)
                {
                    Kratka[g][h]=0;
                }
            }
    }

    template  <typename typ1, typename typ2, typename typ3, typename typ4> void wybor_miejsc (typ1 J, typ2 D, typ3 T, typ4 C);
    void wyswietl();
    void wyswietl_official();

};


void Plansza:: wyswietl()
{
    int z=1;
    //cout<<"Wylosowana plansza: "<<endl<<endl;
    SetConsoleTextAttribute( kolor, 9 );
    cout<<"    "<<"A  "<<"B  "<<"C  "<<"D  "<<"E  "<<"F  "<<"G  "<<"H  "<<"I  "<<"J  "<<endl<<endl;
    for(int i=0; i<10;i++)
    {
        SetConsoleTextAttribute( kolor, 9 );
        cout<<z<<"  ";
        if(z<10)
            cout<<" ";
        for(int j=0;j<10;j++)
        {
            if(Kratka[i][j]==0)
            {
               SetConsoleTextAttribute( kolor, 11 );
               cout<<Kratka[i][j]<<"  ";
            }
            else
            {
                SetConsoleTextAttribute( kolor, 15 );
                cout<<Kratka[i][j]<<"  ";
            }
        }
        z++;
        cout<<endl;
    }
    cout<<endl;
}

void Plansza:: wyswietl_official()
{
    int z=1;
    //cout<<"Wylosowana plansza: "<<endl<<endl;
    SetConsoleTextAttribute( kolor, 9 );
    cout<<"    "<<"A  "<<"B  "<<"C  "<<"D  "<<"E  "<<"F  "<<"G  "<<"H  "<<"I  "<<"J  "<<endl<<endl;
    for(int i=0; i<10;i++)
    {
        SetConsoleTextAttribute( kolor, 9 );
        cout<<z<<"  ";
        if(z<10)
            cout<<" ";
        for(int j=0;j<10;j++)
        {
            if(Kratka[i][j]==0)///nie odkryte pole, fala na wodzie
            {
               SetConsoleTextAttribute( kolor, 11 );
               cout<<'~'<<"  ";
            }
            if(Kratka[i][j]==1)///odkryte i trafiony maszt
            {
                SetConsoleTextAttribute( kolor, 15 );
                cout<<'X'<<"  ";
            }
            if(Kratka[i][j]==2)///odkryte i pudło
            {
                SetConsoleTextAttribute( kolor, 12 );
                cout<<'X'<<"  ";
            }
        }
        z++;
        cout<<endl;
    }
    cout<<endl;
}



class Gra
{
    private:
        int liczba_ruchow;
        int liczba;
        char litera;
        int numer_statku;

    public:

        Gra(){}

        void wejscie()
            {
                //generowanie planszy i morskiego tla
                SetConsoleTextAttribute( kolor, 9 );
                cout<<"W I T A J   W   G R Z E   W   S T A T K I"<<endl<<endl;
                //cout<<"\a"<<endl;
                Beep(800,200);
                Beep(400,200);
                Beep(800,200);
                Beep(400,200);
                //Beep(800,200);
                //Beep(400,800);

            }
        void ruchy();
        int litery(char &);
        char liczby(int &);
        ///void sztuczna_inteligencja(Plansza, JUser, DUser, TUser, CUser);

};


void Gra:: ruchy()
{
    wejscie();
    ///liczba_ruchow=0;
    srand(time(NULL));

    JComp PierwszyC(1);
    DComp DrugiC(2);
    TComp TrzeciC(3);
    CComp CzwartyC(4);
    JUser PierwszyU(1);
    DUser DrugiU(2);
    TUser TrzeciU(3);
    CUser CzwartyU(4);


    Plansza *planszaComp = new Plansza;
    Plansza *planszaUser= new Plansza;
    Plansza *planszaCompWidDlaUser= new Plansza;///plansza ze statkami komp. widoczna dla Usera - w okrojonej wersji
    ///tylko to, co odkrył ruchami widzi

    ///potrzebne do sztucznej inteligencji:
    int a1, a2, b1, b2, c1, c2, d1, d2;
    int liczba1, liczba2, stara_liczba1, stara_liczba2;
    int l_masztow=0; /// liczba trafionych masztow w danym okrecie
    int docelowa_l_masztow;/// dzieki niej poinformuję Compa, kiedy okręt zostanie zatopiony już całkiem, komputer ustawi poprzedni_zatopiony na true i zrozumie, ze nie ma juz co szukac kolejnych masztow, trzeba strzelac gdzie indziej
    //int maks_masztow=4; /// maksymalna liczba masztow, jaka moze byc do trafienia w pojedynczym statku
    ///jesli czteromasztowy zostanie zatopiony, to bd wynosila 3 itd.
    //int m1=1, m2=2, m3=3, m4=4; /// zmienne pomocnicze w ustalaniu, jaki teraz jest maks_masztow;

//    planszaComp->wybor_miejsc<JComp, DComp, TComp, CComp>(PierwszyC, DrugiC, TrzeciC, CzwartyC);
//    planszaUser->wybor_miejsc<JUser, DUser, TUser, CUser>(PierwszyU, DrugiU, TrzeciU, CzwartyU);


    CzwartyC.tworzenie(planszaComp->Kratka);
    TrzeciC.tworzenie(planszaComp->Kratka);
    DrugiC.tworzenie(planszaComp->Kratka);
    PierwszyC.tworzenie(planszaComp->Kratka);
    CzwartyU.tworzenie(planszaUser->Kratka);
    TrzeciU.tworzenie(planszaUser->Kratka);
    DrugiU.tworzenie(planszaUser->Kratka);
    PierwszyU.tworzenie(planszaUser->Kratka);

    cout<<endl<<endl;
    SetConsoleTextAttribute( kolor, 12 );
    cout<<"UWAGA! TA PLANSZA POZOSTAJE UKRYTA, DZIS POKAZUJE SIE TYLKO NA POTRZEBY ZAJEC"<<endl;
    SetConsoleTextAttribute( kolor, 15 );
    cout<<"Plansza Usera:"<<endl;
    planszaUser->wyswietl();
    SetConsoleTextAttribute( kolor, 15 );
    cout<<"Plansza Compa:"<<endl;
    planszaComp->wyswietl();


    int i=4+3+2+1;
    int j=i;
    int ile_sprawdzonych=0;

    bool poprzedni_zatopiony=true; ///zmienna mowiaca o tym, czy juz oblecielismy wszystkie pola wokol zatapianego statku
    ///na poczatek ustawiam true- nie mam zadnych niedokonczonych okretow, czysta karta na starcie
    bool zostal_niespr_sasiad=false;///zmienna mowiaca o tym, czy zostalo jeszcze wokol danego masztu jakies niesprawdzone pole
    ///wiemy dzieki niej, czy mozna brac sie juz za nastepny maszt i skakac dookola niego w poszukiwaniu kolejnych masztow

    //while(i>0 || j>0)
    while(i>0 && j>0)
    {
        SetConsoleTextAttribute( kolor, 14 );
        cout<<endl<<"Twoj ruch (liczba, litera): ";
        cin>>liczba>>litera;

        ///while(liczba>10 || liczba<1 || (litera!='a' && litera!='A' && litera!='b' && litera!='B' && litera!='c' && litera!='C' && litera!='d' && litera!='D' && litera!='e' && litera!='E' && litera!='f' && litera!='F' && litera!='g' && litera!='G' && litera!='h' && litera!='H' && litera!='i' && litera!='I' && litera!='j' && litera!='J'))
        while(liczba>10 || liczba<1 || litery(litera)==10)/// ZGRABNE ZAGRANIE xd - dwie pieczenie na jednym ogniu -
                                                          /// nie ma dlugiego warunku i nie ma warninga w switchu bez defaulta :)
        {
           SetConsoleTextAttribute( kolor, 12 );
           cout<<"Niepoprawne dane!"<<endl;
           cout<<"Wprowadz je jeszcze raz: ";
           cin>>liczba>>litera;
        }

        numer_statku=planszaComp->Kratka[liczba-1][litery(litera)];

        switch(numer_statku)
        {
            case 1:
                {

                    if(planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]==0)///Jeśli dopiero pierwszy raz będzie odkrywane
                    {
                        planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]=1;
                        PierwszyC.trafienie();
                        planszaCompWidDlaUser->wyswietl_official();
                        i--;
                    }
                    else
                        cout<<"To juz bylo!"<<endl;
                     break;
                }
            case 2:
                {

                    if(planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]==0)
                    {
                        planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]=1;
                        DrugiC.trafienie();
                        planszaCompWidDlaUser->wyswietl_official();
                        i--;
                    }
                    else
                        cout<<"To juz bylo!"<<endl;
                     break;
                }
            case 3:
                {

                    if(planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]==0)
                    {
                        planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]=1;
                        TrzeciC.trafienie();
                        planszaCompWidDlaUser->wyswietl_official();
                        i--;
                    }
                    else
                        cout<<"To juz bylo!"<<endl;
                     break;
                }
            case 4:
                {

                    if(planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]==0)
                    {
                        planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]=1;
                        CzwartyC.trafienie();
                        planszaCompWidDlaUser->wyswietl_official();
                        i--;
                    }
                    else
                        cout<<"To juz bylo!"<<endl;
                     break;
                }
            default:
                {

                    SetConsoleTextAttribute( kolor, 4 );
                    if(planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]==0)
                    {
                        planszaCompWidDlaUser->Kratka[liczba-1][litery(litera)]=2;
                        cout<<"Pudlo!"<<endl;
                        Beep(300,900);
                        planszaCompWidDlaUser->wyswietl_official();
                    }
                    else
                        cout<<"To juz bylo!"<<endl;

                }
        }

///-----------------------------------------------------------------------------------------------------------------------------------------------------
        SetConsoleTextAttribute( kolor, 15 );

        cout<<endl<<"Ruch przeciwnika:"<<endl;
        ///sztuczna_inteligencja(&planszaUser, PierwszyU, DrugiU, TrzeciU, CzwartyU, &j);
        if(poprzedni_zatopiony)///jesli poprzedni okret jest juz calkiem zatopiony, szukam nowego punktu zaczepienia
        {
            do
            {
                liczba1=rand()%10;
                liczba2=rand()%10;
            }
            while(planszaUser->Kratka[liczba1][liczba2]==5);///dopoki wybierane jest pole, o ktore juz kiedys pytalam, bo Comp musi pamietac, ktore pola juz sprawdzal i nie pytac o nie wiecej niz raz
            if(planszaUser->Kratka[liczba1][liczba2]!=0 && planszaUser->Kratka[liczba1][liczba2]!=5) ///Gdy trafię, to przestawiam pop..zat.. na false, bo odkryłam nowy statek, ktory dopiero będę zatapiała
                {
                    poprzedni_zatopiony=false;
                    docelowa_l_masztow=planszaUser->Kratka[liczba1][liczba2];///poki jeszcze nie zmienilam wartosci na 5, zapamietuje, zeby poinformowac komp., gdy juz bedzie okret zatopiony
                }
            //else
            //planszaUser->Kratka[liczba1][liczba2]=5;///jak juz wybiore pole, ktore chce sprawdzic pod katem przechowywania masztu, to odznaczam jako juz uzyte
            ///a jesli spelnilo ifa, to jeszcze nie ustawiam na 5, dopiero po wykorzystaniu danych moge zmienic wartosc na 5
        }
        else /// musimy trafiac rozumnie, przy juz trafionych szukamy kolejnych masztow
        {
            if(ile_sprawdzonych==0) ///determinuje, wokol ktorego trafionego masztu szukam nastepnych, gdy jedno jest obszukany, to sprawdzam nastepny maszt
            {
                stara_liczba1=a1;

                stara_liczba2=a2;
            }
            if(ile_sprawdzonych==1)
            {
                stara_liczba1=b1;
                stara_liczba2=b2;
            }
            if(ile_sprawdzonych==2)
            {
                stara_liczba1=c1;
                stara_liczba2=c2;
            }
            if(ile_sprawdzonych==3)
            {
                stara_liczba1=d1;
                stara_liczba2=d2;
            }

            zostal_niespr_sasiad=false; /// Jesli znajde jeszcze jakies pole wokol masztu, ktore dopiero bede oznaczala piątką, to zmienie na true
            /// a jesli nie, to znaczy, ze juz pora odpuscic sb ten maszt, ze juz wszystko przy nim zbadane
            ///ojj obejscia sasiadow nie da sie zrobic juz w petli, tylko trzeba w swiadomym ifie
            if(stara_liczba1-1>=0 && stara_liczba2-1>=0 && planszaUser->Kratka[stara_liczba1-1][stara_liczba2-1]!=5) /// dopoki wybierane pole jest juz bez szans na trafienie lub przed chwila trafione w ramach zatapianego wlasnie masztu
            {
                liczba1=stara_liczba1-1;
                liczba2=stara_liczba2-1;
                zostal_niespr_sasiad=true;
            }
            else
            {
                if(stara_liczba2-1>=0 && planszaUser->Kratka[stara_liczba1][stara_liczba2-1]!=5)
                {
                    liczba1=stara_liczba1;
                    liczba2=stara_liczba2-1;
                    zostal_niespr_sasiad=true;
                }
                else
                {
                    if(stara_liczba1+1<10 && stara_liczba2-1>=0 && planszaUser->Kratka[stara_liczba1+1][stara_liczba2-1]!=5)
                    {
                        liczba1=stara_liczba1+1;
                        liczba2=stara_liczba2-1;
                        zostal_niespr_sasiad=true;
                    }
                    else
                    {
                        if(stara_liczba1-1>=0 && planszaUser->Kratka[stara_liczba1-1][stara_liczba2]!=5)
                        {
                            liczba1=stara_liczba1-1;
                            liczba2=stara_liczba2;
                            zostal_niespr_sasiad=true;
                        }
                        else
                        {
                            if(stara_liczba1+1<10 && planszaUser->Kratka[stara_liczba1+1][stara_liczba2]!=5)
                            {
                                liczba1=stara_liczba1+1;
                                liczba2=stara_liczba2;
                                zostal_niespr_sasiad=true;
                            }
                            else
                            {
                                if(stara_liczba1-1>0 && stara_liczba2+1<10 && planszaUser->Kratka[stara_liczba1-1][stara_liczba2+1]!=5)
                                {
                                    liczba1=stara_liczba1-1;
                                    liczba2=stara_liczba2+1;
                                    zostal_niespr_sasiad=true;
                                }
                                else
                                {
                                    if(stara_liczba2+1<10 && planszaUser->Kratka[stara_liczba1][stara_liczba2+1]!=5)
                                    {
                                        liczba1=stara_liczba1;
                                        liczba2=stara_liczba2+1;
                                        zostal_niespr_sasiad=true;
                                    }
                                    else
                                    {
                                        if(stara_liczba1+1<10 && stara_liczba2+1<10 && planszaUser->Kratka[stara_liczba1+1][stara_liczba2+1]!=5)
                                        {
                                            liczba1=stara_liczba1+1;
                                            liczba2=stara_liczba2+1;
                                            zostal_niespr_sasiad=true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(zostal_niespr_sasiad==false)
            {
                ile_sprawdzonych++;
            }
        }
        SetConsoleTextAttribute( kolor, 15 );
        cout<<liczba1+1<<liczby(liczba2)<<endl;
        numer_statku=planszaUser->Kratka[liczba1][liczba2];
        planszaUser->Kratka[liczba1][liczba2]=5; ///dopiero po ustaleniu numeru statku moge tu sb zakryc wartosc nowym oznaczeniem, odznaczam 5, zeby nie pytac znow o to samo

        switch(numer_statku)
        {
            case 1: PierwszyU.trafienie();break;
            case 2: DrugiU.trafienie(); break;
            case 3: TrzeciU.trafienie(); break;
            case 4: CzwartyU.trafienie(); break;
            default:
                {
                    SetConsoleTextAttribute( kolor, 4 );
                    cout<<"Pudlo!"<<endl; //poprzednie_pudlo=true;
                }
        }

        ///wszystkie mozliwe "niepudla" zlapie w jednym ifie, zeby nie pisac w czterech case'ach tego samego
        //if(numer_statku)
        if(numer_statku!=0 && numer_statku!=5)
        {
             j--;
             if(l_masztow==0)
             {
                 a1=liczba1;
                 a2=liczba2;
             }
             if(l_masztow==1)
             {
                 b1=liczba1;
                 b2=liczba2;
             }
             if(l_masztow==2)
             {
                 c1=liczba1;
                 c2=liczba2;
             }
             if(l_masztow==3)
             {
                 d1=liczba1;
                 d2=liczba2;
             }

        l_masztow++;

        }



        //if(l_masztow==maks_masztow || zostal_niespr_sasiad==false)///zatopilismy caly okret (Kratka[.... przechowuje cyfre odpowiadajaca liczbie masztow okretu, ale nie mozna tego wykorzystac, jesli przeciwnik-komputer ma grac uczciwie
        if(l_masztow==docelowa_l_masztow) ///moge skorzystac z porownania do Kratki, bo
        ///user tez dowiaduje sie o zatopieniu okretu od programu, tak samo Comp ma prawo sie dowiedziec, to porownanie
        /// jest takie samo jak w metodzie trafienie(), tylko ze Comp nie odczyta komuniaktu o zatopieniu, ktory ta metoda
        /// generuje, wiec w ten sposob go informuję
        {
 //TO PRZENOSZE NIZEJ
            /*///jesli ostal sie false, tzn., ze juz okolice statku zbadane i nic wiecej przy nim nie znajde
            ///resetujemy zmienne i sprawdzamy jaki teraz jest maks_masztow, sasiednie pola okretu ustawiamy piatkami
            l_masztow=0; a1=0; a2=0; b1=0; b2=0; c1=0; c2=0; d1=0; d2=0, ile_sprawdzonych=0;
            poprzedni_zatopiony=true;///!!!!!!!!!!!!!!!!!!!!!!!!!*/

            //zostal_niespr_sasiad==false; /// jesli weszlam do tego ifa dzieki warunkowi sprzed || (pierwszemu warunkowi), to to ustalam na false, bo moze jeszcze nie byc ustawione

            /// sasiednie pola okretu zakrywamy piatkami (on sam jest juz zakryty), zeby  sie juz nie pytac, bo wiemy, ze tam nie znajdziemy statku usera
            for(int u=1; u<=l_masztow; u++)
            {
                ///mozemy wykorzystac tu liczba1 i liczba2, bo  te zmienne sa w tym momencie nie uzywane do niczego innego akurat
                if(u==1)
                {
                    liczba1=a1;
                    liczba2=a2;
                }
                if(u==2)
                {
                    liczba1=b1;
                    liczba2=b2;
                }
                if(u==3)
                {
                    liczba1=c1;
                    liczba2=c2;
                }
                if(u==4)
                {
                    liczba1=d1;
                    liczba2=d2;
                }

                if(liczba1-1<10 && liczba2-1<10 && liczba1-1>=0 && liczba2-1>=0)///zeby nie zawiesic, wychodzac za tablice
 ///TU ZMIENIAM PONIZEJ LEPSZE planszaUser->Kratka[liczba1-1][liczba1-1]=5;
                    planszaUser->Kratka[liczba1-1][liczba2-1]=5;
                if(liczba1<10 && liczba2-1<10 && liczba1>=0 && liczba2-1>=0)
                    planszaUser->Kratka[liczba1][liczba2-1]=5;
                if(liczba1+1<10 && liczba2-1<10 && liczba1+1>=0 && liczba2-1>=0)
                    planszaUser->Kratka[liczba1+1][liczba2-1]=5;
                if(liczba1-1<10 && liczba2<10 && liczba1-1>=0 && liczba2>=0)
                    planszaUser->Kratka[liczba1-1][liczba2]=5;
                if(liczba1+1<10 && liczba2<10 && liczba1+1>=0 && liczba2>=0)
                    planszaUser->Kratka[liczba1+1][liczba2]=5;
                if(liczba1-1<10 && liczba2+1<10 && liczba1-1>=0 && liczba2+1>=0)
                    planszaUser->Kratka[liczba1-1][liczba2+1]=5;
                if(liczba1<10 && liczba2+1<10 && liczba1>=0 && liczba2+1>=0)
                    planszaUser->Kratka[liczba1][liczba2+1]=5;
                if(liczba1+1<10 && liczba2+1<10 && liczba1+1>=0 && liczba2+1>=0)
                    planszaUser->Kratka[liczba1+1][liczba2+1]=5;


            }
            //jesli ostal sie false, tzn., ze juz okolice statku zbadane i nic wiecej przy nim nie znajde
            ///resetujemy zmienne i sprawdzamy jaki teraz jest maks_masztow, sasiednie pola okretu ustawiamy piatkami
            l_masztow=0; a1=0; a2=0; b1=0; b2=0; c1=0; c2=0; d1=0; d2=0, ile_sprawdzonych=0;
            poprzedni_zatopiony=true;///!!!!!!!!!!!!!!!!!!!!!!!!!
        }

    }

    cout<<endl;
    SetConsoleTextAttribute( kolor, 9 );
    if(i==0)
        cout<<"Wygrales. Gratuluje!"<<endl;
    if(j==0)
        cout<<"Niestety przegrales."<<endl;

    cout<<endl<<"Twoja plansza:"<<endl;
    planszaUser->wyswietl();
    SetConsoleTextAttribute( kolor, 9 );
    cout<<"Plansza komputera:"<<endl;
    planszaComp->wyswietl();

}

int Gra:: litery(char &m)
	{
		switch(m)
			{
				case 'a' :return 0; break;
				case 'b' :return 1; break;
				case 'c' :return 2; break;
				case 'd' :return 3; break;
				case 'e' :return 4; break;
				case 'f' :return 5; break;
				case 'g' :return 6; break;
				case 'h' :return 7; break;
				case 'i' :return 8; break;
				case 'j' :return 9; break;
				case 'A' :return 0; break;
				case 'B' :return 1; break;
				case 'C' :return 2; break;
				case 'D' :return 3; break;
				case 'E' :return 4; break;
				case 'F' :return 5; break;
				case 'G' :return 6; break;
				case 'H' :return 7; break;
				case 'I' :return 8; break;
				case 'J' :return 9; break;
				default: return 10;
			}
	}

char Gra::liczby(int &r)
{
    switch(r)
    {
        case 0: return 'A'; break;
        case 1: return 'B'; break;
        case 2: return 'C'; break;
        case 3: return 'D'; break;
        case 4: return 'E'; break;
        case 5: return 'F'; break;
        case 6: return 'G'; break;
        case 7: return 'H'; break;
        case 8: return 'I'; break;
        case 9: return 'J'; break;
        default: return 'P'; break; ///tak tylko, zeby nie bylo warninga
    }
}


int main()
{
    Gra *Gierka = new Gra();
    Gierka->ruchy();
    SetConsoleTextAttribute( kolor, 15 );///po zakończonej grze komunikaty systemowe mają być już białe
    return 0;
}

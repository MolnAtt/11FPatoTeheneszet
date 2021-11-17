// 11FPatoTeheneszet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

int N;
int M;
vector<int> kapacitasok;
vector<int> termelesek;
vector<vector<int>> koltseg;

vector<int> legjobbmo;
int legjobb_osszkoltseg;
vector<int> aktualismo;
int aktualis_osszkoltseg;
bool defined;



void Minimumkereses(int i = 0) // most globális változónak hagytam a program paramétereit
{
    bool level = i == N;
    bool remenytelen = defined && legjobb_osszkoltseg <= aktualis_osszkoltseg; 

    if (remenytelen)
        return;
    if (level)
    {
        // cerr << "levelet talaltam\n";
        if (!defined || aktualis_osszkoltseg < legjobb_osszkoltseg) 
        {
            legjobbmo = aktualismo;
            legjobb_osszkoltseg = aktualis_osszkoltseg;
            // cerr << "jobb megoldast talaltam, csereltem\n";
        }
        defined = true;
        return;
    }
        
    for (int j = 0; j < M; j++)
    {
        aktualismo[i] = j;
        if (termelesek[i] <= kapacitasok[j])
        {
            int ezakoltseg = koltseg[i][j] * termelesek[i];
            aktualis_osszkoltseg += ezakoltseg;
                kapacitasok[j] -= termelesek[i];
                    Minimumkereses(i + 1);
                kapacitasok[j] += termelesek[i];
            aktualis_osszkoltseg -= ezakoltseg;
        }
    }
}


int main()
{
    cin >> N >> M;
    termelesek.resize(N, -1);
    kapacitasok.resize(M, -1);
    for (int i = 0; i < N; i++)
    {
        cin >> termelesek[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> kapacitasok[i];
    }

    koltseg.resize(N, vector<int>(M));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> koltseg[i][j];
        }
    }

    aktualis_osszkoltseg = 0;
    aktualismo.resize(N, -1);
    Minimumkereses();

    cout << legjobb_osszkoltseg << endl;
    for (auto& i : legjobbmo)
    {
        cout << i + 1 << " ";
    }
}


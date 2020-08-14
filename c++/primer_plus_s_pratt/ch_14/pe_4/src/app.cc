// workmi.cpp -- multiple inheritance
// compile with workermi.cpp
#include <iostream>
#include <cstring>
#include "person.h"
#include "baddude.h"
#include "gunslinger.h"
#include "pokerplayer.h"

const int SIZE = 5;
int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::strchr;
    Person *lolas[SIZE];
    int ct;

    for (ct = 0; ct < SIZE; ct++)
    {
        char choice;
        cout << "Enter the employee category:\n"
             << "b: bad dude g: gunslinger "
             << "p: poker player q: quit\n";
        cin >> choice;
        while (strchr("bgpq", choice) == NULL)
        {
            cout << "Please enter a b, g, p, or q: ";
            cin >> choice;
        }
        if (choice == 'q')
            break;

        switch (choice)
        {
            case 'b':
                lolas[ct] = new BadDude;
                break;
            case 'g':
                lolas[ct] = new Gunslinger;
                break;
            case 'p':
                lolas[ct] = new PokerPlayer;
                break;
        }
        
        cin.get();
        lolas[ct]->Set();
    }

    cout << "\nHere is your staff:\n";
    int i;
    for (i = 0; i < ct; i++)
    {
        cout << endl;
        lolas[i]->Show();
    }
    
    for (i = 0; i < ct; i++)
        delete lolas[i];
    
    cout << "Bye.\n";
    return 0;
}


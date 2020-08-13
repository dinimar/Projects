// workmi.cpp -- multiple inheritance
// compile with workermi.cpp
#include <iostream>
#include <cstring>
#include "queuetp.h"
#include "workermi.h"
const int SIZE = 5;
int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::strchr;

    Queue<Worker *> lolas(SIZE);
    int ct;
    for (ct = 0; ct < SIZE; ct++)
    {
        char choice;
        cout << "Enter the employee category:\n"
             << "w: waiter s: singer "
             << "t: singing waiter q: quit\n";
        cin >> choice;
        while (strchr("wstq", choice) == NULL)
        {
            cout << "Please enter a w, s, t, or q: ";
            cin >> choice;
        }
        if (choice == 'q')
            break;

        Worker * tmp = nullptr;

        switch (choice)
        {
            case 'w':
                tmp = new Waiter;
                break;
            case 's':
                tmp = new Singer;
                break;
            case 't':
                tmp = new SingingWaiter;
                break;
        }

        cin.get();
        tmp->Set();
        lolas.enqueue(tmp);
    }

    cout << "\nHere is your staff:\n";
    int i;
    for (i = 0; i < ct; i++)
    {
        cout << endl;
        Worker * buffer = nullptr;
        lolas.dequeue(buffer);

        buffer->Show();
    }

    // for (i = 0; i < ct; i++)
    //     delete lolas[i];
    cout << "Bye.\n";
    
    return 0;
}
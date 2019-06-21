#include <iostream>
#include <iomanip>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    time_t ct = time(0);
    struct tm* currtime = localtime(&ct);

    int hs = 0;
    int mins = 0;
    int secs = 0;

    cout << "Enter alarm time:\n";
    cout << "Hours:\n";
    cin >> hs;
    cout << "Minutes:\n";
    cin >> mins;
    cout << "Seconds:\n";
    cin >> secs;

    while (true) {
    	ct = time(0);	
    	currtime = localtime(&ct);

		cout << setfill('0') << setw(2) << currtime->tm_hour << ":"
		     << setw(2) << currtime->tm_min << ":"
		     << setw(2) << currtime->tm_sec << endl;
		this_thread::sleep_for(std::chrono::milliseconds(1000));	    
    	
    	if (currtime->tm_hour == hs && currtime->tm_min == mins && currtime->tm_sec == secs) {
    		cout << "Wake up!" << "\a\n";
    		break;
		}
    }

    return 0;
}
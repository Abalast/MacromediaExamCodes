#include <iostream>

/*
* Ich benutze Namespaces, damit ich „cout” kurz schreiben kann.
* Normalerweise muss man es so schreiben: „std::cout”.
* Der Namespace erlaubt es mir jedoch, es zu verkürzen.
* Deshalb kann ich „cout” anstelle von „std::cout” schreiben.
*/
using namespace std;

// Definiere hier die Variable „playerhealth” als „int”. 
int playerHealth = 100;

/*
* Diese Funktion checkt, ob der Player am leben ist.
* Dabei überprüfe ich, ob playerHealth größer ist als 0
*/
bool IsAlive() {
    if (playerHealth > 0)
    {
        return true; // Wenn playerHealth mehr als 0 ist, dann ist der statement true
    }
    else {
        return false; // sonst ist es falsch
    }
}

/*
* Schreibe das extra als funktion damit ich in den nachfolgenden Tasks weniger schreiben muss.
*/
void CheckStatus() {
    
    cout << "Player Health: " << playerHealth << endl;

    if (IsAlive())
        cout << "Player is Alive" << endl;
    else
        cout << "Player is Dead" << endl;
}

int main()
{
    CheckStatus(); //Schau dir die funktion in checkStatus für mehr informationen.
}

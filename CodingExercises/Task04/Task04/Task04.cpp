#include <iostream> // Wir brauchen dies mne libary um  cout zu verwenden.
#include <cstdlib> // Wir brauchen diese Libary um Rand() zu benutzen.


/*
* Ich benutze Namespaces, damit ich „cout” kurz schreiben kann.
* Normalerweise muss man es so schreiben: „std::cout”.
* Der Namespace erlaubt es mir jedoch, es zu verkürzen.
* Deshalb kann ich „cout” anstelle von „std::cout” schreiben.
*/
using namespace std;

// Definiere hier die Variable „playerhealth” als „int”. 
int playerHealth = 100;

// AI health
int aiHealth = 100;

// Das sind die von mir erstellten Variablen, die darüber entscheiden, ob ich Treffer landen kann.
int critChance = 20;
int hitChance = 70;

// Das sind meine definierte Damage
int CritDamage = 60;
int Damage = 30;

/*
* Diese Funktion checkt, ob der Player am leben ist.
* Dabei überprüfe ich, ob playerHealth größer ist als 0
*/
bool IsAlive(int& health) {
    if (health > 0)
    {
        return true; // Wenn playerHealth mehr als 0 ist, dann ist der statement true
    }
    else {
        return false; // sonst ist es falsch
    }
}

/*
* Eine funktion, die das leben reduziert.
* Dir ist vielleicht aufgefallen, dass diese anders ist von den anderen Task
* int& wird hier benutzt, damit wir variablen, die wir vorher definiert haben der Funktion geben können
* Amsonsten würde es nur den wert kopieren. 
*/
void DamageFunction(int& health,int damage) {
    health -= damage;
}

/*
* Schreibe das extra als funktion damit ich in den nachfolgenden Tasks weniger schreiben muss.
*/
void CheckStatus(string owner, int& health) {

    cout << owner << " Health: " << health << endl;

    if (IsAlive(health))
        cout << owner << " is Alive" << endl;
    else
        cout << owner << " is Dead" << endl;
}

/*
* Wir benutzen rand() um eine zufällige nummer zu generieren
* rand() gibt eine nummer zwischen 0 bis 32767
* Deswegen benutzten wie % um unsere zufällige nummer auf 1-100 zu halten
* % is modulus Operator, genauso wie + ein Adieren Operator ist
* Mehr info zu modulus findest du in internet
*/
void AttackFunction(int& health)
{
    int randomNumber = rand() % 101; // Wichtig, wenn du 100 nehmen würdest, würde es eine number von 0-99 zurück geben.

    if (randomNumber <= critChance) {
        cout << "Critical Hit" << endl;
        DamageFunction(health,CritDamage);
    }
    else if (randomNumber <= hitChance)
    {
        cout << "Hit" << endl;
        DamageFunction(health,Damage);
    }
    else
    {
        cout << "Miss" << endl;
    }

}

void Gameloop()
{
    string command;

    cout << "\nFight Starts Player vs AI\n";

    while (playerHealth > 0 && aiHealth > 0) {
        cout << "\nEnter Atk to attack the AI: ";
        cin >> command;

        if (command == "Atk") {
            AttackFunction(aiHealth);
            CheckStatus("AI", aiHealth);
        }
        else {
            cout << "Not known command, your round is forefit!" << endl;
        }

        if (aiHealth > 0) {
            cout << "\nAI attacks" << endl;
            AttackFunction(playerHealth);
            CheckStatus("Player", playerHealth);
        }
    }

    cout << "\nFight over!" << endl;
    if (playerHealth > 0)
        cout << "You won!" << endl;
    else
        cout << "AI won!" << endl;
}

int main()
{
    srand(time(0)); //Diese Funktion wird benutzt um sicher zu gehen, dass deine Random generierte Zahl random sein wird.

    Gameloop(); //Unser Gameloop
}

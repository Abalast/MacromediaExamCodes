#include <iostream> // Wir brauchen diese libary um  cout zu verwenden.
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

// Das sind die von mir erstellten Variablen, die darüber entscheiden, ob ich Treffer landen kann.
int critChance = 20;
int hitChance = 70;

// Das sind meine definierte Damage
int CritDamage = 70;
int Damage = 30;

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
* Eine funktion, die das leben reduziert.
*/
void DamageFunction(int damage) {
    playerHealth -= damage;
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

/*
* Wir benutzen rand() um eine zufällige nummer zu generieren
* rand() gibt eine nummer zwischen 0 bis 32767
* Deswegen benutzten wie % um unsere zufällige nummer auf 1-100 zu halten
* % is modulus Operator, genauso wie + ein Adieren Operator ist
* Mehr info zu modulus findest du in internet
*/
void AttackFunction()
{
    int randomNumber = rand() % 101; // Wichtig, wenn du 100 nehmen würdest, würde es eine number von 0-99 zurück geben.

    if (randomNumber <= critChance) {
        cout << "Critical Hit" << endl;
        DamageFunction(CritDamage);
    }
    else if (randomNumber <= hitChance)
    {
        cout << "Hit" << endl;
        DamageFunction(Damage);
    }
    else
    {
        cout << "Miss" << endl;
    }

}

int main()
{
    srand(time(0)); //Diese Funktion wird benutzt um sicher zu gehen, dass deine Random generierte Zahl random sein wird.
    CheckStatus();
    AttackFunction();
    CheckStatus(); //Schau dir die funktion in checkStatus für mehr informationen.
}

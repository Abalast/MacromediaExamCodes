// PracticalExercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// Globale Lebenspunkte
int playerHealth = 100;
int aiHealth = 100;

const int critChance = 20;
const int hitChance = 70;

// Funktion Aufgabe 1: Lebensstatus prüfen
void CheckStatus(string name, int health) {
    if (health > 0)
        cout << name << " lebt noch mit " << health << " Lebenspunkten." << endl;
    else
        cout << name << " ist tot." << endl;
}

// Funktion Aufgabe 2: Schaden zufügen
void DamageFunktion(string name, int& health, int damage) {
    health -= damage;
    if (health < 0) 
        health = 0;
    cout << name << " erleidet " << damage << " Schaden." << endl;
    CheckStatus(name, health);
}

// Funktion Aufgabe 3: Angriff mit Wahrscheinlichkeiten
int AngriffFunktion() {
    int zufall = rand() % 100 + 1;

    if (zufall <= critChance) {
        cout << "Kritischer Treffer!" << endl;
        return 30; // Kritischer Schaden
    }
    else if (zufall <= hitChance) {
        cout << "Normaler Treffer." << endl;
        return 15; // Normaler Schaden
    }
    else {
        cout << "Der Angriff verfehlt." << endl;
        return 0; // Kein Schaden
    }
}

// Funktion Aufgabe 4: Spieler gegen KI
void KampfLoop() {
    string eingabe;

    cout << "\nKampf beginnt! Spieler vs KI\n";
    while (playerHealth > 0 && aiHealth > 0) {
        cout << "\nGib 'angriff' ein, um die KI anzugreifen: ";
        cin >> eingabe;

        if (eingabe == "angriff") {
            int schaden = AngriffFunktion();
            DamageFunktion("KI", aiHealth, schaden);
        }
        else {
            cout << "Ungültiger Befehl. Du verlierst deine Runde!" << endl;
        }

        if (aiHealth > 0) {
            cout << "\nKI greift zurueck!" << endl;
            int schaden = AngriffFunktion();
            DamageFunktion("Spieler", playerHealth, schaden);
        }
    }

    cout << "\nKampf beendet!" << endl;
    if (playerHealth > 0)
        cout << "Du hast gewonnen!" << endl;
    else
        cout << "Die KI hat gewonnen!" << endl;
}

int main() {
    cout << "Willkommen zum Health- und Kampf-Simulator!\n";

    srand(time(0));

    CheckStatus("Spieler", playerHealth);
    CheckStatus("KI", aiHealth);

    KampfLoop();

    return 0;
}

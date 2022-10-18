// JUDUL GAME :
// MAGIC ROYAL V3
// 
// 1. Apa Tujuan Game? 
// * Pertarungan 2 player sampai darah habis
//
// 2. Apa peluang / elemen acak dalam permainan?
// * Blessing (tambahan atribut untuk membuat power pemain semakin kuat)
// ---> Saat player ingin mendapatkan blessing ada kemungkinan gagal dan digantikan dengan atribut (health/attack/defend/add.Demage)
// ---> Dodge Blessing memberikan kemungkinan player yang memiliki membuat lawan kehilangan 1 giliran
// * Additional Demage (Serangan tambahan)
// * Heal, terdapat beberapa aksi (serang/dapatkan blessing/heal) saat player melakukan heal memiliki kemungkinan gagal
//
// 3. Apa saja kemampuan pemain?
// * Menyerang lawan
// * Mendapatkan Blessing
// * Heal
// --> Heal sebagai aksi player untuk mencoba kemungkinan menambahkan health
// --> Blessing Healer membuat player mendapatkan tambahan darah setiap kali mendapatkan giliran dengan kemungkinan 100%
// 
// 4. Apa World Rules-nya?
// * Pemain mendapatkan giliran dapat memilih aksi sesuai pilihan yang tersedia secara bergantian
// 
// 5. Apa Gameplay Rules-nya?
// * Menghabiskan health musuh sampai 0 untuk memenangkan permainan
//
// 6. Story?
// Peperangan 2 Hero
//
// 7. Karakter dalam game?
// * Player 1 dan Player 2

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

// FUNGSI-FUNGSI DALAM GAME

// FUNGSI PELENGKAP GAME
// Funsi setter untuk nama player
void setPlayerName(vector<string> &player) {
    for (int i = 0; i < 2; i++) {
        string name;
        cout << "Masukan nama player ke-" << i + 1 << " : ";
        cin >> name;
        player.push_back(name);
    }
}

// Setting custom health
void setCustomHealth(vector<int> &health, int newHealth) {
    for (int i = 0; i < 2; i++) {
        health[i] = newHealth;
    }
}

// Fungsi reset player saat game dimulai (blessing, atribut)
void resetAll(vector<string> &playerOneBlessing, vector<string> &playerTwoBlessing, vector<int> &health, vector<int> &attack, vector<int> &defend, vector<int> &addtionalDemage) {
    // Reset Blessing player 1 dan player 2
    if (playerOneBlessing.size() > 0) {
        playerOneBlessing.clear();
    }
    if (playerTwoBlessing.size() > 0) {
        playerTwoBlessing.clear();
    }

    // reset attribut player 1 dan player 2
    for (int i = 0; i < 2; i++) {
        health[i] = 300;
        attack[i] = 10;
        defend[i] = 0;
        addtionalDemage[i] = 0;
    }

}

// Tampilkan detail player
void showPlayerDetail(string name, int health, int demage, int defend, int additionalDemage) {
    cout << "============================" << endl;
    cout << "Nickname : " << name << endl;
    cout << "============================" << endl;
    cout << "Attribute" << endl;
    cout << "Health\t\t: " << health << endl;
    cout << "Attack\t\t: " << demage << endl;
    cout << "Deff\t\t: " << defend << "%" << endl;
    cout << "Add.DMG\t\t: " << additionalDemage << "%" << endl;
}

// Tampilkan detail blessing player
void showPlayerBlessing(int blessingAmount, vector<string> playerBlessing) {
    cout << "============================" << endl;
    cout << "BLESSING : " << endl;
    for (int i = 0; i < blessingAmount; i++) {
        cout << i + 1 << ". " << playerBlessing[i] << endl;
    }
}

// AKSI YANG DAPAT DILAKUKAN PLAYER (SERANG/MENDAPATKAN BLESSING/HEAL)
// Fungsi Serang dibagi menjadi 3 case : Musuh mempunyai dominance Blessing, Player memiliki Lifesteal Blessing atau keduanya.
// Funsi serangan tanpa ada blessing di kedua player
void attackEnemy(int demage, int additionalDemage, int &enemyHealth, int enemyDefend) {
    demage = demage + (demage * additionalDemage / 100) - (demage * enemyDefend / 100);
    enemyHealth = enemyHealth - demage;
    cout << "Demage " << demage << "!!!" << endl;
    system("pause");
}

// Fungsi serangan apabila musuh memiliki dominance Blessing (defend +20% pasif)
void attackOnDominance(int demage, int additionalDemage, int& enemyHealth, int enemyDefend) {
    demage = demage + (demage * additionalDemage / 100) - ((demage * enemyDefend / 100) + (demage * 20 / 100));
    enemyHealth = enemyHealth - demage;
    cout << "Demage " << demage << "!!!" << endl;
    system("pause");
}

// Funsi serangan apabila player memiliki lifesteal Blessing (lifesteal 15%)
void attackWithLifesteal(int demage, int additionalDemage, int& enemyHealth, int enemyDefend, int &health) {
    demage = demage + (demage * additionalDemage / 100) - (demage * enemyDefend / 100);
    enemyHealth = enemyHealth - demage;
    health = health + (demage * 30 / 100);
    cout << "Demage " << demage << "!!!" << endl;
    cout << "Lifesteal +" << (demage * 30 / 100) << " Health" << endl;
    system("pause");
}

// Fungsi Mendapatkan Blessing (RANDOM)
void getBlessing(vector<string>& playerBlessing, vector<string> blessing, int& health, int& demage, int& defend, int& additionalDemage) {
    int blessNumber;
    srand(static_cast<unsigned int>(time(0)));
    blessNumber = rand() % 40;
    if (blessNumber < blessing.size()) {
        if (count(playerBlessing.begin(), playerBlessing.end(), blessing[blessNumber])) {
            cout << "Blessing" << blessing[blessNumber] << "sudah ada" << endl;
        }
        else {
            cout << blessing[blessNumber] << " BLESSING ACTIVATED!!" << endl;
            playerBlessing.push_back(blessing[blessNumber]);
        }
        system("pause");
    }
    else {
        int Atr;

        if (blessNumber > 8) {
            blessNumber = 8;
        }

        srand(static_cast<unsigned int>(time(0)));
        Atr = rand() % 4 + 1;
        cout << "Gagal Mendapatkan Blessing" << endl;
        if (Atr == 1) {
            cout << "Penambahan Darah sebesar +" << blessNumber << endl;
            health = health + blessNumber;
        }
        else if (Atr == 2) {
            cout << "Penambahan Attack sebesar +" << blessNumber << endl;
            demage = demage + blessNumber;
        }
        else if (Atr == 3) {
            if ((defend + blessNumber) <= 60) {
                cout << "Penambahan Defend sebesar +" << blessNumber << "%" << endl;
                defend = defend + blessNumber;
            }
            else if ((defend + blessNumber) > 60) {
                defend = 60;
                cout << "Mendapatkan defend tambahan. namun," << endl;
                cout << "Defend tidak bisa melampaui 60%" << endl;
            }
        }
        else if (Atr == 4) {
            if ((additionalDemage + blessNumber) <= 35) {
                cout << "Penambahan Add.DMG sebesar +" << blessNumber << "%" << endl;
                additionalDemage = additionalDemage + blessNumber;
            }
            else if ((additionalDemage + blessNumber) > 35) {
                if (count(playerBlessing.begin(), playerBlessing.end(), "Hawkeye")) {
                    if ((additionalDemage + blessNumber) > 55) {
                        additionalDemage = 55;
                        cout << "Anda memiliki Hawkeye blessing" << endl;
                        cout << "Add.DMG maksimal 55%" << endl;
                    }
                    else {
                        additionalDemage = additionalDemage + blessNumber;
                        cout << "Penambahan Add.DMG sebesar +" << blessNumber << "%" << endl;
                        cout << "Dengan maksimal 55% Add.DMG (Hawkeye blessing)" << endl;
                    }
                }
                else {
                    additionalDemage = 35;
                    cout << "Mendapatkan Add.DMG tambahan. namun," << endl;
                    cout << "Add.DMG tidak bisa melampaui 35%" << endl;
                }
            }
        }
        system("pause");
    }
}

// Fungsi Heal Player
void healMe(int& health, int enemyDemage) {
    // Ada kemungkinan heal gagal
    int chance;
    srand(static_cast<unsigned int>(time(0)));
    chance = rand() % 2;
    if (chance == 0) {
        int heal = (enemyDemage * 70 / 100) + (health * 5 / 100);
        health = health + heal;
        cout << "Berhasil Melakukan Heal +" << heal << " Health" << endl;
    }
    else {
        cout << "Gagal Melakukan Heal" << endl;
    }
}

// Efek healer Blessing
void healerHeal(int& health, int enemyDemage) {
    int baseHeal = 15;
    int additionalHeal = enemyDemage * (20 / 100);
    health = health + baseHeal + additionalHeal;
    cout << "Anda mendapatkan heal sebesar +" << (baseHeal + additionalHeal) << endl;
}

// Efek dodging Blessing
int dodged() {
    // Membuat kemungkinan terkena dodge efek sebesar 20%
    int chance;
    srand(static_cast<unsigned int>(time(0)));
    chance = rand() % 50;
    if (chance == 0) {
        return 1;
    }
}

int main()
{
    // Atribut game
    vector<string> player; // Nama Player
    vector<int> health{ 300, 300 }; // Darah Player
    vector<int> demage{ 10, 10 }; // Serangan Player
    vector<int> defend{ 0, 0 }; // Defend Player
    vector<int> additionalDemage{ 0, 0 }; // Demage Tambahan
    vector<string> blessing{ "Healer", "Hawkeye", "Dominance", "Lifesteal", "Dodging" }; // Macam-macam Blessing
    vector<string> playerOneBless; // Blessing yang dimiliki Player 1
    vector<string> playerTwoBless{ "Dominance" }; // Blessing yang dimiliki Player 2

    char loop = 'y';

    // Setting nama player saat pertama game dijalankan
    setPlayerName(player);

    while (loop == 'y') {
        system("cls");

        // Show Intro Game
        cout << "WELCOME TO MAGIC ROYAL!!!" << endl;
        cout << "Player 1 (Health : " << health[0] << ") = " << player[0] << endl;
        cout << "Player 2 (Health : " << health[1] << ") = " << player[1] << endl;
        cout << "MENU GAME : " << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Set Players Health" << endl;
        cout << "0. EXIT" << endl;
        cout << "pilihan --> ";
        char choose;
        cin >> choose;
        if (choose == '1') {
            // Reset player atribut saat memulai game / restart game
            // resetAll(playerOneBless, playerTwoBless, health, demage, defend, additionalDemage);

            for (int i = 0; i < 1000; i++) {
                system("cls");

                // Pemanfaatan ganjil genap untuk menentukan giliran player 1 dan player 2
                string turn;
                if (i % 2 == 0) {
                    turn = player[0];
                }
                else {
                    turn = player[1];
                }

                // cek apakah ada blessing Healer agar setiap turn mendapatkan penambahan darah
                if (turn == player[0]) {
                    if (count(playerOneBless.begin(), playerOneBless.end(), "Healer")) {
                        healerHeal(health[0], demage[1]);
                    }
                }
                else if (turn == player[1]) {
                    if (count(playerTwoBless.begin(), playerTwoBless.end(), "Healer")) {
                        healerHeal(health[1], demage[0]);
                    }
                }

                // cek apakah musuh mempunyai dodging
                if (turn == player[0]) {
                    if (count(playerTwoBless.begin(), playerTwoBless.end(), "Dodging")) {
                        if (dodged() == 1) {
                            continue;
                        }
                    }
                }
                else if (turn == player[1]) {
                    if (count(playerOneBless.begin(), playerOneBless.end(), "Dodging")) {
                        if (dodged() == 1) {
                            continue;
                        }
                    }
                }

                // tampilkan detail plyer
                if (turn == player[0]) {
                    showPlayerDetail(player[0], health[0], demage[0], defend[0], additionalDemage[0]);
                }
                else if (turn == player[1]) {
                    showPlayerDetail(player[1], health[1], demage[1], defend[1], additionalDemage[1]);
                }

                // tampilkan daftar blessing player
                if (turn == player[0]) {
                    showPlayerBlessing(playerOneBless.size(), playerOneBless);
                }
                else if (turn == player[1]) {
                    showPlayerBlessing(playerTwoBless.size(), playerTwoBless);
                }

                // tampilkan dan tentukan aksi player

                cout << "============================" << endl;
                cout << "ACTION : " << endl;
                cout << "1. Attack" << endl;
                cout << "2. Get Blessing" << endl;
                cout << "3. Heal" << endl;
                cout << "4. Surrend" << endl;
                char action;
                cout << "SELECT Action --> ";
                cin >> action;
                if (action == '1') {
                    if (turn == player[0]) {
                        if ((count(playerOneBless.begin(), playerOneBless.end(), "Lifesteal")) && (count(playerTwoBless.begin(), playerTwoBless.end(), "Dominance"))) {
                            attackWithLifesteal(demage[0] - (demage[0] * 20 / 100), additionalDemage[0], health[1], defend[1], health[0]);
                        }
                        else if (count(playerOneBless.begin(), playerOneBless.end(), "Lifesteal")) {
                            attackWithLifesteal(demage[0], additionalDemage[0], health[1], defend[1], health[0]);
                        }
                        else if (count(playerTwoBless.begin(), playerTwoBless.end(), "Dominance")) {
                            attackOnDominance(demage[0], additionalDemage[0], health[1], defend[1]);
                        }
                        else {
                            attackEnemy(demage[0], additionalDemage[0], health[1], defend[1]);
                        }
                    }
                    else if (turn == player[1]) {
                        if ((count(playerTwoBless.begin(), playerTwoBless.end(), "Lifesteal")) && (count(playerOneBless.begin(), playerOneBless.end(), "Dominance"))) {
                            attackWithLifesteal(demage[1] - (demage[1] * 20 / 100), additionalDemage[1], health[0], defend[0], health[1]);
                        }
                        else if (count(playerTwoBless.begin(), playerTwoBless.end(), "Lifesteal")) {
                            attackWithLifesteal(demage[1], additionalDemage[1], health[0], defend[0], health[1]);
                        }
                        else if (count(playerOneBless.begin(), playerOneBless.end(), "Dominance")) {
                            attackOnDominance(demage[1], additionalDemage[1], health[0], defend[0]);
                        }
                        else {
                            attackEnemy(demage[1], additionalDemage[1], health[0], defend[0]);
                        }
                    }
                }
                else if (action == '2') {
                    if (turn == player[0]) {
                        getBlessing(playerOneBless, blessing, health[0], demage[0], defend[0], additionalDemage[0]);
                    }
                    else if (turn == player[1]) {
                        getBlessing(playerOneBless, blessing, health[1], demage[1], defend[1], additionalDemage[1]);
                    }
                }
                else if (action == '3') {
                    if (turn == player[0]) {
                        healMe(health[0], demage[1]);
                    }
                    else if (turn == player[1]) {
                        healMe(health[1], demage[0]);
                    }
                }
                else if (action == '4') {
                    i = i + 1000;
                }
                system("pause");
            }
        }
        else if (choose == '2') {
            int newHealth;
            cout << "Masukan nilai health baru --> ";
            cin >> newHealth;
            setCustomHealth(health, newHealth);
        }
        else if (choose == '0') {
            loop = 'n';
        }
    }
}
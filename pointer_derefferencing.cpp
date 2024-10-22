# include <iostream>
# include <string>

using namespace std;

class Player{
public:
    string name;
    int health;
    int xp;

    void talk(string text_to_say){cout << name << " says " << text_to_say << endl;};
    bool is_dead();
};

class Account{
public:
    string name;
    double balance;

    bool deposit(double bal);
    bool withdraw(double bal);
};

int main(){
    Player frank;
    frank.name = "Frank";
    frank.health = 100;
    frank.xp = 12;

    frank.talk("Hi there");

    Player *enemy = new Player;
    (*enemy).name = "Enemy";
    (*enemy).health = 100;
    enemy->xp = 15;

    enemy->talk("I will destroy you");


    return 0;
}

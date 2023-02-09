#include <vector>
#include <iostream>
using namespace std;

class User {
    private:
        string username;
        vector <User *> following;
    public:
        User(string name);
        void follow(User* newFollow);
        void printWhoIFollow() const;
        void setUsername(string username);
};

User::User(string name) {
    username = name;
}

void User::setUsername(string newName) {
    username = newName;    
}

void User::follow(User *newFollow) {
    following.push_back(newFollow); // the "following" vector holds User*'s
                                    // so we must also pb User*'s 
}

void User::printWhoIFollow() const {
    cout << username << " follows these users: " << endl;
    for (int i = 0; i < following.size(); i++) {
        cout << " " << following[i]->username << endl; // b/c following[i] is a User*, its an address. Instead, a dot operator is used
    }
}

int main() {
    // create objects in memory using pointers
    User *me = new User("wbuziak");
    User *ls = new User("lskywalker");
    User *ts = new User("tswift");
    User *kk = new User("kkevin");
    database <User *> allTwitterUsers;


    // follow lskywalker, tswift, & kkevin
    me->follow(ls);
    me->follow(ts);
    me->follow(kk);

    // everyone changes username
    ts->setUsername("tswozz_official"); 
    ls->setUsername("sky_sucker");
    kk->setUsername("Kactus_the_Kevin");

    me->printWhoIFollow();
}

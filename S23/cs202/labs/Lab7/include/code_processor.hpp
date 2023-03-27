#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>

class User {
  public:
     std::string username;
     std::string realname;
     int points;
     std::set <std::string> phone_numbers;
};

class Prize {
  public:
     std::string id;
     std::string description;
     int points;
     int quantity;
};

class Code_Processor {
  public:
    bool New_Prize(const std::string &id, const std::string &description, int points, int quantity);
    bool New_User(const std::string &username, const std::string &realname, int starting_points);
    bool Delete_User(const std::string &username);

    bool Add_Phone(const std::string &username, const std::string &phone);
    bool Remove_Phone(const std::string &username, const std::string &phone);
    std::string Show_Phones(const std::string &username) const;

    int Enter_Code(const std::string &username, const std::string &code);
    int Text_Code(const std::string &phone, const std::string &code);
    bool Mark_Code_Used(const std::string &code);

    int Balance(const std::string &username) const;
    bool Redeem_Prize(const std::string &username, const std::string &prize);
   
    ~Code_Processor();
    bool Write(const std::string &filename) const;

    void Double_Check_Internals() const;   /* You don't write this */

  protected:
    std::unordered_map <std::string, User *> Names;
    std::unordered_map <std::string, User *> Phones;
    std::unordered_set <std::string> Codes;
    std::unordered_map <std::string, Prize *> Prizes;
};

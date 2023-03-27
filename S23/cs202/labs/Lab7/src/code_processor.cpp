/* Will Buziak
 * Lab 7
 * cs202
 * Code Processing lab
 * implement a mock server that keeps track of rewards with web and cell phone support
*/
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "code_processor.hpp"
using namespace std;

    bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity){};
    bool Code_Processor::New_User(const string &username, const string &realname, int starting_points){};
    bool Code_Processor::Delete_User(const string &username){};

    bool Code_Processor::Add_Phone(const string &username, const string &phone){};
    bool Code_Processor::Remove_Phone(const string &username, const string &phone){};
    string Code_Processor::Show_Phones(const string &username) const{};

    int Code_Processor::Enter_Code(const string &username, const string &code){};
    int Code_Processor::Text_Code(const string &phone, const string &code){};
    bool Code_Processor::Mark_Code_Used(const string &code){};

    int Code_Processor::Balance(const string &username) const{};
    bool Code_Processor::Redeem_Prize(const string &username, const string &prize){};
   
    Code_Processor::~Code_Processor(){};
    bool Code_Processor::Write(const string &filename) const{};


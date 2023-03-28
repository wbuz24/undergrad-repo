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

bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity)
{
  if (Prizes.find(id) != Prizes.end()) return false;
  if (points <= 0) return false;
  if (quantity <= 0) return false;
  Prize *nprize = new Prize;
  nprize->id = id;
  nprize->description = description;
  nprize->points = points;
  nprize->quantity = quantity;
  Prizes.insert(make_pair(id, nprize));
  return true;
};

bool Code_Processor::New_User(const string &username, const string &realname, int starting_points)
{
  if (Names.find(username) != Names.end()) return false;  
  if (starting_points < 0) return false;
  User *newname = new User;
  newname->username = username;
  newname->realname = realname;
  newname->points = starting_points;
  Names.insert(make_pair(username, newname));
  return true;
};

bool Code_Processor::Delete_User(const string &username)
{
  if (Names.find(username) == Names.end()) return false;
  
  return false; 
};

bool Code_Processor::Add_Phone(const string &username, const string &phone)
{
  (void) username;
  (void) phone;
  return false; 
};

bool Code_Processor::Remove_Phone(const string &username, const string &phone)
{
  (void) username;
  (void) phone;
  return false; 
};

string Code_Processor::Show_Phones(const string &username) const
{
  (void) username;
  return ""; 
};

int Code_Processor::Enter_Code(const string &username, const string &code)
{
  (void) username;
  (void) code;
  return 0; 
};

int Code_Processor::Text_Code(const string &phone, const string &code)
{
  (void) phone;
  (void) code;
  return 0; 
};

bool Code_Processor::Mark_Code_Used(const string &code)
{
  (void) code;
  return false; 
};

int Code_Processor::Balance(const string &username) const
{
  (void) username;
  return 0; 
};

bool Code_Processor::Redeem_Prize(const string &username, const string &prize)
{
  (void) username;
  (void) prize;
  return false; 
};

Code_Processor::~Code_Processor()
{
  
};

bool Code_Processor::Write(const string &filename) const
{
  (void) filename;
  return false; 
};


#ifndef LOGIN_SYSTEM_H
#define LOGIN_SYSTEM_H

#include <vector>
#include <string>

class User;

void registerUser(std::vector<User>& users);
bool loginUser(std::vector<User>& users);
void logoutUser();

#endif

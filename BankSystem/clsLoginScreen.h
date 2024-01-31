#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsMainScreen.h"
#include"clsUtil.h"
#include"Global.h"

using namespace std;

class clsLoginScreen : protected clsScreen
{
private:

static bool _Login() {
	bool LoginFailed = false;
	string Username, Password;
	short FailedLoginCount = 0;
	do {


		if (LoginFailed) {
			cout << "\nInvalid Username/Password!\n";
			FailedLoginCount++;
			cout << "You have " << 3 - FailedLoginCount << " trial(s) to login\n\n";
		}
		if (FailedLoginCount == 3) {
			cout << "\nYou are locked after 3 failed trials\n\n";
			return false;
		}
		cout << "Enter Username? ";
		cin >> Username;
		cout << "Enter Password? ";
		cin >> Password;
		CurrentUser = clsUser::Find(Username, Password);
		LoginFailed = CurrentUser.IsEmpty();

	} while (LoginFailed);

	CurrentUser.RegisterLogIn();

	clsMainScreen::ShowMainMenue();

}
public:
	static bool ShowLoginScreen()
	{

		system("cls");

		_DrawScreenHeader("\t Login Screen");

		return _Login();

	}

};


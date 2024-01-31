#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include"clsUtil.h"
#include <iomanip>

class clsTotalBancesScreen :protected clsScreen
{

private:
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {

        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }

public:


     static void ShowTotalBalances()
    {


        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t  Balances List Screen";
        string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";

        _DrawScreenHeader(Title, SubTitle);


        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(25) << left << "" <<"| "<<setw(15) << left << "Accout Number";
        cout << "| " << setw(20) << left <<  "Client Name";
        cout << "| " <<setw(12) << left << "Balance";
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        double TotalBalances = clsBankClient::GetTotalBalances();
        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient& Client : vClients)
            {

                _PrintClientRecordBalanceLine(Client);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << "" << "\t\t\t\t\t\t\t          Total Balances= " << TotalBalances << endl;
        cout << setw(8) << "" << "\t\t\t\t\t (" << clsUtil::NumberToText(TotalBalances) << ")\n";
    }


};


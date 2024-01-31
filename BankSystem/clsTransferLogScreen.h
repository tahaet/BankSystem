#pragma once
#include"clsScreen.h"
#include<iomanip>
#include"clsBankClient.h"
class clsTransferLogScreen :protected clsScreen
{
private:

    static void PrintLoginRegisterRecordLine(clsBankClient::stTransferRegister TransferRegister)
    {

        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferRegister.DateTime;
        cout << "| " << setw(10) << left << TransferRegister.SAcc;
        cout << "| " << setw(10) << left << TransferRegister.DAcc;
        cout << "| " << setw(10) << left << TransferRegister.Amount;
        cout << "| " << setw(10) << left << TransferRegister.SBalance;
        cout << "| " << setw(10) << left << TransferRegister.DBalance;
        cout << "| " << setw(10) << left << TransferRegister.UserName;
    }
public:

    static void ShowTransferRegisterScreen()
    {

        vector <clsBankClient::stTransferRegister> vTransferRegisterRecord = clsBankClient::GetTransferRegisterList();

        string Title = "\tTransfer Register List Screen";
        string SubTitle = "\t\t(" + to_string(vTransferRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acc";
        cout << "| " << left << setw(10) << "d.Acc";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsBankClient::stTransferRegister Record : vTransferRegisterRecord)
            {

                PrintLoginRegisterRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};


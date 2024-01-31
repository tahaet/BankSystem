#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include"Global.h"
#include"clsDate.h"

using namespace std;
 
 class clsBankClient : public clsPerson
    {
    private:

        enum enMode { EmptyMode = 0, UpdateMode = 1,AddNewMode=2 };
        enMode _Mode;
        string _AccountNumber;
        string _PinCode;
        float _AccountBalance;
        bool _MarkForDelete = false;

        static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
        {
            vector<string> vClientData;
            vClientData = clsString::Split(Line, Seperator);

            return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

        }

        static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
        {

            string stClientRecord = "";
            stClientRecord += Client.FirstName + Seperator;
            stClientRecord += Client.LastName + Seperator;
            stClientRecord += Client.Email + Seperator;
            stClientRecord += Client.Phone + Seperator;
            stClientRecord += Client.AccountNumber() + Seperator;
            stClientRecord += Client.PinCode + Seperator;
            stClientRecord += to_string(Client.AccountBalance);

            return stClientRecord;

        }

        static  vector <clsBankClient> _LoadClientsDataFromFile()
        {

            vector <clsBankClient> vClients;

            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {

                string Line;


                while (getline(MyFile, Line))
                {

                    clsBankClient Client = _ConvertLinetoClientObject(Line);

                    vClients.push_back(Client);
                }

                MyFile.close();

            }

            return vClients;

        }

        static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
        {

            fstream MyFile;
            MyFile.open("Clients.txt", ios::out);
            if (MyFile.is_open()) {
                string Line;
                for (clsBankClient C : vClients) {
                    if (C.MarkedForDeleted() == false) {
                        Line = _ConverClientObjectToLine(C);
                        MyFile << Line << endl;
                    }
                }
                MyFile.close();
            }

        }
       
        void _Update()
        {
            vector<clsBankClient>_vClients;
            _vClients = _LoadClientsDataFromFile();
            for (clsBankClient& C : _vClients) {
            
                if (C.AccountNumber() == AccountNumber()) {
                
                    C = *this;
                }
            }

            _SaveCleintsDataToFile(_vClients);

        }

        void _AddDataLineToFile(string  stDataLine)
        {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::out | ios::app);

            if (MyFile.is_open())
            {

                MyFile << stDataLine << endl;

                MyFile.close();
            }

        }
         void _AddNew() {
           string Line= _ConverClientObjectToLine(*this);
           _AddDataLineToFile(Line);
        }

        static clsBankClient _GetEmptyClientObject()
        {
            return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
        }

        string _PrepareTransferRecord(double Amount, clsBankClient DestinationClient ,string userName ,string Separator = "#//#") {
          string TransferRecord = clsDate::GetSystemDateTimeString() + Separator + _AccountNumber + Separator +
                DestinationClient.AccountNumber()+Separator+to_string(Amount)+Separator+to_string(_AccountBalance)+Separator
                + to_string(DestinationClient.AccountBalance)
                + Separator + userName;
            return TransferRecord;

        }
      void _RegisterTransferLog(double Amount, clsBankClient DestinationClient,string UserName) {

          string stDataLine = _PrepareTransferRecord(Amount, DestinationClient, UserName, "#//#");
          fstream MyFile;
          MyFile.open("TransferLog.txt", ios::out | ios::app);
          if (MyFile.is_open()) {

              MyFile << stDataLine << endl;

              MyFile.close();
          }
      }
      struct stTransferRegister;
      static stTransferRegister _ConvertTransferRegisterLineToRecord(string Line, string Seperator = "#//#")
      {
          stTransferRegister TransferRegisterRecord;

          vector<string>TransferRegisterDataLine = clsString::Split(Line, Seperator);

          TransferRegisterRecord.DateTime = TransferRegisterDataLine[0];
          TransferRegisterRecord.SAcc = TransferRegisterDataLine[1];
          TransferRegisterRecord.DAcc = TransferRegisterDataLine[2];
          TransferRegisterRecord.Amount = stof(TransferRegisterDataLine[3]);
          TransferRegisterRecord.SBalance = stof(TransferRegisterDataLine[4]);
          TransferRegisterRecord.DBalance = stof(TransferRegisterDataLine[5]);
          TransferRegisterRecord.UserName = TransferRegisterDataLine[6];

          return TransferRegisterRecord;

      }


    public:
        struct stTransferRegister {
            string DateTime = "";
            string SAcc = "";
            string DAcc = "";
            float Amount = 0;
            float SBalance = 0;
            float DBalance = 0;
            string UserName = "";
        };

        clsBankClient(enMode Mode, string FirstName, string LastName,
            string Email, string Phone, string AccountNumber, string PinCode,
            float AccountBalance) :
            clsPerson(FirstName, LastName, Email, Phone)

        {
            _Mode = Mode;
            _AccountNumber = AccountNumber;
            _PinCode = PinCode;
            _AccountBalance = AccountBalance;

        }

        bool IsEmpty()
        {
            return (_Mode == enMode::EmptyMode);
        }
        bool MarkedForDeleted()
        {
            return _MarkForDelete;
        }

        string AccountNumber()
        {
            return _AccountNumber;
        }

        void SetPinCode(string PinCode)
        {
            _PinCode = PinCode;
        }

        string GetPinCode()
        {
            return _PinCode;
        }
        __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

        void SetAccountBalance(float AccountBalance)
        {
            _AccountBalance = AccountBalance;
        }

        float GetAccountBalance()
        {
            return _AccountBalance;
        }
        __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

       /* void Print()
        {
            cout << "\nClient Card:";
            cout << "\n___________________";
            cout << "\nFirstName   : " << FirstName;
            cout << "\nLastName    : " << LastName;
            cout << "\nFull Name   : " << FullName();
            cout << "\nEmail       : " << Email;
            cout << "\nPhone       : " << Phone;
            cout << "\nAcc. Number : " << _AccountNumber;
            cout << "\nPassword    : " << _PinCode;
            cout << "\nBalance     : " << _AccountBalance;
            cout << "\n___________________\n";

        }*/

        static clsBankClient Find(string AccountNumber)
        {


            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber() == AccountNumber)
                    {
                        MyFile.close();
                        return Client;
                    }

                }

                MyFile.close();

            }

            return _GetEmptyClientObject();
        }

        static clsBankClient Find(string AccountNumber, string PinCode)
        {



            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                    {
                        MyFile.close();
                        return Client;
                    }

                }

                MyFile.close();

            }
            return _GetEmptyClientObject();
        }

        enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1,svFailedAccountNumberExists };

        enSaveResults Save()
        {

            switch (_Mode)
            {
            case enMode::EmptyMode:
            {

                return enSaveResults::svFaildEmptyObject;
            }

            case enMode::UpdateMode:
            {


                _Update();

                return enSaveResults::svSucceeded;

                break;
            }
            case enMode::AddNewMode:
                if (clsBankClient::IsClientExist(_AccountNumber))
                    return enSaveResults::svFailedAccountNumberExists;
                else
                {
                    _AddNew();
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
                break;
            }



        }
        void Deposit(double Amount) {
            _AccountBalance += Amount;
            Save();

        }

        bool Withdraw(double Amount) {
            if (Amount > _AccountBalance) {
                return false;
            }

            else {
                _AccountBalance -= Amount;
                Save();
            }
        }
        bool Transfer(double Amount, clsBankClient& DestinationClient ,string UserName) {
            if (Amount > AccountBalance){
                return false;
        }
            Withdraw(Amount);
            DestinationClient.Deposit(Amount);
            _RegisterTransferLog(Amount ,DestinationClient,UserName);
            return true;
        }

        static bool IsClientExist(string AccountNumber)
        {

            clsBankClient Client1 = clsBankClient::Find(AccountNumber);
            return (!Client1.IsEmpty());
        }
        bool Delete() {
            vector<clsBankClient>_vClients;
            _vClients = _LoadClientsDataFromFile();
            for (clsBankClient& C : _vClients) {
                if (C.AccountNumber() == _AccountNumber) {
                    C._MarkForDelete = true;
                    break;
                }
            }
            _SaveCleintsDataToFile(_vClients);
            *this = _GetEmptyClientObject();
            return true;
        }
        static vector<clsBankClient> GetClientsList() {
            return _LoadClientsDataFromFile();
        }
        static double GetTotalBalances() {
            vector<clsBankClient>_vClients = GetClientsList();
            double TotalBalances = 0;
            for (clsBankClient& Client : _vClients) {
                TotalBalances += Client.AccountBalance;
            }
            return TotalBalances;
        }
        static clsBankClient GetAddNewClientObject(string AccountNumber) {
            return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }
      
        static vector<stTransferRegister> GetTransferRegisterList() {
            fstream MyFile;
            stTransferRegister TransferRegisterRecord;
            vector< stTransferRegister>vTransferRegisterReords;
            MyFile.open("TransferLog.txt", ios::in);
            if (MyFile.is_open()) {
                string DataLine;
                while (getline(MyFile, DataLine)) {
                    TransferRegisterRecord = _ConvertTransferRegisterLineToRecord(DataLine);
                    vTransferRegisterReords.push_back(TransferRegisterRecord);
                }
                MyFile.close();
            }
            return vTransferRegisterReords;
        }
};


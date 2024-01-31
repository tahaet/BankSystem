#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsCurrency.h"
#include"clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen :protected clsScreen
{
private:

    static void _PrintCurrency(clsCurrency Currency, string Title = "Convert From")
    {
        cout << endl << Title << ": " << endl;
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }


    static float _ReadAmount() {
        cout << "\nEnter amount to exchange: ";
        float Amount = clsInputValidate::ReadFloatNumber();
        return Amount;
    }
    static float _CalculateExchage(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo) {

        if (CurrencyFrom.Rate() < 1) {

            return  Amount * CurrencyFrom.Rate();
        }
        else

            return Amount * CurrencyTo.Rate();


    }

    static clsCurrency _GetCurrency(string Message) {
        cout << "\n" << Message << "\n";

        string CurrencyCodeFrom = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCodeFrom))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCodeFrom = clsInputValidate::ReadString();
        }

        return clsCurrency::FindByCode(CurrencyCodeFrom);
    }
   
    static void _PrintCalculationsResults(float Amount ,clsCurrency CurrencyFrom,clsCurrency CurrencyTo) {
        _PrintCurrency(CurrencyFrom);
        float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);

        cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInUSD << " USD\n";
        if (CurrencyTo.CurrencyCode() == "USD") {
            return;
        }
        cout << "\nConverting from USD to:\n";
        _PrintCurrency(CurrencyFrom, "To");
       float AmountInCurrency2 = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);
       cout << Amount << " " << CurrencyFrom.CurrencyCode() << " = " << AmountInCurrency2 << CurrencyTo.CurrencyCode() <<" \n" ;

    }
public:

    static  void ShowCurrencyCalculatorScreen() {
        char Answer = 'n';
        do{
            system("cls");
            _DrawScreenHeader("\tExchange Currency Screen");
        clsCurrency CurrencyFrom = _GetCurrency("Please enter currency1 code : ");
         
        clsCurrency CurrencyTo = _GetCurrency("Please enter currency2 code : ");
        float Amount = _ReadAmount();

        _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
        cout << "\nDo you want to perform another calaculation? y/n ";
        cin >> Answer;

        
    } while (Answer == 'y' || Answer == 'Y');

}
};


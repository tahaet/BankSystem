#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsCurrency.h"
#include"clsCurrenciesListScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyRateScreen.h"
#include"clsCurrencyCalculatorScreen.h"
using namespace std;

class clsCurrencyExchangeScreen :protected clsScreen
{
private:
    enum enCurrencyExchangeOptions { eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrency = 3, eCurrencyCalculator = 4, eMainMenue = 5 };
    static short _ReadCurrencyExchangeenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
        return Choice;
    }
    static void _ShowListCurrenciesScreen() {
       // cout << "List Currencies screen will be here...\n";
        clsCurrenciesListScreen::ShowCurrencyList();
    }

    static void _ShowFindCurrencyScreen() {
       // cout << "Find Currency screen will be here...\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowupdateCurrencyScreen() {
       // cout << "Update Currency screen will be here...\n";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowLCurrencyCalculatorScreen() {
       // cout << "Currency Calculator screen will be here...\n";
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _GoBackToCurrencyExchangeMenue() {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Exchange Menue...\n";

        system("pause>0");
        ShowCurrenceExchangeMenue();
    }
    static void _PerformCurrencyExchabgeMenueOption(enCurrencyExchangeOptions CurrencyExchangeOptions)
    {
        switch (CurrencyExchangeOptions)
        {
        case enCurrencyExchangeOptions::eListCurrencies:
        {
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeOptions::eFindCurrency:
        {
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeOptions::eUpdateCurrency:
        {
            system("cls");
            _ShowupdateCurrencyScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        }

        case enCurrencyExchangeOptions::eCurrencyCalculator:
            system("cls");
            _ShowLCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenue();
            break;

        case enCurrencyExchangeOptions::eMainMenue:
        {
            //do nothing here the main screen will handle it :-) ;

        }
        }


    }


public:

    static void ShowCurrenceExchangeMenue()
    {

        system("cls");
        _DrawScreenHeader("\tCurreny Exchange Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Date.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyExchabgeMenueOption((enCurrencyExchangeOptions)_ReadCurrencyExchangeenueOption());
    }
};


//=========================================================================
// Include Directives
//-------------------------------------------------------------------------
#include <conio.h>
#include <string.h>
#include <iomanip.h>
#include <ctype.h>
#include <stdlib.h>
#include <fstream.h>
//=========================================================================

#include "System.h"						// Program framework service
#include "MenuSer.h"						// Menu Service

#include "Master.h"						// Master table maintenance service
#include "MetBill.h"						// Metering and Billing Service
#include "Collect.h"						// Bill Collection Service
//=========================================================================

Menu MainMenu, MasterMenu;
Menu MandBMenu, CollectMenu;
//=========================================================================

//=========================================================================
// Function Prototypes
//=========================================================================
int SetMainMenu();
int SetMasterMenu();
int SetMandBMenu();
int SetCollectMenu();
void DisplayWelcome();
//=========================================================================

void main()
{
	char Thanks[20] = "Thank you!";
	int MainMnuChoice, SubMnuChoice;

	DisplayWelcome();

	do
	{
		// Set main menu items
		MainMnuChoice = SetMainMenu();

		// Display the sub menu
		switch (MainMnuChoice)
		{
			// Master Files Menu
			case 1 :
				do
				{
					SubMnuChoice = SetMasterMenu();
						switch (SubMnuChoice)
						{
							case 1 :
								MasterService(1);		// Tariff Master
								break;
							case 2 :
								MasterService(2);		// Region Master
								break;
							case 3 :
								MasterService(3);		// Circle Master
								break;
							case 4 :
								MasterService(4);		// Division Master
								break;
							case 5 :
								MasterService(5);		// Consumer Master
								break;
							default :
								break;
						}
				}while(SubMnuChoice != 0);
				break;

			// Metering and Billing Menu
			case 2 :
				do
				{
					SubMnuChoice = SetMandBMenu();
						switch (SubMnuChoice)
						{
							case 1 :
								TransferCon();				// Update Opening Reading
								break;
							case 2 :
								DisplayMeterData();		// Display metering data
								break;
							case 3 :
								UpdateCloseRead();		// Display metering data
								break;
							default :
								break;
						}
				}while(SubMnuChoice != 0);

			// Bill Collection Service
			case 3 :
				do
				{
					SubMnuChoice = SetCollectMenu();
						switch (SubMnuChoice)
						{
							case 1 :
								BillingService(1);				// Collect Bill
								break;
							case 2 :
								BillingService(2);				// Collect Bill
								break;
							default :
								break;
						}
				}while(SubMnuChoice != 0);
			default :
				break;
		}
	}while(MainMnuChoice != 0);

	// Display thanks card
	DisplayTitle("MAHARISHI VIDYAMANDIR SENIOR SECONDARY SCHOOL, CHENNAI");
	SetOutputWindow();
	cout << "\t\t       " << char(201) << setw(30) << setfill(char(205)) << "" << char(187) << endl;
	cout << "\t\t       " << char(186) << "            SPARK             " << char(186) << endl;
	cout << "\t\t       " << char(186) << "   Safe Pay At Right Kiosk    " << char(186) << endl;
	cout << "\t\t       " << char(199) << setw(30) << setfill(char(196)) << "" << char(182) << endl;
	cout << "\t\t       " << char(186) << " UTILITY BILL PAYMENT SYSTEM  " << char(186) << endl;
//	cout << "\t\t       " << char(186) << "             ***              " << char(186) << endl;
//	cout << "\t\t       " << char(186) << "              *               " << char(186) << endl;
	cout << "\t\t       " << char(200) << setw(30) << setfill(char(205)) << "" << char(188) << endl;
	window((80 - strlen(Thanks)) / 2, 12, (80 + strlen(Thanks)) / 2 - 1, 12);
	SetTextAttr(WHITE, BLUE, BLINK);
	cout << Thanks << endl << endl << endl;
	cout << "\t" << char(201) << setw(30) << setfill(char(205)) << "" <<  char(203) << setw(30) << setfill(char(205)) << ""  << char(187) << endl;
	cout << "\t" << char(186) << "          Team Members        " << char(186) << "           Guided By          " << char(186) << endl;
	cout << "\t" << char(199) << setw(30) << setfill(char(196)) << "" << char(215) << setw(30) << setfill(char(196)) << "" << char(182) << endl;
	cout << "\t" << char(186) << "  K.Vikas Mahendar, XII-A5    " << char(186) << setw(30) << setfill(' ') << "" << char(186) << endl;
	cout << "\t" << char(186) << "  N.N.Suganth, XII-A5         " << char(186) << "      Nazreen Banu Ma'am      " << char(186) << endl;
	cout << "\t" << char(186) << "  K.Adithya Krishna, XII-A5   " << char(186) << setw(30) << setfill(' ') << "" << char(186) << endl;
	cout << "\t" << char(186) << "  V.K.Viekash, XII-A5         " << char(186) << setw(30) << setfill(' ') << "" << char(186) << endl;
	cout << "\t" << char(200) << setw(30) << setfill(char(205)) << "" << char(202) << setw(30) << setfill(char(205)) << ""  << char(188) <<endl;

	// Prompt the user to press Enter to continue
	Pause();

	return ;
}

//=======================================================================

//=======================================================================
// Function Declarations
//=======================================================================
//=======================================================================
// Function to set the Main Menu items
//-------------------------------------------------------------------------
int SetMainMenu()
{
	char MainMenuItem[20][75];
	int MnuChoice;

	// Initialize the main menu items
	strcpy(MainMenuItem[0], "[1]....Master Files updation");
	strcpy(MainMenuItem[1], "[2]....Metering and Billing");
	strcpy(MainMenuItem[2], "[3]....Bill Payment");
	strcpy(MainMenuItem[3], "[0]....Exit");

	// Set the main menu items
	MainMenu.SetMenuItem(MainMenuItem, 4);

	// Set the main menu window
	MainMenu.SetColor(MAGENTA, WHITE);
	MainMenu.SetCoord(2, 4, 79, 23);
	MainMenu.SetTitle("Utility Bill Payment System though e-Wallet - Main Menu");
	MainMenu.DrawWindow();

	// Show the main menu
	MnuChoice = MainMenu.ShowMenu();

	return MnuChoice;
}
//=======================================================================

//=======================================================================
// Function to set the Master Menu items
//-------------------------------------------------------------------------
int SetMasterMenu()
{
	char MasterMenuItem[20][75];
	int MnuChoice;

	// Initialize the master service menu items
	strcpy(MasterMenuItem[0], "[1]....Tariff Master");
	strcpy(MasterMenuItem[1], "[2]....Region Master");
	strcpy(MasterMenuItem[2], "[3]....Circle Master");
	strcpy(MasterMenuItem[3], "[4]....Division Master");
	strcpy(MasterMenuItem[4], "[5]....Consumer Master");
	strcpy(MasterMenuItem[5], "[0]....Exit");

	// Set the master service menu items
	MasterMenu.SetMenuItem(MasterMenuItem, 6);

	// Set the master service menu window
	MasterMenu.SetColor(GREEN, WHITE);
	MasterMenu.SetCoord(2, 4, 79, 23);
	MasterMenu.SetTitle("Master Files Updation");
	MasterMenu.DrawWindow();

	// Show the master service menu
	MnuChoice = MasterMenu.ShowMenu();

	return MnuChoice;
}
//=======================================================================

//=======================================================================
// Function to set the Metering and Billing Sevice Menu items
//-------------------------------------------------------------------------
int SetMandBMenu()
{
	char MandBMenuItem[20][75];
	int MnuChoice;

	// Initialize the metering and billing service menu items
	strcpy(MandBMenuItem[0], "[1]...Update Meter Reading");
	strcpy(MandBMenuItem[1], "[2]...Display Metering Data");
	strcpy(MandBMenuItem[2], "[3]...Update Bill data");
	strcpy(MandBMenuItem[3], "[0]...Exit");

	// Set the metering and billing menu items
	MandBMenu.SetMenuItem(MandBMenuItem, 4);

	// Set the metering and billing menu window
	MandBMenu.SetColor(GREEN, WHITE);
	MandBMenu.SetCoord(2, 4, 79, 23);
	MandBMenu.SetTitle("Metering and Billing");
	MandBMenu.DrawWindow();

	// Show the metering and billing service menu
	MnuChoice = MandBMenu.ShowMenu();

	return MnuChoice;
}
//=======================================================================

//=======================================================================
// Function to set the Payment Sevice Menu items
//-------------------------------------------------------------------------
int SetCollectMenu()
{
	char CollectMenuItem[20][75];
	int MnuChoice;

	// Initialize the payment service menu items
	strcpy(CollectMenuItem[0], "[1]..Wallet Account Maintenance");
	strcpy(CollectMenuItem[1], "[2]..Pay Bill");
	strcpy(CollectMenuItem[2], "[0]..Exit");

	// Set the payment menu items
	CollectMenu.SetMenuItem(CollectMenuItem, 3);

	// Set the payment menu window
	CollectMenu.SetColor(GREEN, WHITE);
	CollectMenu.SetCoord(2, 4, 79, 23);
	CollectMenu.SetTitle("Current Consumption Charges - Payment");
	CollectMenu.DrawWindow();

	// Show the payment service menu
	MnuChoice = CollectMenu.ShowMenu();

	return MnuChoice;
}
//=======================================================================

//=======================================================================
// Function to display welcome screen
//-------------------------------------------------------------------------
void DisplayWelcome()
{
	int XC, YC;

	DisplayTitle("Welcome to SPARK - Utility Bill Payment System through e-Wallet");
	SetInputWindow();
	SetTextAttr(YELLOW, BLUE, 0);
	clrscr();
	for(int i = 0; i <= 20; i++)
	{
		if(i < 10)
		{
			for(int j = i; j >= 0; j--)
			{
				gotoxy(47 - i - j, i + 1);
				cout << "*" << endl;
			}
		}
		else
		{
			for(int j = 20 - i ; j >= 0; j--)
			{
				gotoxy(46 - i + j, i);
				cout << "*" << endl;
			}
		}
	}

Pause();

}
//=======================================================================
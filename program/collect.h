//=============
// Class Definitions
//=============

//=============
// Class to maintain bank accounts
//=============
class Account
{
	private:
		unsigned int AccountNo;
		char AccountName[25];
		char AccountType;
		float AccountBalance;

	public:


		// Function to set the account details
		void SetValue()
		{
			int XC, YC;

			// Set the Background
			SetInputWindow();

			// Get the current X and Y Coordinates
			XC = wherex();
			YC = wherey();

			do
			{
				// Get the Account No.
				cout << "Enter the Account No.\t\t\t\t: ";
				cin >> AccountNo;

				if(AccountNo < 1000 || AccountNo > 9999)
				{
					DispMessage("Invalid Code. Enter a four digit acount code.");
					ClearLine(XC, YC+3);    // Offset 3 to the Y-coord to include Title Bar
					DispName();

				}
			}while(AccountNo < 1000 || AccountNo > 9999);


			// Get the account holder's name
			cout << "Enter the Account Holder's Name\t\t\t: ";
			cin >> AccountName;

			// Get the account type
			cout << "Enter the Account Type(S-Savigngs, C-Current)\t: ";
			cin >> AccountType;

			// Get the account balance
			cout << "Enter the Account Balance\t\t\t: ";
			cin >> AccountBalance;
		}

		// Function to return the account number
		int GetAccountNo()
		{
			return AccountNo;
		}

		// Function to return the account name
		void GetAccountName(char Name[])
		{
			strcpy(Name, AccountName);
		}

		// Function to return the account type
		char GetAccountType()
		{
			return AccountType;
		}

		// Function to return the account balance
		float GetAccountBalance()
		{
			return AccountBalance;
		}

		// Function to return the account balance
		void SetAccountBalance(float AcctBal)
		{
			AccountBalance = AcctBal;
		}

		// Function to display the account details
		void DisplayRec()
		{
			// Display the tariff details
			cout << setfill(' ') << setiosflags(ios::left) << setw(15) << AccountNo;
			cout << setw(25) << setiosflags(ios::left) << AccountName;
			cout << setw(15) << setiosflags(ios::left) << AccountBalance;
			cout << setw(15) << setiosflags(ios::left) << AccountType << endl;
		}

		// Function to deposit amount
		void Deposit(float Amount)
		{
			AccountBalance += Amount;
		}

		// Function to withdraw amount
		void Withdraw(float Amount)
		{
			AccountBalance = AccountBalance - Amount;
		}
};
//=============

//=============
// Function Prototypes
//=============

// Function to list all the accounts
void ListAccounts(class Account Accounts[], int Count);
// Function to show transaction menu
void ShowTransMenu();
// Function to get transaction amount
void GetTranAmnt(int TranType);

// Function to maintain Bank Accounts
void UpdateAccounts();

// Function to get transaction amount
void GetTranAmnt(int TranType);

// Function to do deposit / withdraw transaction
void DoTransaction(int TranType);

//=============

//=============
// Function to show table maintenance menu
//-------------------------------------------------------------------------
void ShowAcMtMenu()
{
	// Display the transaction menu
	DrawHor(196, YELLOW, BLACK, 0);
	gotoxy(29, wherey());
	cout << "Account Maintenance Menu" << endl;
	DrawHor(196, YELLOW, BLACK, 0);
	cout << "1: Add Accounts" << endl;
	cout << "2: Deposit Amount" << endl;
	cout << "3: Withdraw Amount" << endl;
	cout << "4: View Accounts" << endl;
	cout << "0: Exit" << endl;
	cout << "Enter your choice : ";
}
//=============


//=============
// Function to insert record into Tariff Master table
//=============
void InsertAccntRec()
{
	Account ObjNew, ObjOld;
	unsigned int ACode;
	int SuccessCode = 1;

	// Get the Account Details
	ObjNew.SetValue();

	// Get the newly entered Tariff Code
	ACode = ObjNew.GetAccountNo();

	// Open the file stream for writing
	fstream fio("Account.dat", ios::binary | ios::in | ios::out | ios::app);

	// Check if exists for the entered tariff code
	while(fio.read((char *)&ObjOld, sizeof(ObjOld)))
	{

		if(ObjOld.GetAccountNo() == ACode )
		{
			// Display key constraints and block inserting the record
			DispMessage("Record exists for this code. Press any key to continue.");
			SuccessCode =  0;		// Set the failure code
			break;
		}
	}

	// Display the Success/Failure message
	if(SuccessCode)
	{
		// Place the file pointer at the end of the file
		fio.clear();
		fio.seekg(0, ios::end);

		// Write the record into the file
		fio.write((char *)&ObjNew, sizeof(ObjNew));
		fio.close();
		DispMessage("Record added. Press any key to continue");
	}
	else
		DispMessage("Record not added. Press any key to continue");
}

//=============
// Function to display all records from Accounts table
//=============
void DisplayAccountRec()
{
	Account Obj;
	char Title[] = "Bank Accounts";

	// Open the file stream for reading
	ifstream fin("Account.dat", ios::binary);

	// Display the title
	gotoxy((80 - strlen(Title)) / 2, wherey());
	cout << Title << endl;

	// Display the Header - Column Headings
	DrawHor(196, BLACK, CYAN, 0);
	cout << setfill(' ') << setw(15) << setiosflags(ios::left) << "Account No";
	cout << setw(25) << setiosflags(ios::left) << "Account Holder";
	cout << setw(15) << setiosflags(ios::left) << "Balance";
	cout << setw(15) << setiosflags(ios::left) << "Account Type" << endl;
	cout << setiosflags(ios::right);
	DrawHor(196, BLACK, CYAN, 0);

	// Display the record(s)
	while(fin.read((char *)&Obj, sizeof(Obj)))
	{
		Obj.DisplayRec();
	}
	DrawHor(196, BLACK, CYAN, 0);

	// Close the file stream
}

//=============
// Function to collect bill
//=============
void CollectBill()
{
	Metering MObj;
	Account AObj;

	char Title[] = "Bill Collection";
	unsigned long ConNo;
	unsigned int OpenRead, CloseRead;
	float Tariff, BillAmnt;
	unsigned int AccountNo;
	float AccntBalance;
	char PaidStatus[4];

	// Open the file streams for reading and writing
	fstream fioA("Account.dat", ios::binary | ios::in | ios::out);
	fstream fioM("Metering.dat", ios::binary | ios::in | ios::out);

	// Display the Header - Column Headings
	SetOutputWindow();
	gotoxy((80 - strlen(Title)) / 2, wherey());
	cout << Title << endl;
	DrawHor(196, BLACK, CYAN, 0);
	cout << setfill(' ') << setw(13) << setiosflags(ios::left) << "Ser. Con. No.";
	cout << setw(20) << setiosflags(ios::left) << "Consumer Name";
	cout << setw(10) << setiosflags(ios::left) << "Tariff";
	cout << setw(12) << setiosflags(ios::left) << "Opn. Read";
	cout << setw(12) << setiosflags(ios::left) << "Cls. Read";
	cout << setw(12) << setiosflags(ios::left) << "Paid Status" << endl;
	cout << setiosflags(ios::right);
	DrawHor(196, BLACK, CYAN, 0);

	// Display the record(s)
	while(fioM.read((char *)&MObj, sizeof(MObj)))
	{
		MObj.DisplayRec();
	}
	DrawHor(196, BLACK, CYAN, 0);

	// Place the file pointer at the beginning
	fioM.clear();
	fioM.seekg(0, ios::beg);

	// Get the Consumer No.
	cout << "Enter the Consumer No.    : ";
	cin >> ConNo;
	cout << endl;

	// Get the Account No.
	cout << "Enter the Account No.     : ";
	cin >> AccountNo;

	// Get the Bill amount and Bill Paid Status
	while(fioM.read((char *)&MObj, sizeof(MObj)))
	{

		if(MObj.GetConsumerNo() == ConNo )
		{
			// Get the Bill Amount
			BillAmnt = MObj.GetBillAmount();
			MObj.GetBillStatus(PaidStatus);
			break;
		}
	}

	// Check if the Bill has already been paid
	if(!strcmp(PaidStatus, "Yes"))
	{
		DispMessage("Bill already paid. Press any key to continue.");
		return;
	}

	// Get the available balance in the Account
	while(fioA.read((char *)&AObj, sizeof(AObj)))
	{
		if(AObj.GetAccountNo() == AccountNo )
		{
			// Get the Balance Amount
			AccntBalance = AObj.GetAccountBalance();
			break;
		}
	}

	// Check for enough balance in the account
	if(BillAmnt > AccntBalance)
	{
		DispMessage("Insufficient balance. Press any key to continue.");
		return;
	}
	else
	{
		int pos;
		// Update Account Ledger
		AObj.SetAccountBalance(AccntBalance - BillAmnt);
		pos = -1 * sizeof(AObj);
		fioA.seekp(pos, ios::cur);
		fioA.write((char *)&AObj, sizeof(AObj));
		fioA.close();

		// Update Bill Ledger
		MObj.SetBillStatus("Yes");
		pos = -1 * sizeof(MObj);
		fioM.seekp(pos, ios::cur);
		fioM.write((char *)&MObj, sizeof(MObj));
		fioM.close();
		DispMessage("Bill data updated. Press any key to continue.");
	}
}

//=============
// Function invoke auxiliary number array functions
//-------------------------------------------------------------------------
void BillingService(int Funct)
{
	do
	{
		switch (Funct)
		{
			case 1 :  // Maintain bank accounts using structures
				UpdateAccounts();			  		break;
			case 2 :  // Collect Bill
				CollectBill();			  			break;
			default :
				break;
														break;
		}
		ReRun();
	}while(toupper(getche()) == 'Y');
}

//=============
// Function to maintain bank accounts using structure
//-------------------------------------------------------------------------
void UpdateAccounts()
{

	// Variable declaration
	int i, AccountCount;
	Account Accounts[25];
	int TranType;
	int AccNo;
	float TranAmnt;
	int AccID;
	float AccBal;

	int Action;

	// Display the title
	DisplayTitle("Bill Collection / Account Maintenance Module");

	// Set input window
	SetInputWindow();

	// Display the master table maintenance menu
	do
	{
		DispName();
		SetInputWindow();				// Set input window
		ShowAcMtMenu();
		cin >> Action;

		switch (Action)
		{
			case 1: // Add Record
//				SetInputWindow();		// Set input window
				InsertAccntRec();
				break;
			case 2: // Deposit amount into the wallet
				SetInputWindow();		// Set input window
				DoTransaction(1);		// Deposit amount
				break;
			case 3: // Withdraw amount from the wallet
				SetInputWindow();		// Set input window
				DoTransaction(2);		// Withdraw amount
				break;
			case 4: // View Table
				SetOutputWindow();	// Set output window
				DisplayAccountRec();
				break;
		}
		DoAnother();			// Prompt the user to press Y to do another transaction
	}while(toupper(getche()) == 'Y');
}
//=============

//=============
// Function to get transaction amount
//-------------------------------------------------------------------------
void GetTranAmnt(int TranType)
{
	// Get the transaction amount
	DrawHor(196, YELLOW, BLACK, 0);
	cout << "Transaction Amount" << endl;
	DrawHor(196, YELLOW, BLACK, 0);
	if(TranType == 1)
		cout << "Enter the Deposit Amount   : ";
	else if(TranType == 2)
		cout << "Enter the Withdrawl Amount : ";
}
//=============

//=============
// Function to do deposit / withdraw transaction
//-------------------------------------------------------------------------
void DoTransaction(int TranType)
{
	Account Obj;
	unsigned int AccountNo;
	float TranAmnt;
	float AccntBalance;
	int pos;

	// Open the file stream for reading and writing
	fstream fio("Account.dat", ios::binary | ios::in | ios::out);

	// Get the Account No.
	cout << "Enter the Account No.     : ";
	cin >> AccountNo;

	// Get the available balance in the Account
	while(fio.read((char *)&Obj, sizeof(Obj)))
	{
		if(Obj.GetAccountNo() == AccountNo )
		{
			// Get the Balance Amount
			AccntBalance = Obj.GetAccountBalance();
			break;
		}
	}

	// Get the transaction amount
	GetTranAmnt(TranType);
	cin >> TranAmnt;

	// Allow withdrawal after checking for minimum balance
	if(TranType == 2)
	{
		if( AccntBalance - TranAmnt < 1000)
		{
			// Set input window
			SetInputWindow();
			SetTextAttr(WHITE, RED,  BLINK);
			cout << "Transaction not permitted. Minimum balance < 1000. Enter amount  < " << AccntBalance - 10000 << endl;
			SetTextAttr(WHITE, BLACK, 0);
			return;
		}
	}

	// Update Balance in Account Ledger
	if(TranType == 1)
		AccntBalance += TranAmnt;
	else
		AccntBalance -= TranAmnt;

	Obj.SetAccountBalance(AccntBalance);
	pos = -1 * sizeof(Obj);
	fio.seekp(pos, ios::cur);
	fio.write((char *)&Obj, sizeof(Obj));
	fio.close();

	DispMessage("Account Ledger updated. Press any key to continue.");
}
//=============

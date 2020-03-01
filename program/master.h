//=============
// Function Prototypes
//=============
// Function to prompt the user to whether to repeat for another customer
void DoAnother();

// Function to show transaction menu
void ShowMenu();

// Maintain Tariff Master Table
void TariffMaster();

// Maintain Region Master Table
void RegionMaster();

// Maintain Circle Master Table
void CircleMaster();

// Maintain Division Master Table
void DivisionMaster();

// Maintain Consumer Master Table
void ConsumerMaster();

// Function to display message
void DispMessage(char Msg[]);

// Function to clear current line
void ClearLine(int XC, int YC);

//=============
// Function Declartions
//=============
//=============
// Function invoke auxiliary number array functions
//-------------------------------------------------------------------------
void MasterService(int Funct)
{
	switch (Funct)
	{
		case 1 :  // Maintain tariff master table
			TariffMaster();								break;
		case 2 :  // Maintain region master table
			RegionMaster();								break;
		case 3 :  // Maintain circle master table
			CircleMaster();								break;
		case 4 :  // Maintain division master table
			DivisionMaster();								break;
		case 5 :  // Maintain consumer master table
			ConsumerMaster();								break;
	}
}
//=============

//=============
// Function to prompt the user to whether to repeat for another record
//-------------------------------------------------------------------------
void DoAnother()
{
	DispName();
	gotoxy(1,25);
	cout << "Do you want to add/view another record? [Y/N] : ";
}
//=============

//=============
// Function to display message
//-------------------------------------------------------------------------
void DispMessage(char Msg[])
{
	DispName();
	gotoxy(1,25);
	cout << setfill(' ') << setiosflags(ios::left) << setw(56) << "" << "\r";
	cout << Msg;
	getch();
}
//=============

//=============
// Function to clear current line
//-------------------------------------------------------------------------
void ClearLine(int XC, int YC)
{
	gotoxy(XC, YC);
	SetTextAttr(WHITE, BLACK, 0);
	clreol();
}
//=============



//=============
// Function to show table maintenance menu
//-------------------------------------------------------------------------
void ShowMenu()
{
	// Display the transaction menu
	DrawHor(196, YELLOW, BLACK, 0);
	gotoxy(29, wherey());
	cout << "Table Maintenance Menu" << endl;
	DrawHor(196, YELLOW, BLACK, 0);
	cout << "1: Add Record" << endl;
	cout << "2: View Table" << endl;
	cout << "0: Exit" << endl;
	cout << "Enter your choice : ";
}
//=============

//=============
// 01 - Maintain Tariff Master
//=============
// Class to maintain Tariff Master
//=============
class Tariff
{
	private:
		unsigned int TariffCode;
		float Tariff;
		char TariffName[25];

	public:

		// Function to set the Tariff details
		void SetValue()
		{
			int XC, YC;

			// Set the Background
			SetInputWindow();

			// Get the current X and Y Coordinates
			XC = wherex();
			YC = wherey();

			// Get the Tariff Code
			do
			{
				cout << "Enter the Tariff Code\t\t\t: ";
				cin >> TariffCode;

				if(TariffCode < 10 || TariffCode > 99)
				{
					DispMessage("Invalid Code. Enter a two digit tariff code.");
					ClearLine(XC, YC+3);    // Offset 3 to the Y-coord to include Title Bar
					DispName();
				}
			}while(TariffCode < 10 || TariffCode > 99);

			// Get the Tariff Name
			cout << "Enter the Tariff Name\t\t\t: ";
			cin >> TariffName;

			// Get the Tariff Name
			cout << "Enter the Tariff (Rate)\t\t\t: ";
			cin >> Tariff;

		}

		// Function to display the Tariff Master table
		void DisplayRec()
		{
			// Display the tariff details
			cout << setfill(' ') << setiosflags(ios::left) << setw(15) << TariffCode;
			cout << setw(20) << setiosflags(ios::left) << TariffName;
			cout << setw(10) << setiosflags(ios::left) << Tariff << endl;
		}

		// Function to return the Tariff Code
		int GetTariffCode()
		{
			return TariffCode;
		}

		// Function to return the Tariff
		float GetTariff()
		{
			return Tariff;
		}
		// Function to return the Tariff Name
		void GetTariffName(char TName[])
		{
			strcpy(TName, TariffName);
		}
};
//=============

//=============
// Function to insert record into Tariff Master table
//=============
void InsertTariffRec()
{
	Tariff ObjNew, ObjOld;
	unsigned int TCode;
	int SuccessCode = 1;

	// Get the Tariff record
	ObjNew.SetValue();

	// Get the newly entered Tariff Code
	TCode = ObjNew.GetTariffCode();

	// Open file stream for writing
	fstream fio("Tariff.dat", ios::binary | ios::in | ios::out | ios::app);

	// Check if exists for the entered tariff code
	while(fio.read((char *)&ObjOld, sizeof(ObjOld)))
	{

		if(ObjOld.GetTariffCode() == TCode )
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

//=============
// Function to display all records from Tariff Master table
//=============
void DisplayTariffRec()
{
	Tariff Obj;
	char Title[] = "Tariff List";
	int i = 0;

	// Open the file stream for reading
	ifstream fin("Tariff.dat", ios::binary);

	// Display the title
	gotoxy((80 - strlen(Title)) / 2, wherey());
	cout << Title << endl;

	// Display the Header - Column Headings
	DrawHor(196, BLACK, CYAN, 0);
	cout << setfill(' ') << setw(15) << setiosflags(ios::left) << "Tariff Code";
	cout << setw(20) << setiosflags(ios::left) << "Tariff Name";
	cout << setw(10) << setiosflags(ios::left) << "Rate/Unit" << endl;
	cout << setiosflags(ios::right);
	DrawHor(196, BLACK, CYAN, 0);

	// Display the record(s)
	while(fin.read((char *)&Obj, sizeof(Obj)))
		Obj.DisplayRec();
	DrawHor(196, BLACK, CYAN, 0);

	// Close the file stream
	fin.close();
}

//=============
// Function to maintain Tariff Master Table
//-------------------------------------------------------------------------
void TariffMaster()
{
	// Variable declaration
	Tariff Tariffs;
	int Action;

	// Display the title
	DisplayTitle("Function to maintain Tariff Master");

	// Set input window
	SetInputWindow();

	// Display the master table maintenance menu
	do
	{
		DispName();
		SetInputWindow();				// Set input window
		ShowMenu();
		cin >> Action;

		switch (Action)
		{
			case 1: // Add Record
				InsertTariffRec();
				break;
			case 2: // View Table
				SetOutputWindow();		// Set Output Window
				DisplayTariffRec();
				break;
		}
		DoAnother();			// Prompt the user to press Y to do another transaction
	}while(toupper(getche()) == 'Y');
}
//=============

//=============
// 02 - Maintain Region Master
//=============
// Class to maintain Region Master
//=============
class Region
{
	private:
		unsigned int RegionCode;
		char RegionName[25];

	public:

		// Function to set the Region details
		void SetValue()
		{
			int XC, YC;

			// Set the Background
			SetInputWindow();

			// Get the current X and Y Coordinates
			XC = wherex();
			YC = wherey();

			// Get the Region Code
			do
			{
				cout << "Enter the Region Code\t\t\t: ";
				cin >> RegionCode;

				if(RegionCode < 10 || RegionCode > 99)
				{
					DispMessage("Invalid Code. Enter a two digit region code.");
					ClearLine(XC, YC+3);    // Offset 3 to the Y-coord to include Title Bar
					DispName();
				}
			}while(RegionCode < 10 || RegionCode > 99);

			// Get the Region Name
			cout << "Enter the Region Name\t\t\t: ";
			cin >> RegionName;
		}

		// Function to display the Region Master table
		void DisplayRec()
		{
				cout << setfill(' ') << setiosflags(ios::left) << setw(15) << RegionCode;
				cout << setw(25) << setiosflags(ios::left) << RegionName << endl;
		}

		// Function to return the Region Code
		int GetRegionCode()
		{
			return RegionCode;
		}

		// Function to return the Region Name
		void GetRegionName(char RName[])
		{
			strcpy(RName, RegionName);
		}
};
//=============

//=============
// Function to insert record into Region Master table
//=============
void InsertRegionRec()
{
	Region ObjNew, ObjOld;
	unsigned int RCode;
	int SuccessCode = 1;

	// Get the Region record
	ObjNew.SetValue();

	// Get the newly entered Region Code
	RCode = ObjNew.GetRegionCode();

	// Open file stream for writing
	fstream fio("Region.dat", ios::binary | ios::in | ios::out | ios::app);

	// Check if exists for the entered tariff code
	while(fio.read((char *)&ObjOld, sizeof(ObjOld)))
	{

		if(ObjOld.GetRegionCode() == RCode )
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

//=============
// Function to display all records from Region Master table
//=============
void DisplayRegionRec()
{
	Region Obj;
	char Title[] = "Region List";
	int i = 0;

	// Open the file stream for reading
	ifstream fin("Region.dat", ios::binary);

	// Display the title
	gotoxy((80 - strlen(Title)) / 2, wherey());
	cout << Title << endl;

	// Display the Header - Column Headings
	DrawHor(196, BLACK, CYAN, 0);
	cout << setfill(' ') << setw(15) << setiosflags(ios::left) << "Region Code";
	cout << setw(25) << setiosflags(ios::left) << "Region Name" << endl;
	cout << setiosflags(ios::right);
	DrawHor(196, BLACK, CYAN, 0);

	// Display the record(s)
	while(fin.read((char *)&Obj, sizeof(Obj)))
		Obj.DisplayRec();
	DrawHor(196, BLACK, CYAN, 0);

	// Close the file stream
	fin.close();
}
//=============

//=============
// Function to maintain Region Master
//-------------------------------------------------------------------------
void RegionMaster()
{

	// Variable declaration
	Region Regions;
	int Action;

	// Display the title
	DisplayTitle("Function to maintain Circle Master");

	// Set input window
	SetInputWindow();

	// Display the master table maintenance menu
	do
	{
		DispName();
		SetInputWindow();				// Set input window
		ShowMenu();
		cin >> Action;

		switch (Action)
		{
			case 1: // Add Record
				SetInputWindow();		// Set input window
				InsertRegionRec();
				break;
			case 2: // View Table
				SetOutputWindow();	// Set output window
				DisplayRegionRec();
				break;
		}
		DoAnother();			// Prompt the user to press Y to do another transaction
	}while(toupper(getche()) == 'Y');
}
//=============

//=============
// 03 - Maintain Circle Master
//=============
// Class to maintain Circle Master
//=============
class Circle
{
	private:
		unsigned int RegionCode;
		unsigned int CircleCode;
		char CircleName[25];

	public:

		// Function to set the Circle details
		void SetValue()
		{
			int XC, YC;

			// Get the Region Code
			cout << "Enter the Region Code\t\t\t: ";
			cin >> RegionCode;

			// Get the current X and Y Coordinates
			XC = wherex();
			YC = wherey();

			// Get the Circle Code
			do
			{
				cout << "Enter the Circle Code\t\t\t: ";
				cin >> CircleCode;
				if(CircleCode < 10 || CircleCode > 99)
				{
					DispMessage("Invalid Code. Enter a two digit circle code.");
					ClearLine(XC, YC+3);    // Offset 3 to the Y-coord to include Title Bar
					DispName();
				}
			}while(CircleCode < 10 || CircleCode > 99);

			// Get the Circle Name
			cout << "Enter the Circle Name\t\t\t: ";
			cin >> CircleName;
		}

		// Function to display the Circle Master table
		void DisplayRec()
		{
				cout << setfill(' ') << setiosflags(ios::left) << setw(15) << RegionCode;
				cout << setiosflags(ios::left) << setw(15) << CircleCode;
				cout << setw(25) << setiosflags(ios::left) << CircleName << endl;
		}

		// Function to return the Region Code
		int GetRegionCode()
		{
			return RegionCode;
		}

		// Function to return the Circle Code
		int GetCircleCode()
		{
			return CircleCode;
		}

		// Function to return the Circle Name
		void GetCircleName(char CName[])
		{
			strcpy(CName, CircleName);
		}
};
//=============

//=============
// Function to insert record into Circle Master table
//=============
void InsertCircleRec()
{
	Circle ObjNew, ObjOld;
	unsigned int RCode, CCode;
	int SuccessCode = 1;

	// Set the background and display the Region table
	SetOutputWindow();
	DisplayRegionRec();
	SetTextAttr(WHITE, BLACK, 0);

	// Get the Region record
	ObjNew.SetValue();

	// Get the newly entered Region Code and Circle Code
	RCode = ObjNew.GetRegionCode();
	CCode = ObjNew.GetCircleCode();

	// Open file stream for writing
	fstream fio("Circle.dat", ios::binary | ios::in | ios::out | ios::app);

	// Check if exists for the entered tariff code
	while(fio.read((char *)&ObjOld, sizeof(ObjOld)))
	{

		if(ObjOld.GetRegionCode() == RCode && ObjOld.GetCircleCode() == CCode)
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
// Function to display all records from Circle Master table
//=============
void DisplayCircleRec()
{
	Circle Obj;
	char Title[] = "Circle List";

	// Open the file stream for reading
	ifstream fin("Circle.dat", ios::binary);

	// Display the title
	gotoxy((80 - strlen(Title)) / 2, wherey());
	cout << Title << endl;

	// Display the Header - Column Headings
	DrawHor(196, BLACK, CYAN, 0);
	cout << setfill(' ') << setw(15) << setiosflags(ios::left) << "Region Code";
	cout << setw(15) << setiosflags(ios::left) << "Circle Code";
	cout << setw(25) << setiosflags(ios::left) << "Circle Name" << endl;
	cout << setiosflags(ios::right);
	DrawHor(196, BLACK, CYAN, 0);

	// Display the record(s)
	while(fin.read((char *)&Obj, sizeof(Obj)))
	{
		Obj.DisplayRec();
	}
	DrawHor(196, BLACK, CYAN, 0);

	// Close the file stream
	fin.close();
}

//=============
// Function to maintain Circle Master
//-------------------------------------------------------------------------
void CircleMaster()
{

	// Variable declaration
	Circle Circles;
	int Action;

	// Display the title
	DisplayTitle("Function to maintain Circle Master");

	// Set input window
	SetInputWindow();

	// Display the master table maintenance menu
	do
	{
		DispName();
		SetInputWindow();				// Set input window
		ShowMenu();
		cin >> Action;

		switch (Action)
		{
			case 1: // Add Record
				SetInputWindow();		// Set input window
				InsertCircleRec();
				break;
			case 2: // View Table
				SetOutputWindow();	// Set output window
				DisplayCircleRec();
				break;
		}
		DoAnother();			// Prompt the user to press Y to do another transaction
	}while(toupper(getche()) == 'Y');
}
//=============

//=============
// 04 - Maintain Division Master
//=============
// Class to maintain Division Master
//=============
class Division
{
	private:
		unsigned int RegionCode;
		unsigned int CircleCode;
		unsigned int DivisionCode;
		char DivisionName[25];

	public:

		// Function to set the Division details
		void SetValue()
		{
			int XC, YC;

			// Get the Region Code
			cout << "Select the Region Code\t\t\t: ";
			cin >> RegionCode;

			// Get the Circle Code
			cout << "Select the Circle Code\t\t\t: ";
			cin >> CircleCode;

			// Get the current X and Y Coordinates
			XC = wherex();
			YC = wherey();

			// Get the Division Code
			do
			{
				cout << "Enter the Division Code\t\t\t: ";
				cin >> DivisionCode;

				if(DivisionCode < 10 || DivisionCode > 99)
				{
					DispMessage("Invalid Code. Enter a two digit division code.");
					ClearLine(XC, YC+3);    // Offset 3 to the Y-coord to include Title Bar
					DispName();
				}
			}while(DivisionCode < 10 || DivisionCode > 99);

			// Get the Divsion Name
			cout << "Enter the Division Name\t\t\t: ";
			cin >> DivisionName;
		}

		// Function to display the Divsion Master table
		void DisplayRec()
		{
				cout << setfill(' ') << setiosflags(ios::left) << setw(15) << RegionCode;
				cout << setiosflags(ios::left) << setw(15) << CircleCode;
				cout << setiosflags(ios::left) << setw(15) << DivisionCode;
				cout << setw(25) << setiosflags(ios::left) << DivisionName << endl;
		}

		// Function to return the Region Code
		int GetRegionCode()
		{
			return RegionCode;
		}

		// Function to return the Circle Code
		int GetCircleCode()
		{
			return CircleCode;
		}

		// Function to return the Division Code
		int GetDivisionCode()
		{
			return DivisionCode;
		}
		// Function to return the Divsion Name
		void GetDivisionName(char DName[])
		{
			strcpy(DName, DivisionName);
		}
};
//=============

//=============
// Function to insert record into Division Master table
//=============
void InsertDivisionRec()
{
	Division ObjOld, ObjNew;
	unsigned int RCode, CCode, DCode;
	int SuccessCode = 1;

	// Open the file stream for writing
	ofstream fout("Division.dat", ios::binary | ios::app);

	// Set input window and display the circle table
	SetOutputWindow();
	DisplayCircleRec();
	SetTextAttr(WHITE, BLACK, 0);

	// Get the division record
	ObjNew.SetValue();

	// Get the newly entered Region Code and Circle Code
	RCode = ObjNew.GetRegionCode();
	CCode = ObjNew.GetCircleCode();
	DCode = ObjNew.GetDivisionCode();

	// Open file stream for writing
	fstream fio("Division.dat", ios::binary | ios::in | ios::out | ios::app);

	// Check if exists for the entered tariff code
	while(fio.read((char *)&ObjOld, sizeof(ObjOld)))
	{

		if(ObjOld.GetRegionCode() == RCode && ObjOld.GetCircleCode() == CCode
							  && ObjOld.GetDivisionCode() == DCode)
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
// Function to display all records from Division Master table
//=============
void DisplayDivisionRec()
{
	Division Obj;
	char Title[] = "Division List";

	// Open the file stream for reading
	ifstream fin("Division.dat", ios::binary);

	// Display the title
	gotoxy((80 - strlen(Title)) / 2, wherey());
	cout << Title << endl;

	// Display the Header - Column Headings
	SetOutputWindow();
	DrawHor(196, BLACK, CYAN, 0);
	cout << setfill(' ') << setw(15) << setiosflags(ios::left) << "Region Code";
	cout << setw(15) << setiosflags(ios::left) << "Circle Code";
	cout << setw(15) << setiosflags(ios::left) << "Division Code";
	cout << setw(25) << setiosflags(ios::left) << "Divsion Name" << endl;
	cout << setiosflags(ios::right);
	DrawHor(196, BLACK, CYAN, 0);

	// Display the record(s)
	while(fin.read((char *)&Obj, sizeof(Obj)))
	{
		Obj.DisplayRec();
	}
	DrawHor(196, BLACK, CYAN, 0);

	// Close the file stream
	fin.close();
}

//=============
// Function to maintain Circle Master
//-------------------------------------------------------------------------
void DivisionMaster()
{

	// Variable declaration
	Division Divisions;
	int Action;

	// Display the title
	DisplayTitle("Function to maintain Division Master");

	// Set input window
	SetInputWindow();

	// Display the master table maintenance menu
	do
	{
		DispName();
		SetInputWindow();		// Set input window
		ShowMenu();
		cin >> Action;

		switch (Action)
		{
			case 1: // Add Record
				InsertDivisionRec();
				break;
			case 2: // View Table
				SetOutputWindow();			// Set output window
				DisplayDivisionRec();
				break;
		}
		DoAnother();			// Prompt the user to press Y to do another transaction
	}while(toupper(getche()) == 'Y');
}
//=============

//=============
// 05 - Maintain Consumer Master
//=============
// Class to maintain Consumer Master
//=============
class Consumer
{
	private:
		unsigned int RegionCode;
		unsigned int CircleCode;
		unsigned int DivisionCode;
		unsigned int ConsumerCode;
		unsigned int TariffCode;
		char ConsumerName[25];

	public:

		// Function to set the Division details
		void SetValue()
		{
			int XC, YC;

			// Get the Region Code
			cout << "Region Code\t\t: ";
			cin >> RegionCode;

			// Get the Circle Code
			gotoxy(40, wherey() - 1);
			cout << "Circle Code\t\t: ";
			cin >> CircleCode;

			// Get the Division Code
			cout << "Division Code\t\t: ";
			cin >> DivisionCode;

			// Get the Tariff Code
			gotoxy(40, wherey() - 1);
			cout << "Tariff Code\t\t: ";
			cin >> TariffCode;

			// Get the current X and Y Coordinates
			XC = wherex();
			YC = wherey();

			// Get the Consumer Code
			do
			{
				cout << "Consumer Code\t\t: ";
				cin >> ConsumerCode;
				if(ConsumerCode < 100 || ConsumerCode > 999)
				{
					DispMessage("Invalid Code. Enter a three digit consumer code.");
					ClearLine(XC, YC+3);    // Offset 3 to the Y-coord to include Title Bar
					DispName();
				}
			}while(ConsumerCode < 100 || ConsumerCode > 999);

			// Get the Consumer Name
			gotoxy(40, wherey() - 1);
			cout << "Consumer Name\t\t: ";
			cin >> ConsumerName;
		}

		// Function to display the Consumer Master table
		void DisplayRec()
		{
				cout << setfill(' ') << setiosflags(ios::left) << setw(10) << RegionCode;
				cout << setiosflags(ios::left) << setw(10) << CircleCode;
				cout << setiosflags(ios::left) << setw(10) << DivisionCode;
				cout << setiosflags(ios::left) << setw(10) << ConsumerCode;
				cout << setw(25) << setiosflags(ios::left) << ConsumerName;
				cout << setiosflags(ios::left) << setw(10) << TariffCode << endl;
		}

		// Function to return the Region Code
		int GetRegionCode()
		{
			return RegionCode;
		}

		// Function to return the Circle Code
		int GetCircleCode()
		{
			return CircleCode;
		}

		// Function to return the Division Code
		int GetDivisionCode()
		{
			return DivisionCode;
		}

		// Function to return the Consumer Code
		int GetConsumerCode()
		{
			return ConsumerCode;
		}

		// Function to return the Tariff Code
		int GetTariffCode()
		{
			return TariffCode;
		}

		// Function to return the Consumer Name
		void GetConsumerName(char ConName[])
		{
			strcpy(ConName, ConsumerName);
		}
};
//=============

//=============
// Function to insert record into Consumer Master table
//=============
void InsertConsumerRec()
{
	Consumer ObjNew, ObjOld;
	unsigned int RCode, CCode, DCode, ConCode;
	int SuccessCode = 1;

	// Open the file stream for writing
	ofstream fout("Consumer.dat", ios::binary | ios::app);

	// Set input window and display the division table and tariff table
	DisplayDivisionRec();
	DisplayTariffRec();
	SetTextAttr(WHITE, BLACK, 0);

	// Get the division record
	ObjNew.SetValue();

	// Get the newly entered Region Code and Circle Code
	RCode = ObjNew.GetRegionCode();
	CCode = ObjNew.GetCircleCode();
	DCode = ObjNew.GetDivisionCode();
	ConCode = ObjNew.GetConsumerCode();

	// Open file stream for writing
	fstream fio("Consumer.dat", ios::binary | ios::in | ios::out | ios::app);

	// Check if exists for the entered tariff code
	while(fio.read((char *)&ObjOld, sizeof(ObjOld)))
	{

		if(ObjOld.GetRegionCode() == RCode && ObjOld.GetCircleCode() == CCode
				  && ObjOld.GetDivisionCode() == DCode && ObjOld.GetConsumerCode() == ConCode)
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
// Function to display all records from Consumer Master table
//=============
void DisplayConsumerRec()
{
	Consumer Obj;
	char Title[] = "Consumer List";

	// Open the file stream for reading
	ifstream fin("Consumer.dat", ios::binary);

	// Display the title
	gotoxy((80 - strlen(Title)) / 2, wherey());
	cout << Title << endl;

	// Display the Header - Column Headings
	DrawHor(196, BLACK, CYAN, 0);
	cout << setfill(' ') << setw(10) << setiosflags(ios::left) << "Region";
	cout << setw(10) << setiosflags(ios::left) << "Circle";
	cout << setw(10) << setiosflags(ios::left) << "Division";
	cout << setw(10) << setiosflags(ios::left) << "Consumer";
	cout << setw(25) << setiosflags(ios::left) << "Consumer Name";
	cout << setw(10) << setiosflags(ios::left) << "Tariff Code" << endl;
	cout << setiosflags(ios::right);
	DrawHor(196, BLACK, CYAN, 0);

	// Display the record(s)
	while(fin.read((char *)&Obj, sizeof(Obj)))
	{
		Obj.DisplayRec();
	}
	DrawHor(196, BLACK, CYAN, 0);

	// Close the file stream
	fin.close();
}

//=============
// Function to maintain Circle Master
//-------------------------------------------------------------------------
void ConsumerMaster()
{

	// Variable declaration
	Consumer Consumers;
	int Action;

	// Display the title
	DisplayTitle("Function to maintain Consumer Master");

	// Set input window
	SetInputWindow();

	// Display the master table maintenance menu
	do
	{
		DispName();
		SetInputWindow();					// Set input window
		ShowMenu();
		cin >> Action;

		switch (Action)
		{
			case 1: // Add Record
				InsertConsumerRec();
				break;
			case 2: // View Table
				SetOutputWindow();		// Set output window
				DisplayConsumerRec();
				break;
		}
		DoAnother();			// Prompt the user to press Y to do another transaction
	}while(toupper(getche()) == 'Y');
}
//=============
 
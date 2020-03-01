//=============
// Class to maintain consumer ledger
//=============
class Metering
{
	private:
		unsigned long ConsumerNo;
		unsigned int TariffCode;
		unsigned int OpenRead;
		unsigned int CloseRead;
		float BillAmnt;
		char ConName[25];
		char BillPaidStatus[5];

	public:

		// Function to get Consumer No
		unsigned long GetConsumerNo()
		{
			return ConsumerNo;
		}

		// Function to get Tariff Code
		unsigned int GetTariffCode()
		{
			return TariffCode;
		}

		// Function to get Opening Reading
		unsigned int GetOpenRead()
		{
			return OpenRead;
		}

		// Function to get Closing  Reading
		unsigned int GetCloseRead()
		{
			return CloseRead;
		}

		// Function to get Consumer Name
		void GetConName(char CName[])
		{
			strcpy(CName, ConName);
		}

		// Function to get Bill Paid Status
		void GetBillStatus(char BStatus[])
		{
			strcpy(BStatus, BillPaidStatus);
		}

		// Function to get Bill Amount
		float GetBillAmount()
		{
			return BillAmnt;
		}

		// Function to set Consumer No.
		void SetRetConsumerNo(unsigned long CNo)
		{
			ConsumerNo = CNo;
		}

		// Function to set  Tariff Code
		void SetTariffCode(unsigned int TCode)
		{
			TariffCode = TCode;
		}

		// Function to set Consumer Name
		void SetConName(char CName[])
		{
			strcpy(ConName, CName);
		};

		// Function to set Bill Paid Status
		void SetBillStatus(char BStatus[])
		{
			strcpy(BillPaidStatus, BStatus);
		}

		// Function to set Opening Reading
		void SetOpenRead()
		{
			OpenRead = 0;
		}

		// Function to set Closing Reading
		void SetCloseRead(unsigned int ClRead )
		{
			CloseRead = ClRead;
		}

		// Function to set Bill Amount
		void SetBillAmount(float Billamnt)
		{
			BillAmnt = Billamnt;
		}

		// Function to display the Consumer Master table
		void DisplayRec()
		{
				cout << setfill(' ') << setiosflags(ios::left) << setw(14) << ConsumerNo;
				cout << setw(20) << setiosflags(ios::left) << ConName;
				cout << setw(10) << setiosflags(ios::left) << TariffCode;
				cout << setw(8) << setiosflags(ios::left) << OpenRead;
				cout << setw(8) << setiosflags(ios::left) << CloseRead;
				cout << setw(11) << setiosflags(ios::left) << BillAmnt;
				cout << setw(9) << setiosflags(ios::left) << BillPaidStatus << endl;
		}
};

//=============
// Function to transfer consumer code and update opening readings
//=============
void TransferCon()
{
	Consumer Obj;
	Metering MObj;

	int f = 0;
	long lenfile = 0;
	unsigned long ConNo;
	unsigned int TCode;
	char ConName[20];

	// Open the file streams for reading and writing
	ifstream fin("Consumer.dat", ios::binary | ios::in);
	ofstream fout("Metering.dat", ios::binary | ios::out);


	// Calculate the length of the file
	fin.seekg(0, ios::end);
	lenfile = fin.tellg();

	// Place the file pointer at the beginning of the file
	fin.clear();
	fin.seekg(0, ios::beg);
	char EvntName[20];

	// Set the Consumer record
	while(fin.read((char *)&Obj, sizeof(Obj)))
	{
		ConNo = Obj.GetRegionCode() * 100;
		ConNo += Obj.GetCircleCode();
		ConNo *= 100;
		ConNo += Obj.GetDivisionCode();
		ConNo *= 1000;
		ConNo += Obj.GetConsumerCode();

		Obj.GetConsumerName(ConName);
		TCode = Obj.GetTariffCode();
		MObj.SetRetConsumerNo(ConNo);
		MObj.SetTariffCode(TCode);
		MObj.SetConName(ConName);
		MObj.SetOpenRead();
		MObj.SetCloseRead(0);
		MObj.SetBillAmount(0);
		MObj.SetBillStatus("No");

		fout.write( (char *)&MObj, sizeof(MObj));
		f++;

		if(fin.tellg() == lenfile)
			break;
	}

	// Close the file streams
	fin.close();
	fout.close();

	// Display the success / failure message
	if(f == 0)
		DispMessage("Record not found. Press any key to continue.");
	else
		DispMessage("Metering table constructed. Press any key to continue.");
	return;
}

//=============
// Function to display all records from Metering and Billing table
//=============
void DisplayMeterData()
{
	Metering Obj;
	char Title[] = "Metering Data";

	// Open the file stream for reading
	ifstream fin("Metering.dat", ios::binary);

	// Display the Header - Column Headings
	SetOutputWindow();
	gotoxy((80 - strlen(Title)) / 2, wherey());
	cout << Title << endl;
	DrawHor(196, BLACK, CYAN, 0);
	cout << setfill(' ') << setw(14) << setiosflags(ios::left) << "Ser. Con. No.";
	cout << setw(20) << setiosflags(ios::left) << "Consumer Name";
	cout << setw(10) << setiosflags(ios::left) << "Tariff";
	cout << setw(8) << setiosflags(ios::left) << "Open";
	cout << setw(8) << setiosflags(ios::left) << "Close";
	cout << setw(11) << setiosflags(ios::left) << "Bill Amnt.";
	cout << setw(9) << setiosflags(ios::left) << "Bill Paid" << endl;
	cout << setiosflags(ios::right);
	DrawHor(196, BLACK, CYAN, 0);

	// Display the record(s)
	while(fin.read((char *)&Obj, sizeof(Obj)))
	{
		Obj.DisplayRec();
	}
	DrawHor(196, BLACK, CYAN, 0);

	// Display the prompt to continue
	DispMessage("Press any key to continue.");
}

//=============
// Function to update the closing reading
//=============
void UpdateCloseRead()
{
	Metering MObj;
	Tariff TObj;

	char Title[] = "Metering Data";
	unsigned long ConNo;
	unsigned int OpenRead, CloseRead;
	unsigned int TCode;
	float Tariff, BillAmnt;
	unsigned int Consumption;

	// Open the file streams for reading and writing
	fstream fio("Metering.dat", ios::binary | ios::in | ios::out);
	ifstream fin("Tariff.dat", ios::binary);

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
	cout << setw(12) << setiosflags(ios::left) << "Bill Amnt." << endl;
	cout << setiosflags(ios::right);
	DrawHor(196, BLACK, CYAN, 0);

	// Display the record(s)
	while(fio.read((char *)&MObj, sizeof(MObj)))
	{
		MObj.DisplayRec();
	}
	DrawHor(196, BLACK, CYAN, 0);

	// Place the file pointer at the beginning
	fio.clear();
	fio.seekg(0, ios::beg);

	// Get the Consumer No.
	cout << "Enter the Consumer No.    : ";
	cin >> ConNo;
	cout << endl;

	// Get the Closing Reading
	cout << "Enter the Closing Reading : ";
	cin >> CloseRead;

	// Set the Closing Reading, Bill Amount and Bill Paid Status
	while(fio.read((char *)&MObj, sizeof(MObj)))
	{

		if(MObj.GetConsumerNo() == ConNo )
		{
			// Get the Opening Reading
			OpenRead = MObj.GetOpenRead();

			// Calculate the consumption
			Consumption = CloseRead - OpenRead;


			// Set the closing Reading
			MObj.SetCloseRead(CloseRead);

			// Get the Tariff Code
			TCode = MObj.GetTariffCode();

			while(fin.read((char *)&TObj, sizeof(TObj)))
			{
				if(TObj.GetTariffCode() == TCode)
					Tariff = TObj.GetTariff();
			}

			// Calculate and set the bill amount
			BillAmnt = Consumption * Tariff;
			MObj.SetBillAmount(BillAmnt);

			// Update the record and close the file stream
			int pos = -1 * sizeof(MObj);
			fio.seekp(pos, ios::cur);
			fio.write( (char *)&MObj, sizeof(MObj));
			fio.close();

			break;
		}
	}
	DispMessage("Bill data updated. Press any key to continue.");
}

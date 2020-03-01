//=======================================================================
// Class for the Menu borders
//-----------------------------------------------------------------------------
class Menu
{
	private:
		char Title[75];
		char MenuItem[20][75];
		int BgColor, TxtColor;
		int Left, Top, Right, Bottom;
		int ItemCount, Choice;
		char StrChoice[5];

	public:
		// Set the title
		void SetTitle(char title[]);

		// Set the coordinates
		void SetCoord(int l, int t, int r, int b);

		// Set the colors
		void SetColor(int BgClr, int TxtClr);

		// Draw the window
		void DrawWindow();

		// Set the menu item
		void SetMenuItem(char MnuItem[][75], int Item);

		// Show the menu item
		int ShowMenu();

};
//=======================================================================

//========================================================================
// Set the title
//-----------------------------------------------------------------------------
void Menu::SetTitle(char title[])
{
	strcpy(Title, title);
}
//=======================================================================

//========================================================================
// Set the coordinates
//-----------------------------------------------------------------------------
void Menu::SetCoord(int l, int t, int r, int b)
{
	Left = l;
	Top = t;
	Right = r;
	Bottom = b;
}
//=======================================================================

//=======================================================================
// Set the colors
//-----------------------------------------------------------------------------
void Menu::SetColor(int BgClr, int TxtClr)
{
	BgColor = BgClr;
	TxtColor = TxtClr;
}
//=======================================================================

//=======================================================================
// Draw the border
//-----------------------------------------------------------------------------
void Menu::DrawWindow()
{
	// Set the title as Main Menu
	DisplayTitle(Title);

	// Set the menu window with black background
	gotoxy(1,4);
	SetTextAttr(TxtColor, BgColor, 0);
}
//=======================================================================

//=======================================================================
// Set the menu items
//-----------------------------------------------------------------------------
void Menu::SetMenuItem(char MnuItem[][75], int Item)
{
	// Set the menu items
	for(int i = 0; i < Item; i++)
		strcpy(MenuItem[i], MnuItem[i]);

	// Set the menu item count
	ItemCount = Item;
}
//=======================================================================

//=======================================================================
// Show the menu items
//-----------------------------------------------------------------------------
int Menu::ShowMenu()
{
	// List the main menu items in the main menu window
	for(int i = 0; i < ItemCount; i++)
	{
		gotoxy(2, 4+i);
		cout << MenuItem[i];
	}

	do
	{
		// Set the choice input window
		window(1,23, 30, 23);
		SetTextAttr(TxtColor, BgColor, 0);

		// Get the user choice
	     //	gotoxy(2, 1);
		cout << "Enter your choice : ";
		cin >> StrChoice;
	       //	gotoxy(22, 1);

		Choice  = atoi(StrChoice);

		// Clear the error window
		window(65, 23, 80,23);
		SetTextAttr(WHITE, BgColor, 0);

		// Validate the chosen choice
		if((Choice > 0 && Choice < ItemCount) || (Choice == 0))
		{
			// Restore the window to default coordinates
			window(1, 1, 80, 25);

			// Return the menu choice
			return Choice;
		}
		else
		{
			// Set the text attributes
			SetTextAttr(WHITE, RED, BLINK);

			// Display the error message
			cout << "Invalid Choice!";
		}
	}while(!(((Choice > 0 && Choice < ItemCount) || (Choice == 999))));
}
//======================================================================

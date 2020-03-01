//=======================================================================
// Function Prototypes
//=======================================================================
void ClearScreen();
void SetTextAttr(int TxtColor, int BgColor, int Blink);
void DrawHor();
void DrawHor(int LineChar, int TxtColor, int BgColor, int Blink);
void DispName();
void DisplayTitle(char Title[]);
void Pause();
void ReRun();
void SetInputWindow();
void SetOutputWindow();

//=======================================================================
// Function Declarations
//=======================================================================

//=======================================================================
// Function to clear the rest of the screen from the current position
//-------------------------------------------------------------------------
void ClearScreen()
{
	int YC = wherey();
	int XC = wherex();
	int WinBottom;
	int WinTop;
	struct text_info TextInfo;

	// Clear the current line from the cursor position
	clreol();

	// Get the current window information
	gettextinfo(&TextInfo);

	// Set the window top and bottom
	WinBottom = TextInfo.winbottom > 23 ? 23 : TextInfo.winbottom;
	WinTop = TextInfo.wintop >= YC ? TextInfo.wintop : YC;

	// Clear the current window
	for(int y = WinTop + 1; y <= WinBottom; y++)
	{
		gotoxy(1, y);
		clreol();
	}
	gotoxy(XC, YC);
}
//=======================================================================

//=======================================================================
// Function to set the text color and background color
//-------------------------------------------------------------------------
void SetTextAttr(int TxtColor, int BgColor, int Blink)
{
	textattr(TxtColor + (BgColor << 4) + Blink);
	ClearScreen();
}
//=======================================================================

//========================================================================
// Function to print a horiztontal ruler (double line)
//-------------------------------------------------------------------------
void DrawHor()
{
	SetTextAttr(YELLOW, BLUE, 0);
	cout << setw(80) << setfill(char(205)) << "";
	SetTextAttr(WHITE, BLACK, 0);
}
//=======================================================================

//=======================================================================
// Function to print a horiztontal line
//-------------------------------------------------------------------------
void DrawHor(int LineChar, int TxtColor, int BgColor, int Blink)
{
	textattr(TxtColor + (BgColor << 4) + Blink);
	clreol();
	cout << setw(80) << setfill(char(LineChar)) << "";
}
//=======================================================================

//=======================================================================
// Function to display the name
//-------------------------------------------------------------------------
void DispName()
{
	int YC = wherey();
	int XC = wherex();

	// Set the task window
	window(1, 24, 80, 25);

	// Draw the horizontal bar
	DrawHor();

	// Display the project name
	SetTextAttr(BLACK, LIGHTGRAY, 0);
	cout << " Guided by: Nazreen Banu Ma'am ";
	gotoxy(57,2);
	cout << char(186);

	// Display the student name
	SetTextAttr(WHITE, BROWN,  BLINK);
	cout << " Vikas Mahendar & Team";

	// Restore the window with the default coordinates
	textmode(LASTMODE);

	// Set the cursor to the previous position
	gotoxy(XC, YC);
}
//=======================================================================

//=======================================================================
// Function to display the title
//-------------------------------------------------------------------------
void DisplayTitle(char Title[])
{
	// Set the title window
	window(1, 1, 80, 3);

	// Draw the top border
	DrawHor();

	// Display title
	SetTextAttr(WHITE, BROWN, 0);

	// Calculate the x-coordinate and display the title
	int Pos = (80 - strlen(Title)) / 2;
	gotoxy(Pos, 2);
	cout << Title << endl;

	// Draw the title underline
	DrawHor();

	// Display the status bar displaying name of the programmer
	DispName();
}
//=======================================================================

//=======================================================================
// Function to prompt the user to press Enter key to continue
//-------------------------------------------------------------------------
void Pause()
{
	// Set the window coordinates
	window(1, 25, 80, 25);
	cout << setw(56) << setfill(' ') << "" << "\r";
	cout << "Press Enter to continue...";
	while(getch() != '\r') {}
}
//=======================================================================

//=======================================================================
// Function to prompt the user to whether to repeat program or not
//-------------------------------------------------------------------------
void ReRun()
{
	// Set the window with default coordinates
	window(1, 25, 56, 25);
	cout << setw(56) << setfill(' ') << " " << "\r";
	cout << "Do you want to run the function again? [Y/N] : ";
}
//=======================================================================

//=======================================================================
// Function to draw input window
//-------------------------------------------------------------------------
void SetInputWindow()
{
	window(1, 4, 80, 23);
	SetTextAttr(WHITE, BLACK, 0);
	clrscr();
}
//=======================================================================

//=======================================================================
// Function to draw output window
//-------------------------------------------------------------------------
void SetOutputWindow()
{
	window(1, 4, 80, 23);
	SetTextAttr(BLACK, CYAN, 0);
	clrscr();
}
//=======================================================================

#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cwchar>
using namespace std;

class Book;
class Librarian;
class Date;
class User;
class Helper;

class Helper
{
public:
	static int StringLength(char* str)
	{
		int stringLength = 0;
		for (char* temp = str; *temp != '\0'; temp++)
			stringLength++;

		return stringLength;
	}

	static char* GetStringFromBuffer(char* str)
	{
		int Length = Helper::StringLength(str);
		Length++;
		char* String = new char[Length];
		int i;
		for (i = 0; str[i] != '\0'; i++)
		{
			String[i] = str[i];
		}
		String[i] = '\0';
		return String;
	}

	static char* Concatenate(char* str1, char* str2)
	{
		int Length1 = StringLength(str1);
		int Length2 = StringLength(str2);

		int Length = Length1 + Length2;
		Length += 2; //For space between words and null character at the end
		char* String = new char[Length];

		int i, j;
		for (i = 0; str1[i] != '\0'; i++)
		{
			String[i] = str1[i];
		}
		String[i++] = ' ';
		for (j = 0; str2[j] != '\0'; j++)
		{
			String[i++] = str2[j];
		}

		String[i] = '\0';
		return String;
	}
	
};


class Date
{
private:
	int Day;
	int Month;
	int Year;
public:
	Date(int day = 0, int month = 0, int year = 0)
	{
		Day = day;
		Month = month;
		Year = year;
	}

	void SetDate(int day = 0, int month = 0, int year = 0)
	{
		Day = day;
		Month = month;
		Year = year;
	}

	void PrintDate()
	{
		cout << Day << "/" << Month << "/" << Year << endl;
	}
};


class Book
{
private:
	int SerialNumber;
	char* NameOfAuthor;
	char* TypeOfBook;
	char* NameOfBook;
	int IssuedByUser;
	bool Status; // True means book is issued and vice varsa
public:
	Book()
	{
		SerialNumber = 0;
		IssuedByUser = 0;
		NameOfAuthor = NULL;
		TypeOfBook = NULL;
		NameOfBook = NULL;
		Status = false;
	}

	int GetSerialNumber()
	{
		return SerialNumber;
	}

	void SetSerialNumber(int serialNumber)
	{
		SerialNumber = serialNumber;
	}

	void SetNameOfAuthor() //Set new name of author provided by librarian
	{
		if (NameOfAuthor)
			delete[] NameOfAuthor;
		char tempBuffer[50];
		cout << "Enter First and Last name of Author: ";
		cin.getline(tempBuffer, 50);
		NameOfAuthor = Helper::GetStringFromBuffer(tempBuffer);
	}

	void SetTypeOfBook() //Set type of book provided by librarian
	{
		if (TypeOfBook)
			delete[] TypeOfBook;
		char tempBuffer[30];
		cout << "Enter type of the book(e.g. Political): ";
		cin >> tempBuffer;
		TypeOfBook = Helper::GetStringFromBuffer(tempBuffer);
	}

	void SetNameOfBook() //Set name of book provided by librarian
	{
		if (NameOfBook)
			delete[] NameOfBook;
		char tempBuffer[80];
		cout << "Enter full name of the book: ";
		cin.getline(tempBuffer, 80);
		NameOfBook = Helper::GetStringFromBuffer(tempBuffer);
	}

	void LoadBookFromFile(ifstream& Input) //Loads each books data
	{
		Input >> SerialNumber;

		char temp_FName[15];
		Input >> temp_FName;
		char temp_LName[15];
		Input >> temp_LName;

		NameOfAuthor = Helper::Concatenate(temp_FName, temp_LName);

		char temp_Buffer[60];
		Input >> temp_Buffer;
		TypeOfBook = Helper::GetStringFromBuffer(temp_Buffer);

		Input.ignore();
		Input.getline(temp_Buffer, 60);
		NameOfBook = Helper::GetStringFromBuffer(temp_Buffer);
	}

	void SaveBookToFile(ofstream& Output) //To save book information in a file
	{
		Output << SerialNumber << "\t" << NameOfAuthor << "\t" << TypeOfBook << "\t" << NameOfBook;
	}

	void CopyDataBetweenArrays(Book*& BookData) //To place data in variables of new array
	{
		SerialNumber = BookData->SerialNumber;
		NameOfAuthor = Helper::GetStringFromBuffer(BookData->NameOfAuthor);
		TypeOfBook = Helper::GetStringFromBuffer(BookData->TypeOfBook);
		NameOfBook = Helper::GetStringFromBuffer(BookData->NameOfBook);
		Status = BookData->Status;
	}

	void SetStatus(bool UpdateStatus) //Updates the status of the book
	{
		Status = UpdateStatus;
	}

	void NewBook(int serialNumber) //A new book is added to the list
	{
		SerialNumber = serialNumber;

		char temp_Buffer[60];
		cout << "Enter the name of the Author: ";
		cin.getline(temp_Buffer, 60);
		NameOfAuthor = Helper::GetStringFromBuffer(temp_Buffer);

		cout << "Enter type of book: ";
		cin.getline(temp_Buffer, 60);
		TypeOfBook = Helper::GetStringFromBuffer(temp_Buffer);

		cout << "Enter name of the book: ";
		cin.getline(temp_Buffer, 60);
		NameOfBook = Helper::GetStringFromBuffer(temp_Buffer);
	}

	void PrintBook() //To print book on console
	{
		cout << SerialNumber << "\t" << NameOfAuthor << "\t\t" << TypeOfBook << "\t" << NameOfBook;
	}

	void PrintBookInformation() //To print information regarding book on users demand
	{
		cout << "\n\nBook Information:\n";
		cout << "Serial Number: " << SerialNumber << endl;
		cout << "Name of the Author: " << NameOfAuthor << endl;
		cout << "Type of the Book: " << TypeOfBook << endl;
		cout << "Name of the Book: " << NameOfBook << endl;
		cout << "Status of the Book: ";
		if (Status)
			cout << "This book is issued by someone" << endl << endl;
		else
			cout << "This book is not issued to anyone" << endl << endl;
	}

	bool GetStatus()
	{
		return Status;
	}

	~Book() //To deallocate memory on heap
	{
		if (NameOfAuthor)
			delete[] NameOfAuthor;
		if (TypeOfBook != 0)
			delete[] TypeOfBook;
		if (NameOfBook)
			delete[] NameOfBook;
	}
};


class User
{
private:
	char* userName;  //Login
	char* Password;	 //Login

	char* Name;
	Book* book; //Connection with a book
	int TotalIssued;
	int IssuedBookSerialNumber;
	Date Issue_Date;
	Date Return_Date;

public:
	User()
	{
		userName = 0;
		Password = 0;
		book = 0;
		Name = 0;
		TotalIssued = 0;
		IssuedBookSerialNumber = 0;
	}

	void SetName(char* name)
	{
		Name = name;
	}

	void SetPassword(char* pass)
	{
		Password = pass;
	}

	void CopyDataBetweenArrays(User*& obj)
	{
		Name = Helper::GetStringFromBuffer(obj->Name);
		Password = Helper::GetStringFromBuffer(obj->Password);
		userName = Helper::GetStringFromBuffer(obj->userName);
	}

	void SetUsername(char* username)
	{
		userName = username;
	}

	void SaveUserToFile(ofstream& Output) //To save book information in a file
	{
		Output << userName << "\t" << Password << "\t" << Name;
	}

	void ReadUserFromFile(ifstream& fin) //Reads user data from file
	{
		char tempBuffer[50];
		char tempBuffer2[30];
		fin >> tempBuffer;
		userName = Helper::GetStringFromBuffer(tempBuffer);

		fin >> tempBuffer;
		Password = Helper::GetStringFromBuffer(tempBuffer);

		fin >> tempBuffer;
		fin >> tempBuffer2;
		Name = Helper::Concatenate(tempBuffer, tempBuffer2);

	}

	void Book_Return(); //To return an issued book

	void Request_For_Issue(); //To issue a book

	void Request_For_Information(); //To acquire information about book

	bool Sign_Up(Librarian& LibObject, User* &userObj); // A new user is added into the list

	bool Login(Librarian& LibObject, User* &userObj); //Checks for correct Roll Number and Password

	~User()
	{
		if (userName)
			delete[] userName;
		if (Name)
			delete[] Name;
		if (Password)
			delete[] Password;
	}

};


class Librarian
{
private:
	char* ID_Number;        //For Login
	char* Password;		  //For Login

	static int TotalBooks;
	static int AvailableBooks;    //Count of books Not issued
	static Book** BooksList;

	User** Members;
	int TotalMembers;

public:
	Librarian()
	{
		TotalBooks = 0;
		TotalMembers = 0;
		BooksList = 0;
		Members = 0;
		AvailableBooks = 0;
	}

	void Add_Book() //To add a new book into the list
	{
		int NewBooks;
		cout << "\n\nHow many books would you like to add: ";
		cin >> NewBooks;
		int PreviousBookCount = TotalBooks;
		TotalBooks += NewBooks;
		Book** tempBooksList = new Book * [TotalBooks];

		int i;
		for (i = 0; i < PreviousBookCount; i++)
		{
			tempBooksList[i] = new Book;
			tempBooksList[i]->CopyDataBetweenArrays(BooksList[i]);
		}


		for (int j = 0; j < PreviousBookCount; j++) //Deallocating Old List
			delete BooksList[j];

		cout << endl << endl;
		cin.ignore(); //To ignore '\n' character
		for (int k = i + 1; k <= TotalBooks; k++)
		{
			tempBooksList[i] = new Book;
			tempBooksList[i]->NewBook(k);
			i++;
			cout << endl << endl;
		}
		cout << "\n\nBook(s) successfully added\n\n";
		BooksList = tempBooksList;
		tempBooksList = 0;
	}

	void Add_User(char* username, char* completeName, char* password, User* &userObj)
	{
		User** tempUsersList = new User * [TotalMembers+1];

		int i;
		for (i = 0; i < TotalMembers; i++)
		{
			tempUsersList[i] = new User;
			tempUsersList[i]->CopyDataBetweenArrays(Members[i]);
		}

		for (int j = 0; j < TotalMembers; j++) //Deallocating Old List
		{
			delete Members[j];
		}

		cout << endl;
		cin.ignore(); //To ignore '\n' character

		tempUsersList[TotalMembers] = new User;
		tempUsersList[TotalMembers]->SetName(completeName);
		tempUsersList[TotalMembers]->SetUsername(username);
		tempUsersList[TotalMembers]->SetPassword(password);

		userObj = tempUsersList[TotalMembers];

		cout << "Member successfully added\n\n";
		Members = tempUsersList;
		tempUsersList = 0;
		TotalMembers++;
	}

	void Remove_Book() //Removes a book from the list
	{
		int serialNumber;
		cout << "\n\nEnter the Serial Number of the book you want to remove: ";
		cin >> serialNumber;

		int PreviousBookCount = TotalBooks;
		TotalBooks--;
		Book** tempBooksList = new Book * [TotalBooks];

		for (int i = 0, j = 0; i < PreviousBookCount; i++) // i for traversing old booklist, j for traversing new booklist
		{
			if (serialNumber == BooksList[i]->GetSerialNumber())
				continue;

			tempBooksList[j] = new Book;
			tempBooksList[j]->CopyDataBetweenArrays(BooksList[i]);
			j++;
		}

		for (int j = 0; j < PreviousBookCount; j++) //Deallocating Old List
			delete BooksList[j];

		cout << "\n\nBook successfully removed\n\n";
		BooksList = 0;
		BooksList = tempBooksList;

		for (int j = 1, i = 0; i < TotalBooks; j++, i++)
		{
			BooksList[i]->SetSerialNumber(j);
		}
	}

	void Edit_Book() //To edit information regarding book
	{
		int serialNumber;
		cout << "\n\nWhich book would you like to edit, enter Serial Number: ";
		cin >> serialNumber;

		int i;
		for (i = 0; i < TotalBooks; i++)
		{
			if (serialNumber == BooksList[i]->GetSerialNumber())
				break;
		}

		cout << "\n\nWhat would you like to edit" << endl;
		int option;
		cout << "1. Name of Author \n2. Type of Book \n3. Name of Book \nEnter Number corresponding to your desired option: ";
		cin >> option;
		cin.ignore();
		switch (option)
		{
		case 1:
			BooksList[i]->SetNameOfAuthor();
			break;
		case 2:
			BooksList[i]->SetTypeOfBook();
			break;
		case 3:
			BooksList[i]->SetNameOfBook();
			break;
		default:
			cout << "Entered option is not valid" << endl;
			break;
		}

	}

	static bool Grant_Permission(int serialNumber) //If requested book is not issued to anyone, permission is granted
	{
		for (int i = 0; i < TotalBooks; i++)
		{
			if (serialNumber == BooksList[i]->GetSerialNumber())
			{
				if (!BooksList[i]->GetStatus())
				{
					cout << "Permission Granted" << endl;
					return true;
				}
				else
				{
					cout << "The Book has already been issued to some student" << endl;
					return false;
				}
			}
		}
	}

	static Book* Issue_Book(int serialNumber) //Issues a book to a member
	{
		int i;
		for (i = 0; i < TotalBooks; i++)
		{
			if (serialNumber == BooksList[i]->GetSerialNumber())
				break;
		}
		bool UpdateStatus = true;
		BooksList[i]->SetStatus(UpdateStatus);

		AvailableBooks--;
		return BooksList[i];
	}

	static bool Returned_Book(int serialNumber, Book* book) //when a member return a book, he is no more associated with that book
	{
		if (serialNumber == book->GetSerialNumber())
		{
			bool UpdateStatus = false;
			book->SetStatus(UpdateStatus);
			AvailableBooks++;
			cout << "Book returned successfully" << endl;
			return true;
		}
		else
		{
			cout << "This book was not issued to you" << endl;
			return false;
		}

	}

	void PrintAllBooks() //To print all books on console
	{
		cout << "Books currently available in the library are: " << endl << endl;
		for (int i = 0; i < TotalBooks; i++)
		{
			BooksList[i]->PrintBook();
			cout << endl;
		}
		cout << endl << endl;
	}

	bool LoadBooks() //To load all books from file
	{
		ifstream Input("Books.txt");

		if (!Input.is_open())
		{
			cout << "Error! File could not be opened" << endl;
			return false;
		}

		Input >> TotalBooks;
		AvailableBooks = TotalBooks;
		BooksList = new Book * [TotalBooks];

		for (int i = 0; i < TotalBooks; i++)
		{
			BooksList[i] = new Book;
			BooksList[i]->LoadBookFromFile(Input);
		}

		cout << "Books Loaded Successfully" << endl;

		Input.close();
		return true;
	}

	bool LoadUsers() //To load all users from file
	{
		ifstream fin("Users.txt");

		if (fin.is_open())
		{
			fin >> TotalMembers;
			Members = new User * [TotalMembers];
			for (int i = 0; i < TotalMembers; i++)
			{
				Members[i] = new User;
				Members[i]->ReadUserFromFile(fin);
			}
			cout << "Users Loaded Successfully" << endl;
		}
		else
		{
			cout << "Error!  Users file could not be opened" << endl;
			return false;
		}
		return true;
	}

	User** GetUsers()
	{
		return Members;
	}

	int GetTotalUsers()
	{
		return TotalMembers;
	}

	void SaveUsers()
	{
		ofstream Output("Users.txt");

		Output << TotalMembers;
		Output << endl;
		for (int i = 0; i < TotalMembers; i++)
		{
			Members[i]->SaveUserToFile(Output);
			if (i != TotalMembers - 1) //To avoid next line command for the last book
				Output << endl;
		}

		Output.close();
	}

	void Save_File() //To save modified list back into the file
	{
		ofstream Output("Books.txt");

		Output << TotalBooks;
		Output << endl;
		for (int i = 0; i < TotalBooks; i++)
		{
			BooksList[i]->SaveBookToFile(Output);
			if (i != TotalBooks - 1) //To avoid next line command for the last book
				Output << endl;
		}

		Output.close();
	}

	bool Login() //Log in for librarian
	{
		ifstream loginFile("Librarian.txt");

		if (!loginFile.is_open())
		{
			cout << "Error!   Users File could not be opened\n";
			return false;
		}

		bool tryAgain = true;
		int again, counter = 0;
		char tempFileID[6];
		char tempFilePass[20];
		char tempID[9];
		char tempPass[20];
		char passwordCharacter;
		string tempUserPassword;


		loginFile >> tempFileID >> tempFilePass;

		ID_Number = Helper::GetStringFromBuffer(tempFileID);
		Password = Helper::GetStringFromBuffer(tempFilePass);

		do
		{
			again = 1;
			cout << "\nEnter Employee number: ";
			cin >> tempID;

			cout << "Enter Password: ";
			do
			{
				passwordCharacter = _getch();
				if (passwordCharacter != 13)
				{
					tempPass[counter++] = passwordCharacter;
					cout << '*';
				}
			} while (passwordCharacter != 13);

			tempPass[counter] = '\0';

			if ((strcmp(tempID, ID_Number) == 0) && (strcmp(tempPass, Password) == 0))
			{
				cout << "\nLogin Successfull!!\n";
				tryAgain = false;
				return true;
			}
			cout << "\nIncorrect Username or Password. 1. Try Again\t2. Exit\n\n";
			cin >> again;
			tryAgain = true;
		} while (tryAgain == true && again == 1);


		return false;
	}

	static void Information_Regarding_Book(int serialNumber) //Privides information regarding book when a member requests
	{
		for (int i = 0; i < TotalBooks; i++)
		{
			if (serialNumber == BooksList[i]->GetSerialNumber())
			{
				BooksList[i]->PrintBookInformation();
				break;
			}
		}
	}

	~Librarian()
	{
		for (int i = 0; i < TotalBooks; i++)
		{
			if (BooksList[i])
				delete BooksList[i];
		}
		if (BooksList)
			delete[] BooksList;

		for (int i = 0; i < TotalMembers; i++)
		{
			if (Members[i])
				delete Members[i];
		}
		if (Members)
			delete[] Members;
	}
};


bool User::Sign_Up(Librarian& LibObject, User* &userObj) // A new user is added into the list
{
	char tempName[9];
	char tempPass[20];
	char tempCompleteName[50];
	char passwordCharacter = '0';
	char duplicatePassword[20];
	bool passwordsMatch = true;
	bool userNameCorrectFormat = true;
	int tryAgain;
	int lengthOfName, counter = 0;

	cout << "Enter you Complete Name: ";
	cin.getline(tempCompleteName, 50, '\n');

	do
	{
		tryAgain = 1;
		cout << "Enter your userName (e.g 20L-1234): ";
		cin >> tempName;
		userNameCorrectFormat = true;

		lengthOfName = strlen(tempName);
		if (lengthOfName != 8)
		{
			userNameCorrectFormat = false;
		}


		if ((int(tempName[0]) < 48) || (int(tempName[0] > 57)))
		{
			userNameCorrectFormat = false;
		}

		if ((int(tempName[1]) < 48) || (int(tempName[1] > 57)))
		{
			userNameCorrectFormat = false;
		}

		if ((int(tempName[2]) < 65) || (int(tempName[3] > 90)))
		{
			userNameCorrectFormat = false;
		}

		if (tempName[3] != '-')
		{
			userNameCorrectFormat = false;
		}

		for (int i = 4; i < lengthOfName; i++)
		{
			if ((int(tempName[i]) < 48) || (int(tempName[i] > 57)))
			{
				userNameCorrectFormat = false;
			}

		}

		if (userNameCorrectFormat == false)
		{
			cout << "\n\nUsername Incorrect Format. Please follow the correct naming scheme e.g. 20L-1361\n\n";
		}
	} while (userNameCorrectFormat == false);


	do
	{
		cout << "Enter Password: ";
		do
		{
			passwordCharacter = _getch();

			if (passwordCharacter != 13)
			{
				tempPass[counter++] = passwordCharacter;
				cout << '*';
			}
		} while (passwordCharacter != 13);

		passwordCharacter = '0';
		cout << strlen(tempPass) << endl;
		tempPass[counter] = '\0';
		counter = 0;

		cout << "\nEnter Password AGAIN: ";
		do
		{
			passwordCharacter = _getch();

			if (passwordCharacter != 13)
			{
				duplicatePassword[counter++] = passwordCharacter;
				cout << '*';
			}
		} while (passwordCharacter != 13);
		duplicatePassword[counter] = '\0';

		if ((strcmp(tempPass, duplicatePassword)) == 0)
		{
			cout << "\nUser account successfully created! You can start using the account to access the library.\n\n";
			passwordsMatch = true;
			char* userName = Helper::GetStringFromBuffer(tempName);
			char* Password = Helper::GetStringFromBuffer(duplicatePassword);
			char* Name = Helper::GetStringFromBuffer(tempCompleteName);
			LibObject.Add_User(userName, Name, Password, userObj);
			return true;
		}
		else
		{
			cout << "\nPasswords didn't match. User account could not be created!\n\n";
			cout << "Would you like to try again?1. Yes 2. No\n";
			cin >> tryAgain;
			passwordsMatch = false;
		}
	} while (passwordsMatch == false && tryAgain == 1);

	return false;
}


void User::Book_Return()
{
	if (book == 0)
	{
		cout << "\n\nYou don't have any issued book\n\n";
		return;
	}
	cout << "\n\nEnter the serial Number of the book you want to return: ";
	int serialNumber;
	cin >> serialNumber;
	if (Librarian::Returned_Book(serialNumber, book))
	{
		Issue_Date.SetDate(); //Sets issue date to 0/0/0
		Return_Date.SetDate(); //Sets return date to 0/0/0
		book = 0;
	}

}


bool User::Login(Librarian& LibObject, User* &userObj)
{
	bool tryAgain = true;
	int again;
	int counter = 0;
	char tempUserName[9];
	char tempPass[20];
	char passwordCharacter;

	User** Members = LibObject.GetUsers();
	int TotalUsers = LibObject.GetTotalUsers();
	
	do
	{
		again = 1;
		cout << "\nEnter Username: ";
		cin >> tempUserName;

		cout << "Enter Password: ";
		do
		{
			passwordCharacter = _getch();
			if (passwordCharacter != 13)
			{
				tempPass[counter++] = passwordCharacter;
				cout << '*';
			}
		} while (passwordCharacter != 13);
		tempPass[counter] = '\0';

		for (int i = 0; i < TotalUsers; i++)
		{
			if ((strcmp(tempUserName, Members[i]->userName) == 0) && (strcmp(tempPass, Members[i]->Password) == 0))
			{
				cout << "\nLogin Successfull!!\n";
				userObj = Members[i];
				tryAgain = false;
				return true;
			}
		}
		cout << "\nIncorrect Username or Password. 1. Try Again\t2. Exit\n\n";
		cin >> again;
		tryAgain = true;
	} while (tryAgain == true && again == 1);


	return false;
}


void User::Request_For_Issue()
{
	if (book)
	{
		cout << "\n\nYou have already issued a book, cannot issue more\n\n";
		return;
	}
	cout << "\n\nEnter the serial Number of the book you want to issue: ";
	int serialNumber;
	cin >> serialNumber;
	bool permission = Librarian::Grant_Permission(serialNumber);

	if (permission)
	{
		book = Librarian::Issue_Book(serialNumber); //Associates user with book
		int day, month, year;
		cout << "Enter date of issue (e.g. day month year): ";
		cin >> day;
		cin >> month;
		cin >> year;
		Issue_Date.SetDate(day, month, year);

		cout << "Enter date of return (e.g. day month year): ";
		cin >> day;
		cin >> month;
		cin >> year;
		Return_Date.SetDate(day, month, year);
		cout << "\n\nBook issued successfully" << endl;
	}
	else
		return;
}


void User::Request_For_Information()
{
	cout << "\n\nEnter the serial number of the book you want to acquire information about: ";
	int serialNumber;
	cin >> serialNumber;
	Librarian::Information_Regarding_Book(serialNumber);

	if (book)
	{
		if (serialNumber == book->GetSerialNumber())
		{
			cout << "Issue date of your book is: ";
			Issue_Date.PrintDate();
			cout << "Return date of your book is: ";
			Return_Date.PrintDate();

			cout << endl << endl;
		}
	}

}


Book** Librarian::BooksList = NULL;
int Librarian::AvailableBooks = NULL;
int Librarian::TotalBooks = NULL;

void main()
{
	SetConsoleTitle(L"Library Management System");
	system("Color 60");
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 20;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	bool books = true, users = true, userLogin, librarianLogin;

	Librarian libObj;
	books = libObj.LoadBooks();
	users = libObj.LoadUsers();

	if (books == false)
	{
		cout << "\nBooks loading failed, the program can't procede until the files are properly loaded.\n";
		Sleep(5000);
		return;
	}

	if (users == false)
	{
		cout << "\nUsers loading failed, the program can't procede until the files are properly loaded.\n";
		Sleep(5000);
		return;
	}

	Label:
	char choice;
	cout << "\n\nChoose your designation:" << endl;
	cout << "\t\t\t\t1. Librarian\t\t2. User\t\t3. Quit\n\n";
	choice = _getch();

	if (choice == '1')
	{
		bool permit = libObj.Login();
		if (permit)
		{
			char libChoice = 0;
			do
			{
				cout << endl << endl;
				libObj.PrintAllBooks();
				cout << "What would like to perform" << endl;
				cout << "\n1. Add Book\n2. Remove Book\n3. Edit Book\n4. Back\n";
				libChoice = _getch();

				if (libChoice == '1')
				{
					libObj.Add_Book();
					libObj.Save_File();
				}
				else if (libChoice == '2')
				{
					libObj.Remove_Book();
					libObj.Save_File();
				}
				else if (libChoice == '3')
				{
					libObj.Edit_Book();
					libObj.Save_File();
				}
				else if (libChoice == '4')
				{
					goto Label;
				}
				else if (libChoice != '4')
				{
					cout << "Wrong choice, please only choose from 1 to 4.\n";
				}
			} while (libChoice != '4');
		}
		else
			goto Label;

	}
	else if (choice == '2')
	{
		char userChoice = '0';
		User* UserObj = 0;
		User* userObj = 0;
		bool permit = false;
		cout << "Login if you already have an accoiunt, Signup if you are a new user" << endl;
		cout << "1. Signup\n2. Login" << endl;
		userChoice = _getch();
		if (userChoice == '1')
		{
			permit = UserObj->Sign_Up(libObj, userObj);
			libObj.SaveUsers();
		}
		else if (userChoice == '2')
		{
			permit = UserObj->Login(libObj, userObj);
		}

		if (permit)
		{
			libObj.PrintAllBooks();
			do
			{
				cout << "\n\nWhat would like to perform" << endl;
				cout << "1. Issue Book\n2. Return Book\n3. Request For Book Information\n4. Back\n";
				userChoice = _getch();

				if (userChoice == '1')
				{
					userObj->Request_For_Issue();
				}
				else if (userChoice == '2')
				{
					userObj->Book_Return();
				}
				else if (userChoice == '3')
				{
					userObj->Request_For_Information();
				}
				else if (userChoice == '4')
				{
					goto Label;
				}
				else if (userChoice != '4')
				{
					cout << "Wrong choice, please only choose from 1 to 4.\n";
				}
			} while (userChoice != '4');
		}
		else
			goto Label;
	}

	else if (choice == '3')
	{
		cout << "\n\nQuitting program in 3 seconds.......\n";
		Sleep(3000);
		return;
	}
	else
	{
		cout << "Wrong choice, please choose only 1 or 2.\n";
	}


	system("pause>0");
}




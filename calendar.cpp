#include <iostream>
#include<string>
#include<cmath>
#include<stdlib.h>
#include <fstream>
#include <ctime>

using namespace std;

class date
{
public:
	int dateNum;
	int day;
	date* dateLink;

    date(){};
	date( date** dateHead, int _dateNum, int _day)
	{
            //DateInsert( date** dateHead, int _dateNum, int _day, char _eventName[100])

            date* newDate = new date ;
            newDate->dateNum = _dateNum;
            newDate->day = _day ;
            newDate->dateLink = DateXOR(*dateHead, NULL);

            if (*dateHead != NULL)
            {
                date* nextDate = DateXOR((*dateHead)->dateLink, NULL);
                (*dateHead)->dateLink = DateXOR(newDate, nextDate);
            }

            *dateHead = newDate;

	};
    bool operator != (date* d)
    {
        if(this != d)
            return true;
        else
            return false;
    }
    date* operator -> ()
    {
        return this;
    }
    date operator = (date d)
    {
        return d;
    }
    virtual string print(int day);
    date* DateXOR( date* currentDate, date* nextDate);
	void print( date* dateHead);
	void printList( date* dateHead);
};
class month: public date
{
public:
	int monthNum;
	int numOfDays;
	int startingDay;
	month* monthLink;
	date * dateHead;

	month(){};
	month(date* _dateHead, int Year, int _monthNum, int yearStartingDay, month** monthHead = NULL)
	{
            //MonthInsert(&monthHead, dateHead, monthNum, year, NonWeekDaysInYear(year));
            month* newMonth = new month;
            newMonth->dateHead = _dateHead;
            newMonth->monthNum = _monthNum;
            newMonth->numOfDays = NumDaysInMonth(_monthNum, Year);
            newMonth->startingDay = (yearStartingDay + NonWeekDaysInMonth(_monthNum, Year)) % 7;
            newMonth->monthLink = MonthXOR(*monthHead, NULL);

            if (*monthHead != NULL)
            {
                month* nextMonth = MonthXOR((*monthHead)->monthLink, NULL);
                (*monthHead)->monthLink = MonthXOR(newMonth, nextMonth);
            }

            *monthHead = newMonth;
	};

    bool operator != (month* d)
    {
        if(this != d)
            return true;
        else
            return false;
    }
    month* operator -> ()
    {
        return this;
    }
    month operator = (month m)
    {
        return m;
    }
    virtual string print(int Month);
	int NonWeekDaysInMonth(int Month, int Year);
	int NumDaysInMonth(int Month,int Year);
    int isLeapYearCheck(int Year);
	month* MonthXOR( month* currentMonth, month* nextMonth);
	void print( month* monthHead);
	void printList( month* monthHead);
	void printChoiceMonth( month* monthHead, int Month);

};
class year: public month
{
public:
	int isLeap;
	int numOfDays;
	int yearNum;
	int startingDay;
	year* yearLink;
	month* monthHead;

	year(){};
	//year(year** yearHead,  month* _monthHead, int _yearNum)
	year( int choice, int Year, int Month)
	{
        date* dateHead = NULL;
        month* monthHead = NULL;
        year* yearHead = NULL;

        /* Insert Dates */
        for (int dateNum = 1; dateNum <= NumDaysInMonth(Month, Year); dateNum++)
        {
            date(&dateHead, dateNum, (((NonWeekDaysInYear(Year) + NonWeekDaysInMonth(Month, Year)) % 7) + (dateNum % 7)) % 7);

            //DateInsert( date** dateHead, int _dateNum, int _day, char _eventName[100])

        }

        /* Insert Months*/
        for (int monthNum = 1; monthNum <= 12; monthNum++)
        {
            month( dateHead, Year, monthNum, NonWeekDaysInYear(Year), &monthHead);
        }

        //void YearInsert( year** yearHead,  month* _monthHead, int _yearNum)
        year* newYear = new year;
        newYear->yearNum = Year;
        newYear->isLeap = isLeapYearCheck(Year);
        if(newYear->isLeap)
            newYear->numOfDays = 366;
        else
            newYear->numOfDays = 365;
        newYear->startingDay = NonWeekDaysInYear(Year);
        newYear->monthHead = monthHead;
        newYear->yearLink = YearXOR(yearHead, NULL);

        if (*yearHead != NULL)
        {
             year* nextYear = YearXOR((yearHead)->yearLink, NULL);
            (*yearHead)->yearLink = YearXOR(newYear, nextYear);
        }
        yearHead = newYear;

        ProcessingFunction( choice, yearHead, Month);

	};

    bool operator != (year* d)
    {
        if(this != d)
            return true;
        else
            return false;
    }
    year* operator -> ()
    {
        return this;
    }
    year operator = (year y)
    {
        return y;
    }
    void ProcessingFunction( int choice, year* yearHead, int Month);
    int NonWeekDaysInYear(int Year);
    int NumDaysInYear(int Year);
    year* YearXOR( year* currentYear, year* nextYear);
    void print( year* yearHead);
    void printList( year* yearHead);
	void FancyMonthPrint( year* Year, int Month);


};


/* Date XOR Linked List Implementation Functions */
 date* date::DateXOR( date* currentDate, date* nextDate)
{
	return ( date*)((unsigned int)(currentDate) ^ (unsigned int)(nextDate));
}

void date::print( date* dateHead)
{
	cout<<" Date Number: "<<dateHead->dateNum<<"\t Day: "<<dateHead->day<<endl;
}
void date::printList( date* dateHead)
{
	date* currentDate = dateHead;
	date* previousDate = NULL;
	date* nextDate;

	//printf("Following are the list of date in a month:\n");

	while (currentDate != NULL)
	{
		print(currentDate);

		nextDate = DateXOR(previousDate, currentDate->dateLink);
		previousDate = currentDate;
		currentDate = nextDate;
	}
}
/* Mon-0, Tue-1, Wed-2, Thu-3, Fri-4, Sat-5, Sun-6 */

string date::print(int day)
{
    switch (day)
			{
			case 0: return "Monday"; break;
			case 1: return "Tuesday"; break;
			case 2: return "Wednesday"; break;
			case 3: return "Thursday"; break;
			case 4: return "Friday"; break;
			case 5: return "Saturday"; break;
			case 6: return "Sunday"; break;
			}
}

/* Month XOR Linked List Implementation Functions */
month* month::MonthXOR( month* currentMonth,  month* nextMonth)
{
	return ( month*)((unsigned int)(currentMonth) ^ (unsigned int)(nextMonth));
}

void month::print(month* monthHead)
{
	cout<<" Month Number: "<<monthHead->monthNum<<"\t number of days: "<<monthHead->numOfDays<<"\t Starting Day: "<<(monthHead->startingDay+1)<<endl;
	//printDateList(monthHead->dateHead);
}
void month::printList(month* monthHead)
{
	month* currentMonth = monthHead;
	month* previousMonth = NULL;
    month* nextMonth;

	//printf("Following are the list of month in a month:\n");

	while (currentMonth != NULL)
	{
		print(currentMonth);

		nextMonth = MonthXOR(previousMonth, currentMonth->monthLink);
		previousMonth = currentMonth;
		currentMonth = nextMonth;
	}
}

/* Function to calculate non week days in each month */
int month::NonWeekDaysInMonth(int Month, int Year)
{
	int nonWeekDays = 0;
	switch (Month)
	{				//nonWeekDays = (Previous month's number of days % 7)
		case 12: nonWeekDays += 2;										//(30 % 7)	December
		case 11: nonWeekDays += 3;										//(31 % 7)	November
		case 10:  nonWeekDays += 2;										//(30 % 7)	October
		case 9:  nonWeekDays += 3;										//(31 % 7)	September
		case 8:  nonWeekDays += 3;										//(31 % 7)	August
		case 7:  nonWeekDays += 2;										//(30 % 7)	July
		case 6:  nonWeekDays += 3;										//(31 % 7)	June
		case 5:  nonWeekDays += 2;										//(30 % 7)	May
		case 4:  nonWeekDays += 3;										//(31 % 7)	April
		case 3:  if (isLeapYearCheck(Year) == 1) { nonWeekDays += 1; }	//(29 % 7)	March	/* Leap Year */
				 else { nonWeekDays += 0; }								//(28 % 7)	March	/* Non-Leap Year */
		case 2:  nonWeekDays += 3; 										//(31 % 7)	February
		case 1: nonWeekDays += 0; break;								//(31 % 7)	January
	}
	return nonWeekDays;
}
/* Function to calculate number of days in a month */
int month::NumDaysInMonth(int Month,int Year)
{
	int numDaysMonth = 0;
	switch (Month)
	{
		case 1:  numDaysMonth = 31; break;							//January
		case 2:  if (isLeapYearCheck(Year)) numDaysMonth = 29;		//February
				 else numDaysMonth = 28;							//February
				 break;												//
		case 3:  numDaysMonth = 30; break;							//March
		case 4:  numDaysMonth = 31; break;							//April
		case 5:  numDaysMonth = 30; break;							//May
		case 6:  numDaysMonth = 31; break;							//June
		case 7:  numDaysMonth = 31; break;							//July
		case 8:  numDaysMonth = 31; break;							//August
		case 9:  numDaysMonth = 30; break;							//September
		case 10: numDaysMonth = 31; break;							//October
		case 11: numDaysMonth = 30; break;							//November
		case 12: numDaysMonth = 31; break;							//December
	}
	return numDaysMonth;
}

void year::FancyMonthPrint( year* Year, int Month)
{
	/* Navigation code to navigate month head to a month passed as parameter */
	month* currentMonth = Year->monthHead;
    month* previousMonth = NULL;
    month* nextMonth;


	while (currentMonth != NULL)
	{
		/* If the month is matched, then make a Fancy calendar for that month */
		if (currentMonth->monthNum == Month)
		{
			/* Print the Month Name*/
			switch (Month)
			{
			case 1: cout<<"\n\n\n January"; break;
			case 2: cout<<"\n\n\n February"; break;
			case 3: cout<<"\n\n\n March"; break;
			case 4: cout<<"\n\n\n April"; break;
			case 5: cout<<"\n\n\n May"; break;
			case 6: cout<<"\n\n\n June"; break;
			case 7: cout<<"\n\n\n July"; break;
			case 8: cout<<"\n\n\n August"; break;
			case 9: cout<<"\n\n\n September"; break;
			case 10:cout<<"\n\n\n October"; break;
			case 11:cout<<"\n\n\n November"; break;
			case 12:cout<<"\n\n\n December"; break;
			}
			/* Print the Week Bar */
			cout<<"\nMo \t Tu \t We \t Th \t Fr \t Sa \t Su\n";
			int i = 0;
			while (i < currentMonth->startingDay)
			{
				cout<<"   \t ";
				i++;
			}
			for (int i = 1; i <= currentMonth->numOfDays; i++)
			{
				cout<<i<<" \t ";
				if ((currentMonth->startingDay + i) % 7 == 0)
                    cout<<endl;
			}
		}
		nextMonth = MonthXOR(previousMonth, currentMonth->monthLink);
		previousMonth = currentMonth;
		currentMonth = nextMonth;
	}
}


/* Year XOR Linked List Implementation Functions */
 year* year::YearXOR( year* currentYear, year* nextYear)
{
	return ( year*)((unsigned int)(currentYear) ^ (unsigned int)(nextYear));
}

void year::print( year* yearHead)
{
	cout<<"\n Is Leap: "<<yearHead->isLeap<<"\n Number of Days: "<<yearHead->numOfDays<<"\n Starting Day: "<<yearHead->startingDay<<"\n Year Number: "<<yearHead->yearNum<<"\n"<<endl;
	month::printList(yearHead->monthHead);

}
void year::printList(year* yearHead)
{
	year* currentYear = yearHead;
	year* previousYear = NULL;
	year* nextYear;

	//printf("Following are the list of year in a year:\n");

	while (currentYear != NULL)
	{
		print(currentYear);

		nextYear = YearXOR(previousYear, currentYear->yearLink);
		previousYear = currentYear;
		currentYear = nextYear;
	}
}

/* Function Used in processing the input regarding year from the user*/
/* Function to Check weather or not the year is leap or not */
int month::isLeapYearCheck(int Year)
{
	if((Year % 4 == 0 && Year % 100 != 0) || Year % 400==0)
		return 1;
	else
		return 0;
}
string month::print(int Month)
{
			/* Print the Month Name*/
			switch (Month)
			{
                case 1: return "January"; break;
                case 2: return "February"; break;
                case 3: return "March"; break;
                case 4: return "April"; break;
                case 5: return "May"; break;
                case 6: return "June"; break;
                case 7: return "July"; break;
                case 8: return "August"; break;
                case 9: return "September"; break;
                case 10:return "October"; break;
                case 11:return "November"; break;
                case 12:return "December"; break;
			}
}

/* number of days in an year*/
int year::NumDaysInYear(int Year)
{
    if(isLeapYearCheck(Year))
        return 366;
    else
        return 365;
}
/* Function to calculate non week days in each year */
int year::NonWeekDaysInYear(int Year)
{
	int i = 0;
	int startingDay = 0;
	/* For Years after 2001 */
	if (Year > 2001)
	{
		for (i = 2002; i <= Year; i++)
		{
			/* If Leap Year then add 2 Non-week Days */
			if (isLeapYearCheck(i-1) == 1)
                startingDay += 2;
			/* If NOT Leap Year then add 1 Non-week Days */
			else startingDay += 1;
		}
		return startingDay % 7;
	}
	/* For Years before 2001 */
	else if (Year < 2001)
	{
		for (i = Year; i < 2001; i++)
		{
			/* If Leap Year then subtract 2 or add 5(7-2=>5) Non-week Days */
			if (isLeapYearCheck(i - 1) == 1) startingDay += 5;
			/* If  NOT Leap Year then subtract 1 or add 6(7-1=>6) Non-week Days */
			else startingDay += 6;
		}
		/* As Days repeat them self in 7 days*/
		return startingDay % 7;
	}
	/* For Year 2001 */
	else if (Year == 2001)
	{
		/* 1 Jan,2001 => Monday */
		return 0;
	}
}

void  EventManagement(int choice)
{
    if(choice == 3)
    {
        fstream file;
        string line;
        ofstream myfile ("event.txt", ios::out | ios::app);
        // opening file
        file.open("event.txt");

        // extracting words form the file
        while ( getline (file,line) )
        {
          cout << line << '\n';
        }
    }
    else if(choice == 4)
    {

        int alreadyexist = 0;
        fstream file;
        string line,line1;
        ofstream myfile ("event.txt", ios::out | ios::app);
        // opening file
        file.open("event.txt");

        cout<<"Enter the event"<<endl;
        cin>>line1;
        // extracting words form the file
        while ( getline (file,line) )
        {
          if(line1 == line)
            alreadyexist = 1;
        }
        if(alreadyexist)
            cout<<"the event already exist";
        else
            myfile<<line1<<endl;
    }
}

int MenuDisplay()
{
	int i = 0;
	int choice = 0;
	/*Print Menu untill program recive correct responce*/
	while (1)
	{
		char topRightCorner = 201;
		char topLeftCorner = 187;
		char BottomRightCorner = 200;
		char BottomLeftCorner = 188;
		char verticalLine = 186;
		char horizontalLine = 205;
		cout<<"\n\n"<<topRightCorner;
		for (i = 0; i < 100; i++)
            cout<<horizontalLine;

		cout<<topLeftCorner<<endl;
		cout<<verticalLine<<"                                                                                                    "<<verticalLine<<endl;
		cout<<verticalLine<<"                                          C++ MiniProject                                           "<<verticalLine<<endl;
		cout<<verticalLine<<"                                                                                                    "<<verticalLine<<endl;
		cout<<verticalLine<<"                                             Almanac                                                "<<verticalLine<<endl;
		cout<<verticalLine<<"                                                                                                    "<<verticalLine<<endl;
		cout<<verticalLine<<"                                           Input Menu :                                             "<<verticalLine<<endl;
		cout<<verticalLine<<"                                            1) Year Print                                           "<<verticalLine<<endl;
		cout<<verticalLine<<"                                            2) Month Print                                          "<<verticalLine<<endl;
		cout<<verticalLine<<"                                            3) display Events                                       "<<verticalLine<<endl;
		cout<<verticalLine<<"                                            4) Add An Events                                        "<<verticalLine<<endl;
		cout<<verticalLine<<"                                            5) Exit                                                 "<<verticalLine<<endl;
		cout<<verticalLine<<"                                                                                                    "<<verticalLine<<endl;
		cout<<BottomRightCorner;
		for (i = 0; i < 100; i++)	cout<< horizontalLine;
		cout<<BottomLeftCorner<<endl;

		/* Ask User for Choice */
		cout<<"\n\n\t\tEnter the Print Style: ";
		cin>>choice;
		if (choice == 1 || choice == 2 || choice == 3 || choice == 4|| choice == 5|| choice == 6) break;
	}
	return choice;
}

void year::ProcessingFunction( int choice, year* yearHead, int Month)
{
    //void ProcessingFunction( int choice, year** yearHead, int month);
    //ProcessingFunction( choice, yearHead, month);
	/*Print according to the Choice made by the user*/
	if (choice == 1)
	{
		printList(yearHead);
		//Looping the below function for all the 12 months in a year
		for (int i = 1; i <= 12; i++)
			FancyMonthPrint(yearHead, i);
	}
	else if (choice == 2)
	{	//printChoiceMonth(monthHead, month);/* This will print all the details of the month i a linked list format */
		FancyMonthPrint(yearHead, Month);
	}
}

/* Main Function */
int main(void)
{
    cout<<"                                             Welcome to Almanac                                               ";
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    year( 2, (timePtr->tm_year + 1900), ++timePtr->tm_mon);
    cout<<endl<<endl;
  cout << "hours = " << timePtr->tm_hour << endl;
  cout << "minutes = " << timePtr->tm_min << endl;
  cout << "seconds= " << timePtr->tm_sec << endl;
  cout << "year = " << (timePtr->tm_year + 1900) << endl;
  cout << "month of year = " << timePtr->tm_mon << endl;
  cout << "day of month = " << timePtr->tm_mday << endl;
  cout << "weekday = " << timePtr->tm_wday << endl;
  cout << "day of year = " << timePtr->tm_yday << endl;
    cout<<"\nPress enter to view the Options \n";
    cin.get();


	/*Setting up the Program*/
	int choice = 0;
	int Year = 0;
	int Month = 0;
	int day = 0;
	int i = 0;
	int exit = 0;
	while(exit != 1)
    {
	/* Clear in the Terminal using terminal commands*/
	system("cls");	/* Works with Windows */
	//system("clear");	/* Works with Linux */

	/* Ask user to make choice */
	choice = MenuDisplay();
	/* Ask user for input */
	if (choice == 1)
	{
		cout<<"\nEnter the Year in numeric format:";
		cin>>Year;
        year( choice, Year, Month);

	}
	else if (choice == 2)
	{
		cout<<"\nEnter the Year in numeric format:";
		cin>>Year;
		cout<<"\nEnter the Month in numeric format:";
		cin>>Month;
        year( choice, Year, Month);
	}

    else if (choice == 3)
	{
		EventManagement( choice);
	}
	else if (choice == 4)
	{
		EventManagement( choice);
	}
    else if (choice == 5)
    {
        cout<<"\nThank You \n";
        cout<<"Have a good day\nProject By SALONI RAJ GOEL\n";
        exit = 1;
    }
    else
        cout<<"Invalid Input\n";
    cout<<"\nPress enter to continue\n";
    cin.get();
    cin.ignore();
    }
    cout<<endl;
	return 0;
}

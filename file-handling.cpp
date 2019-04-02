//header files
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

//function prototype
void addition();
void display();
void search();
void modify();
void deletion();
void input();
void output();

//structure to store player data
struct game
{
  int gamecode;
  char gamename[10];
  int age;
  float score;
  char category[10];
} G1,G2;

//global variable
fstream f1,f2;
char choice;

//main function
void main()
{
  clrscr();
  int ch;	//for making choice between different queries
  f1.open("Game.dat",ios::out|ios::app|ios::binary);
  f1.close();
  while(ch!=6)
  {
    clrscr();
    cout<<"\nMAIN MENU";
    cout<<"\n1.Add records";
    cout<<"\n2.Display records";
    cout<<"\n3.View a record";
    cout<<"\n4.Modify records";
    cout<<"\n5.Delete records";
    cout<<"\n6.Exit";
    cout<<"\nEnter your choice(1-6):";
    cin>>ch;
    if(ch==1)
    {
      addition();
    }
    else if(ch==2)
    {
      display();
    }
    else if(ch==3)
    {
      search();
    }
    else if(ch==4)
    {
      modify();
    }
    else if(ch==5)
    {
      deletion();
    }
    else if(ch==6)
    {
      exit(0);
    }
  }
}

//accept input from user
void input()
{
  cout<<"Enter game code:";
  cin>>G1.gamecode;
  cout<<"Enter game name:";
  gets(G1.gamename);
  cout<<"Enter age:";
  cin>>G1.age;
  cout<<"Enter score:";
  cin>>G1.score;

  if(G1.age>=18)
  {
    strcpy(G1.category,"Major");
  }
  else
  {
    strcpy(G1.category,"Minor");
  }
}

//display stored record
void output()
{
  cout<<"\nGame code:";
  cout<<G1.gamecode;
  cout<<"\nGame name:";
  cout<<G1.gamename;
  cout<<"\nAge:";
  cout<<G1.age;
  cout<<"\nScore:";
  cout<<G1.score;
  cout<<"\nCategory:";
  cout<<G1.category;
}

//add record to the file
void addition()
{
  int length=0,htr=0;
  clrscr();
  do
  {
    f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
    f2.open("temp.dat",ios::out|ios::binary); //open file2 in write mode
	//accepting data from user
    cout<<"Enter game code:";
    cin>>G2.gamecode;
    cout<<"Enter game name:";
    gets(G2.gamename);
    cout<<"Enter age:";
    cin>>G2.age;
    cout<<"Enter score:";
    cin>>G2.score;
    if(G2.age>=18)
    {
      strcpy(G2.category,"Major");
    }
    else
    {
      strcpy(G2.category,"Minor");
    }

    f1.seekg(0,ios::end); //move cursor to begining of file1
    length=f1.tellg(); //to check if file1 is empty
    if(length==0) //file1 is empty
    {
      f2.write((char*)&G2,sizeof(G2)); //write to the file2 directly
    }
    else if(length!=0) //file1 is not empty, data needs to be appended
    {
      f1.seekg(0,ios::beg); //move cursor to begining of file1
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1)); //read a record from file1
        if(!f1.eof())
        {
		  //adding record in correct order based on gamecode
          if(G2.gamecode<G1.gamecode)
          {
            f2.write((char*)&G2,sizeof(G2)); //write record in file2
            htr=1; //record has been written to the file
            f1.seekg(-1*sizeof(G1),ios::cur); //move one record back in file1
            f2.write((char*)&G1,sizeof(G1)); //write record in file2
            f1.seekg(1*sizeof(G1),ios::cur); //move one record forward in file1
            break;
          }
          else if(G2.gamecode==G1.gamecode)
          {
            f2.write((char*)&G2,sizeof(G2)); //write record in file2
            f2.write((char*)&G1,sizeof(G1)); //write record in file2
            htr=1;
            break;
          }
          else
          {
            f2.write((char*)&G1,sizeof(G1)); //write record in file2
          }
        }
      }

      if(htr==0) //record not written to file2 yet
      {
        f2.write((char*)&G2,sizeof(G2));
      }
      else if(!f1.eof()) //if record has been written to file2 but not all records of file1 have been copied to file2
      {
        while(!f1.eof())
        {
          f1.read((char*)&G1,sizeof(G1));
          if(!f1.eof())
            f2.write((char*)&G1,sizeof(G1));
        }
      }
    }
//close files
    f1.close();
    f2.close();
    remove("Game.dat"); //removing the main file
    rename("temp.dat","Game.dat"); //renaming temp file as main file
    cout<<"Record added.";
    cout<<"\nDo you want to enter more records(Y/N):";
    cin>>choice;
    choice=toupper(choice);
  }
  while(choice=='Y');
}

//displaying all records stored in the file
void display()
{
  clrscr();
  int a=2,b=2,str=0;
  f1.open("Game.dat",ios::in|ios::binary); //open file in read mode
  //formatting output to display in tabular format
  gotoxy(a,b);
  cout<<"S.no.";
  gotoxy((a+7),b);
  cout<<"Game Code";
  gotoxy((a+20),b);
  cout<<"Game Name";
  gotoxy((a+33),b);
  cout<<"Age";
  gotoxy((a+40),b);
  cout<<"Score";
  gotoxy((a+50),b);
  cout<<"Category";

  while(!f1.eof())
  {
    f1.read((char*)&G1,sizeof(G1)); //reading from file1
    if(!f1.eof())
    {
      //displaying records in tabular form
      b++;
      gotoxy(a,b);
      cout<<(b-2);
      gotoxy((a+7),b);
      cout<<G1.gamecode;
      gotoxy((a+20),b);
      cout<<G1.gamename;
      gotoxy((a+33),b);
      cout<<G1.age;
      gotoxy((a+40),b);
      cout<<G1.score;
      gotoxy((a+50),b);
      cout<<G1.category;
      str++; //counter for checking if a record is displayed
    }
  }

  if(str==0) //implies that no record exist
  {
    cout<<"\n\n\n No records available.";
  }
  cout<<"\n Press any key to reurn to menu.";
  getch();
  f1.close();
}

//for searching record based on various fields
void search()
{
  clrscr();
  char choice1;
  int basis,ctr=0;
  clrscr();
  do
  {
    cout<<"Choose the basis on which you want to search:";
    cout<<"\n1.Game code";
    cout<<"\n2.Game name";
    cout<<"\n3.Age";
    cout<<"\n4.Score";
    cout<<"\n5.Category";
    cout<<"\nEnter your choice(1-5):";
    cin>>basis;
    if(basis==1) //basis=gamecode
    {
      int gcode;
      cout<<"Enter the game code:";
      cin>>gcode;
      f1.close();
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(f1.eof())
          break;
        else if(gcode==G1.gamecode) //check for equalty
        {
          output();
          ctr++; //counter for checking if matching record exist
        }
      }
      if(ctr==0) //implies no matching record exist
      {
        cout<<"No match found for the entered game code.";
      }
      f1.close();
    }

    else if(basis==2) //basis=gamename
    {
      char gname[10];
      cout<<"Enter the game name:";
      gets(gname);
      f1.close();
      f1.open("Game.dat",ios::in|ios::binary); //open file in read mode
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(f1.eof())
          break;
        else if(strcmpi(gname,G1.gamename)==0) //check for equalty
        {
          output();
          ctr++; //counter for checking if matching record exist
        }
      }
      if(ctr==0) //implies no matching record exist
      {
        cout<<"No match found for the entered game name";
      }
      f1.close();
    }

    else if(basis==3) //basis=age
    {
      int gage;
      cout<<"Enter the age:";
      cin>>gage;
      f1.close();
      f1.open("Game.dat",ios::in|ios::binary); //open file in read mode
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(f1.eof())
          break;
        else if(gage==G1.age) //check for equalty
        {
          output();
          ctr++; //counter for checking if matching record exist
        }
      }
      if(ctr==0) //implies no matching record exist
      {
        cout<<"No match found for the entered age.";
      }
      f1.close();
    }

    else if(basis==4) //basis=score
    {
      int gscore;
      cout<<"Enter the score:";
      cin>>gscore;
      f1.close();
      f1.open("Game.dat",ios::in|ios::binary); //open file in read mode
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(f1.eof())
          break;
        else if(gscore==G1.score) //check for equalty
        {
          output();
          ctr++; //counter for checking if matching record exist
        }
      }
      if(ctr==0) //implies no matching record exist
      {
        cout<<"No match found for the entered score.";
      }
      f1.close();
    }

    else if(basis==5) //basis=category
    {
      char gcategory[10];
      cout<<"Enter the category:";
      gets(gcategory);
      f1.close();
      f1.open("Game.dat",ios::in|ios::binary); //open file in read mode
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(f1.eof())
          break;
        else if(strcmpi(gcategory,G1.category)==0) //check for equalty
        {
          output();
          ctr++; //counter for checking if matching record exist
        }
      }
      if(ctr==0) //implies no matching record exist
      {
        cout<<"No match found for the entered category.";
      }
      f1.close();
    }
    cout<<"\nDo you want to view any other record(Y/N):";
    cin>>choice;
    choice=toupper(choice);
  }
  while(choice!='N');
}

//for modifying record based on different fields
void modify()
{
  char choice1;
  int basis,flag=0;
  clrscr();
  do
  {
    cout<<"Choose the basis on which you want to modify:";
    cout<<"\n1.Game code";
    cout<<"\n2.Game name";
    cout<<"\n3.Age";
    cout<<"\n4.Score";
    cout<<"\n5.Category";
    cout<<"\nEnter your choice(1-5):";
    cin>>basis;
    if(basis==1) //basis=gamecode
    {
      int gcode;
      cout<<"Enter game code:"; //accepting gamecode of record to be modified
      cin>>gcode;
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("temp.dat",ios::out|ios::binary); //open file2 in write mode
	  //finding record to be modified
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(gcode==G1.gamecode)
          {
            output();
            cout<<"\nDo you want to modify this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='Y')
            {
              flag++; //for checking if a matching recor is found
              cout<<"Enter new details\n";
              input();
            }
          }
          f2.write((char*)&G1,sizeof(G1)); //writing records to file2
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(flag==0)
        cout<<"No match found for the entered game code.";
      else
        cout<<"Chosen record modified.";
    }

    else if(basis==2) //basis=gamename
    {
      char gname[10];
      cout<<"Enter game name:"; //accepting gamename of record to be modified
      gets(gname);
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("temp.dat",ios::out|ios::binary); //open file2 in write mode
      //finding record to be modified
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(strcmpi(gname,G1.gamename)==0)
          {
            output();
            cout<<"\nDo you want to modify this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='Y')
            {
              flag++; //for checking if a matching recor is found
              cout<<"Enter new details\n";
              input();
            }
          }
          f2.write((char*)&G1,sizeof(G1)); //writing records to file2
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(flag==0)
        cout<<"No match found for the entered game name.";
      else
        cout<<"Chosen record modified.";
    }

    else if(basis==3) //basis=age
    {
      int gage;
      cout<<"Enter age:"; //accepting age of record to be modified
      cin>>gage;
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("temp.dat",ios::out|ios::binary); //open file2 in write mode
      //finding record to be modified
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(gage==G1.age)
          {
            output();
            cout<<"\nDo you want to modify this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='Y')
            {
              flag++; //for checking if a matching recor is found
              cout<<"Enter new details\n";
              input();
            }
          }
          f2.write((char*)&G1,sizeof(G1)); //writing records to file2
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(flag==0)
        cout<<"No match found for the entered age.";
      else
        cout<<"Chosen record modified.";
    }

    else if(basis==4) //basis=score
    {
      int gscore;
      cout<<"Enter score:"; //accepting score of record to be modified
      cin>>gscore;
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("temp.dat",ios::out|ios::binary); //open file2 in write mode
      //finding record to be modified
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(gscore==G1.score)
          {
            output();
            cout<<"\nDo you want to modify this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='Y')
            {
              flag++; //for checking if a matching recor is found
              cout<<"Enter new details\n";
              input();
            }
          }
          f2.write((char*)&G1,sizeof(G1)); //writing records to file2
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(flag==0)
        cout<<"No match found for the entered score.";
      else
        cout<<"Chosen record modified.";
    }
    
    else if(basis==5) //basis=category
    {
      char gcategory[10];
      cout<<"Enter category:"; //accepting category of record to be modified
      gets(gcategory);
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("temp.dat",ios::out|ios::binary); //open file2 in write mode
      //finding record to be modified
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(strcmpi(gcategory,G1.category)==0)
          {
            output();
            cout<<"\nDo you want to modify this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='Y')
            {
              flag++; //for checking if a matching recor is found
              cout<<"Enter new details\n";
              input();
            }
          }
          f2.write((char*)&G1,sizeof(G1)); //writing records to file2
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(flag==0)
        cout<<"No match found for the entered category.";
      else
        cout<<"Chosen record modified.";
    }
    cout<<"\nDo you want to modify any other record(Y/N):";
    cin>>choice;
    choice=toupper(choice);
  }
  while(choice!='N');
}
void deletion()
{
  char choice1;
  int basis,del=0;;
  clrscr();
  do
  {
    cout<<"Choose the basis on which you want to delete:";
    cout<<"\n1.Game code";
    cout<<"\n2.Game name";
    cout<<"\n3.Age";
    cout<<"\n4.Score";
    cout<<"\n5.Category";
    cout<<"\nEnter your choice(1-5):";
    cin>>basis;
    if(basis==1) //basis=gamecode
    {
      int gcode;
      cout<<"Enter the game code:";
      cin>>gcode;
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("Temp.dat",ios::out|ios::binary); //open file2 in write mode
      //finding record to be deleted
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(gcode!=G1.gamecode) //if record is not to be deleted then copy to file2
          {
            f2.write((char*)&G1,sizeof(G1));
          }
          if(gcode==G1.gamecode) //if record is to be deleted then do not copy to file2
          {
            output();
            cout<<"\nDo you want to delete this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='N')
            {
              f2.write((char*)&G1,sizeof(G1));
            }
            else
              del++; //flag for checking if any record has been deleted
          }
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(del==0) //no matching record found
        cout<<"No match found for the entered game code.";
      else
        cout<<"Chosen record deleted.";
    }

    else if(basis==2) //basis=gamename
    {
      char gname[10];
      cout<<"Enter the game name:";
      gets(gname);
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("Temp.dat",ios::out|ios::binary); //open file2 in write mode
      //finding record to be deleted
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(strcmpi(gname,G1.gamename)!=0) //if record is not to be deleted then copy to file2
          {
            f2.write((char*)&G1,sizeof(G1));
          }
          if(strcmpi(gname,G1.gamename)==0) //if record is to be deleted then do not copy to file2
          {
            output();
            cout<<"\nDo you want to delete this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='N')
            {
              f2.write((char*)&G1,sizeof(G1));
            }
            else
              del++; //flag for checking if any record has been deleted
          }
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(del==0) //no matching record found
        cout<<"No match found for the entered game name.";
      else
        cout<<"Chosen record deleted.";
    }

    else if(basis==3) //basis=age
    {
      int gage;
      cout<<"Enter the age:";
      cin>>gage;
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("Temp.dat",ios::out|ios::binary); //open file2 in write mode
      //finding record to be deleted
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(gage!=G1.age) //if record is not to be deleted then copy to file2
          {
            f2.write((char*)&G1,sizeof(G1));
          }
          if(gage==G1.age) //if record is to be deleted then do not copy to file2
          {
            output();
            cout<<"\nDo you want to delete this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='N')
            {
              f2.write((char*)&G1,sizeof(G1));
            }
            else
              del++; //flag for checking if any record has been deleted
          }
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(del==0) //no matching record found
        cout<<"No match found for the entered age.";
      else
        cout<<"Chosen record deleted.";
    }

    else if(basis==4) //basis=score
    {
      int gscore;
      cout<<"Enter the score:";
      cin>>gscore;
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("Temp.dat",ios::out|ios::binary); //open file2 in write mode
      //finding record to be deleted
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(gscore!=G1.score) //if record is not to be deleted then copy to file2
          {
            f2.write((char*)&G1,sizeof(G1));
          }
          if(gscore==G1.score) //if record is to be deleted then do not copy to file2
          {
            output();
            cout<<"\nDo you want to delete this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='N')
            {
              f2.write((char*)&G1,sizeof(G1));
            }
            else
              del++; //flag for checking if any record has been deleted
          }
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(del==0) //no matching record found
        cout<<"No match found for the entered score.";
      else
        cout<<"Chosen record deleted.";
    }

    else if(basis==5) //basis=category
    {
      char gcategory[10];
      cout<<"Enter the category:";
      gets(gcategory);
      f1.open("Game.dat",ios::in|ios::binary); //open file1 in read mode
      f2.open("Temp.dat",ios::out|ios::binary); //open file2 in write mode
      //finding record to be deleted
      while(!f1.eof())
      {
        f1.read((char*)&G1,sizeof(G1));
        if(!f1.eof())
        {
          if(strcmpi(gcategory,G1.category)!=0) //if record is not to be deleted then copy to file2
          {
            f2.write((char*)&G1,sizeof(G1));
          }
          if(strcmpi(gcategory,G1.category)==0) //if record is to be deleted then do not copy to file2
          {
            output();
            cout<<"\nDo you want to delete this record(Y/N):";
            cin>>choice1;
            choice1=toupper(choice1);
            if(choice1=='N')
            {
              f2.write((char*)&G1,sizeof(G1));
            }
            else
              del++; //flag for checking if any record has been deleted
          }
        }
      }
      f1.close();
      f2.close();
      remove("Game.dat");
      rename("temp.dat","Game.dat");
      if(del==0) //no matching record found
        cout<<"No match found for the entered category.";
      else
        cout<<"Chosen record deleted.";
    }
    cout<<"\nDo you want to delete any other record(Y/N):";
    cin>>choice;
    choice=toupper(choice);
  }
  while(choice!='N');
}

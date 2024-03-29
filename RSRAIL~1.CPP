#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<dos.h>

void menu();
void load();
void copy();

int n=3, flag=0, indic=0, br=0, oath=0, control=0, k=0, dem;
char uni, imp;

struct engine    //Structure used as basis
{
  float t_no, platform;
  char from[20], to[20], via[20], status[20], eta[10], etd[10];
  double fare;
}eng[5], s, mod;


class misc       //Class for miscellaneous & main  functions
{
 int next;

 public:

 void misdisplay();
 void password();
}mis;

void misc :: password()
{
  int level;
  char pass[5];

  for(int m=0; m<80; m++) //Code for a straight line
  cout<<"-";

  cout<<setw(50)<<"RS railways"<<endl;

  for(int l=0; l<80; l++) //Code for a straight line
  cout<<"-";

  cout<<"\n"<<setw(80)<<"Homescreen";

  cout<<"\n\nACCESS LEVELS "<<endl;
  cout<<"\n1.Customer"<<endl;
  cout<<"2.Admin"<<endl;

  if(k>0)
  {
   cout<<"3.Exit"<<endl;
   cout<<"\nChoose an option: ";
  }

  else
  {
   cout<<"\nEnter access level: ";
  }

  cin>>level;
  k++;

  switch(level)
  {
   case 1 : oath=2;
	    load();
	    next=1;
	    misdisplay();
	    break;

   case 2 : next=2;
	    do
	    {
	     cout<<"\n\nEnter Password : ";
	     n--;
	     gets(pass);
	     cout<<"Processing";
	     delay(200);
	     cout<<".";
	     delay(100);
	     cout<<".";
	     delay(100);
	     cout<<".";
	     delay(150);

	     if(strcmpi(pass, "hello")==0)
	     {
	       cout<<"\n\nPassword accepted..."<<endl;
	       cout<<"Welcome Administrator";
	       delay(1000);
	       load();
	       menu();
	       break;
	     }

	     else
	     {
	      clrscr();
	      cout<<"Access denied.\nYou have "<<n<<" attempts remaining"<<endl;
	     }

	    }while(n!=0);

	    if(n>0)
	    do
	    {
	     cout<<"\n\nReturn to menu?(Y/N): ";
	     cin>>uni;

	     if(uni=='y'||uni=='Y')
	     {
	      clrscr();
	      oath=1;
	      load();
	      menu();
	     }

	     else
	     {
	      oath=6;
	      load();
	      exit(0);
	     }
	    }while(uni=='y'||uni=='Y');

	    else
	    {
	     oath=1;
	     load();
	     password();
	    }
	    break;

   case 3 : oath=6;
	    load();
	    exit(0);
	    break;

   default : cout<<"Invalid selection!!"<<endl;
	     clrscr();
	     password();
	     break;
  }
}


void misc :: misdisplay()
{
   for(int m=0; m<80; m++) //Code for a straight line
  cout<<"-";

  cout<<setw(10)<<"Train no."<<setw(11)<<"Departure"<<setw(9)<<"Arival"<<setw(7)<<"Via"<<setw(8)<<"Status"<<setw(5)<<"ETA"<<setw(7)<<"ETD"<<setw(13)<<"Platform"<<setw(6)<<"Fare"<<endl;

  for(int j=0; j<80; j++) //Code for a straight line
  cout<<"-";

  ifstream fin;
  fin.open("train.dat", ios::beg||ios::in);
  fin.seekg(0, ios::beg);
  int i=0;

  while(fin.read((char*)&eng[i], sizeof(eng[i])))
  {
   cout<<setw(6)<<eng[i].t_no<<setw(15)<<eng[i].from<<setw(9)<<eng[i].to<<setw(7)<<eng[i].via<<setw(5)<<eng[i].status<<setw(10)<<eng[i].eta<<setw(7)<<eng[i].etd<<setw(8)<<eng[i].platform<<setw(9)<<eng[i].fare<<endl;
   i++;
  }

  fin.close();
  copy();

  if(next==1)
  {
   cout<<"\nWould you like to return to the homescreen?(Y/N): ";
   cin>>imp;

   switch(imp)
   {
     case 'y' : oath=7;
		load();
		password();
		break;
     case 'Y' : oath=7;
		load();
		password();
		break;
     default :  oath=6;
		load();
		exit(0);
		break;
   }
  }
}


class seat
{
 public:
 int row, column, seat[10][5];

 seat()
 {
  initialize();
 }

 void initialize();    //Function to create seats
 void showseat();      //Function to display seats
 void selectseat();    //Function to book seats
}compartment[7];

void seat::initialize()
{
  for(int i=0; i<10; i++)
   {
      for(int j=0; j<5; j++)
      {
       seat[i][j]=0;
      }
   }
}

void seat::showseat()
{
 cout<<"\n\nColumn  1234 56";
 for(int i=0; i<10; i++)
 {
  cout<<"\n";

  if(i%2==0)
  cout<<"\n";

  cout<<"Row "<<i+1<<"  ";
  if(i!=9)
  cout<<" ";

  for(int j=0; j<6; j++)
  {
   cout<<seat[i][j];

   if(j==3)
   cout<<" ";
  }
 }
}

void seat:: selectseat()
{
   cout<<"\n\nSeats availiable follow the following code";
   cout<<"\nSEATS MARKED 0 ARE FREE";
   cout<<"\nSEATS MARKED 1 ARE OCCUPIED";

   showseat();

   cout<<"\n\nSEAT SELETION";
   cout<<"\nEnter the seat row: ";
   cin>>row;
   row=row-1;
   cout<<"\nEnter the seat column: ";
   cin>>column;
   column=column-1;

   if (row>11||column>5)
   cout<<"\nInvalid seat selection!";

   else if(seat[row][column]==1)
   {
     cout<<"\nSeat is already booked!!";
   }

   else
   {
     cout<<"\nSeat sucessfully booked"<<endl;
     seat[row][column]=1;
     control=1;
   }
}

void search_train();
void putno();
void setno();

class ticketing : public misc, seat
{
 public:

 int ccount, cnoticket, cplatform, number;
 float ctrain;
 char cclass[20], cfrom[20], cto[20], cdate[10], sno[5];
 double classfare, ticketfare;

 ticketing()
 {
  setno();
 }


 void enter_bill();
 void avail();
 int ticket();

}billing;

void ticketing :: enter_bill()
{
   ofstream fout;
   fout.open("transactions.txt", ios::app);
   fout<<"\n\nTicket Number "<<ccount<<" deatils";
   fout<<"\nTrain Number: "<<ctrain;
   fout<<"\nFrom: "<<cfrom;
   fout<<"\nTo: "<<cto;
   fout<<"\nDate: "<<cdate;
   fout<<"\nClass: "<<cclass;
   fout<<"\nSeat: "<<sno;
   fout<<"\nPlatform Number: "<<cplatform;
   fout<<"\nFare: "<<ticketfare;
   fout.close();
}

int ticketing :: ticket()
{
 char ch, choice;
 int cri;

 cout<<"\n\nWould you like a ticket for Train number "<<ctrain<<"? (Y/N): ";
 cin>>choice;

 if(choice=='n'||choice=='N')
 {
  oath=1;
  load();
  menu();
 }

 else if(choice=='y'||choice=='Y')
 {
  cout<<"Enter date of travel: ";
  gets(cdate);
  ccount++;

  cout<<"\n\nCLASS SELECTION"<<endl;
  cout<<"1.First AC"<<endl;
  cout<<"2.Second AC"<<endl;
  cout<<"3.Third AC"<<endl;
  cout<<"4.Sleeper"<<endl;
  cout<<"5.AC chair"<<endl;
  cout<<"6.General compartment"<<endl;
  cout<<"\nChoose a class: ";
  cin>>cri;

  switch(cri)
  {
   case 1 : strcpy(cclass,"First AC");
	    classfare=2000;
	    break;
   case 2 : strcpy(cclass,"Second AC");
	    classfare=1800;
	    break;
   case 3 : strcpy(cclass,"Third AC");
	    classfare=1500;
	    break;
   case 4 : strcpy(cclass,"Sleeper");
	    classfare=1200;
	    break;
   case 5 : strcpy(cclass,"AC chair");
	    classfare=700;
	    break;
   case 6 : strcpy(cclass,"General compartment");
	    classfare=500;
	    break;
   default : cout<<"\nInvalid selection!!"<<endl;
	     oath=7;
	     load();
	     exit(0);
  }

  compartment[cri].selectseat();
  sno[0]='R';
  sno[1]=49+compartment[cri].row;
  sno[2]='C';
  sno[3]=49+compartment[cri].column;
  ticketfare=classfare + eng[number].fare;    //Calculation of total fare

  if(control==1)
  {
   cout<<"\n\nTICKET PREVIEW"<<endl;
   cout<<"\nTrain number: "<<ctrain<<endl;
   cout<<"From: "<<cfrom<<endl;
   cout<<"To: "<<cto<<endl;
   cout<<"Date: "<<cdate<<endl;
   cout<<"Class: "<<cclass<<endl;
   cout<<"Seat: "<<sno<<endl;
   cout<<"Platform Number: "<<cplatform<<endl;
   cout<<"Fare: "<<ticketfare<<endl;
   cout<<"CONFIRM PURCHASE? (Y/N)";
   cin>>ch;

   if(ch=='y'||ch=='Y')
   {
    oath=3;
    load();
    putno();
    enter_bill();                 //Bill will now be stored in the file
    cout<<"\n\nTicket Sucessfully Booked!"<<endl;
    cout<<"Check directory for the soft copy of the transaction...\n\n";
    system("pause");
    oath=1;
    load();
    menu();
   }

   else if(ch=='n'||ch=='N')
   {
    oath=4;
    load();

    oath=1;
    load();

    menu();
   }
  }
 }
  else
  {
   oath=5;
   load();
   menu();
  }
 return 0;
}

void ticketing :: avail()
{
 indic=1;
 cout<<"Booking reservation menu"<<endl;
 void search_train();
 search_train();

 if(flag==1)
 ticket();
}

void setno()   //Function to read the number of transactions already made
{
 ifstream fin;
 fin.open("number.txt", ios::in);
 fin>>billing.ccount;
 fin.close();
}

void putno()
{
 ofstream fout;
 fout.open("number.txt", ios::out);
 fout<<billing.ccount;
 fout.close();
}

class final : public ticketing
{
 public:
 void enter();
 void modify();
}fobj;

void final :: enter()
{
  int pos, cho, var, no;
  char ch;

  cout<<"Enter number of the trains you want to add details of: ";
  cin>>no;

  dem+=no;

  ofstream fout;
  fout.open("train.dat", ios::app||ios::out);
  fout.seekp(0, ios::end);

  for(int i=0; i<no; i++)
  {
     cout<<"\n\nEnter details of Train "<<i+1<<endl;
     cout<<"Train number: ";
     cin>>mod.t_no;
     cout<<"Estimated Time of Arival: ";
     gets(mod.eta);
     cout<<"Estimated Time of Departure: ";
     gets(mod.etd);
     cout<<"From: ";
     gets(mod.from);
     cout<<"To: ";
     gets(mod.to);
     cout<<"Via: ";
     gets(mod.via);
     cout<<"Platform: ";
     cin>>mod.platform;
     cout<<"Fare: ";
     cin>>mod.fare;
     cout<<"Status: ";
     gets(mod.status);
     fout.write((char*)&mod,sizeof(mod));

  }
  fout.close();

  ofstream f;
  f.open("demno.txt", ios::out||ios::beg);
  f<<dem;
  f.close();

  misdisplay();

}

void final :: modify()
{
  int pos, cho, var;
  double no;
  char ch;

  misdisplay();
  cout<<"\n\nEnter registered number of the train you want to modify details of: ";
  cin>>no;

  ifstream fin;
  fin.open("train.dat", ios::in);
  fin.seekg(0, ios::beg);

  for(int i=0; i<3; i++)
  {
   fin.read((char*)&mod,sizeof(mod));

   if(mod.t_no==no)
   {
    pos=fin.tellg();
    var=1;
    cout<<"\n\nThe train has been found!!"<<endl;
    do
    {
     cout<<"1.Train number"<<endl;
     cout<<"2.ETA"<<endl;
     cout<<"3.ETD"<<endl;
     cout<<"4.Platform"<<endl;
     cout<<"5.Fare"<<endl;
     cout<<"6.From"<<endl;
     cout<<"7.To"<<endl;
     cout<<"8.Via"<<endl;
     cout<<"9.Status"<<endl;
     cout<<"What would you like to change? ";
     cin>>cho;

     cout<<"Enter new data: ";

     switch(cho)
     {
      case 1 : cin>>mod.t_no;
	       break;
      case 2 : gets(mod.eta);
	       break;
      case 3 : gets(mod.etd);
	       break;
      case 4 : cin>>mod.platform;
	       break;
      case 5 : cin>>mod.fare;
	       break;
      case 6 : gets(mod.from);
	       break;
      case 7 : gets(mod.to);
	       break;
      case 8 : gets(mod.via);
	       break;
      case 9 : gets(mod.status);
	       break;
      default : cout<<"INVLAID SELECTION!!";
		break;
     }

     cout<<"\n\nDo you want to change anything else?(Y/N)";
     cin>>ch;
    }while(ch=='y'||ch=='Y');

    fin.close();

    ofstream fout;
    fout.open("train.dat", ios::out||ios::app);
    fout.seekp(pos-sizeof(mod));
    fout.write((char*)&mod,sizeof(mod));
    fout.close();
   }

   if(var==1)
   break;
  }

  if(var!=1)
  {
   fin.close();
   cout<<"\nTrain not found!!";
  }
  else
  misdisplay();
}

void search_des()
{
  int number;
  char depa[20], des[20], ch;

  ifstream fin;
  fin.open("train.dat", ios::in||ios::beg);
  fin.seekg(0, ios::beg);

  cout<<"Enter Departing station: ";
  gets(depa);
  cout<<"Enter Destination: ";
  gets(des);

  int i=0;
  flag=0;
  while(fin.read((char*)&mod, sizeof(mod)))
  {
   if((strcmpi(eng[i].to, des)==0)&&(strcmpi(eng[i].from, depa)==0))
   {
    cout<<"\n\nTRAIN FOUND!!"<<endl;
    cout<<"\nDetails"<<endl;
    cout<<"\nTrain number: "<<eng[i].t_no<<endl;
    cout<<"From: "<<eng[i].from<<endl;
    cout<<"To: "<<eng[i].to<<endl;
    cout<<"Via: "<<eng[i].via<<endl;
    cout<<"Status: "<<eng[i].status<<endl;
    cout<<"Estimated time of arival: "<<eng[i].eta<<endl;
    cout<<"Estimated time of departure: "<<eng[i].etd<<endl;
    cout<<"Platform: "<<eng[i].platform<<endl;
    cout<<"Fare: "<<eng[i].fare<<endl;

    flag=1;
    number=i;
   }
   i++;
  }

  if(flag!=1)
  cout<<"\nNo train found!!";

  billing.ctrain=eng[number].t_no;
  strcpy(billing.cfrom, eng[number].from);
  strcpy(billing.cto, eng[number].to);
  billing.cplatform=eng[number].platform;
  billing.ticketfare=eng[number].fare;
}

void search_no()
{
  int number;
  float comp;

  ifstream fin;
  fin.open("train.dat", ios::in||ios::beg);
  fin.seekg(0, ios::beg);

  cout<<"Enter Train Number: ";
  cin>>comp;

  flag=0;
  int i=0;
  while(fin.read((char*)&eng[i], sizeof(eng[i])))
  {
   if(comp==eng[i].t_no)
   {
    cout<<"\n\nTRAIN FOUND!!"<<endl;
    cout<<"\nDetails"<<endl;
    cout<<"Train number: "<<eng[i].t_no<<endl;
    cout<<"From: "<<eng[i].from<<endl;
    cout<<"To: "<<eng[i].to<<endl;
    cout<<"Via: "<<eng[i].via<<endl;
    cout<<"Status: "<<eng[i].status<<endl;
    cout<<"Estimated time of arival: "<<eng[i].eta<<endl;
    cout<<"Estimated time of departure: "<<eng[i].etd<<endl;
    cout<<"Platform: "<<eng[i].platform<<endl;
    cout<<"Fare: "<<eng[i].fare<<endl;

    flag=1;
    number=i;
   }
   i++;
  }

  if(flag!=1)
  cout<<"\nNo train found!!";

  billing.ctrain=eng[number].t_no;
  strcpy(billing.cfrom, eng[number].from);
  strcpy(billing.cto, eng[number].to);
  billing.cplatform=eng[number].platform;
  billing.ticketfare=eng[number].fare;
}

void search_train()
{
  int choice;
  char ch;

  do
  {
   if(indic!=1)
   cout<<"\n\nMENU"<<endl;

   cout<<"\n\n1.Search by Train number"<<endl;
   cout<<"2.Search by stations";

   cout<<"\n\nEnter choice: ";
   cin>>choice;

   switch(choice)
   {
    case 1 : search_no();
	     break;
    case 2 : search_des();
	     break;
    default : br=1;
	      oath=5;
	      load();
	      menu();
	      break;
   }

   if(br==1)
   break;

   cout<<"\nDo you want to search again?(Y/N): ";
   cin>>ch;
  }while(ch=='Y'||ch=='y');
}

void menu()           //Main Menu Function
{
 int choice;

 cout<<"\n\nHS Railways corperation\n\n";
 cout<<"1. View current train schedule "<<endl;
 cout<<"2. Search for trains"<<endl;
 cout<<"3. Book Tickets"<<endl;
 cout<<"4. Add train(s)"<<endl;
 cout<<"5. Modify current train schedule"<<endl;
 cout<<"6. Exit "<<endl;
 cout<<"Enter choice: ";
 cin>>choice;

 switch(choice)
 {
  case 1 : oath=2;
	   load();
	   mis.misdisplay();
	   break;
  case 2 : load();
	   search_train();
	   break;
  case 3 : load();
	   billing.avail();
	   break;
  case 4 : load();
	   fobj.enter();
	   break;
  case 5 : load();
	   fobj.modify();
	   break;
  case 6 : oath=6;
	   load();
	   exit(0);
  default : oath=5;
	    load();
	    break;
 }

}


void load()
{
  clrscr();

  _setcursortype(_NOCURSOR);

  switch(oath)
  {
   case 1 : cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	    cout<<"  Returning to menu..."<<endl;
	    break;
   case 2 : cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	    cout<<"  Loading schedule..."<<endl;
	    break;
   case 3 : cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	    cout<<"  Booking Ticket..."<<endl;
	    break;
   case 4 : cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	    cout<<"  Canceling ticket..."<<endl;
	    break;
   case 5 : cout<<"\n\n\n\n\n\n\n\n\n\n";
	    cout<<"  Invalid selection!!"<<endl;
	    cout<<"  Redirecting to menu..."<<endl;
	    break;
   case 6 : cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	    cout<<"  Exiting the program..."<<endl;
	    break;
   case 7 : cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	    cout<<"  Returning to homepage..."<<endl;
	    break;
   default : cout<<"\n\n\n\n\n\n\n\n\n\n\n";
	     cout<<"  Loading..."<<endl;
	     break;
  }

  cout<<"  ";
  for(int i=0; i<70; i++)
  {
    printf("%c",219);
    delay(30);
  }

  oath=0;
  _setcursortype(_NORMALCURSOR);

  cout<<"\n";
  cout<<"  "<<flush;
  system("pause");
  clrscr();
}

void copy()
{
 ifstream fin;
 fin.open("train.dat", ios::in);
 fin.seekg(0, ios::beg);

 ofstream fout;
 fout.open("train1.txt", ios::beg||ios::out);
 fout<<"--------------------------------------------------------------------------"<<endl;
 fout<<setw(50)<<"Train Details";
 fout<<"\n--------------------------------------------------------------------------";

 for(int i=0; i<dem; i++)
 {
  fin.read((char*)&mod, sizeof(mod));
  fout<<"\n\nTrain Number: "<<mod.t_no<<endl;
  fout<<"Estimated time of arrival: "<<mod.eta<<endl;
  fout<<"Estimated time of departure: "<<mod.etd<<endl;
  fout<<"From: "<<mod.from<<endl;
  fout<<"To: "<<mod.to<<endl;
  fout<<"Via: "<<mod.via<<endl;
  fout<<"Platform Number: "<<mod.platform<<endl;
  fout<<"Fare: "<<mod.fare<<endl;
  fout<<"Status: "<<mod.status<<endl;
 }
 fout.close();
 fin.close();
}
void setdem()
{
 ifstream fin;
 fin.open("demno.txt", ios::in,ios::beg);
 fin>>dem;
 fin.close();
}

void main()
{
  clrscr();
  setno();
  setdem();
  fobj.password();
  getch();
}
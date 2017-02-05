#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<conio.h>

using namespace std;

class transport;
class order;
class customer;
class tour_agent;
class admin;
class train;
class flight;
class bus;

class transport
{
	protected:
		string tname;
		string tid;
		string dtime;
		string atime;
		string duration;
		int seats;
		float price;
		string origin;
		string destination;
	public:
		virtual int gettype()=0;
		virtual string getname()=0;
		virtual string getid()=0;
		virtual string getdtime()=0;
		virtual string getatime()=0;
		virtual string getduration()=0;
		virtual int getseats()=0;
		virtual float getprice()=0;
		virtual string getorigin()=0;
		virtual string getdestination()=0;
		virtual string getflightclass(){}
		virtual string getcoach(){}
		virtual string gettypeofbus(){}  
};

class order
{
	string tname;
	string tid;
	string dtime;
	string atime;
	string duration;
	int seats;
	float price;
	string origin;
	string destination;
	int orderid;
	string flightclass;
	string typeofbus;
	string coach;
	int type;
	public:
		void settype(int w)
		{
			type=w;
		}
		order(int c,transport *t,int type)
		{
			orderid=c;
			tname=t->getname();
			tid=t->getid();
			dtime=t->getdtime();
			atime=t->getatime();
			duration=t->getduration();
			seats=t->getseats();
			price=t->getprice();
			origin=t->getorigin();
			destination=t->getdestination();
			if(type==1)
			flightclass=t->getflightclass();
			if(type==3)
			typeofbus=t->gettypeofbus();
			if(type==2)
			coach=t->getcoach();
		}
		string getname(){return tname;}
		string getid(){return tid;}
		string getdtime(){return dtime;}
		string getatime(){return atime;}
		string getduration(){return duration;}
		float getprice(){return price;}
		string getorigin(){return origin;}
		string getdestination(){return destination;}
		int getorderid(){return orderid;}
		void showdetails()
		{	
			if(type==1)
			{
				cout<<"Order details are:\n";
				cout<<"Orderid:"<<orderid<<endl<<"Ordername:"<<tname<<endl<<"TransportId:"<<tid<<endl<<"Departure Time:"<<dtime<<endl<<"Arrival Time:"<<atime<<endl<<"Flight Class:"<<flightclass<<endl<<"Price:"<<price<<endl<<"Origin:"<<origin<<endl<<"Destination:"<<destination<<endl;
			}
			else if(type==2)
			{
				cout<<"Order details are:\n";
				cout<<"Orderid:"<<orderid<<endl<<"Ordername:"<<tname<<endl<<"TransportId:"<<tid<<endl<<"Departure Time:"<<dtime<<endl<<"Arrival Time:"<<atime<<endl<<"Coach:"<<coach<<endl<<"Price:"<<price<<endl<<"Origin:"<<origin<<endl<<"Destination:"<<destination<<endl;
			}
			else if(type==3)	
			{		
				cout<<"Order details are:\n";
				cout<<"Orderid:"<<orderid<<endl<<"Ordername:"<<tname<<endl<<"TransportId:"<<tid<<endl<<"Departure Time:"<<dtime<<endl<<"Arrival Time:"<<atime<<endl<<"Type of bus:"<<typeofbus<<endl<<"Price:"<<price<<endl<<"Origin:"<<origin<<endl<<"Destination:"<<destination<<endl;
			}
		}
};

class customer
{
    string name;
    string loginid;
    string password;
    string email;
    float budget;
    int flag;
    int tbook;
    order *o[100];
    int cnt;
        public: 
        customer(string n,string e,string i,string p,float b):name(n),email(e),loginid(i),password(p),budget(b)
        {
        	cnt=0;
        	tbook=0;
		}
		string getname()
		{
			return name;
		}
		string getloginid()
		{
			return loginid;
		}
		string getpassword()
		{
			return password;
		}
		string getemail()
		{
			return email;
		}    
		float getbudget()
		{
			return budget;
		} 
		int gettbook()
		{
			return tbook;
		}
		void settbook()
		{
			tbook=1;
		}
		template <class T1,class T2>
		int checklogin(T1 l,T2 e)
		{
			if(loginid==l&&email==e)
			return 1;
			return 0;
		}
		void makepayment(transport *t,int w)
		{
			cout<<"Congratulations! You have successfully booked a ticket.";
			budget=budget-t->getprice();
			tbook=1;
			o[cnt]=new order(cnt,t,w);
			o[cnt]->settype(w);
			cnt++;
			flag=1;
		}
		void updatedetails()
		{
			string n,l,p,e;
			int x;
			float b;
			system("cls");
			cout<<"Select your preference"<<endl;
			cout<<"Press 1 to update name"<<endl;
			cout<<"Press 2 to update loginid"<<endl;
			cout<<"Press 3 to update password"<<endl;
			cout<<"Press 4 to update email"<<endl;
			cout<<"Press 5 to update budget"<<endl;
			cin>>x;
			if(x==1)
			{
				cout<<"Enter new name:\n";
				cin>>n;
				name=n;
			}
			else if(x==2)
			{
				cout<<"Enter new loginid:\n";
				cin>>l;
				loginid=l;
			}
			else if(x==3)
			{
				cout<<"Enter new password:\n";
				cin>>p;
				password=p;
			}
			else if(x==4)
			{
				cout<<"Enter new email:\n";
				cin>>e;
				email=e;
			}
			else if(x==5)
			{
				cout<<"Enter new budget:\n";
				cin>>b;
				budget=b;
			}		
			system("cls");
		}
		void vieworderdetails(int i)
		{	if(flag==1)
			o[i]->showdetails();
			else
			cout<<"No order avaiable.";
		}			
		friend ostream& operator<<(ostream &t,customer *o);
};

ostream& operator<<(ostream &t,customer *o)
{
	cout<<"Detais of customer are:\n";
	t<<"Name:"<<o->name<<endl<<"LoginId:"<<o->loginid<<endl<<"Password:"<<o->password<<endl<<"Email:"<<o->email<<endl<<"Budget:"<<o->budget;
	getch();
	system("cls");
}

class tour_agent
{
	static int count;
	string name;
	string id;
	string email;
	int phoneno;
	transport *t[500];
	public:
		tour_agent(string n,string i,string e,int p):name(n),id(i),email(e),phoneno(p)
		{
		}
		void storetransportinfo(transport *tr)
		{
			t[count++]=tr;
		}
		int displayflightinfo(string o,string d)
		{
			int i=0,flag=0;
			for(i=0;i<count;i++)
			{
				if(t[i]->gettype()==1)
				{
					if(t[i]->getorigin()==o&&t[i]->getdestination()==d)
					{
						cout<<t[i]->getname()<<" "<<t[i]->getid()<<" "<<t[i]->getdtime()<<" "<<t[i]->getatime()<<" "<<t[i]->getduration()<<" "<<t[i]->getseats();
						cout<<" "<<t[i]->getprice()<<" "<<t[i]->getorigin()<<" "<<t[i]->getdestination()<<endl;
						flag=1;
					}
				}
			}
			if(flag==0)
			{
				cout<<"No ticket Available:\n";
				return 0;
			}
			return 1;
		}
		
		int displaytraininfo(string o,string d)
		{
			int i=0,flag=0;
			for(i=0;i<count;i++)
			{
				if(t[i]->gettype()==2)
				{
					if(t[i]->getorigin()==o&&t[i]->getdestination()==d)
					{
						cout<<t[i]->getname()<<" "<<t[i]->getid()<<" "<<t[i]->getdtime()<<" "<<t[i]->getatime()<<" "<<t[i]->getduration()<<" "<<t[i]->getseats();
						cout<<" "<<t[i]->getprice()<<" "<<t[i]->getorigin()<<" "<<t[i]->getdestination()<<endl;
						flag=1;
						break;
					}
				}
			}
			if(flag==0)
			{
				cout<<"No ticket Available:\n";
				return 0;
			}
			return 1;
		}
		
		int displaybusinfo(string o,string d)
		{
			int i=0,flag=0;
			for(i=0;i<count;i++)
			{
				if(t[i]->gettype()==3)
				{
					if(t[i]->getorigin()==o&&t[i]->getdestination()==d)
					{
						cout<<t[i]->getname()<<" "<<t[i]->getid()<<" "<<t[i]->getdtime()<<" "<<t[i]->getatime()<<" "<<t[i]->getduration()<<" "<<t[i]->getseats();
						cout<<" "<<t[i]->getprice()<<" "<<t[i]->getorigin()<<" "<<t[i]->getdestination()<<endl;
						flag=1;
						break;
					}
				}
			}
			
			if(flag==0)
			{
				cout<<"No ticket Available:\n";
				return 0;
			}
			return 1;
		}
		
		void bookticket(int type,int index,customer *cu)
		{
			int i;
			string ch;
			cout<<"Enter the id to book ticket";	
			cin>>ch;
			for(i=0;i<count;i++)
			{
				if(t[i]->getid()==ch)
				{	
					if((t[i]->getprice()<=cu->getbudget())&&t[i]->getseats()>0)
					{
						cu->makepayment(t[i],type);
					}
					else if(t[i]->getseats()==0)
					{
						cout<<"No seat avaiable.";
					}
					else
					{
						cout<<"You do not have sufficient balance in your account.\n";
					}
				}
			}
		}
};

class admin
{
	int count;
	string user_name;
	string password;
	string email;
	customer *c[100];
	tour_agent *to;
	transport *t[100];
	public:
		admin(string u,string p,string e,tour_agent *t):user_name(u),password(p),email(e),to(t)
		{
			count=0;
		}
		void storecustomerinfo(customer *cu)
		{
				c[count]=cu;
				count++;
		}
		int customerlogin(string l,string e)
		{
			int i=0;
			while(c[i]->getloginid()!=l)
			i++;
			if(c[i]->getemail()==e)
			return i ;
			else return 0;
		}
		void search(int type,int index,string o,string d,customer *cu)
		{	
			int x,y;
			if(type==1)
			{
				y=to->displayflightinfo(o,d);
			}
			else if(type==2)
			{
				y=to->displaytraininfo(o,d);
			}
			else if(type==3)
			{
				y=to->displaybusinfo(o,d);
			}
			if(y==1)
			{
				cout<<endl<<"Enter 1 to book ticket or 0 to return:\n";
				cin>>x;
				if(x==1)
				{
					to->bookticket(type,index,cu);
				}
			}
		}
		void add_transport()
		{
			string a;
			cout<<"Enter The Type Of Transport You Want To Add";
			cin>>a;
			string tname,tid,dtime,atime,duration,origin,destination;
			int seats;
			float price;	
			
			if(a=="bus"||a=="BUS")
			{
				cout<<"enter the details of the transport : name,id,dtime,atime,duration,seats,price,origin and destination";
				cin>>tname>>tid>>dtime>>atime>>duration>>seats>>price>>origin>>destination;
				fstream obj("bus.txt",ios::app);
				obj<<"\n"<<tname<<" "<<tid<<" "<<atime<<" "<<dtime<<" "<<duration<<" "<<seats<<" "<<price<<" "<<origin<<" "<<destination;
				obj.close();
				cout<<"Data Added Successfully";
			}
		   	else if(a=="train"||a=="TRAIN")
			{
				cout<<"enter the details of the transport : name,id,dtime,atime,duration,seats,price,origin and destination";
				cin>>tname>>tid>>dtime>>atime>>duration>>seats>>price>>origin>>destination;
				fstream obj("train.txt",ios::app);
				obj<<"\n"<<tname<<" "<<tid<<" "<<atime<<" "<<dtime<<" "<<duration<<" "<<seats<<" "<<price<<" "<<origin<<" "<<destination;
				obj.close();
				cout<<"Data Added Successfully";
			}
		    else if(a=="FLIGHT"||a=="flight")
			{
				cout<<"enter the details of the transport : name,id,dtime,atime,duration,seats,price,origin and destination";
				cin>>tname>>tid>>dtime>>atime>>duration>>seats>>price>>origin>>destination;
				fstream obj("flight.txt",ios::app);
            	obj<<"\n"<<tname<<" "<<tid<<" "<<atime<<" "<<dtime<<" "<<duration<<" "<<seats<<" "<<price<<" "<<origin<<" "<<destination;
				obj.close();
				cout<<"Data Added Successfully";
			}
			else
			{
				cout<<"Wrong Choice...!! Please Add Bus,Train Or Flight";
			}
			
		}
};

class train:public transport
{
	string coach;
	public:
		train(string n,string i,string d,string a,string du,int s,float p,string o,string de)
		{
			tname=n;
			tid=i;
			dtime=d;
			atime=a;
			duration=du;
			seats=s;
			price=p;
			origin=o;
			destination=de;
		}
		string getname(){return tname;}
		string getid(){return tid;}
		string getdtime(){return dtime;}
		string getatime(){return atime;}
		string getduration(){return duration;}
		int getseats(){return seats;}
		float getprice(){return price;}
		string getorigin(){return origin;}
		string getdestination(){return destination;}
		int gettype(){ return 2;}
		string getcoach(){return coach;}
};

class flight:public transport
{
	string flightclass;
	public:
		flight(string n,string i,string d,string a,string du,int s,float p,string o,string de)
		{
			tname=n;
			tid=i;
			dtime=d;
			atime=a;
			duration=du;
			seats=s;
			price=p;
			origin=o;
			destination=de;
		}
		string getname(){return tname;}
		string getid(){return tid;}
		string getdtime(){return dtime;}
		string getatime(){return atime;}
		string getduration(){return duration;}
		int getseats(){return seats;}
		float getprice(){return price;}
		string getorigin(){return origin;}
		string getdestination(){return destination;}
		int gettype(){ return 1;}
		string getflightclass(){return flightclass; }
};

class bus:public transport
{
	string typeofbus;
	public:
		bus(string n,string i,string d,string a,string du,int s,float p,string o,string de)
		{
			tname=n;
			tid=i;
			dtime=d;
			atime=a;
			duration=du;
			seats=s;
			price=p;
			origin=o;
			destination=de;
		}
		string getname(){return tname;}
		string getid(){return tid;}
		string getdtime(){return dtime;}
		string getatime(){return atime;}
		string getduration(){return duration;}
		int getseats(){return seats;}
		float getprice(){return price;}
		string getorigin(){return origin;}
		string getdestination(){return destination;}
		int gettype(){return 3;}
		string gettypeofbus(){return typeofbus;}
};

int tour_agent::count=0;

int main()
{
    int ch,i=0,count=0,l,y,tcount=0,budget,seats,x,ono,flag=-1;
    float price;
    string name,email,loginid,password,origin,destination,tname,tid,dtime,atime,duration;
    fstream obj("cust.txt",ios::in);
    customer *cu[100];
    transport *tr[500];
    tour_agent *t=new tour_agent("agent","agent123","agentcool@gmail.com",123456);
    admin *a=new admin("admin","admin123","admin123@gmail.com",t);
    while(!obj.eof())
    {	
    	obj>>name>>email>>loginid>>password>>budget;
    	cu[count++]=new customer(name,email,loginid,password,budget);
		a->storecustomerinfo(cu[count-1]);
	}
	obj.close();
	obj.open("flight1.txt",ios::in);
	while(!obj.eof())
	{
		obj>>tname>>tid>>dtime>>atime>>duration>>seats>>price>>origin>>destination;
		tr[tcount++]=new flight(tname,tid,dtime,atime,duration,seats,price,origin,destination);
		t->storetransportinfo(tr[tcount-1]);
	}
	obj.close();
	obj.open("train2.txt",ios::in);
	while(!obj.eof())
	{
		obj>>tname>>tid>>dtime>>atime>>duration>>seats>>price>>origin>>destination;
		tr[tcount++]=new train(tname,tid,dtime,atime,duration,seats,price,origin,destination);
		t->storetransportinfo(tr[tcount-1]);
	}
	obj.close();
	obj.open("bus.txt",ios::in);
	while(!obj.eof())
	{
		obj>>tname>>tid>>dtime>>atime>>duration>>seats>>price>>origin>>destination;
		tr[tcount++]=new bus(tname,tid,dtime,atime,duration,seats,price,origin,destination);
		t->storetransportinfo(tr[tcount-1]);
	}
	obj.close();
    do
    {
		cout<<"Welcome to Aao ghume.Please select the type of user:\n";
    	cout<<"1.Register as new user\n";
    	cout<<"2.View account as existing user\n";
    	cout<<"3.Login As Admin\n";
    	cout<<"4.Exit\n";
    	cin>>ch;
    	flag=-1;
    	switch(ch)
    	{
        	case 1: {
					obj.open("cust.txt",ios::app);
            		cout<<"Enter name:"<<endl;
            		cin>>name;
            		cout<<"Enter email:"<<endl; 
            		cin>>email;
            		cout<<"Enter loginid:"<<endl;
        	 		cin>>loginid;
   			        cout<<"Enter password:"<<endl;
        		    cin>>password;
        		    cout<<"Enter budget:"<<endl;
        		    try
					{
        		    	cin>>budget;
        		    	if(cin.fail())
        		    	{
							throw "Enter budget correctly";
						}
  		          	}
  		          	catch(const char* msg)
  		          	{	
						cerr<< msg <<endl;
					}				
					obj<<"\n"<<name<<" "<<email<<" "<<loginid<<" "<<password<<" "<<budget;
            		obj.close();
            		cout<<"Account Successfully Created...";
            		getch();
            		system("cls");
            		cu[count++]=new customer(name,email,loginid,password,budget);
            		a->storecustomerinfo(cu[count]);
            		}
            		break;
            		
     	    case 2: {
			 		cout<<"Enter the loginid of customer:\n";
     				cin>>loginid;
     				cout<<"Enter the email of customer:\n";
     				cin>>email;
     				for(y=0;y<count;y++)
     				{
     					if(cu[y]->checklogin(loginid,email))
     					{	
     						cout<<"Login Successful...";
     						flag=1;
     						break;
						}
					}
					if(flag==-1)
					{
						flag=0;
						cout<<"Incorrect email or password...\n";
					}
						if(flag==0)
						{
							getch();
							system("cls");
							break;
						}
						getch();
						system("cls");
						do
						{
						cout<<"Select your preference:"<<endl;
						cout<<"Press 1 to view details"<<endl;
						cout<<"Press 2 to update details"<<endl;
						cout<<"Press 3 to view details of Booking"<<endl;
						cout<<"Press 4 to book tickets"<<endl;
						cout<<"Press 5 to exit"<<endl;
						cin>>ch;
						if(ch==1)
						{
							cout<<cu[y];
						}
						else if(ch==2)
						{
							cu[y]->updatedetails();
						}
						else if(ch==3)
						{
							if(cu[y]->gettbook()==0)
							{
								cout<<"No tickets booked";
								getch();
								system("cls");
							}
							else
							{
								cout<<"Enter orderno:\n";
								cin>>ono;
								cu[y]->vieworderdetails(ono);
							}
						}
						else if(ch==4)
						{
							system("cls");
							cout<<"Enter origin:\n";
							cin>>origin;
							cout<<"Enter destination:\n";
							cin>>destination;
							system("cls");
							cout<<"Select your preference:"<<endl;
							cout<<"Press 1 to search for flights"<<endl;
							cout<<"Press 2 to search for trains"<<endl;
							cout<<"Press 3 to search for bus"<<endl;
							cin>>x;
							if(x==1)
							a->search(1,y,origin,destination,cu[y]);	
							else if(x==2)
							a->search(2,y,origin,destination,cu[y]);
							else if(x==3)
							a->search(3,y,origin,destination,cu[y]);
						}
					}while(ch!=5);
					}
					break;
					
			case 3:   {      
					cout<<"Enter Your Username And Password";
					string Username,Password;
					cin>>Username>>Password;
					if(Username=="admin" && Password=="admin123")
							{
							cout<<"You Have Successfully Logged In As Admin\n";
								a->add_transport();}
						else 
						{cout<<"You Are Not Authorised To Enter As The Administrator\n";}
				break;
				}		
			case 4: break;
		}
	}while(ch!=4);
    return 0;
}

#include "../include/login.h"

string u="zainab";
string p="password";

void changeu(string newu){
	u=newu;
}

void changep(string newp){
	p=newp;
}

uint32 login()
{
	uint32 m=0;
	
	do{
	clearScreen();
	
	print("\nUsername: ");
	string uname=readStr();
	
	if(strEql(uname,u))
	{
		print("\n\nPassword: ");
		string pass= readStr();
		
		if(strEql(pass,p))
		{
			print("\n\n\tLogin successful!");
			for(int i=0;i<15000;i++)
				for(int j=0;j<15000;j++);
			m=1;	
		}
		else{
			print("\n\n\tPassword incorrect!");
			for(int i=0;i<15000;i++)
				for(int j=0;j<15000;j++);
		}
	}
	
	else{
		print("\n\n\tUsername incorrect!");
		for(uint32 i=0;i<15000;i++)
			for(uint32 j=0;j<15000;j++);
	}
		
	}while(m==0);
	
	return m;
}



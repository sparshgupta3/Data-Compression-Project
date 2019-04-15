#include<bits/stdc++.h>
using namespace std;

int main(){
	string st,s;
	cin>>st;
	s=st;
	int l = st.length();
	int *n;
	n = new int[l];
	int i,j,num=0;
	char c;
	
	for(i=0; i<l; i++)
	{
		n[i]=0;
	}
	for(i=0; i<l; i++)
	{
		c=s[i];
		if(c!='_')
		{
			
			for(j=i; j<l; j++)
			{
				if(s[j]==c)
				{
					s[j]='_';
					n[num]++;
						
				}
				
				
			}
			num++;
		}
	}
	
	for(i=0; i<num; i++)
	{
		cout << n[i] << endl ;
	}
	return 0;
}

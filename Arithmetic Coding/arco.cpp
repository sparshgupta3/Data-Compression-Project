#include<bits/stdc++.h>
using namespace std;
struct ar{
	char ch;
	int oc;
};

bool compare(struct ar a1, struct ar a2){
	return (a1.oc>a2.oc);
}

int main(){
	string s,st;
	cin>>st;
	s = st;
	int l = st.length();	
	struct ar* arr = new ar[l];
	int i,j,num=0;
	char c;
	
	for(i=0; i<l; i++)
	{
		arr[i].oc =0;
	}
	for(i=0; i<l; i++)
	{
		c=s[i];
		arr[num].ch = c;
		if(c!='$')
		{
			
			for(j=i; j<l; j++)
			{
				if(s[j]==c)
				{
					s[j]='$';
					(arr[num].oc)++;		
				}
			}
			num++;
		}
	}
	sort(arr,arr+num,compare);
	
	cout<<endl;
	int num1=0,num2=1,de1=1,de2=1;
	int total = l;
	for(int i=0;i<l;i++){
		int j=0;
		int k;
		for(k=0;k<num;k++){
			if(arr[k].ch == st[i])
				break;
			j += arr[k].oc;
		}
		num1 *= total;
		num2 *= total;
		de1 *= total;
		de2 *= total;
		int f = (num2-num1)/total;
		num1 += j*f;
		num2 = num1 + f*arr[k].oc;
		for(int m=0;m<=i;m++){
			cout<<st[m];
		}
		cout<<"\t\t";
		cout<<num1<<"/"<<de1<<"\t\t"<<num2<<"/"<<de2<<endl;
	}
	
}
//BE_A_BEE

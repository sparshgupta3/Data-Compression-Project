#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

struct node{
	char ch;
	float pro;
	int arr[20];
	int top;
};

bool compare(struct node l1,struct node l2){
	return (l1.pro > l2.pro);
}

void shannon(int l,int h,struct node* p){
	//cout <<endl << l << " __" << h;
	float left = 0, right = 0, diff1 = 0, diff2 = 0; 
    int i, k, j; 
    if (((l + 1) == h) || (l == h) || (l > h)) { 
        if (l >= h) 
            return; 
        p[l].arr[++(p[l].top)] = 0; 
        p[h].arr[++(p[h].top)] = 1; 
        return; 
    } 
    else {
    	for (i = l+1; i <= h; i++) 
            right = right + p[i].pro; 
        left = left + p[l].pro; 
        diff1 = left-right; 
        if (diff1 < 0) 
            diff1 = diff1 * -1; 
        j = 1; 
        while(j!=(h-l+1)){
        	left = right = 0; 
        	for(i=l;i<=(j+l); i++){
        		left += p[i].pro;
			}
			for(i=l+j+1;i<=h;i++){
				right += p[i].pro;
			}
        	diff2 = left - right; 
            if (diff2 < 0) 
                diff2 = diff2 * -1; 
            if (diff2 >= diff1) 
                break; 
            diff1 = diff2; 
            j++; 
		}
		j--;
		 
        for (i = l; i <= l+j; i++) 
            p[i].arr[++(p[i].top)] = 0; 
        for (i =l+j + 1; i <= h; i++) 
            p[i].arr[++(p[i].top)] = 1; 
  
        shannon(l, l+j, p); 
        shannon(l+j+1, h, p); 
	}
}

int main(){
	int n;
	cout<<"Enter the number of symbols : ";
	cin>>n;
	int total = 0;
	node* p = new struct node[n];
	cout<<"Enter the symbol and its frequency : \n";
	for(int i=0;i<n;i++){
		cin>>p[i].ch>>p[i].pro;
		total+=p[i].pro;
	}
	for(int i=0;i<n;i++){
		p[i].pro /= total;
	}
	
	sort(p,p+n,compare);
  
    for (int i=0; i<n;i++) 
        p[i].top = -1; 
        
    shannon(0, n-1, p); 
     
    int i, j; 
    cout << "\n\tSymbol\tFrequency\tCode"; 
    for (i = 0; i<n; i++) { 
        cout << "\n\t" << p[i].ch << "\t\t" << (p[i].pro)*total << "\t"; 
        for (j = 0; j <= p[i].top; j++) 
            cout << p[i].arr[j]; 
	}
    return 0; 
}
//5 a 22 b 28 c 15 d 30 e 5

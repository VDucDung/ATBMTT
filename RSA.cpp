#include<bits/stdc++.h>
using namespace std;

//Tinh UCLN
int gcd(int a, int b) {	
	if(b == 0 )
		return a;
	if(a % b == 0)
		return b;
	return gcd(b, a % b);
}

int soNguyenTo(int n)
{
    if (n < 2)    
        return 0;
	if(n == 2)
		return 1;
    for (int i = 2; i <= sqrt((float)n); i ++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

//Tinh nghich dao d = e^-1 mod n
long modInverse(long a, long n) {
	if(gcd(a, n) != 1)
		return 0;
	else {
		int r[50], q[50], x[50], y[50];
	
		r[0] = n; 
		r[1] = a;				
		x[0] = 0; 
		x[1] = 1;
		y[0] = 1; 
		y[1] = 0;
	 
		int i = 1;
		while (r[i] > 1) {
			r[i+1] = r[i-1] % r[i];
			q[i+1] = r[i-1] / r[i];
			x[i+1] = x[i-1] - q[i+1] * x[i];
			y[i+1] = y[i-1] - q[i+1] * y[i];
			i++;
		}
		
		if(x[i] < 0){
			x[i] += n;
		}	
		return x[i];
	}	
}

//Tinh a^b mod n
long mod(int a, int b, int n) {
	int temp[50];
	int k = 0; 
	
    while (b > 0) {  
        temp[k] = b % 2; 
        b = b / 2; 
        k++; 
    }

    long f = 1;
    
    for(int i = k-1; i >= 0; i--) {
    	f = (f * f) % n;
    	if(temp[i] == 1)
    		f = (f * a) % n;
	}
    return f;
}

int main() {
	int p, q;

	cout<<"Nhap 2 so nguyen to: "<<endl;
	do {
		cout<<"p = ";
		cin>>p;
	} while(!soNguyenTo(p));

	do {
		cout<<"q = ";
		cin>>q;
	} while(!soNguyenTo(q));

	int n = p * q;
	int phi_n = (p - 1) * (q - 1);
	
	//Tim e sao cho 1 < e < phi_n 
	int e;
	cout<<"e = ";
	cin>>e;
	if(gcd(e, phi_n) != 1){
		cout<<"gcd(e, phi_n) khac 1, thay doi gia tri cua e"<<endl;
		while(e < phi_n) {
			if(gcd(e, phi_n) == 1)
				break;
			else 
				e++;
		}	
		cout<<"e = "<<e<<endl;
	}
	
	//Dung thuat toan Euclid mo rong tinh d (1 < d < phi_n)
	int d = modInverse(e, phi_n);
	cout<<"d = "<<d<<endl;
	
	cout<<"Public key (n, e) = ("<<n<<", "<<e<<")"<<endl;
	cout<<"Private key (n, d) = ("<<n<<", "<<d<<")"<<endl;

	//Ban ma de cho17
	int m;
	cout<<"m = ";
	cin>>m;

	//Ma hoa 
	int c = mod(m, e, n);
	cout<<"Ban ma: c = "<<c<<endl;
	
	//Giai ma
	int giaima = mod(c, d, n);
	cout<<"Ban ro: m = "<<giaima<<endl;
	
}
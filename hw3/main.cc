#include <cstdio>
#include <cstdlib>

#include <sort.h>
#include <timer.h>
#include <random_generator.h>

bool  check_digit_sorted(int l, int r,int d,int ** A,int n);
void  my_insertion_sort(int** A,int n,int l, int r,int* A_len,int d);
void  my_radix_sort_insert(int** A,int n,int l, int r,int* A_len);
void  my_counting_sort(int** A,int** B,int d,int * A_len, int m,int n);
void  my_radix_sort_counting(int** A,int** B,int * A_len, int m,int n);
int** my_create_ivector(int n, int m);
void  my_swap(int ** p1,int ** p2);

	
int main(int argc, char* argv[])
{ 
	int ** ints;
	int ** B;
	int*  A_len;
	int n,m,d;
	int choice,s,debug,cc,test;
	timer t;
	
	cout<<"choose purpose:\n" 
		<<"1->test insertion sort according to d-th digit\n"
		<<"2->radix sort using modified insertion sort\n"
		<<"3->test counting sort according to d-th digit\n"
		<<"4->radix sort using counting sort\n"
		<<"5->naive insertion sort\n";
	cin>>choice;
	
	if(choice==1||choice==2||choice==3||choice==4||choice==5)
		;
	else {
		cout<<"invalid choice\n";
		return -1;
	}

	d=0;		
	s=0;
	debug=0;
	test = 0;
	cout<<"input n: ";
	cin>>n;
	cout<<"input m: ";
	cin>>m;
	cout<<"play small? 1->Yes 0->No  : ";
	cin>>s;	
	if ((s!=0)&&(s!=1)) {
		cout<<"invalid play small choice\n";
		return -1;		
	}
	if(m>=5) {
		cout<<"show first 5 for debugging? 1->Yes 0->No ";
		cin>>debug;		
	}
	if (choice==1||choice==3) {
		cout<<"input d:";
		cin>>d;	
		if ((d>3)||(d<0)) {
			cout<<"invalid d\n";
			return -1;
		}
	}
	cout<<"test times:? ( for measuring runtime performance) ";
	cin>>test;
    
    for (int u = 0; u<test; u++) {
        
    
	ints = create_random_ivector(n,m,s);	
	A_len = new int[m];			
	switch(choice){
		case 1: { 
		/* insertion sort according to d-th digit */
			t.start();
			for (int i=0; i<m;i++ ) {
				A_len[i] = ivector_length(ints[i],n);
			}
			my_insertion_sort(ints,n,0, m-1,A_len,d);
			t.stop();
			cout<<"digit "<<d<<" check: ";
			cout<<(check_digit_sorted(0, m-1,d,ints,n)==true ? "sorted":"not sorted")<<endl;
		
		} break;
		case 2: {
		/* radix sort using modified insertion sort */	
			t.start();
			for (int i=0; i<m;i++ ) {
				A_len[i] = ivector_length(ints[i],n);
			}
			my_radix_sort_insert(ints,n, 0, m-1, A_len);
			t.stop();
			cout<<"radix insert sort check: ";	
			cout<<(check_sorted(ints, n, 0, m-1)==true ? "sorted":"not sorted")<<endl;	
		
		} break;
		case 3: {
		/* counting sort according to d-th digit */
            B = my_create_ivector(n,m);	
			t.start();
			for (int i=0; i<m;i++ ) {
				A_len[i] = ivector_length(ints[i],n);
			}
			my_counting_sort(ints,B,d, A_len,m,n);
			t.stop();
			cout<<"digit "<<d<<" check: ";
			cout<<(check_digit_sorted(0, m-1,d,ints,n)==true ? "sorted":"not sorted")<<endl;
            for (int cc=0;cc<m;cc++) {
                delete[] B[cc];
            }
            delete[] B;
		
		} break;
		case 4: {
		/* radix sort using counting sort */
        	B = my_create_ivector(n,m);	
			t.start();
			for (int i=0; i<m;i++ ) {
				A_len[i] = ivector_length(ints[i],n);
			}
			my_radix_sort_counting(ints,B,A_len,m,n);
			t.stop();
			cout<<"radix counting sort check: ";	
			cout<<(check_sorted(ints, n, 0, m-1)==true ? "sorted":"not sorted")<<endl;
            for (int cc=0;cc<m;cc++) {
                delete[] B[cc];
            }
            delete[] B;
		
		} break;
		case 5: {
		/* naive insertion sort */
			t.start();
			insertion_sort(ints, n, 0, m-1);
			t.stop();		
			cout<<"naive insert sort check: ";	
			cout<<(check_sorted(ints, n, 0, m-1)==true ? "sorted":"not sorted")<<endl;	
			}break;
		default: break;	// not reachable
	}

	if((debug!=0)&&(m>=5)) {
		cout<<"print first 5 integers for debugging:\n";
		for (cc=0;cc<5;cc++) {
			cout.width(3);
			cout<<cc<<" => ";
			cout.width(4);
			cout<<length_digit(ivector_length(ints[cc],n),3)<<" : ";	
			cout.width(4);
			cout<<length_digit(ivector_length(ints[cc],n),2)<<" : ";
			cout.width(4);
			cout<<length_digit(ivector_length(ints[cc],n),1)<<" : ";
			cout.width(4);
			cout<<length_digit(ivector_length(ints[cc],n),0)<<endl;	
		}
	}
	
	cout << "time: " << t << endl;
		
	for (cc=0;cc<m;cc++) {
		delete[] ints[cc];
	}
	
	delete[] ints;
	delete[] A_len;
        
    }

  	return 0;
}

bool check_digit_sorted(int l, int r,int d,int ** A,int n)
{
  for (int i = l+1; i <= r; i++)
    if (length_digit(ivector_length(A[i-1],n), d) > length_digit(ivector_length(A[i],n), d))
      return false;
  return true;
}

void my_insertion_sort(int** A,int n,int l, int r,int* A_len,int d)
{ 
	register int i;
	int* key;
	int len,temp;

	for (int j = l+1; j <= r; j++) {
		key = A[j];
		len = length_digit(A_len[j], d);
		temp = ivector_length(A[j],n);
		i = j - 1;
		while ((i >= l) && (length_digit(A_len[i], d)>len)) {
			A[i+1] = A[i];
			A_len[i+1] = A_len[i];
			i = i - 1;
		}
    	A[i+1] = key;
		A_len[i+1] = temp;
    }
}

void my_radix_sort_insert(int** A,int n,int l, int r,int* A_len)
{
	for (int i=0;i<4;i++) {
		my_insertion_sort(A,n, l, r,A_len,i);
	}
}

int** my_create_ivector(int n, int m)
{
  int i,k;
  int** iv_array;
  iv_array = create_ivector(n, m);
  for (i=0; i < m; i++) {
	for (k=0 ; k<n ; k++) {
		iv_array[i][k]=0;		
	}	
  }
  return iv_array;
}

void my_counting_sort(int** A,int** B, int d,int * A_len, int m,int n)
{
	int* d_len;
	int* C;
	int* temp;
	int j,k,cont;	
	C = new int[256];	
	d_len = new int[m];
	
	for(int c=0;c<m;c++) {
		d_len[c] = length_digit(A_len[c],d);
	}	
	for(k=0;k<256;k++)
		C[k]=0;
	for(j=0;j<m;j++)
		C[d_len[j]]++;
	for(k=1;k<256;k++)
		C[k]+=C[k-1];
	
	for(j=m-1;j>=0;j--) {
		my_swap(&B[C[d_len[j]]-1],&A[j]);
		C[d_len[j]]--;
	}
	
	for (int i=0; i<m;i++ ) {
		my_swap(&A[i],&B[i]);
		A_len[i] = ivector_length(A[i],n);	
	}
	
	delete[] C;
	delete[] d_len;
}

void my_radix_sort_counting(int** A, int** B,int * A_len, int m,int n)
{	
	for (int i=0;i<4;i++) {
		my_counting_sort(A,B,i, A_len,m,n);
	}
}

void my_swap(int **p1, int **p2){
    int *temp;
    temp=*p1;
    *p1=*p2;
    *p2=temp;
}

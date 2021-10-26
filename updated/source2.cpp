#include<bits\stdc++.h>

using namespace std;



struct header{
	unsigned long long bits;
	int symbols;
	unsigned char symbol_code[256];
	char encoded_code[256][256];
};


int main()
{
	string filename;
	cout<<"ENTER FILENAME: ";
	cin>>filename;

	header h;
	
	h.symbols  = 0;
	h.bits = 0;
	memset(h.encoded_code, 0, 256*256);

	fstream f1;
	f1.open("dest_info.bin", ios::in | ios::out | ios::binary);
	f1.read( (char*)&h , sizeof(h));

	
	unordered_map<string , int > hash;
	for(int i= 0; i<h.symbols; ++i)
	{
		string s = "";
		for(int j=0; h.encoded_code[i][j] != '\0'; ++j)
			s += h.encoded_code[i][j];

		hash[s] = h.symbol_code[i];
	}

	for(auto itr: hash)
		cout<<itr.first<< " "<< itr.second<<endl;


	cout<<"done with info\nreading and writing now\n";

	fstream f2;
	f2.open("dest.bin", ios::in | ios::out | ios::binary);


	fstream f3;
	f3.open(filename,  ios::out | ios::binary);

	unsigned long long read_bits = 0;
	string s = "";

	while(read_bits != h.bits)
	{
		unsigned char x;
		f2.read((char*)&x, 1);

	//	cout<<(int)x;

		if(h.bits - read_bits < 8)
		{
			cout<<"hell yeah\n";
			for(int i = h.bits - read_bits  - 1; i>=0; --i )
			{
				if( x & (1<<i)  ) s+='1';
				else s+='0';

				if(hash.find(s)!=hash.end()){
					f3.write((char*)&hash[s], 1 ) ; 
					s = "";
				}

				read_bits++;
			}
		}
		else{
			for(int i= 7 ; i>=0 ; --i)
			{
				if(x & ( 1<<i ) )  s += '1';
				else s += '0';

				if(hash.find(s)!=hash.end()){
					f3.write((char*)&hash[s], 1 ) ; 
					s = "";
				}

				read_bits ++ ; 
			}
		}
	}

	cout<<"done\n";

	return 0;
}
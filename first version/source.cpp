#include<bits\stdc++.h>

using namespace std;


struct header{
	unsigned long long bits;
	int symbols;
	unsigned char symbol_code[256];
	char encoded_code[256][256];
};

class comp{

public:
	bool operator () ( const pair<int,int> &p1,  const pair<int,int> &p2 )
	{
		return p1.first > p2.first;
	}
};

int main () 
{
	string filename;
	cout<< "ENTER FILENAME: ";
	cin>>filename;

	header h;

	h.symbols  = 0;
	h.bits = 0;
	memset(h.encoded_code, 0, 256*256);

	fstream f1;
	f1.open(filename, ios::in | ios::binary);


	fstream f2;
	f2.open("dest.bin", ios::out | ios::trunc | ios::binary );

	fstream f3;
	f3.open("dest_info.bin", ios::out | ios::trunc | ios::binary );

	map<int, int> hash, hash1;
	priority_queue< pair<int , int> , vector<pair<int,int>> , comp >   pq;

	unsigned char x;
	while(!(f1.eof()) )
	{	
		f1.read((char*)&x, 1);
		

			hash[(int) x ] ++;
	}	


	if(hash[(int)x] == 1) hash.erase((int)x);
	else hash[(int)x]--;

	for(auto itr: hash)
	{
		pq.push(make_pair(itr.second , itr.first));
	}


	int index = 256;
	vector<vector<int>> g(1000);

	while(pq.size() > 1)
	{
		pair<int, int>a = pq.top(); pq.pop(); 
		pair<int, int>b = pq.top(); pq.pop();

		g[index].push_back(a.second);
		g[index].push_back(b.second);

		pq.push( make_pair(a.first+b.first , index )  );
		index++;
	}	
	index--;


	stack< pair<int,string> > s1;
	s1.push ( make_pair(index , "" ) );

	while(s1.size()){
		int elem = s1.top().first;
		string s = s1.top().second;
		s1.pop();

		for(int i=0; i<g[elem].size(); ++i)
		{
			if(i==0)
			s1.push(make_pair(g[elem][i] , string(s + "0") ) );
			else
			s1.push(make_pair(g[elem][i] , string(s + "1") ) );
		}

		if(g[elem].size()== 0)
		{

				cout<<elem << " " << s<<endl;
				h.symbol_code[h.symbols]  = elem; 

				for(int i =0 ; i < s.size(); ++ i )
				{
					if(s[i] == '0') h.encoded_code[h.symbols][i] = '0'; 
					else h.encoded_code[h.symbols][i] = '1';
				}

				hash1[elem] = h.symbols;

				h.symbols++;
		}

	}

	cout<<"tree done\n";
	cout<<"reading, processing from tree and writing..\n";
	
	f1.clear();
	f1.seekg(ios::beg);

	int bit_counter = 0;
	unsigned char box=0;
	while(!(f1.eof()) )
	{	

		unsigned char x;
		f1.read((char*)&x, 1);
		
		if(!f1.good())
			break;

		int pos = hash1[(int)x];



		for(int i =0 ; h.encoded_code[pos][i]!='\0'; ++i )
		{
			if(bit_counter==8){
				f2.write( (char*)&box, 1 );
	//			cout<<(int)box<<" ";

				h.bits = h.bits + 8;
				bit_counter = 0;
				box = 0;
			}
			
			box = (box << 1) + 1 * (h.encoded_code[pos][i] == '1') ; 
			bit_counter++;	

		}
		
	}	

//	cout<<(int)box<<" ";
		h.bits = h.bits + bit_counter;
		f2.write( (char*)&box, 1 );
	f3.write((char*)&h, sizeof(h));


	cout<<"done everything";

	return 0;
}



/*
int main () 
{
	header h;
	
	unsigned char x[256];
	for(int i=0; i<256; ++i) x[i] = (unsigned char)(i);

	fstream f; 
	f.open("C:\\Users\\Kunwar Pratap Singh\\Desktop\\huffman\\filew.bin", ios::out | ios::in | ios::trunc | ios::binary );
	f.write((char*)&h, sizeof(h));
	f.write((char*)x, 256);

	f.seekg(0);

	unsigned char y[256];
	
	f.read((char*)&h, sizeof(h));
	f.read((char*)y, 256);

	for(int i=0;i< 256; ++i ) cout << (int) y[i] << endl; 

	f.close();



	return 0;
}

*/

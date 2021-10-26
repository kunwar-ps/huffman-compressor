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

char str[256]; // for dfs

void dfs( int height , vector<vector<int>> &g, int elem )
{
		for(int i=0; i<g[elem].size(); ++i)
		{
			if(i==0)
			{
				str[height] = '0';
				dfs(height+1, g, g[elem][i]);
				str[height] = 0;
			}
			else
			{
				str[height] = '1';
				dfs(height+1, g, g[elem][i]);
				str[height] = 0;
			}
		}

		if(g[elem].size()== 0)
		{

				cout<<elem << " " ;
				for(int i=0; str[i]!='\0'; ++i) cout<<str[i];
				cout<<endl;
			/*
				h.symbol_code[h.symbols]  = elem; 

				for(int i =0 ; s[i]!= 0;  ++ i )
				{
					if(str[i] == '0') h.encoded_code[h.symbols][i] = '0'; 
					else h.encoded_code[h.symbols][i] = '1';
				}

				hash1[elem] = h.symbols;

				h.symbols++;

			*/
		}
}


class streamer{

public:
	unsigned char streamer_buffer[1000000];// 0 - 999999
	int pos;

	streamer()
	{
		pos = 0;
	}

	void add(unsigned char box,  fstream &f)
	{
		if(pos!=999999)
		{
			streamer_buffer[pos++] = box;
		}
		else{
			streamer_buffer[pos] = box;
			f.write((char*)streamer_buffer, 1000000 );
			pos = 0 ;
		}
	}

	void flush(fstream &f)
	{
		for(int i= 0; i< pos ; ++i )
		{
			f.write((char*) &streamer_buffer[i], 1 );
		}
	}
};


int main () 
{
	memset(str, 0, 256); // for  dfs 

	streamer stream_object; 

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


	vector<int> hash(300, 0 ), hash1(300, 0);
	priority_queue< pair<int , int> , vector<pair<int,int>> , comp >   pq;

/*
	unsigned char x;
	while(!(f1.eof()) )
	{	
		f1.read((char*)&x, 1);
		

			hash[(int) x ] ++;

		//cout<<(int)x<<endl;
	}	
	hash[(int)x]--;
	return 0;
	cout<<"done reading\n";
*/


	unsigned char x;
	unsigned char buffer[10005]; 
	while(!(f1.eof()) )
	{	
		

		f1.read((char*)buffer, 10000);
		
		for(int i=0; i<f1.gcount(); ++i)
		{
			hash[(int) buffer[i] ] ++;
			x = buffer[i];
		}
		
	}	


	cout<<"done reading\n";

	
//	if(hash[(int)x] == 1) hash.erase((int)x);
//	else hash[(int)x]--;



	for(int i= 0; i<300 ; ++i)
	{
		if(hash[i] !=0 )
			pq.push(make_pair( hash[i] , i ));
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
		f1.read((char*)buffer, 10000);
		
		for(int i=0; i<f1.gcount(); ++i)
		{
			x = buffer[i];
		

	//	unsigned char x;
	//	f1.read((char*)&x, 1);
	//	
	//	if(!f1.good())
	//		break;

			int pos = hash1[(int)x];



			for(int i =0 ; h.encoded_code[pos][i]!='\0'; ++i )
			{
				if(bit_counter==8){
		
					stream_object.add( box , f2 );

		//			f2.write( (char*)&box, 1 );
		//			cout<<(int)box<<" ";

					h.bits = h.bits + 8;
					bit_counter = 0;
					box = 0;
				}
			
				box = (box << 1) + 1 * (h.encoded_code[pos][i] == '1') ; 
				bit_counter++;	

			}

		}
		
	}	

//	cout<<(int)box<<" ";
		h.bits = h.bits + bit_counter;
		stream_object.add( box , f2);


		stream_object.flush(f2);
	
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

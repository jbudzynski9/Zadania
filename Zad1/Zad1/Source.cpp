#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;


string toHex(char C) {

	stringstream sstream;
	sstream << hex << C;
	return sstream.str();

}


int numberOfOnes(int c) {
	switch (c) {
	case 0: return 0;
	case 1: return 1;
	case 2: return 1;
	case 3: return 2;
	case 4: return 1;
	case 5: return 2;
	case 6: return 2;
	case 7: return 3;
	case 8: return 1;
	case 9: return 2;
	case 10: return 2;
	case 11: return 3;
	case 12: return 2;
	case 13: return 3;
	case 14: return 3;
	case 15: return 4;
	}
}

int toInt(char c) {
	switch (c) {
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'A': return 10;
	case 'B': return 11;
	case 'C': return 12;
	case 'D': return 13;
	case 'E': return 14;
	case 'F': return 15;
	}
}

struct packed {
	unsigned char a : 4, b : 4;
};

int main() {

	cout << "Podaj nazwe pliku z formatem (example.txt): ";

	string fileName;
	cin >> fileName;
	

	ifstream inFile;
	inFile.open(fileName);

	if (!inFile.good())
		cout << "nie mozna odczytac pliku" << endl;

	stringstream buffer;
	buffer << inFile.rdbuf();
	string chars = buffer.str();
	inFile.close();
	packed p;

	string charsFiltered;
	vector<string>bytes;
	vector<packed>even;
	vector<packed>odd;
	vector<packed>newBytes;
	string temp;
	
	
	for (int i = 0; i < chars.length(); i++) {
		if (chars.at(i) > 47 &&chars.at(i) < 58 || chars.at(i) > 64 && chars.at(i) < 71) {
			charsFiltered.push_back(chars.at(i));
		}
	}
	for (int i = 0; i < charsFiltered.length(); i += 2) {
		if (i == charsFiltered.length() - 1) {
			p.a = 0;
			p.b = toInt(charsFiltered.at(i));
		}
		else {
			
			p.a = toInt(charsFiltered.at(i));
			p.b = toInt(charsFiltered.at(i + 1));
		}
		newBytes.push_back(p);
	}

	for (int i = 0; i < newBytes.size(); i++) {
		int onesL = numberOfOnes((int)newBytes[i].a);
		int onesR = numberOfOnes((int)newBytes[i].b);
		int sum = onesL + onesR;
		if (sum % 2 == 0)
			even.push_back(newBytes[i]);
		else
			odd.push_back(newBytes[i]);
	}

	for (int i = 0; i < even.size()-1; i++)
		for (int j = 0; j < even.size()-1; j++)
			if ((int)even[j].a > (int)even[j + 1].a)
				swap(even[j], even[j + 1]);
			else if ((int)even[j].a == (int)even[j + 1].a && (int)even[j].b > (int)even[j + 1].b)
				swap(even[j], even[j + 1]);

	for (int i = 0; i < odd.size() - 1; i++)
		for (int j = 0; j < odd.size() - 1; j++)
			if ((int)odd[j].a >(int)odd[j + 1].a)
				swap(odd[j], odd[j + 1]);
			else if ((int)odd[j].a == (int)odd[j + 1].a && (int)odd[j].b >(int)odd[j + 1].b)
				swap(odd[j], odd[j + 1]);



	ofstream outFile("result.txt");
	outFile << "Even number of ones (ascending):" << endl;;
	for (int i = 0; i < even.size(); i++)
		outFile << hex << uppercase <<(int)even[i].a << hex << uppercase << (int)even[i].b << endl;

	outFile << endl;
	outFile << "Odd number of ones (descending):"<<endl;
	for (int i = odd.size()-1;i>-1;i--)
		outFile << hex << uppercase << (int)odd[i].a << hex << uppercase << (int)odd[i].b << endl;

	outFile << endl;
	outFile.close();	

	system("pause");
	return 0;
}
#include<iostream>
#include<conio.h>
#include<vector>
#include<string>


using namespace std;

int main() {

	int testCases, elements;
	
	cout << "Number of test cases: "<<endl;
	cin >> testCases;
	vector<string> isEqual;

	for (int i = 0; i < testCases; i++) {
		int flagEqual = 0;
		cout << "Number of elements: " << endl;
		cin >> elements;
		cout << "Insert " << elements << " elements:" << endl;
		vector<int> numbers;		

		for (int j = 0; j < elements; j++) {
			int element;			
			cin >> element;
			numbers.push_back(element);
		}

		for (int j = 0; j < elements; j++) {
			int sumL = 0, sumR = 0;
			for (int k = 0; k < elements; k++) {
				if (k < j) {
					sumL += numbers[k];
				}
				if (k > j) {
					sumR += numbers[k];
				}
			}

			if (sumL == sumR) {				
				flagEqual = 1;
				break;
			}
		}

		if (flagEqual == 1) 
			isEqual.push_back("Yes");
		else 
			isEqual.push_back("No");
		

	}

	for (int j = 0; j <testCases; j++) {
		cout << isEqual[j] << endl;
	}

	system("pause");

	return 0;

}

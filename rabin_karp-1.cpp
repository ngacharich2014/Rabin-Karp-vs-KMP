/* Following program is a C++ implementation of Rabin Karp */

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;


static const char alphanum[] =
"AB";
int stringLength = sizeof(alphanum) - 1;

using std::cout;
using std::endl;
// d is the number of characters in the input alphabet 
#define d 256 

/* pat -> pattern
txt -> text
q -> A prime number
*/
void search(char pat[], char txt[], int q)
{
	int M = strlen(pat);
	int N = strlen(txt);
	int i, j;
	int p = 0; // hash value for pattern 
	int t = 0; // hash value for txt 
	int h = 1;

	// The value of h would be "pow(d, M-1)%q" 
	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;

	// Calculate the hash value of pattern and first 
	// window of text 
	for (i = 0; i < M; i++)
	{
		p = (d * p + pat[i]) % q;
		t = (d * t + txt[i]) % q;
	}

	// Slide the pattern over text one by one 
	for (i = 0; i <= N - M; i++)
	{

		// Check the hash values of current window of text 
		// and pattern. If the hash values match then only 
		// check for characters on by one 
		if (p == t)
		{
			/* Check for characters one by one */
			for (j = 0; j < M; j++)
			{
				if (txt[i + j] != pat[j])
					break;
			}

			// if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1] 
			if (j == M)
				cout << "Pattern found at index " << i << endl;
		}

		// Calculate hash value for next window of text: Remove 
		// leading digit, add trailing digit 
		if (i < N - M)
		{
			t = (d*(t - txt[i] * h) + txt[i + M]) % q;

			// We might get negative value of t, converting it 
			// to positive 
			if (t < 0)
				t = (t + q);
		}
	}
}

char genRandom()  // Random string generator function.
{

	return alphanum[rand() % stringLength];
}


/* Driver code */
int main()
{

	for (int i = 0; i < 5; i++) {
		
		char txt[50] = { 0 };
		char pat[] = "ABB";

		for (int z = 0; z < 50; z++)
		{
			txt[z] = genRandom();

		}

		for (int j = 0; j < 3; j++)
		{
			pat[j] = genRandom();

		}

		int q = 101; // A prime number 

		/* Recording the starting clock tick.*/
		auto start = chrono::high_resolution_clock::now();
		search(pat, txt, q);
		// Recording the end clock tick. 
		auto end = chrono::high_resolution_clock::now();
		// Calculating total time taken by the program. 
		double time_taken =
			chrono::duration_cast<chrono::nanoseconds>(end - start).count();

		time_taken *= 1e-9;

		cout << "Time taken by program is : " << fixed
			<< time_taken << setprecision(9);
		cout << " sec" << endl;

		cout << "txt: ";
		for (int i = 0; i < 50; i++) {
			cout << txt[i];
		}

		cout << "\npat: ";
		for (int j = 0; j < 3; j++) {
			cout << pat[j];
		}
		cout << endl;
	}
	return 0;
}



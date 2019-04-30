/* Following program is a C++ implementation of KMP */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <chrono>
#include <iomanip>

using namespace std;

static const char alphanum[] =
"AB";
int stringLength = sizeof(alphanum) - 1;

void computeLPSArray(char* pat, int M, int* lps);

// Prints occurrences of txt[] in pat[] 
void KMPSearch(char* pat, char* txt)
{
	

	
	int M = strlen(pat);
	int N = strlen(txt);
	
	// create lps[] that will hold the longest prefix suffix 
	// values for pattern 
	int lps[3];

	// Preprocess the pattern (calculate lps[] array) 
	computeLPSArray(pat, M, lps);

	int i = 0; // index for txt[] 
	int j = 0; // index for pat[] 
	while (i < N) {
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {
			printf("Found pattern at index %d \n", i - j);
			j = lps[j - 1];
		}

		// mismatch after j matches 
		else if (i < N && pat[j] != txt[i]) {
			// Do not match lps[0..lps[j-1]] characters, 
			// they will match anyway 
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}


	
	
}

// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSArray(char* pat, int M, int* lps)
{
	// length of the previous longest prefix suffix 
	int len = 0;

	lps[0] = 0; // lps[0] is always 0 

				// the loop calculates lps[i] for i = 1 to M-1 
	int i = 1;
	while (i < M) {
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else // (pat[i] != pat[len]) 
		{
			// This is tricky. Consider the example. 
			// AAACAAAA and i = 7. The idea is similar 
			// to search step. 
			if (len != 0) {
				len = lps[len - 1];

				// Also, note that we do not increment 
				// i here 
			}
			else // if (len == 0) 
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

char genRandom()  // Random string generator function.
{

	return alphanum[rand() % stringLength];
}

// Driver program to test above function 
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

		/* Recording the starting clock tick.*/
		auto start = chrono::high_resolution_clock::now();
		KMPSearch(pat, txt);
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
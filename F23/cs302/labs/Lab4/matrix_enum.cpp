/*
 * Mung-Shu Shen
 * yvy976
 * Lab 4: Enumeration
 * 09/20/2023
 * Enumerates all possible positions of 'x','e', and '.' via double recursion 
 */ 

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

void choose(char &h, int e, int &w, int index, vector <int> &v, vector <vector < char > > &m)
{
	if ((int)v.size() - index <  e) return;
	
	// print the matrix
	if (e == 0)
	{
		for (int i = 0; i < (int)m.size(); i ++)
		{
			int s = 0;
			for (int j = 0; j < (int)m[i].size(); j ++)
			{
				if (h == 'h')
				{
					if (m[i][j] == 'E' || m[i][j] == 'X') s += 1 << j;

				}
				else { cout << m[i][j];}
			}
			if (h == 'h') printf("%x", s);
			cout << endl;
		}
		cout << endl;
		return;
	}

	// enumerate the positions of 'e'
	if (e > 0)
	{
		m[v[index] / w][v[index] % w] = 'E';
		choose(h,e-1,w,index + 1, v, m);
		m[v[index] / w][v[index] % w] = '.';
		choose(h,e,w,index + 1, v, m);
	}
}
void permute(char &h, int e, int &w,vector < int > &v,int index)
{
	int i, j, temp;

	if (index == (int) v.size())
	{

		vector < vector < char > > matrix;
		matrix.resize(w);
		vector <int> d;
		for (int t = 0; t < w; t ++) matrix[t].resize(w,'.');

		// mapping 'x' positions to matrix
		for (j = 0; j < (int) v.size(); j ++) matrix[j][v[j]%w] = 'X';


		// finding the '.'
		for (j = 0; j < (int) w; j ++)
		{
			for (i = 0; i < (int) w; i ++)
			{
				if (matrix[j][i] == '.')
				{
					d.push_back((j*w+i));

				}
			} 

		}
		// enumerate the matrix with d.size possible positions for 'e'
		choose(h,e,w,0,d,matrix);
		return;
	}

	// recursive call
	for (i = index; i < (int) v.size(); i ++)
	{
		temp = v[i];
		v[i] = v[index];
		v[index] = temp;

		permute(h,e,w,v,index + 1 );

		temp = v[i];
		v[i] = v[index];
		v[index] = temp;
	}
}


int main(int argc, char ** argv)
{
	if (argc != 4)
	{
		return -1;
	}

	int w, e;
	char f;
	int i; 

	w = stoi(argv[1]);
	e = stoi(argv[2]);
	f = argv[3][0];
	vector < vector < vector < char > >  >big;
	vector < vector < int > > x_pos;
	vector < int > x;

	// vector of 0,1,2,...w-1
	for (i = 0; i < w; i ++) x.push_back(i);

	// dat fat double recursive call
	permute(f,e,w,x,0);
	return 0;
}









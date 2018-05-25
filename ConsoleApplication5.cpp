// ConsoleApplication5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
#include<algorithm>
#include <random>
#include "math.h"
using namespace std;
void createInitial(bool* bit,int n){
	for (int i = 0; i < n; i++){
		int random = rand() % 2;
		bit[i] = random;
	}
}
int eval(bool* bit, int n,int *a){
	int sum = 0;
	for (int i = 0; i < n; i++){
		
		if (bit[i] == 1){
			sum += a[i];
		}
		
		
	}
	return sum;
}
void update(bool** bit, int& idx,int index, int n){
	for (int i = 0; i < n; i++){
		bit[idx][i] = bit[index][i];
	}
	idx++;
}

void exchange(bool** bit, int i, int j, int n, int type){

	for (int idx = type*(n/4); idx < (type+1)*n / 4; idx++){
		int temp = bit[j][idx];
		bit[j][idx] = bit[i][idx];
		bit[i][idx] = temp;
	}
}
void  variation(bool* bit, int n){
	int random = rand() % n;
	bit[random] = (bit[random] + 1) % 2;
}
int main()
{
	int k, n;
	
	cin >> k >> n;
	int num = n * 100000;
	int* a = new int[n];
	int* b = new int[n];
	bool** bit = new bool*[num];
	for (int i = 0; i < num; i++){
		bit[i] = new bool[n];
	}
	for (int i = 0; i < n; i++){
		cin >> a[i] >> b[i];
	}
	for (int i = 0; i < num; i++){
		createInitial(bit[i], n);
	}
	//迭代次数
	int iter = 0;
	int available = num;
	while (iter < 100){
		int idx = 0;
		int type = 0;
		for (int i = 0; i < available; i++){
			int weight = eval(bit[i], n, a);
			//cout << weight << endl;
			
			if (weight <= k){
				update(bit, idx, i, n);
			}
			else if (k - weight < 10){
				variation(bit[i], n);
			}
		}
	
		//exchange
		for (int i = 0; i < idx; i += 2){
			exchange(bit, i, i + 1, n, (type++) % 4);
		}
		available = idx;
		
		iter++;
	}
	int max = 0, maxweight = 0;
	for (int i = 0; i < available; i++){
		for (int j = 0, sum = 0,weight=0; j < n; j++){
			
			if (bit[i][j] == 1){
				sum += b[j];
				weight += a[j];
			}
			if (sum > max){
				max = sum;
				maxweight = weight;
			}
		}
	}

	cout << max << endl;
	cout << maxweight << endl;
}
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	double vec[n][2*n],org[n][n],fin[n][n],err=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<2*n;j++){
			if(j<n){
				scanf("%lf",&vec[i][j]);
				org[i][j]=vec[i][j];
			}
			else if(i+n==j) vec[i][j]=1;
			else vec[i][j]=0;
		}
	for(int k=0;k<n;k++){
		if(vec[k][k]!=0){
			for(int i=0;i<n;i++){
				if(i==k) continue;
				double mlt=vec[i][k];
				for(int j=k;j<2*n;j++)
					vec[i][j]-=vec[k][j]*mlt/vec[k][k];
			}
		}
		else{
			int find=k;
			while(vec[find][k]==0) find++;
			for(int j=k;j<2*n;j++) vec[k][j]+=vec[find][j];
			k--;
		}
	}
	for(int i=0;i<n;i++)
		for(int j=n;j<2*n;j++)
			vec[i][j]/=vec[i][i];
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			fin[i][j]=0;
			for(int k=0;k<n;k++)
				fin[i][j]+=vec[i][k+n]*org[k][j];
			if(i==j) fin[i][j]--;
			if(fabs(fin[i][j])>err) err=fabs(fin[i][j]);
		}
	printf("%e\n",err);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			printf("%f",vec[i][j+n]);
			printf(n==j+1?"\n":" ");
		}
	return 0;
}
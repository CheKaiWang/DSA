#include <iostream>
#include <unordered_set>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
unordered_set<string> dic;

vector<string> ed1,edf;
void Ins(string fir,int len,int t)
{
	string ttmp="abcdefghijklmnopqrstuvwxyz";
	for(int i=0;i<=len;i++)
		for(int j=0;j<26;j++)
		{
			string tmp=fir;
			tmp.insert(i,ttmp,j,1);
			if(t==1) ed1.push_back(tmp);
			unordered_set<string>::const_iterator got = dic.find (tmp);
			if(got != dic.end()) edf.push_back(*got);
		}
	return;
}
void Del(string fir,int len,int t)
{
	for(int i=0;i<len;i++)
	{
		string tmp=fir;
		tmp.erase(i,1);
		if(t==1) ed1.push_back(tmp);
		unordered_set<string>::const_iterator got = dic.find (tmp);
		if(got != dic.end()) edf.push_back(*got);
	}
	return;
}
void Sub(string fir,int len,int t)
{
	string ttmp="abcdefghijklmnopqrstuvwxyz";
	for(int i=0;i<len;i++)
		for(int j=0;j<26;j++)
		{
			string tmp=fir;
			tmp.replace(i,1,ttmp,j,1);
			if(t==1) ed1.push_back(tmp);
			unordered_set<string>::const_iterator got = dic.find (tmp);
			if(got != dic.end()) edf.push_back(*got);
		}
	return;
}
void Tra(string fir,int len,int t)
{
	for(int i=0;i<len-1;i++)
	{
		string tmp=fir;
		swap(tmp[i],tmp[i+1]);
		if(t==1) ed1.push_back(tmp);
		unordered_set<string>::const_iterator got = dic.find (tmp);
		if(got != dic.end()) edf.push_back(*got);
	}
}
int main()
{
	char str[128],fir[32];
	//FILE *f=fopen("C:\\Users\\user\\Desktop\\D.S.A\\HW5\\cmudict-0.7b.txt","r");
	FILE *f=fopen("cmudict-0.7b","r");
	while(fgets(str,100,f)!=NULL)
	{
		sscanf(str,"%s",fir);
		int i=0;
		while(fir[i])
		{
		    fir[i]=tolower(fir[i]);
	    	i++;
		}
		dic.insert(fir);
	}
	fclose(f);
	while(fgets(str,100,stdin)!=NULL)
	{
		sscanf(str,"%s",fir);
		int len=strlen(fir);
		unordered_set<string>::const_iterator got = dic.find (fir);
		if(got!=dic.end()) printf("%s ==> OK\n",fir); //cout<<fir<<" ==> OK\n";
		else
		{
			Ins(fir,len,1);
			Del(fir,len,1);
			Sub(fir,len,1);
			Tra(fir,len,1);
			vector<string>::iterator it;
			for(it=ed1.begin();it!=ed1.end();it++)
			{
				int itlen=(*it).size();
				Ins(*it,itlen,2);
				Del(*it,itlen,2);
				Sub(*it,itlen,2);
				Tra(*it,itlen,2);
			}
			if(edf.begin()==edf.end()) printf("%s ==> NONE\n",fir); //cout<<fir<<" ==> NONE\n";
			else
			{
				string tmp="!";
				sort(edf.begin(),edf.end());
				//cout<<fir<<" ==>";
				printf("%s ==>",fir);
				for(it=edf.begin();it!=edf.end();it++)
				{
					if(*it!=tmp)
					{
						//cout<<" "<<*it;
						printf(" %s",(*it).c_str());
						tmp=*it;
					}
				}
				printf("\n");
			}
		}
		ed1.clear();
		edf.clear();
	}
	return 0;
}

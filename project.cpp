//#include<bits/stdc++.h>
#include<iostream>
#include<queue>
using namespace std;
struct process {	
		int pid, priority, burst, at;
};

int total_time=0;
int p;

struct process pro[100];

struct process find(int pid)
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].pid==pid)
		{
			return pro[i];
		}
	}
}

bool compare(process p1, process p2)
	{
		if(p1.priority!=p2.priority)
		return p1.priority<p2.priority;
	}

void enterprocess(int p)
{
	for(int i=0; i<p; i++)
	{
		pro[i].pid=(i+1);
		cout<<"-------------------";
		cout<<"\nInput P"<<i+1;
		cout<<"\nArrival_time: ";
		cin>>pro[i].at;
		cout<<"Priority: ";
		cin>>pro[i].priority;
		cout<<"Burst_time: ";
		cin>>pro[i].burst;
		cout<<"--------------------\n";
	}
	//sort(pro, pro+p, compare);
}

queue <int> q1;
queue <int> q2;
queue <int> q3;

void qload(int total_time)
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].at==total_time)
		{
			if(pro[i].priority>0 && pro[i].priority<=3)
			{
				cout<<"\n-----------------------------";
				cout<<"\nP"<<i+1<<" Pushed to Q1 at time: "<<total_time;
				cout<<"\n-----------------------------";
				q1.push(pro[i].pid);
			}
			else if(pro[i].priority>=7 && pro[i].priority<=9){
				q3.push(pro[i].pid);
				//cout<<"\n-----------------------------";
				cout<<"\nP"<<i+1<<" Pushed to Q3 at: "<<total_time;
				//cout<<"\n-----------------------------";
			}
		}
	}
}

bool compare1(int a, int b)
{
	if(find(a).priority!=find(b).priority)
	return find(a).priority<find(b).priority;
}

void qload2 (int total_time)
{
	vector <int> a;
	int flag=0;
	for(int i=0; i<p; i++)
	{
		if(pro[i].at==total_time)
		{
			if(pro[i].priority>=4 and pro[i].priority<=6)
			{
			//	cout<<"\n-----------------------------";
				cout<<"\nP"<<i+1<<" Pushed to Q2 at time: "<<total_time;
			//	cout<<"\n-----------------------------";
				a.push_back(pro[i].pid);
				flag=1;
			}
		}
	}
	int cnt=1;
	if(flag==1)
	{
//		cout<<"\nSize in func: "<<q2.size();
		int x=q2.size();
		for(int j=0; j<x; j++)
		{
//			cout<<"\nLoading into array from queue: "<<q2.front();
			a.push_back(q2.front());
			q2.pop();
			cnt++;
		}
		//sort(a.begin(),a.end(), compare1); commented
		for(int j=0; j<a.size(); j++)
		{
//			cout<<"\nPushing into queue: "<<a[j];
			q2.push(a[j]);
		}
	}
}

void proupdate(int b, int id)
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].pid==id)
		{
			pro[i].burst=b;
		}
	}
}

struct process currpro;

bool procheck()
{
	for(int i=0; i<p; i++)
	{
		if(pro[i].burst!=0)
			return false;
	}
	return true;

}


int main()
{
	cout<<"\nNo of processes: ";
	cin>>p;
    cout<<"Priority of Q1(Round Robin) is 0 to 3\n";
    cout<<"Priority of Q2(Priority Scheduling) is 4 to 6\n";
    cout<<"Priority of Q3(First Come First Serve) is 7 to 9\n";
	enterprocess(p);
	int flagclose=0;
	
	qload(total_time);

	qload2(total_time);
	/*cout<<"\nq1 size "<<q1.size();
	cout<<"\nq1 front "<<q1.front();
	cout<<"\nq2 size "<<q2.size();
	cout<<"\nq2 front "<<q2.front();
	cout<<"\nq3 size "<<q3.size();
	cout<<"\nq3 front "<<q3.front();*/
	int t=0;
	while( flagclose==0)
	{
		int t1=0;
		int curr, b;
		
		t=0;
		
		if(!q1.empty())
		{
			curr=q1.front();
			currpro=find(curr);
			b=currpro.burst;
		}
		cout<<"\n---------------------------";
		cout<<"\nQueue 1 | Total Time: "<<total_time;
		while(t1<4 && t<10 && q1.size()!=0)
		{
			b--;
			t++;
			t1++;
			total_time++;
			proupdate(b,q1.front());
			if(t%4+1==1)
				cout<<"\nProcessing P"<<q1.front();
				
			if(t%4==0)
				cout<<"\nProcess P"<<q1.front()<<" | Q-Time "<<t<<" | RR-Time "<<t1<<" | Remaining-Time "<<b<<" |";
			qload(total_time);
			qload2(total_time);
			
			/*	cout<<"\nq1 size "<<q1.size();
				cout<<"\nq1 front "<<q1.front();
			cout<<"\nq2 size "<<q2.size();
			cout<<"\nq2 front "<<q2.front();*/
			if(t==10)
			{
				proupdate(b,q1.front());
				int x=q1.front();
//				q1.pop();
//				q1.push(x);
			}
			if(t1==4 || b==0)
			{
				if(b==0)
				//cout<<"\nhere";
				q1.pop();
				if(b!=0)
				{
					proupdate(b,q1.front());
					int x=q1.front();
					q1.pop();
					q1.push(x);
				}
				if(q1.size()!=0)
				{
//					cout<<"\nhere2";
					curr=q1.front();
					currpro=find(curr);
					b=currpro.burst;
					t1=0;
				}
				else
				t=10;
			}		
		}
		
		
		t=0;
		
		if(q2.size()!=0)
		{
			curr=q2.front();
			currpro=find(curr);
			b=currpro.burst;
		}
		
		cout<<"\nQueue 1 End | Total Time: "<<total_time;
		cout<<"\n---------------------------";
		cout<<"\nQueue 2 | Total Time: "<<total_time;
		while(t<10 && q2.size()!=0)
		{
			curr=q2.front();
					currpro=find(curr);
					b=currpro.burst;
			b--;
			t++;
			total_time++;
			proupdate(b,q2.front());
			cout<<"\nProcessing P"<<q2.front();
			cout<<"\nProcess P"<<q2.front()<<" | Q-Time "<<t<<" | Remaining-Time "<<b<<" |";
			if(t==10 && b>0)
			{
				proupdate(b,q2.front());	
			}
			if(b==0)
			{
				q2.pop();
				qload(total_time);
				qload2(total_time);
				/*cout<<"\nq1 size "<<q1.size();
				cout<<"\nq1 front "<<q1.front();
				cout<<"\nq2 size "<<q2.size();
				cout<<"\nq2 front "<<q2.front();*/
//				cout<<"\nsize when b=0: "<<q2.size();
//				cout<<"\nfront when b=0: "<<q2.front();
				if(q2.size()!=0)
				{
					curr=q2.front();
					currpro=find(curr);
					b=currpro.burst;
				}
				else
				{
				t=10;
//				cout<<"\nhere3";
				}
			}
			else
			{
				qload(total_time);
				qload2(total_time);
				/*cout<<"\nq1 size "<<q1.size();
				cout<<"\nq1 front "<<q1.front();
				cout<<"\nq2 size "<<q2.size();
				cout<<"\nq2 front "<<q2.front();*/
			}
		}
		
		cout<<"\nQueue 2 End | Total Time: "<<total_time; 
		cout<<"\n--------------------------";
		t=0;
		cout<<"\nQueue 3 | Total Time: "<<total_time;
		if(q3.size()!=0)
		{
			curr=q3.front();
			currpro=find(curr);
			b=currpro.burst;
		}
		while(t<10 && q3.size()!=0)
		{
			b--;
			t++;
			total_time++;
			proupdate(b,q3.front());
			cout<<"\nProcessing P"<<q3.front();
			cout<<"\nProcess P"<<q3.front()<<" | Q-Time "<<t<<" | Remaining-Time "<<b<<" |";
			qload(total_time);
			qload2(total_time);
			
			/*cout<<"\nq1 size "<<q1.size();
				cout<<"\nq1 front "<<q1.front();
			cout<<"\nq2 size "<<q2.size();
			cout<<"\nq2 front "<<q2.front();
			cout<<"\nq3 size "<<q3.size();
			cout<<"\nq3 front "<<q3.front();*/
			
			if(t==10)
			{
				proupdate(b,q3.front());
				int x=q3.front();
//				q1.pop();
//				q1.push(x);
			}
			//if(t1==4 || b==0)
			//{
				if(b==0)
				{//cout<<"\nhere";
				q3.pop();
//				if(b!=0)
//				{
//					proupdate(b,q3.front());
//					int x=q3.front();
//					q3.pop();
//					q3.push(x);
//				}
				if(q3.size()!=0)
				{
//					cout<<"\nhere2";
					curr=q3.front();
					currpro=find(curr);
					b=currpro.burst;
					
				}
				else
				t=10;
				}
		}
		
		cout<<"\nQueue 3 End | Total Time: "<<total_time;
		
		if(q2.size()==0 && q1.size()==0 && q3.size()==0)
		{
			if(procheck()){
				cout<<"\n--------------------------";
				flagclose=1;
				cout<<"\nEnd Of Program.";
				cout<<"\n--------------------------\n";
			}
			else
			{
				cout<<"\n--------------------------";
				cout<<"\nProcesses Remaining";
				cout<<"\n--------------------------";
				total_time++;
				qload(total_time);
				qload2(total_time);
			}
			
		}
	}
	
}


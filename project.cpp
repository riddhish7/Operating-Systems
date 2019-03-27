#include<iostream>
#include<queue>
using namespace std;
int main(){
    
    int n,i,j,k;
    
    
    cout<<"Enter the number of processses: ";
    cin>>n;
    int arrival_time[n],burst_time[n],temp[n];
    int arr[n][2];
    
    for(i = 0; i < n; i++) 
      {
            cout<<"\nEnter Details of Process " <<i+1<<"\n";
            cout<<"Arrival Time:\t";
            cin>>arrival_time[i];
            cout<<"Burst Time:\t";
            cin>>burst_time[i]; 
            temp[i] = burst_time[i];
      }
    for(i=0;i<n;i++)
    {
        arr[i][0]=arrival_time[i];
        arr[i][1]=burst_time[i];
    }
    cout<<"  Arrival time\t   Burst time\n";
    for(i=0;i<n;i++)
    {
        for(j=0;j<2;j++)
        {
            cout<<"\t"<<arr[i][j]<<"\t";
            
        }
        cout<<"\n";
    }
    
    for(k=0;k<n-2;k++)
    {
            for(i=0;i<n-1;i++)
            {
                if(arr[i][0]>arr[i+1][0])
                {
                    int t=arr[i][0];
                    arr[i][0]=arr[i+1][0];
                    arr[i+1][0]=t;

                    int q=arr[i][1];
                    arr[i][1]=arr[i+1][1];
                    arr[i+1][1]=q;
                }
            }  
    }
    
    cout<<"After swapping\n";
    cout<<"  Arrival time\t   Burst time\n";
    for(i=0;i<n;i++)
    {
        for(j=0;j<2;j++)
        {
            cout<<"\t"<<arr[i][j]<<"\t";
            
        }
        cout<<"\n";
    }
    
 
    
}

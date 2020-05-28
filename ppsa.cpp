#include <bits/stdc++.h>
using namespace std;

// This contains info abt CT, TAT, WT
map<int, int> completion_time, turnaround_time, waiting_time, Bursts;
vector<int> jobSequence;

class Process{
	public:
		int pid;
		int priority;
		int arrival_time;
		int burst_time;
};

// This is to sort the process acc to their priorities
class compare{
	public:
		bool operator()(Process a, Process b){
			if(a.priority > b.priority)return 1;
			else if(a.priority < b.priority)return 0;
			return a.arrival_time > b.arrival_time;
		}
};

// String representation of a process for debugging purposes
string toString(Process a){
	return "{" + to_string(a.pid) + "," + to_string(a.burst_time) + "," + to_string(a.arrival_time) + "," + to_string(a.priority) + "}";
}

// Actual algorithm
void shedule(queue<Process> jobs){
	priority_queue<Process, vector<Process>, compare> jobQueue;
	int time = 0;
	while(true){
		while(!jobs.empty() && jobs.front().arrival_time <= time){
			jobQueue.push(jobs.front());
			jobs.pop();
		}
		if(jobQueue.empty())time++;
		else break;
	}	
	// Do until job queue is empty
	while(!jobQueue.empty()){
		Process now = jobQueue.top();
		jobQueue.pop();
		jobSequence.push_back(now.pid);
		time++;
		now.burst_time--;
		if(now.burst_time == 0){
			completion_time[now.pid] = time;
			turnaround_time[now.pid] = completion_time[now.pid] - now.arrival_time;
			waiting_time[now.pid] = turnaround_time[now.pid] - Bursts[now.pid];
		}
		else jobQueue.push(now);
		while(!jobs.empty() && jobs.front().arrival_time <= time){
			jobQueue.push(jobs.front());
			jobs.pop();
		}
	}
}
const char separator = ' ';
template<typename T> void print(T t, const int& width){
    cout << left << setw(width) << setfill(separator) << t;
}
// display the table	
void display(vector<Process> list){
	cout << "*-------*-------------*-------*-------*-------*--------*---*\n";
	print("| PID", 7);
	print(" | PRIORITY", 12);
	print("   | AT", 6);
	print("    | BT", 6);
	print("    | CT", 6);
	print("    | TAT", 7);
	print("    | WT", 0);
	cout << "|\n";
	cout << "*-------*-------------*-------*-------*-------*--------*---*\n";
	for(auto job: list){
		cout << "| ";
		print(job.pid, 6);
		cout << "| ";
		print(job.priority, 10);
		cout << "  | ";
		print(job.arrival_time, 3);
		cout << "   | ";
		print(job.burst_time, 3);
		cout << "   | ";
		print(completion_time[job.pid], 3);
		cout << "   | ";
		print(turnaround_time[job.pid], 4);
		cout << "   | ";
		print(waiting_time[job.pid], 0);
		cout << " |\n";
		cout << "*-------*-------------*-------*-------*-------*--------*---*\n";
	}

}
int main(){
	
	vector<Process> list;
	int numProcess;
	cout << "How many Processes to shedule?\n";
	cin >> numProcess;
	for(int i = 1; i <= numProcess; i++){
		Process* a = new Process();
		cout << "Enter Job " << i << " priority: ";
		cin >> a -> priority;
		cout << "Enter Job " << i << " Arrival Time: ";
		cin >> a ->arrival_time;
		cout << "Enter Job " << i << " Burst Time: ";
		cin >> a -> burst_time;
		list.push_back({i, a -> priority, a -> arrival_time, a -> burst_time});
		Bursts[i] = a -> burst_time;
	}
	queue<Process> jobs;
	for(auto job: list)jobs.push(job);
	shedule(jobs);
	display(list);
	return 0;
}
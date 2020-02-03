// C++ program to illustrate Banker's Algorithm 
#include<iostream> 
using namespace std;

int processes[100];
int avail[10];
int maxm[100][10];
int allot[100][10];
int need[100][10];
int safeSeq[100];
int work[10];
int request[10];

int n, m;

// calculates and store the need of each process in need[][]matrix
void calculateNeed()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			need[i][j] = maxm[i][j] - allot[i][j];
}

// Function to check the state is safe or not
bool isSafe()
{
	// in the begining all processes are not finished
	bool finish[100] = { 0 };

	// Make a copy of available resources 
	for (int i = 0; i < m; i++)
	{
		work[i] = avail[i];
	}

	// until all processes are finished the algorithm will iterate throug every possible process
	int count = 0;
	while (count < n)
	{
		bool found = false;
		//safety algorithm implementation
		for (int p = 0; p < n; p++)
		{
			if (finish[p] == 0)
			{
				int j;
				for (j = 0; j < m; j++)
					if (need[p][j] > work[j])
						break;

				// If all needs of p were satisfied. 
				if (j == m)
				{
					for (int k = 0; k < m; k++)
					{
						work[k] += allot[p][k];
					}

					safeSeq[count++] = p;
					finish[p] = 1;
					found = true;
				}
			}
		}
		if (found == false)
		{
			cout << "System state : UN SAFE\nHIGHER CHANCE OF DEADLOCKS\n";
			return false;
		}
	}

	// If system is in safe state then 
	// safe sequence will be as below 
	cout << "System State : SAFE.\nPrograms will be executed in the following order: \n";
	for (int i = 0; i < n; i++)
		cout <<"Process "<< safeSeq[i] << " >> ";

	return true;
}

// Driver code 
int main()
{
	int temp;
	cout << "No. of Processes : ";
	cin >> n;
	cout << endl << "No. of Resources : ";
	cin >> m;
	cout << endl;

	for (int i = 0; i < n; i++)
	{
		processes[i] = i;
	}

	// Available instances of resources 
	for (int i = 0; i < m; i++)
	{
		cout << "R (" << i << ") : ";
		cin >> avail[i];
	}

	cout << "Please enter the maximum resources that can be allocated in the following manner.\n<Memory for P0>\n<Memory for P1>\n...\n...\n\n";
	// Maximum R that can be allocated 
	// to processes 
	int total[10] = { 0 };
	for (int j = 0; j < n; j++)
	{
		for (int l = 0; l < m; l++)
		{
			cout << "P" << j << " -> R(" << l << ") : ";
			cin >> maxm[j][l];
		}
	}

	cout << "Please enter the Pre allocated resources\\n<Memory for P0>\n<Memory for P1>\n...\n...\n\n";
	// Resources allocated to processes 
	for (int j = 0; j < n; j++)
	{
		for (int l = 0; l < m; l++)
		{
			cout << "P" << j << " -> R(" << l << ") : ";
			cin >> allot[j][l];
			total[l] += allot[j][l];
		}
	}
	for (int l = 0; l < m; l++)
	{
		avail[l] -= total[l];
	}
	// Check system is in safe state or not 
	// Function to calculate need matrix 
	calculateNeed();
	bool status = isSafe();
	int r;
	if (status == true)
	{
		cout << "\n\nTo what process the new request must be added(0,1,2..) : ";
		cin >> r;
		bool s = 0;
	jumppoint:
		for (int i = 0; i < m; i++)
		{
			cout << "R (" << i << ") : ";
			cin >> request[i];
			if (request[i] > need[r][i])
			{
				cout << "Request is exceeding the needed resource" << endl;
				goto jumppoint;
			}
			if (request[i] > avail[i])
			{
				cout << "Request is exceeding the available resource" << endl;
				goto jumppoint;
			}
			avail[i] -= request[i];
			allot[r][i] += request[i];
			need[r][i] -= request[i];
			s = 1;
		}
		if (s)
			cout << "SYSTEM STATE : SAFE\n";
		else
			cout << "SYSTEM State : UN SAFE\n";
			cout << "SYSTEM State : UN SAFE\n";
	}
	system("pause");
	return 0;
}

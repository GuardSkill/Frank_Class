#define CPULIBDLL
#include "CPUinfo.h"
int CPUinfo::GetCPUNum()                    //get CPU's number
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
}
DWORD CPUinfo::getCPUMask()
{
	int i = 0;
	static int CPUNum = GetCPUNum();
	HQUERY query;
	if (PdhOpenQuery(NULL, NULL, &query) != ERROR_SUCCESS)
	{
		cout << "Add Counter Error" << endl;
		return -1;
	}
	vector<HCOUNTER> counters;
	for (i = 0; i < CPUNum; i++)
	{
		//HCOUNTER counter = (HCOUNTER *)GlobalAlloc(GPTR, sizeof(HCOUNTER));
		HCOUNTER counter;
		string CounterPath = "\\Processor(";
		char count = '0' + i;
		CounterPath = CounterPath + count + ")\\% Processor Time";
		if (PdhAddCounterA(query, CounterPath.c_str(), NULL, &counter) != ERROR_SUCCESS)
		{
			cout << "Add Counter Error" << endl;
			return -1;
		}
		counters.push_back(counter);
	}
	PdhCollectQueryData(query);
	//while (TRUE)
	//{
	int idleCPUindex = 0;
	double MiniLoad = 100;
	Sleep(1000);
	PdhCollectQueryData(query);
	for (i = 0; i < CPUNum; i++)
	{
		PDH_FMT_COUNTERVALUE pdhValue;
		DWORD dwValue;
		if (PdhGetFormattedCounterValue(counters[i], PDH_FMT_DOUBLE, &dwValue, &pdhValue) != ERROR_SUCCESS)
		{
			cout << "Get Value Error" << endl;
			return -1;
		}
		if (pdhValue.doubleValue < MiniLoad)
		{
			idleCPUindex = i;
			MiniLoad = pdhValue.doubleValue;
		}
		cout << "CPU" << i << " Load:" << pdhValue.doubleValue << "%\t";

	}
	//cout << endl;
	//}
	vector<HCOUNTER>(counters).swap(counters);  //delete vector
	return (1 << idleCPUindex);

}

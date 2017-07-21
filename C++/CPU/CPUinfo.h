#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#pragma comment(lib,"pdh.lib")                 //cpu load query need pdh.lib
#include <iostream>
#include <Pdh.h> 
#include <PdhMsg.h>  
using namespace std;

#ifdef CPULIBDLL  
#define CPUAPI _declspec(dllexport)  
#else  
#define CPUAPI  _declspec(dllimport)  
#endif  

class CPUAPI CPUinfo
{
public:
	int GetCPUNum();                    //get CPU's number
	DWORD getCPUMask();
};
#include <Windows.h>
#include <stdio.h>
#include <tlhelp32.h>
class ThreadAndProcess
{
	BOOL ListProcessThreads(DWORD dwOwnerPID) {
		THREADENTRY32 te32;
		// 在使用 Thread32First 前初始化 THREADENTRY32 的结构大小.  
		te32.dwSize = sizeof(te32);
		// 把所有进程拍一个快照  
		HANDLE hThreadSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (hThreadSnap == INVALID_HANDLE_VALUE)
		{
			printf("CreateToolhelp32Snapshot failed");
			return(FALSE);
		}


		// 获取第一个线程信息, 如果失败则退出.  
		if (!Thread32First(hThreadSnap, &te32)) {
			printf("Thread32First failed");
			CloseHandle(hThreadSnap);     // 必须在使用后清除快照对象!  
			return(FALSE);
		}

		// 现在获取系统线程列表, 并显示与指定进程相关的每个线程的信息  
		do {
			if (te32.th32OwnerProcessID == dwOwnerPID) {
				printf("the thread's owner process ID:%u\n", te32.th32OwnerProcessID);
				printf(" thread  id =%u\n", te32.th32ThreadID);
			}
		} while (Thread32Next(hThreadSnap, &te32));
		//  千万不要忘记清除快照对象!  
		CloseHandle(hThreadSnap);
		return(TRUE);
	}
	bool DisplayProcess()
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(pe32);
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);   //take a snapshot for processes
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			printf("CreateToolhelp32Snapshot failed");
			return -1;
		}
		BOOL bMore = ::Process32First(hProcessSnap, &pe32);  //get the first snapshot
		while (bMore)
		{
			printf("process name:%s\n", pe32.szExeFile);
			printf("process ID:%u\n", pe32.th32ProcessID);
			bMore = ::Process32Next(hProcessSnap, &pe32);
		}
		::CloseHandle(hProcessSnap);
	}
};

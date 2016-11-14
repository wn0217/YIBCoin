#include <stdio.h>  
#include <stdlib.h>  
#include <assert.h>  
#include <stdint.h>
typedef unsigned int UINT;
#ifdef EnableLicense
//typedef char BYTE;
//static char result[512] = { 0 };
static const void  GetCpuID(char result[] )
{
	// 定义一些变量，用于存储 CPU 的 ID信息  

	BYTE szCpu[16] = { 0 };
	UINT uCpuID = 0U;

	// 调用汇编代码，获取 CPU ID 信息  

	__asm{
		mov eax, 0
			cpuid
			mov dword ptr szCpu[0], ebx
			mov dword ptr szCpu[4], edx
			mov dword ptr szCpu[8], ecx
			mov eax, 1
			cpuid
			mov uCpuID, edx
	}
	
	result[512] = { 0 };
	// 把结果输出到文件中  
	sprintf(result ,"cpu id is %u, info is %s", uCpuID, szCpu);
	//return result;
}
static  bool WriteLicenseFile(std::string strdata, std::string saveFilename) {
	FILE *f = fopen(saveFilename.c_str(), "wb");
	if (f)
	{
		size_t length = strdata.size();
		fwrite(&length, sizeof(unsigned long), 1, f);
		fwrite(&strdata[0], strdata.size(), 1, f);
		fclose(f);
	}
	return true;
}
static  bool WriteLicenseFile(char data[], long Length, std::string saveFilename) {
	std::string strdata;
	for (int i = 0; i < Length; i++)
	{
		strdata.push_back(data[i]);
	}
	FILE *f = fopen(saveFilename.c_str(), "wb");
	if (f)
	{
		size_t length = strdata.size();
		fwrite(&length, sizeof(unsigned long), 1, f);
		fwrite(&strdata[0], strdata.size(), 1, f);
		fclose(f);
	}
	return true;
}
static  std::string ReadLicenseFile() {
	FILE* f = fopen("license.dat", "rb");
	if (f)
	{

		unsigned long Length;
		fread(&Length, sizeof(unsigned long), 1, f);
		BYTE* Buffer = new BYTE[Length + 1];
		Buffer[Length] = '\0';
		if (Length != 0)
			fread_s(Buffer, Length, 1, Length, f);
		std::string target;
		for (int i = 0; i < Length; i++)
		{
			target.push_back(Buffer[i]);
		}
		fclose(f);
		delete[] Buffer;
		return target;
	}
	else
	{
		return "";
	}
}
static std::vector <IDXGIAdapter*> EnumerateAdapters(void)
{
	IDXGIAdapter * pAdapter;
	std::vector <IDXGIAdapter*> vAdapters;
	IDXGIFactory* pFactory = NULL;


	// Create a DXGIFactory object.
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory)))
	{
		return vAdapters;
	}

	for (UINT i = 0;
		pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND;
		++i)
	{
		vAdapters.push_back(pAdapter);
	}


	if (pFactory)
	{
		pFactory->Release();
	}

	return vAdapters;

}
#endif
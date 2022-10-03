#pragma once
#include<string>
#include<Windows.h>
#include<windows.system.diagnostics.h>

class Diagnostic : public ABI::Windows::System::Diagnostics::IProcessCpuUsage
{
public:
	void RetrieveInfo();

private:
	//ABI::Windows::System::Diagnostics::IProcessCpuUsage info;
	IProcessCpuUsage* info;
	IProcessCpuUsage** value;
};


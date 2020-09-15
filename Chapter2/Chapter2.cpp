#include <ntddk.h> // imported to use driver types

// called before the driver is unloaded
// should be used to free resources used on DriverEntry so there is not a leak in kernel memory
void SampleUnload(_In_ PDRIVER_OBJECT DriverObject) 
{ 
	UNREFERENCED_PARAMETER(DriverObject); 
}

extern "C" NTSTATUS // Gives DriveryEntry C linkage

// EntryPoint to the driver application
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath); // used so driver compiles, we do not use RegistryPath
	DriverObject->DriverUnload = SampleUnload; // set to call SampleUnload before driver exits
	return STATUS_SUCCESS; 
}

void PrintVersion() {
	_Out_ RTL_OSVERSIONINFOW WindowsInfo; // declare structure that holds OS info
	RtlZeroMemory(&WindowsInfo, sizeof(PRTL_OSVERSIONINFOW)); // allocate memory for the structure
	RtlGetVersion(&WindowsInfo); // populate the structure
	KdPrint(("Windows version %d.%d, build %ul\n", WindowsInfo.dwMajorVersion, WindowsInfo.dwMinorVersion, WindowsInfo.dwBuildNumber)); // print os info
	return;
}

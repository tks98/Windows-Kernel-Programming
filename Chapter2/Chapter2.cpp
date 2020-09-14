#include <ntddk.h> // imported to use driver types

// called before the driver is unloaded
// should be used to free resources used on DriverEntry so there is not a leak in kernel memory
void SampleUnload(_In_ PDRIVER_OBJECT DriverObject) 
{ 
	UNREFERENCED_PARAMETER(DriverObject);
	KdPrint(("Sample driver unload called\n"));
}

extern "C" NTSTATUS // Gives DriveryEntry C linkage

// EntryPoint to the driver application
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(RegistryPath); // used so driver compiles, we do not use RegistryPath
	DriverObject->DriverUnload = SampleUnload; // set to call SampleUnload before driver exits
	KdPrint(("Sample driver initialized successfully"));
	return STATUS_SUCCESS; 
}

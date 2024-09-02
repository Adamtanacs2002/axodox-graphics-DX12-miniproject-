#include "pch.h"
#include "GPUDiagnostics.h"
void Miniproject::GPUDiagnostics::Dred::initDred()
{
	com_ptr<ID3D12DeviceRemovedExtendedDataSettings> pDredSettings;
	check_hresult(D3D12GetDebugInterface(IID_PPV_ARGS(&pDredSettings)));

	// Turn on AutoBreadcrumbs and Page Fault reporting
	pDredSettings->SetAutoBreadcrumbsEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
	pDredSettings->SetPageFaultEnablement(D3D12_DRED_ENABLEMENT_FORCED_ON);
}

void Miniproject::GPUDiagnostics::Dred::frameReport(ID3D12Device2* pDevice)
{
	com_ptr<ID3D12DeviceRemovedExtendedData> pDred;
	check_hresult(pDevice->QueryInterface(IID_PPV_ARGS(&pDred)));

	D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT DredAutoBreadcrumbsOutput;
	D3D12_DRED_PAGE_FAULT_OUTPUT DredPageFaultOutput;
	check_hresult(pDred->GetAutoBreadcrumbsOutput(&DredAutoBreadcrumbsOutput));
	check_hresult(pDred->GetPageFaultAllocationOutput(&DredPageFaultOutput));

	// Custom processing of DRED data can be done here.
	// Produce telemetry...
	// Log information to console...
	// break into a debugger...
}

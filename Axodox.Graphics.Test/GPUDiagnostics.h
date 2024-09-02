#pragma once



namespace Miniproject::GPUDiagnostics
{
	using namespace DirectX;
	using namespace winrt;
	class Dred
	{
	private:
		void initDred();
	public:
		Dred()
		{
			initDred();
		}

		void frameReport(ID3D12Device2* pDevice);
	};
}
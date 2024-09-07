#include "pch.h"

using namespace Axodox::Graphics::D3D12;

class MeshUpdater
{
private:
public:
	MeshUpdater() {}
	~MeshUpdater() {}

	// Allocate resources
	void Init(GraphicsDevice device, CommandAllocator& allocator);
	// Release resources
	void Release();

	// Reload shaders
	void ReloadShaders();

	// Update a given mesh
	void Update();
	// Check if Mesh topology is valid
	void Validate();

	// Reset the buffers
	void ResetBuffers();
	// Prepare the mesh for indirect dispatches
	void PrepIndirect();

	// Control if the validation pass should run
	void CheckIfValid();

	// Query occupancy
	void QueryOccupancy();

	// Get the occupancy
	uint32_t get_occupancy();
};


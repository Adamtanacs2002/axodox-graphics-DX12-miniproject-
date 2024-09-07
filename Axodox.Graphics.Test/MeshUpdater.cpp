#include "pch.h"
#include "MeshUpdater.h"

void MeshUpdater::Init(GraphicsDevice device, CommandAllocator& allocator)
{
}

void MeshUpdater::Release()
{
}

void MeshUpdater::ReloadShaders()
{
}

void MeshUpdater::Update()
{
	// Reset Pass
	// Classify Pass
	// Prepare Indirect Split Pass
	// Split Pass
	// Prepare Indirect Allocate Pass
	// Allocate Pass
	// Copy Pass
	// Bisect Pass
	// Prepare Indirect Propagate Pass
	// Propagate Split/Bisect Pass
	// Prepare Simplify Pass
	// Prepare Indirect Simplify Pass
	// Simplify Pass
	// Prepare Indirect Propagate Simplify Pass
	// Propagate Simplify Pass
	// Update (Reduce) Tree

	// Move to next bisector

	// Prep indirect dispatches
}

void MeshUpdater::Validate()
{
}

void MeshUpdater::ResetBuffers()
{
}

void MeshUpdater::PrepIndirect()
{
}

void MeshUpdater::CheckIfValid()
{
}

void MeshUpdater::QueryOccupancy()
{
}

uint32_t MeshUpdater::get_occupancy()
{
	return 0;
}

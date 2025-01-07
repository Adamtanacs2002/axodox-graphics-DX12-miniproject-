#pragma once

using namespace Axodox::Graphics::D3D12;

interface MutableMeshBase
{
public:

	MutableMeshBase(const ResourceAllocationContext& context, MeshDescription&& description) :
	_vertexBuffer(context.ResourceAllocator->CreateBuffer(BufferDefinition(description.Vertices))),
    _indexBuffer(context.ResourceAllocator->CreateBuffer(BufferDefinition(description.Indices))),
    _topology(D3D12_PRIMITIVE_TOPOLOGY(description.Topology)),
    _vertexCount(description.Vertices.ItemCount()),
    _indexCount(description.Indices.ItemCount())
	{
		if (_vertexBuffer)
		{
			_verticesAllocatedSubscription = _vertexBuffer->Allocated([this, buffer = move(description.Vertices), context](Resource* resource) {
				context.ResourceUploader->EnqueueUploadTask(resource, &buffer);
				_vertexBufferView = { (*resource)->GetGPUVirtualAddress(), buffer.ByteCount(), buffer.ItemSize() };
				});
		}

		if (_indexBuffer)
		{
			_indicesAllocatedSubscription = _indexBuffer->Allocated([this, buffer = move(description.Indices), context](Resource* resource) {
				context.ResourceUploader->EnqueueUploadTask(resource, &buffer);
				_indexBufferView = { (*resource)->GetGPUVirtualAddress(), buffer.ByteCount(), GetIndexFormat(buffer.ItemSize()) };
				});
		}
	}

	void DrawBase(CommandAllocator& allocator, uint32_t instanceCount = 1)
	{
		if (bool(_vertexBuffer) != bool(_vertexBufferView) || bool(_indexBuffer) != bool(_indexBufferView) || !instanceCount) return;

		if (_vertexBuffer) allocator->IASetVertexBuffers(0, 1, &*_vertexBufferView);
		if (_indexBuffer) allocator->IASetIndexBuffer(&*_indexBufferView);
		allocator->IASetPrimitiveTopology(_topology);

		if (_indexBuffer)
		{
			allocator->DrawIndexedInstanced(_indexCount, instanceCount, 0u, 0u, 0u);
		}
		else
		{
			allocator->DrawInstanced(_vertexCount, instanceCount, 0u, 0u);
		}
	}

protected:
	// VAO & IBO
	BufferRef _vertexBuffer;
	BufferRef _indexBuffer;

	// Counters
	uint32_t _vertexCount, _indexCount;

	// Allocation events
	event_subscription _verticesAllocatedSubscription, _indicesAllocatedSubscription;

	// Topology Type
	D3D12_PRIMITIVE_TOPOLOGY _topology;

	// Buffer Views
	std::optional<D3D12_VERTEX_BUFFER_VIEW> _vertexBufferView;
	std::optional<D3D12_INDEX_BUFFER_VIEW> _indexBufferView;

	static DXGI_FORMAT GetIndexFormat(uint32_t size)
	{
		switch (size)
		{
		case 4:
			return DXGI_FORMAT_R32_UINT;
		case 2:
			return DXGI_FORMAT_R16_UINT;
		default:
			return DXGI_FORMAT_UNKNOWN;
		}
	}
};


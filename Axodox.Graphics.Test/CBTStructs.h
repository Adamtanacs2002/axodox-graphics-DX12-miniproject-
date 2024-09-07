#include "pch.h"

using namespace Axodox::Graphics::D3D12;

namespace CBT::Signatures
{
#pragma region Slot Definitions
  // For C++, just output as is

#define CBV_SLOT(X) {X}
#define SRV_SLOT(X) {X}
#define UAV_SLOT(X) {X}
#define SPL_SLOT(X) {X}

// CBVs
#define GLOBAL_CB_BINDING_SLOT CBV_SLOT(0)
#define GEOMETRY_CB_BINDING_SLOT CBV_SLOT(1)
#define UPDATE_CB_BINDING_SLOT CBV_SLOT(2)

// SRVs
#define CURRENT_VERTEX_BUFFER_SLOT SRV_SLOT(0)
#define INDEXED_BISECTOR_BUFFER_BINDING_SLOT SRV_SLOT(1)

// UAVs
// CBT buffers
#define CBT_BUFFER0_BINDING_SLOT UAV_SLOT(0)
#define CBT_BUFFER1_BINDING_SLOT UAV_SLOT(1)

// Bisector buffers
#define HEAP_ID_BUFFER_BINDING_SLOT UAV_SLOT(2)
#define NEIGHBORS_BUFFER_BINDING_SLOT UAV_SLOT(3)
#define NEIGHBORS_OUTPUT_BUFFER_BINDING_SLOT UAV_SLOT(4)

// Intermediate buffers
#define BISECTOR_DATA_BUFFER_BINDING_SLOT UAV_SLOT(5)
#define CLASSIFICATION_BUFFER_BINDING_SLOT UAV_SLOT(6)
#define SIMPLIFICATION_BUFFER_BINDING_SLOT UAV_SLOT(7)
#define ALLOCATE_BUFFER_BINDING_SLOT UAV_SLOT(8)
#define PROPAGATE_BUFFER_BINDING_SLOT UAV_SLOT(9)
#define MEMORY_BUFFER_BINDING_SLOT UAV_SLOT(10)

// Indexation buffers
#define INDIRECT_DISPATCH_BUFFER_BINDING_SLOT UAV_SLOT(11)
#define INDIRECT_DRAW_BUFFER_BINDING_SLOT UAV_SLOT(12)
#define BISECTOR_INDICES_BINDING_SLOT UAV_SLOT(13)
#define VISIBLE_BISECTOR_INDICES_BINDING_SLOT UAV_SLOT(14)
#define MODIFIED_BISECTOR_INDICES_BINDING_SLOT UAV_SLOT(15)

// Debug
#define VALIDATION_BUFFER_BINDING_SLOT UAV_SLOT(16)
#pragma endregion

  struct CBTRootDescriptor : public RootSignatureMask
  {
    // CBVs
    RootDescriptor<RootDescriptorType::ConstantBuffer> TestCBV;
    // SRVs
    RootDescriptor<RootDescriptorType::ShaderResource> TestSRV;
    // UAVs
    RootDescriptor<RootDescriptorType::UnorderedAccess> TestUAV;

    CBTRootDescriptor(const RootSignatureContext& context) :
      RootSignatureMask(context),
      TestCBV(this, { 0 }),
      TestSRV(this, { 1 }),
      TestUAV(this, { 2 })
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };

  #pragma region Previous

  struct ClassifySignature : public RootSignatureMask
  {
    // CBVs
    RootDescriptor<RootDescriptorType::ConstantBuffer> globalCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> geometryCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> updateCB;
    // SRVs
    RootDescriptor<RootDescriptorType::ShaderResource> currentVertexBuffer;
    RootDescriptor<RootDescriptorType::ShaderResource> indexedBisectorBuffer;
    // UAVs
    RootDescriptor<RootDescriptorType::UnorderedAccess> indirectDrawBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> heapIDBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> updateBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> classificationBuffer;

    ClassifySignature(const RootSignatureContext& context) :
      RootSignatureMask(context),
      globalCB(this, GLOBAL_CB_BINDING_SLOT),
      geometryCB(this, GEOMETRY_CB_BINDING_SLOT),
      updateCB(this, UPDATE_CB_BINDING_SLOT),
      currentVertexBuffer(this, CURRENT_VERTEX_BUFFER_SLOT),
      indexedBisectorBuffer(this, INDEXED_BISECTOR_BUFFER_BINDING_SLOT),
      indirectDrawBuffer(this, INDIRECT_DRAW_BUFFER_BINDING_SLOT),
      heapIDBuffer(this, HEAP_ID_BUFFER_BINDING_SLOT),
      updateBuffer(this, UPDATE_CB_BINDING_SLOT),
      classificationBuffer(this, { 0 })
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  struct PrepareIndirectSignature : public RootSignatureMask
  {
    // UAVs
    RootDescriptor<RootDescriptorType::UnorderedAccess> allocatedBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> indirectDispatchBuffer;
    PrepareIndirectSignature(const RootSignatureContext& context) :
      RootSignatureMask(context),
      allocatedBuffer(this, ALLOCATE_BUFFER_BINDING_SLOT),
      indirectDispatchBuffer(this, INDIRECT_DISPATCH_BUFFER_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  struct SplitSignature : public RootSignatureMask
  {
    // CBVs
    RootDescriptor<RootDescriptorType::ConstantBuffer> globalCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> geometryCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> updateCB;
    // UAVs
    RootDescriptor<RootDescriptorType::UnorderedAccess> classificationBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> heapIDBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> bisectorDataBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> neighborsBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> memoryBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> allocatedBuffer;
    SplitSignature(const RootSignatureContext& context) :
      RootSignatureMask(context),
      globalCB(this, GLOBAL_CB_BINDING_SLOT),
      geometryCB(this, GEOMETRY_CB_BINDING_SLOT),
      updateCB(this, UPDATE_CB_BINDING_SLOT),
      classificationBuffer(this, CLASSIFICATION_BUFFER_BINDING_SLOT),
      heapIDBuffer(this, HEAP_ID_BUFFER_BINDING_SLOT),
      bisectorDataBuffer(this, BISECTOR_DATA_BUFFER_BINDING_SLOT),
      neighborsBuffer(this, NEIGHBORS_BUFFER_BINDING_SLOT),
      memoryBuffer(this, MEMORY_BUFFER_BINDING_SLOT),
      allocatedBuffer(this, ALLOCATE_BUFFER_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  struct AllocateSignature : public RootSignatureMask
  {
    // CBVs
    RootDescriptor<RootDescriptorType::ConstantBuffer> globalCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> geometryCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> updateCB;
    // UAVs
    uint32_t cbtBufferCounter = 0;
    RootDescriptor<RootDescriptorType::UnorderedAccess>* cbtBuffer; // MEGKÉRDEZ

    RootDescriptor<RootDescriptorType::UnorderedAccess> bisectorDataBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> memoryBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> allocatedBuffer;
    AllocateSignature(const RootSignatureContext& context) :
      RootSignatureMask(context),
      globalCB(this, GLOBAL_CB_BINDING_SLOT),
      geometryCB(this, GEOMETRY_CB_BINDING_SLOT),
      updateCB(this, UPDATE_CB_BINDING_SLOT),
      bisectorDataBuffer(this, BISECTOR_DATA_BUFFER_BINDING_SLOT),
      memoryBuffer(this, MEMORY_BUFFER_BINDING_SLOT),
      allocatedBuffer(this, ALLOCATE_BUFFER_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  struct BisectSignature : public RootSignatureMask
  {
    // CBVs
    RootDescriptor<RootDescriptorType::ConstantBuffer> globalCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> geometryCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> updateCB;
    // UAVs
    uint32_t cbtBufferCounter = 0;
    RootDescriptor<RootDescriptorType::UnorderedAccess>* cbtBuffer; // MEGKÉRDEZ

    RootDescriptor<RootDescriptorType::UnorderedAccess> allocatedBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> heapIDBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> bisectorDataBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> neighborsBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> neighborsOutputBuffer;
    BisectSignature(const RootSignatureContext& context) :
      RootSignatureMask(context),
      globalCB(this, GLOBAL_CB_BINDING_SLOT),
      geometryCB(this, GEOMETRY_CB_BINDING_SLOT),
      updateCB(this, UPDATE_CB_BINDING_SLOT),
      allocatedBuffer(this, ALLOCATE_BUFFER_BINDING_SLOT),
      heapIDBuffer(this, HEAP_ID_BUFFER_BINDING_SLOT),
      bisectorDataBuffer(this, BISECTOR_DATA_BUFFER_BINDING_SLOT),
      neighborsBuffer(this, NEIGHBORS_BUFFER_BINDING_SLOT),
      neighborsOutputBuffer(this, NEIGHBORS_OUTPUT_BUFFER_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  struct PropagateSignature : public RootSignatureMask
  {
    // CBVs
    RootDescriptor<RootDescriptorType::ConstantBuffer> globalCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> geometryCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> updateCB;
    // UAVs
    uint32_t cbtBufferCounter = 0;
    RootDescriptor<RootDescriptorType::UnorderedAccess>* cbtBuffer; // MEGKÉRDEZ

    RootDescriptor<RootDescriptorType::UnorderedAccess> propagateBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> bisectorDataBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> neighborsBuffer;
    PropagateSignature(const RootSignatureContext& context) :
      RootSignatureMask(context),
      globalCB(this, GLOBAL_CB_BINDING_SLOT),
      geometryCB(this, GEOMETRY_CB_BINDING_SLOT),
      updateCB(this, UPDATE_CB_BINDING_SLOT),
      propagateBuffer(this, PROPAGATE_BUFFER_BINDING_SLOT),
      bisectorDataBuffer(this, BISECTOR_DATA_BUFFER_BINDING_SLOT),
      neighborsBuffer(this, NEIGHBORS_BUFFER_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  struct SimplifySignature : public RootSignatureMask
  {
    // CBVs
    RootDescriptor<RootDescriptorType::ConstantBuffer> globalCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> geometryCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> updateCB;
    // UAVs
    uint32_t cbtBufferCounter = 0;
    RootDescriptor<RootDescriptorType::UnorderedAccess>* cbtBuffer; // MEGKÉRDEZ

    RootDescriptor<RootDescriptorType::UnorderedAccess> simplificationBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> bisectorDataBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> neighborsBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> heapIDBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> propagateBuffer;
    SimplifySignature(const RootSignatureContext& context) :
      RootSignatureMask(context),
      globalCB(this, GLOBAL_CB_BINDING_SLOT),
      geometryCB(this, GEOMETRY_CB_BINDING_SLOT),
      updateCB(this, UPDATE_CB_BINDING_SLOT),
      simplificationBuffer(this, SIMPLIFICATION_BUFFER_BINDING_SLOT),
      bisectorDataBuffer(this, BISECTOR_DATA_BUFFER_BINDING_SLOT),
      neighborsBuffer(this, NEIGHBORS_BUFFER_BINDING_SLOT),
      heapIDBuffer(this, HEAP_ID_BUFFER_BINDING_SLOT),
      propagateBuffer(this, PROPAGATE_BUFFER_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  struct ResetBuffersSignature : public RootSignatureMask
  {
    // UAVs
    uint32_t cbtBufferCounter = 0;
    RootDescriptor<RootDescriptorType::UnorderedAccess>* cbtBuffer; // MEGKÉRDEZ

    RootDescriptor<RootDescriptorType::UnorderedAccess> memoryBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> classificationBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> allocateBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> indirectDrawBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> simplificationBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> propagateBuffer;
    ResetBuffersSignature(const RootSignatureContext& context) :
      RootSignatureMask(context),
      memoryBuffer(this, MEMORY_BUFFER_BINDING_SLOT),
      classificationBuffer(this, CLASSIFICATION_BUFFER_BINDING_SLOT),
      allocateBuffer(this,ALLOCATE_BUFFER_BINDING_SLOT),
      indirectDrawBuffer(this,INDIRECT_DRAW_BUFFER_BINDING_SLOT),
      simplificationBuffer(this,SIMPLIFICATION_BUFFER_BINDING_SLOT),
      propagateBuffer(this,PROPAGATE_BUFFER_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  #pragma region Update Tree Signatures

  struct UpdateTreeSignature0 : public RootSignatureMask
  {
    // UAVs
    RootDescriptor<RootDescriptorType::UnorderedAccess> cbtBuffer0;
    RootDescriptor<RootDescriptorType::UnorderedAccess> cbtBuffer1;
    UpdateTreeSignature0(const RootSignatureContext& context) :
      RootSignatureMask(context),
      cbtBuffer0(this, CBT_BUFFER0_BINDING_SLOT),
      cbtBuffer1(this, CBT_BUFFER1_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  struct UpdateTreeSignature1 : public RootSignatureMask
  {
    // UAVs
    RootDescriptor<RootDescriptorType::UnorderedAccess> cbtBuffer0;
    RootDescriptor<RootDescriptorType::UnorderedAccess> cbtBuffer1;
    UpdateTreeSignature1(const RootSignatureContext& context) :
      RootSignatureMask(context),
      cbtBuffer0(this, CBT_BUFFER0_BINDING_SLOT),
      cbtBuffer1(this, CBT_BUFFER1_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };
  struct UpdateTreeSignature2 : public RootSignatureMask
  {
    // UAVs
    RootDescriptor<RootDescriptorType::UnorderedAccess> cbtBuffer0;
    RootDescriptor<RootDescriptorType::UnorderedAccess> cbtBuffer1;
    UpdateTreeSignature2(const RootSignatureContext& context) :
      RootSignatureMask(context),
      cbtBuffer0(this, CBT_BUFFER0_BINDING_SLOT),
      cbtBuffer1(this, CBT_BUFFER1_BINDING_SLOT)
    {
      Flags = RootSignatureFlags::AllowInputAssemblerInputLayout;
    }
  };

  struct UpdateTreeSignatureGroup
  {
    UpdateTreeSignature0 firstPass;
    UpdateTreeSignature1 secondPass;
    UpdateTreeSignature2 thirdPass;

    UpdateTreeSignatureGroup(const RootSignatureContext& context) :
      firstPass(context),
      secondPass(context),
      thirdPass(context)
    {}
  };

  #pragma endregion

  #pragma endregion

  constexpr auto NUM_CBV_BINDING_SLOTS = 3;
  constexpr auto NUM_SRV_BINDING_SLOTS = 2;
  constexpr auto NUM_UAV_BINDING_SLOTS = 17;

  struct CBTUpdateRootSignature : public RootSignatureMask
  {
    // CBVs
    RootDescriptor<RootDescriptorType::ConstantBuffer> globalCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> geometryCB;
    RootDescriptor<RootDescriptorType::ConstantBuffer> updateCB;
    // SRVs
    RootDescriptor<RootDescriptorType::ShaderResource> currentVertexBuffer;
    RootDescriptor<RootDescriptorType::ShaderResource> indexedBisectorBuffer;
    // UAVs
    // CBT buffers
    RootDescriptor<RootDescriptorType::UnorderedAccess> cbtBuffer00;
    RootDescriptor<RootDescriptorType::UnorderedAccess> cbtBuffer01;
    // Bisector buffers
    RootDescriptor<RootDescriptorType::UnorderedAccess> heapIDBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> neighborsBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> neighborsOutputBuffer;
    // Intermediate buffers
    RootDescriptor<RootDescriptorType::UnorderedAccess> BisectorDataBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> classificationBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> simplificationBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> allocateBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> propegateBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> memoryBuffer;
    // Indexation buffers
    RootDescriptor<RootDescriptorType::UnorderedAccess> indirectDispatchBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> indirectDrawBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> bisectorIndicesBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> visibleBisectorIndicesBuffer;
    RootDescriptor<RootDescriptorType::UnorderedAccess> ModifiedBisectorIndicesBuffer;
    // Debug
    RootDescriptor<RootDescriptorType::UnorderedAccess> validationBuffer;
  };
}
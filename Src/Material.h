#pragma once

#include "Common.h"

class MaterialPipeline
{
public:
	MaterialPipeline() = delete;
	MaterialPipeline(ID3D12Device* device, RenderPass renderPass, VertexFormat::Type vertexFormat, const std::string vs, const std::string ps, const std::string rootSig);
	void Bind(ID3D12GraphicsCommandList* cmdList) const;

private:
	Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pso;
};

class Material
{
public:
	Material() = default;
	Material(const std::string& name);

	virtual void BindPipeline(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, RenderPass renderPass, VertexFormat::Type vertexFormat) = 0;
	virtual void BindConstants(ID3D12GraphicsCommandList* cmdList) const = 0;
	bool IsValid() const;

protected:
	std::unique_ptr<MaterialPipeline> m_pipelines[RenderPass::Count][VertexFormat::Type::Count];
	std::string m_name;
	bool m_valid;
};

class NullMaterial : public Material
{
public:
	NullMaterial() = default;
	void BindPipeline(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, RenderPass renderPass, VertexFormat::Type vertexFormat) override {};
	void BindConstants(ID3D12GraphicsCommandList* cmdList) const override {};
};

class DefaultOpaqueMaterial : public Material
{
	static inline std::string k_vs = "mtl_default.vs.cso";
	static inline std::string k_ps = "mtl_default.ps.cso";
	static inline std::string k_rootSig = "mtl_default.rootsig.cso";
	static inline uint32_t k_srvDescriptorIndex = 2;

public:
	DefaultOpaqueMaterial(std::string& name, const D3D12_GPU_DESCRIPTOR_HANDLE srvHandle);
	void BindPipeline(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, RenderPass renderPass, VertexFormat::Type vertexFormat) override;
	void BindConstants(ID3D12GraphicsCommandList* cmdList) const override;

private:
	D3D12_GPU_DESCRIPTOR_HANDLE m_srvBegin;
};

class DefaultMaskedMaterial : public Material
{
	static inline std::string k_vs = "mtl_masked.vs.cso";
	static inline std::string k_ps = "mtl_masked.ps.cso";
	static inline std::string k_rootSig = "mtl_masked.rootsig.cso";
	static inline uint32_t k_srvDescriptorIndex = 2;

public:
	DefaultMaskedMaterial(std::string& name, const D3D12_GPU_DESCRIPTOR_HANDLE srvHandle);
	void BindPipeline(ID3D12Device* device, ID3D12GraphicsCommandList* cmdList, RenderPass renderPass, VertexFormat::Type vertexFormat) override;
	void BindConstants(ID3D12GraphicsCommandList* cmdList) const override;

private:
	D3D12_GPU_DESCRIPTOR_HANDLE m_srvBegin;
};
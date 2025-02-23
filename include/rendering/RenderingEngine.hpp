#pragma once
#include "rendering/renderer/Renderer.hpp"

namespace Ge
{
	enum ERenderingEngineType
	{
		Rasterization,
		RaytracingCPU,
		RaytracingGPU
	};

	struct SRenderingEngineCreateInfo
	{
		ERenderingEngineType e_rendering_engine_type;
		SRendererCreateInfo* p_renderer_create_info;
	};

	class RenderingEngine
	{
	public:

		virtual ~RenderingEngine() = default;
		virtual void Initialize(const SRenderingEngineCreateInfo& _renderingEngineCreateInfo) = 0;
		virtual void Release() = 0;
		virtual void Render(float _lag) = 0;

		Renderer* GetRenderer();

	protected:

		bool m_initialized = false;
		Renderer* mp_renderer = nullptr;

	};

}
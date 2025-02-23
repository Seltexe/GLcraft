#include "RenderingEngine.hpp"

namespace Ge
{
	class RasterizationEngine : public RenderingEngine
	{
	public:
		~RasterizationEngine() override;
		void Initialize(const SRenderingEngineCreateInfo& _renderingEngineCreateInfo) final;
		void Release() final;
		void Render(float _lag) final;
	};


}
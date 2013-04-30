#pragma once

#include "minko/Common.hpp"
#include "minko/scene/controller/AbstractController.hpp"

namespace minko
{
	namespace scene
	{
		namespace controller
		{
			using namespace minko;
			using namespace minko::render;
			using namespace minko::render::geometry;
			using namespace minko::scene::data;

			class SurfaceController :
				public AbstractController,
				public std::enable_shared_from_this<SurfaceController>
			{
			public:
				typedef std::shared_ptr<SurfaceController>	ptr;

			public:
				static
				ptr
				create(std::shared_ptr<Geometry> geometry, std::shared_ptr<DataProvider> material)
				{
					ptr surface(new SurfaceController(geometry, material));

					surface->initialize();

					return surface;
				}

			private:
				std::shared_ptr<Geometry>		_geometry;
				std::shared_ptr<DataProvider>	_material;

				std::shared_ptr<DrawCall>		_drawCall;

			private:
				SurfaceController(std::shared_ptr<Geometry> geometry, std::shared_ptr<DataProvider> material);

				void
				initialize();

				void
				targetAddedHandler(std::shared_ptr<AbstractController> ctrl, std::shared_ptr<Node> target);

				void
				targetRemovedHandler(std::shared_ptr<AbstractController> ctrl, std::shared_ptr<Node> target);
			};
		}
	}
}
			
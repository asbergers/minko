/*
Copyright (c) 2014 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "minko/Common.hpp"
#include "minko/Signal.hpp"
#include "minko/component/AbstractComponent.hpp"
#include "minko/data/ArrayProvider.hpp"

namespace minko
{
    namespace component
    {
        class Picking :
            public AbstractComponent
        {
        public:
            typedef std::shared_ptr<Picking>                    Ptr;
            typedef std::shared_ptr<Renderer>                   RendererPtr;
            typedef std::shared_ptr<AbstractComponent>          AbsCtrlPtr;
            typedef std::shared_ptr<scene::Node>                NodePtr;
            typedef std::shared_ptr<render::Texture>            TexturePtr;
            typedef std::shared_ptr<render::AbstractContext>    ContextPtr;
            typedef std::shared_ptr<SceneManager>               SceneManagerPtr;
            typedef std::shared_ptr<input::Mouse>               MousePtr;
            typedef std::shared_ptr<input::Touch>               TouchPtr;
            typedef std::shared_ptr<math::Matrix4x4>            MatrixPtr;
            typedef std::shared_ptr<Surface>                    SurfacePtr;
            typedef std::shared_ptr<data::ArrayProvider>        ArrayProviderPtr;
            typedef std::shared_ptr<data::StructureProvider>    StructureProviderPtr;
            typedef std::shared_ptr<AbstractCanvas>             AbstractCanvasPtr;

        private:
            TexturePtr                                          _renderTarget;
            RendererPtr                                         _renderer;
            SceneManagerPtr                                     _sceneManager;
            MousePtr                                            _mouse;
            TouchPtr                                            _touch;
            NodePtr                                             _camera;
            MatrixPtr                                           _pickingProjection;
            std::map<SurfacePtr, uint>                          _surfaceToPickingId;
            std::map<uint, SurfacePtr>                          _pickingIdToSurface;
            std::map<SurfacePtr, StructureProviderPtr>          _surfaceToProvider;
            std::map<NodePtr, StructureProviderPtr>             _targetToProvider;
            uint                                                _pickingId;
            ContextPtr                                          _context;
            StructureProviderPtr                                _pickingProvider;

            std::vector<NodePtr>                                _descendants;

            Signal<AbsCtrlPtr, NodePtr>::Slot                   _targetAddedSlot;
            Signal<AbsCtrlPtr, NodePtr>::Slot                   _targetRemovedSlot;
            Signal<NodePtr, NodePtr, NodePtr>::Slot             _addedSlot;
            Signal<NodePtr, NodePtr, NodePtr>::Slot             _removedSlot;
            Signal<RendererPtr>::Slot                           _renderingBeginSlot;
            Signal<RendererPtr>::Slot                           _renderingEndSlot;
            Signal<NodePtr, NodePtr, AbsCtrlPtr>::Slot          _componentAddedSlot;
            Signal<NodePtr, NodePtr, AbsCtrlPtr>::Slot          _componentRemovedSlot;

            Signal<NodePtr>::Ptr                                _mouseOver;
            Signal<NodePtr>::Ptr                                _mouseRightDown;
            Signal<NodePtr>::Ptr                                _mouseLeftDown;
            Signal<NodePtr>::Ptr                                _mouseRightUp;
            Signal<NodePtr>::Ptr                                _mouseLeftUp;
            Signal<NodePtr>::Ptr                                _mouseRightClick;
            Signal<NodePtr>::Ptr                                _mouseLeftClick;
            Signal<NodePtr>::Ptr                                _mouseOut;
            Signal<NodePtr>::Ptr                                _mouseMove;

            Signal<NodePtr>::Ptr                                _touchDown;
            Signal<NodePtr>::Ptr                                _touchUp;
            Signal<NodePtr>::Ptr                                _touchMove;
            Signal<NodePtr>::Ptr                                _tap;
            Signal<NodePtr>::Ptr                                _doubleTap;
            Signal<NodePtr>::Ptr                                _longHold;

            unsigned char                                       _lastColor[4];
            SurfacePtr                                          _lastPickedSurface;

            Signal<MousePtr, int, int>::Slot                    _mouseMoveSlot;
            Signal<MousePtr>::Slot                              _mouseRightDownSlot;
            Signal<MousePtr>::Slot                              _mouseLeftDownSlot;
            Signal<MousePtr>::Slot                              _mouseRightUpSlot;
            Signal<MousePtr>::Slot                              _mouseLeftUpSlot;
            Signal<MousePtr>::Slot                              _mouseRightClickSlot;
            Signal<MousePtr>::Slot                              _mouseLeftClickSlot;
            Signal<TouchPtr, int, float, float>::Slot           _touchDownSlot;
            Signal<TouchPtr, int, float, float>::Slot           _touchUpSlot;
            Signal<TouchPtr, int, float, float>::Slot           _touchMoveSlot;
            Signal<TouchPtr, float, float>::Slot                _touchTapSlot;
            Signal<TouchPtr, float, float>::Slot                _touchDoubleTapSlot;
            Signal<TouchPtr, float, float>::Slot                _touchLongHoldSlot;

            bool                                                _executeMoveHandler;
            bool                                                _executeRightClickHandler;
            bool                                                _executeLeftClickHandler;
            bool                                                _executeRightDownHandler;
            bool                                                _executeLeftDownHandler;
            bool                                                _executeRightUpHandler;
            bool                                                _executeLeftUpHandler;
            bool                                                _executeTouchDownHandler;
            bool                                                _executeTouchUpHandler;
            bool                                                _executeTouchMoveHandler;
            bool                                                _executeTapHandler;
            bool                                                _executeDoubleTapHandler;
            bool                                                _executeLongHoldHandler;

            bool                                                _addPickingLayout;
            bool                                                _emulateMouseWithTouch;

        public:
            inline static
            Ptr
            create(NodePtr camera, bool addPickingLayoutToNodes = true, bool emulateMouseWithTouch = true)
            {
                Ptr picking = std::shared_ptr<Picking>(new Picking());

                picking->initialize(camera, addPickingLayoutToNodes, emulateMouseWithTouch);

                return picking;
            }

            inline
            Signal<NodePtr>::Ptr
            mouseOver()
            {
                return _mouseOver;
            }

            inline
            Signal<NodePtr>::Ptr
            mouseRightDown()
            {
                return _mouseRightDown;
            }

            inline
            Signal<NodePtr>::Ptr
            mouseRightUp()
            {
                return _mouseRightUp;
            }

            inline
            Signal<NodePtr>::Ptr
            mouseDown()
            {
                return _mouseLeftDown;
            }

            inline
            Signal<NodePtr>::Ptr
            mouseUp()
            {
                return _mouseLeftUp;
            }

            inline
            Signal<NodePtr>::Ptr
            mouseRightClick()
            {
                return _mouseRightClick;
            }

            inline
            Signal<NodePtr>::Ptr
            mouseClick()
            {
                return _mouseLeftClick;
            }

            inline
            Signal<NodePtr>::Ptr
            mouseOut()
            {
                return _mouseOut;
            }

            inline
            Signal<NodePtr>::Ptr
            mouseMove()
            {
                return _mouseMove;
            }

            inline
            Signal<NodePtr>::Ptr
            touchDown()
            {
                return _touchDown;
            }

            inline
            Signal<NodePtr>::Ptr
            touchMove()
            {
                return _touchMove;
            }

            inline
            Signal<NodePtr>::Ptr
            touchUp()
            {
                return _touchUp;
            }

            inline
            Signal<NodePtr>::Ptr
            touchTap()
            {
                return _tap;
            }

            inline
            Signal<NodePtr>::Ptr
            touchDoubleTap()
            {
                return _doubleTap;
            }

            inline
            Signal<NodePtr>::Ptr
            touchLongHold()
            {
                return _longHold;
            }

            inline
            SurfacePtr
            pickedSurface()
            {
                return _lastPickedSurface;
            }

        private:
            void
            initialize(NodePtr camera, bool addPickingLayout, bool emulateMouseWithTouch);

            void
            targetAddedHandler(AbsCtrlPtr ctrl, NodePtr target);

            void
            targetRemovedHandler(AbsCtrlPtr ctrl, NodePtr target);

            void
            bindSignals();

            void
            addedHandler(NodePtr node, NodePtr target, NodePtr parent);

            void
            removedHandler(NodePtr node, NodePtr target, NodePtr parent);

            void
            componentAddedHandler(NodePtr node, NodePtr target, AbsCtrlPtr    ctrl);

            void
            componentRemovedHandler(NodePtr node, NodePtr target, AbsCtrlPtr ctrl);

            void
            addSurfacesForNode(NodePtr node);

            void
            removeSurfacesForNode(NodePtr node);

            void
            addSurface(SurfacePtr surface);

            void
            removeSurface(SurfacePtr surface, NodePtr node);

            void
            renderingBegin(RendererPtr renderer);

            void
            renderingEnd(RendererPtr renderer);

            Picking();

            void
            mouseMoveHandler(MousePtr mouse, int dx, int dy);

            void
            mouseRightDownHandler(MousePtr mouse);

            void
            mouseLeftDownHandler(MousePtr mouse);

            void
            mouseRightClickHandler(MousePtr mouse);

            void
            mouseLeftClickHandler(MousePtr mouse);

            void
            mouseRightUpHandler(MousePtr mouse);

            void
            mouseLeftUpHandler(MousePtr mouse);

            void
            touchDownHandler(TouchPtr touch, int identifier, float x, float y);

            void
            touchUpHandler(TouchPtr touch, int identifier, float x, float y);

            void
            touchMoveHandler(TouchPtr touch, int identifier, float x, float y);

            void
            touchTapHandler(TouchPtr touch, float x, float y);

            void
            touchDoubleTapHandler(TouchPtr touch, float x, float y);

            void
            touchLongHoldHandler(TouchPtr touch, float x, float y);

            void
            updateDescendants(NodePtr target);
        };
    }
}

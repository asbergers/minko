/*
Copyright (c) 2013 Aerys

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

#include "BoxShape.hpp"
#include "minko/math/Matrix4x4.hpp"

using namespace minko;
using namespace minko::math;
using namespace minko::component;

void
bullet::BoxShape::apply(std::shared_ptr<math::Matrix4x4> matrix)
{
/*	
	_localScaleX	= matrix->values()[0] * _halfExtentX;
	_localScaleY	= matrix->values()[5] * _halfExtentY;
	_localScaleZ	= matrix->values()[10] * _halfExtentZ;
	*/

	_halfExtentX	= matrix->values()[0]  * 0.5f;
	_halfExtentY	= matrix->values()[5]  * 0.5f;
	_halfExtentZ	= matrix->values()[10] * 0.5f;

	std::cout << "bullet::BoxShape::apply\t-> half extents = " << _halfExtentX << ", " << _halfExtentY << ", " << _halfExtentZ << std::endl;
}

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

#include "minko/math/Vector3.hpp"

namespace minko
{
    namespace math
    {
        class Ray
        {
        public:
            typedef std::shared_ptr<Ray>        Ptr;

        private:
            typedef std::shared_ptr<Vector3>    Vector3Ptr;

        private:
            Vector3Ptr                          _origin;
            Vector3Ptr                          _direction;

        public:
            inline static
            Ptr
            create(Vector3Ptr origin, Vector3Ptr direction)
            {
                return std::shared_ptr<Ray>(new Ray(origin, direction));
            }

            inline static
            Ptr
            create()
            {
                return std::shared_ptr<Ray>(new Ray());
            }

            inline
            Vector3Ptr
            direction()
            {
                return _direction;
            }

            inline
            Vector3Ptr
            origin()
            {
                return _origin;
            }

        private:
            Ray(Vector3Ptr origin, Vector3Ptr direction) :
                _origin(Vector3::create(origin)),
                _direction(Vector3::create(direction))
            {
            }

            Ray() :
                _origin(Vector3::create()),
                _direction(Vector3::create(0.f, 0.f, -1.f))
            {
            }
        };
    }
}
/*
 * Copyright 2011-2017 Blender Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __UTIL_MATH_FLOAT8_H__
#define __UTIL_MATH_FLOAT8_H__

#ifndef __UTIL_MATH_H__
#  error "Do not include this file directly, include util_types.h instead."
#endif

CCL_NAMESPACE_BEGIN

/*******************************************************************************
 * Declaration.
 */

#ifndef __KERNEL_OPENCL__
ccl_device_inline float8 operator-(const float8 &a);
ccl_device_inline float8 operator*(const float8 &a, const float8 &b);
ccl_device_inline float8 operator*(const float8 &a, float f);
ccl_device_inline float8 operator*(float f, const float8 &a);
ccl_device_inline float8 operator/(const float8 &a, float f);
ccl_device_inline float8 operator/(const float8 &a, const float8 &b);
ccl_device_inline float8 operator+(const float8 &a, const float f);
ccl_device_inline float8 operator+(const float8 &a, const float8 &b);
ccl_device_inline float8 operator-(const float8 &a, const float f);
ccl_device_inline float8 operator-(const float8 &a, const float8 &b);
ccl_device_inline float8 operator+=(float8 &a, const float8 &b);
ccl_device_inline float8 operator*=(float8 &a, const float8 &b);
ccl_device_inline float8 operator*=(float8 &a, float f);
ccl_device_inline float8 operator/=(float8 &a, float f);

ccl_device_inline bool operator==(const float8 &a, const float8 &b);

ccl_device_inline float8 rcp(const float8 &a);
ccl_device_inline float8 safe_rcp(const float8 &a);
ccl_device_inline float8 sqrt(const float8 &a);
ccl_device_inline float8 sqr(const float8 &a);
ccl_device_inline bool is_zero(const float8 &a);
ccl_device_inline float average(const float8 &a);
ccl_device_inline float8 min(const float8 &a, const float8 &b);
ccl_device_inline float8 max(const float8 &a, const float8 &b);
ccl_device_inline float8 clamp(const float8 &a, const float8 &mn, const float8 &mx);
ccl_device_inline float8 fabs(const float8 &a);
ccl_device_inline float8 floor(const float8 &a);
ccl_device_inline float8 mix(const float8 &a, const float8 &b, float t);
#endif /* !__KERNEL_OPENCL__*/

ccl_device_inline float8 safe_divide(const float8 a, const float b);
ccl_device_inline float8 safe_divide(const float8 a, const float8 b);
ccl_device_inline float8 safe_divide_even(const float8 a, const float8 b);

#ifndef __KERNEL_GPU__
ccl_device_inline float8 select(const int4 &mask, const float8 &a, const float8 &b);
ccl_device_inline float8 reduce_min(const float8 &a);
ccl_device_inline float8 reduce_max(const float8 &a);
ccl_device_inline float8 reduce_add(const float8 &a);

ccl_device_inline float reduce_min_f(const float8 &a);
ccl_device_inline float reduce_max_f(const float8 &a);
ccl_device_inline float reduce_add_f(const float8 &a);

ccl_device_inline float8 saturate(const float8 &a);
ccl_device_inline bool isequal(const float8 a, const float8 b);
#endif /* !__KERNEL_GPU__ */

/*******************************************************************************
 * Definition.
 */

#ifndef __KERNEL_OPENCL__
ccl_device_inline float8 operator-(const float8 &a)
{
  return a * -1.0f;
}

ccl_device_inline float8 operator*(const float8 &a, const float8 &b)
{
  return make_float8(
      a.a * b.a, a.b * b.b, a.c * b.c, a.d * b.d, a.e * b.e, a.f * b.f, a.g * a.g, a.h * b.h);
}

ccl_device_inline float8 operator*(const float8 &a, float f)
{
  return make_float8(a.a * f, a.b * f, a.c * f, a.d * f, a.e * f, a.f * f, a.g * f, a.h * f);
}

ccl_device_inline float8 operator*(float f, const float8 &a)
{
  return a * f;
}

ccl_device_inline float8 operator/(const float8 &a, float f)
{
  return a * (1.0f / f);
}

ccl_device_inline float8 operator/(const float8 &a, const float8 &b)
{
  return make_float8(
      a.a / b.a, a.b / b.b, a.c / b.c, a.d / b.d, a.e / b.e, a.f / b.f, a.g / b.g, a.h / b.h);
}

ccl_device_inline float8 operator+(const float8 &a, const float f)
{
  return a + make_float8(f);
}

ccl_device_inline float8 operator+(const float8 &a, const float8 &b)
{
  return make_float8(
      a.a + b.a, a.b + b.b, a.c + b.c, a.d + b.d, a.e + b.e, a.f + b.f, a.g + b.g, a.h + b.h);
}

ccl_device_inline float8 operator-(const float8 &a, const float f)
{
  return a - make_float8(f);
}

ccl_device_inline float8 operator-(const float8 &a, const float8 &b)
{
  return make_float8(
      a.a - b.a, a.b - b.b, a.c - b.c, a.d - b.d, a.e - b.e, a.f - b.f, a.g - b.g, a.h - b.h);
}

ccl_device_inline float8 operator+=(float8 &a, const float8 &b)
{
  return a = a + b;
}

ccl_device_inline float8 operator-=(float8 &a, const float8 &b)
{
  return a = a - b;
}

ccl_device_inline float8 operator*=(float8 &a, const float8 &b)
{
  return a = a * b;
}

ccl_device_inline float8 operator*=(float8 &a, float f)
{
  return a = a * f;
}

ccl_device_inline float8 operator/=(float8 &a, float f)
{
  return a = a / f;
}

ccl_device_inline bool operator==(const float8 &a, const float8 &b)
{
  return (a.a == b.a && a.b == b.b && a.c == b.c && a.d == b.d && a.e == b.e && a.f == b.f &&
          a.g == b.g && a.h == b.h);
}

ccl_device_inline float8 rcp(const float8 &a)
{
  return make_float8(1.0f / a.a,
                     1.0f / a.b,
                     1.0f / a.c,
                     1.0f / a.d,
                     1.0f / a.e,
                     1.0f / a.f,
                     1.0f / a.g,
                     1.0f / a.h);
}

ccl_device_inline float8 safe_rcp(const float8 &a)
{
  return make_float8(a.a == 0.0f ? 0.0f : 1.0f / a.a,
                     a.b == 0.0f ? 0.0f : 1.0f / a.b,
                     a.c == 0.0f ? 0.0f : 1.0f / a.c,
                     a.d == 0.0f ? 0.0f : 1.0f / a.d,
                     a.e == 0.0f ? 0.0f : 1.0f / a.e,
                     a.f == 0.0f ? 0.0f : 1.0f / a.f,
                     a.g == 0.0f ? 0.0f : 1.0f / a.g,
                     a.h == 0.0f ? 0.0f : 1.0f / a.h);
}

ccl_device_inline float8 sqrt(const float8 &a)
{
  return make_float8(sqrtf(a.a),
                     sqrtf(a.b),
                     sqrtf(a.c),
                     sqrtf(a.d),
                     sqrtf(a.e),
                     sqrtf(a.f),
                     sqrtf(a.g),
                     sqrtf(a.h));
}

ccl_device_inline float8 sqr(const float8 &a)
{
  return a * a;
}

ccl_device_inline bool is_zero(const float8 &a)
{
  return (a.a == 0.0f && a.b == 0.0f && a.c == 0.0f && a.d == 0.0f && a.e == 0.0f && a.f == 0.0f &&
          a.g == 0.0f && a.h == 0.0f);
}

ccl_device_inline float average(const float8 &a)
{
  return reduce_add_f(a) / 8.0f;
}

ccl_device_inline float8 min(const float8 &a, const float8 &b)
{
  return make_float8(min(a.a, b.a),
                     min(a.b, b.b),
                     min(a.c, b.c),
                     min(a.d, b.d),
                     min(a.e, b.e),
                     min(a.f, b.f),
                     min(a.g, b.g),
                     min(a.h, b.h));
}

ccl_device_inline float8 max(const float8 &a, const float8 &b)
{
  return make_float8(max(a.a, b.a),
                     max(a.b, b.b),
                     max(a.c, b.c),
                     max(a.d, b.d),
                     max(a.e, b.e),
                     max(a.f, b.f),
                     max(a.g, b.g),
                     max(a.h, b.h));
}

ccl_device_inline float8 clamp(const float8 &a, const float8 &mn, const float8 &mx)
{
  return min(max(a, mn), mx);
}

ccl_device_inline float8 fabs(const float8 &a)
{
  return make_float8(fabsf(a.a),
                     fabsf(a.b),
                     fabsf(a.c),
                     fabsf(a.d),
                     fabsf(a.e),
                     fabsf(a.f),
                     fabsf(a.g),
                     fabsf(a.h));
}

ccl_device_inline float8 mix(const float8 &a, const float8 &b, float t)
{
  return a + t * (b - a);
}

#endif /* !__KERNEL_OPENCL__*/

#ifndef __KERNEL_GPU__

ccl_device_inline float8 reduce_min(const float8 &a)
{
  return make_float8(min(min(min(a.a, a.b), min(a.c, a.d)), min(min(a.e, a.f), min(a.g, a.h))));
}

ccl_device_inline float8 reduce_max(const float8 &a)
{
  return make_float8(max(max(max(a.a, a.b), max(a.c, a.d)), max(max(a.e, a.f), max(a.g, a.h))));
}

ccl_device_inline float8 reduce_add(const float8 &a)
{
  return make_float8(a.a + a.b + a.c + a.d + a.e + a.f + a.g + a.h);
}

ccl_device_inline float reduce_min_f(const float8 &a)
{
  return reduce_min(a).a;
}

ccl_device_inline float reduce_max_f(const float8 &a)
{
  return reduce_max(a).a;
}

ccl_device_inline float reduce_add_f(const float8 &a)
{
  return reduce_add(a).a;
}

ccl_device_inline float8 saturate(const float8 &a)
{
  return clamp(a, make_float8(0.0f), make_float8(1.0f));
}

ccl_device_inline bool isequal(const float8 a, const float8 b)
{
  return a == b;
}

#endif /* !__KERNEL_GPU__ */

ccl_device_inline float8 safe_divide(const float8 a, const float b)
{
  return (b != 0.0f) ? a / b : make_float8(0.0f);
}

ccl_device_inline float8 safe_divide(const float8 a, const float8 b)
{
  return make_float8((b.a != 0.0f) ? a.a / b.a : 0.0f,
                     (b.b != 0.0f) ? a.b / b.b : 0.0f,
                     (b.c != 0.0f) ? a.c / b.c : 0.0f,
                     (b.d != 0.0f) ? a.d / b.d : 0.0f,
                     (b.e != 0.0f) ? a.e / b.e : 0.0f,
                     (b.f != 0.0f) ? a.f / b.f : 0.0f,
                     (b.g != 0.0f) ? a.g / b.g : 0.0f,
                     (b.h != 0.0f) ? a.h / b.h : 0.0f);
}

ccl_device_inline float8 safe_divide_even(const float8 a, const float8 b)
{
  return reduce_add(safe_divide(a, b)) / 8.0f;
}

ccl_device_inline float8 ensure_finite(float8 v)
{
  if (!isfinite_safe(v.a))
    v.a = 0.0f;
  if (!isfinite_safe(v.b))
    v.b = 0.0f;
  if (!isfinite_safe(v.c))
    v.c = 0.0f;
  if (!isfinite_safe(v.d))
    v.d = 0.0f;
  if (!isfinite_safe(v.e))
    v.e = 0.0f;
  if (!isfinite_safe(v.f))
    v.f = 0.0f;
  if (!isfinite_safe(v.g))
    v.g = 0.0f;
  if (!isfinite_safe(v.h))
    v.h = 0.0f;
  return v;
}

ccl_device_inline bool isfinite_safe(float8 v)
{
  return isfinite_safe(v.a) && isfinite_safe(v.b) && isfinite_safe(v.c) && isfinite_safe(v.d) &&
         isfinite_safe(v.e) && isfinite_safe(v.f) && isfinite_safe(v.g) && isfinite_safe(v.h);
}

ccl_device_inline float8 pow(float8 v, float e)
{
  return make_float8(powf(v.a, e),
                     powf(v.b, e),
                     powf(v.c, e),
                     powf(v.d, e),
                     powf(v.e, e),
                     powf(v.f, e),
                     powf(v.g, e),
                     powf(v.h, e));
}

ccl_device_inline float8 exp(float8 v)
{
  return make_float8(
      expf(v.a), expf(v.b), expf(v.c), expf(v.d), expf(v.e), expf(v.f), expf(v.g), expf(v.h));
}

ccl_device_inline float8 log(float8 v)
{
  return make_float8(
      logf(v.a), logf(v.b), logf(v.c), logf(v.d), logf(v.e), logf(v.f), logf(v.g), logf(v.h));
}

ccl_device_inline float dot(const float8 &a, const float8 &b)
{
  return (a.a * b.a) + (a.b * b.b) + (a.c * b.c) + (a.d * b.d) + (a.e * b.e) + (a.f * b.f) +
         (a.g * b.g) + (a.h * b.h);
}

CCL_NAMESPACE_END

#endif /* __UTIL_MATH_FLOAT8_H__ */

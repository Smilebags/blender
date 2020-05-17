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

#ifndef __UTIL_TYPES_SPECTRAL_COLOR_H__
#define __UTIL_TYPES_SPECTRAL_COLOR_H__

#ifndef __UTIL_TYPES_H__
#  error "Do not include this file directly, include util_types.h instead."
#endif

CCL_NAMESPACE_BEGIN

#define WAVELENGTHS_PER_RAY 4
typedef float4 SpectralColor;

#define SPECTRAL_COLOR_FOR_EACH(counter) \
  for (int counter = 0; counter < WAVELENGTHS_PER_RAY; counter++)

#define SPECTRAL_COLOR_FOR_EACH_WAVELENGTH(wavelengths, counter, wavelength) \
  float wavelength = wavelengths[0]; \
  for (int counter = 0; counter < WAVELENGTHS_PER_RAY; \
       counter++, wavelength = wavelengths[counter])

ccl_device_inline SpectralColor make_spectral_color(float value);

CCL_NAMESPACE_END

#endif /* __UTIL_TYPES_FLOAT4_H__ */

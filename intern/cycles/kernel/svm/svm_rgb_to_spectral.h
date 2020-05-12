/*
 * Copyright 2011-2013 Blender Foundation
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

CCL_NAMESPACE_BEGIN

/* RGB to Spectral Node */

ccl_device void svm_node_rgb_to_spectral(
    KernelGlobals *kg, PathState *state, float *stack, uint color_in, uint spectral_out)
{
  /* Input */
  float3 color = stack_load_float3(stack, color_in);
  float3 spectral = linear_to_wavelength_intensities(color, state->wavelengths);

  stack_store_float3(stack, spectral_out, spectral);
}

CCL_NAMESPACE_END

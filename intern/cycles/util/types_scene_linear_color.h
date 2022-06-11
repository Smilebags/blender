/* SPDX-License-Identifier: Apache-2.0
 * Copyright 2011-2022 Blender Foundation */

#ifndef __UTIL_TYPES_SCENE_LINEAR_COLOR_H__
#define __UTIL_TYPES_SCENE_LINEAR_COLOR_H__

#ifndef __UTIL_TYPES_H__
#  error "Do not include this file directly, include util/types.h instead."
#endif

CCL_NAMESPACE_BEGIN

#define KERNEL_CHANNELS_PER_RAY 3
#define KERNEL_SCENE_LINEAR_COLOR_DATA_TYPE float3
#define KERNEL_PACKED_SCENE_LINEAR_COLOR_DATA_TYPE packed_float3

using SceneLinearColor = KERNEL_SCENE_LINEAR_COLOR_DATA_TYPE;
using PackedSceneLinearColor = KERNEL_PACKED_SCENE_LINEAR_COLOR_DATA_TYPE;

#define make_scene_linear_color(f) CONCAT(make_, KERNEL_SCENE_LINEAR_COLOR_DATA_TYPE(f))
#define load_scene_linear_color(f) CONCAT(load_, KERNEL_SCENE_LINEAR_COLOR_DATA_TYPE(f))
#define store_scene_linear_color(s, f) \
  CONCAT(store_, KERNEL_SCENE_LINEAR_COLOR_DATA_TYPE((s), (f)))

#define zero_scene_linear_color CONCAT(zero_, KERNEL_SCENE_LINEAR_COLOR_DATA_TYPE)
#define one_scene_linear_color CONCAT(one_, KERNEL_SCENE_LINEAR_COLOR_DATA_TYPE)

#define FOREACH_CHANNEL(counter) \
  for (int counter = 0; counter < KERNEL_CHANNELS_PER_RAY; counter++)

#define GET_CHANNEL(v, i) (((float *)(&(v)))[i])

CCL_NAMESPACE_END

#endif /* __UTIL_TYPES_SCENE_LINEAR_COLOR_H__ */

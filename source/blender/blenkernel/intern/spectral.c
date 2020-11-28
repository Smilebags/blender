/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/** \file
 * \ingroup bke
 */

#include "BLI_math_base.h"
#include "BLI_math_inline.h"
#include "BLI_math_matrix.h"

#include "BKE_colortools.h"
#include "BKE_spectral_stuff.h"

#include "MEM_guardedalloc.h"

static float inverse_lerp(float a, float b, float x)
{
  return (x - a) / (b - a);
}

static float lerp(float a, float b, float x)
{
  return a * (1.0f - x) + b * x;
}

void wavelength_to_xyz(const float wavelength, float *r_xyz)
{
  const static int lut_start = 360;
  const static int lut_end = 830;
  const static int lut_size = 830 - 360 + 1;

  float position = lerp(0.0f, lut_size - 1.0f, inverse_lerp(lut_start, lut_end, wavelength));

  int lower_bound = (int)position;
  int upper_bound = min_ii(lower_bound + 1, lut_size - 1);
  float progress = position - lower_bound;

  const float *lower_value = wavelength_xyz_lookup[lower_bound];
  const float *upper_value = wavelength_xyz_lookup[upper_bound];

  r_xyz[0] = lerp(lower_value[0], upper_value[0], progress);
  r_xyz[1] = lerp(lower_value[1], upper_value[1], progress);
  r_xyz[2] = lerp(lower_value[2], upper_value[2], progress);
}

void wavelength_to_xyz_from_crf(CurveMapping *cumap, const float wavelength, float *r_xyz)
{
  if (!cumap) {
    r_xyz[0] = r_xyz[1] = r_xyz[2] = 0.0f;
  }

  float wavelengths[3] = {wavelength, wavelength, wavelength};
  BKE_curvemapping_init(cumap);
  BKE_curvemapping_evaluate3F(cumap, r_xyz, wavelengths);
}

void xyz_to_linear_srgb(const float *xyz, float *r_srgb)
{
  const static float xyz_d65_to_srgb_linear_matrix[3][3] = {{3.2406255f, -1.537208f, -0.4986286f},
                                                            {-0.9689307f, 1.8757561f, 0.0415175},
                                                            {0.0557101f, -0.2040211f, 1.0569959f}};

  mul_v3_m3v3(r_srgb, xyz_d65_to_srgb_linear_matrix, xyz);
}

void BKE_curvemapping_init_cie1931(CurveMapping *cumap)
{
  const float curve_size = 830 - 360 + 1;

  for (int channel = 0; channel < 3; channel++) {
    CurveMap *curve_map = &cumap->cm[channel];

    if (curve_map->curve) {
      MEM_freeN(curve_map->curve);
    }
    curve_map->totpoint = curve_size;
    curve_map->curve = MEM_callocN(curve_map->totpoint * sizeof(CurveMapPoint), "curve points");

    for (int i = 0; i < curve_size; i++) {
      float wavelength = i + 360;
      float xyz[3];
      wavelength_to_xyz(wavelength, xyz);

      curve_map->curve[i].x = wavelength;
      curve_map->curve[i].y = wavelength_xyz_lookup[i][channel];
      curve_map->curve[i].flag |= CUMA_HANDLE_VECTOR;
    }
  }

  cumap->flag &= ~CUMA_DO_CLIP;

  BKE_curvemapping_changed_all(cumap);
}

void BKE_curvemapping_set_defaults_spectrum(CurveMapping *cumap, int channels)
{
  BKE_curvemapping_set_defaults(cumap, channels, MIN_WAVELENGTH, 0.0f, MAX_WAVELENGTH, 1.0f);
}

CurveMapping *BKE_curvemapping_add_spectrum(int channels)
{
  return BKE_curvemapping_add(channels, MIN_WAVELENGTH, 0.0f, MAX_WAVELENGTH, 1.0f);
}

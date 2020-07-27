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
 *
 * The Original Code is Copyright (C) 2005 Blender Foundation.
 * All rights reserved.
 */

#include "../node_shader_util.h"

/* **************** Gaussian Spectrum ******************** */
static bNodeSocketTemplate sh_node_gaussian_spectrum_in[] = {
    {SOCK_FLOAT, N_("Wavelength"), 500.0f, 0.0f, 0.0f, 0.0f, 380.0f, 780.0f},
    {SOCK_FLOAT, N_("Width"), 5.0f, 0.0f, 0.0f, 0.0f, 0.01f, 100.0f},
    {-1, ""},
};

static bNodeSocketTemplate sh_node_gaussian_spectrum_out[] = {
    {SOCK_RGBA, N_("Spectrum")},
    {-1, ""},
};

static void node_shader_init_gaussian_spectrum(bNodeTree *UNUSED(ntree), bNode *node)
{
  NodeGaussianSpectrum *data = MEM_callocN(sizeof(NodeGaussianSpectrum), "NodeGaussianSpectrum");
  data->normalize = true;
  node->storage = data;
}

/* node type definition */
void register_node_type_sh_gaussian_spectrum(void)
{
  static bNodeType ntype;

  sh_node_type_base(
      &ntype, SH_NODE_GAUSSIAN_SPECTRUM, "Gaussian Spectrum", NODE_CLASS_CONVERTOR, 0);
  node_type_size_preset(&ntype, NODE_SIZE_MIDDLE);
  node_type_socket_templates(&ntype, sh_node_gaussian_spectrum_in, sh_node_gaussian_spectrum_out);
  node_type_init(&ntype, node_shader_init_gaussian_spectrum);
  node_type_storage(
      &ntype, "NodeGaussianSpectrum", node_free_standard_storage, node_copy_standard_storage);

  nodeRegisterType(&ntype);
}

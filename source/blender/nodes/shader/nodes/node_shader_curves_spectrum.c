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

/** \file
 * \ingroup shdnodes
 */

#include "node_shader_util.h"

/* **************** CURVE VEC  ******************** */
static bNodeSocketTemplate sh_node_curve_spectrum_in[] = {
    {-1, ""},
};

static bNodeSocketTemplate sh_node_curve_spectrum_out[] = {
    {SOCK_RGBA, N_("Spectrum")},
    {-1, ""},
};

static void node_shader_init_curve_spectrum(bNodeTree *UNUSED(ntree), bNode *node)
{
  node->storage = BKE_curvemapping_add(3, -1.0f, -1.0f, 1.0f, 1.0f);
}

void register_node_type_sh_curve_spectrum(void)
{
  static bNodeType ntype;

  sh_node_type_base(&ntype, SH_NODE_CURVE_SPECTRUM, "Spectrum Curves", NODE_CLASS_OP_COLOR, 0);
  node_type_socket_templates(&ntype, sh_node_curve_spectrum_in, sh_node_curve_spectrum_out);
  node_type_init(&ntype, node_shader_init_curve_spectrum);
  node_type_size_preset(&ntype, NODE_SIZE_LARGE);
  node_type_storage(&ntype, "CurveMapping", node_free_curves, node_copy_curves);

  nodeRegisterType(&ntype);
}

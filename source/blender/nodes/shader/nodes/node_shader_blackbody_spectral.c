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

/* **************** Spectral Blackbody ******************** */
static bNodeSocketTemplate sh_node_blackbody_spectral_in[] = {
    {SOCK_FLOAT, N_("Temperature"), 1500.0f, 0.0f, 0.0f, 0.0f, 800.0f, 12000.0f},
    {-1, ""},
};

static bNodeSocketTemplate sh_node_blackbody_spectral_out[] = {
    {SOCK_RGBA, N_("Spectrum")},
    {-1, ""},
};

/* node type definition */
void register_node_type_sh_blackbody_spectral(void)
{
  static bNodeType ntype;

  sh_node_type_base(
      &ntype, SH_NODE_BLACKBODY_SPECTRAL, "Spectral Blackbody", NODE_CLASS_CONVERTOR, 0);
  node_type_size_preset(&ntype, NODE_SIZE_MIDDLE);
  node_type_socket_templates(
      &ntype, sh_node_blackbody_spectral_in, sh_node_blackbody_spectral_out);
  node_type_init(&ntype, NULL);
  node_type_storage(&ntype, "", NULL, NULL);

  nodeRegisterType(&ntype);
}

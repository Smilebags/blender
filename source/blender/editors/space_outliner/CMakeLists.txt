# SPDX-License-Identifier: GPL-2.0-or-later

set(INC
  ../include
  ../../blenkernel
  ../../blenlib
  ../../blentranslation
  ../../depsgraph
  ../../gpu
  ../../imbuf
  ../../makesdna
  ../../makesrna
  ../../sequencer
  ../../windowmanager
  ../../../../intern/clog
  ../../../../intern/glew-mx
  ../../../../intern/guardedalloc
  # RNA_prototypes.h
  ${CMAKE_BINARY_DIR}/source/blender/makesrna
)


set(SRC
  outliner_collections.cc
  outliner_context.cc
  outliner_dragdrop.cc
  outliner_draw.cc
  outliner_edit.cc
  outliner_ops.cc
  outliner_select.cc
  outliner_sync.cc
  outliner_tools.cc
  outliner_tree.cc
  outliner_utils.cc
  space_outliner.cc
  tree/common.cc
  tree/tree_display.cc
  tree/tree_display_data.cc
  tree/tree_display_libraries.cc
  tree/tree_display_orphaned.cc
  tree/tree_display_override_library_properties.cc
  tree/tree_display_override_library_hierarchies.cc
  tree/tree_display_scenes.cc
  tree/tree_display_sequencer.cc
  tree/tree_display_view_layer.cc
  tree/tree_element.cc
  tree/tree_element_anim_data.cc
  tree/tree_element_collection.cc
  tree/tree_element_driver.cc
  tree/tree_element_gpencil_layer.cc
  tree/tree_element_id.cc
  tree/tree_element_id_library.cc
  tree/tree_element_id_scene.cc
  tree/tree_element_nla.cc
  tree/tree_element_overrides.cc
  tree/tree_element_rna.cc
  tree/tree_element_scene_objects.cc
  tree/tree_element_seq.cc
  tree/tree_element_view_layer.cc

  outliner_intern.hh
  tree/common.hh
  tree/tree_display.hh
  tree/tree_element.hh
  tree/tree_element_anim_data.hh
  tree/tree_element_collection.hh
  tree/tree_element_driver.hh
  tree/tree_element_gpencil_layer.hh
  tree/tree_element_id.hh
  tree/tree_element_id_library.hh
  tree/tree_element_id_scene.hh
  tree/tree_element_nla.hh
  tree/tree_element_overrides.hh
  tree/tree_element_rna.hh
  tree/tree_element_scene_objects.hh
  tree/tree_element_seq.hh
  tree/tree_element_view_layer.hh
)

set(LIB
  bf_blenkernel
  bf_blenlib
  bf_editor_undo
)


blender_add_lib(bf_editor_space_outliner "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")

# RNA_prototypes.h
add_dependencies(bf_editor_space_outliner bf_rna)

<?php

/**
 * Implements hook_preprocess_block().
 */
function primo_preprocess_block(&$vars) {
  // Add ARIA roles attributes to blocks.
  $roles = array(
    'complementary' => array(
      'aggregator',
      'help',
      'locale',
      'poll',
      'profile',
      'node' => array('syndicate'),
      'system' => array('powered-by', 'help'),
      'user' => array('new', 'online'),
    ),
    'navigation' => array(
      'blog',
      'book',
      'comment',
      'forum',
      'menu',
      'menu_block',
      'node' => array('recent'),
      'shortcut',
      'statistics',
      'system' => array_keys(menu_list_system_menus()),
    ),
    'search' => array(
      'search',
    ),
    'form' => array(
      'user' => array('login'),
    ),
  );

  foreach ($roles as $role => $module) {
    if (!is_array($role) && in_array($vars['block']->module, $module)) {
      $vars['attributes_array']['role'] = "$role";
    }
    elseif (is_array($role)) {
      foreach ($role as $module => $delta) {
        if ($vars['block']->module == $module && in_array($vars['block']->delta, $delta)) {
          $vars['attributes_array']['role'] = "$role";
        }
      }
    }
  }

  // Consolidate all attributes in one variable.
  $vars['attributes_array']['id'] = $vars['block_html_id'];
  $vars['attributes_array']['class'] = $vars['classes_array'];
}

/**
 * Implements hook_process_block().
 */
function primo_process_block(&$vars) {

}

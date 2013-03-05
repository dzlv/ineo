<?php

/**
 * Implements hook_preprocess_node().
 */
function primo_preprocess_node(&$variables) {
  global $theme_key;
  $node = $variables['node'];

  // Define node type-specific variables
  // by calling their own preprocess functions (if they exist).
  // Parent or sub-theme.
  $functions = array(
    'primo_preprocess_node__' . $node->type,
    $theme_key . '_preprocess_node__' . $node->type,
  );
  foreach ($functions as $function) {
    if (function_exists($function)) {
      $function($variables);
    }
  }

  // // Add article ARIA role and lang attributes.
  $variables['attributes_array']['role'] = 'article';
  if (isset($variables['language']) && $variables['language'] != 'und') {
    $variables['attributes_array']['lang'] = $variables['language'];
  }
}

/**
 * Implements hook_process_node().
 */
function primo_process_node(&$variables) {

}

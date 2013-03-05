<?php

/**
 * Implements hook_preprocess_page().
 */
function primo_preprocess_page(&$variables) {

}

/**
 * Implements hook_page_alter().
 */
function primo_page_alter(&$page) {
  // Remove all the region wrappers.
  foreach (element_children($page) as $key => $region) {
    if (!empty($page[$region]['#theme_wrappers'])) {
      $page[$region]['#theme_wrappers'] = array_diff($page[$region]['#theme_wrappers'], array('region'));
    }
  }
  // Remove the wrapper from the main content block.
  if (!empty($page['content']['system_main'])) {
    $page['content']['system_main']['#theme_wrappers'] = array_diff($page['content']['system_main']['#theme_wrappers'], array('block'));
  }
}

/**
 * Implements hook_preprocess_region().
 */
function primo_preprocess_region(&$variables) {
  // Provide a valid, unique HTML ID.
  $variables['region'] = drupal_html_id($variables['region']);
}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function primo_preprocess_maintenance_page(&$variables) {
  primo_preprocess_html($variables);
  // primo_preprocess_page($variables);
}

/**
 * Implements hook_process_maintenance_page().
 */
function primo_process_maintenance_page(&$variables) {
  primo_process_html($variables);
  $regions = array(
    'header',
    'navigation',
    'highlighted',
    'help',
    'content',
    'sidebar_first',
    'sidebar_second',
    'footer',
    'bottom',
  );
  // Ensure default regions get a variable.
  foreach ($regions as $region) {
    if (!isset($variables[$region])) {
      $variables[$region] = '';
    }
  }
}

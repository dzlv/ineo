<?php

/**
 * @file
 * contains theme's functions to manipulate Drupal's default markup.
 * - preprocess/process templates.
 * - preprocess/process/hook theme functions.
 * - alter forms, registry, elements.
 *
 * Complete documentation for this file is available online.
 * @see http://dgo.to/1728096
 */

/**
 * Implements hook_css_alter().
 */
function ineo_css_alter(&$css) {
  // Remove unwanted stylesheets.
  // See http://dgo.to/901062 for doing so in info file.

  // Make your own choices here...
  $exclude = array(
    //'misc/ui/jquery.ui.core.css' => FALSE,
    //'misc/ui/jquery.ui.theme.css' => FALSE,
    //'modules/overlay/overlay-parent.css' => FALSE,
    //'modules/system/system.base.css' => FALSE,
    //'modules/system/system.menus.css' => FALSE,
    //'modules/system/system.messages.css' => FALSE,
    //'modules/system/system.theme.css' => FALSE,
    //'modules/comment/comment.css' => FALSE,
    //'modules/field/theme/field.css' => FALSE,
    //'modules/node/node.css' => FALSE,
    //'modules/search/search.css' => FALSE,
    //'modules/user/user.css' => FALSE,
    //'modules/contextual/contextual.css' => FALSE,
    //'modules/shortcut/shortcut.css' => FALSE,
    //'modules/toolbar/toolbar.css' => FALSE,
    //'sites/all/modules/date/date_api/date.css' => FALSE,
    //'sites/all/modules/date/date_popup/themes/datepicker.1.7.css' => FALSE,
    //'sites/all/modules/date/date_popup/themes/jquery.timeentry.css' => FALSE,
  );
  $css = array_diff_key($css, $exclude);
}

/**
 * Implements hook_preprocess().
 *
 * Preprocess variables for *.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered.
 */
function ineo_preprocess(&$variables, $hook) {

}

/**
 * Implements hook_process().
 *
 * Process variables for *.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered.
 */
function ineo_process(&$variables, $hook) {

}

/**
 * Implements hook_preprocess_html().
 *
 * Preprocess variables for html.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 */
function ineo_preprocess_html(&$variables) {

}

/**
 * Implements hook_preprocess_page().
 *
 * Preprocess variables for page.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 */
function ineo_preprocess_page(&$variables) {

}

/**
 * Implements hook_preprocess_maintenance_page().
 *
 * Preprocess variables for maintenance-page.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 */
function ineo_preprocess_maintenance_page(&$variables) {
  ineo_preprocess_html($variables);
  ineo_preprocess_page($variables);
}

/**
 * Implements hook_preprocess_region().
 *
 * Preprocess variables for region.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 */
function ineo_preprocess_region(&$variables) {

}

/**
 * Implements hook_preprocess_node().
 *
 * Preprocess variables for node.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 */
function ineo_preprocess_node(&$variables) {
  $node = $variables['node'];
  // Apply to all node content-types
}

/**
 * Primo base theme gives content-type specific preprocess functions.
 * i.e.
 * ineo_preprocess_node__page()
 * ineo_preprocess_node__article()
 */

/**
 * Implements hook_preprocess_block().
 *
 * Preprocess variables for block.tpl.php
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 */
function ineo_preprocess_block(&$variables) {

}

/**
 * Implements hook_form_alter().
 */
function ineo_form_alter(&$form, &$form_state, $form_id) {
  // Add a global class to selected forms.
  $forms = array(
    'user_login',
    'search_block_form',
    'search_form',
    'contact_site_form',
    'comment_form',
  );
  if (in_array($form_id, $forms)) {
    $form['#attributes'] = array('class' => array('ineo-form'));
  }
}

<?php

/**
 * Implements hook_form_alter().
 */
function primo_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_block_form') {
    $form['search_block_form']['#attributes']['placeholder'] = t('Search');
  }
}

/**
 * Changes the search form to use the HTML5 "search" input attribute
 */
function primo_preprocess_search_block_form(&$vars) {
  $vars['search_form'] = str_replace('type="text"', 'type="search"', $vars['search_form']);
}
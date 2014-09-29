<?php

/**
 * Implements hook_preprocess_html().
 */
function primo_preprocess_html(&$variables) {

  // Theme implementation from Drupal 8 RDFa / HTML5 html.tpl.php.
  // @see http://dgo.to/1077566
  // @see http://dgo.to/1164926

  // HTML element attributes.
  $variables['html_attributes_array'] = array(
    'class' => array('no-js'),
     'lang' => $variables['language']->language,
      'dir' => $variables['language']->dir,
  );

  // Adds RDF namespace prefix bindings in the form of an RDFa 1.1 prefix
  // attribute inside the html element.
  if (function_exists('rdf_get_namespaces')) {
    $variables['rdf'] = array('prefix' => '');
    foreach (rdf_get_namespaces() as $prefix => $uri) {
      $variables['rdf']['prefix'] .= "\n" . $prefix . ': ' . $uri;
    }
  }

  // Let sub-themes decide whether to add ie conditional comments or not.
  if ($ie_support = theme_get_setting('ie_support')) {
    unset($variables['html_attributes_array']['class']);
    $variables['theme_hook_suggestions'][] = 'html__ie';
  }

  // Consolidate all body attributes in one variable.
  $variables['body_attributes_array'] = array(
    'role'  => 'document',
    'class' => $variables['classes_array'],
  );
  $variables['body_attributes_array'] += $variables['attributes_array'];

  // Move JS files "$scripts" to page bottom for perfs/logic,
  // since most jQuery code and Drupal.behaviors wait for DOM .ready() event.
  // Add JS files that *needs* to be loaded in the head in a new "$head_scripts" scope.

  // Provide a stripped down version of Modernizr
  // if a sub-theme does not declare any.
  if ($modernizr = theme_get_setting('modernizr')) {
    $theme = $GLOBALS['theme_key'];
  }
  else {
    $theme = 'primo';
    $modernizr = '/js/vendor/modernizr.custom.js';
  }
  $path = drupal_get_path('theme', $theme);
  $variables['modernizr'] = $path . $modernizr;
  drupal_add_js($variables['modernizr'], array('scope' => 'head_scripts', 'weight' => -1, 'preprocess' => FALSE));
}

/**
 * Implements hook_process_html().
 */
function primo_process_html(&$variables) {
  // Flatten out html_attributes and body_attributes.
  $variables['html_attributes'] = drupal_attributes($variables['html_attributes_array']);
  $variables['body_attributes'] = drupal_attributes($variables['body_attributes_array']);
  if (isset($variables['rdf'])) {
    $variables['rdf_namespaces']  = drupal_attributes($variables['rdf']);
  }
  // Render the head scripts
  $variables['head_scripts'] = drupal_get_js('head_scripts');
}

/**
 * Implements hook_html_head_alter().
 */
function primo_html_head_alter(&$head_elements) {

  $elements = array(
    // Simplify the meta charset declaration.
    'system_meta_content_type' => array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'charset' => 'utf-8',
      ),
    ),
    // Force the latest IE rendering engine and Google Chrome Frame.
    'chrome_frame' => array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'X-UA-Compatible',
        'content' => 'IE=edge,chrome=1',
      ),
    ),
    // Optimize the mobile viewport.
    'MobileOptimized' => array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'MobileOptimized',
        'content' => 'width',
      ),
    ),
    'HandheldFriendly' => array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'HandheldFriendly',
        'content' => 'true',
      ),
    ),
    'viewport' => array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'name' => 'viewport',
        'content' => 'width=device-width',
      ),
    ),
    // Mobile IE allows to activate ClearType technology for smoothing fonts.
    'cleartype' => array(
      '#type' => 'html_tag',
      '#tag' => 'meta',
      '#attributes' => array(
        'http-equiv' => 'cleartype',
        'content' => 'on',
      ),
    ),
  );

  $head_elements = array_merge($head_elements, $elements);
}

/**
 * Implements hook_process_html_tag().
 *
 * - Remove the type attribute from the <script>, <style> and <link> tags.
 * - Remove the CDATA comments from inline JavaScript and CSS.
 * - Remove implicit media="all" from <style> tags.
 */
function primo_process_html_tag(&$variables) {
  $tag = &$variables['element'];

  if (in_array($tag['#tag'], array('script', 'link', 'style'))) {
    // Remove the "type" attribute.
    unset($tag['#attributes']['type']);
    // Remove CDATA comments.
    if (isset($tag['#value_prefix'])
        && ($tag['#value_prefix'] == "\n<!--//--><![CDATA[//><!--\n"
        || $tag['#value_prefix'] == "\n<!--/*--><![CDATA[/*><!--*/\n")) {
      unset($tag['#value_prefix']);
    }
    if (isset($tag['#value_suffix'])
        && ($tag['#value_suffix'] == "\n//--><!]]>\n"
        || $tag['#value_suffix'] == "\n/*]]>*/-->\n")) {
      unset($tag['#value_suffix']);
    }
    // Remove media="all".
    if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] == 'all') {
      unset($tag['#attributes']['media']);
    }
  }
}

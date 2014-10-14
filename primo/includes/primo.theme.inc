<?php

/* ================================================================================================
   Theme functions overrides
   ============================================================================================= */

/**
 * Implements hook_theme_registry_alter().
 */
function primo_theme_registry_alter(&$theme_registry) {

}

/**
 * Implements theme_menu_tree().
 */
function primo_menu_tree($variables) {
  return '<ul>' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_menu_link().
 */
function primo_menu_link($variables) {
 $element = $variables['element'];
 $sub_menu = '';

 // Classes cleaning
 foreach ($element['#attributes']['class'] as $key => $val) {
   if ($val == 'leaf') {
     unset($element['#attributes']['class'][$key]);
   }
 }
 if (empty($element['#attributes']['class'])) {
   unset($element['#attributes']['class']);
 }
 if ($element['#below']) {
   $sub_menu = drupal_render($element['#below']);
 }
 $output = l($element['#title'], $element['#href'], $element['#localized_options']);

 return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements theme_html_tag().
 */
function primo_html_tag($variables) {
  $element = $variables['element'];
  $attributes = isset($element['#attributes']) ? drupal_attributes($element['#attributes']) : '';
  if (!isset($element['#value'])) {
    return '<' . $element['#tag'] . $attributes . ">\n";
  }
  else {
    $output = '<' . $element['#tag'] . $attributes . '>';
    if (isset($element['#value_prefix'])) {
      $output .= $element['#value_prefix'];
    }
    $output .= $element['#value'];
    if (isset($element['#value_suffix'])) {
      $output .= $element['#value_suffix'];
    }
    $output .= '</' . $element['#tag'] . ">\n";
    return $output;
  }
}

/**
 * Implements theme_item_list().
 */
function primo_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];

  $wrapper_attributes = isset($variables['wrapper_attributes']) ? $variables['wrapper_attributes'] : array();
  if (empty($wrapper_attributes['class'])) {
    $wrapper_attributes['class'] = array('item-list');
  }

  $output = '';

  if (isset($title)) {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $attributes = array();
      $children = array();
      $data = '';
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      if ($i == 0) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items - 1) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }

  if (isset($variables['wrapper'])) {
    $output = '<div' . drupal_attributes($wrapper_attributes) . '>' . $output . '</div>';
  }

  return $output;
}

/**
 * Implements theme_breadcrmb().
 */
function primo_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  $output = '';
  if (!empty($breadcrumb)) {
    $output .= '<nav role="navigation" class="breadcrumb">';
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output .= '<h2 class="element-invisible">' . t('You are here') . '</h2>';
    $output .= '<ol><li>' . implode(' » </li><li>', $breadcrumb) . '</li></ol>';
    $output .= '</nav>';
  }
  return $output;
}

/**
 * Implements theme_mark().
 */
function primo_mark($variables) {
  $type = $variables['type'];
  global $user;
  if ($user->uid) {
    if ($type == MARK_NEW) {
      return ' <mark class="marker new">' . t('new') . '</mark>';
    }
    elseif ($type == MARK_UPDATED) {
      return ' <mark class="marker updated">' . t('updated') . '</mark>';
    }
  }
}

/* ================================================================================================
   Primo theme functions
   ============================================================================================= */

/**
 * Implements hook_theme().
 */
function primo_theme($existing, $type, $theme, $path) {
  return array(
    'datetime' => array(
      'variables' => array('timestamp' => NULL, 'text' => NULL, 'attributes' => array(), 'html' => FALSE),
    ),
    'copyright' => array(
      'variables' => array('title' => NULL, 'start' => NULL),
    ),
  );
}

/**
 * Preprocess variables for theme_datetime().
 */
function primo_preprocess_datetime(&$variables) {
  // Format the 'datetime' attribute based on the timestamp.
  // @see http://www.w3.org/TR/html5-author/the-time-element.html#attr-time-datetime
  if (!isset($variables['attributes']['datetime']) && isset($variables['timestamp'])) {
    $variables['attributes']['datetime'] = format_date($variables['timestamp'], 'html_datetime', '', 'UTC');
  }

  // If no text was provided, try to auto-generate it.
  if (!isset($variables['text'])) {
    // Format and use a human-readable version of the timestamp, if any.
    if (isset($variables['timestamp'])) {
      $variables['text'] = format_date($variables['timestamp']);
      $variables['html'] = FALSE;
    }
    // Otherwise, use the literal datetime attribute.
    elseif (isset($variables['attributes']['datetime'])) {
      $variables['text'] = $variables['attributes']['datetime'];
      $variables['html'] = FALSE;
    }
  }
}

/**
 * Returns HTML for a date / time.
 *
 * @param $variables
 *   An associative array containing:
 *   - timestamp: (optional) A UNIX timestamp for the datetime attribute. If the
 *     datetime cannot be represented as a UNIX timestamp, use a valid datetime
 *     attribute value in $variables['attributes']['datetime'].
 *   - text: (optional) The content to display within the <time> element. Set
 *     'html' to TRUE if this value is already sanitized for output in HTML.
 *     Defaults to a human-readable representation of the timestamp value or the
 *     datetime attribute value using format_date().
 *     When invoked as #theme or #theme_wrappers of a render element, the
 *     rendered #children are autoamtically taken over as 'text', unless #text
 *     is explicitly set.
 *   - attributes: (optional) An associative array of HTML attributes to apply
 *     to the <time> element. A datetime attribute in 'attributes' overrides the
 *     'timestamp'. To create a valid datetime attribute value from a UNIX
 *     timestamp, use format_date() with one of the predefined 'html_*' formats.
 *   - html: (optional) Whether 'text' is HTML markup (TRUE) or plain-text
 *     (FALSE). Defaults to FALSE. For example, to use a SPAN tag within the
 *     TIME element, this must be set to TRUE, or the SPAN tag will be escaped.
 *     It is the responsibility of the caller to properly sanitize the value
 *     contained in 'text' (or within the SPAN tag in aforementioned example).
 *
 * @see template_preprocess_datetime()
 * @see http://www.w3.org/TR/html5-author/the-time-element.html#attr-time-datetime
 */
function primo_datetime($variables) {
  $output = '<time' . drupal_attributes($variables['attributes']) . '>';
  $output .= !empty($variables['html']) ? $variables['text'] : check_plain($variables['text']);
  $output .= '</time>';
  return $output;
}

/**
 * Returns HTML for a copyright string.
 *
 * @param $variables
 *   An associative array containing:
 *   - title: the copyright owner title or name.
 *   - start: the copyright starting year.
 * @return
 *   Returns a formatted string.
 */
function theme_copyright($variables) {
  $range = '';

  $current = format_date(time(), 'custom', 'Y');
  if (isset($start) && $current != $start) {
    $range = "{$start}-{$current}";
  }
  else {
    $range = $current;
  }

  return "&copy; {$title} {$range}";
}

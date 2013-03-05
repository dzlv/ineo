<?php
/**
 * @file
 * Primo theme implementation,
 * display the basic html structure of a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see http://drupal.org/node/1728208
 */
?>
<!DOCTYPE html>
<!--[if IEMobile 7]><html class="no-js iem7" <?php print $html_attributes; ?>><![endif]-->
<!--[if lt IE 7]><html class="no-js lt-ie9 lt-ie8 lt-ie7" <?php print $html_attributes; ?>><![endif]-->
<!--[if (IE 7)&(!IEMobile)]><html class="no-js lt-ie9 lt-ie8" <?php print $html_attributes; ?>><![endif]-->
<!--[if IE 8]><html class="no-js lt-ie9" <?php print $html_attributes; ?>><![endif]-->
<!--[if (gt IE 8)|(gt IEMobile 7)]><!--><html class="no-js"<?php print $html_attributes . $rdf_namespaces; ?>><!--<![endif]-->
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $head_scripts; ?>
</head>

<body<?php print $body_attributes;?>>
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable">
      <?php print t('Skip to main content'); ?>
    </a>
  </div>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $scripts; ?>
  <?php print $page_bottom; ?>
</body>
</html>

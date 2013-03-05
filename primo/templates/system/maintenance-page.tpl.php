<?php
/**
 * @file
 * Primo theme implementation,
 * display a single Drupal page while offline.
 *
 * Complete documentation for this file is available online.
 * @see http://drupal.org/node/1728174
 */
?>

<!DOCTYPE html>
<html<?php print $html_attributes; ?>>
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $head_scripts; ?>
</head>

<body<?php print $body_attributes;?>>

  <?php print $page_top; ?>

  <div id="page">

    <header id="header" role="banner" class="clearfix">

      <?php if ($logo): ?>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      <?php endif; ?>

      <?php if ($site_name || $site_slogan): ?>
        <hgroup id="name-and-slogan">
          <?php if ($site_name): ?>
            <h1 id="site-name">
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
            </h1>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <h2 id="site-slogan"><?php print $site_slogan; ?></h2>
          <?php endif; ?>
        </hgroup><!-- #name-and-slogan -->
      <?php endif; ?>

      <?php print $header; ?>

    </header>

    <?php if ($messages): ?>
      <div id="messages"><?php print $messages; ?></div>
    <?php endif; ?>

    <main role="main" class="clearfix">
      <a id="main-content"></a>

      <div id="content" class="column">
        <?php if ($highlighted): ?><div id="highlighted"><?php print $highlighted; ?></div><?php endif; ?>
        <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
        <?php print $content; ?>
      </div>

      <?php if ($sidebar_first): ?>
        <aside id="sidebar-first" class="column sidebar">
          <?php $sidebar_first; ?>
        </aside><!-- #sidebar-first -->
      <?php endif; ?>

      <?php if ($sidebar_second): ?>
        <aside id="sidebar-second" class="column sidebar">
          <?php print $sidebar_second; ?>
        </aside><!-- #sidebar-second -->
      <?php endif; ?>

    </main>

    <footer id="footer" role="contentinfo">
      <?php print $footer; ?>
    </footer>

  </div><!-- #page -->

  <?php print $scripts; ?>
  <?php print $page_bottom; ?>
</body>
</html>

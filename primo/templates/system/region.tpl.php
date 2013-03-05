<?php
/**
 * @file
 * Primo theme implementation,
 * display a region.
 *
 * Complete documentation for this file is available online.
 * @see http://drupal.org/node/1728112
 */
?>

<?php if ($content): ?>
  <section id="<?php print $region; ?>" class="<?php print $classes; ?>">
    <?php print $content; ?>
  </section>
<?php endif; ?>

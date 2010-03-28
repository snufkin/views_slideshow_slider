<?php
// $Id: views-slideshow-slider.tpl.php,v 1.1 2010/03/27 17:17:43 snufkin Exp $

/**
 * @file
 * Views Slideshow: Slider template file.
 */
?>

<?php if ($slider_left): ?>
  <div class="views-slideshow-slider-left clear-block">
    <?php print $slider_left; ?>
  </div>
<?php endif; ?>

<?php if ($controls_top || $image_count_top || $slider_top): ?>
  <div class="views-slideshow-controls-top clear-block">
    <?php print $controls_top; ?>
    <?php print $pager_top; ?>
    <?php print $slider_top; ?>
  </div>
<?php endif; ?>

<?php print $slideshow; ?>

<?php if ($slider_bottom || $controls_bottom || $image_count_bottom): ?>
  <div class="views-slideshow-controls-bottom clear-block">
    <?php print $slider_bottom; ?>
    <?php print $controls_bottom; ?>
    <?php print $image_count_bottom; ?>
  </div>
<?php endif; ?>

<?php if ($slider_right): ?>
  <div class="views-slideshow-slider-right clear-block">
    <?php print $slider_right; ?>
  </div>
<?php endif; ?>

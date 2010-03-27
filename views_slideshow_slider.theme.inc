<?php
// $Id: views_slideshow_slider.theme.inc,v 1.1.2.1.2.20 2010/03/01 11:05:12 psynaptic Exp $

/**
 * @file
 * Theme & preprocess functions for the Views Slideshow: slider module.
 */

/**
 * Implements template_preprocess_hook_THEMENAME().
 */
function template_preprocess_views_slideshow_slider(&$vars) {
  $options = $vars['options'];
  $id = $vars['id'];
  $view = $vars['view'];
  $rows = $vars['rows'];

  $settings = array_merge(
    array(
      'num_divs' => sizeof($vars['rows']),
      'teasers_last' => ($options['slider']['teasers_last']) ? 'true' : 'false',
      'id_prefix' => '#views_slideshow_slider_main_',
      'div_prefix' => '#views_slideshow_slider_div_',
      'id' => $vars['id'],
    ),
    $options['slider']
  );


  if ('slider_left' == $options['slider']['position'] ||
    'slider_right' == $options['slider']['position']) {
    $settings['orientation'] = 'vertical';
  }
  else {
    $settings['orientation'] = 'horizontal';
  }

  jquery_ui_add('ui.slider');
  drupal_add_css(drupal_get_path('module', 'jquery_ui') . '/jquery.ui/themes/base/ui.all.css', 'module', 'all', FALSE);
  drupal_add_js(array('viewsSlideshowSlider' => array("#views_slideshow_slider_main_$id" => $settings)), 'setting'); 

  $hidden_elements = theme('views_slideshow_slider_no_display_section', $view, $rows, $id, $options, $teaser);
  $vars['slideshow'] = theme('views_slideshow_main_section', $id, $hidden_elements, 'slider');

  $slider = $vars['options']['slider'];

  if ($slider['controls'] == 1) {
    $vars['controls_top'] = theme('views_slideshow_slider_controls', $id, $view, $options);
  }
  elseif ($slider['controls'] == 2) {
    $vars['controls_bottom'] = theme('views_slideshow_slider_controls', $id, $view, $options);
  }

  $vars[$slider['position']] = theme('views_slideshow_slider_slider', $id);

  if ($slider['image_count'] == 1) {
    $vars['image_count_top'] = theme('views_slideshow_slider_image_count', $id, $view, $options);
  }
  elseif ($slider['image_count'] == 2) {
    $vars['image_count_bottom'] = theme('views_slideshow_slider_image_count', $id, $view, $options);
  }
}

/**
 * Create the divs that will be turned into the slider.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_slider_slider($id) {
  $attributes['id'] = "views_slideshow_slider_slider_$id";
  $attributes = drupal_attributes($attributes);
  return "<div$attributes></div>";
}

/**
 * Add the the HTML for the hidden slideshow elements.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_slider_no_display_section($view, $rows, $id, $options, $teaser = TRUE) {
  // Add the slideshow elements.
  
  $attributes['id'] = "views_slideshow_slider_teaser_section_$id";
  $attributes['class'] = 'views_slideshow_slider_teaser_section';
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  foreach ($rows as $count => $item) {
    $output .= theme('views_slideshow_slider_no_display_teaser', $item, $id, $count);
  }
  $output .= "</div>";
  return $output;
}

/**
 * Views Slideshow: active element.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_slider_no_display_teaser($item, $id, $count) {
  $current = $count + 1;

  $classes = array(
    'views_slideshow_slider_slide',
    "views_slideshow_slide views-row-$current",
  );

  if ($count) {
    $classes[] = 'views_slideshow_slider_hidden';
  }
  $classes[] = ($count % 2) ? 'views-row-even' : 'views-row-odd';

  $attributes['id'] = "views_slideshow_slider_div_${id}_${count}";
  $attributes['class'] = implode(' ', $classes);
  $attributes = drupal_attributes($attributes);

  return "<div$attributes>$item</div>";
}


/**
 * Views Slideshow: slideshow controls.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_slider_controls($id, $view, $options) {
  $classes = array(
    'views_slideshow_slider_controls',
    'views_slideshow_controls',
  );

  $attributes['class'] = implode(' ', $classes);
  $attributes['id'] = "views_slideshow_slider_controls_$id";
  $attributes = drupal_attributes($attributes);

  $output = "<div$attributes>";
  $output .= theme('views_slideshow_slider_control_previous', $id, $view, $options);
  $output .= theme('views_slideshow_slider_control_pause', $id, $view, $options);
  $output .= theme('views_slideshow_slider_control_next', $id, $view, $options);
  $output .= "</div>\n";
  return $output;
}

/**
 * Views Slideshow: "previous" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_slider_control_previous($id, $view, $options) {
  return l(t('Previous'), '#', array('attributes' => array(
    'class' => 'views_slideshow_slider_previous views_slideshow_previous',
    'id' => "views_slideshow_slider_prev_$id",
  )));
}

/**
 * Views Slideshow: "pause" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_slider_control_pause($id, $view, $options) {
  return l(t('Pause'), '#', array('attributes' => array(
    'class' => 'views_slideshow_slider_pause views_slideshow_pause',
    'id' => "views_slideshow_slider_playpause_$id",
  )));
}

/**
 * Views Slideshow: "next" control.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_slider_control_next($id, $view, $options) {
  return l(t('Next'), '#', array('attributes' => array(
    'class' => 'views_slideshow_slider_next views_slideshow_next',
    'id' => "views_slideshow_slider_next_$id",
  )));
}

/**
 * Views Slideshow: image counter.
 *
 * @ingroup themeable
 */
function theme_views_slideshow_slider_image_count($id, $view, $options) {
  $attributes['class'] = 'views_slideshow_slider_image_count views_slideshow_image_count';
  $attributes['id'] = "views_slideshow_slider_image_count_$id";
  $attributes = drupal_attributes($attributes);

  $counter = '<span class="num"></span> ' . t('of') .' <span class="total"></span>';

  return "<div$attributes>$counter</div>";
}

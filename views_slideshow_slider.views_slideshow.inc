<?php
// $Id: views_slideshow_slider.views_slideshow.inc,v 1.1 2010/03/27 17:17:43 snufkin Exp $

/**
 * @file
 * The default options available with Views Slideshow: slider.
 */

function views_slideshow_slider_views_slideshow_modes() {
  $options = array(
    'slider' => t('Slider'),
  );
  return $options;
}

function views_slideshow_slider_views_slideshow_option_definition() {
  $options['slider'] = array(
    'contains' => array (
      'timeout' => array('default' => 5000),
      'sort' => array('default' => 1),
      'effect' => array('default' => 'fade'),
      'position' => array('default' => 'bottom'),
      'speed' => array('default' => 300),
      'ie' => array(
        'contains' => array(
          'cleartype' => array('default' => TRUE),
          'cleartypenobg' => array('default' => FALSE),
        ),
      ),
      'advanced' => array('default' => ''),
    ),
  );
  return $options;
}

function views_slideshow_slider_views_slideshow_options_form(&$form, &$form_state, &$view) {
  $form['slider'] = array(
    '#type' => 'fieldset',
    '#title' => t('Slider options'),
    '#collapsible' => TRUE,
    '#attributes' => array('class' => 'slider'),
  );

  $options = array(
    'slider_top' => t('Top'),
    'slider_bottom' => t('Bottom'),
    'slider_left' => t('Left'),
    'slider_right' => t('Right'),
  );

  $form['slider']['position'] = array(
    '#type' => 'select',
    '#title' => t('Slider position'),
    '#options' => $options,
    '#default_value' => $view->options['slider']['position'],
    '#description' => t('Determine where the slider will be printed.'),
  );
  $form['slider']['timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timer delay'),
    '#default_value' => $view->options['slider']['timeout'],
    '#description' => t('Amount of time in milliseconds between transitions.'),
  );
  $form['slider']['delay'] = array(
    '#type' => 'textfield',
    '#title' => t('Initial slide delay offset'),
    '#default_value' => (isset($view->options['slider']['delay'])) ? $view->options['slider']['delay'] : 0,
    '#description' => t('Amount of time in milliseconds for the first slide to transition. This number will be added to Timer delay to create the initial delay.  For example if Timer delay is 4000 and Initial delay is 2000 then the first slide will change at 6000ms (6 seconds).  If Initial delay is -2000 then the first slide will change at 2000ms (2 seconds).')
  );
  $form['slider']['speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Speed'),
    '#default_value' => $view->options['slider']['speed'],
    '#description' => t('Time in milliseconds that each transition lasts. Numeric only!'),  
  );
  $form['slider']['random'] = array(
    '#type' => 'radios',
    '#title' => t('Random'),
    '#description' => t('This option controls the order items are displayed. The default setting, False, uses the views ordering. True will cause the images to display in a random order.'),
    '#options' => array(0 => t('False'), 1 => t('True')),
    '#default_value' => isset($view->options['slider']['random'])? $view->options['slider']['random'] : 0,
  );
  $form['slider']['pause'] = array(
    '#type' => 'radios',
    '#title' => t('Pause'),
    '#options' => array(1 => t('Yes'),2 => t('No')),
    '#default_value' => $view->options['slider']['pause'],
    '#description' => t('Pause when hovering on the slideshow image.'),
  );
  $form['slider']['controls'] = array(
    '#type' => 'select',
    '#title' => t('Controls'),
    '#options' => array(0 => t('None'),1 => t('Top'),2 => t('Bottom')),
    '#default_value' => (isset($view->options['slider']['controls'])) ? $view->options['slider']['controls'] : 0,
    '#description' => t('Determine if controls for the slideshow (start/stop/next/previous) should appear, and if so whether they should appear before or after the slideshow.'),
  );
  $form['slider']['image_count'] = array(
    '#type' => 'select',
    '#title' => t('Image Counter'),
    '#options' => array(0 => t('None'),1 => t('Top'),2 => t('Bottom')),
    '#default_value' => (isset($view->options['slider']['image_count'])) ? $view->options['slider']['image_count'] : 0,
    '#description' => t('Determine if Image Counter (1 of 4) should be displayed and if so whether they should appear before or after the slideshow.'),
  );
  $options = array(
    'none' => 'none',
    'blindX' => 'blindX',
    'blindY' => 'blindY',
    'blindZ' => 'blindZ',
    'cover' => 'cover',
    'curtainX' => 'curtainX',
    'curtainY' => 'curtainY',
    'fade' => 'fade',
    'fadeZoom' => 'fadeZoom',
    'growX' => 'growX',
    'growY' => 'growY',
    'scrollUp' => 'scrollUp',
    'scrollDown' => 'scrollDown',
    'scrollLeft' => 'scrollLeft',
    'scrollRight' => 'scrollRight',
    'scrollHorz' => 'scrollHorz',
    'scrollVert' => 'scrollVert',
    'shuffle' => 'shuffle',
    'slideX' => 'slideX',
    'slideY' => 'slideY',
    'toss' => 'toss',
    'turnUp' => 'turnUp',
    'turnDown' => 'turnDown',
    'turnLeft' => 'turnLeft',
    'turnRight' => 'turnRight',
    'uncover' => 'uncover',
    'wipe' => 'wipe',
    'zoom' => 'zoom',
  );
  $form['slider']['effect'] = array(
    '#type' => 'select',
    '#title' => t('Effect'),
    '#options' => $options,
    '#default_value' => $view->options['slider']['effect'],
    '#description' => t('The transition effect that will be used to change between images. Not all options below may be relevant depending on the effect.'),
  );
  $form['slider']['sync'] = array(
    '#type' => 'radios',
    '#title' => t('Sync'),
    '#options' => array(1 => t('Yes'), 2 => t('No')),
    '#default_value' =>$view->options['slider']['sync'],
    '#description' => t('The sync option controls whether the slide transitions occur simultaneously. The default is yes which means that the current slide transitions out as the next slide transitions in. By setting the sync option to no you can get some interesting twists on your transitions.'),  
  );
  $form['slider']['advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced Options'),
    '#default_value' =>(isset($view->options['slider']['advanced'])) ? $view->options['slider']['advanced'] : '',
    '#description' => t('Add other jQuery cycle options one per line.  Ex. height: 350  !url', array('!url' => l('Click here for the additional options to add.', 'http://malsup.com/jquery/cycle/options.html'))),
  );
  $form['slider']['ie'] = array(
    '#type' => 'fieldset',
    '#title' => t('Internet Explorer Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['slider']['ie']['cleartype'] = array(
    '#type' => 'radios',
    '#title' => t('ClearType'),
    '#options' => array('true' => t('True'), 'false' => t('False')),
    '#default_value' =>(isset($view->options['slider']['ie']['cleartype'])) ? $view->options['slider']['ie']['cleartype'] : 'true',
    '#description' => t('True if clearType corrections should be applied (for IE).  Some background issues could be fixed by setting this to false.'),
  );
  $form['slider']['ie']['cleartypenobg'] = array(
    '#type' => 'radios',
    '#title' => t('ClearType Background'),
    '#options' => array('true' => t('True'), 'false' => t('False')),
    '#default_value' =>(isset($view->options['slider']['ie']['cleartypenobg'])) ? $view->options['slider']['ie']['cleartypenobg'] : 'false',
    '#description' => t('Set to true to disable extra cleartype fixing (leave false to force background color setting on slides)'),
  );
}
function views_slideshow_slider_views_slideshow_options_form_validate(&$form, &$form_state, &$view) {
  if (!is_numeric($form_state['values']['style_options']['slider']['speed'])) {
    form_error($form['slider']['speed'], t('!setting must be numeric!',array('!setting' => 'Speed')));
  }
  if (!is_numeric($form_state['values']['style_options']['slider']['timeout'])) {
    form_error($form['slider']['timeout'],t('!setting must be numeric!',array('!setting' => 'Timeout')));
  }
}

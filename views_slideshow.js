// $Id: views_slideshow.js,v 1.1.2.2 2010/03/30 18:03:28 snufkin Exp $

/**
 *  @file
 *  A simple jQuery Slider Div Slideshow Rotator.
 */

/**
 * This will set our initial behavior, by starting up each individual slideshow.
 */
Drupal.behaviors.viewsSlideshowSlider = function (context) {
  $('.views_slideshow_slider_main:not(.viewsSlideshowSlider-processed)', context).addClass('viewsSlideshowSlider-processed').each(function() {
    var fullId = '#' + $(this).attr('id');
    var settings = Drupal.settings.viewsSlideshowSlider[fullId];
    settings.targetId = '#' + $(fullId + " :first").attr('id');

    // Attach the slider before we create the slideshow so the 
    // after callback in the cycle can find the slider.
    var slider = $('#views_slideshow_slider_slider_' + settings.id);
    slider.slider({
        orientation: settings.orientation,
        value: 0,
        min: 0,
        max: settings.num_divs - 1, // We start from 0.
        range: "min",
        animate: true,
        step: 1,
        change: function(event, ui) {
          if (event.originalEvent) { // On machine update this is undefined.
            $(settings.targetId).cycle(ui.value);
            // Restart the cycle, otherwise we end up with flicker.
            $(settings.targetId).cycle('stop'); 
            settings.opts.startingSlide = ui.value;
            $(settings.targetId).cycle(settings.opts);
          }
        },
    });

    settings.opts = {
      speed:settings.speed,
      timeout:parseInt(settings.timeout),
      delay:parseInt(settings.delay),
      sync:settings.sync==1,
      random:settings.random==1,
      pause:settings.pause==1,
      prev:(settings.controls > 0)?'#views_slideshow_slider_prev_' + settings.id:null,
      next:(settings.controls > 0)?'#views_slideshow_slider_next_' + settings.id:null,
      after:function(curr, next, opts) {
        // After a loop move the slider. 
        slider.slider('value', opts.currSlide);
        // Used for Image Counter.
        if (settings.image_count) {
          $('#views_slideshow_slider_image_count_' + settings.id + ' span.num').html(opts.currSlide + 1);
          $('#views_slideshow_slider_image_count_' + settings.id + ' span.total').html(opts.slideCount);
        }
      },
      cleartype:(settings.ie.cleartype),
      cleartypeNoBg:(settings.ie.cleartypenobg)
    }
    
    if (settings.effect == 'none') {
      settings.opts.speed = 1;
    }
    else {
      settings.opts.fx = settings.effect;
    }
    
    // Add additional settings.
    var advanced = settings.advanced.split("\n");
    for (i=0; i<advanced.length; i++) {
      var prop = '';
      var value = '';
      var property = advanced[i].split(":");
      for (j=0; j<property.length; j++) {
        if (j == 0) {
          prop = property[j];
        }
        else if (j == 1) {
          value = property[j];
        }
        else {
          value += ":" + property[j];
        }
      }
      
      // Need to evaluate so true and false isn't a string.
      if (value == 'true' || value == 'false') {
        value = eval(value);
      }
      
      settings.opts[prop] = value;
    }
    
    $(settings.targetId).cycle(settings.opts);

    // Show image count for people who have js enabled.
    $('#views_slideshow_slider_image_count_' + settings.id).show();
    
    if (settings.controls > 0) {
      // Show controls for people who have js enabled browsers.
      $('#views_slideshow_slider_controls_' + settings.id).show();
      
      $('#views_slideshow_slider_playpause_' + settings.id).click(function(e) {
      	if (settings.paused) {
      	  $(settings.targetId).cycle('resume');
      	  $('#views_slideshow_slider_playpause_' + settings.id)
      	    .addClass('views_slideshow_slider_pause')
      	    .addClass('views_slideshow_pause')
      	    .removeClass('views_slideshow_Slider_play')
            .removeClass('views_slideshow_play')
      	    .text('Pause');
      	  settings.paused = false;
      	}
      	else {
      	  $(settings.targetId).cycle('pause');
      	  $('#views_slideshow_slider_playpause_' + settings.id)
      	    .addClass('views_slideshow_slider_play')
      	    .addClass('views_slideshow_play')
      	    .removeClass('views_slideshow_slider_pause')
      	    .removeClass('views_slideshow_pause')
      	    .text('Resume');
      	  settings.paused = true;
      	}
        e.preventDefault();
      });
    }
  });
}


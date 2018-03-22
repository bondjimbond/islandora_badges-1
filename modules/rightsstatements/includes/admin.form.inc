<?php
/**
 * @file
 * CC badge admin options
 */
/**
 * Admin form: configure CC URI xpath.
 */
function islandora_rightsstatements_admin_form($form, $form_settings) {
  $form['islandora_rightsstatements_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Xpath to Rightsstatements badge URI'),
    '#description' => t('Xpath to Rightsstatements badge URI. Note: Xpaths are case-sensitive.'),
    '#default_value' => variable_get('islandora_rightsstatements_path', '/mods:mods/mods:accessCondition[@type="use and reproduction"]'),
  );
  $form['islandora_rightsstatements_image_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Image Height'),
    '#description' => t('The height in pixels for the Rightsstatements badge image.'),
    '#default_value' => variable_get('islandora_rightsstatements_image_height', '31'),
  );
  
  $form['islandora_rightsstatements_image_colour'] = array(
    '#type' => 'radios',
    '#title' => t('Image Text Colour'),
    '#description' => t('The colour of the text in the Rightsstatements badge image.'),
    '#options' => array('black' => t('black'), 'blue' => t('blue')),
    '#default_value' => variable_get('islandora_rightsstatements_image_colour', 'black'),                                           
  );

  return system_settings_form($form);
}


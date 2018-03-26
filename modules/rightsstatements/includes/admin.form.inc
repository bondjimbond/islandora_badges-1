<?php
/**
 * @file
 * CC badge admin options
 */
/**
 * Admin form: configure CC URI xpath.
 */
function islandora_rightsstatements_admin_form($form, $form_settings) {
  $form['islandora_rightsstatements_rights_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Solr field for Rightsstatements.org URI'),
    '#description' => t('The solr field that contains the Rightsstatements.org URI'),
    '#default_value' => variable_get('islandora_rightsstatements_rights_field', 'dc.rights'),
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


<?php

/**
 * @file
 * Utility functions.
 */

/**
 * Take URI, return HTML code for a rights statement badge.
 * @return string
 */

function islandora_rightsstatements_get_html($uri) {
  $height = variable_get('islandora_rightsstatements_image_height', '31');
  $colour = variable_get('islandora_rightsstatements_image_colour', 'black');
  if ($colour == 'blue') {
    $colour = '-blue-type';
  }
  else {
    $colour = '';
  }
  if ($uri == 'http://rightsstatements.org/vocab/CNE/1.0/') {
    $alt_text = 'Copyright Not Evaluated';
    $image = 'http://rightsstatements.org/files/buttons/CNE.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/UND/1.0/') {
    $alt_text = 'Copyright Undetermined';
    $image = 'http://rightsstatements.org/files/buttons/UND.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC/1.0/') {
    $alt_text = 'In Copyright';
    $image = 'http://rightsstatements.org/files/buttons/InC.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC-EDU/1.0/') {
    $alt_text = 'In Copyright - Educational Use Permitted';
    $image = 'http://rightsstatements.org/files/buttons/InC-EDU.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC-OW-EU/1.0/') {
    $alt_text = 'In Copyright - EU Orphan Work';
    $image = 'http://rightsstatements.org/files/buttons/InC-OW-EU.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC-NC/1.0/') {
    $alt_text = 'In Copyright - Non-Commercial Use Permitted';
    $image = 'http://rightsstatements.org/files/buttons/InC-NC.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC-RUU/1.0/') {
    $alt_text = 'In Copyright - Rights Holders Unlocatable or Unidentifiable';
    $image = 'http://rightsstatements.org/files/buttons/InC-RUU.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NoC-CR/1.0/') {
    $alt_text = 'No Copyright - Contractual Restrictions';
    $image = 'http://rightsstatements.org/files/buttons/NoC-CR.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NoC-NC/1.0/') {
    $alt_text = 'No Copyright - Non-Commercial Use Only';
    $image = 'http://rightsstatements.org/files/buttons/NoC-NC.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NoC-OKLR/1.0/') {
    $alt_text = 'No Copyright - Other Known Legal Restrictions';
    $image = 'http://rightsstatements.org/files/buttons/NoC-OKLR.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NoC-US/1.0/') {
    $alt_text = 'No Copyright - United States';
    $image = 'http://rightsstatements.org/files/buttons/NoC-US.dark-white-interior' . $colour . '.png';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NKC/1.0/') {
    $alt_text = 'No Known Copyright';
    $image = 'http://rightsstatements.org/files/buttons/NKC.dark-white-interior' . $colour . '.png';
  }
  else {
    return;
  }
  
  $img = array(
    '#theme' => 'image',
    '#path' => $image,
    '#alt' => $alt_text,
    '#height' => $height,
  );
  $badge = array(
    '#type' => 'link',
    '#title' => drupal_render($img),
    '#href' => $uri,
    '#options' => array(
      'attributes' => array(
        'target' => '_blank',
      ),
      'html' => TRUE,
    ),
  );
  return $badge;
}

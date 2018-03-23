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

/**
 * Get URI from the configured Solr field.
 * @return string
 */
function islandora_rightsstatements_get_uri(AbstractObject $object) {
  // Gets the rightsstatements.org URI from the configured Solr field.
  $qp = new islandoraSolrQueryProcessor();
  $qp->buildQuery(format_string('@field:"@pid"', array(
    '@field' => 'PID',
    '@pid' =>"{$object->id}")
  ));
  $uri_field = variable_get('islandora_rightsstatements_rights_field', 'mods_accessCondition_ms');
  $qp->solrParams['fl'] = implode(', ', array(
    'PID',
    $uri_field,
  ));
  $qp->solrStart = 0;
  $qp->solrLimit = 100000;
  $qp->executeQuery(FALSE);
  if ($qp->islandoraSolrResult['response']['numFound'] > 0) {
    if (array_key_exists($uri_field, $qp->islandoraSolrResult['response']['objects']['0']['solr_doc'])) {
      $rights_uri_array = ($qp->islandoraSolrResult['response']['objects']['0']['solr_doc'][$uri_field]);
      foreach ($rights_uri_array as $uri) {
        if (strpos($uri, 'rightsstatements.org')) {
          $rights_uri = $uri;
        }
      }
    }
  }
  if (!isset($rights_uri)) {
    return;
  }
  else {
    return $rights_uri;
  }
}

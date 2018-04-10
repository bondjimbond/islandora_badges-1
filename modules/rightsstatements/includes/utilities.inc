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
  // Extract just the statement terms from the URI to use in image URL
  $terms = substr($uri, strpos($uri, "/vocab/")+7);
  $terms = substr($terms, 0, strlen($terms)-5);

  $image = 'http://rightsstatements.org/files/buttons/' . $terms . '.dark-white-interior' . $colour . '.png';

  if ($uri == 'http://rightsstatements.org/vocab/CNE/1.0/') {
    $alt_text = 'Copyright Not Evaluated';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/UND/1.0/') {
    $alt_text = 'Copyright Undetermined';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC/1.0/') {
    $alt_text = 'In Copyright';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC-EDU/1.0/') {
    $alt_text = 'In Copyright - Educational Use Permitted';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC-OW-EU/1.0/') {
    $alt_text = 'In Copyright - EU Orphan Work';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC-NC/1.0/') {
    $alt_text = 'In Copyright - Non-Commercial Use Permitted';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/InC-RUU/1.0/') {
    $alt_text = 'In Copyright - Rights Holders Unlocatable or Unidentifiable';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NoC-CR/1.0/') {
    $alt_text = 'No Copyright - Contractual Restrictions';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NoC-NC/1.0/') {
    $alt_text = 'No Copyright - Non-Commercial Use Only';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NoC-OKLR/1.0/') {
    $alt_text = 'No Copyright - Other Known Legal Restrictions';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NoC-US/1.0/') {
    $alt_text = 'No Copyright - United States';
  }
  elseif ($uri == 'http://rightsstatements.org/vocab/NKC/1.0/') {
    $alt_text = 'No Known Copyright';
  }
  else {
    return;
  }
  
  $img = array(
    '#theme' => 'image',
    '#path' => $image,
    '#alt' => $alt_text,
    '#height' => $height,
    '#title' => $alt_text,
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
  $uri_field = variable_get('islandora_rightsstatements_rights_field', 'dc.rights');
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

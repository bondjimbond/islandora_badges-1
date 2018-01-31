<?php
/**
 * @file
 * CC badge admin options
 */
/**
 * Admin form: configure CC URI xpath.
 */
function islandora_cc_badge_admin_form($form, $form_settings) {
  $form['islandora_cc_badge_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Xpath to Creative Commons badge URI'),
    '#description' => t('Xpath to Creative Commons badge URI. Note: Xpaths are case-sensitive.'),
    '#default_value' => variable_get('islandora_cc_badge_path', 'mods:mods/mods:accessCondition[@type="use and reproduction"]'),
  );
  return system_settings_form($form);
}


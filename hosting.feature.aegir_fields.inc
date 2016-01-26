<?php
/**
 * @file
 * The hosting feature definition for passing field values to sites.
 */

/**
 * Register a hosting feature with Aegir.
 *
 * This will be used to generate the 'admin/hosting' page.
 *
 * @return
 *   associative array indexed by feature key.
 */
function aegir_fields_hosting_feature() {
  $features['aegir_fields'] = array(
    'title' => 'Aegir Fields',
    'description' => t('Transfer field values and tags to site instances'),
    'status' => HOSTING_FEATURE_DISABLED,
    'module' => 'aegir_fields',
    'group' => 'experimental',
  );
  return $features;
}

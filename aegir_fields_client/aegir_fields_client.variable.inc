<?php
/**
 * @file
 * Expose conf settings as variables in the site.
 *
 * This is only active if you are already using
 * https://www.drupal.org/project/variable .
 *
 * Though these seem to become editible under
 * admin/config/system/variable/edit/aegir_fields
 * as expected,
 * they don't (currently) provide the expected tokens for use with
 * token_filter. TODO Find out why.
 *
 * You can (if you must) render the token
 *   [variable:aegir_field]
 * and get formatted data.
 * We just can't seem to give you keyed values.
 */

/**
 * Implements hook_variable_info().
 */
function aegir_fields_client_variable_info($options) {
  $variables['aegir_fields'] = array(
    'type' => 'array',
    'title' => t('aegir_fields', array(), $options),
    'description' => t('Values provided by aegir_fields.module and set by this sites hostmaster.', array(), $options),
    // Array does not get the honor of providing a token by default.
    'default' => array(),
    'token' => TRUE,
  );
  return $variables;
}

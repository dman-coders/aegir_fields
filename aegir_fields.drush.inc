<?php
/**
 * @file
 * Transfer field values into site-alias properties.
 */

/**
 * Transfers the data from the site node field into the task context.
 *
 * So that the drush tasks know what the site definition wants.
 *
 * Getting data in here means it shows up in the site-alias inc.
 *
 * Implementation of hook_hosting_TASK_OBJECT_context_options()
 * hook_hosting_site_context_options()
 */
function aegir_fields_hosting_site_context_options(&$task) {
  // $task->context_options['web_server']
  // = hosting_context_name($task->ref->web_server);
  $node = $task->ref;

  // Find all CCK fields on this node.
  // Put each of their values into the site alias data.
  $fields = content_fields(NULL, $node->type);
  foreach ($fields as $field_id => $field_info) {
    if (empty($node->$field_id)) {
      continue;
    }
    // I can't remember how to content_field_get_value!
    $value = array();
    foreach ($node->$field_id as $i => $f) {
      if (isset($f['value'])) {
        $value[$i] = $f['value'];
      }
    }
    if (!$field_info['multiple']) {
      $value = array_pop($value);
    }

    $task->context_options['aegir_fields'][$field_id] = $value;
  }

  // Also do taxonomy terms. Similar logic.
  if (!empty($task->ref->taxonomy)) {
    $field_val = $task->ref->taxonomy;
    foreach ($field_val as $term) {
      $task->context_options['tags'][] = $term->name;
    }
  }
  else {
    $task->context_options['tags'] = array();
  }
}


/**
 * Saves data UP from a site to the hostmaster node.
 *
 * Implementation of hook_drush_context_import().
 * hook_hosting_TASK_OBJECT_context_options()
 */
function xx_aegir_fields_drush_context_import($context, &$node) {
  if ($context->type == 'site') {
    if (isset($context->http_basic_auth_username) && !empty($context->http_basic_auth_username)) {
      $node->http_basic_auth_username = $context->http_basic_auth_username;
      $node->http_basic_auth_password = $context->http_basic_auth_password;
      $node->http_basic_auth_message = $context->http_basic_auth_message;
    }
  }

}


/* The following funcs are to be used by the backend. */

/**
 * Implements hook_drush_init().
 */
function aegir_fields_drush_init() {
  aegir_fields_provision_register_autoload();
}

/**
 * Register our directory as a place to find provision classes.
 *
 * Dunno about all this, copied from http_auth.
 */
function aegir_fields_provision_register_autoload() {
  static $loaded = FALSE;
  if (!$loaded) {
    $loaded = TRUE;
    provision_autoload_register_prefix('Provision_', dirname(__FILE__));
  }
}

/**
 * Expose the service type this extension defines to provision.
 *
 * @return array
 *   An array with the service type the key,
 *   and the default implementation the value.
 */
function aegir_fields_provision_services() {
  aegir_fields_provision_register_autoload();
  return array('aegir_fields' => NULL);
}


/**
 * Append PHP code to Drupal's settings.php file.
 *
 * To use templating, return an include statement for the template.
 *
 * @param string $uri
 *   URI for the site.
 * @param array $data
 *   Associative array of data from Provision_Config_Drupal_Settings::data.
 *
 * @return string
 *   Lines to add to the site's settings.php file.
 *
 * @see Provision_Config_Drupal_Settings
 */
function aegir_fields_provision_drupal_config($uri, $data) {
  // Not sure WTF d() is, but it contains the values I'm looking for.
  $aegir_fields = d()->aegir_fields;

  $output = '/* From ' . basename(__FILE__) . ':' . __FUNCTION__ . '() */';
  if (!empty($aegir_fields)) {
    $output .= "\n";
    $output .= '$conf[\'aegir_fields\'] = ' . var_export($aegir_fields, 1) . ';';
  }
  else {
    $output .= "\n";
    $output .= '/* (no aegir_fields) */';
  }
  $output .= "\n";
  return $output;
}

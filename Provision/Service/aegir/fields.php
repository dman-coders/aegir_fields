<?php
/**
 * @file
 * The aegir_fields service base class.
 */

/**
 * The aegir_fields service base class.
 */
class Provision_Service_aegir_fields extends Provision_Service {
  public $service = 'aegir_fields';

  /**
   * This method is called when provision is initialising a site context.
   *
   * Add the needed properties to the site context.
   */
  static function subscribe_site($context) {
    $context->setProperty('aegir_fields');
  }

}

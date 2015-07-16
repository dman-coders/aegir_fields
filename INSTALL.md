For this utility to work, the drush.inc file must also be made available to 
aegir provisioning on the commandline, eg by copying or linking it in to 
the drush installs 'commands' folder.

sudo ln -s /var/aegir/hostmaster-*/sites/all/modules/aegir_fields/aegir_fields.drush.inc /usr/share/drush/commands/

After installation, you may 'verify' the target site, through the UI or with 
  sudo -u aegir drush @hostmaster provision-verify -v @my.site.alias
Re-saving the site node at any time should also trigger this.


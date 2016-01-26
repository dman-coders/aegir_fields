Aegir Fields Client
===================

Makes values passed down to a site from its Aegir hostmaster re-usable in the
site context.

aegir_fields (a contrib component of aegir hosting platform) may choose to
set values in a managed site to customize the site.
These values are inserted to the sites settings.php during aegir site validation.

This module extracts those values, and lets you use them in the site.

One way to do this is via tokens, eg by embedding the value
into a freetext area..

A token like [aegir_fields:field_site_slogan] may be set,
and you can use that where needed.


Under the hood
---------------

If the aegir_fields hostmaster has set a cck value called

    field_rss_url

then there will be a corresponding setting added to your sites settings.php,
in the shape of

    $conf['aegir_fields'] = array(
      'field_rss_url' => 'http://example.com/feed.rss',
    );

With this in place, you can now enable token_filter module, and edit a textarea
to include the markdown token string

    [aegir_fields:field_rss_url]

to use that value.

Caveat
------

As these values are overridden by hard-code in the settings.php at any given
time, and just *cannot* be meaningfully updated locally, as soon as you wish
to override these values, _stop using these tokens_ and do your own thing,

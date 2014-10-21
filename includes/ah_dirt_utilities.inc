<?php

/**
 * @file
 * harvests data from endpoints.
 */

/**
 * Retrieves DiRT data through REST.
 *
 * @global url $base_url
 *
 * @param string $nitems
 *   number of items to return
 * @param string $tool_name
 *   Name of tool to be returned
 */
function ah_dirt_fetch($nitems = NULL, $tool_name = NULL) {
  global $base_url;
  $url = "$base_url/rest";
  $api_key = variable_get('ah_dirt_api_key', '');
  $post_data = array(
    'api-key' => $api_key,
    'nitems' => $nitems,
    'tool_name' => $tool_name,
  );
  $data = http_build_query($post_data, '', '&');
  $options = array(
    'headers' => array('Accept' => 'application/json',
      'Content-Type' => 'application/x-www-form-urlencoded'),
    'method' => 'POST',
    'data' => $data
  );
  $response = drupal_http_request($url . '/tool/fetch', $options);
  return json_decode($response->data);
}

<?php

/**
 * @file
 * harvests data from endpoints.
 */
function ah_dirt_get_items() {
  $user = user_load_by_name('Rest User');
  $user_id = $user->uid;
  $base_url = 'http://localhost/DIRT';
  $data = array(
    'username' => 'Rest User',
    'password' => 'anypass',
  );
  $data = http_build_query($data, '', '&');
  $options = array(
    'headers' => array(
      'Accept' => 'application/json',
    ),
    'method' => 'POST',
    'data' => $data
  );
  $response = drupal_http_request($base_url . '/user/login', $options);

  $data = $response->data;
// Check if login was successful
  if ($response->code == 200) {
    // Now recycle the login cookie we recieved in the first request
    $options['headers']['Cookie'] = $data->session_name . '=' . $data->sessid;
    // Get info about a user
    $data = array();
    $options['data'] = http_build_query($data, '', '&');
    $options['method'] = 'GET';
    $response = drupal_http_request($base_url . "/user/$user_id", $options);
    dsm($response);
  }
}

/**
 *
module_load_include('inc', 'ah_dirt', 'includes/get_data');
ah_dirt_get_items();
 */
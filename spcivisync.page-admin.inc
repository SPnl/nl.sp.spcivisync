<?php

function spcivisync_admin_add_group_role_rules($form, &$form_state) {
  $form = array();
  $groups = spcivisync_get_civi_groups();
  $form['groups'] = array(
    '#type' => 'fieldset', 
    '#title' => 'CiviCRM groepen -> Drupal rollen',
  );
  $form['groups']['civi_groups'] = array(
    '#type' => 'select',
    '#title' => 'CiviCRM groepen',
    '#options' => $groups,
    '#multiple' => TRUE,
    '#required' => TRUE,
    '#description' => 'Mailgroepen worden niet weergegeven.',
  );
  $roles = spcivisync_get_roles();
  $form['groups']['drupal_roles'] = array(
    '#type' => 'select',
    '#title' => 'Drupal rol(len)',
    '#options' => $roles,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );

  $form['groups']['submit'] = array(
    '#type'  => 'submit',
    '#value' => 'Voeg toe',
    '#submit' => array('spcivisync_admin_add_group_role_rules_submit'),
  );

  return $form;
}

function spcivisync_admin_add_group_role_rules_submit($form, &$form_state) {
  //variable_set('spcivisync_rules', array());
  $duplicates = array();
  $values = $form_state['values'];
  // Create values to store.
  foreach ($values['civi_groups'] as $value) {
    $civi_groups[$value] = $form['groups']['civi_groups']['#options'][$value];
  }
  foreach ($values['drupal_roles'] as $value) {
    $drupal_roles[$value] = $form['groups']['drupal_roles']['#options'][$value];
  }
  // Store values.
  $rules = variable_get('spcivisync_rules', array());
  $new_rules = $rules;
  $new_rules['groups-roles'][] = array(
    'civi_groups' => $civi_groups,
    'drupal_roles' => $drupal_roles,
  );
  // Controleer of regel reeds bestaat.
  foreach ($new_rules['groups-roles'] as $key_a => $rule_a) {
    $duplicates[$key_a] = 0;
    foreach ($new_rules['groups-roles'] as $key_b => $rule_b) {
      if ($rule_a == $rule_b) {
        $duplicates[$key_a] ++;
        foreach ($duplicates as $number) {
          if ($number > 1) {
            // Regel bestaat reeds.
            drupal_set_message('Regel bestaat al, er is geen nieuwe regel toegevoegd.', 'error');
            return;
          }
        }
      }
    }
  }
  // Nieuwe regel.
  variable_set('spcivisync_rules', $new_rules);
  drupal_set_message('Regel is opgeslagen.');
}

function spcivisync_admin_add_relation_role_rules($form, &$form_state) {
  $form = array();
  $relations = spcivisync_get_civi_relationships();
  $form['relations'] = array(
    '#type' => 'fieldset', 
    '#title' => 'CiviCRM relaties -> Drupal rollen',
  );
  $form['relations']['civi_relations'] = array(
    '#type' => 'select',
    '#title' => 'CiviCRM relatie(s)',
    '#options' => $relations,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );
  $roles = spcivisync_get_roles();
  $form['relations']['drupal_roles'] = array(
    '#type' => 'select',
    '#title' => 'Drupal rol(len)',
    '#options' => $roles,
    '#multiple' => TRUE,
    '#required' => TRUE,
  );

  $form['relations']['submit'] = array(
    '#type'  => 'submit',
    '#value' => 'Voeg toe',
    '#submit' => array('spcivisync_admin_add_relation_role_rules_submit'),
  );

  return $form;
}

function spcivisync_admin_add_relation_role_rules_submit($form, &$form_state) {
  //variable_set('spcivisync_rules', array());
  $duplicates = array();
  $values = $form_state['values'];
  // Create values to store.
  foreach ($values['civi_relations'] as $value) {
    $civi_relations[$value] = $form['relations']['civi_relations']['#options'][$value];
  }
  foreach ($values['drupal_roles'] as $value) {
    $drupal_roles[$value] = $form['relations']['drupal_roles']['#options'][$value];
  }
  // Store values.
  $rules = variable_get('spcivisync_rules', array());
  $new_rules = $rules;
  $new_rules['relations-roles'][] = array(
    'civi_relations' => $civi_relations,
    'drupal_roles' => $drupal_roles,
  );
  // Controleer of regel reeds bestaat.
  foreach ($new_rules['relations-roles'] as $key_a => $rule_a) {
    $duplicates[$key_a] = 0;
    foreach ($new_rules['relations-roles'] as $key_b => $rule_b) {
      if ($rule_a == $rule_b) {
        $duplicates[$key_a] ++;
        foreach ($duplicates as $number) {
          if ($number > 1) {
            // Regel bestaat reeds.
            drupal_set_message('Regel bestaat al, er is geen nieuwe regel toegevoegd.', 'error');
            return;
          }
        }
      }
    }
  }
  // Nieuwe regel.
  variable_set('spcivisync_rules', $new_rules);
  drupal_set_message('Regel is opgeslagen.');
}

function spcivisync_set_field_options($options){
  if(is_array($options)) {
    return $options;
  } else {
    return null;
  }
}

function spcivisync_admin_add_field_field_rules($form, &$form_state) {
  $form = array();
  $form['fields'] = array(
    '#type' => 'fieldset', 
    '#title' => t('CiviCRM fields &rarr; Drupal fields'),
  );
  $form['fields']['civi_contact_simple_fields'] = array(
    '#type' => 'fieldset', 
    '#prefix' => '<h1>Synchronizeer:</h1><h4>eenvoudig veld</h4>',
  );

  $form['fields']['civi_contact_simple_fields']['civi_contact_simple_field'] = array(
    '#type' => 'select',
    '#empty_option' => t('-Select-'),
    '#options' => spcivisync_get_civi_contact_fields(),
  );

  $form['fields']['civi_contact_email_fields'] = array(
    '#type' => 'fieldset', 
    '#prefix' => '<h4>of email veld</h4>',
  );

  $form['fields']['civi_contact_email_fields']['civi_contact_email_primary_field'] = array(
    '#type' => 'checkbox',
    '#title' => 'Primair',
    '#suffix' => 'of',
  );

  $form['fields']['civi_contact_email_fields']['civi_contact_email_location_field'] = array(
    '#type' => 'select',
    '#empty_option' => t('-Select-'),
    '#options' => spcivisync_get_civi_email_locations(),
  );

  $form['fields']['civi_contact_phone_fields'] = array(
    '#type' => 'fieldset', 
    '#prefix' => '<h4>of telefoon veld</h4>',
  );

  $form['fields']['civi_contact_phone_fields']['civi_contact_phone_primary_field'] = array(
    '#type' => 'checkbox',
    '#title' => 'Primair',
    '#suffix' => 'of',
  );

  $form['fields']['civi_contact_phone_fields']['civi_contact_phone_location_field'] = array(
    '#type' => 'select',
    '#empty_option' => t('-Select-'),
    '#options' => spcivisync_get_civi_phone_locations(),
  );

  $form['fields']['civi_contact_phone_fields']['civi_contact_phone_type_field'] = array(
    '#type' => 'select',
     '#empty_option' => t('-Select phone type-'),
     '#options' => spcivisync_get_civi_phone_types(),
  );

  $form['fields']['civi_contact_address_fields'] = array(
    '#type' => 'fieldset', 
    '#prefix' => '<h4>of adres veld</h4>',
  );

  $form['fields']['civi_contact_address_fields']['civi_contact_address_primary_field'] = array(
    '#type' => 'checkbox',
    '#title' => 'Primair',
    '#suffix' => 'of',
  );

  $form['fields']['civi_contact_address_fields']['civi_contact_address_location_field'] = array(
    '#type' => 'select',
    '#title' => 'Selecteer type',
    '#empty_option' => t('-Select location field-'),
    '#options' => spcivisync_get_civi_address_locations(),
  );

  $form['fields']['civi_contact_address_fields']['civi_contact_address_field'] = array(
    '#type' => 'select',
    '#empty_option' => t('-Select adress field-'),
    '#options' => spcivisync_get_civi_address_fields(),
  );

  $drupal_fields = spcivisync_get_account_fields();
  spcivisync_cleanup_used_fields($drupal_fields); 
  $form['fields']['drupal_field'] = array(
    '#type' => 'select',
    '#prefix' => '<h1>Met:</h1><h4>Drupal account veld</h4>',
    '#required' => TRUE,
    '#options' => $drupal_fields,
  );

  $form['fields']['submit'] = array(
    '#type'  => 'submit',
    '#value' => 'Voeg toe',
    '#submit' => array('spcivisync_admin_add_field_field_rules_submit'),
  );

  return $form;
}

function spcivisync_admin_add_field_field_rules_validate($form, &$form_state) {
  $set = 0;
  $selected = array();
  $values = $form_state['values'];
  // Check which field to sync.
  // Check if simple field is selected.
  if ($values['civi_contact_simple_field']) {
    $set ++;
    $selected[] = 'civi_contact_simple_field';
  }
  // Check if email field is selected.
  if ($values['civi_contact_email_location_field'] || $values['civi_contact_email_primary_field']) {
    $set ++;
    if ($values['civi_contact_email_primary_field']) {
      $selected[] = 'civi_contact_email_primary_field';
    }
    if ($values['civi_contact_email_location_field']) {
      $selected[] = 'civi_contact_email_location_field';
    }
    // Check if not primary and location are selected.
    if ($values['civi_contact_email_location_field'] && $values['civi_contact_email_primary_field']) {
      form_set_error('civi_contact_email_primary_field', 'Selecteer of primair of een locatie, niet beiden!');
    }
  }
  // Check if phone fields are selected.
  if ($values['civi_contact_phone_location_field'] || $values['civi_contact_phone_type_field'] || $values['civi_contact_phone_primary_field']) {
    $set ++;
    if ($values['civi_contact_phone_primary_field']) {
      $selected[] = 'civi_contact_phone_primary_field';
    }
    if ($values['civi_contact_phone_location_field']) {
      $selected[] = 'civi_contact_phone_location_field';
    }
    if ($values['civi_contact_phone_type_field']) {
      $selected[] = 'civi_contact_phone_type_field';
    }
    // Check if not primary and other options are selected.
    if ($values['civi_contact_phone_primary_field'] && ($values['civi_contact_phone_location_field'] || $values['civi_contact_phone_type_field'])) {
      form_set_error('civi_contact_phone_primary_field', 'Selecteer of primair of de andere opties, niet beiden!');
    }
    // Check if both fields are set.
    if (!$values['civi_contact_phone_primary_field'] && !($values['civi_contact_phone_location_field'] && $values['civi_contact_phone_type_field'])) {
      if ($values['civi_contact_phone_location_field']) {
        form_set_error('civi_contact_phone_type_field', 'Selecteer zowel een telefoon locatie als type veld!');
      }
      else {
        form_set_error('civi_contact_phone_location_field', 'Selecteer zowel een telefoon locatie als type veld!');
      }
    }
  }
  // Check if address fields are selected.
  if ($values['civi_contact_address_location_field'] || $values['civi_contact_address_field'] || $values['civi_contact_address_primary_field']) {
    $set ++;
    if ($values['civi_contact_address_primary_field']) {
      $selected[] = 'civi_contact_address_primary_field';
    }
    if ($values['civi_contact_address_location_field']) {
      $selected[] = 'civi_contact_address_location_field';
    }
    if ($values['civi_contact_address_field']) {
      $selected[] = 'civi_contact_address_field';
    }
    // Check if not primary and other options are selected.
    if ($values['civi_contact_address_primary_field'] && ($values['civi_contact_address_location_field'] || $values['civi_contact_address_field'])) {
      form_set_error('civi_contact_address_primary_field', 'Selecteer of primair of de andere opties, niet beiden!');
    }
    // Check if both fields are set.
    if (!$values['civi_contact_address_primary_field'] && !($values['civi_contact_address_location_field'] && $values['civi_contact_address_field'])) {
      if ($values['civi_contact_address_location_field']) {
        form_set_error('civi_contact_address_type_field', 'Selecteer zowel een adres locatie als type veld!');
      }
      else {
        form_set_error('civi_contact_address_location_field', 'Selecteer zowel een adres locatie als type veld!');
      }
    }
  }
  if ($set == 0) {
    form_set_error('fields', 'Selecteer tenminste &eacute;&eacute;n CiviCRM type veld!');
  }
  if ($set > 1) {
    foreach ($selected as $error_field) {
      form_set_error($error_field, 'Selecteer slechts &eacute;&eacute;n type veld!');
    }
  }
}

function spcivisync_admin_add_field_field_rules_submit($form, &$form_state) {
  $values = $form_state['values'];
  $rules = variable_get('spcivisync_rules', array());
  // Create values to store.
  if ($values['civi_contact_simple_field']) {
    $rules['field-field'][]['simple'] = array(
      'simple_field' => $values['civi_contact_simple_field'],
      'drupal_field' => $values['drupal_field'],
    );
  }
  elseif ($values['civi_contact_email_primary_field']) {
    $rules['field-field'][]['email'] = array(
      'email_primary_field' => TRUE,
      'drupal_field' => $values['drupal_field'],
    );
  }
  elseif ($values['civi_contact_email_location_field']) {
    $rules['field-field'][]['email'] = array(
      'email_location_field' => $values['civi_contact_email_location_field'],
      'drupal_field' => $values['drupal_field'],
    );
  }
  elseif ($values['civi_contact_phone_primary_field']) {
    $rules['field-field'][]['phone'] = array(
      'phone_primary_field' => TRUE,
      'drupal_field' => $values['drupal_field'],
    );
  }
  elseif ($values['civi_contact_phone_location_field']) {
    $rules['field-field'][]['phone'] = array(
      'phone_location_field' => $values['civi_contact_phone_location_field'],
      'phone_type_field' => $values['civi_contact_phone_type_field'],
      'drupal_field' => $values['drupal_field'],
    );
  }
  elseif ($values['civi_contact_address_primary_field']) {
    $rules['field-field'][]['address'] = array(
      'address_primary_field' => TRUE,
      'drupal_field' => $values['drupal_field'],
    );
  }
  elseif ($values['civi_contact_address_location_field']) {
    $rules['field-field'][]['address'] = array(
      'address_location_field' => $values['civi_contact_address_location_field'],
      'address_field' => $values['civi_contact_address_field'],
      'drupal_field' => $values['drupal_field'],
    );
  }
  // Controleer of regel reeds bestaat.
  foreach ($rules['field-field'] as $key_a => $rule_a) {
    $duplicates[$key_a] = 0;
    foreach ($rules['field-field'] as $key_b => $rule_b) {
      if ($rule_a == $rule_b) {
        $duplicates[$key_a] ++;
        foreach ($duplicates as $number) {
          if ($number > 1) {
            // Regel bestaat reeds.
            drupal_set_message('Regel bestaat al, er is geen nieuwe regel toegevoegd.', 'error');
            return;
          }
        }
      }
    }
  }
  // Nieuwe regel.
  variable_set('spcivisync_rules', $rules);
  drupal_set_message('Regel is opgeslagen.');
  return;
}

function spcivisync_admin_add_relation_field_rules($form, &$form_state) {
  $form = array();
  $relations = spcivisync_get_civi_relationships();
  $form['relation-field'] = array(
    '#type' => 'fieldset', 
    '#title' => 'CiviCRM relaties -> Drupal velden',
  );
  $form['relation-field']['civi_relation'] = array(
    '#type' => 'select',
    '#title' => 'CiviCRM relatie(s)',
    '#options' => $relations,
    '#required' => TRUE,
    '#prefix' => '<h1>Synchronizeer:</h1><h4>Relatie</h4>',
  );

  $drupal_fields = spcivisync_get_account_fields();
  spcivisync_cleanup_used_fields($drupal_fields); 
  $form['relation-field']['drupal_field'] = array(
    '#type' => 'select',
    '#prefix' => '<h1>Met:</h1><h4>Drupal account veld</h4>',
    '#required' => TRUE,
    '#options' => $drupal_fields,
  );

  $form['relation-field']['submit'] = array(
    '#type'  => 'submit',
    '#value' => 'Voeg toe',
    '#submit' => array('spcivisync_admin_add_relation_field_rules_submit'),
  );

  return $form;
}

function spcivisync_admin_add_relation_field_rules_submit($form, &$form_state) {
  $values = $form_state['values'];

  // Create values to store.
  $store = array(
    $values['civi_relation'] => $form['relation-field']['civi_relation']['#options'][$values['civi_relation']],
  );

  // Store values.
  $rules = variable_get('spcivisync_rules', array());
  $new_rules = $rules;
  $new_rules['relation-field'][] = array(
    'civi_relation' => $store,
    'drupal_field' => $values['drupal_field'],
  );
  // Controleer of regel reeds bestaat.
  $duplicates = array();
  foreach ($new_rules['relation-field'] as $key_a => $rule_a) {
    $duplicates[$key_a] = 0;
    foreach ($new_rules['relation-field'] as $key_b => $rule_b) {
      if ($rule_a === $rule_b) {
        $duplicates[$key_a] ++;
        foreach ($duplicates as $number) {
          if ($number > 1) {
            // Regel bestaat reeds.
            drupal_set_message('Regel bestaat al, er is geen nieuwe regel toegevoegd.', 'error');
            return;
          }
        }
      }
    }
  }

  // Nieuwe regel.
  variable_set('spcivisync_rules', $new_rules);
  drupal_set_message('Regel is opgeslagen.');
}

function spcivisync_admin_list_rules() {
  $rules = variable_get('spcivisync_rules');
  $output = '';
  // Group - role rules.
  if (!empty($rules['groups-roles'])) {
    $output .= '<table><tr><th>Id</th><th>CiviCRM groepen</th><th></th><th>Drupal rollen</th><th></th></tr>';
    foreach($rules['groups-roles'] as $rule_id => $rule) {
      $output .= '<tr><td>' . $rule_id . '</td><td>';
      foreach ($rule['civi_groups'] as $id => $title) {
        $output .= $title . '<br/>';
      }
      $output .= '</td><td>&rarr;</td><td>';
      foreach ($rule['drupal_roles'] as $id => $title) {
        $output .= $title . '<br/>';
      }
      $output .= '</td><td><a href="/admin/config/sp/spcivisync/delete/groups-roles/' . $rule_id . '">' . t('Delete') . '</a></td></tr>';
    }
    $output .= '</table>';
  }

  // Relation - role rules.
  if (!empty($rules['relations-roles'])) {
    $output .= '<table><tr><th>Id</th><th>CiviCRM relaties</th><th></th><th>Drupal rollen</th><th></th></tr>';
    foreach($rules['relations-roles'] as $rule_id => $rule) {
      $output .= '<tr><td>' . $rule_id . '</td><td>';
      foreach ($rule['civi_relations'] as $id => $title) {
        $output .= $title . '<br/>';
      }
      $output .= '</td><td>&rarr;</td><td>';
      foreach ($rule['drupal_roles'] as $id => $title) {
        $output .= $title . '<br/>';
      }
      $output .= '</td><td><a href="/admin/config/sp/spcivisync/delete/relations-roles/' . $rule_id . '">' . t('Delete') . '</a></td></tr>';
    }
    $output .= '</table>';
  }

  // Field - field rules.
  if (!empty($rules['field-field'])) {
    $output .= '<table><tr><th>Id</th><th>CiviCRM velden</th><th></th><th>Drupal velden</th><th></th></tr>';
    $account_fields = spcivisync_get_account_fields();
    foreach ($rules['field-field'] as $rule_id => $rule) {
      $output .= '<tr><td>' . $rule_id . '</td>';
      if (isset($rule['simple'])) {
        $fields = spcivisync_get_civi_contact_fields(FALSE);
        $output .= '<td>' . $fields[$rule['simple']['simple_field']] . '</td><td>&rarr;</td><td>' . $account_fields[$rule['simple']['drupal_field']] . '</td>';
      }
      elseif (isset($rule['email']['email_primary_field'])) {
        $output .= '<td>Email (Primair)</td><td>&rarr;</td><td>' . $account_fields[$rule['email']['drupal_field']] . '</td>';
      }
      elseif (isset($rule['email']['email_location_field'])) {
        $locations = spcivisync_get_civi_email_locations(FALSE);
        $output .= '<td>Email (locatie: ' . $locations[$rule['email']['email_location_field']] . ')</td><td>&rarr;</td><td>' . $account_fields[$rule['email']['drupal_field']] . '</td>';
      }
      elseif (isset($rule['phone']['phone_primary_field'])) {
        $output .= '<td>Telefoon (Primair)</td><td>&rarr;</td><td>' . $account_fields[$rule['phone']['drupal_field']] . '</td>';
      }
      elseif (isset($rule['phone']['phone_location_field'])) {
        $locations = spcivisync_get_civi_phone_locations(FALSE);
        $types = spcivisync_get_civi_phone_types(FALSE);
        $output .= '<td>Telefoon (locatie: ' . $locations[$rule['phone']['phone_location_field']] . ', type: ' . $types[$rule['phone']['phone_type_field']]  . ')</td><td>&rarr;</td><td>' . $account_fields[$rule['phone']['drupal_field']] . '</td>';
      }
      elseif (isset($rule['address']['address_primary_field'])) {
        $output .= '<td>Adres (Primair)</td><td>&rarr;</td><td>' . $account_fields[$rule['address']['drupal_field']] . '</td>';
      }
      elseif (isset($rule['address']['address_location_field'])) {
        $locations = spcivisync_get_civi_address_locations(FALSE);
        $fields = spcivisync_get_civi_address_fields(FALSE);
        $output .= '<td>Adres (locatie: ' . $locations[$rule['address']['address_location_field']] . ', veld: ' . $fields[$rule['address']['address_field']]  . ')</td><td>&rarr;</td><td>' . $account_fields[$rule['address']['drupal_field']] . '</td>';
      }
      $output .= '<td><a href="/admin/config/sp/spcivisync/delete/field-field/' . $rule_id . '">' . t('Delete') . '</a></td></tr>';
    }
  }
  $output .= '</table>';

  // Relation - field rules.
  if (!empty($rules['relation-field'])) {
    $output .= '<table><tr><th>Id</th><th>CiviCRM relaties</th><th></th><th>Drupal velden</th><th></th></tr>';
    foreach($rules['relation-field'] as $rule_id => $rule) {
      $output .= '<tr><td>' . $rule_id . '</td><td>';
      foreach ($rule['civi_relation'] as $id => $title) {
        $output .= $title . '<br/>';
      }
      $output .= '</td><td>&rarr;</td><td>';
      $output .= $rule['drupal_field'] . '<br/>';
      $output .= '</td><td><a href="/admin/config/sp/spcivisync/delete/relation-field/' . $rule_id . '">' . t('Delete') . '</a></td></tr>';
    }
    $output .= '</table>';
  }

  if (empty($output)) {
    drupal_set_message('Er zijn nog geen regels aangemaakt.', 'warning');
  }
  return $output;
}

function spcivisync_admin_test_rules($form, &$form_state) {
  $form = array();
  $options = array();
  $users = spcivisync_get_users();
  foreach ($users as $user) {
    $options[$user->uid] = $user->name;
  }
  natsort($options);
  $form['user'] = array(
    '#type' => 'select',
    '#title' => 'Selecteer een gebruiker.',
    '#options' => $options,
    '#multiple' => FALSE,
    '#required' => TRUE,
  );

  $form['store'] = array(
    '#type' => 'checkbox',
    '#title' => 'Wijzigingen opslaan in database.',
  );

  $form['submit'] = array(
    '#type'  => 'submit',
    '#value' => 'Test',
    '#submit' => array('spcivisync_admin_test_rules_submit'),
  );

  return $form;
}

function spcivisync_admin_test_rules_submit($form, &$form_state) {
  $values = $form_state['values'];
  $user = user_load($values['user']);
  if ($values['store']) {
    $test = FALSE;
  }
  else {
    $test = TRUE;
  }
  spcivisync_sync_users(array($user), $test);
}

function spcivisync_admin_sync() {
  return '<a href="/admin/config/sp/spcivisync/sync/all">Synchronizeer alle gebruikers</a>';
}

function spcivisync_delete($type, $rule_id) {
  $rules = variable_get('spcivisync_rules');
  switch ($type) {
  case 'groups-roles':
    if (!empty($rules['groups-roles'][$rule_id])) {
      unset($rules['groups-roles'][$rule_id]);
      variable_set('spcivisync_rules', $rules);
      drupal_set_message('Rule was deleted.');
    }
    else {
      drupal_set_message('Error deleting rule.', 'error');
    }
    break;
  case 'relations-roles':
    if (!empty($rules['relations-roles'][$rule_id])) {
      unset($rules['relations-roles'][$rule_id]);
      variable_set('spcivisync_rules', $rules);
      drupal_set_message('Rule was deleted.');
    }
    else {
      drupal_set_message('Error deleting rule.', 'error');
    }
    break;
  case 'field-field':
    if (!empty($rules['field-field'][$rule_id])) {
      unset($rules['field-field'][$rule_id]);
      variable_set('spcivisync_rules', $rules);
      drupal_set_message('Rule was deleted.');
    }
    else {
      drupal_set_message('Error deleting rule.', 'error');
    }
    break;
  case 'relation-field':
    if (!empty($rules['relation-field'][$rule_id])) {
      unset($rules['relation-field'][$rule_id]);
      variable_set('spcivisync_rules', $rules);
      drupal_set_message('Rule was deleted.');
    }
    break;
  }
  drupal_goto('/admin/config/sp/spcivisync');
}

function spcivisync_cleanup_used_fields(&$drupal_fields) {
  // Cleanup already used fields
  $rules = variable_get('spcivisync_rules', array());
  if (!empty($rules['field-field'])) {
    foreach ($rules['field-field'] as $key => $value) {
      foreach (array('simple', 'email', 'phone', 'address') as $type) {
        if (isset($value[$type])) {
          unset($drupal_fields[$value[$type]['drupal_field']]);
        }
      }
    }
  }
  if (!empty($rules['relation-field'])) {
    foreach ($rules['relation-field'] as $key => $value) {
      if (isset($value['drupal_field'])) {
        unset($drupal_fields[$value['drupal_field']]);
      }
    }
  }
}

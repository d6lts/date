<?php

/**
 * @file
 * Views sort for a single date field, using Date API form selectors and SQL.
 */

/**
 * Views sort for a single date field, using Date API form selectors and SQL.
 */
class date_views_sort_handler_simple extends views_handler_sort_date {

  /**
   * Called to add the sort to a query.
   */
  function query() {
    $this->ensure_my_table();
    $field = field_info_field($this->definition['field_name']);
  
    // Initialize date sql handler to help generate the correct database and
    // fieldtype query strings.
    $date_handler = new date_sql_handler($field['type'], date_default_timezone());

    // Set timezones to ensure correct handling
    $date_handler->db_timezone = date_get_timezone_db($field['settings']['tz_handling']);
    $date_handler->local_timezone = date_get_timezone($field['settings']['tz_handling']);

    // Get formating based on granularity.
    $format = $date_handler->views_formats($this->options['granularity'], 'sql');

    // Create field string.
    $formula = $date_handler->sql_format($format,$date_handler->sql_field("$this->table_alias.$this->real_field"));
  
    // Order by newly created field string
    $this->query->add_orderby(NULL, $formula, $this->options['order'], $this->table_alias . '_' . $this->field . '_' . $this->options['granularity']);
  }

}

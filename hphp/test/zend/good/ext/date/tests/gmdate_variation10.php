<?php
/* Prototype  : string gmdate(string format [, long timestamp])
 * Description: Format a GMT date/time 
 * Source code: ext/date/php_date.c
 * Alias to functions: 
 */
<<__EntryPoint>> function main() {
echo "*** Testing gmdate() : usage variation ***\n";

// Initialise all required variables
date_default_timezone_set('Asia/Calcutta');
$timestamp = mktime(8, 8, 8, 8, 8, 2008);

echo "\n-- Testing gmdate() function with Timezone identifier format --\n";
var_dump( gmdate('e') );
var_dump( gmdate('e', $timestamp) );

echo "\n-- Testing gmdate() function with checking whether date is in daylight saving time format --\n";
var_dump( gmdate('I') );
var_dump( gmdate('I', $timestamp) );

echo "\n-- Testing gmdate() function with difference to GMT in hours format --\n";
var_dump( gmdate('O') );
var_dump( gmdate('O', $timestamp) );

echo "\n-- Testing gmdate() function with Difference to GMT in hours using colon as separator format --\n";
var_dump( gmdate('P') );
var_dump( gmdate('P', $timestamp) );

echo "\n-- Testing gmdate() function with timezone abbreviation format --\n";
var_dump( gmdate('T') );
var_dump( gmdate('T', $timestamp) );

echo "\n-- Testing gmdate() function with timezone offset format --\n";
var_dump( gmdate('T') );
var_dump( gmdate('T', $timestamp) );

echo "===DONE===\n";
}

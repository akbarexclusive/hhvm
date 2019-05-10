<?php
/* Prototype  : string mb_strrchr(string haystack, string needle[, bool part[, string encoding]])
 * Description: Finds the last occurrence of a character in a string within another 
 * Source code: ext/mbstring/mbstring.c
 * Alias to functions: 
 */
<<__EntryPoint>> function main() {
echo "*** Testing mb_strrchr() : error conditions ***\n";


//Test mb_strrchr with one more than the expected number of arguments
echo "\n-- Testing mb_strrchr() function with more than expected no. of arguments --\n";
$haystack = b'string_val';
$needle = b'string_val';
$part = true;
$encoding = 'string_val';
$extra_arg = 10;
try { var_dump( mb_strrchr($haystack, $needle, $part, $encoding, $extra_arg) ); } catch (Exception $e) { echo "\n".'Warning: '.$e->getMessage().' in '.__FILE__.' on line '.__LINE__."\n"; }

// Testing mb_strrchr with one less than the expected number of arguments
echo "\n-- Testing mb_strrchr() function with less than expected no. of arguments --\n";
$haystack = b'string_val';
try { var_dump( mb_strrchr($haystack) ); } catch (Exception $e) { echo "\n".'Warning: '.$e->getMessage().' in '.__FILE__.' on line '.__LINE__."\n"; }

echo "===DONE===\n";
}

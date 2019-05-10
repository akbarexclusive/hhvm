<?php
/* Prototype : bool unlink ( string $filename [, resource $context] );
   Description : Deletes filename
*/

/* Try deleting a file which is already deleted */
<<__EntryPoint>> function main() {
$file_path = getenv('HPHP_TEST_TMPDIR') ?? dirname(__FILE__);

// temp file used
$filename = "$file_path/unlink_variation4.tmp";

echo "*** Testing unlink() on deleted file ***\n";
// create temp file
$fp = fopen($filename, "w");
fclose($fp);

// delete temp file
var_dump( unlink($filename) );  // expected: true
var_dump( file_exists($filename) );  // confirm file deleted

// delete deleted file
var_dump( unlink($filename) );  // expected: false

echo "Done\n";
}

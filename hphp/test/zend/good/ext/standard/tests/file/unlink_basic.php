<?php
/* Prototype : bool unlink ( string $filename [, resource $context] );
   Description : Deletes filename
*/
<<__EntryPoint>> function main() {
$file_path = getenv('HPHP_TEST_TMPDIR') ?? dirname(__FILE__);

echo "*** Testing unlink() on a file ***\n";
$filename = "$file_path/unlink_basic.tmp";  // temp file name used here
$fp = fopen($filename, "w");  // create file
fwrite($fp, "Hello World");
fclose($fp);

// delete file
var_dump( unlink($filename) );
var_dump( file_exists($filename) );  // confirm file doesnt exist

echo "\n*** Testing unlink() : checking second argument ***\n";
// creating a context
$context = stream_context_create();
// temp file name used here
$filename = "$file_path/unlink_basic.tmp";
$fp = fopen($filename, "w");  // create file
fclose($fp);

// delete file
var_dump( unlink($filename, $context) );  // using $context in second argument
var_dump( file_exists($filename) );  // confirm file doesnt exist

echo "Done\n";
}

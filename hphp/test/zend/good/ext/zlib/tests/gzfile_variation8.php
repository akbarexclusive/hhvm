<?php

<<__EntryPoint>> function main() {
$filename = dirname(__FILE__)."/004.txt.gz";


$index_array = array(1, 2, 3);
$assoc_array = array(1 => 'one', 2 => 'two');

$variation = array(
  'empty array' => array(),
  'int indexed array' => $index_array,
  'associative array' => $assoc_array,
  'nested arrays' => array('foo', $index_array, $assoc_array),
  );


foreach ( $variation as $var ) {
  try { var_dump(gzfile( $filename, $var  ) ); } catch (Exception $e) { echo "\n".'Warning: '.$e->getMessage().' in '.__FILE__.' on line '.__LINE__."\n"; }
}
echo "===DONE===\n";
}

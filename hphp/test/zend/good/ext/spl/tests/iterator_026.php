<?hh
<<__EntryPoint>> function main(): void {
$ar = array(1, 2, array(31, 32, array(331)), 4);

$it = new RecursiveArrayIterator($ar);
$it = new RecursiveCachingIterator($it);
$it = new RecursiveIteratorIterator($it);

foreach($it as $k=>$v)
{
	echo "$k=>$v\n";
	echo "hasNext: " . ($it->getInnerIterator()->hasNext() ? "yes" : "no") . "\n";
}

echo "===DONE===\n";
}

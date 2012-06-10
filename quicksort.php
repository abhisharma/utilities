<?php
function partition(&$arr, $start, $end)
{
  $x = $arr[$end];
  $i = $start-1;
  for($j=$start; $j<$end; $j++)
   {
     if ($arr[$j] <= $x)
      {
	$i++;
	list($arr[$i],$arr[$j])  = array($arr[$j],$arr[$i]); //swap 
      }
   }
  list($arr[$i+1],$arr[$end])  = array($arr[$end],$arr[$i+1]); //swap
  return $i+1;
}
function quicksort(&$arr, $start, $end)
{
  if ($start < $end)
  {
    $pos = partition($arr, $start, $end);
    quicksort($arr, $start, $pos-1);
    quicksort($arr, $pos+1, $end);
  }

}
?>
<html>
<head>
<title>
Quicksort
</title>
</head>
<body>
<h1>Sorts an  integer array using quicksort</h1>
<?php
 // take an array and shuffle it
$ar = range(1,200);
shuffle($ar);
echo "Input array is ";
echo "[ ";
foreach($ar as $item)
{
    echo $item. ", ";
}
echo "]<br/><br/>";

// sort the array
quicksort($ar,0,count($ar)-1);

// print the output
echo "Output array is ";
echo "[ ";
foreach($ar as $item)
{
    echo $item. ", ";
}
echo "]";

?>
</body>
</html>
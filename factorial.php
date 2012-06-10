<html>
<head>
<title>
Compute Factorial
</title>
</head>
<body>
<h1>Computes factorial function</h1>
<?php
 // Computes a factorial function
function fact($x)
{
  if ($x == 0) return 1;
  else
  {
    return $x*fact($x-1);
  } 
}

// Execution starts here
if (array_key_exists('x', $_GET))
{
  $x = $_GET['x'];
}
if (!isset($x) || $x == NULL)
{
  echo "Please provide 'x=number' as the URL argument for computing factorial of number";
}
else
{
  for($index=1; $index<=$x; $index++)
  {
    $ans = fact($index);
    echo "Factorial of $index is $ans<br/>"; 
  }
}
echo<<<endTag
 This is
 end 
 of function
endTag
?>
</body>
</html>
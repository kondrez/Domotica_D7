<?php echo date('Y-m-d H:i:s');

$num = 1;

$str = file_get_contents('./webin.json');

$sensors = json_decode($str,true);
echo "<h2>";
echo "sensor 1:";
echo $sensors[sensor1];
echo "</h2>";
echo "<h2>";
echo "sensor 2:";
echo $sensors[sensor2];
echo "</h2>";
echo "<h2>";
echo "sensor 3:";
echo $sensors[sensor3];
echo "</h2>";

echo "<form action=\"test.php\" method=\"post\">";
echo "<input type=\"checkbox\" name=\"deur\" value=\"1\">";
echo "<span class=\"slider round\"></span>";
echo "</form>";

$arr = Array ("deur" => $_POST["deur"]);
$json = json_encode($arr);

file_put_contents("./webout.json", $json);
?>
<?php

$fd = fopen("mobile", "w");

$json = array();

$json["PAC"] = (float) $_POST["PAC"];
$json["KDY"] = (float) $_POST["KDY"];
$json["UL1"] = (float) $_POST["UL1"];
$json["TKK"] = (int) $_POST["TKK"];
$json["TNF"] = (float) $_POST["TNF"];

$string = json_encode($json);

fwrite($fd, $string);

fclose($fd);

?>
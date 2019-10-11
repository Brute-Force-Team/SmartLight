<?php
  if(isset($_POST['param'])){
    $params = json_decode($_POST['param'], true);
    $red = $params['red'];
    $green = $params['green'];
    $blue = $params['blue'];
    $id = $params['id'];
    $url_string = "/?text=$red-$green-$blue-$id";
    $url = "193.168.43.250";
    
    file_get_contents($url.$url_string);
    file_put_contents("configs",$url.$url_string);
  }
?>
